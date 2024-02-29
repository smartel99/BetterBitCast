/**
 * @file    deserializer.h
 * @author  Samuel Martel
 * @date    2022-10-11
 * @brief
 *
 * @copyright
 * This program is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 * You should have received a copy of the GNU General Public License along with this program. If
 * not, see <a href=https://www.gnu.org/licenses/>https://www.gnu.org/licenses/</a>.
 */

#ifndef GUARD_NILAI_SERVICES_DESERIALIZER_H
#define GUARD_NILAI_SERVICES_DESERIALIZER_H

#include "internals/concepts.h"

#include "internals/assert.h"
#include "internals/traits/always_false.h"
#include "internals/traits/is_array_like.h"
#include "internals/traits/is_specialization_of.h"
#include "internals/traits/serializable_container.h"

#include <bit>
#include <boost/pfr.hpp>
#include <cassert>
#include <string>
#include <type_traits>
#include <vector>

namespace bbc
{
namespace Internal
{
template<typename T>
concept IsEnum = std::is_enum_v<T>;
}
template<IntegralAndNotBool T, typename Begin, typename End>
T Deserialize(Begin&& b, End&& e);

template<std::same_as<float> T, typename Begin, typename End>
float Deserialize(Begin&& b, End&& e);

template<std::same_as<double> T, typename Begin, typename End>
double Deserialize(Begin&& b, End&& e);

template<std::same_as<bool> T, typename Begin, typename End>
bool Deserialize(Begin&& b, End&& e);

template<SerializableContainer T, typename Begin, typename End>
T Deserialize(Begin&& b, End&& e);

template<std::derived_from<Frasy::Internal::Enum> T, typename Begin, typename End>
T Deserialize(Begin&& b, End&& e);

template<typename T, typename Begin, typename End>
T Deserialize(Begin&& b, End&& e);


template<IntegralAndNotBool T, typename Begin, typename End>
T Deserialize(Begin&& b, End&& e)
{
    constexpr size_t N = sizeof(T);
    T                t = {};
    for (size_t i = 1; i <= sizeof(T); i++)
    {
        t |= static_cast<T>(*b) << ((N * 8) - (i * 8));
        ++b;
    }
    return t;
}

template<Internal::IsEnum T, typename Begin, typename End>
T Deserialize(Begin&& b, End&& e)
{
    return static_cast<T>(Deserialize<std::underlying_type_t<T>>(b, e));
}

template<std::same_as<float> T, typename Begin, typename End>
float Deserialize(Begin&& b, End&& e)
{
    static_assert(sizeof(uint32_t) == sizeof(float));
    return std::bit_cast<float>(Deserialize<uint32_t>(b, e));
}

template<std::same_as<double> T, typename Begin, typename End>
double Deserialize(Begin&& b, End&& e)
{
    static_assert(sizeof(uint64_t) == sizeof(double));
    return std::bit_cast<double>(Deserialize<uint64_t>(b, e));
}

template<std::same_as<bool> T, typename Begin, typename End>
bool Deserialize(Begin&& b, End&& e)
{
    ASSERT(static_cast<int>(sizeof(bool)) <= std::distance(b, e),
           "Not enough data, need %d, got %d",
           sizeof(bool),
           std::distance(b, e));
    bool v = (*b) == 0x01;
    b++;
    return v;
}

template<SerializableContainer T, typename Begin, typename End>
T Deserialize(Begin&& b, End&& e)
{
    using VT = typename T::value_type;

    T                t;
    uint16_t         size      = Deserialize<uint16_t>(b, e);    // Get reported size from serializer
    constexpr size_t arraySize = sizeof(T) / sizeof(VT);
    if constexpr (std::is_same_v<std::array<VT, arraySize>, T>)
    {
        // Array, check size is valid
        ASSERT(size == arraySize, "Received invalid size for array, need %d, got %d", arraySize, size);
    }
    else if constexpr (std::is_same_v<std::vector<VT>, T>)
    {
        // Vector, must resize
        t.resize(size);
    }
    else if constexpr (std::is_same_v<std::string, T>)
    {
        // String, must resize
        t.resize(size);
    }
    else { static_assert(Brigerad::always_false_v<T>, "Invalid type for container deserialization"); }

    for (size_t i = 0; i < size; ++i) { t[i] = Deserialize<VT>(b, e); }
    return t;
}

template<std::derived_from<Frasy::Internal::Enum> T, typename Begin, typename End>
T Deserialize(Begin&& b, End&& e)
{
    return T {Deserialize<typename T::underlying_type>(b, e)};
}

template<typename T, typename Begin, typename End>
T Deserialize(Begin&& b, End&& e)
{
    T t;
    boost::pfr::for_each_field(t, [&](auto&& i) { i = Deserialize<std::remove_cvref_t<decltype(i)>>(b, e); });
    return t;
}

}    // namespace Frasy

//!@}

#endif    // GUARD_NILAI_SERVICES_DESERIALIZER_H

/**
 * @file    is_complete.h
 * @author  Samuel Martel
 * @date    2023-03-07
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

#ifndef INSTRUMENTATION_BOARD_MAIN_UTILS_TRAITS_IS_COMPLETE_H
#define INSTRUMENTATION_BOARD_MAIN_UTILS_TRAITS_IS_COMPLETE_H

#include <type_traits>

namespace Brigerad
{
template<typename T, typename = void>
struct is_complete
{
    static constexpr bool value = false;
};

template<typename T>
struct is_complete<T, std::void_t<decltype(sizeof(T))>>
{
    static constexpr bool value = true;
};

/**
 * @brief True if type T is complete.
 *
 * This uses SFINAE to determine the completeness of a type through the attempt of determining its size.
 * Since sizeof cannot be used to determine the size of an incomplete type, the expression <code>decltype(sizeof(T))</code> is not valid,
 * thus removing the <code>true</code> candidate value from the candidate set with <code>std::void_t</code>.
 *
 * @tparam T
 */
template<typename T>
static constexpr bool is_complete_v = is_complete<T>::value;
}    // namespace Brigerad

#endif    // INSTRUMENTATION_BOARD_MAIN_UTILS_TRAITS_IS_COMPLETE_H

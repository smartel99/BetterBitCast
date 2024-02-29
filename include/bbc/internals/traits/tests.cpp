/**
 * @file    tests.cpp
 * @author  Samuel Martel
 * @date    2023-02-15
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
#include "is_array_like.h"
#include "is_complete.h"
#include "is_specialization_of.h"

#include <string>

namespace Brigerad
{
namespace
{
// <editor-fold desc="is_array_like">
static_assert(is_array_like<char[]>::value);
static_assert(is_array_like<char[1]>::value);
static_assert(is_array_like<char[1][1]>::value);
static_assert(is_array_like<std::array<int, 1>>::value);
static_assert(is_array_like<std::array<std::array<int, 1>, 1>>::value);

static_assert(is_array_like_v<char[]>);
static_assert(is_array_like_v<char[1]>);
static_assert(is_array_like_v<char[1][1]>);
static_assert(is_array_like_v<std::array<int, 1>>);
static_assert(is_array_like_v<std::array<std::array<int, 1>, 1>>);

static_assert(array_like<char[]>);
static_assert(array_like<char[1]>);
static_assert(array_like<char[1][1]>);
static_assert(array_like<std::array<int, 1>>);
static_assert(array_like<std::array<std::array<int, 1>, 1>>);

static_assert(!is_array_like<int>::value);
static_assert(!is_array_like<std::vector<int>>::value);
static_assert(!is_array_like<std::string>::value);

static_assert(!is_array_like_v<int>);
static_assert(!is_array_like_v<std::vector<int>>);
static_assert(!is_array_like_v<std::string>);

static_assert(!array_like<int>);
static_assert(!array_like<std::vector<int>>);
static_assert(!array_like<std::string>);
// </editor-fold>

// <editor-fold desc="is_specialization_of">
template<typename>
struct Foo;
static_assert(is_specialization_of<std::vector<int>, std::vector>::value);
static_assert(is_specialization_of<std::string, std::basic_string>::value);
static_assert(is_specialization_of<Foo<int>, Foo>::value);
// static_assert(is_specialization_of<std::array<int,1>, std::array>::value);

static_assert(is_specialization_of_v<std::vector<int>, std::vector>);
static_assert(is_specialization_of_v<std::string, std::basic_string>);
static_assert(is_specialization_of_v<Foo<int>, Foo>);
// static_assert(is_specialization_of_v<std::array<int,1>, std::array>);

static_assert(specializes<std::vector<int>, std::vector>);
static_assert(specializes<std::string, std::basic_string>);
static_assert(specializes<Foo<int>, Foo>);
// static_assert(specializes<std::array<int,1>, std::array>);

static_assert(!specializes<int, std::vector>);
// </editor-fold>

// <editor-fold desc="is_complete">
namespace
{
struct Foo
{
};
struct Bar;

static_assert(is_complete_v<int>, "Int should be complete!");
static_assert(is_complete_v<Foo>, "Foo should be complete!");
static_assert(!is_complete_v<Bar>, "Bar should not be complete!");
}    // namespace
// </editor-fold>

}    // namespace
}    // namespace Brigerad

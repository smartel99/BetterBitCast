/**
* @file    is_specialization_of.h
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

#ifndef INSTRUMENTATION_BOARD_MAIN_UTILS_TRAITS_IS_SPECIALIZATION_OF_H
#define INSTRUMENTATION_BOARD_MAIN_UTILS_TRAITS_IS_SPECIALIZATION_OF_H

#include <type_traits>
#include <vector>


namespace Brigerad
{
template<typename T, template<typename...> typename Base>
struct is_specialization_of : std::false_type
{
};

template<template<typename...> typename Base, typename... Args>
struct is_specialization_of<Base<Args...>, Base> : std::true_type
{
};

/**
* Checks if T is a specialization of template Base
* @tparam T
* @tparam Base
*
* @bug Does not work with std::array
*/
template<typename T, template<typename...> typename Base>
static constexpr bool is_specialization_of_v = is_specialization_of<T, Base>::value;

/**
* Constrains T to specializations of Base
* @tparam T
* @tparam Base
*
* @bug Does not work with std::array
*/
template<typename T, template<typename...> typename Base>
concept specializes = is_specialization_of_v<T, Base>;

}    // namespace Brigerad
#endif    // INSTRUMENTATION_BOARD_MAIN_UTILS_TRAITS_IS_SPECIALIZATION_OF_H

/**
 * @file    always_false.h
 * @author  Samuel Martel
 * @date    2023-02-24
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

#ifndef GUARD_BRIGERAD_UTILS_TRAITS_ALWAYS_FALSE_H
#define GUARD_BRIGERAD_UTILS_TRAITS_ALWAYS_FALSE_H

namespace Brigerad
{
    template<typename T>
    struct always_false
    {
        static constexpr bool value = false;
    };

    template<typename T>
    static constexpr bool always_false_v = always_false<T>::value;
}

#endif
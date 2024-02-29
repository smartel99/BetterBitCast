/**
 * @file    assert.h
 * @author  Samuel Martel
 * @date    2022-09-14
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

#ifndef GUARD_ASSERT_H
#define GUARD_ASSERT_H
#include <csignal>

#if !defined(NDEBUG)
#    if defined(SIGTRAP)
#        define ABORTION_SIGNAL SIGTRAP
#    else
#        define ABORTION_SIGNAL SIGABRT
#    endif
#    define ASSERT(x, msg, ...)                                                                    \
        do                                                                                         \
        {                                                                                          \
            if (!(x))                                                                              \
            {                                                                                      \
                ESP_LOGE("assert", "%s:%i " msg, __FILE__, __LINE__ __VA_OPT__(, ) __VA_ARGS__);   \
                raise(ABORTION_SIGNAL);                                                            \
            }                                                                                      \
        } while (0)
#else
#    define ASSERT(x, msg, ...) x
#endif

#endif    // GUARD_ASSERT_H

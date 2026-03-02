/**
 * @file test_macro.h
 * @brief Brief description
 * @version 0.1
 * @date 2026-03-02
 *
 * SPDX-FileCopyrightText: 2026 CYK-Dot <chenyukai@xmurcs.cn>
 * SPDX-License-Identifier: GPL-3.0-only

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef TEST_MACRO_H__
#define TEST_MACRO_H__

#include <string.h>
#include <stdio.h>

#define ASSERT_STR_EQ(string1, string2, errno_msg) do { \
    int ret = strcmp((string1), (string2));             \
    if (ret != 0) {                                     \
        printf("[FAILED] reason: %s\n", #errno_msg);    \
        return 1;                                       \
    }                                                   \
} while (0)

#define ASSERT_EQ(val1, val2, errno_msg) do {        \
    if (val1 != val2) {                              \
        printf("[FAILED] reason: %s\n", #errno_msg); \
        return 1;                                    \
    }                                                \
} while (0)

#define TESTCASE(case_name) \
    int case_name(void)

#define RUN_TEST(case_name) do {                           \
    int ret = case_name();                                 \
    if (ret != 0) {                                        \
        printf("[FAILED] testcase %s fail.\n", #case_name);\
        return ret;                                        \
    }                                                      \
} while (0)

#endif
/**
 * @file example_inherit.c
 * @brief 继承测试用例实现文件
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
#include "example_inherit.h"

void IMPL_METHOD_PUB(limited_counter, set_max)(limited_counter *pthis, uint32_t max_val) {
    pthis->MEMBER_PUB(max_value) = max_val;
}

uint32_t IMPL_METHOD_PUB(limited_counter, get_max)(limited_counter *pthis) {
    return pthis->MEMBER_PUB(max_value);
}

void IMPL_METHOD_CTOR(limited_counter)(limited_counter *pthis, uint32_t initial_value, uint32_t max_val) {
    counter *base = THIS_PARENT(pthis, counter);
    METHOD_CTOR(counter)(base, initial_value);
    pthis->MEMBER_PUB(max_value) = max_val;
}

void IMPL_METHOD_DTOR(limited_counter)(limited_counter *pthis) {
    // 简单继承不需要特殊清理
    (void)pthis;
}
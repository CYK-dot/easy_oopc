/**
 * @file example_encap.c
 * @brief 封装测试用例实现文件
 * @version 0.1
 * @date 2026-03-01
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
#include "example_encap.h"

uint32_t IMPL_METHOD_PUB(counter, get_value)(counter *pthis) {
    return pthis->MEMBER_PUB(value);
}

void IMPL_METHOD_PUB(counter, increment)(counter *pthis) {
    pthis->MEMBER_PUB(value)++;
}

void IMPL_METHOD_PUB(counter, decrement)(counter *pthis) {
    if (pthis->MEMBER_PUB(value) > 0) {
        pthis->MEMBER_PUB(value)--;
    }
}

void IMPL_METHOD_PUB(counter, reset)(counter *pthis) {
    pthis->MEMBER_PUB(value) = 0;
}

void IMPL_METHOD_CTOR(counter)(counter *pthis, uint32_t initial_value) {
    pthis->MEMBER_PUB(value) = initial_value;
}

void IMPL_METHOD_DTOR(counter)(counter *pthis) {
    // 简单计数器不需要特殊清理
    (void)pthis;
}

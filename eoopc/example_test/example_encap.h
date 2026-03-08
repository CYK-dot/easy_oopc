/**
 * @file example_encap.h
 * @brief 封装测试用例头文件
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
#ifndef EXAMPLE_ENCAP_H__
#define EXAMPLE_ENCAP_H__

#include <stddef.h>
#include <stdint.h>
#include "eoopc.h"

/**
 * @brief 一个简单的计数器类，用于演示封装特性
 */
CLASS_DECLARE(counter);
    OBJECT_DECLARE(
        counter,
        uint32_t MEMBER_PUB(value);
    );
    uint32_t METHOD_PUB(counter, get_value)(counter *pthis);
    void METHOD_PUB(counter, increment)(counter *pthis);
    void METHOD_PUB(counter, decrement)(counter *pthis);
    void METHOD_PUB(counter, reset)(counter *pthis);
    void METHOD_CTOR(counter)(counter *pthis, uint32_t initial_value);
    void METHOD_DTOR(counter)(counter *pthis);
END_CLASS(counter);

#endif
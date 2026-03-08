/**
 * @file example_polymo.c
 * @brief 多态测试用例实现文件
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
#include "example_polymo.h"
#include <stdio.h>

#define PI_CONST 3.1415926f

static TYPE_VTABLE(shape) IMPL_VTABLE(shape, default_vtbl) = {
    .NAME_VMETHOD_PUB(get_area) = NULL,  // 基类不实现
    .NAME_VMETHOD_PUB(draw) = NULL,      // 基类不实现
};

void IMPL_METHOD_CTOR(shape)(shape *pthis, float x, float y) {
    pthis->MEMBER_PUB(x) = x;
    pthis->MEMBER_PUB(y) = y;
    CTOR_VTABLE(pthis, shape, default_vtbl);
}

void IMPL_METHOD_DTOR(shape)(shape *pthis) {
    (void)pthis;
}

static float IMPL_VMETHOD_PUB(circle, overrided_get_area)(shape *pthis_base) {
    circle *pthis = THIS_CHILD(pthis_base, shape, circle);
    return PI_CONST * pthis->MEMBER_PUB(radius) * pthis->MEMBER_PUB(radius);
}

static void IMPL_VMETHOD_PUB(circle, overrided_draw)(shape *pthis_base) {
    circle *pthis = THIS_CHILD(pthis_base, shape, circle);
    printf("Drawing circle at (%.2f, %.2f) with radius %.2f\n",
           pthis_base->MEMBER_PUB(x), pthis_base->MEMBER_PUB(y), pthis->MEMBER_PUB(radius));
}

static TYPE_VTABLE(shape) IMPL_VTABLE(circle, overrided_vtbl) = {
    CTOR_VMETHOD_PUB(get_area, circle, overrided_get_area),
    CTOR_VMETHOD_PUB(draw, circle, overrided_draw),
};

void IMPL_METHOD_CTOR(circle)(circle *pthis, float x, float y, float radius) {
    shape *base = THIS_PARENT(pthis, shape);
    METHOD_CTOR(shape)(base, x, y);
    pthis->MEMBER_PUB(radius) = radius;
    CTOR_VTABLE(base, circle, overrided_vtbl);
}

void IMPL_METHOD_DTOR(circle)(circle *pthis) {
    (void)pthis;
}

static float IMPL_VMETHOD_PUB(rectangle, overrided_get_area)(shape *pthis_base) {
    rectangle *pthis = THIS_CHILD(pthis_base, shape, rectangle);
    return pthis->MEMBER_PUB(width) * pthis->MEMBER_PUB(height);
}

static void IMPL_VMETHOD_PUB(rectangle, overrided_draw)(shape *pthis_base) {
    rectangle *pthis = THIS_CHILD(pthis_base, shape, rectangle);
    printf("Drawing rectangle at (%.2f, %.2f) with width %.2f, height %.2f\n",
           pthis_base->MEMBER_PUB(x), pthis_base->MEMBER_PUB(y), pthis->MEMBER_PUB(width), pthis->MEMBER_PUB(height));
}

static TYPE_VTABLE(shape) IMPL_VTABLE(rectangle, overrided_vtbl) = {
    CTOR_VMETHOD_PUB(get_area, rectangle, overrided_get_area),
    CTOR_VMETHOD_PUB(draw, rectangle, overrided_draw),
};

void IMPL_METHOD_CTOR(rectangle)(rectangle *pthis, float x, float y, float width, float height) {
    shape *base = THIS_PARENT(pthis, shape);
    METHOD_CTOR(shape)(base, x, y);
    pthis->MEMBER_PUB(width) = width;
    pthis->MEMBER_PUB(height) = height;
    CTOR_VTABLE(base, rectangle, overrided_vtbl);
}

void IMPL_METHOD_DTOR(rectangle)(rectangle *pthis) {
    (void)pthis;
}
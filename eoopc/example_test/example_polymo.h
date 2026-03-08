/**
 * @file example_polymo.h
 * @brief 多态测试用例头文件
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
#ifndef EXAMPLE_POLYMO_H__
#define EXAMPLE_POLYMO_H__

#include <stdint.h>
#include "eoopc.h"
#include "example_inherit.h"

CLASS_DECLARE(shape);
    VTABLE_DECLARE(
        shape,
        float VMETHOD_PUB(get_area)(shape *pthis);
        void VMETHOD_PUB(draw)(shape *pthis);
    );
    OBJECT_DECLARE(
        shape,
        HAVE_VTABLE(shape);
        float MEMBER_PUB(x);
        float MEMBER_PUB(y);
    );
    void METHOD_CTOR(shape)(shape *pthis, float x, float y);
    void METHOD_DTOR(shape)(shape *pthis);
END_CLASS(shape);

CLASS_DECLARE(circle);
    OBJECT_DECLARE(
        circle,
        HAVE_PARENT(shape);
        float MEMBER_PUB(radius);
    );
    void METHOD_CTOR(circle)(circle *pthis, float x, float y, float radius);
    void METHOD_DTOR(circle)(circle *pthis);
END_CLASS(circle);

CLASS_DECLARE(rectangle);
    OBJECT_DECLARE(
        rectangle,
        HAVE_PARENT(shape);
        float MEMBER_PUB(width);
        float MEMBER_PUB(height);
    );
    void METHOD_CTOR(rectangle)(rectangle *pthis, float x, float y, float width, float height);
    void METHOD_DTOR(rectangle)(rectangle *pthis);
END_CLASS(rectangle);

#endif
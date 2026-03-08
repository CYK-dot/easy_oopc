/**
 * @file test.c
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
#include "test_macro.h"
#include "example_encap.h"
#include "example_inherit.h"
#include "example_polymo.h"

TESTCASE(basic_encap)
{
    counter c;
    float result;

    // 测试初始值
    METHOD_CTOR(counter)(&c, 0);
    ASSERT_EQ(METHOD_PUB(counter, get_value)(&c), 0, "counter初始值错误");

    // 测试递增
    METHOD_PUB(counter, increment)(&c);
    ASSERT_EQ(METHOD_PUB(counter, get_value)(&c), 1, "counter递增后值错误");

    // 测试递增多次
    METHOD_PUB(counter, increment)(&c);
    METHOD_PUB(counter, increment)(&c);
    ASSERT_EQ(METHOD_PUB(counter, get_value)(&c), 3, "多次increment后值错误");

    // 测试递减
    METHOD_PUB(counter, decrement)(&c);
    ASSERT_EQ(METHOD_PUB(counter, get_value)(&c), 2, "decrement后值错误");

    // 测试重置
    METHOD_PUB(counter, reset)(&c);
    ASSERT_EQ(METHOD_PUB(counter, get_value)(&c), 0, "reset后值错误");

    METHOD_DTOR(counter)(&c);
    return 0;
}

TESTCASE(basic_inherit)
{
    limited_counter lc;
    float result;

    // 测试继承的counter功能
    METHOD_CTOR(limited_counter)(&lc, 0, 10);
    counter *pc = THIS_PARENT(&lc, counter);
    ASSERT_EQ(METHOD_PUB(limited_counter, get_value)(pc), 0, "limited_counter初始值错误");

    // 测试递增到上限
    METHOD_PUB(counter, increment)(pc);
    ASSERT_EQ(METHOD_PUB(limited_counter, get_value)(pc), 1, "limited_counter递增后值错误");

    // 测试设置最大值
    METHOD_PUB(limited_counter, set_max)(&lc, 5);
    ASSERT_EQ(METHOD_PUB(limited_counter, get_max)(&lc), 5, "set_max设置错误");

    // 测试析构
    METHOD_DTOR(limited_counter)(&lc);
    return 0;
}

TESTCASE(basic_polymo)
{
    shape *pshape;
    circle c;
    rectangle r;
    float area;

    // 测试 circle 多态
    METHOD_CTOR(circle)(&c, 0.0f, 0.0f, 1.0f);
    pshape = THIS_PARENT(&c, shape);
    
    area = CALL_VMETHOD_PUB(pshape, get_area) (pshape);
    ASSERT_NEAR(area, 3.1415926f, "circle面积计算错误", 0.001f);
    
    CALL_VMETHOD_PUB(pshape, draw);

    // 测试 rectangle 多态
    METHOD_CTOR(rectangle)(&r, 0.0f, 0.0f, 3.0f, 4.0f);
    pshape = THIS_PARENT(&r, shape);
    
    area = CALL_VMETHOD_PUB(pshape, get_area) (pshape);
    ASSERT_EQ(area, 12.0f, "rectangle面积计算错误");    
    
    CALL_VMETHOD_PUB(pshape, draw);

    METHOD_DTOR(circle)(&c);
    METHOD_DTOR(rectangle)(&r);
    return 0;
}

int main(void)
{
    RUN_TEST(basic_encap);
    RUN_TEST(basic_inherit);
    RUN_TEST(basic_polymo);
    printf("[OK] all testcase passed.\n");
    return 0;
}
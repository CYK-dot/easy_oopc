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
    animal dog;
    CONSTRUCT(&dog, animal_ctor, "dog");
    ASSERT_STR_EQ(dog.name, "dog", "constructor of dog not act as expected.");

    int last_health = dog.health;
    animal_eat(&dog, 5);
    ASSERT_EQ(dog.health, last_health + 5, "method animal_eat not act as expected.");

    last_health = dog.health;
    animal_starve(&dog);
    animal_starve(&dog);
    ASSERT_EQ(dog.health, last_health - 1, "method animal_starve not act as expected.");

    return 0;
}

TESTCASE(basic_inherit)
{
    human lihua;
    CONSTRUCT(&lihua, human_ctor, "Lihua", "China");

    animal *lihua_super = THIS_PARENT(&lihua, animal);
    int last_health = lihua_super->health;
    animal_eat(lihua_super, 5);
    ASSERT_EQ(lihua_super->health, last_health + 5, "method animal_eat not act as expected.");

    human_travel(&lihua, "America");
    char where[200] = {0};
    human_is_at_where(&lihua, where, 200);
    ASSERT_STR_EQ(where, "America", "method human_is_at_where not act as expected.");

    return 0;
}

TESTCASE(basic_polymo)
{
    file_device obj;
    CONSTRUCT(&obj, file_ctor);
    file_set_path(&obj, "./example_test.txt");

    device *obj_super = THIS_PARENT(&obj, device);
    device_write(obj_super, "Hello World", sizeof("Hello World"));

    char buf[200] = {0};
    device_read(obj_super, buf, sizeof("Hello World"));
    ASSERT_STR_EQ(buf, "Hello World", "polymo call failed.");

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
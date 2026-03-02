/**
 * @file example.c
 * @brief Brief description
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
#include <string.h>
#include <stdio.h>
#include "example_encap.h"

CONSTRUCT_METHOD(animal_ctor, animal, char *name)
{
    pthis->name = name; /** public成员，通过->或.运算符直接访问 */
    PUBLIC_MEMBER_REF(pthis, health) = 50; /** public成员，也可以通过PUBLIC_MEMBER_REF访问 */
    PRIVATE_MEMBER_REF(pthis, starve_times) = 0;
}

static void animal_starve_caculator(animal *pthis) /** 在.c文件中定义静态函数，构成私有方法 */
{
    pthis->health -= PRIVATE_MEMBER_REF(pthis, starve_times); 
    PRIVATE_MEMBER_REF(pthis, starve_times)++;
}

void animal_eat(animal *pthis, int food_energy)
{
    pthis->health += food_energy;
    PRIVATE_MEMBER_REF(pthis, starve_times) = 0;
}

void animal_starve(animal *pthis)
{
    animal_starve_caculator(pthis);
}
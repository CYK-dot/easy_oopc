/**
 * @file example.h
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
#ifndef EXAMPLE_H__
#define EXAMPLE_H__

#include <stddef.h>
#include <stdint.h>
#include "eoopc.h"

CLASS_DECLARE(animal)              /** animal类 */
    char *name;                    /** 在类中声明变量，默认为pubilic成员 */
    PUBLIC_MEMBER(int, health);    /** 也可以使用PUBLIC_MEMBER，声明public成员 */
    PRIVATE_MEMBER(int ,starve_times);
DECLARE_END(animal);

/** 构造函数，签名为void animal_default_ctor(animal *pthis, char *name) */
CONSTRUCT_METHOD(animal_ctor, animal, char *name); 
/** public方法 */
void animal_eat(animal *pthis, int food_energy);
void animal_starve(animal *pthis);

#endif
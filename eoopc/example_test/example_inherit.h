/**
 * @file example_inherit.h
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
#ifndef EXAMPLE_INHERIT_H__
#define EXAMPLE_INHERIT_H__

#include "eoopc.h"
#include "example_encap.h"

CLASS_DECLARE(human)
    PRIVATE_MEMBER(char, position_now[200]);
    CLASS_EXTERND(animal);
DECLARE_END(human);

CONSTRUCT_METHOD(human_ctor, human, char *name, char *birth_country); 
void human_travel(human *pthis, char *destination);
void human_is_at_where(human *pthis, char *out_buf, size_t out_max);

#endif
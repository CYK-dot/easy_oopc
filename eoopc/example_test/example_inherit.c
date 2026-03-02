/**
 * @file example_inherit.c
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
#include <string.h>
#include <stdbool.h>
#include "example_inherit.h"

CONSTRUCT_METHOD(human_ctor, human, char *name, char *birth_country)
{
    CONSTRUCT_BRINGUP(animal, animal_ctor, name);
    char *buf = PRIVATE_MEMBER_REF(pthis, position_now);
    strcpy(buf, birth_country);
}

void human_travel(human *pthis, char *destination)
{
    if (strlen(destination) >= sizeof(PRIVATE_MEMBER_REF(pthis, position_now))) {
        return;
    }
    char *buf = PRIVATE_MEMBER_REF(pthis, position_now);
    strcpy(buf, destination);
}

void human_is_at_where(human *pthis, char *out_buf, size_t out_max)
{
    if (strlen(PRIVATE_MEMBER_REF(pthis, position_now)) >= (out_max - 1)) {
        return;
    }
    strcpy(out_buf, PRIVATE_MEMBER_REF(pthis, position_now));
}
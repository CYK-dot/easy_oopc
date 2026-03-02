/**
 * @file example_polymo.h
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
#ifndef EXAMPLE_POLYMO_H__
#define EXAMPLE_POLYMO_H__

#include <stdint.h>
#include "eoopc.h"

CLASS_DECLARE(device)
    VMETHOD(int, v_write, device, const uint8_t *data, size_t size);
    VMETHOD(int, v_read, device, uint8_t *data, size_t size);
DECLARE_END(device);
void device_write(device *pthis, const uint8_t *data, size_t size);
void device_read(device *pthis, uint8_t *data, size_t size);

CLASS_DECLARE(file_device)
    CLASS_EXTERND(device);
    char *current_file;
DECLARE_END(file_device);
CONSTRUCT_METHOD(file_ctor, file_device);
void file_set_path(file_device *pthis, const char *path);

#endif
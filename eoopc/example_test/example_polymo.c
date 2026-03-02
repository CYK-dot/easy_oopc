/**
 * @file example_polymo.c
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
#include <stdio.h>
#include "example_polymo.h"

void device_write(device *pthis, const uint8_t *data, size_t size)
{
    VMETHOD_CALL(pthis, v_write, data, size);
}

void device_read(device *pthis, uint8_t *data, size_t size)
{
    VMETHOD_CALL(pthis, v_read, data, size);
}

int file_write(device *pthis, const uint8_t *data, size_t size)
{
    file_device *pthis_lower = THIS_CHILD(pthis, device, file_device);

    FILE *fp = fopen(pthis_lower->current_file, "ab");
    if (!fp) return -1;
    size_t written = fwrite(data, 1, size, fp);
    fclose(fp);
    return (written == size) ? (int)size : -1;
}

int file_read(device *pthis, uint8_t *data, size_t size)
{
    file_device *pthis_lower = THIS_CHILD(pthis, device, file_device);

    FILE *fp = fopen(pthis_lower->current_file, "rb");
    if (!fp) return -1;
    size_t read = fread(data, 1, size, fp);
    fclose(fp);
    return (int)read;
}

void file_set_path(file_device *pthis, const char *path)
{
    pthis->current_file = (char *)path;
}

CONSTRUCT_METHOD(file_ctor, file_device)
{
    device *pthis_super = THIS_PARENT(pthis, device);
    VMETHOD_SET(pthis_super, v_write, file_write);
    VMETHOD_SET(pthis_super, v_read, file_read);
}
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
#include "example.h"

/* comm_port ------------------------------------------------------------------------*/
CONSTRUCT_METHOD(comm_port_ctor, comm_port, const char *default_name)
{
    pthis->PUBLIC_MEMBER_REF(name) = default_name;
}

void comm_port_set_name(comm_port *pthis, const char *name)
{
    pthis->PUBLIC_MEMBER_REF(name) = name;
}

/* buffer ---------------------------------------------------------------------------*/
CONSTRUCT_METHOD(buffer_ctor, buffer, uint8_t *buf, size_t capacity)
{
    if (pthis->PRIVATE_MEMBER_REF(buf) != NULL) {
        return;
    }
    pthis->PRIVATE_MEMBER_REF(buf) = buf;
    pthis->PRIVATE_MEMBER_REF(index) = 0;
    pthis->PRIVATE_MEMBER_REF(buf_size) = capacity;
}

size_t buffer_send(buffer *pthis, const uint8_t *data, size_t data_size)
{

}

size_t buffer_recv(buffer *pthis, uint8_t *data, size_t data_size)
{

}

/* msg_port -------------------------------------------------------------------------*/
CONSTRUCT_METHOD(msg_port_ctor, msg_port, const char *default_name)
{
    CONSTRUCT_BRINGUP(pthis, comm_port, comm_port_ctor, "/msg0/invalid");
    CONSTRUCT(&(pthis->PRIVATE_MEMBER_REF(rx_buf)), buffer_ctor, pthis->PRIVATE_MEMBER_REF(tx_buf), 200);
}

DESTRUCT_METHOD(msg_port_dtor, msg_port)
{

}

size_t msg_port_send(comm_port *pthis, const void *data, size_t data_size)
{

}

size_t msg_port_recv(comm_port *pthis, void *data, size_t data_size)
{

}
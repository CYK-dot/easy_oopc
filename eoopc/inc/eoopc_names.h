/**
 * @file eoopc_namespace.h
 * @brief eoopc使用的符号名称。仅eoopc内部使用，不建议外部使用。
 * @version 0.1
 * @date 2026-03-08
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
#ifndef EOOPC_NAMESPACE_H__
#define EOOPC_NAMESPACE_H__

#define NAME_PARENT_REFER(parent_class_name) \
    _parent_##parent_class_name

#define NAME_VTBL_REFER \
    _vtbl

#define NAME_VMETHOD_PUB(method_name) \
    _vmtdpub_##method_name

#define NAME_VMETHOD_PVT(method_name) \
    _vmtdpvt_##method_name

#endif
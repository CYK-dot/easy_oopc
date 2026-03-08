/**
 * @file eoopc_type.h
 * @brief eoopc使用到的类型别名
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
#ifndef EOOPC_TYPE_H__
#define EOOPC_TYPE_H__
/**
 * @addtogroup EOOPC-API
 * @{
 * @addtogroup 变量类型
 * @{
 */

/**
 * @brief 结构体类的类型
 * @tparam class_name 类名称
 * @note 用法：struct TYPE_RAW_CLASS_STRUCT(class_name) my_object;
 */
#define TYPE_RAW_CLASS_STRUCT(class_name) \
    _class_##class_name

/**
 * @brief 虚表类型
 * @tparam class_name 属于哪个类的虚表
 */
#define TYPE_VTABLE(class_name) \
    _vtbl_##class_name


/** 
 * @}
 * @}
 */
#endif
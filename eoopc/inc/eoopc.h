/**
 * @file eoopc.h
 * @brief EOOPC编程框架宏
 * @version 0.1
 * @date 2026-02-28
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
#ifndef EOOPC_H__
#define EOOPC_H__

/** ---------------------------------------------------------------
 * @addtogroup 封装相关的宏
 * @{
 ** --------------------------------------------------------------*/

/**
 * @brief 类成员声明开始
 * @tparam class_name 类名称，可作为对象的变量类型
 */
#define CLASS_DECLARE_START(class_name) \
    typedef struct tag_eoopc_class_##class_name {

/**
 * @brief 类成员声明结束
 * @tparam class_name 类名称，可作为对象的变量类型
 */
#define CLASS_DECLARE_END(class_name) \
    } class_name;

/**
 * @brief 声明一个私有成员
 * @tparam member_type 成员的变量类型
 * @tparam member_name 成员的名称
 * 
 * @note 声明时，必须放在类成员声明的开始和结束之间
 */
#define PRIVATE_MEMBER(member_type, member_name) \
    member_type _oopc_private_##member_name

/**
 * @brief 声明一个公开成员
 * @tparam member_type 成员的变量类型
 * @tparam member_name 成员的名称
 * 
 * @note 必须放在类成员声明的开始和结束之间
 */
#define PUBLIC_MEMBER(member_type, member_name) \
    member_type member_name

/**
 * @brief 获取对象私有成员的引用
 * @tparam member_name 私有成员名称
 * 
 * @note 使用方式: object->PRIVATE_MEMBER_REF(xxx)
 */
#define PRIVATE_MEMBER_REF(member_name) \
    _oopc_private_##member_name

/**
 * @brief 获取对象公开成员的引用
 * @tparam member_name 私有成员名称
 * 
 * @note 使用方式: object->PRIVATE_MEMBER_REF(xxx)
 * @note 当然，公开成员可以通过.和->运算符直接访问到，不一定需要使用此宏
 */
#define PUBLIC_MEMBER_REF(member_name) \
    member_name

/**
 * @brief 声明类的方法开始
 * @tparam class_name 类名称，可作为对象的变量类型
 */
#define PUBLIC_METHOD_DECLARE_START(class_name)

/**
 * @brief 声明类的方法结束
 * @tparam class_name 类名称，可作为对象的变量类型
 */
#define PUBLIC_METHOD_DECLARE_END(class_name)
/** @} */

/** ---------------------------------------------------------------
 * @addtogroup 继承
 * @{
 ** --------------------------------------------------------------*/

/**
 * @brief 声明此类继承自哪一个类
 * @tparam class_name 父类名称
 * 
 * @note 必须放在类成员声明的开始和结束之间
 */
#define CLASS_EXTERND(father_class_name) \
    father_class_name eoopc_inherit_##father_class_name

/**
 * @brief 将某个对象指针，转变为父类的对象指针
 * @tparam obj_this 需要被转换的对象指针
 * @tparam father_class_name 父类名称
 */
#define THIS_PARENT(obj_this, father_class_name) \
    (&((obj_this)->eoopc_inherit_##father_class_name))

/**
 * @brief 将某个对象指针，转变为父类的父类的对象指针
 * @tparam obj_this 需要被转换的对象指针
 * @tparam father_class_name 父类名称
 * @tparam gfather_class_name 父类的父类名称
 */
#define THIS_GRAND_PARENT(obj_this, father_class_name, gfather_class_name) \
    (&(((obj_this)->eoopc_inherit_##father_class_name).eoopc_inherit_##gfather_class_name))
/** @} */

/** ---------------------------------------------------------------
 * @addtogroup 多态
 * @{
 ** --------------------------------------------------------------*/

/**
 * @brief 声明类中的一个虚函数
 * @tparam ret_type 虚函数的返回值类型
 * @tparam method_name 虚函数的名称
 * @tparam class_name 虚函数所在类的名称
 * @tparam ... 虚函数形参
 * 
 * @note 必须放在类成员声明的开始和结束之间
 */
#define VMETHOD(ret_type, method_name, class_name, ...) \
    ret_type (*##method_name)(class_name, __VA_ARGS__)

/**
 * @brief 设置对象的虚函数指向
 * @tparam method_name 虚函数名称
 * @tparam method_implement 指向哪一个实现
 * 
 * @note 使用方式为 object->VMETHOD_SET(xxx, xxx);
 */
#define VMETHOD_SET(method_name, method_implement) \
    method_name = (method_implement)

/**
 * @brief 调用对象的虚函数
 * @tparam method_name 虚函数名称
 * 
 * @note 使用方式为 object->VMETHOD_SET(xxx, xxx);
 */
#define VMETHOD_CALL(method_name) \
    method_name
/** @} */

#endif
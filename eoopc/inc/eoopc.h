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
 * 
 */
#ifndef EOOPC_H__
#define EOOPC_H__
#include "eoopc_types.h"
#include "eoopc_names.h"
#include "eoopc_util.h"

/**
 * @addtogroup EOOPC-API
 * @{
 * @details
 * EOOPC的目标是，提供C兼容的面向对象框架，让项目中各个子模块具有一致的插口和接口。提高可移植性和可扩展性。
 * # 一、第一性原则
 * C并不原生支持面向对象，各种面向对象的写法都会不可避免地降低可读性、可调式性。
 * 
 * 理论上，并没有不得不面向对象的场景，任何范式都可以解决所有问题，区别在于复杂度与开发效率。
 * 
 * 若使用不当，面向对象照样会造成负担。
 * 下面逐个讲解面向对象适合的场景
 * 
 * ## 1. 需要降低认知负担时
 * 一个抽象良好的工程，哪怕其复杂程度很高，也能快速上手；一个抽象不佳的工程，哪怕功能不复杂，也是难以阅读和维护的。
 * 
 * 根据工程经验，一个做到“高内聚、低耦合”的工程，往往是抽象良好的，能有效降低认知负担。
 * 
 * 而面向对象提供了一种选择，让开发者在短时间内构思出一个还行的抽象，可以类比成PID在控制方式的地位。
 * 
 * 它就一套预制构件，让开发者能在短时间内搭出一个结构清晰的架子，而不是从零开始规划每个函数的关系。
 * 
 * 可以把它想象成乐高积木——不决定最终搭什么，但提供了标准化的连接方式，让组合变得容易。
 * 
 * ## 2. 需要复用代码且变化方向明确时
 * 过程式编程通常通过函数库来复用，但函数库的复用粒度较粗，而且如果两个模块需要共享一些数据和行为，往往要借助全局变量或复杂的参数传递。
 * 
 * 而面向对象提供了两种更精细的复用方式：
 * - 继承复用：子类可以直接复用父类的代码，只需关注自己独特的部分。
 * - 组合复用：一个类包含另一个类的对象，通过委托来复用功能（“has-a”关系）。
 * 
 * 例如，要实现多个通信协议（TCP、UDP、蓝牙），它们都有“打开连接”、“发送数据”、“关闭连接”等操作，但具体实现不同。
 * 
 * 面向对象的做法是定义一个抽象接口（或虚函数表），然后让每个协议去实现它。
 * 
 * 上层代码只需要针对接口编程，新增一个协议时完全不影响现有代码——这就是著名的开闭原则。
 */

/**
 * @addtogroup 类的声明
 * @{
 * @details 
 * EOOP基于C宏实现，而不基于脚本生成代码。好处是EOOPC易于集成，缺点是写出来的代码，与主流面向对象语言存在差异，需要文档注解。
 * 
 * 下面展示了两份代码，一份是C++原生的面向对象声明，一份是EOOPC在C语言下的声明
 * @code
 * // shape.hpp
 * class shape {
 * public:
 *      shape(const char *name);
 *      virtual float get_length();
 * private:
 *      char *name;
 * };
 * @endcode
 * @code
 * // shape.h
 * CLASS_DECLARE(shape);
 *      VTABLE_DECLARE(
 *          shape,
 *          float VMETHOD_PUB(get_length) (shape *pthis);
 *      );
 *      OBJECT_DECLARE(
 *          shape,
 *          char *MEMBER_PVT(name);
 *      );
 *      void METHOD_CTOR(shape) (shape *pthis, const char *name);
 * END_CLASS(shape);
 * @endcode
 * 
 * @note 从上面的例子可以看到，主流面向对象语言中，总是先声明作用域，再指定要素。
 * @note 由于C编译器无法自动解析类结构，因此EOOPC采用的声明策略更偏实现：总是先声明要素，再在要素中指定作用域。
 * 
 * EOOPC的类包含3个要素：静态方法、虚方法、对象结构。下面描述这三个部分扮演的功能。
 * 
 * ### 1. 静态方法
 * 静态方法，即直接隶属于类的方法。因为其实现不会随对象变化而变化，也不会在对象运行时发生变更，因此称为静态。
 * 
 * @note 从静态一直到动态，方法可以分为3挡。
 * @note 1. 静态方法。静态方法与类绑定，不会发生变更。
 * @note 2. 虚方法。虚方法与对象绑定，在对象创建之初确定，之后便不再变更。
 * @note 3. 动态方法。动态方法不做任何绑定，一般采用函数指针实现，想执行什么就指到那。
 * 
 * EOOPC静态方法采用了命名空间的思想。由宏拼接命名空间，得到最终用于编译的符号。详见 @ref 为类声明静态方法
 * 
 * 比如下面这个函数名称为get_length，命名空间为shape，其符号通过VMETHOD_PUB构造。
 * @code
 * float VMETHOD_PUB(shape, get_length) (shape *pthis) {
 *      return 0;
 * }
 * @endcode
 * 
 * @note 要注意，EOOPC不支持真正意义上的成员方法，而是以静态方法作为替代。
 * @note 因为C语言并不支持在结构体中声明函数，也不支持自动传递this指针。
 * @note 若硬要将方法放入成员列表中，就不得不引入函数指针。这不仅带来了额外的开销，也会给人造成误解，以为成员方法可以在运行时变更。
 * 
 * ### 2. 虚方法
 * 虚方法，即与对象绑定的方法，下面举一个例子。
 * @note vehicle类有set_speed方法，car类继承自vehicle类。现在有一个car对象，其指针为 car *white_bmw。
 * @note 限制，将white_bmw对象指针的类型转为vehicle*，然后调用set_speed方法：
 * @note - 如果set_speed是实方法，那么指针转换后，将会调用vehicle类的set_speed方法
 * @note - 如果set_speed是虚方法，那么指针转换后，仍然会调用car类的set_speed方法
 * 
 * 在EOOPC中，虚方法采用虚函数表的方式实现，需要先声明虚函数表，然后将其加入到对象成员中。 详见 @ref 为类声明虚方法
 * 
 * ### 3. 对象结构
 * 对象结构，指的是声明对象中包含哪些要素。在EOOPC概念下，对象可以具备下面这三种要素。声明方式详见 @ref 为类声明对象结构
 * 
 * 1. 成员。包括公开成员、静态成员。
 * 2. 通过继承得到的父类结构。允许多继承。
 * 3. 虚函数表。一个对象只能持有一份虚函数表。
 */

/** --------------------------------------------------------------------------------
 * @addtogroup 类声明的开始与结束
 * @{
 */

/**
 * @brief 类声明的开始
 * @tparam class_name 类的名称
 */
#define CLASS_DECLARE(class_name) \
    typedef struct TYPE_RAW_CLASS_STRUCT(class_name) class_name;

/**
 * @brief 类声明的结束
 * @tparam class_name 类的名称
 */
#define END_CLASS(class_name)
/** @} */

/** --------------------------------------------------------------------------------
 * @addtogroup 为类声明静态方法
 * @{
 * @details
 * 静态方法可继续细分为4类，声明格式均为METHOD_xxx
 * 1. 公开方法：任何外部类都可以访问该方法。
 * 2. 私有方法：方法仅类内部可见。
 * 3. 构造方法：用于创建对象。
 * 4. 析构方法：用于销毁对象。
 * 
 * 下面展示了一个例子，fmath为一个纯方法类。
 * @code
 * CLASS_DECLARE(fmath);
 *      float METHOD_PUB(fmath, plus_add)(fmath *context, float num1, float num2, float num3);
 *      float METHOD_PUB(fmath, sqrt)(fmath *context, float num);
 * 
 *      float METHOD_CTOR(fmath)(fmath *pthis, uint8_t *buf, size_t buf_size);
 *      float METHOD_CTOR_ALTER(fmath, without_buf)(fmath *pthis);
 *      float METHOD_DTOR(fmath)(void);
 * END_CLASS(fmath);
 * @endcode
 * 
 * @note
 * 不过要注意的是，C语言并不支持真正的访问控制，也不支持构造/析构函数自动调用。因此：
 * 1. 公开与私有的可见性是文档性质的，需要程序员主动遵守。
 * 2. 构造与析构函数同样是文档性质的，需要程序员自行调用构造/析构函数，维护对象的声明周期。
 */

/**
 * @brief 一个符号，代表静态公开方法
 * @tparam class_name 类名称，被用于构造命名空间前缀
 * @tparam method_name 方法名称
 * 
 * @note 静态方法直接隶属于类。应包含在 @ref CLASS_DECLARE 和 @ref END_CLASS 之间
 */
#define METHOD_PUB(class_name, method_name) \
    _mtdpub_class_name##_##method_name

/**
 * @brief 一个符号，代表静态私有方法
 * @tparam class_name 类名称，被用于构造命名空间前缀
 * @tparam method_name 方法名称
 * 
 * @note 静态方法直接隶属于类。应包含在 @ref CLASS_DECLARE 和 @ref END_CLASS 之间
 */
#define METHOD_PVT(class_name, method_name) \
    _mtdpvt_class_name##_##method_name

/**
 * @brief 一个符号，代表默认构造函数
 * @tparam class_name 类名称，被用于构造命名空间前缀
 * 
 * @note 静态方法直接隶属于类。应包含在 @ref CLASS_DECLARE 和 @ref END_CLASS 之间
 */
#define METHOD_CTOR(class_name) \
    _ctor_##class_name

/**
 * @brief 一个符号，代表可选的构造函数
 * @tparam class_name 类名称，被用于构造命名空间前缀
 * @tparam ctor_name 构造函数名称
 * 
 * @note 静态方法直接隶属于类。应包含在 @ref CLASS_DECLARE 和 @ref END_CLASS 之间
 */
#define METHOD_CTOR_ALTER(class_name, ctor_name) \
    _ctor_##ctor_name##_of_##class_name

/**
 * @brief 一个符号，代表默认析构函数
 * @tparam class_name 类名称，被用于构造命名空间前缀
 * 
 * @note 静态方法直接隶属于类。应包含在 @ref CLASS_DECLARE 和 @ref END_CLASS 之间
 */
#define METHOD_DTOR(class_name) \
    _dtor_##class_name

/**
 * @brief 一个符号，代表可选的析构函数
 * @tparam class_name 类名称，被用于构造命名空间前缀
 * @tparam dtor_name 析构函数名称
 * 
 * @note 静态方法直接隶属于类。应包含在 @ref CLASS_DECLARE 和 @ref END_CLASS 之间
 */
#define METHOD_DTOR_ALTER(class_name, dtor_name) \
    _dtor_##dtor_name##_of_##class_name
/** @} */

/** --------------------------------------------------------------------------------
 * @addtogroup 为类声明虚方法
 * @{
 * @details
 * 下面的声明了一个只有虚方法的shape类
 * @code
 * CLASS_DECLARE(shape);
 *      VTABLE_DECLARE(
 *          shape,
 *          float VMETHOD_PUB(get_area) (shape *pthis);
 *          bool VMETHOD_PVT(set_color) (shape *pthis, uint8_t color);
 *      );
 *      OBJECT_DECLARE(
 *          shape,
 *          HAVE_VTABLE(shape);
 *      );
 * END_CLASS(shape);
 * @endcode
 */

/**
 * @brief 声明虚函数表，用于容纳该类中所有的虚方法
 * @tparam class_name 类名称，被用于构造命名空间前缀
 * @tparam method_name 方法名称
 * 
 * @note 虚函数表隶属于类，应包含在 @ref CLASS_DECLARE 和 @ref END_CLASS 之间。
 * @note 声明虚函数表后，还需要在 @ref OBJECT_DECLARE 中使用 @ref HAVE_VTABLE ，使其生效
 */
#define VTABLE_DECLARE(class_name, ...)  \
    typedef struct _vtbl_##class_name {  \
        __VA_ARGS__                      \
    } TYPE_VTABLE(class_name);

/**
 * @brief 一个符号，表示虚公开方法
 * @tparam class_name 类名称，被用于构造命名空间前缀
 * @tparam method_name 方法名称
 * 
 * @note 虚方法均应包含在 @ref VTABLE_DECLARE 中
 */
#define VMETHOD_PUB(method_name) \
    (*NAME_VMETHOD_PUB(method_name))

/**
 * @brief 一个符号，表示虚私有方法
 * @tparam class_name 类名称，被用于构造命名空间前缀
 * @tparam method_name 方法名称
 * 
 * @note 虚方法均应包含在 @ref VTABLE_DECLARE 中
 */
#define VMETHOD_PVT(method_name) \
    (*NAME_VMETHOD_PVT(method_name))
/** @} */

/** --------------------------------------------------------------------------------
 * @addtogroup 为类声明对象结构
 * @{
 * @details
 * 下面展示了一个rectangle类，他继承自shape类。
 * @code
 * CLASS_DECLARE(rectangle);
 *      OBJECT_DECLARE(
 *          rectangle,
 *          HAVE_PARENT(shape);
 *          float MEMBER_PVT(length);
 *          float MEMBER_PVT(width);
 *      );
 *      void METHOD_CTOR(rectangle) (rectangle *pthis, float len, float wid);
 * END_CLASS(rectangle);
 * @endcode
 */

/**
 * @brief 声明对象的结构
 * @tparam class_name 类的名称
 * @tparam ... 成员列表，以;分割
 * 
 * @note 应包含在 @ref CLASS_DECLARE 和 @ref END_CLASS 之间
 */
#define OBJECT_DECLARE(class_name, ...)        \
    struct TYPE_RAW_CLASS_STRUCT(class_name) { \
        __VA_ARGS__                            \
    };

/**
 * @brief 一个符号，表示公开成员
 * @tparam member_name 成员名称
 * 
 * @note 应在 @ref OBJECT_DECLARE 中调用，且可以出现多次。
 */
#define MEMBER_PUB(member_name) \
    _mbrpub_##member_name

/**
 * @brief 一个符号，表示私有成员
 * @tparam member_name 成员名称
 * 
 * @note 应在 @ref OBJECT_DECLARE 中调用，且可以出现多次。
 */
#define MEMBER_PVT(member_name) \
    _mbrpvt_##member_name

/**
 * @brief 声明一条继承关系
 * @tparam parent_class_name 父类名称
 * 
 * @note 应在 @ref OBJECT_DECLARE 中调用，且可以出现多次。
 */
#define HAVE_PARENT(parent_class_name) \
    parent_class_name NAME_PARENT_REFER(parent_class_name)

/**
 * @brief 声明对象携带虚函数表
 * @tparam 类名称
 * 
 * @note 应在 @ref OBJECT_DECLARE 中调用，且只能出现一次。
 * @par
 * @note 需要确保虚表声明( @ref VTABLE_DECLARE )早于对象声明( @ref OBJECT_DECLARE )，
 *       否则会出现找不到符号的问题 
 */
#define HAVE_VTABLE(class_name) \
    TYPE_VTABLE(class_name) *NAME_VTBL_REFER;
/** @} */
/** @} */

/** --------------------------------------------------------------------------------
 * @addtogroup 类的实现
 * @{
 */

/** --------------------------------------------------------------------------------
 * @addtogroup 为类实现静态方法
 * @{
 * @details 
 * 静态方法的声明方式为符号声明，因此对符号进行实现即可。
 * 当然，为了提高可读性，可以在METHOD_xxx前面加上IMPL，突出“定义”。
 * @code
 * // u32math.h
 * #include <stdint.h>
 * CLASS_DECLARE(u32math);
 *      uint32_t METHOD_PUB(u32math, plus)(u32math *context, uint32_t num1, uint32_t num2);
 *      uint32_t METHOD_PUB(u32math, minus)(u32math *context, uint32_t num);
 * END_CLASS(u32math);
 * @endcode
 * 
 * @code
 * // u32math.c
 * #include "u32math.h"
 * #include <limits.h>
 * uint32_t METHOD_PUB(u32math, plus)(u32math *context, uint32_t num1, uint32_t num2) { // 允许的写法
 *      if (UINT32_MAX - num1 < num2) return UINT32_MAX;
 *      return num1 + num2;
 * }
 * uint32_t IMPL_METHOD_PUB(u32math, minus)(u32math *context, uint32_t num1, uint32_t num2) { // 推荐的写法
 *      if (num1 < num2) return 0;
 *      return num1 - num2;
 * }
 * @endcode
 */

/**
 * @brief 一个符号，表示公开方法的实现
 */
#define IMPL_METHOD_PUB(class_name, method_name) \
    METHOD_PUB(class_name, method_name)

/**
 * @brief 一个符号，表示私有方法的实现
 */
#define IMPL_METHOD_PVT(class_name, method_name) \
    METHOD_PVT(class_name, method_name)

/**
 * @brief 一个符号，表示构造函数的实现
 */
#define IMPL_METHOD_CTOR(class_name) \
    METHOD_CTOR(class_name)

/**
 * @brief 一个符号，表示析构函数的实现
 */
#define IMPL_METHOD_DTOR(class_name) \
    METHOD_DTOR(class_name)

/**
 * @brief 一个符号，表示可选构造函数的实现
 */
#define IMPL_METHOD_CTOR_ALTER(class_name, ctor_name) \
    METHOD_CTOR_ALTER(class_name, ctor_name)

/**
 * @brief 一个符号，表示可选析构函数的实现
 */
#define IMPL_METHOD_DTOR_ALTER(class_name, dtor_name) \
    METHOD_DTOR_ALTER(class_name, dtor_name)
/** @} */

/** --------------------------------------------------------------------------------
 * @addtogroup 为类实现虚方法
 * @{
 * @details
 * 虚方法的实现分为3步：
 * 1. 实现虚方法
 * 2. 定义虚表变量，填入虚方法的实现
 * 3. 在对象构造函数中，设置虚表变量
 * 
 * 下面展示了一个例子，继承自 @ref 为类声明虚方法 中的例子
 * @code
 * // circle.h
 * #include "shape.h"
 * CLASS_DECLARE(circle);
 *      OBJECT_DECLARE(
 *          circle,
 *          HAVE_PARENT(shape);
 *          float MEMBER_PVT(radius);
 *      );
 *      void METHOD_CTOR(circle) (circle *pthis, float rad);
 * END_CLASS(circle);
 * @endcode
 * 
 * @code
 * // circle.c
 * #include "eoopc.h"
 * #include "circle.h"
 * #define PI_CONST 3.1415926f
 * 
 * // 为了覆盖父类虚函数get_area，形参需要保持一致。因此是shape*而非circle*
 * static float IMPL_VMETHOD_PUB(circle, overrided_get_area) (shape *pthis_base) {
 *      // 将形参中的父类指针转为子类指针，用于访问circle类的成员
 *      circle *pthis = THIS_CHILD(pthis_base, shape, circle);
 *      float rad = pthis->MEMBER_PUB(raduis);
 *      return PI_CONST * rad * rad;
 * }
 * 
 * static TYPE_VTABLE(shape) IMPL_VTABLE(circle, overrided_vtbl) = {
 *      CTOR_VMETHOD_PUB(get_area, circle, overrided_get_area), // 把虚表中的get_area 覆盖为 circle类的overrided_get_area方法
 * };
 * 
 * void IMPL_METHOD_CTOR(circle) (circle *pthis, float rad) {
 *      shape *this_base = THIS_PARENT(pthis, shape);
 *      CTOR_VTABLE(this_base, circle, overrided_vtbl); // shape类的虚表 覆盖为 circle类的overrided_vtbl表
 * }
 * @endcode
 */

/**
 * @brief 一个符号，表示虚公开方法的实现
 * @tparam override_class_name 虚表由哪个类覆写
 * @tparam method_name 覆盖虚方法的 方法的名称
 */
#define IMPL_VMETHOD_PUB(override_class_name, method_name) \
    _impl_##override_class_name##_vmtdpub_##method_name

/**
 * @brief 一个符号，表示虚私有方法的实现
 * @tparam override_class_name 虚表由哪个类覆写
 * @tparam method_name 覆盖虚方法的 方法的名称
 */
#define IMPL_VMETHOD_PVT(override_class_name, method_name) \
    _impl_##override_class_name##_vmtdpvt_##method_name

/**
 * @brief 一个符号，表示虚表的实现
 * @tparam override_class_name 虚表由哪个类覆写
 * @tparam vtable_name 覆盖虚表的 表名称
 */
#define IMPL_VTABLE(override_class_name, vtable_name) \
    g_vtbl_##override_class_name##_##vtable_name

/**
 * @brief 在虚表实现中，指定公开虚方法的指向
 * @tparam vmethod_name 需要被覆盖的虚方法名称
 * @tparam override_class_name 虚表由哪个类覆写
 * @tparam method_name 覆盖虚方法的 方法的名称
 */
#define CTOR_VMETHOD_PUB(vmethod_name, override_class_name, method_name) \
    .NAME_VMETHOD_PUB(vmethod_name) =  IMPL_VMETHOD_PUB(override_class_name, method_name)

/**
 * @brief 在虚表实现中，指定私有虚方法的指向
 * @tparam override_class_name 虚表由哪个类覆写
 * @tparam method_name 被用于覆写的方法名称
 */
#define CTOR_VMETHOD_PVT(vmethod_name, override_class_name, method_name) \
    .NAME_VMETHOD_PVT(vmethod_name) =  IMPL_VMETHOD_PVT(override_class_name, method_name)

/**
 * @brief 在构造函数实现中，指定对象的虚函数表
 * @tparam override_class_name 虚表由哪个类覆写
 * @tparam vtable_name 覆盖虚表的 表名称
 */
#define CTOR_VTABLE(object_this, override_class_name, vtable_name) \
    (object_this)->NAME_VTBL_REFER = &(IMPL_VTABLE(override_class_name, vtable_name))
/** @} */
/** @} */

/** --------------------------------------------------------------------------------
 * @addtogroup 对象的访问
 * @{
 */

/** --------------------------------------------------------------------------------
 * @addtogroup 对象指针的类型转换
 * @{
 * @details
 * EOOPC不支持对继承成员平铺展开。子类如果想要访问父类成员，可通过向上转型，获取父类指针的方式访问。
 */

/**
 * @brief 向上转型，获取对象指针的父类指针
 * @tparam object_this 需要被操作的对象
 * @tparam parent_class_name 该对象的父类名称
 */
#define THIS_PARENT(object_this, parent_class_name) \
    (&((object_this)->NAME_PARENT_REFER(parent_class_name)))

/**
 * @brief 向下转型，获取对象指针的子类指针
 * @tparam object_this 需要被操作的对象
 * @tparam parent_class_name 需要被转换成哪种子类指针
 * @note 一般用于虚函数编写
 * @warning EOOPC无法检查转换能否成立，请自行确保obj_this存在该子类，否则会造成未定义行为！
 */
#define THIS_CHILD(obj_this, this_class_name, child_class_name) \
    (child_class_name *)((uint8_t *)obj_this - EOOPC_OFFSETOF(child_class_name, NAME_PARENT_REFER(this_class_name)))
/** @} */


/** --------------------------------------------------------------------------------
 * @addtogroup 访问对象的成员
 * @{
 * @details
 * EOOPC不支持对继承成员平铺展开。子类如果想要访问父类成员，可通过向上转型，获取父类指针的方式访问。
 * 同理，父类指针无法访问子类成员，需要向下转型。一般用于虚函数中。
 * 由于EOOPC支持多继承，因此不应通过C语言强制类型转换的方式实现向上向下转型，而是使用eoopc提供的转型宏，参见 @ref 对象指针的类型转换
 */

/**
 * @brief 获取公开成员的引用
 * @tparam object_this 对象指针
 * @tparam member_name 成员的名称
 */
#define THIS_MEMBER_PUB(object_this, member_name) \
    ((object_this)->MEMBER_PUB(member_name))

/**
 * @brief 获取私有成员的引用
 * @tparam object_this 对象指针
 * @tparam member_name 成员的名称
 */
#define THIS_MEMBER_PVT(object_this, member_name) \
    ((object_this)->MEMBER_PUB(member_name))
/** @} */

/** --------------------------------------------------------------------------------
 * @addtogroup 调用类的静态方法
 * @{
 */

/**
 * @brief 一个符号，表示公开方法调用
 */
#define CALL_METHOD_PUB(class_name, method_name) \
    METHOD_PUB(class_name, method_name)

/**
 * @brief 一个符号，表示私有方法调用
 */
#define CALL_METHOD_PVT(class_name, method_name) \
    METHOD_PVT(class_name, method_name)

/**
 * @brief 一个符号，表示构造函数调用
 */
#define CALL_METHOD_CTOR(class_name) \
    METHOD_CTOR(class_name)

/**
 * @brief 一个符号，表示析构函数调用
 */
#define CALL_METHOD_DTOR(class_name) \
    METHOD_DTOR(class_name)

/**
 * @brief 一个符号，表示可选构造函数调用
 */
#define CALL_METHOD_CTOR_ALTER(class_name, ctor_name) \
    METHOD_CTOR_ALTER(class_name, ctor_name)

/**
 * @brief 一个符号，表示可选析构函数调用
 */
#define CALL_METHOD_DTOR_ALTER(class_name, dtor_name) \
    METHOD_DTOR_ALTER(class_name, dtor_name)

/** @} */

/** --------------------------------------------------------------------------------
 * @addtogroup 访问对象的虚方法
 * @{
 * @details
 * EOOPC不支持对继承成员平铺展开。子类如果想要访问父类成员，可通过向上转型，获取父类指针的方式访问。参见 @ref 对象指针的类型转换
 */

/**
 * @brief 一个符号，表示公开虚函数调用
 * 
 */
#define CALL_VMETHOD_PUB(obj_this, vmethod_name) \
    (((obj_this)->NAME_VTBL_REFER)->NAME_VMETHOD_PUB(vmethod_name))

/**
 * @brief 一个符号，表示私有虚函数调用
 * 
 */
#define CALL_VMETHOD_PVT(obj_this, vmethod_name) \
    (((obj_this)->NAME_VTBL_REFER)->NAME_VMETHOD_PVT(vmethod_name))
/** @} */
/** @} */
/** @} */
#endif
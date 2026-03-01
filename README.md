# 一、组件介绍
一个轻量化的面向对象编程框架，在不支持C/C++混合编程的环境下，提供基础的面向对象抽象能力。

优势：
- 纯宏头文件设计，无函数调用带来的栈开销。
- 相比于通过void*继承，eoopc的继承是类型安全的。
- 仅虚函数采用函数指针实现，程序调用流直观。

## 1.1 功能描述
1. 封装
   - 支持类声明
   - 支持public/private两种访问权限
   - 支持构造函数/析构函数，并允许手动指定父类构造顺序
2. 继承
   - 支持多继承
   - 子类可覆盖父类方法
3. 多态
   - 通过指定继承路径，可将对象指针类型转变为父类
   - 支持虚函数，以实现运行时多态

# 二、使用方式

## 2.1. 封装
在 CLASS_DECLARE_START 和 CLASS_DECLARE_END 之间，声明成员。
```c
CLASS_DECLARE_START(example_class)
    int example_member;
CLASS_DECLARE_END(example_class)
```

成员函数由用户自行声明和定义，不应放入 CLASS_DECLARE_START 和 CLASS_DECLARE_END之间。

成员函数通常的声明方式是，把对象指针放在第一个形参。
```c
int example_method(example_class *class);
```

私有成员通过PRIVATE_MEMBER宏声明和获取。
```c
CLASS_DECLARE_START(example_class)
    int example_member;
    int PRIVATE_MEMBER(example_private_member);
CLASS_DECLARE_END(example_class)

int example_method(example_class *object)
{
    object->PRIVATE_MEMBER(example_private_member) = 10;
    return 0;
}
```

不加任何声明，默认为公开成员。当然，也可以使用 PUBLIC_MEMBER宏显式声明，并通过OBJECT_PUBLIC_MEMBER显式获取。
```c
CLASS_DECLARE_START(example_class)
    int PUBLIC_MEMBER(example_member);
    int PRIVATE_MEMBER(example_private_member);
CLASS_DECLARE_END(example_class)

int example_method(example_class *object)
{
    object->PRIVATE_MEMBER(example_private_member) = 10;
    object->PUBLIC_MEMBER(example_member) = 10;
    return 0;
}
```

---
## 2.2. 继承
在 CLASS_DECLARE_START 和 CLASS_DECLARE_END 之间，通过CLASS_EXTENDS宏声明继承关系。
```c
CLASS_DECLARE_START(example_class)
    int example_member;
CLASS_DECLARE_END(example_class)

CLASS_DECLARE_START(example_child_class)
    CLASS_EXTENDS(example_class);
    int example_member2;
CLASS_DECLARE_END(example_child_class)
```

宏机制无法实现真正的继承。eoopc的继承是通过组合来实现的。

若需要访问父类的成员，需要使用 THIS_PARENT 和 THIS_GRAND_PARENT，显式指定继承路径。

两个宏可嵌套使用，或自行继续定义新宏，以规避编译器的宏展开次数限制。
```c
int print_member(example_child_class *obj)
{
    printf("%d", THIS_PARENT(obj, example_class)->example_member);
}
```

---
## 2.3. 多态
eoopc当前仅支持运行时多态。可在类中用VMETHOD声明多态函数。
```c
CLASS_DECLARE_START(example_poly)
    /* inherit */
    CLASS_EXTENDS(example_class);
    /* members */
    int example_member;
    int PRIVATE(example_private_member);
    /* virtual methods */
    VMETHOD(void, vmethod1, example_poly, int, int); /**< void vmethod1(example_poly *, float, float) */
CLASS_DECLARE_END(example_poly)
/* methods */
void example_method1(example_poly *obj);
```

eoopc多态的机制是函数指针。在对象创建时，可使用OBJECT_VMETHOD_SET，改变多态指向。
```c
void eample_member_add(example_poly *obj, int num1, int num2)
{
    obj->PRIVATE_MEMBER(example_private_member) = num1 + num2;
}
void eample_member_minus(example_poly *obj, int num1, int num2)
{
    obj->PRIVATE_MEMBER(example_private_member) = num1 - num2;
}

void example_poly_object_construct(example_poly *obj, bool isAdd)
{
    if (isAdd) {
        obj->VMETHOD_SET(example_poly) = eample_member_add;
    }
    obj->VMETHOD_SET(example_poly) = eample_member_minus;
}
```

# 三、附录：什么时候需要面向对象
**面向对象是一种抽象思维工具，旨在将复杂的抽象问题化整为零，简化认知，用概念去思考，而不是陷入细节。**

为了理解上面这句话，首先需要理解什么是抽象，为什么需要。

简单来说，抽象的目的是**提炼共性，为实体之间的交互提供标准基座**，标准是求同存异。
举一个现实中的例子：小明对小张说，“开一下灯”。
> "求同"是提炼共性，"存异"是保留差异。两者缺一不可。
> 
> "求同"：找出不同对象之间的共同点，形成抽象概念（如"灯"的"开"操作）。
> 
> "存异"：在共性基础上，允许不同对象实现各自特有的行为（如"电灯"和"LED灯"的"开"操作细节不同）。
> 
> 小明不需要知道灯的类型（电灯、LED灯）、内部结构（电路、开关）。只需关注“开灯”这个共性操作——所有灯都能被“开”这个动作触发。
> 
> 换言之，抽象将“开灯”从具体实现中剥离，形成一个通用概念。
> 
> 小明只需记住“开灯”这个概念，无需学习每种灯的差异；小张也只需实现“开灯”逻辑，无需预判小明的所有需求。
> 
> 这正是抽象的核心价值：**解耦细节，聚焦协作。"求同"让系统能统一处理多种对象，"存异"让系统能适配每种对象的独特性。**

ST主推的HAL/LL体系同样是一种抽象。它将外设操作中相同的部分封装到了HAL（求同）、差异的部分保留在LL（存异）。
> STM32系列有两种UART外设。比如F1/F4等系列携带的老UART，以及G4/H7等系列携带的新UART。
> 
> 新UART具有硬件缓冲区、RXTX交换、自动波特率等功能，功能上不同于老一代。但只要使用了HAL库，都能用HAL_UART_Transmit发送数据。
> 
> 因此，基于HAL的业务代码能快速在不同型号之间移植，仅需对LL部分进行适配。因为他们不依赖于实现细节，而是依赖于抽象。

抽象的方式千千万万，面向对象作为其中的一种，在过去的几十年中被证明了价值，也被直接集成到了语言规范中（例如C++、Python）。

但这并不意味着面向对象就是一种解决一切问题的“银弹抽象”，因为抽象是有成本的。
- 认知成本：需要设计类、继承、接口等结构，初期学习曲线陡峭
- 代码成本：冗余的类定义可能使代码量增加，甚至引入“过度设计”
- 运行成本：虚函数、动态绑定等机制带来的性能开销

> 例如，一个“打印日志”的需求：
> 
> 用函数式：print_log(level, message)，一行代码搞定；
> 
> 用面向对象：需定义Logger类、set_level()方法、log()方法，再实例化对象。
> 
> 若需求简单且固定，后者无异于“用大炮打蚊子”。

我们总说，如无必要，勿增实体。那么，回到章节的核心，什么时候需要面向对象呢？

这需要回到面向对象概念本身（封装、继承、多态），根据需要选取使用。

---
### 1.1. 类(Class)和对象(Object)
类是面向对象编程中的核心概念，它定义了一类对象共有的属性和行为。
- 属性(数据)：描述对象的状态，如颜色、大小、速度
- 行为(方法)：描述对象能做什么，如启动、加速、刹车

对象是根据类创建的具体实例，它拥有类中定义的属性和方法，并具有独立的状态（即属性值）。

换言之，**类是抽象的蓝图，对象是具体的实体。**
> 李华想要造一辆车。
> 
> 在真正造车之前，他会先设计一张图纸——这张图纸描述了车的结构、功能和特性。
> 
> 但图纸本身不是一辆车，它只是一个"模板"。这个"模板"就是**类**。
> 
> 当李华根据这张图纸造出一辆实际的车，这辆具体的车就是**对象**。
>
> 李华的图纸定义了一个抽象的"汽车"概念，但它本身不是一辆车。它只是规定了汽车应该有什么属性（颜色、品牌）和能做什么（启动、加速）

那么问题来了，为什么需要类和对象？

在没有类和对象之前，我们只能用函数和全局变量来处理问题：
> ```c
> char car_color[20] = "红色";
> char car_brand[20] = "丰田";
>
> void start_car() {
>    printf("%s汽车启动了！\n", car_brand);
> }
>
> void accelerate_car(int speed) {
>    printf("%s汽车加速到 %d km/h\n", car_brand, speed);
> }
> ```
> 这种方式的问题显而易见，代码难以复用，而且难以轻松创建多辆汽车。
>
> 类和对象提供了更好的组织方式。汽车类声明了汽车相同的部分（求同），汽车对象容纳汽车个体之间的差异（存异）。

类定义了"是什么"，对象体现了"是什么"。当我们需要处理多个相似但不完全相同的实体时，类和对象就是趁手的工具。

---
### 1.2. 封装Encapsulation
**封装是将对象的状态（数据）和行为（方法）绑定在一起，并对外隐藏内部实现细节，仅通过公开的接口（如公有方法）与外界交互。**

封装的本质，不是“把数据和函数写进一个 class 里”，而是用封装明确访问边界。

在工程语境中，封装解决的是两个问题：
- 状态如何被保护？
- 行为如何被约束？

如果一个模块存在内部状态，且不希望这个状态被“不该修改的模块修改”，就可以考虑采用封装。
> 一个模块分配了动态内存，并将指针暴露给外部：
> ```c
> struct Buffer {
>   char* data;
>   int size;
> };
> ```
> 这使得内存所有权难以追踪，外部可能错误地free这个指针、越界访问，导致程序崩溃或安全漏洞。
简单来说，封装的目的是**强制系统通过合法路径改变或获取状态**。

当然，采用封装还有一个好处：让模块不对外暴露过多细节，保持模块与模块之间干净简洁的依赖关系。
> 假设一个模块使用数组存储学生信息，并直接暴露数组给外部：
> ```c
> // student.h
> extern Student students[100];
> extern int count;
> ```
> 后来需求变化，需要改用链表或动态数组，所有直接使用 students[i] 的外部代码都必须修改，导致维护成本增加。

---
### 1.3. 继承Inheritance
继承是一种机制，允许一个类（子类）基于另一个类（父类）构建，从而自动获得父类的属性和方法。

子类可以扩展或重写父类的行为，实现代码复用和层次化抽象。继承体现了“一般-特殊”的关系，支持软件的可扩展性。
> 继承经常被误解为“代码复用工具”，但从抽象层面看，它的真正作用是表达“is-a”关系，用于构建概念层级。
>
> 比如，上层业务只想收发数据，不希望感知具体的外设。那么，SPI、IIC、UART等，都可以被抽象为“通信设备基类”的继承。
>
> 也即，SPI **is-a** 通信设备、IIC **is-a** 通信设备、UART **is-a**通信设备。

如果系统中存在大量“共性行为 + 少量差异行为”的结构，并且这种结构是稳定的层级关系，那么继承是合理的。

但问题在于：现实工程中，“层级关系”往往不稳定。随着业务变更，抽象逻辑变得复杂和混乱。比如：
> 李华今天认为“传感器”是一个基类，并让所有传感器继承自该基类。
>
> 明天，李华发现有的传感器支持 DMA，有的不支持。于是李华又设计了“支持DMA的传感器”基类，继承自传感器基类。
>
> 后天，李华发现部分传感器还支持低功耗模式。于是又设计了“支持低功耗的传感器”基类，也继承自传感器基类。
>
> 第三天，李华发现了棘手的问题：有的传感器既有DMA，又支持低功耗。两个父类都实现了同一个方法，子类该继承哪一个？
>
> 李华开始反思：继承真的是表达“既有DMA又支持低功耗”的最佳方式吗？
> 
> 这些“能力”更像是可以插拔的特性，而不是“is-a”关系。传感器依然是传感器，它只是“拥有”DMA功能和低功耗功能。
>
> 与其让传感器继承自“支持DMA的传感器”，不如让传感器内部包含一个“DMA控制器”对象，将DMA操作委托给该对象。
>
> 这样，能力可以自由组合，继承树变得扁平，系统也更加灵活。

这也就是业界说的**组合(has-a)优于继承(is-a)**。因为大部分is-a抽象会随着业务变化，成为has-a。那不如从一开始就使用has-a抽象。

那么问题来了，继承有什么存在的必要性吗？
> 继承的问题不在于它本身是坏的，而在于它经常被滥用。我们不能因为锤子会砸到手指就否认锤子的价值。
>
> 当两个类之间确实存在一种本质的、层次化的“是一种”关系时，继承是最自然、最符合人类思维模型的表达方式。
>
> 回到传感器的问题。李华一开始的思路并没有错，低功耗传感器、DMA传感器、低功耗DMA传感器，都是传感器。
>
> 李华碰壁的根本原因，是让传感器基类承担了太多的职责。此时最合适的方式是保留继承关系，但重构基类的实现，变成：
>
> - 传感器          has-a 初始化/去初始化接口
> - DMA传感器       is-a  传感器
> - DMA传感器       has-a DMA读写控制接口
> - 低功耗传感器    is-a  传感器
> - 低功耗传感器    has-a 低功耗控制接口
> - 低功耗DMA传感器 is-a  DMA传感器
> - 低功耗DMA传感器 is-a  低功耗传感器

---
### 1.4. 多态Polymorphism
多态的字面意思是“多种形态”，在面向对象中，它指的是同一操作作用于不同对象上时，可以产生不同的解释和执行结果。

封装隔离了变化，继承定义了类型间的血缘。多态则是让抽象真正“活起来”的关键。
> 想象一个雨天的场景：小明对不同的人说“带伞”。
> 
> 对小张说：“带伞”，小张（带伞者）会从包里拿出伞；
> 
> 对小李说：“带伞”，小李（雨衣爱好者）会拉上雨衣拉链；
> 
> 对小王说：“带伞”，小王（习惯用手机查天气的科技控）会打开天气App。
> 
> 关键在于：小明只需说“带伞”这个抽象概念，无需知道具体执行方式。 伞的“带”操作被抽象为统一接口，而执行细节由不同对象自行实现。
>
> HAL库的HAL_UART_Transmit也体现了多态。调用者无需知道是F1系列还是H7系列芯片，底层自动适配不同实现。
>
> 换言之，**多态让抽象真正“活”起来：它将“行为”与“对象”解耦，让系统能动态响应变化。**

回到1.3章节提出的问题。继承的困境源于它强制了“is-a”的刚性关系，而现实世界往往更倾向于“has-a”的灵活组合。

多态的真正力量，恰恰在于它不依赖于继承，而是依赖于接口和抽象类型——让行为与对象解耦，而非通过血缘绑定。
> 定义一个 CommunicationDevice 接口，包含 send() 和 receive() 方法。
> 
> SPI、IIC、UART 等设备都实现这个接口，而非继承一个父类。
> 
> 业务代码（如数据传输模块）只依赖于 CommunicationDevice 接口，无需知道具体是 SPI 还是 UART。
> 
> 当新增 USB 设备时，只需实现接口，无需修改现有代码。
> 
> 系统通过接口调用 send()，多态自动选择正确的硬件实现。



# 17.1 — std::array 简介

在课程[16.1 -- 容器和数组介绍](https://www.learncpp.com/cpp-tutorial/introduction-to-containers-and-arrays/)中，我们介绍了容器和数组。总结一下：

- 容器为未命名对象（称为元素）的集合提供存储。
- 数组在内存中连续分配其元素，并允许通过下标快速、直接地访问任何元素。
- C++ 有三种常用的不同数组类型：`std::vector`、、`std::array`和 C 样式数组。

在课程[16.10 -- std::vector 的大小调整和容量](https://www.learncpp.com/cpp-tutorial/stdvector-resizing-and-capacity/)中，我们提到数组分为两类：

- 固定大小数组（也称为固定长度数组）要求在实例化时知道数组的长度，并且之后不能更改该长度。C 样式数组和`std::array`都是固定大小数组。
- 动态数组可以在运行时调整大小。`std::vector`是一个动态数组。

在上一章中，我们重点介绍了`std::vector`，因为它速度快、相对易用且用途广泛。这使得它成为我们需要数组容器时的首选类型。

## **那么为什么不对所有事情都使用动态数组呢？**

动态数组功能强大且方便，但就像生活中的所有事物一样，它们在提供好处的同时，也需要做出一些权衡。

- `std::vector`性能略低于固定大小数组。在大多数情况下，您可能不会注意到差异（除非您编写的代码很粗糙，导致大量无意的重新分配）。
- `std::vector`仅`constexpr`在非常有限的环境中提供支持。

在现代 C++ 中，后一点才是最重要的。`Constexpr` 数组提供了编写更强大的代码的能力，并且还可以由编译器进行更高程度的优化。只要我们可以使用 `constexpr` 数组，我们就应该这样做——如果我们需要 `constexpr` 数组，`std::array`那么它就是我们应该使用的容器类。

**最佳实践**

**用于`std::array`constexpr 数组和`std::vector`非 `constexpr` 数组。**

## 定义一个`std::array`

`std::array`在 <array> 标头中定义。它的设计工作方式与 类似`std::vector`，正如您所见，两者之间的相似之处多于不同之处。

一个区别在于我们如何声明`std::array`：

```cpp
#include <array>  // for std::array
#include <vector> // for std::vector

int main()
{
    std::array<int, 5> a {};  // a std::array of 5 ints

    std::vector<int> b(5);    // a std::vector of 5 ints (for comparison)

    return 0;
}
```



我们的`std::array`声明有两个模板参数。第一个（`int`）是定义数组元素类型的类型模板参数。第二个（`5`）是定义数组长度的整数非类型模板参数。

**相关内容**

**我们在第 11.9 课“非类型模板参数”中介绍[非类型模板参数](https://www.learncpp.com/cpp-tutorial/non-type-template-parameters/)。**

## `std::array`的长度必须是一个常量表达式

`std::vector`与可以在运行时调整大小的 不同， `std::array`的长度必须是常量表达式。通常，长度的值将是整数文字、 `constexpr` 变量或无作用域枚举器。

```cpp
#include <array>

int main()
{
    std::array<int, 7> a {}; // Using a literal constant

    constexpr int len { 8 };
    std::array<int, len> b {}; // Using a constexpr variable

    enum Colors
    {
         red,
         green,
         blue,
         max_colors
    };

    std::array<int, max_colors> c {}; // Using an enumerator

#define DAYS_PER_WEEK 7
    std::array<int, DAYS_PER_WEEK> d {}; // Using a macro (don't do this, use a constexpr variable instead)

    return 0;
}
```

请注意，非常量变量和运行时常量不能用于长度：

```cpp
#include <array>
#include <iostream>

void foo(const int length) // length is a runtime constant
{
    std::array<int, length> e {}; // error: length is not a constant expression
}

int main()
{
    // using a non-const variable
    int numStudents{};
    std::cin >> numStudents; // numStudents is non-constant

    std::array<int, numStudents> {}; // error: numStudents is not a constant expression

    foo(7);

    return 0;
}
```

**警告**

也许令人惊讶的是，a 的`std::array`长度可以定义为 0：

```cpp
#include <array>
#include <iostream>

int main()
{
    std::array<int, 0> arr {}; // creates a zero-length std::array
    std::cout << arr.empty();  // true if arr is zero-length

    return 0;
}
```

零长度`std::array`是没有数据的特殊情况类。因此，调用任何访问零长度`std::array`（包括`operator[]`）数据的成员函数都将产生未定义的行为。

您可以使用成员函数测试 a 是否`std::array`为零长度`empty()`，`true`如果数组长度为零，则返回，`false`否则返回。

## 聚合初始化`std::array`

也许令人惊讶的是，`std::array`它是一个聚合。这意味着它没有构造函数，而是使用聚合初始化进行初始化。简单回顾一下，聚合初始化允许我们直接初始化聚合的成员。为此，我们提供了一个初始化列表，它是一个用括号括起来的逗号分隔的初始化值列表。

相关内容

我们在第[13.8 课“结构聚合初始化”](https://www.learncpp.com/cpp-tutorial/struct-aggregate-initialization/)中介绍了结构体的聚合初始化。

```cpp
#include <array>

int main()
{
    std::array<int, 6> fibonnaci = { 0, 1, 1, 2, 3, 5 }; // copy-list initialization using braced list
    std::array<int, 5> prime { 2, 3, 5, 7, 11 };         // list initialization using braced list (preferred)

    return 0;
}
```

这些初始化形式中的每一种都按顺序初始化数组成员，从元素 0 开始。

如果定义 a 时`std::array`没有使用初始化器，则元素将被默认初始化。在大多数情况下，这将导致元素未初始化。

因为我们通常希望我们的元素被初始化，所以`std::array`当没有初始化器定义时应该进行值初始化（使用空括号）。

```cpp
#include <array>
#include <vector>

int main()
{
    std::array<int, 5> a;   // Members default initialized (int elements are left uninitialized)
    std::array<int, 5> b{}; // Members value initialized (int elements are zero initialized) (preferred)

    std::vector<int> v(5);  // Members value initialized (int elements are zero initialized) (for comparison)

    return 0;
}
```

如果初始化列表中提供的初始化器数量多于定义的数组长度，则编译器会出错。如果初始化列表中提供的初始化器数量少于定义的数组长度，则其余没有初始化器的元素将进行值初始化：

```cpp
#include <array>

int main()
{
    std::array<int, 4> a { 1, 2, 3, 4, 5 }; // compile error: too many initializers
    std::array<int, 4> b { 1, 2 };          // b[2] and b[3] are value initialized

    return 0;
}
```

## Const 和 constexpr`std::array`

A`std::array`可以是 const：

```cpp
#include <array>

int main()
{
    const std::array<int, 5> prime { 2, 3, 5, 7, 11 };

    return 0;
}
```

即使 a 的元素`const std::array`没有明确标记为 const，它们仍然被视为 const（因为整个数组都是 const）。

`std::array`还完全支持 `constexpr`：

```cpp
#include <array>

int main()
{
    constexpr std::array<int, 5> prime { 2, 3, 5, 7, 11 };

    return 0;
}
```

对 `constexpr` 的支持是使用 的主要原因`std::array`。

**最佳实践**

**`std::array`尽可能将你的定义为 `constexpr`。如果你的`std::array`不是 constexpr，请考虑改用`std::vector`。**

## C++17的类模板参数推导 (CTAD)`std::array`

`std::array`使用 C++17 中的 CTAD（类模板参数推导），我们可以让编译器从初始化器列表中推断出元素类型和数组长度：

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array a1 { 9, 7, 5, 3, 1 }; // The type is deduced to std::array<int, 5>
    constexpr std::array a2 { 9.7, 7.31 };     // The type is deduced to std::array<double, 2>

    return 0;
}
```

只要切实可行，我们都会推荐这种语法。如果您的编译器不支持 C++17，则需要明确提供类型和长度模板参数。

**最佳实践**

**使用类模板参数推导（CTAD）让编译器`std::array`从其初始化器中推导其类型和长度。**

CTAD 不支持模板参数的部分省略（从 C++23 开始），因此无法使用核心语言功能来仅省略长度或类型`std::array`：

```cpp
#include <iostream>

int main()
{
    constexpr std::array<int> a2 { 9, 7, 5, 3, 1 };     // error: too few template arguments (length missing)
    constexpr std::array<5> a2 { 9, 7, 5, 3, 1 };       // error: too few template arguments (type missing)

    return 0;
}
```

## 使用C++20仅省略数组长度`std::to_array`

但是，TAD（模板参数推导，用于函数模板解析）确实支持部分省略模板参数。从 C++20 开始，可以`std::array`使用`std::to_array`辅助函数省略 a 的数组长度：

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr auto myArray1 { std::to_array<int, 5>({ 9, 7, 5, 3, 1 }) }; // Specify type and size
    constexpr auto myArray2 { std::to_array<int>({ 9, 7, 5, 3, 1 }) };    // Specify type only, deduce size
    constexpr auto myArray3 { std::to_array({ 9, 7, 5, 3, 1 }) };         // Deduce type and size

    return 0;
}
```

不幸的是，使用`std::to_array`比直接创建更昂贵`std::array`，因为它涉及创建一个临时对象`std::array`，然后将其用于复制初始化我们所需的`std::array`。因此，`std::to_array`应该只在无法从初始化器中有效确定类型的情况下使用，并且应该在多次创建数组时避免使用（例如在循环内）。

例如，因为无法指定类型的文字`short`，所以您可以使用以下命令创建值`std::array`（`short`而不必明确指定的长度`std::array`）：

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr auto shortArray { std::to_array<short>({ 9, 7, 5, 3, 1 }) };
    std::cout << sizeof(shortArray[0]) << '\n';

    return 0;
}
```

## 使用以下方式访问数组元素`operator[]`

就像 a 一样`std::vector`，访问 a 元素的最常见方式`std::array`是使用下标运算符 ( `operator[]`)：

```cpp
#include <array> // for std::array
#include <iostream>

int main()
{
    constexpr std::array<int, 5> prime{ 2, 3, 5, 7, 11 };

    std::cout << prime[3]; // print the value of element with index 3 (7)
    std::cout << prime[9]; // invalid index (undefined behavior)

    return 0;
}
```

提醒一下，`operator[]`不进行边界检查。如果提供了无效的索引，则会导致未定义的行为。

`std::array`在下一课中，我们将讨论其他几种索引方法。

## 测验时间

### 问题 #1

使用哪种类型的初始化`std::array`？

`std::array`是一个聚合，因此它使用聚合初始化。

`std::array`如果您没有提供初始化值，为什么要明确地初始化值？

`std::array`如果没有提供初始化器，A将默认初始化成员。这将使大多数类型的元素处于未初始化状态。

### 问题 #2

定义一个`std::array`可以保存一年中每一天的高温（精确到十分之一度）。

```cpp
#include <array>

std::array<double, 365> highTemp {};
```

### **问题 #3**

使用以下值初始化 a `std::array`：'h'、'e'、'l'、'l'、'o'。打印索引为 1 的元素的值。

```cpp
#include <array>
#include <iostream>

int main()
{
        constexpr std::array arr { 'h', 'e', 'l', 'l', 'o' };
        std::cout << arr[1] << '\n';

        return 0;
}
```

# 17.2 — std::array 长度和索引

在课程[16.3 — std::vector 和无符号长度和下标问题](https://www.learncpp.com/cpp-tutorial/stdvector-and-the-unsigned-length-and-subscript-problem/)中，我们讨论了让标准库容器类使用无符号值作为长度和索引的不幸决定。由于`std::array`是标准库容器类，因此它也会遇到同样的问题。

在本课中，我们将回顾索引和获取 的长度的方法`std::array`。由于`std::vector`和`std::array`具有相似的接口，因此这将与我们介绍的 相似`std::vector`。但由于仅`std::array`完全支持 constexpr，我们将重点关注这一点。

在继续之前，现在是刷新你对“符号转换是缩小转换，除了 constexpr”的记忆的好时机（参见[16.3 - std::vector 和无符号长度和下标问题](https://www.learncpp.com/cpp-tutorial/stdvector-and-the-unsigned-length-and-subscript-problem/#constexprconversions)）。

## std::array`has 类型的长度`std::size_t

`std::array`作为模板结构实现，其声明如下：

```cpp
template<typename T, std::size_t N> // N is a non-type template parameter
struct array;
```

如您所见，表示数组长度（`N`）的非类型模板参数具有类型`std::size_t`。您现在可能已经知道，`std::size_t`这是一个大型无符号整数类型。

**相关内容**

**[我们在第13.13](https://www.learncpp.com/cpp-tutorial/class-templates/)课 - 类模板中介绍了类模板（包括结构模板），在第[11.9 课 - 非类型模板参数](https://www.learncpp.com/cpp-tutorial/non-type-template-parameters/)中介绍了非类型模板参数。**

因此，当我们定义 a 时`std::array`，长度非类型模板参数必须具有类型`std::size_t`，或者可以转换为类型的值`std::size_t`。因为这个值必须是 constexpr，所以当我们使用有符号整数值时，我们不会遇到符号转换问题，因为编译器会`std::size_t`在编译时愉快地将有符号整数值转换为 a ，而不会被视为缩小转换。

**顺便说一下……**

**在 C++23 之前，C++ 甚至没有 的文字后缀，因为从到 的`std::size_t`隐式编译时转换通常足以满足我们需要 constexpr 的情况。`int``std::size_t``std::size_t`**

**添加后缀主要是为了类型推断的目的，因为`constexpr auto x { 0 }`将给出一个`int`而不是一个`std::size_t`。在这种情况下，能够区分`0`（`int`）和`0UZ`（`std::size_t`）而无需使用显式的后缀`static_cast`是很有用的。**

`std::array`的长度和索引具有类型`size_type`，它始终是`std::size_t` 

就像 一样`std::vector`，`std::array`定义一个名为 的嵌套 typedef 成员`size_type`，它是用于容器长度（和索引，如果支持）的类型的别名。在 的情况下`std::array`，*始终*`size_type`是的别名。`std::size_t`

请注意，定义 长度的非类型模板参数`std::array`明确定义为`std::size_t`而不是`size_type`。这是因为`size_type`是 的成员`std::array`，并且此时未定义。这是唯一`std::size_t`明确使用 的地方——其他地方都使用`size_type`。

## 获取长度`std::array`

获取对象的长度有三种常见的方法`std::array`。

首先，我们可以使用成员函数（以无符号形式返回长度）询问`std::array`对象的长度：`size()``size_type`

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array arr { 9.0, 7.2, 5.4, 3.6, 1.8 };
    std::cout << "length: " << arr.size() << '\n'; // returns length as type `size_type` (alias for `std::size_t`)
    return 0;
}
```

这将打印：

```
长度：5
```

`std::string`与和不同`std::string_view`，它们同时具有`length()`和`size()`成员函数（执行相同的操作），而`std::array`（以及 C++ 中的大多数其他容器类型）只有`size()`。

其次，在 C++17 中，我们可以使用`std::size()`非成员函数（它只`std::array`调用`size()`成员函数，从而将长度返回为 unsigned `size_type`）。

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array arr{ 9, 7, 5, 3, 1 };
    std::cout << "length: " << std::size(arr); // C++17, returns length as type `size_type` (alias for `std::size_t`)

    return 0;
}
```

最后，在 C++20 中，我们可以使用`std::ssize()`非成员函数，它将长度作为大的*有符号*整数类型返回（通常为`std::ptrdiff_t`）：

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array arr { 9, 7, 5, 3, 1 };
    std::cout << "length: " << std::ssize(arr); // C++20, returns length as a large signed integral type

    return 0;
}
```

这是三个函数中唯一一个以有符号类型返回长度的函数。

## 获取 a 的长度`std::array`作为 constexpr 值

因为 a 的长度`std::array`是 constexpr，所以上述每个函数都将以`std::array`constexpr 值的形式返回 a 的长度（即使在非 constexpr`std::array`对象上调用时也是如此）！这意味着我们可以在常量表达式中使用这些函数中的任何一个，并且返回的长度可以隐式转换为，`int`而无需进行缩小转换：

```cpp
#include <array>
#include <iostream>

int main()
{
    std::array arr { 9, 7, 5, 3, 1 }; // note: not constexpr for this example
    constexpr int length{ std::size(arr) }; // ok: return value is constexpr std::size_t and can be converted to int, not a narrowing conversion

    std::cout << "length: " << length << '\n';

    return 0;
}
```

**对于 Visual Studio 用户**

**Visual Studio 错误地触发了上述示例的警告 C4365。此问题已[报告给 Microsoft](https://developercommunity.visualstudio.com/t/Bug:-C4365-triggers-incorrectly-for-cons/10372737)。**

**警告**

**`std::array`由于语言缺陷，当通过 (const) 引用传递的函数参数调用上述函数时，它们将返回非 `constexpr` 值：**

```cpp
#include <array>
#include <iostream>

void printLength(const std::array<int, 5> &arr)
{
    constexpr int length{ std::size(arr) }; // compile error!
    std::cout << "length: " << length << '\n';
}

int main()
{
    std::array arr { 9, 7, 5, 3, 1 };
    constexpr int length{ std::size(arr) }; // works just fine
    std::cout << "length: " << length << '\n';

    printLength(arr);

    return 0;
}
```

此缺陷已在 C++23 中通过[P2280](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2280r4.html)解决。在撰写本文时，目前很少有编译器[支持](https://en.cppreference.com/w/cpp/compiler_support/23)此功能。

一种解决方法是制作`foo()`一个函数模板，其中数组长度是非类型模板参数。然后可以在函数内部使用此非类型模板参数。我们将在第[17.3 课“传递和返回 std::array”](https://www.learncpp.com/cpp-tutorial/passing-and-returning-stdarray/)中进一步讨论这一点。

```cpp
template <auto Length>
void printLength(const std::array<int, Length> &arr)
{
    std::cout << "length: " << Length << '\n';
}
```

## `std::array`使用`operator[]`或`at()`成员函数进行下标

在上一课[17.1 -- std::array 简介](https://www.learncpp.com/cpp-tutorial/introduction-to-stdarray/)中，我们介绍了索引 a 的最常见方式`std::array`是使用下标运算符 ( `operator[]`)。在这种情况下不进行边界检查，传入无效索引将导致未定义的行为。

和 一样`std::vector`，`std::array`也有一个`at()`成员函数，它使用运行时边界检查来执行下标。我们建议避免使用此函数，因为我们通常希望在索引之前进行边界检查，或者我们希望进行编译时边界检查。

这两个函数都要求索引的类型为`size_type`( `std::size_t`)。

如果使用 constexpr 值调用这两个函数中的任何一个，编译器都会将 constexpr 转换为`std::size_t`。这不被视为收缩转换，因此您不会在这里遇到符号问题。

但是，如果使用非 constexpr 有符号整数值调用这两个函数中的任何一个，则转换为会被视为缩小，并且您的编译器可能会发出警告。我们将在第[16.3 课——std::vector 和无符号长度和下标问题](https://www.learncpp.com/cpp-tutorial/stdvector-and-the-unsigned-length-and-subscript-problem/)`std::size_t`中进一步讨论这种情况（使用`std::vector`）。

## `std::get()`对 `constexpr` 索引进行编译时边界检查

由于 a 的长度`std::array`是 `constexpr`，如果我们的索引也是一个 `constexpr` 值，那么编译器应该能够在编译时验证我们的 `constexpr` 索引是否在数组的范围内（如果 `constexpr` 索引超出范围，则停止编译）。

但是，`operator[]`根据定义，不进行边界检查，`at()`成员函数只进行运行时边界检查。并且函数参数不能是 `constexpr`（即使对于 `constexpr` 或 `consteval` 函数也是如此），那么我们如何传递 `constexpr` 索引呢？

当我们有一个 `constexpr` 索引时，为了获得编译时边界检查，我们可以使用`std::get()`函数模板，它将索引作为非类型模板参数：

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array prime{ 2, 3, 5, 7, 11 };

    std::cout << std::get<3>(prime); // print the value of element with index 3
    std::cout << std::get<9>(prime); // invalid index (compile error)

    return 0;
}
```

在 的实现中`std::get()`，有一个 static_assert 用来检查非类型模板参数是否小于数组长度。如果不是，则 static_assert 将以编译错误停止编译过程。

由于模板参数必须是 `constexpr`，因此`std::get()`只能使用 `constexpr` 索引来调用。

## 测验时间

问题 #1

使用以下值初始化 a `std::array`：'h'、'e'、'l'、'l'、'o'。打印数组的长度，然后使用`operator[]`、`at()`和`std::get()`打印索引为 1 的元素的值。

该程序应该打印：

```
The length is 5
eee
```

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array arr { 'h', 'e', 'l', 'l', 'o' };
    std::cout << "The length is " << std::size(arr) << '\n';
    std::cout << arr[1] << arr.at(1) << std::get<1>(arr) << '\n';

    return 0;
}
```

# 17.3 — 传递和返回 std::array

`std::array`类型的对象可以像任何其他对象一样传递给函数。这意味着如果我们`std::array`按值传递，则会进行昂贵的复制。因此，我们通常`std::array`通过 (const) 引用传递以避免此类复制。

对于 a 来说`std::array`，元素类型和数组长度都是对象类型信息的一部分。因此，当我们使用 a`std::array`作为函数参数时，我们必须明确指定元素类型和数组长度：

```cpp
#include <array>
#include <iostream>

void passByRef(const std::array<int, 5>& arr) // we must explicitly specify <int, 5> here
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 }; // CTAD deduces type std::array<int, 5>
    passByRef(arr);

    return 0;
}
```

CTAD（目前）不适用于函数参数，因此我们不能仅`std::array`在这里指定并让编译器推断模板参数。

## `std::array`使用函数模板传递不同的元素类型或长度

为了编写一个可以接受`std::array`任何类型的元素或任何长度的函数，我们可以创建一个函数模板，该模板同时参数化我们的元素类型和长度`std::array`，然后 C++ 将使用该函数模板来实例化具有实际类型和长度的真实函数。

由于`std::array`定义如下：

```cpp
template<typename T, std::size_t N> // N is a non-type template parameter
struct array;
```

我们可以创建一个使用相同模板参数声明的函数模板：

```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t N> // note that this template parameter declaration matches the one for std::array
void passByRef(const std::array<T, N>& arr)
{
    static_assert(N != 0); // fail if this is a zero-length std::array

    std::cout << arr[0] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 }; // use CTAD to infer std::array<int, 5>
    passByRef(arr);  // ok: compiler will instantiate passByRef(const std::array<int, 5>& arr)

    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // use CTAD to infer std::array<int, 6>
    passByRef(arr2); // ok: compiler will instantiate passByRef(const std::array<int, 6>& arr)

    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // use CTAD to infer std::array<double, 5>
    passByRef(arr3); // ok: compiler will instantiate passByRef(const std::array<double, 5>& arr)

    return 0;
}
```

在上面的例子中，我们创建了一个名为的函数模板`passByRef()`，它有一个类型为`std::array<T, N>`.的参数`T`，并`N`在上一行的模板参数声明中定义：`template <typename T, std::size_t N>`.`T`是一个标准类型模板参数，允许调用者指定元素类型。`N`是一个非类型模板参数，类型为`std::size_t`，允许调用者指定数组长度。

**警告**

**请注意，的非类型模板参数的类型`std::array`应该是`std::size_t`，而不是`int`！这是因为`std::array`定义为`template<class T, std::size_t N> struct array;`。如果使用`int`作为非类型模板参数的类型，编译器将无法将类型的参数`std::array<T, std::size_t>`与类型的参数匹配`std::array<T, int>`（并且模板不会进行转换）。**

因此，当我们调用`passByRef(arr)`from `main()`（其中`arr`定义为`std::array<int, 5>`）时，编译器将实例化并调用。和 也会`void passByRef(const std::array<int, 5>& arr)`发生类似`arr2``arr3`的过程。

因此，我们创建了一个单一函数模板，可以实例化函数来处理`std::array`任何元素类型和长度的参数！

如果需要，也可以只模板化两个模板参数中的一个。在下面的例子中，我们只参数化了 的长度`std::array`，但元素类型明确定义为`int`：

```cpp
#include <array>
#include <iostream>

template <std::size_t N> // note: only the length has been templated here
void passByRef(const std::array<int, N>& arr) // we've defined the element type as int
{
    static_assert(N != 0); // fail if this is a zero-length std::array

    std::cout << arr[0] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 }; // use CTAD to infer std::array<int, 5>
    passByRef(arr);  // ok: compiler will instantiate passByRef(const std::array<int, 5>& arr)

    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // use CTAD to infer std::array<int, 6>
    passByRef(arr2); // ok: compiler will instantiate passByRef(const std::array<int, 6>& arr)

    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // use CTAD to infer std::array<double, 5>
    passByRef(arr3); // error: compiler can't find matching function

    return 0;
}
```

## 自动非类型模板参数C++20

必须记住（或查找）非类型模板参数的类型，以便可以在自己的函数模板的模板参数声明中使用它，这很麻烦。

在 C++20 中，我们可以`auto`在模板参数声明中让非类型模板参数从参数中推断出其类型：

```cpp
#include <array>
#include <iostream>

template <typename T, auto N> // now using auto to deduce type of N
void passByRef(const std::array<T, N>& arr)
{
    static_assert(N != 0); // fail if this is a zero-length std::array

    std::cout << arr[0] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 }; // use CTAD to infer std::array<int, 5>
    passByRef(arr);  // ok: compiler will instantiate passByRef(const std::array<int, 5>& arr)

    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // use CTAD to infer std::array<int, 6>
    passByRef(arr2); // ok: compiler will instantiate passByRef(const std::array<int, 6>& arr)

    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // use CTAD to infer std::array<double, 5>
    passByRef(arr3); // ok: compiler will instantiate passByRef(const std::array<double, 5>& arr)

    return 0;
}
```

如果您的编译器支持 C++20，那么就可以使用。

## 数组长度静态断言

考虑以下模板函数，它与上面介绍的函数类似：

```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t N>
void printElement3(const std::array<T, N>& arr)
{
    std::cout << arr[3] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 };
    printElement3(arr);

    return 0;
}
```

虽然在`printElement3()`这种情况下运行良好，但这个程序中有一个潜在的错误，等待着粗心的程序员。看到了吗？

上述程序打印索引为 3 的数组元素的值。只要数组具有索引为 3 的有效元素，这就可以了。但是，编译器很乐意让您传入索引 3 超出范围的数组。例如：

```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t N>
void printElement3(const std::array<T, N>& arr)
{
    std::cout << arr[3] << '\n'; // invalid index
}

int main()
{
    std::array arr{ 9, 7 }; // a 2-element array (valid indexes 0 and 1)
    printElement3(arr);

    return 0;
}
```

这会导致未定义的行为。理想情况下，当我们尝试执行此类操作时，我们希望编译器发出警告！

模板参数相对于函数参数的一个优势是模板参数是编译时常量。这意味着我们可以利用需要常量表达式的功能。

因此，一个解决方案是使用`std::get()`（执行编译时边界检查）而不是`operator[]`（不执行边界检查）：

```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t N>
void printElement3(const std::array<T, N>& arr)
{
    std::cout << std::get<3>(arr) << '\n'; // checks that index 3 is valid at compile-time
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 };
    printElement3(arr); // okay

    std::array arr2{ 9, 7 };
    printElement3(arr2); // compile error

    return 0;
}
```

当编译器到达对 的调用时`printElement3(arr2)`，它将实例化函数`printElement3(const std::array<int, 2>&)`。此函数体中有行`std::get<3>(arr)`。由于数组参数的长度为 2，因此这是无效访问，编译器将发出错误。

另一种解决方案是`static_assert`自己验证数组长度的先决条件：

**相关内容**

**我们在第[9.6 课“Assert 和 static_assert”](https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/)中介绍了先决条件。**

```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t N>
void printElement3(const std::array<T, N>& arr)
{
    // precondition: array length must be greater than 3 so element 3 exists
    static_assert (N > 3);

    // we can assume the array length is greater than 3 beyond this point

    std::cout << arr[3] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 };
    printElement3(arr); // okay

    std::array arr2{ 9, 7 };
    printElement3(arr2); // compile error

    return 0;
}
```

当编译器到达对 的调用时`printElement3(arr2)`，它将实例化函数`printElement3(const std::array<int, 2>&)`。此函数体内有行`static_assert (N > 3)`。由于`N`模板非类型参数的值为`2`，并且`2 > 3`为 false，因此编译器将发出错误。

**关键见解**

**在上面的例子中，你可能想知道为什么我们使用`static_assert (N > 3);`而不是`static_assert (std::size(arr) > 3)`。由于上一课中提到的语言缺陷（[17.2 -- std::array 长度和索引](https://www.learncpp.com/cpp-tutorial/stdarray-length-and-indexing/)），后者在 C++23 之前无法编译。**

## 返回`std::array`

撇开语法不谈，将 a 传递`std::array`给函数在概念上很简单——通过 (const) 引用传递它。但是如果我们有一个需要返回 a 的函数怎么办`std::array`？事情会稍微复杂一些。与 不同`std::vector`，`std::array`不可移动，因此`std::array`按值返回 a 将复制数组。如果数组中的元素可移动，则它们将被移动，否则将被复制。

这里有两个常规选项，具体选择哪个取决于具体情况。

## 返回`std::array`值

`std:array`当以下所有条件都为真时，可以返回值：

- 该阵列并不大。
- 元素类型的复制（或移动）成本很低。
- 该代码未在性能敏感的环境中使用。

在这种情况下，将会进行复制`std::array`，但如果以上所有情况均为真，则性能下降将很小，并且坚持使用最常规的方式将数据返回给调用者可能是最好的选择。

```cpp
#include <array>
#include <iostream>
#include <limits>

// return by value
template <typename T, std::size_t N>
std::array<T, N> inputArray() // return by value
{
	std::array<T, N> arr{};
	std::size_t index { 0 };
	while (index < N)
	{
		std::cout << "Enter value #" << index << ": ";
		std::cin >> arr[index];

		if (!std::cin) // handle bad input
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		++index;
	}

	return arr;
}

int main()
{
	std::array<int, 5> arr { inputArray<int, 5>() };

	std::cout << "The value of element 2 is " << arr[2] << '\n';

	return 0;
}
```

此方法有以下优点：

- 它使用最常规的方式将数据返回给调用者。
- 很明显该函数正在返回一个值。
- 我们可以定义一个数组并使用函数在单个语句中初始化它。

还有一些缺点：

- 该函数返回数组及其所有元素的副本，这并不便宜。
- 当我们调用该函数时，我们必须明确提供模板参数，因为没有参数可以从中推导出它们。

## `std::array`通过输出参数返回

如果按值返回成本太高，我们可以使用输出参数。在这种情况下，调用者负责通过`std::array`非常量引用（或地址）传入，然后函数可以修改此数组。

```cpp
#include <array>
#include <limits>
#include <iostream>

template <typename T, std::size_t N>
void inputArray(std::array<T, N>& arr) // pass by non-const reference
{
	std::size_t index { 0 };
	while (index < N)
	{
		std::cout << "Enter value #" << index << ": ";
		std::cin >> arr[index];

		if (!std::cin) // handle bad input
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		++index;
	}

}

int main()
{
	std::array<int, 5> arr {};
	inputArray(arr);

	std::cout << "The value of element 2 is " << arr[2] << '\n';

	return 0;
}
```

此方法的主要优点是无需复制数组，因此非常高效。

还有一些缺点：

- 这种返回数据的方法是不常规的，而且不容易分辨出函数正在修改参数。
- 我们只能使用此方法为数组分配值，而不能初始化它。
- 此类函数不能用于生成临时对象。

## 返回`std::vector`一个

`std::vector`具有移动功能，并且可以通过值返回，而无需进行昂贵的复制。如果您`std::array`通过值返回，则`std::array`可能不是 `constexpr`，您应该考虑改用（并返回）`std::vector`。

## 测验时间

### 问题 #1

完成以下程序：

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array arr1 { 1, 4, 9, 16 };
    printArray(arr1);

    constexpr std::array arr2 { 'h', 'e', 'l', 'l', 'o' };
    printArray(arr2);

    return 0;
}
```

运行时，它应该打印：

```
The array (1, 4, 9, 16) has length 4
The array (h, e, l, l, o) has length 5
```

```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t N>
void printArray(const std::array<T, N>& arr)
{
    bool first { true };

    std::cout << "The array (";

    for (const auto& e: arr)
    {
        std::cout << (first ? "" : ", ");
        std::cout << e;
        first = false;
    }

    std::cout << ") has length " << N << '\n';
}

int main()
{
    constexpr std::array arr1 { 1, 4, 9, 16 };
    printArray(arr1);

    constexpr std::array arr2 { 'h', 'e', 'l', 'l', 'o' };
    printArray(arr2);

    return 0;
}
```

# 17.4 — 类类型的 std::array 和括号省略

A`std::array`不限于基本类型的元素。相反，a 的元素`std::array`可以是任何对象类型，包括复合类型。这意味着您可以创建一个`std::array`指针类型的对象，或者创建一个`std::array`结构类型的对象（或类）

然而，初始化`std::array`结构或类往往会让新程序员感到困惑，所以我们将花一节课明确地讨论这个主题。

## 定义并分配`std::array`结构体

让我们从一个简单的结构开始：

```cpp
struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};
```

定义并分配元素`std::array`的`House`工作方式与您预期的一样：

```cpp
#include <array>
#include <iostream>

struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

int main()
{
    std::array<House, 3> houses{};

    houses[0] = { 13, 1, 7 };
    houses[1] = { 14, 2, 5 };
    houses[2] = { 15, 2, 4 };

    for (const auto& house : houses)
    {
        std::cout << "House number " << house.number
                  << " has " << (house.stories * house.roomsPerStory)
                  << " rooms.\n";
    }

    return 0;
}
```

上述输出如下：

```
House number 13 has 7 rooms.
House number 14 has 10 rooms.
House number 15 has 8 rooms.
```

## 初始化`std::array`结构体

初始化结构数组也像您预期的那样工作，只要您明确说明元素类型：

```cpp
#include <array>
#include <iostream>

struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

int main()
{
    constexpr std::array houses { // use CTAD to deduce template arguments <House, 3>
            House{ 13, 1, 7 },
            House{ 14, 2, 5 },
            House{ 15, 2, 4 }
        };

    for (const auto& house : houses)
    {
        std::cout << "House number " << house.number
            << " has " << (house.stories * house.roomsPerStory)
            << " rooms.\n";
    }

    return 0;
}
```

`std::array`在上面的例子中，我们使用 CTAD 推断出as的类型`std::array<House, 3>`。然后，我们提供 3 个`House`对象作为初始化器，效果很好。

初始化时没有明确指定每个初始化器的元素类型

在上面的例子中，您会注意到每个初始化器都要求我们列出元素类型：

```cpp
constexpr std::array houses {
        House{ 13, 1, 7 }, // we mention House here
        House{ 14, 2, 5 }, // and here
        House{ 15, 2, 4 }  // and here
    };
```

但是在赋值的情况下我们不必做同样的事情：

```cpp
// The compiler knows that each element of houses is a House
// so it will implicitly convert the right hand side of each assignment to a House
houses[0] = { 13, 1, 7 };
houses[1] = { 14, 2, 5 };
houses[2] = { 15, 2, 4 };
```

因此你可能会想尝试这样的事情：

```cpp
// doesn't work
constexpr std::array<House, 3> houses { // we're telling the compiler that each element is a House
        { 13, 1, 7 }, // but not mentioning it here
        { 14, 2, 5 },
        { 15, 2, 4 }
    };
```

也许令人惊讶的是，这种方法不起作用。让我们来探究一下原因。

A`std::array`被定义为一个包含单个 C 样式数组成员（其名称由实现定义）的结构，如下所示：

```cpp
template<typename T, std::size_t N>
struct array
{
    T implementation_defined_name[N]; // a C-style array with N elements of type T
}
```

**作者注**

**我们还没有介绍过 C 风格的数组，但就本课而言，您只需要知道它`T implementation_defined_name[N];`是一个由 N 个 T 类型元素组成的固定大小数组（就像`std::array<T, N> implementation_defined_name;`）。**

**我们将在即将到来的 17.7 课——C 风格数组简介中[介绍 C 风格数组](https://www.learncpp.com/cpp-tutorial/introduction-to-c-style-arrays/)。**

因此，当我们尝试按照上述方式进行初始化时`houses`，编译器会按如下方式解释初始化：

```cpp
// Doesn't work
constexpr std::array<House, 3> houses { // initializer for houses
    { 13, 1, 7 }, // initializer for C-style array member with implementation_defined_name
    { 14, 2, 5 }, // ?
    { 15, 2, 4 }  // ?
};
```

编译器将解释`{ 13, 1, 7 }`为 的第一个成员的初始化器`houses`，即具有实现定义名称的 C 样式数组。这将使用 初始化 C 样式数组元素 0 `{ 13, 1, 7 }`，其余成员将初始化为零。然后编译器将发现我们提供了另外两个初始化值（`{ 14, 2, 7 }`和`{ 15, 2, 5 }`），并产生编译错误，告诉我们提供了太多的初始化值。

初始化上述内容的正确方法是添加一组额外的括号，如下所示：

```cpp
// This works as expected
constexpr std::array<House, 3> houses { // initializer for houses
    { // extra set of braces to initialize the C-style array member with implementation_defined_name
        { 13, 4, 30 }, // initializer for array element 0
        { 14, 3, 10 }, // initializer for array element 1
        { 15, 3, 40 }, // initializer for array element 2
     }
};
```

请注意需要额外的一组括号（用于开始初始化结构内的 C 样式数组成员`std::array `）。在这些括号内，我们可以单独初始化每个元素，每个元素都在其自己的一组括号内。

`std::array`这就是为什么当元素类型需要值列表而我们没有明确提供元素类型作为初始化器的一部分时，您会看到带有一组额外括号的初始化器。

**关键见解**

**当使用结构、类或数组初始化`std::array`并且不为每个初始化器提供元素类型时，您将需要一对额外的括号，以便编译器正确解释要初始化的内容。**

**这是聚合初始化的产物，其他标准库容器类型（使用列表构造函数）在这些情况下不需要双括号。**

这是一个完整的例子：

```cpp
#include <array>
#include <iostream>

struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

int main()
{
    constexpr std::array<House, 3> houses {{ // note double braces
        { 13, 1, 7 },
        { 14, 2, 5 },
        { 15, 2, 4 }
    }};

    for (const auto& house : houses)
    {
        std::cout << "House number " << house.number
                  << " has " << (house.stories * house.roomsPerStory)
                  << " rooms.\n";
    }

    return 0;
}
```

## 聚合体的括号省略

根据上述解释，您可能想知道为什么上述情况需要双括号，但我们见过的所有其他情况只需要单括号：

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array<int, 5> arr { 1, 2, 3, 4, 5 }; // single braces

    for (const auto n : arr)
        std::cout << n << '\n';

    return 0;
}
```

事实证明，你可以为此类数组提供双括号：

```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array<int, 5> arr {{ 1, 2, 3, 4, 5 }}; // double braces

    for (const auto n : arr)
        std::cout << n << '\n';

    return 0;
}
```

但是，C++ 中的聚合支持一种称为**括号省略的**概念，该概念规定了何时可以省略多个括号。通常，在`std::array`使用标量（单个）值初始化时，或者在使用类类型或数组初始化时（其中类型用每个元素明确命名），可以省略括号。

总是用双括号初始化并没有什么坏处`std::array`，因为它避免了考虑在特定情况下是否可以使用括号省略。或者，您可以尝试使用单括号初始化，如果编译器无法弄清楚，它通常会报错。在这种情况下，您可以快速添加一组额外的括号。

另一个例子

下面是另一个我们`std::array`用`Student`结构体初始化的例子。

```cpp
#include <array>
#include <iostream>
#include <string_view>

// Each student has an id and a name
struct Student
{
	int id{};
	std::string_view name{};
};

// Our array of 3 students (single braced since we mention Student with each initializer)
constexpr std::array students{ Student{0, "Alex"}, Student{ 1, "Joe" }, Student{ 2, "Bob" } };

const Student* findStudentById(int id)
{
	// Look through all the students
	for (auto& s : students)
	{
		// Return student with matching id
		if (s.id == id) return &s;
	}

	// No matching id found
	return nullptr;
}

int main()
{
	constexpr std::string_view nobody { "nobody" };

	const Student* s1 { findStudentById(1) };
	std::cout << "You found: " << (s1 ? s1->name : nobody) << '\n';

	const Student* s2 { findStudentById(3) };
	std::cout << "You found: " << (s2 ? s2->name : nobody) << '\n';

	return 0;
}
```

这将打印：

```
You found: Joe
You found: nobody
```

注意，因为`std::array students`是 `constexpr`，所以我们的`findStudentById()`函数必须返回一个 const 指针，这意味着我们的`Student`指针`main()`也必须是 const。

## 测验时间

### **问题 #1**

定义一个名为的结构体`Item`，其中包含两个成员：`std::string_view name`和`int gold`。定义一个`std::array`并用 4 个 Item 对象初始化它。使用 CTAD 推断元素类型和数组大小。

```
A sword costs 5 gold.
A dagger costs 3 gold.
A club costs 2 gold.
A spear costs 7 gold.
```

```cpp
#include <array>
#include <iostream>
#include <string_view>

struct Item
{
    std::string_view name {};
    int gold {};
};

template <std::size_t N>
void printStore(const std::array<Item, N>& arr)
{
    for (const auto& item: arr)
    {
        std::cout << "A " << item.name << " costs " << item.gold << " gold.\n";
    }
}

int main()
{
    constexpr std::array store { // CTAD, single braces due to brace elision
        Item { "sword",    5 },
        Item { "dagger",   3 },
        Item { "club",     2 },
        Item { "spear",    7 } };
    printStore(store);

    return 0;
}
```

### 问题 #2

更新测验 1 的解决方案，不要明确指定每个初始化程序的元素类型。

```cpp
#include <array>
#include <iostream>
#include <string_view>

struct Item
{
    std::string_view name {};
    int gold {};
};

template <std::size_t N>
void printStore(const std::array<Item, N>& arr)
{
    for (const auto& item: arr)
    {
        std::cout << "A " << item.name << " costs " << item.gold << " gold.\n";
    }
}

int main()
{
    constexpr std::array<Item, 4> store {{ // No CTAD, must use double braces
        { "sword",    5 },
        { "dagger",   3 },
        { "club",     2 },
        { "spear",    7 }
    }};
    printStore(store);

    return 0;
}
```

# 17.5 — 通过 std::reference_wrapper 引用数组

在上一课中，我们提到数组可以包含任何对象类型的元素。这包括基本类型的对象（例如 int）和复合类型的对象（例如指向 int 的指针）。

```cpp
#include <array>
#include <iostream>
#include <vector>

int main()
{
    int x { 1 };
    int y { 2 };

    [[maybe_unused]] std::array valarr { x, y };   // an array of int values
    [[maybe_unused]] std::vector ptrarr { &x, &y }; // a vector of int pointers

    return 0;
}
```

但是，由于引用不是对象，因此不能创建引用数组。数组的元素也必须是可分配的，并且引用不能重新放置。

```cpp
#include <array>
#include <iostream>

int main()
{
    int x { 1 };
    int y { 2 };

    [[maybe_unused]] std::array<int&, 2> refarr { x, y }; // compile error: cannot define array of references

    int& ref1 { x };
    int& ref2 { y };
    [[maybe_unused]] std::array valarr { ref1, ref2 }; // ok: this is actually a std::array<int, 2>, not an array of references

    return 0;
}
```

在本课中，我们将使用`std::array`示例，但这同样适用于所有数组类型。

但是，如果您想要一个引用数组，那么有一个解决方法。

## **std::reference_wrapper**

`std::reference_wrapper`是位于 < functional > 标头中的标准库类模板。它采用类型模板参数 T，然后表现为对 T 的可修改左值引用。

有几件事值得注意`std::reference_wrapper`：

- `Operator=`将重新安置`std::reference_wrapper`（更改正在引用的对象）。
- `std::reference_wrapper<T>`将隐式转换为`T&`。
- 成员函数`get()`可用于获取`T&`。当我们想要更新所引用对象的值时，这很有用。

这是一个简单的例子：

```cpp
#include <array>
#include <functional> // for std::reference_wrapper
#include <iostream>

int main()
{
    int x { 1 };
    int y { 2 };
    int z { 3 };

    std::array<std::reference_wrapper<int>, 3> arr { x, y, z };

    arr[1].get() = 5; // modify the object in array element 1

    std::cout << arr[1] << y << '\n'; // show that we modified arr[1] and y, prints 55

    return 0;
}
```

此示例打印以下内容：

```
55
```

请注意，我们必须使用`arr[1].get() = 5`而不是`arr[1] = 5`。后者具有歧义，因为编译器无法判断我们是否打算将 重新设置`std::reference_wrapper<int>`为值 5（无论如何这都是非法的）或更改所引用的值。使用`get()`可以消除这种歧义。

当打印 时`arr[1]`，编译器会意识到它无法打印`std::reference_wrapper<int>`，因此它会隐式地将其转换为`int&`，然后才能打印。所以我们不需要`get()`在这里使用 。

## std::ref`和`std::cref

在 C++17 之前，CTAD（类模板参数推导）并不存在，因此需要明确列出类类型的所有模板参数。因此，要创建`std::reference_wrapper<int>`，您可以执行以下操作之一：

```cpp
int x { 5 };

std::reference_wrapper<int> ref1 { x };        // C++11
auto ref2 { std::reference_wrapper<int>{ x }}; // C++11
```

在长名称和必须明确列出模板参数之间，创建许多这样的引用包装器可能会很麻烦。

为了简化操作，提供了`std::ref()`和`std::cref()`函数作为创建`std::reference_wrapper`和`const std::reference_wrapper`包装对象的快捷方式。请注意，这些函数可以与一起使用，`auto`以避免必须明确指定模板参数。

```cpp
int x { 5 };
auto ref { std::ref(x) };   // C++11, deduces to std::reference_wrapper<int>
auto cref { std::cref(x) }; // C++11, deduces to std::reference_wrapper<const int>
```

当然，现在我们在 C++17 中有了 CTAD，我们也可以这样做：

```cpp
std::reference_wrapper ref1 { x };        // C++17
auto ref2 { std::reference_wrapper{ x }}; // C++17
```

但由于`std::ref()`和`std::cref()`输入较短，它们仍然被广泛用于创建`std::reference_wrapper`对象。

# 17.6 — std::array 和枚举

在第 16.9 课[——使用枚举器进行数组索引和长度计算](https://www.learncpp.com/cpp-tutorial/array-indexing-and-length-using-enumerators/)中，我们讨论了数组和枚举。

现在我们有了`constexpr std::array`工具包，我们将继续讨论并展示一些额外的技巧。

## 使用静态断言来确保数组初始化器的数量正确

使用 CTAD初始化时`constexpr std::array`，编译器会根据初始化器的数量推断数组的长度。如果提供的初始化器数量少于应有的数量，数组的长度将比预期的要短，并且对其进行索引可能会导致未定义的行为。

例如：

```cpp
#include <array>
#include <iostream>

enum StudentNames
{
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    max_students // 5
};

int main()
{
    constexpr std::array testScores { 78, 94, 66, 77 }; // oops, only 4 values

    std::cout << "Cartman got a score of " << testScores[StudentNames::cartman] << '\n'; // undefined behavior due to invalid index

    return 0;
}
```

只要可以合理地检查初始化器的数量`constexpr std::array`，就可以使用静态断言来进行：

```cpp
#include <array>
#include <iostream>

enum StudentNames
{
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    max_students // 5
};

int main()
{
    constexpr std::array testScores { 78, 94, 66, 77 };

    // Ensure the number of test scores is the same as the number of students
    static_assert(std::size(testScores) == max_students); // compile error: static_assert condition failed

    std::cout << "Cartman got a score of " << testScores[StudentNames::cartman] << '\n';

    return 0;
}
```

这样，如果您稍后添加新的枚举器但忘记添加相应的初始化器`testScores`，则程序将编译失败。

您还可以使用静态断言来确保两个不同的`constexpr std::array`具有相同的长度。

## 使用 constexpr 数组实现更好的枚举输入和输出

在第 13.5课[——I/O 运算符重载简介](https://www.learncpp.com/cpp-tutorial/introduction-to-overloading-the-i-o-operators/)中，我们介绍了几种输入和输出枚举器名称的方法。为了协助完成这项任务，我们提供了辅助函数，用于将枚举器转换为字符串，反之亦然。这些函数各自都有一组（重复的）字符串文字，我们必须专门编写代码逻辑来检查每个函数：

```cpp
constexpr std::string_view getPetName(Pet pet)
{
    switch (pet)
    {
    case cat:   return "cat";
    case dog:   return "dog";
    case pig:   return "pig";
    case whale: return "whale";
    default:    return "???";
    }
}

constexpr std::optional<Pet> getPetFromString(std::string_view sv)
{
    if (sv == "cat")   return cat;
    if (sv == "dog")   return dog;
    if (sv == "pig")   return pig;
    if (sv == "whale") return whale;

    return {};
}
```



这意味着如果我们要添加新的枚举器，我们必须记住更新这些函数。

让我们稍微改进一下这些函数。如果枚举器的值从 0 开始并按顺序进行（大多数枚举都是如此），我们可以使用数组来保存每个枚举器的名称。

这使我们能够做两件事：

1. 使用枚举器的值对数组进行索引以获取该枚举器的名称。
2. 使用循环遍历所有名称，并能够根据索引将名称关联回枚举器。

```cpp
#include <array>
#include <iostream>
#include <string>
#include <string_view>

namespace Color
{
    enum Type
    {
        black,
        red,
        blue,
        max_colors
    };

    // use sv suffix so std::array will infer type as std::string_view
    using namespace std::string_view_literals; // for sv suffix
    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

    // Make sure we've defined strings for all our colors
    static_assert(std::size(colorName) == max_colors);
};

constexpr std::string_view getColorName(Color::Type color)
{
    // We can index the array using the enumerator to get the name of the enumerator
    return Color::colorName[color];
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout
// The return type and parameter type are references (to prevent copies from being made)!
std::ostream& operator<<(std::ostream& out, Color::Type color)
{
    return out << getColorName(color);
}

// Teach operator>> how to input a Color by name
// We pass color by non-const reference so we can have the function modify its value
std::istream& operator>> (std::istream& in, Color::Type& color)
{
    std::string input {};
    std::getline(in >> std::ws, input);

    // Iterate through the list of names to see if we can find a matching name
    for (std::size_t index=0; index < Color::colorName.size(); ++index)
    {
        if (input == Color::colorName[index])
        {
            // If we found a matching name, we can get the enumerator value based on its index
            color = static_cast<Color::Type>(index);
            return in;
        }
    }

    // We didn't find a match, so input must have been invalid
    // so we will set input stream to fail state
    in.setstate(std::ios_base::failbit);

    // On an extraction failure, operator>> zero-initializes fundamental types
    // Uncomment the following line to make this operator do the same thing
    // color = {};
    return in;
}

int main()
{
    auto shirt{ Color::blue };
    std::cout << "Your shirt is " << shirt << '\n';

    std::cout << "Enter a new color: ";
    std::cin >> shirt;
    if (!std::cin)
        std::cout << "Invalid\n";
    else
        std::cout << "Your shirt is now " << shirt << '\n';

    return 0;
}
```

这将打印：

```
Your shirt is blue
Enter a new color: red
Your shirt is now red
```

## 基于范围的 for 循环和枚举

有时我们会遇到需要遍历枚举的枚举器的情况。虽然我们可以使用带有整数索引的 for 循环来执行此操作，但这可能需要将整数索引大量静态转换为我们的枚举类型。

```cpp
#include <array>
#include <iostream>
#include <string_view>

namespace Color
{
    enum Type
    {
        black,
        red,
        blue,
        max_colors
    };

    // use sv suffix so std::array will infer type as std::string_view
    using namespace std::string_view_literals; // for sv suffix
    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

    // Make sure we've defined strings for all our colors
    static_assert(std::size(colorName) == max_colors);
};

constexpr std::string_view getColorName(Color::Type color)
{
    return Color::colorName[color];
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout
// The return type and parameter type are references (to prevent copies from being made)!
std::ostream& operator<<(std::ostream& out, Color::Type color)
{
    return out << getColorName(color);
}

int main()
{
    // Use a for loop to iterate through all our colors
    for (int i=0; i < Color::max_colors; ++i )
        std::cout << static_cast<Color::Type>(i) << '\n';

    return 0;
}
```

不幸的是，基于范围的 for 循环不允许您迭代枚举的枚举器：

```cpp
#include <array>
#include <iostream>
#include <string_view>

namespace Color
{
    enum Type
    {
        black,
        red,
        blue,
        max_colors
    };

    // use sv suffix so std::array will infer type as std::string_view
    using namespace std::string_view_literals; // for sv suffix
    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

    // Make sure we've defined strings for all our colors
    static_assert(std::size(colorName) == max_colors);
};

constexpr std::string_view getColorName(Color::Type color)
{
    return Color::colorName[color];
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout
// The return type and parameter type are references (to prevent copies from being made)!
std::ostream& operator<<(std::ostream& out, Color::Type color)
{
    return out << getColorName(color);
}

int main()
{
    for (auto c: Color::Type) // compile error: can't traverse enumeration
        std::cout << c < '\n';

    return 0;
}
```

对此有很多创造性的解决方案。由于我们可以在数组上使用基于范围的 for 循环，因此最直接的解决方案之一是创建一个`constexpr std::array`包含每个枚举器的数组，然后对其进行迭代。此方法仅在枚举器具有唯一值时才有效。

```cpp
#include <array>
#include <iostream>
#include <string_view>

namespace Color
{
    enum Type
    {
        black,     // 0
        red,       // 1
        blue,      // 2
        max_colors // 3
    };

    using namespace std::string_view_literals; // for sv suffix
    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };
    static_assert(std::size(colorName) == max_colors);

    constexpr std::array types { black, red, blue }; // A std::array containing all our enumerators
    static_assert(std::size(types) == max_colors);
};

constexpr std::string_view getColorName(Color::Type color)
{
    return Color::colorName[color];
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout
// The return type and parameter type are references (to prevent copies from being made)!
std::ostream& operator<<(std::ostream& out, Color::Type color)
{
    return out << getColorName(color);
}

int main()
{
    for (auto c: Color::types) // ok: we can do a range-based for on a std::array
        std::cout << c << '\n';

    return 0;
}
```



在上面的例子中，由于 的元素类型`Color::types`是`Color::Type`，变量`c`将被推断为`Color::Type`，这正是我们想要的！

这将打印：

```
black
red
blue
```

## 测验时间

定义一个名为 的命名空间`Animal`。在其中定义一个枚举，其中包含以下动物：鸡、狗、猫、大象、鸭子和蛇。还要创建一个名为 的结构体`Data`来存储每种动物的名称、腿的数量以及它们发出的声音。创建一个`std::array`Data 并为每种动物填写一个 Data 元素。

要求用户输入动物的名称。如果该名称与我们的某个动物的名称不匹配，请告知他们。否则，打印该动物的数据。然后打印与其输入不匹配的所有其他动物的数据。

例如：

```
Enter an animal: dog
A dog has 4 legs and says woof.

Here is the data for the rest of the animals:
A chicken has 2 legs and says cluck.
A cat has 4 legs and says meow.
A elephant has 4 legs and says pawoo.
A duck has 2 legs and says quack.
A snake has 0 legs and says hissss.
Enter an animal: frog
That animal couldn't be found.

Here is the data for the rest of the animals:
A chicken has 2 legs and says cluck.
A dog has 4 legs and says woof.
A cat has 4 legs and says meow.
A elephant has 4 legs and says pawoo.
A duck has 2 legs and says quack.
A snake has 0 legs and says hissss.
```

```cpp
#include <array>
#include <iostream>
#include <string>
#include <string_view>

namespace Animal
{
    enum Type
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        max_animals
    };

    struct Data
    {
        std::string_view name{};
        int legs{};
        std::string_view sound{};
    };

    constexpr std::array types { chicken, dog, cat, elephant, duck, snake };
    constexpr std::array data {
        Data{ "chicken",    2, "cluck" },
        Data{ "dog",        4, "woof" },
        Data{ "cat",        4, "meow" },
        Data{ "elephant",   4, "pawoo" },
        Data{ "duck",       2, "quack" },
        Data{ "snake",      0, "hissss" },
    };

    static_assert(std::size(types) == max_animals);
    static_assert(std::size(data) == max_animals);
}

// Teach operator>> how to input an Animal by name
// We pass animal by non-const reference so we can have the function modify its value
std::istream& operator>> (std::istream& in, Animal::Type& animal)
{
    std::string input {};
    std::getline(in >> std::ws, input);

    // See if we can find a match
    for (std::size_t index=0; index < Animal::data.size(); ++index)
    {
        if (input == Animal::data[index].name)
        {
            animal = static_cast<Animal::Type>(index);
            return in;
        }
    }

    // We didn't find a match, so input must have been invalid
    // so we will set input stream to fail state
    in.setstate(std::ios_base::failbit);
    return in;
}

void printAnimalData(Animal::Type type)
{
    const Animal::Data& animal { Animal::data[type] };
    std::cout << "A " << animal.name << " has " << animal.legs << " legs and says " << animal.sound << ".\n";
}

int main()
{
    std::cout << "Enter an animal: ";
    Animal::Type type{};
    std::cin >> type;

    // If users input didn't match
    if (!std::cin)
    {
        std::cin.clear();
        std::cout << "That animal couldn't be found.\n";
        type = Animal::max_animals; // set to invalid option so we don't match below
    }
    else
        printAnimalData(type);


    std::cout << "\nHere is the data for the rest of the animals:\n";
    for (auto a : Animal::types)
    {
        if (a != type)
            printAnimalData(a);
    }

    return 0;
}
```

# 17.7 — C 风格数组简介

现在我们已经介绍了`std::vector`和`std::array`，我们将通过介绍最后一种数组类型：C 样式数组来完成对数组的介绍。

正如第[16.1 课 - 容器和数组简介](https://www.learncpp.com/cpp-tutorial/introduction-to-containers-and-arrays/)中提到的，C 样式数组是从 C 语言继承而来的，并且内置于 C++ 的核心语言中（与其他数组类型不同，它们是标准库容器类）。这意味着我们不需要 #include 头文件来使用它们。

**顺便说一下……**

**因为它们是该语言本身支持的唯一数组类型，所以标准库数组容器类型（例如`std::array`和`std::vector`）通常使用 C 样式数组实现。**

## 声明 C 样式数组

由于 C 样式数组是核心语言的一部分，因此它们有自己的特殊声明语法。在 C 样式数组声明中，我们使用方括号 ( `[]`) 来告诉编译器声明的对象是 C 样式数组。在方括号内，我们可以选择提供数组的长度，这是一个类型的整数值，`std::size_t`它告诉编译器数组中有多少个元素。

以下定义创建一个名为的 C 样式数组变量`testScore`，其中包含 30 个类型元素`int`：

```cpp
int main()
{
    int testScore[30] {};      // Defines a C-style array named testScore that contains 30 value-initialized int elements (no include required)

//  std::array<int, 30> arr{}; // For comparison, here's a std::array of 30 value-initialized int elements (requires #including <array>)

    return 0;
}
```

C 样式数组的长度必须至少为 1。如果数组长度为零、负数或非整数值，编译器将出错。

**对于高级读者**

**在堆上动态分配的 C 样式数组的长度可以为 0。**

**C 风格数组的数组长度必须是常量表达式**

**就像`std::array`，当声明一个 C 风格的数组时，数组的长度必须是一个常量表达式（类型为`std::size_t`，尽管这通常并不重要）。**

**提示**

**一些编译器可能允许创建具有非 constexpr 长度的数组，以与称为可变长度数组 (VLA) 的 C99 特性兼容。**

**可变长度数组不是有效的 C++，不应在 C++ 程序中使用。如果您的编译器允许这些数组，您可能忘记禁用编译器扩展（请参阅[0.10 -- 配置您的编译器：编译器扩展](https://www.learncpp.com/cpp-tutorial/configuring-your-compiler-compiler-extensions/)）。**

## 对 C 样式数组进行下标

就像一样`std::array`，C 样式数组可以使用下标运算符 ( `operator[]`) 进行索引：

```cpp
#include <iostream>

int main()
{
    int arr[5]; // define an array of 5 int values

    arr[1] = 7; // use subscript operator to index array element 1
    std::cout << arr[1]; // prints 7

    return 0;
}
```

与标准库容器类（`std::size_t`仅使用无符号类型的索引）不同，C 样式数组的索引可以是任何整数类型（有符号或无符号）的值或无范围枚举。这意味着 C 样式数组不受标准库容器类所具有的所有符号转换索引问题的影响！

```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 8, 7, 6, 5 };

    int s { 2 };
    std::cout << arr[s] << '\n'; // okay to use signed index

    unsigned int u { 2 };
    std::cout << arr[u] << '\n'; // okay to use unsigned index

    return 0;
}
```

**提示**

**C 风格数组将接受有符号或无符号索引（或无范围枚举）。**

**`operator[]`不进行任何边界检查，传递超出边界的索引将导致未定义的行为。**

**顺便说一下……**

**当声明一个数组（例如`int arr[5]`）时，使用`[]`是声明语法的一部分，而不是下标运算符的调用`operator[]`。**

## C 风格数组的聚合初始化

就像一样`std::array`，C 风格的数组是聚合体，这意味着它们可以使用聚合初始化来初始化。

简单回顾一下，聚合初始化允许我们直接初始化聚合的成员。为此，我们提供了一个初始化列表，它是一个用括号括起来的逗号分隔的初始化值列表。

```cpp
int main()
{
    int fibonnaci[6] = { 0, 1, 1, 2, 3, 5 }; // copy-list initialization using braced list
    int prime[5] { 2, 3, 5, 7, 11 };         // list initialization using braced list (preferred)

    return 0;
}
```

这些初始化形式中的每一种都按顺序初始化数组成员，从元素 0 开始。

如果您没有为 C 样式数组提供初始化程序，则元素将被默认初始化。在大多数情况下，这将导致元素未初始化。因为我们通常希望初始化元素，所以当定义时不使用初始化程序时，C 样式数组应该进行值初始化（使用空括号）。

```cpp
int main()
{
    int arr1[5];    // Members default initialized int elements are left uninitialized)
    int arr2[5] {}; // Members value initialized (int elements are zero uninitialized) (preferred)

    return 0;
}
```

如果初始化列表中提供的初始化器数量多于定义的数组长度，则编译器会出错。如果初始化列表中提供的初始化器数量少于定义的数组长度，则其余没有初始化器的元素将进行值初始化：

```cpp
int main()
{
    int a[4] { 1, 2, 3, 4, 5 }; // compile error: too many initializers
    int b[4] { 1, 2 };          // arr[2] and arr[3] are value initialized

    return 0;
}
```

使用 C 样式数组的一个缺点是必须明确指定元素的类型。CTAD 不起作用，因为 C 样式数组不是类模板。并且使用`auto`尝试从初始化器列表中推断数组的元素类型也不起作用：

```cpp
int main()
{
    auto squares[5] { 1, 4, 9, 16, 25 }; // compile error: can't use type deduction on C-style arrays

    return 0;
}
```

## 省略长度

下面的数组定义中有一个微妙的冗余。发现了吗？

```cpp
int main()
{
    const int prime[5] { 2, 3, 5, 7, 11 }; // prime has length 5

    return 0;
}
```

我们明确地告诉编译器数组的长度为 5，然后我们还用 5 个元素初始化它。当我们使用初始化列表初始化 C 样式数组时，我们可以省略长度（在数组定义中），让编译器根据初始化器的数量推断出数组的长度。

以下数组定义的行为相同：

```cpp
int main()
{
    const int prime1[5] { 2, 3, 5, 7, 11 }; // prime1 explicitly defined to have length 5
    const int prime2[] { 2, 3, 5, 7, 11 };  // prime2 deduced by compiler to have length 5

    return 0;
}
```

仅当为所有数组成员明确提供初始化程序时这才有效。

```cpp
int main()
{
    int bad[] {}; // error: the compiler will deduce this to be a zero-length array, which is disallowed!

    return 0;
}
```

使用初始化列表初始化 C 样式数组的所有元素时，最好省略长度并让编译器计算数组的长度。这样，如果添加或删除初始化程序，数组的长度将自动调整，并且我们不会面临定义的数组长度与提供的初始化程序数量不匹配的风险。

**最佳实践**

**当用值明确初始化每个数组元素时，最好省略 C 样式数组的长度。**

## Const 和 constexpr C 样式数组

就像 一样`std::array`，C 风格数组可以是`const`或`constexpr`。与其他 const 变量一样，const 数组必须初始化，并且之后不能更改元素的值。

```cpp
#include <iostream>

namespace ProgramData
{
    constexpr int squares[5] { 1, 4, 9, 16, 25 }; // an array of constexpr int
}

int main()
{
    const int prime[5] { 2, 3, 5, 7, 11 }; // an array of const int
    prime[0] = 17; // compile error: can't change const int

    return 0;
}
```

## C 风格数组的大小

在之前的课程中，我们使用`sizeof()`运算符来获取对象或类型的大小（以字节为单位）。应用于 C 样式数组，`sizeof()`返回整个数组使用的字节数：

```cpp
#include <iostream>

int main()
{
    const int prime[] { 2, 3, 5, 7, 11 }; // the compiler will deduce prime to have length 5

    std::cout << sizeof(prime); // prints 20 (assuming 4 byte ints)

    return 0;
}
```

假设整数为 4 字节，上述程序将打印`20`。该`prime`数组包含 5 个`int`元素，每个元素为 4 字节，因此 5 * 4 = 20 字节。

请注意，这里没有任何开销。C 样式数组对象仅包含其元素，不包含任何其他内容。

## 获取 C 样式数组的长度

在 C++17 中，我们可以使用`std::size()`(在 <iterator> 标头中定义)，它将数组长度作为无符号整数值 (类型`std::size_t`) 返回。在 C++20 中，我们还可以使用`std::ssize()`，它将数组长度作为有符号整数值 (可能是大的有符号整数类型`std::ptrdiff_t`) 返回。

```cpp
#include <iostream>
#include <iterator> // for std::size and std::ssize

int main()
{
    const int prime[] { 2, 3, 5, 7, 11 };   // the compiler will deduce prime to have length 5

    std::cout << std::size(prime) << '\n';  // C++17, returns unsigned integral value 5
    std::cout << std::ssize(prime) << '\n'; // C++20, returns signed integral value 5

    return 0;
}
```

**提示**

**`std::size()`和定义的标准标头`std::ssize()`是 <iterator>。但是，由于这些函数非常有用，许多其他标头也使它们可用，包括 <array> 和 <vector>。在 C 样式数组上使用`std::size()`或时`std::ssize()`，我们可能尚未包含其他标头之一。在这种情况下，<iterator> 标头是常规包含的标头。**

**[您可以在cppreference 文档中查看定义这些函数的大小函数](https://en.cppreference.com/w/cpp/iterator/size)的完整标头列表。**

## 获取 C 样式数组的长度（C++14 或更早版本）

在 C++17 之前，没有标准库函数可以获取 C 风格数组的长度。

如果您使用的是 C++11 或 C++14，则可以改用此函数：

```cpp
#include <cstddef> // for std::size_t
#include <iostream>

template <typename T, std::size_t N>
constexpr std::size_t length(const T(&)[N]) noexcept
{
	return N;
}

int main() {

	int array[]{ 1, 1, 2, 3, 5, 8, 13, 21 };
	std::cout << "The array has: " << length(array) << " elements\n";

	return 0;
}
```

它使用一个函数模板，该模板通过引用获取 C 样式数组，然后返回表示数组长度的非类型模板参数。

在更老的代码库中，你可能会看到 C 样式数组的长度是通过将整个数组的大小除以数组元素的大小来确定的：

```cpp
#include <iostream>

int main()
{
    int array[8] {};
    std::cout << "The array has: " << sizeof(array) / sizeof(array[0]) << " elements\n";

    return 0;
}
```

这将打印：

```
该数组有：8 个元素
```

这是如何实现的？首先，请注意，整个数组的大小等于数组的长度乘以元素的大小。更简洁地说：`array size = length * element size`。

使用代数，我们可以重新排列这个等式：`length = array size / element size`。我们通常用`sizeof(array[0])`表示元素大小。因此，长度 = `sizeof(array) / sizeof(array[0])`。您可能偶尔会看到它写成`sizeof(array) / sizeof(*array)`，它的作用相同。

但是，正如我们将在下一课中向您展示的那样，此公式很容易失败（传递衰减数组时），导致程序意外损坏。在这种情况下，C++17`std::size()`和`length()`上面显示的函数模板都会导致编译错误，因此可以安全使用它们。

相关内容

我们将在下一课[17.8——C 风格数组衰减](https://www.learncpp.com/cpp-tutorial/c-style-array-decay/)中介绍**数组衰减。**

## C 风格数组不支持赋值

也许令人惊讶的是，C++ 数组不支持赋值：

```cpp
int main()
{
    int arr[] { 1, 2, 3 }; // okay: initialization is fine
    arr[0] = 4;            // assignment to individual elements is fine
    arr = { 5, 6, 7 };     // compile error: array assignment not valid

    return 0;
}
```

从技术上讲，这是行不通的，因为赋值要求左操作数是可修改的左值，而 C 样式数组不被视为可修改的左值。

如果您需要将新的值列表分配给 C 样式数组，最好改用`std::vector`。或者，您可以逐个元素地将新值分配给 C 样式数组，或使用`std::copy`复制现有的 C 样式数组：

```cpp
#include <algorithm> // for std::copy

int main()
{
    int arr[] { 1, 2, 3 };
    int src[] { 5, 6, 7 };

    // Copy src into arr
    std::copy(std::begin(src), std::end(src), std::begin(arr));

    return 0;
}
```

## 测验时间

### 问题 #1

将以下`std::array`定义转换为等效的 constexpr C 样式数组定义：

```cpp
constexpr std::array<int, 3> a{}; // allocate 3 ints
```

```cpp
constexpr int a[3] {}; // allocate 3 ints
```

### 问题 #2

以下程序有哪三处错误？

```cpp
#include <iostream>

int main()
{
    int length{ 5 };
    const int arr[length] { 9, 7, 5, 3, 1 };

    std::cout << arr[length];
    arr[0] = 4;

    return 0;
}
```

1. 定义数组时，长度必须是编译时常量。在上面的程序中，是 non-const，因此不允许`length`定义。`const int arr[length]`
2. 数组的索引从 0 到 length-1。因此，`arr[length]`是越界索引，并将导致未定义的行为。
3. 数组元素的类型为“const int”，因此`arr[0]`不能通过赋值来修改

### 问题 #3

“完全平方数”是指平方根为整数的自然数。我们可以通过将自然数（包括零）乘以自身来得到完全平方数。前 4 个完全平方数为：0、1、4、9。

使用全局 constexpr C 样式数组保存 0 到 9（含）之间的完全平方数。反复要求用户输入一位整数，或输入 -1 退出。打印用户输入的数字是否为完全平方数。

输出应与以下内容匹配：

```
Enter a single digit integer, or -1 to quit: 4
4 is a perfect square

Enter a single digit integer, or -1 to quit: 5
5 is not a perfect square

Enter a single digit integer, or -1 to quit: -1
Bye
```

```cpp
#include <iostream>

namespace ProgramData
{
    constexpr int squares[] { 0, 1, 4, 9 };
}

bool matchSquare(int input)
{
    for (const auto& e : ProgramData::squares)
    {
        if (input == e)
            return true;
    }

    return false;
}

int main()
{
    while (true)
    {
        std::cout << "Enter a single digit integer, or -1 to quit: ";
        int input{};
        std::cin >> input;

        if (input == -1)
            break;

        if (matchSquare(input))
            std::cout << input << " is a perfect square\n";
        else
            std::cout << input << " is not a perfect square\n";
    }

    std::cout << "Bye\n";

    return 0;
}
```

# 17.8 — C 风格数组衰减

## C 风格数组传递挑战

C 语言的设计者遇到了一个问题。请考虑以下简单程序：

```cpp
#include <iostream>

void print(int val)
{
    std::cout << val;
}

int main()
{
    int x { 5 };
    print(x);

    return 0;
}
```

当`print(x)`被调用时，参数`x(5)`的值被复制到参数( `val`) 中。在函数主体中，`val( 5)` 的值被打印到控制台。由于`x`复制过程简单，因此这里没有问题。

现在考虑以下类似的程序，它使用 1000 个元素的 C 样式 int 数组而不是单个 int：

```cpp
#include <iostream>

void printElementZero(int arr[1000])
{
    std::cout << arr[0]; // print the value of the first element
}

int main()
{
    int x[1000] { 5 };   // define an array with 1000 elements, x[0] is initialized to 5
    printElementZero(x);

    return 0;
}
```

该程序还编译并将预期值（`5`）打印到控制台。

虽然本例中的代码与前一个示例中的代码类似，但其机械工作原理可能与您预期的略有不同（我们将在下文中解释这一点）。这是由于 C 语言设计者想出了解决两个主要挑战的解决方案。

首先，每次调用函数时复制 1000 个元素的数组是昂贵的（如果元素是复制成本高昂的类型，则更是如此），因此我们希望避免这种情况。但该怎么做呢？C 没有引用，因此使用传递引用来避免复制函数参数不是一个选择。

其次，我们希望能够编写一个可以接受不同长度数组参数的函数。理想情况下，`printElementZero()`上面示例中的函数应该可以使用任意长度的数组参数来调用（因为元素 0 肯定存在）。我们不想为想要用作参数的每种可能的数组长度编写不同的函数。但该怎么做呢？C 没有指定“任意长度”数组的语法，也不支持模板，也不能将一种长度的数组转换为另一种长度的数组（大概是因为这样做会涉及进行昂贵的复制）。

C 语言的设计者想出了一个巧妙的解决方案（出于兼容性原因，C++ 继承了这一解决方案），解决了这两个问题：

```cpp
#include <iostream>

void printElementZero(int arr[1000]) // doesn't make a copy
{
    std::cout << arr[0]; // print the value of the first element
}

int main()
{
    int x[7] { 5 };      // define an array with 7 elements
    printElementZero(x); // somehow works!

    return 0;
}
```

不知何故，上面的示例将一个包含 7 个元素的数组传递给一个需要包含 1000 个元素的数组的函数，而没有进行任何复制。在本课中，我们将探索其工作原理。

我们还将了解为什么 C 设计人员选择的解决方案是危险的，并且不适合在现代 C++ 中使用。

但首先，我们需要讨论两个子主题。

## 数组到指针的转换（数组衰减）

在大多数情况下，当在表达式中使用 C 样式数组时，该数组将被隐式转换为指向元素类型的指针，并使用第一个元素的地址（索引为 0）进行初始化。通俗地说，这称为**数组衰减**（或简称为**衰减**）。

您可以在以下程序中看到这一点：

```cpp
#include <iomanip> // for std::boolalpha
#include <iostream>

int main()
{
    int arr[5]{ 9, 7, 5, 3, 1 }; // our array has elements of type int

    // First, let's prove that arr decays into an int* pointer

    auto ptr{ arr }; // evaluation causes arr to decay, type deduction should deduce type int*
    std::cout << std::boolalpha << (typeid(ptr) == typeid(int*)) << '\n'; // Prints true if the type of ptr is int*

    // Now let's prove that the pointer holds the address of the first element of the array

    std::cout << std::boolalpha << (&arr[0] == ptr) << '\n';

    return 0;
}
```

在作者的机器上打印了以下内容：

```
真的
真的
```

数组退化后的指针并没有什么特别之处，它是一个普通的指针，保存着第一个元素的地址。

类似地，const 数组（例如`const int arr[5]`）衰减为指向 const 的指针（`const int*`）。

**提示**

**在 C++ 中，有几种常见的情况 C 风格数组不会衰减：**

1. **`sizeof()`当用作或 的参数时`typeid()`。**
2. **当使用获取数组地址时`operator&`。**
3. **当作为类类型的成员传递时。**
4. **当通过引用传递时。**

由于 C 风格数组在大多数情况下会退化为指针，因此认为数组*就是*指针是一种常见的谬论。事实并非如此。数组对象是元素序列，而指针对象仅保存地址。

数组和衰减数组的类型信息不同。在上面的例子中，数组`arr`的类型为`int[5]`，而衰减数组的类型为`int*`。值得注意的是，数组类型`int[5]`包含长度信息，而衰减数组指针类型`int*`不包含。

**关键见解**

**衰减的数组指针不知道它指向的数组有多长。术语“衰减”表示长度类型信息的丢失。**

## 对 C 风格数组进行下标实际上适用`operator[]`于衰减指针

因为 C 风格数组在求值时会衰减为指针，所以当 C 风格数组被加下标时，下标实际上是在衰减的数组指针上进行操作：

```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 7, 5, 3, 1 };
    std::cout << arr[2]; // subscript decayed array to get element 2, prints 5

    return 0;
}
```

我们也可以直接在指针上使用`operator[]`。如果该指针保存的是第一个元素的地址，则结果将相同：

```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 7, 5, 3, 1 };

    const int* ptr{ arr };  // arr decays into a pointer
    std::cout << ptr[2];    // subscript ptr to get element 2, prints 5

    return 0;
}
```

我们马上就会看到这种方法的便利之处，并在下一课[17.9 -- 指针运算和下标](https://www.learncpp.com/cpp-tutorial/pointer-arithmetic-and-subscripting/)中更深入地了解它实际上是如何工作的（以及当指针保存的不是第一个元素的地址时会发生什么） 。

## 数组衰减解决了我们的 C 风格数组传递问题

数组衰减解决了我们在课程顶部遇到的两个挑战。

当将 C 样式数组作为参数传递时，数组会退化为指针，而保存数组第一个元素地址的指针会传递给函数。因此，尽管我们看起来像是通过值传递 C 样式数组，但实际上是通过地址传递！这就是避免复制 C 样式数组参数的方法。

**关键见解**

**C 样式数组通过地址传递，即使它看起来像是通过值传递的。**

现在考虑两个元素类型相同但长度不同的数组（例如`int[5]`和`int[7]`）。它们是不同的类型，彼此不兼容。但是，它们都会衰减为相同的指针类型（例如`int*`）。它们的衰减版本是可以互换的！从类型中删除长度信息使我们能够传递不同长度的数组而不会出现类型不匹配的情况。

**关键见解**

**两个具有相同元素类型但不同长度的 C 风格数组将衰减为相同的指针类型。**

在下面的例子中，我们将说明两件事：

- 我们可以将不同长度的数组传递给单个函数（因为两者都衰减为相同的指针类型）。
- 我们接收数组的函数参数可以是数组元素类型的（const）指针。

```cpp
#include <iostream>

void printElementZero(const int* arr) // pass by const address
{
    std::cout << arr[0];
}

int main()
{
    const int prime[] { 2, 3, 5, 7, 11 };
    const int squares[] { 1, 4, 9, 25, 36, 49, 64, 81 };

    printElementZero(prime);   // prime decays to an const int* pointer
    printElementZero(squares); // squares decays to an const int* pointer

    return 0;
}
```

这个例子运行良好，并打印：

```
2
1
```

在 中`main()`，当我们调用 时`printElementZero(prime)`，`prime`数组从 类型数组退化`const int[5]`为 类型指针，该指针`const int*`保存 的第一个元素的地址`prime`。类似地，当我们调用 时`printElementZero(squares)`，`squares`从 类型数组退化为 类型指针，该指针保存 的第一个元素的地址。这些 类型指针实际上是作为参数传递给函数的。`const int[8]``const int*``squares``const int*`

因为我们传递的是类型的指针`const int*`，所以我们的`printElementZero()`函数需要有一个相同指针类型的参数（`const int*`）。

在这个函数中，我们对指针进行下标以访问所选的数组元素。

由于 C 样式数组是通过地址传递的，因此函数可以直接访问传入的数组（而不是副本），并且可以修改其元素。因此，如果函数不打算修改数组元素，最好确保函数参数为 const。

## C 风格数组函数参数语法

将函数参数声明为 的一个问题`int* arr`是，它不明显`arr`应该是指向值数组的指针，而不是指向单个整数的指针。因此，在传递 C 样式数组时，最好使用替代声明形式`int arr[]`：

```cpp
#include <iostream>

void printElementZero(const int arr[]) // treated the same as const int*
{
    std::cout << arr[0];
}

int main()
{
    const int prime[] { 2, 3, 5, 7, 11 };
    const int squares[] { 1, 4, 9, 25, 36, 49, 64, 81 };

    printElementZero(prime);  // prime decays to a pointer
    printElementZero(squares); // squares decays to a pointer

    return 0;
}
```

此程序的行为与前一个程序相同，因为编译器将把函数参数解释`const int arr[]`为`const int*`。但是，这样做的好处是可以向调用者传达`arr`预期为衰减的 C 样式数组，而不是指向单个值的指针。请注意，方括号之间不需要长度信息（因为它反正用不到）。如果提供了长度，它将被忽略。

**最佳实践**

**期望 C 样式数组类型的函数参数应该使用数组语法（例如`int arr[]`）而不是指针语法（例如`int *arr`）。**

使用这种语法的缺点是它使衰减不太明显`arr`（而使用指针语法则非常清楚），因此您需要格外小心，不要对衰减数组执行任何不能按预期工作的操作（我们稍后会介绍其中的一些）。

## array衰减的问题

尽管数组衰减是一个聪明的解决方案，可以确保不同长度的 C 风格数组可以传递给函数而无需进行昂贵的复制，但数组长度信息的丢失很容易导致几种类型的错误。

首先，`sizeof()`将对数组和衰减数组返回不同的值：

```cpp
#include <iostream>

void printArraySize(int arr[])
{
    std::cout << sizeof(arr) << '\n'; // prints 4 (assuming 32-bit addresses)
}

int main()
{
    int arr[]{ 3, 2, 1 };

    std::cout << sizeof(arr) << '\n'; // prints 12 (assuming 4 byte ints)

    printArraySize(arr);

    return 0;
}
```

这意味着在 C 样式数组上使用`sizeof()`具有潜在危险，因为您必须确保仅在可以访问实际数组对象而不是衰减数组或指针时使用它。

在上一课（[17.7--C 风格数组简介](https://www.learncpp.com/cpp-tutorial/introduction-to-c-style-arrays/)）中，我们提到，`sizeof(arr)/sizeof(*arr)`过去曾使用 来获取 C 风格数组的大小。这种技巧很危险，因为如果`arr`已衰减，`sizeof(arr)`将返回指针的大小而不是数组的大小，从而产生错误的数组长度，可能会导致程序出现故障。

幸运的是，如果传递了指针值，C++17 的更好的替代品`std::size()`（和 C++20 的`std::ssize()`）将编译失败：

```cpp
#include <iostream>

int printArrayLength(int arr[])
{
    std::cout << std::size(arr) << '\n'; // compile error: std::size() won't work on a pointer
}

int main()
{
    int arr[]{ 3, 2, 1 };

    std::cout << std::size(arr) << '\n'; // prints 3

    printArrayLength(arr);

    return 0;
}
```

其次，也许最重要的是，数组衰减会使重构（将长函数分解为更短、更模块化的函数）变得困难。使用非衰减数组按预期运行的代码可能无法编译（或更糟的是，可能会默默发生故障），而相同的代码使用衰减数组时则无法编译。

第三，没有长度信息会带来一些编程挑战。没有长度信息，对数组长度进行合理性检查就不同了。用户很容易传入比预期短的数组（甚至是指向单个值的指针），当使用无效索引对其进行下标时，这将导致未定义的行为。

```cpp
#include <iostream>

void printElement2(int arr[])
{
    // How do we ensure that arr has at least three elements?
    std::cout << arr[2] << '\n';
}

int main()
{
    int a[]{ 3, 2, 1 };
    printElement2(a);  // ok

    int b[]{ 7, 6 };
    printElement2(b);  // compiles but produces undefined behavior

    int c{ 9 };
    printElement2(&c); // compiles but produces undefined behavior

    return 0;
}
```

没有数组长度也会给遍历数组带来困难——我们如何知道何时到达末尾？

这些问题有解决方案，但这些解决方案增加了程序的复杂性和脆弱性。

### 解决数组长度问题

从历史上看，程序员通过以下两种方法之一解决缺少数组长度信息的问题。

首先，我们可以将数组和数组长度作为单独的参数传递：

```cpp
#include <cassert>
#include <iostream>

void printElement2(const int arr[], int length)
{
    assert(length > 2 && "printElement2: Array too short"); // can't static_assert on length

    std::cout << arr[2] << '\n';
}

int main()
{
    constexpr int a[]{ 3, 2, 1 };
    printElement2(a, static_cast<int>(std::size(a)));  // ok

    constexpr int b[]{ 7, 6 };
    printElement2(b, static_cast<int>(std::size(b)));  // will trigger assert

    return 0;
}
```

但这仍然存在一些问题：

- 调用者需要确保数组和数组长度是配对的——如果传入了错误的长度值，函数仍然会出现故障。
- `std::size()`如果您使用或返回长度的函数，则可能存在符号转换问题`std::size_t`。
- 运行时断言仅在运行时遇到时触发。如果我们的测试路径没有涵盖对函数的所有调用，则存在将程序交付给客户的风险，当他们执行我们未明确测试的某些操作时，该程序将断言。在现代 C++ 中，我们希望使用它`static_assert`来对 constexpr 数组的数组长度进行编译时验证，但没有简单的方法可以做到这一点（因为函数参数不能是 constexpr，即使在 constexpr 或 consteval 函数中也是如此！）。
- 该方法仅在我们进行显式函数调用时才有效。如果函数调用是隐式的（例如，我们调用以数组为操作数的运算符），则没有机会传递长度。

其次，如果元素值在语义上无效（例如测试分数为`-1`），我们可以使用该值的元素标记数组的末尾。这样，可以通过计算数组开头和终止元素之间存在的元素数来计算数组的长度。也可以通过从开头迭代直到到达终止元素来遍历数组。这种方法的好处在于它甚至可以使用隐式函数调用。

**关键见解**

**C 风格字符串（即 C 风格数组）使用空终止符来标记字符串的结束，这样即使它们已经衰减，也可以遍历它们。**

但这种方法也存在一些问题：

- 如果终止元素不存在，遍历将直接到达数组的末尾，从而导致未定义的行为。
- 遍历数组的函数需要对终止元素进行特殊处理（例如，C 样式字符串打印函数需要知道不要打印终止元素）。
- 实际数组长度与语义上有效的元素数量不匹配。如果使用了错误的长度，语义上无效的终止元素可能会被“处理”。
- 这种方法仅当存在语义无效的值时才有效，但情况通常并非如此。

大多数情况下应避免使用 C 风格数组

由于传递语义不标准（使用按地址传递而不是按值传递）以及与数组衰减丢失其长度信息相关的风险，C 风格数组通常已不再受欢迎。我们建议尽可能避免使用它们。

**最佳实践**

**尽可能避免使用 C 风格的数组。**

- **优先`std::string_view`适用于只读字符串（字符串文字符号常量和字符串参数）。**
- **优先选择`std::string`可修改的字符串。**
- **优先考虑`std::array`非全局 constexpr 数组。**
- **优先考虑`std::vector`非 constexpr 数组。**

**对于全局 constexpr 数组，可以使用 C 样式数组。我们稍后会讨论这个问题。**

**顺便说一下……**

**在 C++ 中，数组可以通过引用传递，在这种情况下，数组参数在传递给函数时不会衰减（但在评估时对数组的引用仍会衰减）。但是，很容易忘记始终如一地应用这一点，一次错过的引用就会导致参数衰减。此外，数组引用参数必须具有固定长度，这意味着该函数只能处理特定长度的数组。如果我们想要一个可以处理不同长度数组的函数，那么我们还必须使用函数模板。但如果您要同时做这两件事来“修复” C 风格的数组，那么您不妨只使用`std::array`！**

## 那么在现代 C++ 中何时使用 C 风格数组？

在现代 C++ 中，C 样式数组通常在两种情况下使用：

1. 存储 constexpr 全局（或 constexpr 静态局部）程序数据。由于此类数组可从程序中的任何位置直接访问，因此我们无需传递数组，从而避免了与衰减相关的问题。定义 C 样式数组的语法可能比 稍微不那么复杂`std::array`。更重要的是，索引此类数组不会像标准库容器类那样存在符号转换问题。
2. 作为要直接处理非 constexpr C 样式字符串参数的函数或类的参数（而不是要求转换为`std::string_view`）。这可能有两个原因：首先，将非 constexpr C 样式字符串转换为`std::string_view`需要遍历 C 样式字符串以确定其长度。如果函数位于代码的性能关键部分并且不需要长度（例如，因为函数无论如何都会遍历字符串），则避免转换可能会很有用。其次，如果函数（或类）调用需要 C 样式字符串的其他函数，则转换为`std::string_view`然后再转换回来可能不是最佳选择（除非您有其他原因想要`std::string_view`）。

## 测验时间

### 问题 #1

什么是阵列衰减？为什么它是一个问题？

当评估 C 样式数组时，在大多数情况下它将被隐式转换为指向数组元素类型的指针。

衰减的数组会丢失其长度信息，这使得与长度相关的错误更容易引入到程序中

## 问题 #2

为什么 C 风格字符串（即 C 风格数组）使用空终止符？

将 C 样式数组传递给函数时，它会衰减并丢失其长度信息。如果 C 样式字符串没有空终止符，则函数将无法确定字符串的长度。

## 问题 #3

为什么 C 风格字符串使用空终止符，而不是要求将衰减的 C 风格字符串和明确的长度信息传递给函数？

这个问题可能有很多答案，但以下是其中一些：

- 人体工程学会很糟糕，因为我们到处都会有额外的参数和神奇的数字（例如`printString("Hello", 5)`）。
- 字符串和提供的字符串长度很容易不匹配。字符串长度本质上是字符串本身的不变量。依赖用户来维护这个不变量必然会导致错误（例如`printString("Hello", 6)`）。

即使 C++ 想要实现传递明确的长度信息，为什么它不起作用呢？

仅当显式调用函数时才可以传递 C 样式字符串和显式长度信息。如果隐式调用函数，则无法传递长度信息。

考虑这样的语句`std::cout << cstr`。二进制`operator<<`只能采用两个操作数：`std::cout`和`cstr`。没有办法传递另一个表示长度信息的参数。空终止符方法没有这个问题。

# 17.9 — 指针运算和下标

在第 16.1 课[——容器和数组简介](https://www.learncpp.com/cpp-tutorial/introduction-to-containers-and-arrays/)中，我们提到数组在内存中按顺序存储。在本课中，我们将深入了解数组索引数学的工作原理。

虽然我们不会在未来的课程中使用索引数学，但本课中涵盖的主题将让您深入了解基于范围的 for 循环的实际工作方式，并且在我们介绍迭代器时将再次派上用场。

## 什么是指针运算？

**指针算术**是一项功能，它允许我们将某些整数算术运算符（加、减、增量或减量）应用于指针以产生新的内存地址。

给定某个指针`ptr`，返回内存中下*一个对象*`ptr + 1`的地址（基于指向的类型）。因此，如果是，并且是 4 个字节，则将返回 之后 4 个字节的内存地址，并将返回 之后 8 个字节的内存地址。`ptr``int*``int``ptr + 1``ptr``ptr + 2``ptr`

```cpp
#include <iostream>

int main()
{
    int x {};
    const int* ptr{ &x }; // assume 4 byte ints

    std::cout << ptr << ' ' << (ptr + 1) << ' ' << (ptr + 2) << '\n';

    return 0;
}
```

在作者的机器上打印了以下内容：

```
00AFFD80 00AFFD84 00AFFD88
```

请注意，每个内存地址都比前一个大 4 个字节。

虽然不太常见，但指针算法也适用于减法。给定某个指针`ptr`，返回内存中*前*`ptr - 1`一个对象的地址（基于指向的类型）。

```cpp
#include <iostream>

int main()
{
    int x {};
    const int* ptr{ &x }; // assume 4 byte ints

    std::cout << ptr << ' ' << (ptr - 1) << ' ' << (ptr - 2) << '\n';

    return 0;
}
```

在作者的机器上打印了以下内容：

```
00AFFD80 00AFFD7C 00AFFD78
```

在这种情况下，每个内存地址都比前一个少 4 个字节。

**关键见解**

**指针运算返回下一个/上一个对象的地址（基于指向的类型），而不是下一个/上一个地址。**

对指针应用增量（`++`）和减量（`--`）运算符分别与指针加法和指针减法执行相同的操作，但实际上修改的是指针保存的地址。

给定某个 int 值`x`，`++x`是 的简写`x = x + 1`。类似地，给定某个指针`ptr`，`++ptr`是 的简写`ptr = ptr + 1`，它执行指针运算并将结果赋回`ptr`。

```cpp
#include <iostream>

int main()
{
    int x {};
    const int* ptr{ &x }; // assume 4 byte ints

    std::cout << ptr << '\n';

    ++ptr; // ptr = ptr + 1
    std::cout << ptr << '\n';

    --ptr; // ptr = ptr - 1
    std::cout << ptr << '\n';

    return 0;
}
```

在作者的机器上打印了以下内容：

```
00AFFD80 00AFFD84 00AFFD80
```

**警告**

**从技术上讲，上述行为是未定义的行为。根据 C++ 标准，[只有当指针和结果位于同一数组（或末尾后一个）内时，指针运算才是定义的行为](https://eel.is/c++draft/expr.add#4)。但是，现代 C++ 实现通常不强制执行这一点，并且通常不会禁止您在数组之外使用指针运算。**

## 下标是通过指针算法实现的

在上一课 ( [17.8 -- C 风格数组衰减](https://www.learncpp.com/cpp-tutorial/c-style-array-decay/)) 中，我们注意到`operator[]`可以应用于指针：

```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 7, 5, 3, 1 };

    const int* ptr{ arr }; // a normal pointer holding the address of element 0
    std::cout << ptr[2];   // subscript ptr to get element 2, prints 5

    return 0;
}
```

让我们深入了解一下这里发生的事情。

事实证明，下标运算`ptr[n]`是一种简洁的语法，相当于更详细的表达式`*((ptr) + (n))`。您会注意到，这只是指针算法，带有一些额外的括号以确保事物以正确的顺序进行评估，以及隐式取消引用以获取该地址处的对象。

首先，我们`ptr`用进行初始化`arr`。当`arr`用作初始化器时，它会衰减为一个指针，该指针保存索引为 0 的元素的地址。所以`ptr`现在保存元素 0 的地址。

接下来，我们打印`ptr[2]`。`ptr[2]`相当于`*((ptr) + (2))`，相当于`*(ptr + 2)`。`ptr + 2`返回距离两个对象较远的对象的地址`ptr`，即索引为 2 的元素。然后将该地址处的对象返回给调用者。

我们来看另一个例子：

```cpp
#include <iostream>

int main()
{
    const int arr[] { 3, 2, 1 };

    // First, let's use subscripting to get the address and values of our array elements
    std::cout << &arr[0] << ' ' << &arr[1] << ' ' << &arr[2] << '\n';
    std::cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << '\n';

    // Now let's do the equivalent using pointer arithmetic
    std::cout << arr<< ' ' << (arr+ 1) << ' ' << (arr+ 2) << '\n';
    std::cout << *arr<< ' ' << *(arr+ 1) << ' ' << *(arr+ 2) << '\n';

    return 0;
}
```

在作者的机器上打印了以下内容：

```
00AFFD80 00AFFD84 00AFFD88
3 2 1
00AFFD80 00AFFD84 00AFFD88
3 2 1
```

您会注意到，它`arr`保存的是地址`00AFFD80`，`(arr + 1)`返回 4 个字节后的地址，并`(arr + 2)`返回 8 个字节后的地址。我们可以取消引用这些地址以获取这些地址处的元素。

因为数组元素在内存中总是连续的，所以如果`arr`是指向数组元素 0 的指针，`*(arr + n)`将返回数组中的第 n 个元素。

这是数组以 0 为基数而不是以 1 为基数的主要原因。它使数学运算更加高效（因为编译器不必在下标时减去 1）！

顺便说一下……

有趣的是，由于编译器在对指针进行下标时会将`ptr[n]`其转换``*((ptr) + (n))``，这意味着我们也可以将指针下标为`n[ptr]`！编译器将其转换为`*((n) + (ptr))`，其行为与 `*((ptr) + (n))`相同。但实际上不要这样做，因为它会造成混淆。``

## 指针运算和下标都是相对地址

第一次学习数组下标时，很自然地会认为索引代表数组内的固定元素：索引 0 始终是第一个元素，索引 1 始终是第二个元素，等等……

这是一种错觉。数组索引实际上是相对位置。索引看起来是固定的，因为我们几乎总是从数组的开头（元素 0）开始索引！

请记住，给定某个指针`ptr`，`*(ptr + 1)`和`ptr[1]`都会返回内存中的*下一个对象*（基于指向的类型）。下一个是相对的，而不是绝对的。因此，如果`ptr`指向元素 0，则`*(ptr + 1)`和`ptr[1]`都会返回元素 1。但如果`ptr`指向元素 3，则`*(ptr + 1)`和`ptr[1]`都会返回元素 4！

下面的例子证明了这一点：

```cpp
#include <array>
#include <iostream>

int main()
{
    const int arr[] { 9, 8, 7, 6, 5 };
    const int *ptr { arr }; // arr decays into a pointer to element 0

    // Prove that we're pointing at element 0
    std::cout << *ptr << ptr[0] << '\n'; // prints 99
    // Prove that ptr[1] is element 1
    std::cout << *(ptr+1) << ptr[1] << '\n'; // prints 88

    // Now set ptr to point at element 3
    ptr = &arr[3];

    // Prove that we're pointing at element 3
    std::cout << *ptr << ptr[0] << '\n'; // prints 66
    // Prove that ptr[1] is element 4!
    std::cout << *(ptr+1) << ptr[1] << '\n'; // prints 55

    return 0;
}
```

但是，您还会注意到，如果我们不能假设它始终是索引为 1 的元素，我们的程序会更加混乱。`ptr[1]`因此，我们建议仅在从数组开头（元素 0）进行索引时使用下标。仅在进行相对定位时使用指针算法。

**最佳实践**

**从数组的开头（元素 0）进行索引时支持下标，以便数组索引与元素对齐。**

**当从给定元素进行相对定位时，优先使用指针算法。**

## 负索引

在上一课中，我们提到（与标准库容器类不同）C 样式数组的索引可以是无符号整数，也可以是带符号整数。这样做不只是为了方便——实际上可以使用负下标来索引 C 样式数组。这听起来很有趣，但很有道理。

我们刚刚介绍了`*(ptr+1)`返回内存中的*下一个对象*。这`ptr[1]`只是执行相同操作的便捷语法。

在本课的开头，我们注意到`*(ptr-1)`返回内存中的*前一个对象*。想猜猜下标等价是什么吗？没错，`ptr[-1]`。

```cpp
#include <array>
#include <iostream>

int main()
{
    const int arr[] { 9, 8, 7, 6, 5 };

    // Set ptr to point at element 3
    const int* ptr { &arr[3] };

    // Prove that we're pointing at element 3
    std::cout << *ptr << ptr[0] << '\n'; // prints 66
    // Prove that ptr[-1] is element 2!
    std::cout << *(ptr-1) << ptr[-1] << '\n'; // prints 77

    return 0;
}
```

## 指针运算可用于遍历数组

指针算法最常见的用途之一是在不显式索引的情况下迭代 C 样式数组。以下示例说明了如何执行此操作：

```cpp
#include <iostream>

int main()
{
	constexpr int arr[]{ 9, 7, 5, 3, 1 };

	const int* begin{ arr };                // begin points to start element
	const int* end{ arr + std::size(arr) }; // end points to one-past-the-end element

	for (; begin != end; ++begin)           // iterate from begin up to (but excluding) end
	{
		std::cout << *begin << ' ';     // dereference our loop variable to get the current element
	}

	return 0;
}
```

在上面的例子中，我们从 指向的元素开始遍历`begin`（在本例中是数组的元素 0）。由于`begin != end`，循环体执行。在循环内部，我们通过 访问当前元素`*begin`，这只是一个指针取消引用。在循环体之后，我们执行`++begin`，它使用指针算法来递增`begin`以指向下一个元素。由于`begin != end`，循环体再次执行。这一直持续到，`begin != end`当`false`时就会发生这种情况`begin == end`。

因此，上面的打印结果为：

```
9 7 5 3 1
```

请注意，`end`设置为数组末尾的后一位。保留`end`此地址是可以的（只要我们不取消引用`end`，因为该地址没有有效元素）。我们这样做是因为它使我们的数学和比较尽可能简单（无需在任何地方加 1 或减 1）。

**提示**

**对于指向 C 样式数组元素的指针，只要结果地址是有效数组元素的地址或最后一个元素的后一个地址，指针运算就是有效的。如果指针运算导致地址超出这些范围，则为未定义行为（即使结果未取消引用）。**

在之前的课程[17.8 -- C 风格数组衰减](https://www.learncpp.com/cpp-tutorial/c-style-array-decay/)中，我们提到数组衰减使重构函数变得困难，因为某些东西适用于非衰减数组，但不适用于衰减数组（如`std::size`）。以这种方式遍历数组的一个巧妙之处在于，我们可以将上述示例的循环部分重构为一个单独的函数，完全按照编写的方式，它仍然可以工作：

```cpp
#include <iostream>

void printArray(const int* begin, const int* end)
{
	for (; begin != end; ++begin)   // iterate from begin up to (but excluding) end
	{
		std::cout << *begin << ' '; // dereference our loop variable to get the current element
	}

	std::cout << '\n';
}

int main()
{
	constexpr int arr[]{ 9, 7, 5, 3, 1 };

	const int* begin{ arr };                // begin points to start element
	const int* end{ arr + std::size(arr) }; // end points to one-past-the-end element

	printArray(begin, end);

	return 0;
}
```

请注意，即使我们从未明确将数组传递给函数，此程序也会编译并产生正确的结果！而且因为我们没有传递`arr`，所以我们不必处理衰减`arr`。`printArray()`相反，`begin`和`end`包含遍历数组所需的所有信息。

`begin`在未来的课程中（当我们介绍迭代器和算法时），我们将看到标准库充满了使用和对来定义函数`end`应该对容器的哪些元素进行操作的函数。

## 使用指针算法实现 C 风格数组的基于范围的循环

考虑以下基于范围的 for 循环：

```cpp
#include <iostream>

int main()
{
	constexpr int arr[]{ 9, 7, 5, 3, 1 };

	for (auto e : arr)         // iterate from `begin` up to (but excluding) `end`
	{
		std::cout << e << ' '; // dereference our loop variable to get the current element
	}

	return 0;
}
```

如果您查看基于范围的 for 循环的[文档](https://en.cppreference.com/w/cpp/language/range-for)，您会发现它们通常是像这样实现的：

```
{
    自动 __begin = begin-expr;
    自动 __end = end-expr;

    对于（；__begin != __end；++__begin）
    {
        范围声明 = *__begin;
        循环语句；
    }
}
```

让我们用这个实现替换前面例子中基于范围的 for 循环：

```cpp
#include <iostream>

int main()
{
	constexpr int arr[]{ 9, 7, 5, 3, 1 };

	auto __begin = arr;                // arr is our begin-expr
	auto __end = arr + std::size(arr); // arr + std::size(arr) is our end-expr

	for ( ; __begin != __end; ++__begin)
	{
		auto e = *__begin;         // e is our range-declaration
		std::cout << e << ' ';     // here is our loop-statement
	}

	return 0;
}
```



注意，这与我们在上一节中写的示例多么相似！唯一的区别是我们分配`*__begin`并`e`使用，`e`而不是`*__begin`直接使用！

## 测验时间

### 问题 #1

a) 为什么`arr[0]`与 相同`*arr`？

`arr[0]`是 的简写`*((arr) + (0))`，等于`*(arr + 0)`，等于`*arr`。

# 17.10 — C 风格字符串

在第 17.7 课[— — C 风格数组介绍](https://www.learncpp.com/cpp-tutorial/introduction-to-c-style-arrays/)中，我们介绍了 C 风格数组，它允许我们定义一个连续的元素集合：

```cpp
int testScore[30] {}; // an array of 30 ints, indices 0 through 29
```

在课程[5.2 — 文字](https://www.learncpp.com/cpp-tutorial/literals/)中，我们将字符串定义为连续字符的集合（例如“Hello, world!”），并介绍了 C 风格的字符串文字。我们还注意到 C 风格的字符串文字“Hello, world!”具有类型`const char[14]`（13 个显式字符加上 1 个隐藏的空终止符）。

如果你之前没有把这些点联系起来，那么现在应该很明显了，C 风格的字符串只是元素类型为`char`或的C 风格的数组`const char`！

尽管 C 风格的字符串文字在我们的代码中可以使用，但 C 风格的字符串对象在现代 C++ 中已不再受欢迎，因为它们难以使用且危险（因为和`std::string`是`std::string_view`现代替代品）。无论如何，您仍可能在较旧的代码中遇到 C 风格字符串对象的使用，如果我们完全不介绍它们，那就太失职了。

因此，在本课中，我们将了解现代 C++ 中有关 C 样式字符串对象的最重要的点。

## 定义 C 风格字符串

要定义 C 样式的字符串变量，只需声明一个 C 样式的数组变量`char`(或`const char`/ `constexpr char`)：

```cpp
char str1[8]{};                    // an array of 8 char, indices 0 through 7

const char str2[]{ "string" };     // an array of 7 char, indices 0 through 6
constexpr char str3[] { "hello" }; // an array of 6 const char, indices 0 through 5
```

请记住，我们需要一个额外的字符作为隐式空终止符。

使用初始化器定义 C 样式字符串时，我们强烈建议省略数组长度，让编译器计算长度。这样，如果初始化器将来发生变化，您就不必记得更新长度，也不会有忘记添加额外元素来保存空终止符的风险。

## C 风格的字符串将会衰减

在课程[17.8 — C 样式数组衰减](https://www.learncpp.com/cpp-tutorial/c-style-array-decay/)中，我们讨论了在大多数情况下 C 样式数组如何衰减为指针。由于 C 样式字符串是 C 样式数组，因此它们会衰减 — C 样式字符串文字会衰减为`const char*`，而 C 样式字符串数组会衰减为 或`const char*`，`char*`具体取决于数组是否为 const。当 C 样式字符串衰减为指针时，字符串的长度（编码在类型信息中）会丢失。

长度信息的丢失是 C 风格字符串具有空终止符的原因。可以通过计算字符串开头和空终止符之间的元素数量（低效地）重新生成字符串的长度。

## 输出 C 风格字符串

输出 C 样式字符串时，`std::cout`输出字符直到遇到空终止符。此空终止符标记字符串的结尾，因此衰减的字符串（已丢失其长度信息）仍可打印。

```cpp
#include <iostream>

void print(char ptr[])
{
    std::cout << ptr << '\n'; // output string
}

int main()
{
    char str[]{ "string" };
    std::cout << str << '\n'; // outputs string

    print(str);

    return 0;
}
```

如果您尝试打印没有空终止符的字符串（例如，因为空终止符以某种方式被覆盖），则结果将是未定义的行为。在这种情况下，最有可能的结果是打印字符串中的所有字符，然后它将继续打印相邻内存槽中的所有内容（解释为一个字符），直到它碰巧碰到一个包含 0 的内存字节（这将被解释为空终止符）！

## 输入 C 风格字符串

考虑一下这种情况：我们要求用户随意掷骰子，并输入掷出的数字（不带空格）（例如`524412616`）。用户将输入多少个字符？我们不知道。

因为 C 风格的字符串是固定大小的数组，所以解决方案是声明一个比我们可能需要的更大的数组：

```cpp
#include <iostream>

int main()
{
    char rolls[255] {}; // declare array large enough to hold 254 characters + null terminator
    std::cout << "Enter your rolls: ";
    std::cin >> rolls;
    std::cout << "You entered: " << rolls << '\n';

    return 0;
}
```

在 C++20 之前，`std::cin >> rolls`会提取尽可能多的字符`rolls`（在第一个非前导空格处停止）。没有什么可以阻止用户输入超过 254 个字符（无论是无意还是恶意）。如果发生这种情况，用户的输入将溢出数组`rolls`并导致未定义的行为。

**关键见解**

**数组溢出或缓冲区溢出是一种计算机安全问题，当复制到存储中的数据量超过存储容量时就会发生这种情况。在这种情况下，存储之外的内存将被覆盖，从而导致未定义的行为。恶意行为者可能会利用此类漏洞覆盖内存内容，希望以某种有利的方式改变程序的行为。**

在 C++20 中，`operator>>`它被更改为仅适用于输入非衰减的 C 样式字符串。这样可以只`operator>>`提取 C 样式字符串长度允许的字符数，从而防止溢出。但这也意味着您不能再使用它`operator>>`来输入衰减的 C 样式字符串。

读取 C 风格字符串的推荐方法`std::cin`如下：

```cpp
#include <iostream>
#include <iterator> // for std::size

int main()
{
    char rolls[255] {}; // declare array large enough to hold 254 characters + null terminator
    std::cout << "Enter your rolls: ";
    std::cin.getline(rolls, std::size(rolls));
    std::cout << "You entered: " << rolls << '\n';

    return 0;
}
```

此调用`cin.getline()`将读取最多 254 个字符（包括空格）到 中`rolls`。任何多余的字符都将被丢弃。由于`getline()`需要长度，我们可以提供要接受的最大字符数。对于非衰减数组，这很容易——我们可以使用`std::size()`来获取数组长度。对于衰减数组，我们必须以其他方式确定长度。如果我们提供错误的长度，我们的程序可能会出现故障或出现安全问题。

在现代 C++ 中，存储用户输入的文本时，使用更安全`std::string`，因为`std::string`它会自动调整以保存所需的尽可能多的字符。

## 修改 C 风格字符串

需要注意的一点是，C 样式字符串遵循与 C 样式数组相同的规则。这意味着您可以在创建时初始化字符串，但此后不能使用赋值运算符为其赋值！

```cpp
char str[]{ "string" }; // ok
str = "rope";           // not ok!
```

## 这使得使用 C 风格的字符串有点尴尬。

由于 C 风格的字符串是数组，因此可以使用 [] 运算符来更改字符串中的各个字符：

```cpp
#include <iostream>

int main()
{
    char str[]{ "string" };
    std::cout << str << '\n';
    str[1] = 'p';
    std::cout << str << '\n';

    return 0;
}
```

该程序打印：

```
string
spring
```

## 获取 C 风格字符串的长度

由于 C 样式字符串是 C 样式数组，因此可以使用`std::size()`（或在 C++20 中为`std::ssize()`）以数组形式获取字符串的长度。这里有两个注意事项：

1. 这对衰减的琴弦不起作用。
2. 返回 C 风格数组的实际长度，而不是字符串的长度。

```cpp
#include <iostream>

int main()
{
    char str[255]{ "string" }; // 6 characters + null terminator
    std::cout << "length = " << std::size(str) << '\n'; // prints length = 255

    char *ptr { str };
    std::cout << "length = " << std::size(ptr) << '\n'; // compile error

    return 0;
}
```

另一种解决方案是使用`strlen()`位于`<cstring>`标题中的函数。`strlen()`将对衰减数组起作用，并返回所保存的字符串的长度，不包括空终止符：

```cpp
#include <cstring> // for std::strlen
#include <iostream>

int main()
{
    char str[255]{ "string" }; // 6 characters + null terminator
    std::cout << "length = " << std::strlen(str) << '\n'; // prints length = 6

    char *ptr { str };
    std::cout << "length = " << std::strlen(ptr) << '\n';   // prints length = 6

    return 0;
}
```

但是，`std::strlen()`速度很慢，因为它必须遍历整个数组，计数字符直到遇到空终止符。

## 其他 C 风格字符串操作函数

由于 C 样式字符串是 C 中的主要字符串类型，因此 C 语言提供了很多用于操作 C 样式字符串的函数。这些函数已被 C++ 继承为`<cstring>`头文件的一部分。

以下是您可能在旧代码中看到的一些最有用的功能：

- `strlen()`——返回 C 风格字符串的长度
- `strcpy()`、strncpy()、`strcpy_s()` - 用一个 C 风格字符串覆盖另一个
- `strcat()`, `strncat()` -- 将一个 C 风格字符串附加到另一个字符串的末尾
- `strcmp()`, `strncmp()` - 比较两个 C 风格字符串（`0`如果相等则返回）

除此之外`strlen()`，我们一般建议避免这些。

## 避免使用非常量 C 风格字符串对象

除非您有特定的、令人信服的理由使用非 const C 风格字符串，否则最好避免使用它们，因为它们使用起来很不方便并且容易溢出，这将导致未定义的行为（并且是潜在的安全问题）。

在极少数情况下，您确实需要使用 C 风格的字符串或固定缓冲区大小（例如，对于内存有限的设备），我们建议使用为此目的而设计的经过充分测试的第三方固定长度字符串库。

**最佳实践**

**避免使用非 const C 风格字符串对象，而应使用`std::string`。**

## 测验时间

### 问题 #1

编写一个函数逐个字符地打印 C 样式的字符串。使用指针和指针算法遍历字符串的每个字符并打印该字符。编写一个`main`函数，使用字符串文字“Hello, world!”测试该函数。

```cpp
#include <iostream>

// str will point to the first letter of the C-style string.
// Note that str points to a const char, so we can not change the values it points to.
// However, we can point str at something else.  This does not change the value of the argument.
void printCString(const char str[])
{
    // While we haven't encountered a null terminator
    while (*str != '\0')
    {
        // print the current character
        std::cout << *str;

        // and use pointer arithmetic to move str to the next character
        ++str;
    }
}

int main()
{
    printCString("Hello world!");

    std::cout << '\n';

    return 0;
}
```

### 问题 #2

重复测验#1，但这次函数应该向后打印字符串。

```cpp
#include <iostream>

void printCStringBackwards(const char str[])
{
    // We can't modify str this time (we need it later)
    // So we'll define a new pointer with the same address as str
    const char *ptr{ str };

    // Find the null terminator
    while (*ptr != '\0')
        ++ptr;

    // Now walk backwards and print characters until ptr reaches str again
    while (ptr-- != str)
    {
        std::cout << *ptr;
    }
}

int main()
{
    printCStringBackwards("Hello world!");

    std::cout << '\n';

    return 0;
}
```

# 17.11 — C 风格字符串符号常量

在上一课（[17.10 -- C 风格的字符串](https://www.learncpp.com/cpp-tutorial/c-style-strings/)）中，我们讨论了如何创建和初始化 C 风格的字符串对象：

```cpp
#include <iostream>

int main()
{
    char name[]{ "Alex" }; // C-style string
    std::cout << name << '\n';

    return 0;
}
```

C++ 支持两种不同的方式来创建 C 风格的字符串符号常量：

```cpp
#include <iostream>

int main()
{
    const char name[] { "Alex" };        // case 1: const C-style string initialized with C-style string literal
    const char* const color{ "Orange" }; // case 2: const pointer to C-style string literal

    std::cout << name << ' ' << color << '\n';

    return 0;
}
```

这将打印：

```
Alex Orange
```

虽然上述两种方法产生相同的结果，但 C++ 处理这些方法的内存分配略有不同。

在情况 1 中，“Alex”被放入（可能是只读的）内存中的某个位置。然后程序为长度为 5（四个显式字符加上空终止符）的 C 样式数组分配内存，并使用字符串“Alex”初始化该内存。因此，我们最终得到了“Alex”的 2 个副本——一个在全局内存中的某个位置，另一个由 拥有`name`。由于`name`是 const（并且永远不会被修改），因此复制效率很低。

在情况 2 中，编译器如何处理这个问题由实现定义。*通常的*情况是，编译器将字符串“Orange”放入某个只读内存中，然后用字符串的地址初始化指针。

为了优化目的，可以将多个字符串文字合并为一个值。例如：

```cpp
const char* name1{ "Alex" };
const char* name2{ "Alex" };
```

`name1`这是两个具有相同值的不同字符串文字。由于这些文字是常量，因此编译器可能会选择将它们组合成一个共享字符串文字，并将和`name2`指向同一地址，以节省内存。

## 使用 const C 风格字符串进行类型推断

使用 C 风格字符串文字进行类型推断相当简单：

```cpp
auto s1{ "Alex" };  // type deduced as const char*
auto* s2{ "Alex" }; // type deduced as const char*
auto& s3{ "Alex" }; // type deduced as const char(&)[5]
```

## 输出指针和 C 风格字符串

`std::cout`您可能已经注意到处理不同类型指针的方式的一些有趣的地方。

请考虑以下示例：

```cpp
#include <iostream>

int main()
{
    int narr[]{ 9, 7, 5, 3, 1 };
    char carr[]{ "Hello!" };
    const char* ptr{ "Alex" };

    std::cout << narr << '\n'; // narr will decay to type int*
    std::cout << carr << '\n'; // carr will decay to type char*
    std::cout << ptr << '\n'; // name is already type char*

    return 0;
}
```

在作者的机器上打印了以下内容：

```
003AF738
Hello!
Alex
```

为什么 int 数组打印地址，而字符数组却打印为字符串？

答案是输出流（例如`std::cout`）会对您的意图做出一些假设。如果您向其传递一个非字符指针，它将仅打印该指针的内容（指针所保存的地址）。但是，如果您向其传递类型为`char*`或 的对象`const char*`，它将假定您打算打印一个字符串。因此，它不会打印指针的值（地址），而是打印指向的字符串！

虽然大多数情况下这是理想的，但它可能会导致意想不到的结果。考虑以下情况：

```cpp
#include <iostream>

int main()
{
    char c{ 'Q' };
    std::cout << &c;

    return 0;
}
```

在这种情况下，程序员打算打印变量的地址`c`。但是，`&c`具有类型`char*`，因此`std::cout`尝试将其打印为字符串！并且由于`c`不是以空字符结尾的，我们得到了未定义的行为。

在作者的机器上打印了以下内容：

```
Q╠╠╠╠╜╡4;¿■A
```

它为什么会这样做？首先，它假设`&c`(类型为`char*`) 是一个 C 样式的字符串。因此它打印了“Q”，然后继续运行。接下来内存中是一堆垃圾。最后，它遇到了一些保存`0`值的内存，它将其解释为空终止符，因此它停止了。您看到的内容可能因变量 之后内存中的内容而异`c`。

这种情况在现实生活中不太可能发生（因为您不太可能真正想要打印内存地址），但它说明了事情在幕后是如何运作的，以及程序是如何无意中出轨的。

如果您确实想打印字符指针的地址，请将其 static_cast 为类型`const void*`：

```cpp
#include <iostream>

int main()
{
    const char* ptr{ "Alex" };

    std::cout << ptr << '\n';                           // print ptr as C-style string
    std::cout << static_cast<const void*>(ptr) << '\n'; // print address held by ptr

    return 0;
}
```

**相关内容**

**我们将`void*`在第 19.5 课中介绍[Void 指针](https://www.learncpp.com/cpp-tutorial/void-pointers/)。在这里，您无需了解它的工作原理即可使用它。**

## 支持使用 std::string_view 作为 C 风格字符串符号常量

在现代 C++ 中，几乎没有理由使用 C 样式的字符串符号常量。相反，更倾向于使用`constexpr std::string_view`对象，因为它们往往同样快（如果不是更快的话）并且行为更一致。

**最佳实践**

**避免使用 C 风格的字符串符号常量，而应使用`constexpr std::string_view`。**

# 17.12 — 多维 C 风格数组

[以井字](https://en.wikipedia.org/wiki/Tic-tac-toe)游戏为例。该游戏的标准棋盘是 3×3 网格，玩家轮流放置“X”和“O”符号。最先将三个符号连成一线的玩家获胜。

虽然您可以将棋盘数据存储为 9 个单独的变量，但我们知道，当您拥有一个元素的多个实例时，最好使用数组：

```cpp
int ttt[9]; // a C-style array of ints (value 0 = empty, 1 = player 1, 2 = player 2)
```

这定义了一个 C 样式数组，其中 9 个元素在内存中按顺序排列。我们可以想象这些元素以一行值的形式排列，如下所示：

```
// ttt[0] ttt[1] ttt[2] ttt[3] ttt[4] ttt[5] ttt[6] ttt[7] ttt[8]
```

数组的维度是选择元素所需的索引数。仅包含单个维度的数组称为**单****维数组**或**一维数组**（有时缩写为**1d 数组**）。`ttt`上面是一个一维数组的示例，因为可以使用单个索引（例如）选择元素`ttt[2]`。

但请注意，我们的一维数组看起来与井字棋盘不太相似，后者是二维的。我们可以做得更好。

## 二维数组

在之前的课程中，我们注意到数组的元素可以是任何对象类型。这意味着数组的元素类型可以是另一个数组！定义这样的数组很简单：

```cpp
int a[3][5]; // a 3-element array of 5-element arrays of int
```

数组的数组被称为**二维数组**（有时缩写为**2d 数组**），因为它具有两个下标。

对于二维数组，可以方便地将第一个（左）下标视为选择行，将第二个（右）下标视为选择列。从概念上讲，我们可以想象这个二维数组的布局如下：

```
// col 0    col 1    col 2    col 3    col 4
// a[0][0]  a[0][1]  a[0][2]  a[0][3]  a[0][4]  row 0
// a[1][0]  a[1][1]  a[1][2]  a[1][3]  a[1][4]  row 1
// a[2][0]  a[2][1]  a[2][2]  a[2][3]  a[2][4]  row 2
```

要访问二维数组的元素，我们只需使用两个下标：

```cpp
a[2][3] = 7; // a[row][col], where row = 2 and col = 3
```

因此，对于井字游戏棋盘，我们可以定义这样的二维数组：

```cpp
int ttt[3][3];
```

现在我们有一个 3×3 的元素网格，我们可以使用行和列索引轻松地操作它们！

## 多维数组

具有多个维度的数组称为**多维数组**。

C++ 甚至支持超过 2 维的多维数组：

```cpp
int threedee[4][4][4]; // a 4x4x4 array (an array of 4 arrays of 4 arrays of 4 ints)
```

例如，Minecraft 中的地形被划分为 16x16x16 个块（称为区块部分）。

支持维度高于 3 的数组，但很少见。

## 二维数组在内存中的布局方式

内存是线性的（一维），因此多维数组实际上存储为元素的连续列表。

下列数组在内存中的存储方式有两种可能：

```cpp
// col 0   col 1   col 2   col 3   col 4
// [0][0]  [0][1]  [0][2]  [0][3]  [0][4]  row 0
// [1][0]  [1][1]  [1][2]  [1][3]  [1][4]  row 1
// [2][0]  [2][1]  [2][2]  [2][3]  [2][4]  row 2
```

C++ 使用**按行主序排列的顺序**，其中元素按行顺序放置在内存中，从左到右、从上到下的顺序排列：

```
[0][0] [0][1] [0][2] [0][3] [0][4] [1][0] [1][1] [1][2] [1 ][3] [1][4] [2][0] [2][1] [2][2] [2][3] [2][4]
```

一些其他语言（例如 Fortran）使用**列主顺序**，元素按列顺序依次放置在内存中，从上到下、从左到右：

```
[0][0] [1][0] [2][0] [0][1] [1][1] [2][1] [0][2] [1][2] [2 ][2] [0][3] [1][3] [2][3] [0][4] [1][4] [2][4]
```

在 C++ 中，初始化数组时，元素按行优先顺序初始化。而遍历数组时，按元素在内存中的排列顺序访问元素是最高效的。

## 初始化二维数组

要初始化二维数组，最简单的方法是使用嵌套括号，每组数字代表一行：

```cpp
int array[3][5]
{
  { 1, 2, 3, 4, 5 },     // row 0
  { 6, 7, 8, 9, 10 },    // row 1
  { 11, 12, 13, 14, 15 } // row 2
};
```

尽管某些编译器允许您省略内部括号，但为了便于阅读，我们还是强烈建议您将其包括在内。

当使用内部括号时，缺少的初始化器将被值初始化：

```cpp
int array[3][5]
{
  { 1, 2 },          // row 0 = 1, 2, 0, 0, 0
  { 6, 7, 8 },       // row 1 = 6, 7, 8, 0, 0
  { 11, 12, 13, 14 } // row 2 = 11, 12, 13, 14, 0
};
```



初始化的多维数组可以省略（仅）最左边的长度指定：

```cpp
int array[][5]
{
  { 1, 2, 3, 4, 5 },
  { 6, 7, 8, 9, 10 },
  { 11, 12, 13, 14, 15 }
};
```

在这种情况下，编译器可以通过计算根据初始化器的数量来确定最左边的长度。

不允许省略非最左边的维度：

```cpp
int array[][]
{
  { 1, 2, 3, 4 },
  { 5, 6, 7, 8 }
};
```

与普通数组一样，多维数组仍然可以初始化为 0，如下所示：

```cpp
int array[3][5] {};
```

## 二维数组和循环

对于一维数组，我们可以使用单个循环来遍历数组中的所有元素：

```cpp
#include <iostream>

int main()
{
    int arr[] { 1, 2, 3, 4, 5 };

    // for-loop with index
    for (std::size_t i{0}; i < std::size(arr); ++i)
        std::cout << arr[i] << ' ';

    std::cout << '\n';

    // range-based for-loop
    for (auto e: arr)
        std::cout << e << ' ';

    std::cout << '\n';

    return 0;
}
```

对于二维数组，我们需要两个循环：一个用于选择行，另一个用于选择列。

对于两个循环，我们还需要确定哪个循环是外循环，哪个是内循环。按照元素在内存中的排列顺序访问元素是最有效的。由于 C++ 使用行优先顺序，因此行选择器应该是外循环，列选择器应该是内循环。

```cpp
#include <iostream>

int main()
{
    int arr[3][4] {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }};

    // double for-loop with indices
    for (std::size_t row{0}; row < std::size(arr); ++row) // std::size(arr) returns the number of rows
    {
        for (std::size_t col{0}; col < std::size(arr[0]); ++col) // std::size(arr[0]) returns the number of columns
            std::cout << arr[row][col] << ' ';

        std::cout << '\n';
    }

    // double range-based for-loop
    for (const auto& arow: arr)   // get each array row
    {
        for (const auto& e: arow) // get each element of the row
            std::cout << e << ' ';

        std::cout << '\n';
    }

    return 0;
}
```

## 二维数组示例

我们来看一个二维数组的实际例子：

```cpp
#include <iostream>

int main()
{
    constexpr int numRows{ 10 };
    constexpr int numCols{ 10 };

    // Declare a 10x10 array
    int product[numRows][numCols]{};

    // Calculate a multiplication table
    // We don't need to calc row and col 0 since mult by 0 always is 0
    for (std::size_t row{ 1 }; row < numRows; ++row)
    {
        for (std::size_t col{ 1 }; col < numCols; ++col)
        {
            product[row][col] = static_cast<int>(row * col);
        }
     }

    for (std::size_t row{ 1 }; row < numRows; ++row)
    {
        for (std::size_t col{ 1 }; col < numCols; ++col)
        {
            std::cout << product[row][col] << '\t';
        }

        std::cout << '\n';
     }


    return 0;
}
```

此程序计算并打印 1 到 9（含）之间所有值的乘法表。请注意，打印表格时，for 循环从 1 开始，而不是从 0 开始。这是为了省略打印 0 列和 0 行，它们只会是一堆 0！以下是输出：

```
1 2 3 4 5 6 7 8 9
2 4 6 8 10 12 14 16 18
3 6 9 12 15 18 21 24 27
4 8 12 16 20 24 28 32 36
5 10 15 20 25 30 35 40 45
6 12 18 24 30 36 42 48 54
7 14 21 28 35 42 49 56 63
8 16 24 32 40 48 56 64 72
9 18 27 36 45 54 63 72 81
```

## 笛卡尔坐标与数组索引

在几何学中，[笛卡尔坐标系](https://en.wikipedia.org/wiki/Cartesian_coordinate_system)通常用于描述物体的位置。在二维空间中，我们有两个坐标轴，通常称为“x”和“y”。“x”是水平轴，“y”是垂直轴。

![笛卡尔坐标系图](./assets/ngcb2.webp)

在二维中，物体的笛卡尔位置可以描述为 { x, y } 对，其中 x 坐标和 y 坐标表示物体位于 x 轴右侧多远以及 y 轴上方多远的值。有时 y 轴会被翻转（因此 y 坐标描述物体位于 y 轴下方多远）。

现在让我们看一下 C++ 中的二维数组布局：

```cpp
// col 0   col 1   col 2   col 3   col 4
// [0][0]  [0][1]  [0][2]  [0][3]  [0][4]  row 0
// [1][0]  [1][1]  [1][2]  [1][3]  [1][4]  row 1
// [2][0]  [2][1]  [2][2]  [2][3]  [2][4]  row 2
```



这也是一个二维坐标系，其中元素的位置可以描述为 [row][col]（其中 col 轴被翻转）。

虽然每个坐标系都很容易独立理解，但从笛卡尔坐标 { x, y } 转换为数组索引 [row][col] 有点违反直觉。

关键见解是，笛卡尔系统中的 x 坐标描述了在数组索引系统中选择了哪一*列。相反，y 坐标描述了选择了哪一**行*。因此，{ x, y } 笛卡尔坐标转换为 [y][x] 数组坐标，这与我们的预期正好相反！

这会导致如下二维循环：

```cpp
for (std::size_t y{0}; y < std::size(arr); ++y) // outer loop is rows / y
{
    for (std::size_t x{0}; x < std::size(arr[0]); ++x) // inner loop is columns / x
        std::cout << arr[y][x] << ' '; // index with y (row) first, then x (col)
```

请注意，在这种情况下，我们将数组索引为`a[y][x]`，这可能与您期望的字母顺序相反。

# 17.13 — 多维 std::array

在上一课（[17.12——C 风格多维数组](https://www.learncpp.com/cpp-tutorial/multidimensional-c-style-arrays/)）中，我们讨论了 C 风格的多维数组。

```cpp
// C-style 2d array
int arr[3][4] {
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9, 10, 11, 12 }};
```

但正如您所知，我们通常要避免使用 C 风格的数组（除非它们被用来存储全局数据）。

在本课中，我们将了解多维数组如何协同工作`std::array`。

没有标准库多维数组类

请注意，它`std::array`是作为一维数组实现的。因此，您应该问的第一个问题是，“是否有用于多维数组的标准库类？”答案是……没有。太糟糕了。呜呜呜。

## 二维`std::array`

创建二维数组的规范方法`std::array`是创建一个`std::array`，其中模板类型参数是另一个`std::array`。这会导致这样的结果：

```cpp
std::array<std::array<int, 4>, 3> arr {{  // note double braces
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9, 10, 11, 12 }}};	·
```

有许多“有趣”的事情值得注意：

- 当初始化多维时`std::array`，我们需要使用双括号（我们在第[17.4 课中讨论了为什么——类类型的 std::array 和括号省略](https://www.learncpp.com/cpp-tutorial/stdarray-of-class-types-and-brace-elision/)）。
- 语法冗长且难以阅读。
- 由于模板嵌套的方式，数组维度被切换。我们想要一个有 3 行、4 个元素的数组，所以`arr[3][4]`很自然。`std::array<std::array<int, 4>, 3>`是反向的。

索引二维`std::array`元素的方式与索引二维 C 样式数组的方式相同：

```cpp
std::cout << arr[1][2]; // print the element in row 1, column 2
```

`std::array`我们还可以像传递一维数据一样将二维数据传递给函数`std::array`：

```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t Row, std::size_t Col>
void printArray(const std::array<std::array<T, Col>, Row> &arr)
{
    for (const auto& arow: arr)   // get each array row
    {
        for (const auto& e: arow) // get each element of the row
            std::cout << e << ' ';

        std::cout << '\n';
    }
}

int main()
{
    std::array<std::array<int, 4>, 3>  arr {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }}};

    printArray(arr);

    return 0;
}
```

真恶心。这还是二维的`std::array`。三维或更高级别的`std::array`就更冗长了！

## `std::array`使用别名模板让二维设计更加简单

在课程[10.7 -- 类型定义和类型别名](https://www.learncpp.com/cpp-tutorial/typedefs-and-type-aliases/)中，我们介绍了类型别名，并指出类型别名的用途之一是使复杂类型更易于使用。但是，对于普通类型别名，我们必须显式指定所有模板参数。例如

```cpp
using Array2dint34 = std::array<std::array<int, 4>, 3>;
```

这允许我们在需要的地方使用`Array2dint34`3×4 二维 std::array `int`。但请注意，对于我们想要使用的每种元素类型和维度组合，我们都需要这样一个别名！

这是一个使用别名模板的最佳场所，它让我们将类型别名的元素类型、行长度和列长度指定为模板参数！

```cpp
// An alias template for a two-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;
```

然后我们可以`Array2d<int, 3, 4>`在任何需要的地方使用 3×4 二维 std::array `int`。这好多了！

这是一个完整的例子：

```cpp
#include <array>
#include <iostream>

// An alias template for a two-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;

// When using Array2d as a function parameter, we need to respecify the template parameters
template <typename T, std::size_t Row, std::size_t Col>
void printArray(const Array2d<T, Row, Col> &arr)
{
    for (const auto& arow: arr)   // get each array row
    {
        for (const auto& e: arow) // get each element of the row
            std::cout << e << ' ';

        std::cout << '\n';
    }
}

int main()
{
    // Define a two-dimensional array of int with 3 rows and 4 columns
    Array2d<int, 3, 4> arr {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }}};

    printArray(arr);

    return 0;
}
```

请注意，它更加简洁，使用更加方便！

我们的别名模板的一个巧妙之处在于，我们可以按照我们喜欢的顺序定义模板参数。由于 a`std::array`首先指定元素类型，然后指定维度，因此我们坚持这一惯例。但是我们可以灵活地定义`Row`或`Col`first。由于 C 样式数组定义是按行优先定义的，因此我们使用`Row`before定义我们的别名模板`Col`。

该方法也能很好地扩展到高维`std::array`：

```cpp
// An alias template for a three-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col, std::size_t Depth>
using Array3d = std::array<std::array<std::array<T, Depth>, Col>, Row>;
```

## 获取二维数组的维长度

对于一维的`std::array`，我们可以使用`size()`成员函数（或`std::size()`）来获取数组的长度。但是当我们有二维的 时我们该怎么办`std::array`？在这种情况下，`size()`将仅返回第一维的长度。

一个看似有吸引力（但可能很危险）的选项是获取所需维度的元素，然后调用`size()`该元素：

```cpp
#include <array>
#include <iostream>

// An alias template for a two-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;

int main()
{
    // Define a two-dimensional array of int with 3 rows and 4 columns
    Array2d<int, 3, 4> arr {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }}};

    std::cout << "Rows: " << arr.size() << '\n';    // get length of first dimension (rows)
    std::cout << "Cols: " << arr[0].size() << '\n'; // get length of second dimension (cols), undefined behavior if length of first dimension is zero!

    return 0;
}
```

为了获取第一维的长度，我们调用`size()`数组。为了获取第二维的长度，我们首先调用`arr[0]`以获取第一个元素，然后调用`size()`该元素。为了获取三维数组的第三维的长度，我们将调用`arr[0][0].size()`。

但是，上述代码是有缺陷的，因为如果除最后一个维度之外的任何维度的长度为 0，它将产生未定义的行为！

更好的选择是使用函数模板直接从关联的非类型模板参数返回维度的长度：

```cpp
#include <array>
#include <iostream>

// An alias template for a two-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;

// Fetch the number of rows from the Row non-type template parameter
template <typename T, std::size_t Row, std::size_t Col>
constexpr int rowLength(const Array2d<T, Row, Col>&) // you can return std::size_t if you prefer
{
    return Row;
}

// Fetch the number of cols from the Col non-type template parameter
template <typename T, std::size_t Row, std::size_t Col>
constexpr int colLength(const Array2d<T, Row, Col>&) // you can return std::size_t if you prefer
{
    return Col;
}

int main()
{
    // Define a two-dimensional array of int with 3 rows and 4 columns
    Array2d<int, 3, 4> arr {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }}};

    std::cout << "Rows: " << rowLength(arr) << '\n'; // get length of first dimension (rows)
    std::cout << "Cols: " << colLength(arr) << '\n'; // get length of second dimension (cols)

    return 0;
}
```

如果任何维度的长度为零，这可以避免任何未定义的行为，因为它仅使用数组的类型信息，而不是数组的实际数据。这还允许我们根据`int`需要轻松地将长度返回为（不需要 static_cast，因为从 a 转换`constexpr std::size_t`为非`constexpr int`缩小，因此隐式转换就可以了）。

## 平展二维数组

二维或二维以上的数组存在一些挑战：

- 它们的定义和使用起来更加冗长。
- 获得大于第一个的尺寸的长度是很困难的。
- 它们越来越难以迭代（每个维度都需要一个循环）。

使多维数组更易于使用的一种方法是将其展平。**展平**数组是降低数组维数（通常降至一维）的过程。

例如，我们可以创建一个包含元素的一维数组，而不是创建包含`Row`行和列的二维数组。这样，我们只需使用一个维度即可获得相同的存储空间。`Col``Row * Col`

但是，由于我们的一维数组只有一个维度，因此我们无法将其用作多维数组。为了解决这个问题，我们可以提供一个模拟多维数组的接口。此接口将接受二维坐标，然后将它们映射到一维数组中的唯一位置。

下面是在 C++11 或更新版本中有效的方法的一个例子：

```cpp
#include <array>
#include <iostream>
#include <functional>

// An alias template to allow us to define a one-dimensional std::array using two dimensions
template <typename T, std::size_t Row, std::size_t Col>
using ArrayFlat2d = std::array<T, Row * Col>;

// A modifiable view that allows us to work with an ArrayFlat2d using two dimensions
// This is a view, so the ArrayFlat2d being viewed must stay in scope
template <typename T, std::size_t Row, std::size_t Col>
class ArrayView2d
{
private:
    // You might be tempted to make m_arr a reference to an ArrayFlat2d,
    // but this makes the view non-copy-assignable since references can't be reseated.
    // Using std::reference_wrapper gives us reference semantics and copy assignability.
    std::reference_wrapper<ArrayFlat2d<T, Row, Col>> m_arr {};

public:
    ArrayView2d(ArrayFlat2d<T, Row, Col> &arr)
        : m_arr { arr }
    {}

    // Get element via single subscript (using operator[])
    T& operator[](int i) { return m_arr.get()[static_cast<std::size_t>(i)]; }
    const T& operator[](int i) const { return m_arr.get()[static_cast<std::size_t>(i)]; }

    // Get element via 2d subscript (using operator(), since operator[] doesn't support multiple dimensions prior to C++23)
    T& operator()(int row, int col) { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }
    const T& operator()(int row, int col) const { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }

    // in C++23, you can uncomment these since multidimensional operator[] is supported
//    T& operator[](int row, int col) { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }
//    const T& operator[](int row, int col) const { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }

    int rows() const { return static_cast<int>(Row); }
    int cols() const { return static_cast<int>(Col); }
    int length() const { return static_cast<int>(Row * Col); }
};

int main()
{
    // Define a one-dimensional std::array of int (with 3 rows and 4 columns)
    ArrayFlat2d<int, 3, 4> arr {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12 };

    // Define a two-dimensional view into our one-dimensional array
    ArrayView2d<int, 3, 4> arrView { arr };

    // print array dimensions
    std::cout << "Rows: " << arrView.rows() << '\n';
    std::cout << "Cols: " << arrView.cols() << '\n';

    // print array using a single dimension
    for (int i=0; i < arrView.length(); ++i)
        std::cout << arrView[i] << ' ';

    std::cout << '\n';

    // print array using two dimensions
    for (int row=0; row < arrView.rows(); ++row)
    {
        for (int col=0; col < arrView.cols(); ++col)
            std::cout << arrView(row, col) << ' ';
        std::cout << '\n';
    }

    std::cout << '\n';

    return 0;
}
```

这将打印：

```
行：3
列数：4
1 2 3 4 5 6 7 8 9 10 11 12
1 2 3 4
5 6 7 8
9 10 11 12
```

因为`operator[]`在 C++23 之前只能接受单个下标，所以有两种替代方法：

- 改为使用`operator()`，它可以接受多个下标。这允许您`[]`用于单索引和`()`多维索引。我们在上面选择了这种方法。
- 返回一个也会`operator[]`过载的子视图，`operator[]`以便您可以链接`operator[]`。这更复杂，并且不能很好地扩展到更高的维度。

在 C++23 中，`operator[]`它被扩展为接受多个下标，因此您可以重载它来处理单个和多个下标（而不是用于`operator()`多个下标）。

**相关内容**

**我们将`std::reference_wrapper`在第 17.5 课中介绍[如何通过 std::reference_wrapper 访问引用数组](https://www.learncpp.com/cpp-tutorial/arrays-of-references-via-stdreference_wrapper/)。**

## std::mdspan C++23

C++23 中引入了`std::mdspan`可修改视图，它为连续的元素序列提供多维数组接口。可修改视图的意思是，`std::mdspan`不仅仅是只读视图（如`std::string_view`）——如果底层元素序列非常量，则可以修改这些元素。

以下示例打印与前面的示例相同的输出，但使用`std::mdspan`我们自己的自定义视图：

```cpp
#include <array>
#include <iostream>
#include <mdspan>

// An alias template to allow us to define a one-dimensional std::array using two dimensions
template <typename T, std::size_t Row, std::size_t Col>
using ArrayFlat2d = std::array<T, Row * Col>;

int main()
{
    // Define a one-dimensional std::array of int (with 3 rows and 4 columns)
    ArrayFlat2d<int, 3, 4> arr {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12 };

    // Define a two-dimensional span into our one-dimensional array
    // We must pass std::mdspan a pointer to the sequence of elements
    // which we can do via the data() member function of std::array or std::vector
    std::mdspan mdView { arr.data(), 3, 4 };

    // print array dimensions
    // std::mdspan calls these extents
    std::size_t rows { mdView.extents().extent(0) };
    std::size_t cols { mdView.extents().extent(1) };
    std::cout << "Rows: " << rows << '\n';
    std::cout << "Cols: " << cols << '\n';

    // print array in 1d
    // The data_handle() member gives us a pointer to the sequence of elements
    // which we can then index
    for (std::size_t i=0; i < mdView.size(); ++i)
        std::cout << mdView.data_handle()[i] << ' ';
    std::cout << '\n';

    // print array in 2d
    // We use multidimensional [] to access elements
    for (std::size_t row=0; row < rows; ++row)
    {
        for (std::size_t col=0; col < cols; ++col)
            std::cout << mdView[row, col] << ' ';
        std::cout << '\n';
    }
    std::cout << '\n';

    return 0;
}
```

这应该相当简单，但有几点值得注意：

- `std::mdspan`让我们定义一个具有任意多个维度的视图。
- 的构造函数的第一个参数`std::mdspan`应该是指向数组数据的指针。这可以是衰减的 C 样式数组，或者我们可以使用的`data()`成员函数`std::array`或`std::vector`来获取此数据。
- 为了在一维中索引 a `std::mdspan`，我们必须获取指向数组数据的指针，这可以使用`data_handle()`成员函数来实现。然后我们可以对其进行下标。
- 在 C++23 中，`operator[]`接受多个索引，因此我们使用`[row, col]`作为索引而不是`[row][col]`。

C++26 将包括`std::mdarray`，它本质上将`std::array`和`std::mdspan`结合成一个拥有多维数组！

# 17.x — 第 17 章总结和测验

## 章节回顾

**固定大小数组**（或**固定长度数组**）要求在实例化时知道数组的长度，并且之后不能更改该长度。C 样式数组和`std::array`都是固定大小数组。动态数组可以在运行时调整大小。`std::vector`是动态数组。

的长度`std::array`必须是常量表达式。通常，长度的值将是整数文字、constexpr 变量或无作用域枚举器。

`std::array`是一个聚合。这意味着它没有构造函数，而是使用聚合初始化来初始化。

`std::array`尽可能将你的定义为 constexpr。如果你的`std::array`不是 constexpr，请考虑改用`std::vector`。

使用类模板参数推导（CTAD）让编译器从其初始化器中推导 std::array 的类型和长度。

`std::array`作为模板结构实现，其声明如下：

```cpp
template<typename T, std::size_t N> // N is a non-type template parameter
struct array;
```

表示数组长度的非类型模板参数（`N`）的类型为`std::size_t`。

获取 a 的长度`std::array`：

- 我们可以使用成员函数（以无符号形式返回长度）询问`std::array`对象的长度。`size()``size_type`
- 在 C++17 中，我们可以使用`std::size()`非成员函数（它只`std::array`调用`size()`成员函数，从而以无符号形式返回长度`size_type`）。
- 在 C++20 中，我们可以使用`std::ssize()`非成员函数，它将长度作为大的*有符号*整数类型（通常`std::ptrdiff_t`）返回。

这三个函数都将以 constexpr 值的形式返回长度，除非在`std::array`通过引用传递时调用。此缺陷已在 C++23 中通过[P2280](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2280r4.html)解决。

要索引 a `std::array`：

- 使用下标运算符 ( `operator[]`)。在这种情况下不进行边界检查，传入无效索引将导致未定义的行为。
- 使用执行`at()`带有运行时边界检查的下标的成员函数。我们建议避免使用此函数，因为我们通常希望在索引之前进行边界检查，或者我们希望进行编译时边界检查。
- 使用`std::get()`函数模板，它将索引作为非类型模板参数，并进行编译时边界检查。

您可以`std::array`使用带有模板参数声明的函数模板将不同的元素类型和长度传递给函数`template <typename T, std::size_t N>`。或者在 C++20 中使用`template <typename T, auto N>`。

返回一个`std::array`by 值将复制数组和所有元素，但如果数组很小并且元素的复制成本不高，那么这可能是可以的。在某些情况下，使用 out 参数可能是更好的选择。

当使用结构、类或数组初始化 a`std::array`并且不为每个初始化器提供元素类型时，您需要一对额外的括号，以便编译器正确解释要初始化的内容。这是聚合初始化的产物，其他标准库容器类型（使用列表构造函数）在这些情况下不需要双括号。

C++ 中的聚合支持一种称为**括号省略的**概念，该概念规定了何时可以省略多个括号。通常，在`std::array`使用标量（单个）值初始化时，或者在使用类类型或数组初始化时（其中类型用每个元素明确命名），可以省略括号。

您不能拥有一个引用数组，但您可以拥有一个数组`std::reference_wrapper`，其行为类似于可修改的左值引用。

有几件事值得注意`std::reference_wrapper`：

- `Operator=`将重新安置`std::reference_wrapper`（更改正在引用的对象）。
- `std::reference_wrapper<T>`将隐式转换为`T&`。
- 成员函数`get()`可用于获取`T&`。当我们想要更新所引用对象的值时，这很有用。

`std::ref()`和`std::cref()`函数作为创建`std::reference_wrapper`和包装`std::reference_wrapper`对象的快捷方式提供。

`static_assert`尽可能使用以确保`constexpr std::array`使用 CTAD 具有正确数量的初始化程序。

C 样式数组继承自 C 语言，并内置于 C++ 的核心语言中。由于 C 样式数组是核心语言的一部分，因此它们有自己的特殊声明语法。在 C 样式数组声明中，我们使用方括号 ([]) 来告诉编译器声明的对象是 C 样式数组。在方括号内，我们可以选择性地提供数组的长度，它是 std::size_t 类型的整数值，它告诉编译器数组中有多少个元素。C 样式数组的长度必须是常量表达式。

C 样式数组是聚合，这意味着可以使用聚合初始化来初始化它们。使用初始化列表初始化 C 样式数组的所有元素时，最好省略长度并让编译器计算数组的长度。

C 样式数组可通过 进行索引`operator[]`。C 样式数组的索引可以是有符号或无符号整数，也可以是无范围枚举。这意味着 C 样式数组不受标准库容器类存在的所有符号转换索引问题的影响！

C 样式数组可以是 const 或 constexpr。

获取 C 样式数组的长度：

- 在 C++17 中，我们可以使用`std::size()`非成员函数，它以无符号形式返回长度`std::size_t`。
- 在 C++20 中，我们可以使用`std::ssize()`非成员函数，它将长度作为大的*有符号*整数类型（通常`std::ptrdiff_t`）返回。

在大多数情况下，当在表达式中使用 C 样式数组时，该数组将被隐式转换为指向元素类型的指针，并使用第一个元素的地址（索引为 0）进行初始化。通俗地说，这称为**数组衰减**（或简称为衰减）。

**指针运算**是一种功能，它允许我们将某些整数运算运算符（加法、减法、递增或递减）应用于指针以生成新的内存地址。给定某个指针`ptr`，返回内存中下一个*对象*`ptr + 1`的地址（基于指向的类型）。

从数组开头（元素 0）开始索引时使用下标，这样数组索引与元素对齐。
从给定元素进行相对定位时使用指针算法。

C 风格字符串只是元素类型为`char`或 的C 风格数组`const char`。因此，C 风格字符串将会衰减。

数组的维度**是**选择元素所需的索引数量。

仅包含一个维度的数组称为**单维数组**或**一维数组**（有时缩写为**1d 数组**）。数组的数组称为**二维数组**（有时缩写为**2d 数组**），因为它有两个下标。具有多个维度的数组称为**多维数组**。**展平**数组是降低数组维数（通常降至单个维度）的过程。

在 C++23 中，`std::mdspan`是一种为连续元素序列提供多维数组接口的视图。

## 测验时间

### 问题 #1

每个片段有什么问题？如何修复？

a）

```cpp
#include <array>
#include <iostream>

int main()
{
    std::array arr { 0, 1, 2, 3 };

    for (std::size_t count{ 0 }; count <= std::size(arr); ++count)
    {
        std::cout << arr[count] << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

for 循环出现 off-by-one 错误，并尝试访问索引 4 的数组元素，但该元素不存在。

解决方案：for循环中的条件应该使用<而不是<=。

b)

```cpp
#include <iostream>

void printArray(int array[])
{
    for (int element : array)
    {
        std::cout << element << ' ';
    }
}

int main()
{
    int array[] { 9, 7, 5, 3, 1 };

    printArray(array);

    std::cout << '\n';

    return 0;
}
```

`array`当传递给时，会衰减为指针`printArray()`。基于范围的 for 循环无法处理指向数组的指针，因为数组的大小未知。

解决方法：改用`std::array`不会衰减的。

c)

```cpp
#include <array>
#include <iostream>

int main()
{
    std::cout << "Enter the number of test scores: ";
    std::size_t length{};
    std::cin >> length;

    std::array<int, length> scores;

    for (std::size_t i { 0 } ; i < length; ++i)
    {
        std::cout << "Enter score " << i << ": ";
        std::cin >> scores[i];
    }
    return 0;
}
```

`length`不是常量表达式，不能用来定义的长度`std::array`。

解决方法：改用a `std::vector`。

### 问题 #2

在本次测验中，我们将实现 Roscoe 的药水商场，这是全国最好的药水商店！这将是一个更大的挑战。

实现一个程序，输出以下内容：

```
欢迎来到 Roscoe 的药水商店！
输入您的姓名：Alex
您好，Alex，您有 85 金币。

这是我们今天的选择：
0) 治疗费用 20 
1) 法力费用 30 
2) 速度费用 12 
3) 隐身费用 50
输入您想要购买的药水编号，或按“q”退出：a
输入无效。重试：3
您购买了隐身药水。您还剩下 35 金币。

这是我们今天的选择：
0) 治疗费用 20 
1) 法力费用 30 
2) 速度费用 12 
3) 隐身费用 50
输入您想要购买的药水编号，或按“q”退出：4
输入无效。重试：2
您购买了速度药水。您还剩下 23 金币。

这是我们今天的选择：
0) 治疗费用 20 
1) 法力费用 30 
2) 速度费用 12 
3) 隐身费用 50
输入您要购买的药水数量，或按“q”退出： 2
您购买了一瓶速度药水。您还剩下 11 金币。

这是我们今天的选择：
0) 治疗费用 20 
1) 法力费用 30 
2) 速度费用 12 
3) 隐身费用 50
输入您要购买的药水数量，或按“q”退出： 4
您买不起。

以下是我们今天的选择：
0) 治疗费用 20 
1) 法力费用 30 
2) 速度费用 12 
3) 隐形费用 50
输入您要购买的药水数量，或按“q”退出：q

您的库存包含：
2x 速度药水
1x 隐形药水
您逃脱时还剩下 11 金币。

感谢您在 Roscoe 的药水商店购物！
```

玩家开始时拥有随机数量的金币，介于 80 到 120 之间。

听起来很有趣？让我们开始吧！因为一次性实现起来很困难，所以我们将分步实施。

#### 步骤#1

创建一个`Potion`包含枚举的命名空间，枚举`Type`包含药水类型。创建两个`std::array`：一个`int`数组用于保存药水成本，另一个`std::string_view`数组用于保存药水名称。

还编写一个名为的函数`shop()`，枚举列表`Potions`并打印它们的编号、名称和成本。

该程序应输出以下内容：

```
Here is our selection for today:
0) healing costs 20
1) mana costs 30
2) speed costs 12
3) invisibility costs 50
```

```cpp
#include <array>
#include <iostream>
#include <string_view>

namespace Potion
{
    enum Type
    {
    healing,
    mana,
    speed,
    invisibility,
    max_potions
    };

    constexpr std::array types { healing, mana, speed, invisibility }; // An array of our enumerators

    // We could put these in a struct, but since we only have two attributes we'll keep them separate for now
    // We will explicitly define the element type so we don't have to use the sv suffix
    constexpr std::array<std::string_view, max_potions> name { "healing", "mana", "speed", "invisibility" };
    constexpr std::array cost { 20, 30, 12, 50 };

    static_assert(std::size(types) == max_potions);  // ensure 'all' contains the correct number of enumerators
    static_assert(std::size(cost) == max_potions);
    static_assert(std::size(name) == max_potions);
}

void shop()
{
    std::cout << "Here is our selection for today:\n";

    for (auto p: Potion::types)
        std::cout << p << ") " << Potion::name[p] << " costs " << Potion::cost[p] << '\n';
}

int main()
{
    shop();

    return 0;
}
```

#### 步骤#2

创建一个`Player`类来存储玩家的姓名、药水库存和金币。为 Roscoe 的商店添加介绍和告别文字。获取玩家的姓名并随机化他们的金币。

使用课 8.15 中的“Random.h”文件[——全局随机数（Random.h）](https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/#RandomH)可以轻松实现随机化。

该程序应输出以下内容：

```
Welcome to Roscoe's potion emporium!
Enter your name: Alex
Hello, Alex, you have 84 gold.

Here is our selection for today:
0) healing costs 20
1) mana costs 30
2) speed costs 12
3) invisibility costs 50

Thanks for shopping at Roscoe's potion emporium!
```

```cpp
#include <array>
#include <iostream>
#include <string_view>
#include "Random.h"

namespace Potion
{
    enum Type
    {
        healing,
        mana,
        speed,
        invisibility,
        max_potions
    };

    constexpr std::array types { healing, mana, speed, invisibility }; // An array of our enumerators

    // We could put these in a struct, but since we only have two attributes we'll keep them separate for now
    // We will explicitly define the element type so we don't have to use the sv suffix
    constexpr std::array<std::string_view, max_potions> name { "healing", "mana", "speed", "invisibility" };
    constexpr std::array cost { 20, 30, 12, 50 };

    static_assert(std::size(types) == max_potions);  // ensure 'all' contains the correct number of enumerators
    static_assert(std::size(cost) == max_potions);
    static_assert(std::size(name) == max_potions);
}

class Player
{
private:
    static constexpr int s_minStartingGold { 80 };
    static constexpr int s_maxStartingGold { 120 };

    std::string m_name {};
    int m_gold {};
    std::array<int, Potion::max_potions> m_inventory { };

public:
    explicit Player(std::string_view name) :
        m_name { name },
        m_gold { Random::get(s_minStartingGold, s_maxStartingGold) }
    {
    }

    int gold() const { return m_gold; }
    int inventory(Potion::Type p) const { return m_inventory[p]; }
};

void shop()
{
    std::cout << "Here is our selection for today:\n";

    for (auto p: Potion::types)
        std::cout << p << ") " << Potion::name[p] << " costs " << Potion::cost[p] << '\n';
}

int main()
{
    std::cout << "Welcome to Roscoe's potion emporium!\n";
    std::cout << "Enter your name: ";

    std::string name{};
    std::getline(std::cin >> std::ws, name); // read a full line of text into name

    Player player { name };

    std::cout << "Hello, " << name << ", you have " << player.gold() << " gold.\n\n";

    shop();

    std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";

    return 0;
}
```

#### 步骤#3

添加购买药水的功能，处理无效输入（将任何无关输入视为失败）。在玩家离开后打印玩家的库存。完成此步骤后程序应该已完成。

确保测试以下情况：

- User enters an invalid potion number (e.g. ‘d’)
- User enters a valid potion number but with extraneous input (e.g. `2d`, `25`)

我们在第 9.5 课中介绍了无效输入处理[——std::cin 和处理无效输入](https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/)。

```cpp
#include <array>
#include <iostream>
#include <limits> // for std::numeric_limits
#include <string_view>
#include "Random.h"

namespace Potion
{
    enum Type
    {
        healing,
        mana,
        speed,
        invisibility,
        max_potions
    };

    constexpr std::array types { healing, mana, speed, invisibility }; // An array of our enumerators

    // We could put these in a struct, but since we only have two attributes we'll keep them separate for now
    // We will explicitly define the element type so we don't have to use the sv suffix
    constexpr std::array<std::string_view, max_potions> name { "healing", "mana", "speed", "invisibility" };
    constexpr std::array cost { 20, 30, 12, 50 };

    static_assert(std::size(types) == max_potions);  // ensure 'all' contains the correct number of enumerators
    static_assert(std::size(cost) == max_potions);
    static_assert(std::size(name) == max_potions);
}

class Player
{
private:
    static constexpr int s_minStartingGold { 80 };
    static constexpr int s_maxStartingGold { 120 };

    std::string m_name {};
    int m_gold {};
    std::array<int, Potion::max_potions> m_inventory { };

public:
    explicit Player(std::string_view name) :
        m_name { name },
        m_gold { Random::get(s_minStartingGold, s_maxStartingGold) }
    {
    }

    // returns false if can't afford, true if purchased
    bool buy(Potion::Type type)
    {
        if (m_gold < Potion::cost[type])
            return false;

        m_gold -= Potion::cost[type];
        ++m_inventory[type];
        return true;
    }

    int gold() const { return m_gold; }
    int inventory(Potion::Type p) const { return m_inventory[p]; }
};

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int charNumToInt(char c)
{
    return c - '0';
}

Potion::Type whichPotion()
{
    std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";
    char input{};
    while (true)
    {
        std::cin >> input;
        if (!std::cin)
        {
            std::cin.clear(); // put us back in 'normal' operation mode
            ignoreLine(); // and remove the bad input
            continue;
        }

        // If there is extraneous input, treat as failure case
        if (!std::cin.eof() && std::cin.peek() != '\n')
        {
            std::cout << "I didn't understand what you said.  Try again: ";
            ignoreLine(); // ignore any extraneous input
            continue;
        }

        if (input == 'q')
            return Potion::max_potions;

        // Convert the char to a number and see if it's a valid potion selection
        int val { charNumToInt(input) };
        if (val >= 0 && val < Potion::max_potions)
            return static_cast<Potion::Type>(val);

        // It wasn't a valid potion selection
        std::cout << "I didn't understand what you said.  Try again: ";
        ignoreLine();
    }
}

void shop(Player &player)
{
    while (true)
    {
        std::cout << "Here is our selection for today:\n";

        for (auto p: Potion::types)
            std::cout << p << ") " << Potion::name[p] << " costs " << Potion::cost[p] << '\n';

        Potion::Type which { whichPotion() };
        if (which == Potion::max_potions)
            return;

        bool success { player.buy(which) };
        if (!success)
            std::cout << "You can not afford that.\n\n";
        else
            std::cout << "You purchased a potion of " << Potion::name[which] << ".  You have " << player.gold() << " gold left.\n\n";
    }
}

void printInventory(Player& player)
{
    std::cout << "Your inventory contains: \n";

    for (auto p: Potion::types)
    {
        if (player.inventory(p) > 0)
            std::cout << player.inventory(p) << "x potion of " << Potion::name[p] << '\n';
    }

    std::cout << "You escaped with " << player.gold() << " gold remaining.\n";
}

int main()
{
    std::cout << "Welcome to Roscoe's potion emporium!\n";
    std::cout << "Enter your name: ";

    std::string name{};
    std::cin >> name;

    Player player { name };

    std::cout << "Hello, " << name << ", you have " << player.gold() << " gold.\n\n";

    shop(player);

    std::cout << '\n';

    printInventory(player);

    std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";

    return 0;
}
```

### 问题 #3

假设我们想编写一款使用标准纸牌的纸牌游戏。为了做到这一点，我们需要某种方式来表示这些纸牌和纸牌组。让我们构建该功能。

我们将在下一个测验问题中使用它来实际实现游戏。

#### 步骤#1

一副牌有 52 张不同的牌（4 种花色，13 个牌号）。为牌号（A、2、3、4、5、6、7、8、9、10、J、Q、K）和花色（梅花、方块、红心、黑桃）创建枚举。

```cpp
// Because identifiers can't start with a number, we'll use a "rank_" prefix for these
enum Rank
{
    rank_ace,
    rank_2,
    rank_3,
    rank_4,
    rank_5,
    rank_6,
    rank_7,
    rank_8,
    rank_9,
    rank_10,
    rank_jack,
    rank_queen,
    rank_king,

    max_ranks
};

// We'll also prefix these for consistency
enum Suit
{
    suit_club,
    suit_diamond,
    suit_heart,
    suit_spade,

    max_suits
};
```

#### 步骤#2

每张牌将由一个包含等级和花色成员的结构体表示`Card`。创建结构体并将枚举移入其中。

```cpp
struct Card
{
    enum Rank
    {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,

        max_ranks
    };

    enum Suit
    {
        suit_club,
        suit_diamond,
        suit_heart,
        suit_spade,

        max_suits
    };

    Rank rank{};
    Suit suit{};
};
```

#### 步骤#3

接下来，让我们为 Card 结构添加一些有用的函数。首先，重载`operator<<`以 2 个字母的代码打印卡片等级和花色（例如，黑桃 J 将打印为 JS）。您可以通过完成以下函数来实现这一点：

```cpp
struct Card
{
    // Your other stuff here

    friend std::ostream& operator<<(std::ostream& out, const Card &card)
    {
        out << // print your card rank and suit here
        return out;
    }
};
```

其次，添加一个返回牌面值的函数。将 A 视为值 11。最后，添加`std::array`Rank 和 Suit（分别命名为`allRanks`和`allSuits`），以便可以对它们进行迭代。由于它们是结构（而不是命名空间）的一部分，因此将它们设为静态，以便它们仅被实例化一次（而不是每个对象都实例化一次）。

以下内容应编译：

```cpp
int main()
{
    // Print one card
    Card card { Card::rank_5, Card::suit_heart };
    std::cout << card << '\n';

    // Print all cards
    for (auto suit : Card::allSuits)
        for (auto rank : Card::allRanks)
            std::cout << Card { rank, suit } << ' ';
    std::cout << '\n';

    return 0;
}
```

并产生以下输出：

```
5H 
AC 2C 3C 4C 5C 6C 7C 8C 9C TC JC QC KC AD 2D 3D 4D 5D 6D 7D 8D 9D TD JD QD KD AH 2H 3H 4H 5H 6H 7H 8H 9H TH JH QH KH AS 2S 3S 4S 5S 6S 7S 8S 9S TS JS QS KS
```

```cpp
#include <array>
#include <iostream>

struct Card
{
    enum Rank
    {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,

        max_ranks
    };

    enum Suit
    {
        suit_club,
        suit_diamond,
        suit_heart,
        suit_spade,

        max_suits
    };

    // These need to be static so they are only created once per program, not once per Card
    static constexpr std::array allRanks { rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
    static constexpr std::array allSuits { suit_club, suit_diamond, suit_heart, suit_spade };

    Rank rank{};
    Suit suit{};

    friend std::ostream& operator<<(std::ostream& out, const Card &card)
    {
        static constexpr std::array ranks { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
        static constexpr std::array suits { 'C', 'D', 'H', 'S' };

        out << ranks[card.rank] << suits[card.suit];
        return out;
    }

    int value() const
    {
        static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
        return rankValues[rank];
    }
};

int main()
{
    // Print one card
    Card card { Card::rank_5, Card::suit_heart };
    std::cout << card << '\n';

    // Print all cards
    for (auto suit : Card::allSuits)
        for (auto rank : Card::allRanks)
            std::cout << Card { rank, suit } << ' ';
    std::cout << '\n';

    return 0;
}
```

#### 步骤#4

接下来，让我们创建一副牌。创建一个名为的类`Deck`，其中包含一副`std::array`牌。你可以假设一副牌有 52 张。

Deck应该具备三个功能：

首先，默认构造函数应初始化纸牌数组。您可以使用类似于上例中 main() 函数中的 ranged-for 循环来遍历所有花色和等级。

其次，添加一个`dealCard()`函数，按值返回 Deck 中的下一张牌。由于`std::array`是固定大小的数组，请考虑如何跟踪下一张牌的位置。如果 Deck 遍历完所有牌后调用此函数，则应断言此函数是否有效。

第三，编写一个`shuffle()`成员函数来洗牌。为了简化这一过程，我们将借助`std::shuffle`：

```cpp
#include <algorithm> // for std::shuffle
#include "Random.h"  // for Random::mt

    // Put this line in your shuffle function to shuffle m_cards using the Random::mt Mersenne Twister
    // This will rearrange all the Cards in the deck randomly
    std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
```

该`shuffle()`功能也应该重置，但是您正在追踪下一张牌回到牌组起点的位置。

应运行以下程序：

```cpp
int main()
{
    Deck deck{};
    std::cout << deck.dealCard() << ' ' << deck.dealCard() << ' ' << deck.dealCard() << '\n';

    deck.shuffle();
    std::cout << deck.dealCard() << ' ' << deck.dealCard() << ' ' << deck.dealCard() << '\n';

    return 0;
}
```

并产生以下输出（最后 3 张卡片应该是随机的）：

```
AC 2C 3C
2H 7H 9C
```

```cpp
#include <algorithm> // for std::shuffle
#include <array>
#include <cassert>
#include <iostream>
#include "Random.h"

struct Card
{
    enum Rank
    {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,

        max_ranks
    };

    enum Suit
    {
        suit_club,
        suit_diamond,
        suit_heart,
        suit_spade,

        max_suits
    };

    static constexpr std::array allRanks { rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
    static constexpr std::array allSuits { suit_club, suit_diamond, suit_heart, suit_spade };

    Rank rank{};
    Suit suit{};

    friend std::ostream& operator<<(std::ostream& out, const Card &card)
    {
        static constexpr std::array ranks { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
        static constexpr std::array suits { 'C', 'D', 'H', 'S' };

        out << ranks[card.rank] << suits[card.suit];
        return out;
    }

    int value() const
    {
        static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
        return rankValues[rank];
    }
};

class Deck
{
private:
    std::array<Card, 52> m_cards {};
    std::size_t m_nextCardIndex { 0 };

public:
    Deck()
    {
        std::size_t count { 0 };
        for (auto suit: Card::allSuits)
            for (auto rank: Card::allRanks)
                m_cards[count++] = Card{rank, suit};
    }

    void shuffle()
    {
        std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
        m_nextCardIndex = 0;
    }

    Card dealCard()
    {
        assert(m_nextCardIndex != 52 && "Deck::dealCard ran out of cards");
        return m_cards[m_nextCardIndex++];
    }
};

int main()
{
    Deck deck{};
    std::cout << deck.dealCard() << ' ' << deck.dealCard() << ' ' << deck.dealCard() << '\n';

    deck.shuffle();
    std::cout << deck.dealCard() << ' ' << deck.dealCard() << ' ' << deck.dealCard() << '\n';

    return 0;
}
```

### 问题 #4

好了，现在让我们使用 Card 和 Deck 来实现简化版的二十一点！如果您还不熟悉二十一点，维基百科文章中有关[二十一点](https://en.wikipedia.org/wiki/Blackjack)的内容有摘要。

以下是我们版本的二十一点游戏的规则：

- 发牌人会拿到一张牌开始（实际上，发牌人会拿到两张牌，但是其中一张是面朝下的，所以此时这并不重要）。
- 玩家开始时会得到两张牌。
- 玩家先行。
- 玩家可以反复“要牌”或“停牌”。
- 如果玩家“停牌”，则他们的回合结束，并且他们的分数根据他们已发的牌计算。
- 如果玩家“击中”，他们会得到另一张牌，并且该牌的值将添加到他们的总分中。
- 通常情况下，A 牌算作 1 或 11（以总分较高的为准）。为简单起见，我们在此将其算作 11。
- 如果玩家的分数超过 21 点，他们就会立即爆牌并输掉游戏。
- 当玩家完成后，就轮到发牌者了。
- 发牌人反复抽牌，直到分数达到 17 或更高，此时发牌人必须停止抽牌。
- 如果庄家的点数超过 21 点，庄家就会爆牌，玩家立即获胜。
- 否则，如果玩家的分数高于庄家，则玩家获胜。否则，玩家输掉游戏（为简单起见，我们将平局视为庄家获胜）。

在我们简化版的二十一点游戏中，我们不会记录玩家和庄家发了哪些特定的牌。我们只会记录玩家和庄家发的牌的总值。这样可以让事情变得更简单。

从您在之前的测验中编写的代码开始（或使用我们的参考解决方案）。

#### \> 步骤#1

创建一个名为的结构体`Player`，它将代表我们游戏中的参与者（庄家或玩家）。由于在这个游戏中我们只关心玩家的得分，所以这个结构体只需要一个成员。

编写一个函数，最终将玩一轮二十一点。目前，此函数应为庄家抽取一张随机牌，为玩家抽取两张随机牌。它应返回一个布尔值，指示谁的分数更高。

代码应输出以下内容：

```
The dealer is showing: 10
You have score: 13
You win!
The dealer is showing: 10
You have score: 8
You lose!
```

```cpp
#include <algorithm> // for std::shuffle
#include <array>
#include <cassert>
#include <iostream>
#include "Random.h"

struct Card
{
    enum Rank
    {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,

        max_ranks
    };

    enum Suit
    {
        suit_club,
        suit_diamond,
        suit_heart,
        suit_spade,

        max_suits
    };

    static constexpr std::array allRanks { rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
    static constexpr std::array allSuits { suit_club, suit_diamond, suit_heart, suit_spade };

    Rank rank{};
    Suit suit{};

    friend std::ostream& operator<<(std::ostream& out, const Card &card)
    {
        static constexpr std::array ranks { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
        static constexpr std::array suits { 'C', 'D', 'H', 'S' };

        out << ranks[card.rank] << suits[card.suit];
        return out;
    }

    int value() const
    {
        static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
        return rankValues[rank];
    }
};

class Deck
{
private:
    std::array<Card, 52> m_cards {};
    std::size_t m_nextCardIndex { 0 };

public:
    Deck()
    {
        std::size_t count { 0 };
        for (auto suit: Card::allSuits)
            for (auto rank: Card::allRanks)
                m_cards[count++] = Card{rank, suit};
    }

    void shuffle()
    {
        std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
        m_nextCardIndex = 0;
    }

    Card dealCard()
    {
        assert(m_nextCardIndex != 52 && "Deck::dealCard ran out of cards");
        return m_cards[m_nextCardIndex++];
    }
};

struct Player
{
    int score{};
};

bool playBlackjack()
{
    Deck deck{};
    deck.shuffle();

    Player dealer{ deck.dealCard().value() };

    std::cout << "The dealer is showing: " << dealer.score << '\n';

    Player player { deck.dealCard().value() + deck.dealCard().value() };

    std::cout << "You have score: " << player.score << '\n';

    return (player.score > dealer.score);
}

int main()
{
    if (playBlackjack())
    {
        std::cout << "You win!\n";
    }
    else
    {
        std::cout << "You lose!\n";
    }

    return 0;
}
```

#### 步骤#2

添加一个`Settings`包含两个常量的命名空间：玩家爆牌的值和发牌人必须停止抽牌的值。

添加处理庄家轮次的逻辑。庄家会一直抽牌，直到达到 17 点，然后必须停止。如果爆牌，玩家获胜。

以下是一些示例输出：

```
The dealer is showing: 8
You have score: 9
The dealer flips a 4D.  They now have: 12
The dealer flips a JS.  They now have: 22
The dealer went bust!
You win!
The dealer is showing: 6
You have score: 13
The dealer flips a 3D.  They now have: 9
The dealer flips a 3H.  They now have: 12
The dealer flips a 9S.  They now have: 21
You lose!
The dealer is showing: 7
You have score: 21
The dealer flips a JC.  They now have: 17
You win!
```

```cpp
#include <algorithm> // for std::shuffle
#include <array>
#include <cassert>
#include <iostream>
#include "Random.h"

struct Card
{
    enum Rank
    {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,

        max_ranks
    };

    enum Suit
    {
        suit_club,
        suit_diamond,
        suit_heart,
        suit_spade,

        max_suits
    };

    static constexpr std::array allRanks { rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
    static constexpr std::array allSuits { suit_club, suit_diamond, suit_heart, suit_spade };

    Rank rank{};
    Suit suit{};

    friend std::ostream& operator<<(std::ostream& out, const Card &card)
    {
        static constexpr std::array ranks { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
        static constexpr std::array suits { 'C', 'D', 'H', 'S' };

        out << ranks[card.rank] << suits[card.suit];
        return out;
    }

    int value() const
    {
        static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
        return rankValues[rank];
    }
};

class Deck
{
private:
    std::array<Card, 52> m_cards {};
    std::size_t m_nextCardIndex { 0 };

public:
    Deck()
    {
        std::size_t count { 0 };
        for (auto suit: Card::allSuits)
            for (auto rank: Card::allRanks)
                m_cards[count++] = Card{rank, suit};
    }

    void shuffle()
    {
        std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
        m_nextCardIndex = 0;
    }

    Card dealCard()
    {
        assert(m_nextCardIndex != 52 && "Deck::dealCard ran out of cards");
        return m_cards[m_nextCardIndex++];
    }

};

struct Player
{
    int score{};
};

namespace Settings
{
    // Maximum score before losing.
    constexpr int bust{ 21 };

    // Minium score that the dealer has to have.
    constexpr int dealerStopsAt{ 17 };
}

// Returns true if the dealer went bust. False otherwise.
bool dealerTurn(Deck& deck, Player& dealer)
{
    while (dealer.score < Settings::dealerStopsAt)
    {
        Card card { deck.dealCard() };
        dealer.score += card.value();
        std::cout << "The dealer flips a " << card << ".  They now have: " << dealer.score << '\n';
    }

    if (dealer.score > Settings::bust)
    {
        std::cout << "The dealer went bust!\n";
        return true;
    }

    return false;
}

bool playBlackjack()
{
    Deck deck{};
    deck.shuffle();

    Player dealer{ deck.dealCard().value() };

    std::cout << "The dealer is showing: " << dealer.score << '\n';

    Player player { deck.dealCard().value() + deck.dealCard().value() };

    std::cout << "You have score: " << player.score << '\n';

    if (dealerTurn(deck, dealer))
        return true;

    return (player.score > dealer.score);
}

int main()
{
    if (playBlackjack())
    {
        std::cout << "You win!\n";
    }
    else
    {
        std::cout << "You lose!\n";
    }

    return 0;
}
```

#### 步骤#3

最后，添加玩家回合的逻辑。这样游戏就完成了。

以下是一些示例输出：

```
The dealer is showing: 2
You have score: 14
(h) to hit, or (s) to stand: h
You were dealt KH.  You now have: 24
You went bust!
You lose!
The dealer is showing: 10
You have score: 9
(h) to hit, or (s) to stand: h
You were dealt TH.  You now have: 19
(h) to hit, or (s) to stand: s
The dealer flips a 3D.  They now have: 13
The dealer flips a 7H.  They now have: 20
You lose!
The dealer is showing: 7
You have score: 12
(h) to hit, or (s) to stand: h
You were dealt 7S.  You now have: 19
(h) to hit, or (s) to stand: h
You were dealt 2D.  You now have: 21
(h) to hit, or (s) to stand: s
The dealer flips a 6H.  They now have: 13
The dealer flips a QC.  They now have: 23
The dealer went bust!
You win!
```

```
庄家显示：2
您的分数：14 
(h) 要牌，或 (s) 停牌：h
您拿到的是 KH。您现在有：24
您爆牌了！
您输了！
庄家显示：10
您的分数：9 
(h) 要牌，或 (s) 停牌：h
您拿到的是 TH。您现在有：19 
(h) 要牌，或 (s) 停牌：s
庄家翻出一张 3D。他们现在有：13
庄家翻出一张 7H。他们现在有：20
您输了！
庄家显示：7
您的分数：12 
(h) 要牌，或 (s) 停牌：h
您拿到了 7S。您现在有：19 
(h) 要牌，或 (s) 停牌：h
您拿到了 2D。您现在有：21 
(h) 要牌，或 (s) 停牌：s
庄家翻出 6H。他们现在有：13 庄家翻出
QC。他们现在有：23
庄家爆牌！
您赢了！
```

```cpp
#include <algorithm> // for std::shuffle
#include <array>
#include <cassert>
#include <iostream>
#include "Random.h"

struct Card
{
    enum Rank
    {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,

        max_ranks
    };

    enum Suit
    {
        suit_club,
        suit_diamond,
        suit_heart,
        suit_spade,

        max_suits
    };

    static constexpr std::array allRanks { rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
    static constexpr std::array allSuits { suit_club, suit_diamond, suit_heart, suit_spade };

    Rank rank{};
    Suit suit{};

    friend std::ostream& operator<<(std::ostream& out, const Card &card)
    {
        static constexpr std::array ranks { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
        static constexpr std::array suits { 'C', 'D', 'H', 'S' };

        out << ranks[card.rank] << suits[card.suit];
        return out;
    }

    int value() const
    {
        static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
        return rankValues[rank];
    }
};

class Deck
{
private:
    std::array<Card, 52> m_cards {};
    std::size_t m_nextCardIndex { 0 };

public:
    Deck()
    {
        std::size_t count { 0 };
        for (auto suit: Card::allSuits)
            for (auto rank: Card::allRanks)
                m_cards[count++] = Card{rank, suit};
    }

    void shuffle()
    {
        std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
        m_nextCardIndex = 0;
    }

    Card dealCard()
    {
        assert(m_nextCardIndex != 52 && "Deck::dealCard ran out of cards");
        return m_cards[m_nextCardIndex++];
    }

};

struct Player
{
    int score{};
};

namespace Settings
{
    // Maximum score before losing.
    constexpr int bust{ 21 };

    // Minium score that the dealer has to have.
    constexpr int dealerStopsAt{ 17 };
}

bool playerWantsHit()
{
    while (true)
    {
        std::cout << "(h) to hit, or (s) to stand: ";

        char ch{};
        std::cin >> ch;

        switch (ch)
        {
            case 'h':
                return true;
            case 's':
                return false;
        }
    }
}

// Returns true if the player went bust. False otherwise.
bool playerTurn(Deck& deck, Player& player)
{
    while (player.score < Settings::bust && playerWantsHit())
    {
        Card card { deck.dealCard() };
        player.score += card.value();

        std::cout << "You were dealt " << card  << ". You now have: " << player.score << '\n';
    }

    if (player.score > Settings::bust)
    {
        std::cout << "You went bust!\n";
        return true;
    }

    return false;
}

// Returns true if the dealer went bust. False otherwise.
bool dealerTurn(Deck& deck, Player& dealer)
{
    while (dealer.score < Settings::dealerStopsAt)
    {
        Card card { deck.dealCard() };
        dealer.score += card.value();
        std::cout << "The dealer flips a " << card << ".  They now have: " << dealer.score << '\n';
    }

    if (dealer.score > Settings::bust)
    {
        std::cout << "The dealer went bust!\n";
        return true;
    }

    return false;
}

bool playBlackjack()
{
    Deck deck{};
    deck.shuffle();

    Player dealer{ deck.dealCard().value() };

    std::cout << "The dealer is showing: " << dealer.score << '\n';

    Player player { deck.dealCard().value() + deck.dealCard().value() };

    std::cout << "You have score: " << player.score << '\n';

    if (playerTurn(deck, player))
        return false;

    if (dealerTurn(deck, dealer))
        return true;

    return (player.score > dealer.score);
}

int main()
{
    if (playBlackjack())
    {
        std::cout << "You win!\n";
    }
    else
    {
        std::cout << "You lose!\n";
    }

    return 0;
}
```

### 问题 #5

a) 描述如何修改上述程序，以处理 A 等于 1 或 11 的情况。

值得注意的是，我们只跟踪卡片总数，而不是用户拥有哪些具体卡片。

一种方法是记录玩家和庄家分别拿到了多少张 A 牌（在 中`Player` `struct`，以整数表示）。如果玩家或庄家的 A 牌超过 21 点，并且他们的 A 牌计数器大于零，则可以将他们的分数减少 10（将 A 牌从 11 点转换为 1 点）并从 A 牌计数器中“移除”一分。此操作可根据需要多次执行，直到 A 牌计数器达到零。

b) 在实际的二十一点游戏中，如果玩家和庄家的分数相同（并且玩家没有爆牌），结果就是平局，双方都不会获胜。描述一下你将如何修改上述程序来解决这个问题。

我们的版本`playBlackjack()`目前返回一个布尔值，表示玩家是否获胜。我们需要更新此函数以返回三种可能性：庄家获胜、玩家获胜、平局。最好的方法是为这三个选项定义一个枚举，并让函数返回适当的枚举器。

c) 额外奖励：将上述两个想法运用到您的二十一点游戏中。请注意，您需要展示庄家的初始牌和玩家的初始两张牌，以便他们知道他们是否有 A。

以下是示例输出：

```
庄家显示 JH (10)
您显示 AH 7D (18) 
(h) 要牌，或 (s) 停牌：h
您拿到的是 JD。您现在有：18 
(h) 要牌，或 (s) 停牌：s
庄家翻出一张 6C。他们现在有：16
庄家翻出一张 AD。他们现在有：17
您赢了！
```

```cpp
#include <algorithm> // for std::shuffle
#include <array>
#include <cassert>
#include <iostream>
#include "Random.h"

struct Card
{
    enum Rank
    {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,

        max_ranks
    };

    enum Suit
    {
        suit_club,
        suit_diamond,
        suit_heart,
        suit_spade,

        max_suits
    };

    static constexpr std::array allRanks { rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, rank_10, rank_jack, rank_queen, rank_king };
    static constexpr std::array allSuits { suit_club, suit_diamond, suit_heart, suit_spade };

    Rank rank{};
    Suit suit{};

    friend std::ostream& operator<<(std::ostream& out, const Card &card)
    {
        static constexpr std::array ranks { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
        static constexpr std::array suits { 'C', 'D', 'H', 'S' };

        out << ranks[card.rank] << suits[card.suit];
        return out;
    }

    int value() const
    {
        static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
        return rankValues[rank];
    }
};

class Deck
{
private:
    std::array<Card, 52> m_cards {};
    std::size_t m_nextCardIndex { 0 };

public:
    Deck()
    {
        std::size_t count { 0 };
        for (auto suit: Card::allSuits)
            for (auto rank: Card::allRanks)
                m_cards[count++] = Card{rank, suit};
    }

    void shuffle()
    {
        std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
        m_nextCardIndex = 0;
    }

    Card dealCard()
    {
        assert(m_nextCardIndex != 52 && "Deck::dealCard ran out of cards");
        return m_cards[m_nextCardIndex++];
    }

};

class Player
{
private:
    int m_score{ };
    int m_aceCount { 0 };

public:
    // We'll use a function to add the card to the player's score
    // Since we now need to count aces
    void addToScore(Card card)
    {
        m_score += card.value();
        if (card.rank == Card::rank_ace)
            ++m_aceCount;
    }

    void consumeAces(int maxScore)
    {
        while (m_score > maxScore && m_aceCount > 0)
        {
            m_score -= 10;
            --m_aceCount;
        }
    }

    int score() { return m_score; }
};

namespace Settings
{
    // Maximum score before losing.
    constexpr int bust{ 21 };

    // Minium score that the dealer has to have.
    constexpr int dealerStopsAt{ 17 };
}

bool playerWantsHit()
{
    while (true)
    {
        std::cout << "(h) to hit, or (s) to stand: ";

        char ch{};
        std::cin >> ch;

        switch (ch)
        {
            case 'h':
                return true;
            case 's':
                return false;
        }
    }
}

// Returns true if the player went bust. False otherwise.
bool playerTurn(Deck& deck, Player& player)
{
    while (player.score() < Settings::bust && playerWantsHit())
    {
        Card card { deck.dealCard() };
        player.addToScore(card);
        player.consumeAces(Settings::bust);

        std::cout << "You were dealt " << card  << ". You now have: " << player.score() << '\n';
    }

    if (player.score() > Settings::bust)
    {
        std::cout << "You went bust!\n";
        return true;
    }

    return false;
}


// Returns true if the dealer went bust. False otherwise.
bool dealerTurn(Deck& deck, Player& dealer)
{
    while (dealer.score() < Settings::dealerStopsAt)
    {
        Card card { deck.dealCard() };
        dealer.addToScore(card);
        dealer.consumeAces(Settings::bust);

        std::cout << "The dealer flips a " << card << ".  They now have: " << dealer.score() << '\n';
    }

    if (dealer.score() > Settings::bust)
    {
        std::cout << "The dealer went bust!\n";
        return true;
    }

    return false;
}

enum class GameResult
{
    playerWon,
    dealerWon,
    tie
};

GameResult playBlackjack()
{
    Deck deck{};
    deck.shuffle();

    Player dealer{};
    Card card1 { deck.dealCard() };
    dealer.addToScore(card1);
    std::cout << "The dealer is showing " << card1 << " (" << dealer.score() << ")\n";

    Player player{};
    Card card2 { deck.dealCard() };
    Card card3 { deck.dealCard() };
    player.addToScore(card2);
    player.addToScore(card3);
    std::cout << "You are showing " << card2 << ' ' << card3 << " (" << player.score() << ")\n";

    if (playerTurn(deck, player)) // if player busted
        return GameResult::dealerWon;

    if (dealerTurn(deck, dealer)) // if dealer busted
        return GameResult::playerWon;

    if (player.score() == dealer.score())
        return GameResult::tie;

    return (player.score() > dealer.score() ? GameResult::playerWon : GameResult::dealerWon);
}

int main()
{
    switch (playBlackjack())
    {
    case GameResult::playerWon:
        std::cout << "You win!\n";
        return 0;
    case GameResult::dealerWon:
        std::cout << "You lose!\n";
        return 0;
    case GameResult::tie:
        std::cout << "It's a tie.\n";
        return 0;
    }

    return 0;
}
```
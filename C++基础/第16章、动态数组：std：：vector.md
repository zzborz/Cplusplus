# 第16章、动态数组：std：：vector

## 16.1 — 容器和数组简介

### 可变可扩展性的挑战

假设我们想要记录 30 名学生的考试成绩并计算全班的平均分数。为此，我们需要 30 个变量。我们可以像这样定义它们：

```cpp
// allocate 30 integer variables (each with a different name)
int testScore1 {};
int testScore2 {};
int testScore3 {};
// ...
int testScore30 {};
```

要定义很多变量！要计算班级的平均分数，我们需要执行以下操作：

```cpp
int average { (testScore1 + testScore2 + testScore3 + testScore4 + testScore5
     + testScore6 + testScore7 + testScore8 + testScore9 + testScore10
     + testScore11 + testScore12 + testScore13 + testScore14 + testScore15
     + testScore16 + testScore17 + testScore18 + testScore19 + testScore20
     + testScore21 + testScore22 + testScore23 + testScore24 + testScore25
     + testScore26 + testScore27 + testScore28 + testScore29 + testScore30)
     / 30; };
```

这不仅需要大量输入，而且非常重复（而且很容易打错一个数字而不被注意到）。如果我们想对每个值进行任何操作（例如将它们打印到屏幕上），我们必须重新输入每个变量的名称。

现在假设我们需要修改程序以适应刚刚加入班级的另一名学生。我们必须扫描整个代码库并手动添加相关内容。每次修改现有代码时，都有可能引入新的错误。例如，在计算从到 的`testScore31`平均值时，很容易忘记从`30、31`更新除数！

这还只是 30 个变量的情况。想想我们有数百或数千个对象的情况。当我们需要多个相同类型的对象时，定义单个变量根本无法扩展。

我们可以将数据放入结构体中：

```cpp
struct testScores
{
// allocate 30 integer variables (each with a different name)
int score1 {};
int score2 {};
int score3 {};
// ...
int score30 {};
}
```

虽然这为我们的分数提供了一些额外的组织（并允许我们更轻松地将它们传递给函数），但它并不能解决核心问题：我们仍然需要单独定义和访问每个测试分数对象。

你可能已经猜到了，C++ 已经为上述挑战提供了解决方案。在本章中，我们将介绍一种这样的解决方案。在接下来的章节中，我们将探索该解决方案的其他一些变体。

### 容器

当你去杂货店买一打鸡蛋时，你（可能）不会单独挑选 12 个鸡蛋并将它们放入购物车（你不会，对吧？）。相反，你很可能会选择一盒鸡蛋。纸盒是一种容器，可容纳预定数量的鸡蛋（可能是 6、12 或 24 个）。现在考虑早餐麦片，其中包含许多小块麦片。你肯定不想将所有这些小块单独存放在食品储藏室中！麦片通常装在盒子里，这是另一种容器。我们在现实生活中一直使用容器，因为它们可以轻松管理物品集合。

容器也存在于编程中，以便于创建和管理（可能很大的）对象集合。在一般编程中，**容器**是一种数据类型，用于存储一组未命名的对象（称为**元素**）。

**关键见解**

**当我们需要处理一组相关值时，我们通常使用容器。**

事实证明，您已经使用了一种容器类型：字符串！字符串容器为字符集合提供存储，然后可以将其输出为文本：

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name{ "Alex" }; // strings are a container for characters
    std::cout << name; // output our string as a sequence of characters

    return 0;
}
```

### 容器的元素未命名

虽然容器对象本身通常有一个名称（否则我们将如何使用它？），但容器的元素是未命名的。这样我们就可以根据需要将任意数量的元素放入容器中，而不必为每个元素赋予唯一的名称！缺乏命名元素很重要，这也是容器与其他类型的数据结构的区别所在。这就是为什么普通结构（那些只是数据成员集合的结构，如`testScores`上面的结构）通常不被视为容器的原因——它们的数据成员需要唯一的名称。

在上面的例子中，我们的字符串容器有一个名称（`name`），但是容器内的字符（`'A'`，`'l'`，`'e'`，`'x'`）却没有。

但是如果元素本身没有命名，我们如何访问它们？每个容器都提供一种或多种方法来访问其元素——但具体方法取决于容器的类型。我们将在下一课中看到第一个例子。

**关键见解**

**容器的元素没有自己的名字，这样容器可以拥有任意数量的元素，而不必赋予每个元素唯一的名称。**

**每个容器都提供了一些方法来访问这些元素，但如何访问取决于容器的具体类型。**

### 容器的长度

在编程中，容器中元素的数量通常称为其**长度**（有时称为**计数**）。

在第 5.9课[——std::string 简介](https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring/)中，我们展示了如何使用`length`成员函数`std::string`来获取字符串容器中的字符元素的数量：

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name{ "Alex" };
    std::cout << name << " has " << name.length() << " characters\n";

    return 0;
}
```

这将打印：

```cpp
Alex has 4 characters
```

在 C++ 中，术语“ **size** ”也常用于表示容器中的元素数量。这是一个不太恰当的命名选择，因为术语“size”也可以指对象使用的内存字节数（由运算符返回`sizeof`）。

当指代容器中元素的数量时，我们更喜欢使用术语“长度”，而使用术语“大小”来指代对象所需的存储量。

### 集装箱作业

让我们回到鸡蛋盒上。你能用这样的纸盒做什么？首先，你可以得到一盒鸡蛋。你可以打开鸡蛋盒，选择一个鸡蛋，然后对这个鸡蛋做任何你想做的事情。你可以从纸盒中取出一个现有的鸡蛋，或者在空的地方放一个新鸡蛋。你还可以计算纸盒中鸡蛋的数量。

类似地，容器通常实现以下操作的重要子集：

- 创建一个容器（例如空的，用于存储来自值列表的一些初始数量的元素）。
- 访问元素（例如获取第一个元素、获取最后一个元素、获取任何元素）。
- 插入和删除元素。
- 获取容器中元素的数量。

容器还可以提供其他操作（或上述操作的变体）来协助管理元素集合。

现代编程语言通常提供各种不同的容器类型。这些容器类型在它们实际支持的操作以及这些操作的性能方面有所不同。例如，一种容器类型可能提供对容器中任何元素的快速访问，但不支持插入或删除元素。另一种容器类型可能提供快速插入和删除元素，但只允许按顺序访问元素。

每个容器都有其优点和局限性。为要解决的任务选择正确的容器类型会对代码的可维护性和整体性能产生巨大影响。我们将在以后的课程中进一步讨论这个主题。

### 元素类型

在大多数编程语言（包括 C++）中，容器都是**同质的**，这意味着容器的元素需要具有相同的类型。

一些容器使用预设的元素类型（例如，字符串通常具有`char`元素），但更多时候，元素类型可以由容器的用户设置。在 C++ 中，容器通常实现为类模板，以便用户可以提供所需的元素类型作为模板类型参数。我们将在下一课中看到一个例子。

这使得容器变得灵活，因为我们不需要为每种不同的元素类型创建新的容器类型。相反，我们只需使用所需的元素类型实例化类模板，就可以开始了。

**顺便说一下……**

**同质容器的对立面是异构容器，它允许元素属于不同类型。异构容器通常由脚本语言（例如 Python）支持。**

### C++ 中的容器

**Containers 库**是C++ 标准库的一部分，其中包含实现一些常见容器类型的各种类类型。实现容器的类类型有时称为**容器类**。Containers 库中容器的完整列表[在此处](https://en.cppreference.com/w/cpp/container)列出。

在 C++ 中，“容器”的定义比一般的编程定义要窄。在 C++ 中，只有 Containers 库中的类类型才被视为容器。我们在一般谈论容器时使用术语“容器”，在具体谈论属于 Containers 库的容器类类型时使用术语“容器类”。

**对于高级读者**

**以下类型是通用编程定义下的容器，但 C++ 标准不将其视为容器：**

- **C 风格数组**
- **`std::string`**
- **`std::vector<bool>`**

**[要成为 C++ 中的容器，容器必须实现此处](https://en.cppreference.com/w/cpp/named_req/Container)列出的所有要求。请注意，这些要求包括某些成员函数的实现 - 这意味着 C++ 容器必须是类类型！上面列出的类型并未实现所有这些要求。**

**然而，由于`std::string`和`std::vector<bool>`实现了大部分要求，它们在大多数情况下表现得像容器。因此，它们有时被称为“伪容器”。**

在提供的容器类中，`std::vector`和`std::array`是目前使用最多的，也是我们关注的重点。其他容器类通常只在更特殊的情况下使用。

### 数组简介

数组是一种容器数据类型，用于**连续**存储一系列值（这意味着每个元素都放置在相邻的内存位置，没有间隙）。数组允许快速、直接访问任何元素。它们**概念**简单且易于使用，因此当我们需要创建和使用一组相关值时，它们是首选。

C++ 包含三种主要数组类型：（C 风格）数组、`std::vector`容器类和`std::array`容器类。

(C 风格) 数组是从 C 语言继承而来的。为了向后兼容，这些数组被定义为核心 C++ 语言的一部分（与基本数据类型非常相似）。C++ 标准将这些称为“数组”，但在现代 C++ 中，它们通常被称为**C 数组**或**C 风格数组，**以将它们与名称相似的数组区分开来`std::array`。C 风格数组有时也被称为“裸数组”、“固定大小数组”、“固定数组”或“内置数组”。我们更喜欢使用术语“C 风格数组”，并在讨论数组类型时使用“数组”。按照现代标准，C 风格数组的行为很奇怪并且很危险。我们将在以后的章节中探讨原因。

为了使数组在 C++ 中更安全、更易于使用，`std::vector`C++03 中引入了容器类。`std::vector`是三种数组类型中最灵活的，并且具有其他数组类型所没有的一系列有用功能。

最后，`std::array`C++11 引入了容器类，直接替代 C 风格数组。它比 更受限制`std::vector`，但效率也更高，尤其是对于较小的数组。

所有这些数组类型在现代 C++ 中仍然以不同的方式使用，因此我们将不同程度地介绍这三种类型。

**作者注**

**关于术语的简要说明：**

- **`container classes`当我们谈论适用于大多数或所有标准库容器类的内容时，我们将会使用它。**
- **`array`当我们谈论通常适用于所有数组类型（甚至是用其他编程语言实现的数组类型）的东西时，我们就会使用它。**

**`std::vector`属于这两个类别，因此即使我们可能使用不同的术语，它仍然适用于`std::vector`。**

## 16.2 — std::vector 和 list 构造函数简介

### 简介`std::vector`

`std::vector`是 C++ 标准容器库中实现数组的容器类之一。`std::vector`在 <vector> 标头中定义为类模板，带有定义元素类型的模板类型参数。因此，`std::vector<int>`声明一个`std::vector`元素类型为 的`int`。

实例化一个`std::vector`对象很简单：

```cpp
#include <vector>

int main()
{
	// Value initialization (uses default constructor)
	std::vector<int> empty{}; // vector containing 0 int elements

	return 0;
}
```

变量`empty`定义为`std::vector`元素类型为 的`int`。因为我们在这里使用了值初始化，所以我们的向量将从空开始（即没有元素）。

没有元素的向量现在看起来可能没什么用，但我们在以后的课程中会再次遇到它（特别是[16.11 - std::vector 和堆栈行为](https://www.learncpp.com/cpp-tutorial/stdvector-and-stack-behavior/)）。

### `std::vector`使用值列表初始化

由于容器的目标是管理一组相关值，因此我们通常会希望使用这些值来初始化容器。我们可以通过使用列表初始化和我们想要的特定初始化值来实现这一点。例如：

```cpp
#include <vector>

int main()
{
	// List construction (uses list constructor)
	std::vector<int> primes{ 2, 3, 5, 7 };          // vector containing 4 int elements with values 2, 3, 5, and 7
	std::vector vowels { 'a', 'e', 'i', 'o', 'u' }; // vector containing 5 char elements with values 'a', 'e', 'i', 'o', and 'u'.  Uses CTAD (C++17) to deduce element type char (preferred).

	return 0;
}
```

使用`primes`，我们明确指定我们想要一个 ，`std::vector`其元素类型为`int`。因为我们提供了 4 个初始化值，所以`primes`将包含 4 个元素，其值分别为`2`、`3`、`5`和`7`。

对于`vowels`，我们没有明确指定元素类型。相反，我们使用 C++17 的 CTAD（类模板参数推导）让编译器从初始化器中推导元素类型。因为我们提供了 5 个初始化值，所以`vowels`将包含 5 个元素，其值分别为`'a'`、`'e'`、`'i'`、`'o'`和`'u'`。

### 列出构造函数和初始化程序列表

让我们更详细地讨论一下上述工作原理。

在课[13.8 -- 结构聚合初始化](https://www.learncpp.com/cpp-tutorial/struct-aggregate-initialization/)中，我们将初始化列表定义为以逗号分隔的值的括号列表（例如`{ 1, 2, 3 }`）。

容器通常有一个特殊的构造函数，称为**列表构造函数**，它允许我们使用初始化列表构造容器的实例。列表构造函数执行三件事：

- 确保容器有足够的存储空间来保存所有初始化值（如果需要）。
- 将容器的长度设置为初始化列表中的元素数（如果需要）。
- 将元素初始化为初始化列表中的值（按顺序）。

因此，当我们为容器提供一个初始化值列表时，就会调用列表构造函数，并使用该值列表构造容器！

**最佳实践**

**使用带有初始化值列表的列表初始化来构造具有这些元素值的容器。**

### 使用下标运算符（operator[]）访问数组元素

现在我们已经创建了一个元素数组……我们如何访问它们？

我们先打个比方。考虑一组并排的相同邮箱。为了更容易识别邮箱，每个邮箱的前面都画有一个数字。第一个邮箱的编号为 0，第二个邮箱的编号为 1，等等……所以如果有人告诉你把东西放在 0 号邮箱里，你就知道这意味着第一个邮箱。

在 C++ 中，访问数组元素的最常见方法是使用数组名称和下标运算符 ( `operator[]`)。要选择特定元素，请在下标运算符的方括号内提供一个整数值，该整数值标识我们要选择的元素。此整数值称为**下标**（或非正式地称为**索引**）。与我们的邮箱非常相似，使用索引 0 访问第一个元素，使用索引 1 访问第二个元素，等等……

例如，`primes[0]`将从数组中返回具有索引的元素`0`（第一个元素）`prime`。下标运算符返回对实际元素的引用，而不是副本。一旦我们访问了数组元素，我们就可以像普通对象一样使用它（例如为其分配一个值，输出它等……）

因为索引从 0 开始，而不是从 1 开始，所以我们说 C++ 中的数组是**从零开始的**。这可能会造成混淆，因为我们习惯从 1 开始计数对象。

**关键见解**

**索引实际上是与数组第一个元素的距离（偏移量）。**

**如果你从数组的第一个元素开始，然后移动 0 个元素，你仍然在第一个元素上。因此索引 0 是第一个元素。**

**如果你从数组的第一个元素开始，然后移动 1 个元素，那么现在你位于第二个元素。因此索引 1 是第二个元素。**

**[我们在第17.9 课——指针运算和下标]中讨论了索引是相对距离（而不是绝对位置）**

这也会导致一些语言歧义，因为当我们谈论数组元素 1 时，可能不清楚我们是在谈论第一个数组元素（索引为 0）还是第二个数组元素（索引为 1）。通常，我们会根据位置而不是索引来谈论数组元素（因此“第一个元素”是索引为 0 的元素）。

以下是一个例子：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector primes { 2, 3, 5, 7, 11 }; // hold the first 5 prime numbers (as int)

    std::cout << "The first prime number is: " << primes[0] << '\n';
    std::cout << "The second prime number is: " << primes[1] << '\n';
    std::cout << "The sum of the first 5 primes is: " << primes[0] + primes[1] + primes[2] + primes[3] + primes[4] << '\n';

    return 0;
}
```

```
The first prime number is: 2
The second prime number is: 3
The sum of the first 5 primes is: 28
```

通过使用数组，我们不再需要定义 5 个不同名称的变量来保存 5 个素数。相反，我们可以定义一个`primes`包含 5 个元素的数组 ()，只需更改索引值即可访问不同的元素！

`operator[]`我们将在下一课[16.3——std::vector 和无符号长度和下标问题](https://www.learncpp.com/cpp-tutorial/stdvector-and-the-unsigned-length-and-subscript-problem/)中进一步讨论以及访问数组元素的一些其他方法。

### 下标越界

在索引数组时，提供的索引必须选择数组的有效元素。也就是说，对于长度为 N 的数组，下标必须是 0 到 N-1（含）之间的值。

`operator[]`不进行任何类型的**边界检查**，这意味着它不会检查索引是否在 0 到 N-1（含）的范围内。传递无效索引将`operator[]`返回未定义的行为。

记住不要使用负下标是相当容易的。但记住没有索引为 N 的元素就没那么容易了！数组的最后一个元素的索引为 N-1，因此使用索引 N 将导致编译器尝试访问数组末尾后面一个元素。

**提示**

**在一个有 N 个元素的数组中，第一个元素的索引为 0，第二个元素的索引为 1，最后一个元素的索引为 N-1。没有索引为 N 的元素！**

**使用 N 作为下标将导致未定义的行为（因为这实际上是试图访问第 N+1 个元素，它不是数组的一部分）。**

**提示**

**某些编译器（如 Visual Studio）提供运行时断言，以表明索引有效。在这种情况下，如果在调试模式下提供了无效索引，程序将断言。在发布模式下，断言会被编译出来，因此不会影响性能。**

### 数组在内存中是连续的

数组的定义特征之一是元素在内存中总是连续分配，这意味着元素在内存中都是相邻的（它们之间没有间隙）。

举例来说：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector primes { 2, 3, 5, 7, 11 }; // hold the first 5 prime numbers (as int)

    std::cout << "An int is " << sizeof(int) << " bytes\n";
    std::cout << &(primes[0]) << '\n';
    std::cout << &(primes[1]) << '\n';
    std::cout << &(primes[2]) << '\n';

    return 0;
}
```

在作者的机器上，上述程序运行一次产生以下结果：

```
一个 int 是 4 个字节
00DBF720 
00DBF724 
00DBF728
```

`int`您会注意到这些 int 元素的内存地址相隔 4 个字节，与作者机器上的大小相同。

这意味着数组没有任何每个元素的开销。它还允许编译器快速计算数组中任何元素的地址。

数组是少数允许**随机访问**的容器类型之一，这意味着可以直接访问容器中的任何元素（与顺序访问相反，顺序访问必须按特定顺序访问元素）。随机访问数组元素通常很高效，并且使数组非常易于使用。这就是为什么数组通常比其他容器更受欢迎的主要原因。

### 构造`std::vector`特定长度的

考虑一下我们希望用户输入 10 个值并将它们存储在 中的情况`std::vector`。在这种情况下，我们需要一个`std::vector`长度为 10 的 ，然后才能将任何值放入 中`std::vector`。我们该如何解决这个问题？

我们可以创建一个`std::vector`并使用具有 10 个占位符值的初始化列表来初始化它：

```cpp
std::vector<int> data { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // vector containing 10 int values
```

但这样做有很多弊端。它需要大量输入。不容易看出有多少个初始化器。而且如果我们稍后决定要使用不同数量的值，也不容易更新。

幸运的是，`std::vector`有一个显式的构造函数（`explicit std::vector<T>(std::size_t)`），它采用单个`std::size_t`值来定义要构造的长度`std::vector`：

```cpp
std::vector<int> data( 10 ); // vector containing 10 int elements, value-initialized to 0
```

每个创建的元素都经过值初始化，对于类类型则`int`执行零初始化（对于类类型则调用默认构造函数）。

但是，使用此构造函数有一个不太明显的地方：必须使用直接初始化来调用它。

### 列表构造函数优先于其他构造函数

要理解为什么必须使用直接初始化来调用以前的构造函数，请考虑以下定义：

```cpp
std::vector<int> data{ 10 }; // what does this do?
```

有两个不同的构造函数与此初始化匹配：

- `{ 10 }`可以解释为一个初始化列表，并与列表构造函数匹配，构造一个长度为 1、值为 10 的向量。
- `{ 10 }`可以被解释为一个单括号初始化值，并与`std::vector<T>(std::size_t)`构造函数匹配，构造一个长度为 10 的向量，其元素值初始化为 0。

通常，当类类型定义与多个构造函数匹配时，该匹配被视为不明确，并会导致编译错误。但是，C++ 针对这种情况有一个特殊规则：将选择匹配的列表构造函数而不是其他匹配的构造函数。如果没有此规则，列表构造函数将导致与任何采用单一类型参数的构造函数不明确匹配。

由于`{ 10 }`可以解释为初始化列表并且`std::vector`具有列表构造函数，因此在这种情况下列表构造函数优先。

**关键见解**

**当构造一个类类型对象时，会从其他匹配的构造函数中选择一个匹配的列表构造函数。**

为了进一步阐明各种初始化情况下发生的情况，让我们看看使用复制、直接和列表初始化的类似情况：

```cpp
// Copy init
std::vector<int> v1 = 10;     // 10 not an initializer list, copy init won't match explicit constructor: compilation error

// Direct init
std::vector<int> v2(10);      // 10 not an initializer list, matches explicit single-argument constructor

// List init
std::vector<int> v3{ 10 };    // { 10 } interpreted as initializer list, matches list constructor

// Copy list init
std::vector<int> v4 = { 10 }; // { 10 } interpreted as initializer list, matches list constructor
std::vector<int> v5({ 10 });  // { 10 } interpreted as initializer list, matches list constructor
```

如果`v1`， 的初始化值`10`不是初始化列表，因此列表构造函数不匹配。单参数构造函数`explicit std::vector<T>(std::size_t)`也不匹配，因为复制初始化与显式构造函数不匹配。由于没有构造函数匹配，因此这是一个编译错误。

如果`v2`， 的初始化值`10`不是初始化列表，因此列表构造函数不匹配。单参数构造函数`explicit std::vector<T>(std::size_t)`匹配，因此选择单参数构造函数。

在`v3`(列表初始化) 的情况下，`{ 10 }`可以与列表构造函数或匹配`explicit std::vector<T>(std::size_t)`。列表构造函数优先于其他匹配的构造函数并被选中。

如果`v4`(复制列表初始化)，`{ 10 }`则可以与列表构造函数匹配（这是一个非显式构造函数，因此可以与复制初始化一起使用）。选择列表构造函数。

令人惊讶的是， Case`v5`是复制列表初始化（而不是直接初始化）的替代语法，并且与 相同`v4`。

这是 C++ 初始化的一个缺陷：`{ 10 }`如果存在列表构造函数，则匹配列表构造函数；如果不存在列表构造函数，则匹配单参数构造函数。这意味着您获得的行为取决于是否存在列表构造函数！您通常可以假设容器具有列表构造函数。

总而言之，列表初始化器通常旨在允许我们使用元素值列表初始化容器，并且应该用于此目的。无论如何，这在大多数情况下都是我们想要的。因此，如果是元素值，`{ 10 }`则适用。如果是容器非列表构造函数的参数，则使用直接初始化。`10``10`

**最佳实践**

**当使用非元素值的初始化器构造容器（或任何具有列表构造函数的类型）时，请使用直接初始化。**

<u>提示</u>

<u>当 a是类类型的成员时，如何提供一个默认初始化程序将 a 的长度设置为某个初始值`std::vector`并不明显：`std::vector`</u>

```cpp
#include <vector>

struct Foo
{
    std::vector<int> v1(8); // compile error: direct initialization not allowed for member default initializers
};
```

<u>这不起作用，因为成员默认初始化器不允许直接（括号）初始化。</u>

<u>为类类型的成员提供默认初始化程序时：</u>

- <u>我们必须使用复制初始化或列表初始化（直接或复制）。</u>
- <u>不允许 CTAD（所以我们必须明确指定元素类型）。</u>

<u>答案如下：</u>

```cpp
struct Foo
{
    std::vector<int> v{ std::vector<int>(8) }; // ok
};
```

<u>这将创建一个`std::vector`容量为 8 的，然后使用它作为 的初始化器`v`。</u>

### Const 和 constexpr`std::vector`

`std::vector`可以制作以下类型的对象`const`：

```cpp
#include <vector>

int main()
{
    const std::vector<int> prime { 2, 3, 5, 7, 11 }; // prime and its elements cannot be modified

    return 0;
}
```

必须初始化A `const std::vector`，然后不能修改。此类向量的元素将被视为 const。

a 的元素类型`std::vector`不能定义为 const（例如`std::vector<const int>`不允许）。

**关键见解**

**根据[Howard Hinnant 在此处的评论](https://stackoverflow.com/questions/6954906/does-c11-allow-vectorconst-t#comment8294604_6955332)，标准库容器并非设计为具有 const 元素。**

**容器的 const-ness 来自于容器本身的 const-ing，而不是元素。**

的最大缺点之一`std::vector`是它不能被制作`constexpr`。如果需要`constexpr`数组，请使用`std::array`。

### 为什么称之为矢量呢？

当人们在谈话中使用“矢量”一词时，他们通常指的是几何矢量，即具有大小和方向的对象。那么，`std::vector`既然它不是几何矢量，它的名字又是怎么来的呢？

在《从数学到泛型编程》一书中，Alexander Stepanov 写道：“STL 中的向量这个名称取自早期的编程语言 Scheme 和 Common Lisp。不幸的是，这与该术语在数学中更古老的含义不一致……这种数据结构应该称为数组。不幸的是，如果你犯了一个错误并违反了这些原则，结果可能会持续很长时间。”

因此，从根本上来说，`std::vector`这个名字是错误的，但是现在更改它已经太晚了。

### **测验**

#### 问题 #1

使用 CTAD定义一个`std::vector`并用前 5 个正平方数（1、4、9、16 和 25）初始化它。

```cpp
std::vector squares{ 1, 4, 9, 16, 25 };
```

#### 问题 #2

这两个定义之间的行为差异是什么？

```cpp
std::vector<int> v1 { 5 };
std::vector<int> v2 ( 5 );
```

`v1`调用列表构造函数定义一个包含值的 1 个元素向量`5`。
`v2`调用非列表构造函数定义一个 5 个元素向量，其元素均按值初始化。

#### 问题 #3

定义一个`std::vector`（使用显式模板类型参数）来保存一年中每一天的最高温度（精确到十分之一度）（假设一年有 365 天）。

```cpp
std::vector<double> temperature (365); // create a vector to hold 365 double values
```

#### 问题 #4

使用`std::vector`编写一个程序，要求用户输入 3 个整数值。打印这些值的和与乘积。

输出应与以下内容匹配：

```
输入 3 个整数：3 4 5
总和为：12
乘积为：60
```

```cpp
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> arr(3); // create a vector of length 3

	std::cout << "Enter 3 integers: ";
	std::cin >> arr[0] >> arr[1] >> arr[2];

	std::cout << "The sum is: " << arr[0] + arr[1] + arr[2] << '\n';
	std::cout << "The product is: " << arr[0] * arr[1] * arr[2] << '\n';

	return 0;
}
```

## 16.3 — std::vector 和无符号长度和下标问题

在上一课[16.2 -- std::vector 和 list 构造函数介绍](https://www.learncpp.com/cpp-tutorial/introduction-to-stdvector-and-list-constructors/)中，我们介绍了`operator[]`，它可以用来对数组进行下标操作来访问其中的元素。

在本课中，我们将研究访问数组元素的其他方法，以及获取容器类的长度（容器类中当前元素的数量）的几种不同方法。

但在这样做之前，我们需要讨论 C++ 设计者所犯的一个重大错误，以及它如何影响 C++ 标准库中的所有容器类。

### 集装箱长度标志问题

让我们先来断言一下：数组下标使用的数据类型应该与存储数组长度使用的数据类型相匹配。这样，最长的数组中的所有元素都可以被索引，而不会超过这个范围。

Bjarne Stroustrup[回忆道](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1428r0.pdf)，在设计 C++ 标准库中的容器类时（大约 1997 年），设计人员必须选择将长度（和数组下标）设置为有符号的还是无符号的。他们选择了无符号的。

给出的原因是：标准库数组类型的下标不能为负数，使用无符号类型由于额外的位而允许更长的数组（这在 16 位时代很重要），并且范围检查下标需要一个条件检查而不是两个（因为不需要检查来确保索引小于 0）。

回想起来，这通常被认为是错误的选择。我们现在明白，使用无符号值来尝试强制非负性是行不通的，这是因为隐式转换规则（因为负有符号整数只会隐式转换为较大的无符号整数，从而产生垃圾结果），32 位或 64 位系统通常不需要额外的范围位（因为您可能不会创建包含超过 20 亿个元素的数组），而且常用的`operator[]`无论如何都不会进行范围检查。

在课程[4.5 — 无符号整数以及为什么要避免使用它们](https://www.learncpp.com/cpp-tutorial/unsigned-integers-and-why-to-avoid-them/)中，我们讨论了为什么我们更喜欢使用有符号值来保存数量。我们还注意到，混合有符号值和无符号值会导致意外行为。因此，标准库容器类使用无符号值作为长度（和索引）这一事实是有问题的，因为这使得在使用这些类型时无法避免使用无符号值。

目前，我们只能面对这个选择以及它所导致的不必要的复杂性。

### 回顾：符号转换是收缩转换，除了 constexpr

在我们继续学习之前，让我们快速回顾一下第[10.4 课中的一些材料——缩小转换、列表初始化和 constexpr 初始化器](https://www.learncpp.com/cpp-tutorial/narrowing-conversions-list-initialization-and-constexpr-initializers/)中有关符号转换（从有符号到无符号或反之亦然的整数转换）的内容，因为我们将在本章中大量讨论这些内容。

符号转换被视为收缩转换，因为有符号或无符号类型无法容纳相反类型范围内的所有值。当在运行时执行此类转换时，编译器将在不允许收缩转换的上下文中发出错误（例如在列表初始化中），并且在执行此类转换的其他上下文中可能会或可能不会发出警告。

例如：

```cpp
#include <iostream>

void foo(unsigned int)
{
}

int main()
{
    int s { 5 };

    [[maybe_unused]] unsigned int u { s }; // compile error: list initialization disallows narrowing conversion
    foo(s);                                // possible warning: copy initialization allows narrowing conversion

    return 0;
}
```

在上面的例子中，变量的初始化`u`会产生编译错误，因为在进行列表初始化时不允许进行收缩转换。对的调用`foo()`执行复制初始化，这确实允许收缩转换，并且可能会或可能不会产生警告，具体取决于编译器产生符号转换警告的积极程度。例如，当`-Wsign-conversion`使用编译器标志时，GCC 和 Clang 都会在这种情况下产生警告。

但是，如果要进行符号转换的值是 constexpr，并且可以转换为相反类型的等效值，则符号转换不被*视为*收缩。这是因为编译器可以保证转换是安全的，否则将停止编译过程。

```cpp
#include <iostream>

void foo(unsigned int)
{
}

int main()
{
    constexpr int s { 5 };                 // now constexpr
    [[maybe_unused]] unsigned int u { s }; // ok: s is constexpr and can be converted safely, not a narrowing conversion
    foo(s);                                // ok: s is constexpr and can be converted safely, not a narrowing conversion

    return 0;
}
```

在这种情况下，由于`s`是 `constexpr`，并且要转换的值（`5`）可以表示为无符号值，因此转换不被视为缩小，并且可以隐式执行而不会出现问题。

我们将经常使用这种非缩小的 `constexpr` 转换（从`constexpr int`到`constexpr std::size_t`）。

### std::vector的长度和索引具有类型`size_type` 

在课程[10.7 -- 类型定义和类型别名](https://www.learncpp.com/cpp-tutorial/typedefs-and-type-aliases/)中，我们提到类型定义和类型别名通常用于需要为可能变化的类型命名的情况（例如，因为它是实现定义的）。例如，`std::size_t`是某些大型无符号整数类型的类型定义，通常`unsigned long`是 或`unsigned long long`。

每个标准库容器类都定义了一个嵌套的 typedef 成员名为`size_type`（有时写为`T::size_type`），它是用于容器长度（和索引，如果支持的话）的类型的别名。

您通常会`size_type`在文档和编译器警告/错误消息中看到 。例如，的[成员函数](https://en.cppreference.com/w/cpp/container/vector/size)的此[文档`size()`](https://en.cppreference.com/w/cpp/container/vector/size)`std::vector`表示`size()`返回 的值`size_type`。

`size_type`几乎总是 的别名`std::size_t`，但可以被覆盖（在极少数情况下）以使用不同类型。

**关键见解**

**`size_type`是在标准库容器类中定义的嵌套 typedef，用作容器类的长度（和索引，如果支持的话）的类型。**

**`size_type`默认为`std::size_t`，并且由于它几乎从未改变，我们可以合理地假设`size_type`是 的别名`std::size_t`。**

<u>对于高级读者</u>

<u>所有标准库容器除了`std::array`使用[`std::allocator`](https://en.cppreference.com/w/cpp/memory/allocator)来分配内存之外。对于这些容器，`T::size_type`是从所`size_type`用分配器的 派生出来的。由于`std::allocator`最多可以分配`std::size_t`字节的内存，`std::allocator<T>::size_type`定义为`std::size_t`。因此，`T::size_type`默认为`std::size_t`。</u>

<u>只有在自定义分配器`T::size_type`被定义为 以外的其他东西的情况下，`std::size_t`容器才会`T::size_type`是 以外的其他东西`std::size_t`。这种情况很少见，并且是在每个应用程序的基础上完成的，因此通常可以安全地假设`T::size_type`将是 ，`std::size_t`除非您的应用程序正在使用这样的自定义分配器（如果是这种情况，您会知道）。</u>

访问`size_type`容器类的成员时，我们必须使用容器类的完全模板名称来限定其范围。例如，`std::vector<int>::size_type`。

### std::vector`使用`size()`成员函数或获取的长度`std::size()

`size()`我们可以使用成员函数（以无符号形式返回长度）询问容器类对象其长度`size_type`：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime { 2, 3, 5, 7, 11 };
    std::cout << "length: " << prime.size() << '\n'; // returns length as type `size_type` (alias for `std::size_t`)
    return 0;
}
```

这将打印：

```
长度：5
```

`std::string`与和不同`std::string_view`，它们同时具有`length()`和`size()`成员函数（它们执行相同的操作），而`std::vector`（以及 C++ 中的大多数其他容器类型）只有`size()`。现在您明白了为什么容器的长度有时会被含糊地称为其大小。

在 C++17 中，我们还可以使用`std::size()`非成员函数（对于容器类来说，它只调用`size()`成员函数）。

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime { 2, 3, 5, 7, 11 };
    std::cout << "length: " << std::size(prime); // C++17, returns length as type `size_type` (alias for `std::size_t`)

    return 0;
}
```

<u>对于高级读者</u>

<u>因为`std::size()`也可以用于非衰减的 C 风格数组，所以有时比使用`size()`成员函数更倾向于使用此方法（特别是在编写可以接受容器类或非衰减的 C 风格数组参数的函数模板时）。</u>

<u>我们在第 17.8 课——C 风格数组衰减中讨论[C 风格数组衰减](https://www.learncpp.com/cpp-tutorial/c-style-array-decay/)。</u>

如果我们想使用上述任一方法将长度存储在有符号类型的变量中，这可能会导致有符号/无符号转换警告或错误。这里最简单的做法是将结果 static_cast 为所需类型：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime { 2, 3, 5, 7, 11 };
    int length { static_cast<int>(prime.size()) }; // static_cast return value to int
    std::cout << "length: " << length ;

    return 0;
}
```

### std::vector`使用C++20获取的长度`std::ssize()

C++20 引入了`std::ssize()`非成员函数，它将长度作为大的*有符号*整数类型返回（通常为`std::ptrdiff_t`，这是通常用作 的有符号对应部分的类型`std::size_t`）：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };
    std::cout << "length: " << std::ssize(prime); // C++20, returns length as a large signed integral type

    return 0;
}
```

这是三个函数中唯一一个以有符号类型返回长度的函数。

如果您想使用此方法将长度存储在具有符号类型的变量中，则您有几个选择。

首先，因为`int`类型可能小于返回的有符号类型`std::ssize()`，所以如果要将长度分配给变量`int`，则应该将结果 static_cast 为`int`以使任何此类转换显式（否则您可能会收到缩小转换警告或错误）：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };
    int length { static_cast<int>(std::ssize(prime)) }; // static_cast return value to int
    std::cout << "length: " << length;

    return 0;
}
```

或者，您可以使用`auto`编译器推断出要用于变量的正确符号类型：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };
    auto length { std::ssize(prime) }; // use auto to deduce signed type, as returned by std::ssize()
    std::cout << "length: " << length;

    return 0;
}
```

### 使用访问数组元素`operator[]`不进行边界检查

在上一课中，我们介绍了下标运算符（`operator[]`）：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::cout << prime[3];  // print the value of element with index 3 (7)
    std::cout << prime[9]; // invalid index (undefined behavior)

    return 0;
}
```

`operator[]`不进行边界检查。operator[] 的索引可以是非 const 的。我们将在后面的部分进一步讨论这一点。

使用成员函数访问数组元素`at()`会进行运行时边界检查

数组容器类支持另一种访问数组的方法。`at()`成员函数可用于通过运行时边界检查进行数组访问：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::cout << prime.at(3); // print the value of element with index 3
    std::cout << prime.at(9); // invalid index (throws exception)

    return 0;
}
```

在上面的例子中，对 的调用`prime.at(3)`检查以确保索引 3 有效，并且由于有效，它返回对数组元素 3 的引用。然后我们可以打印此值。但是，对 的调用`prime.at(9)`失败（在运行时），因为 9 不是此数组的有效索引。该`at()`函数不会返回引用，而是生成终止程序的错误。

<u>对于高级读者</u>

<u>当`at()`成员函数遇到越界索引时，它实际上会抛出 类型的异常`std::out_of_range`。如果不处理该异常，程序将终止。我们将在[第 27 章](https://www.learncpp.com/#Chapter27)中介绍异常及其处理方法。</u>

就像一样`operator[]`，传递给的索引`at()`可以是非 const 的。

因为它在每次调用时都会进行运行时边界检查，`at()`所以比 慢（但更安全）`operator[]`。尽管不太安全，`operator[]`但通常比 更常用`at()`，主要是因为在索引之前进行边界检查更好，所以我们首先不会尝试使用无效索引。

### `std::vector`使用 c`onstexpr` 有符号整数进行索引

`std::vector`当使用 `constexpr` `(signed) int`索引 a 时，我们可以让编译器将其隐式转换为 a `std::size_t`，而无需进行缩小转换：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::cout << prime[3] << '\n';     // okay: 3 converted from int to std::size_t, not a narrowing conversion

    constexpr int index { 3 };         // constexpr
    std::cout << prime[index] << '\n'; // okay: constexpr index implicitly converted to std::size_t, not a narrowing conversion

    return 0;
}
```

`std::vector`使用非 `constexpr` 值进行索引

用于索引数组的下标可以是非 const 的：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::size_t index { 3 };           // non-constexpr
    std::cout << prime[index] << '\n'; // operator[] expects an index of type std::size_t, no conversion required

    return 0;
}
```

但是，根据我们的最佳实践（[4.5——无符号整数，以及为什么要避免使用它们](https://www.learncpp.com/cpp-tutorial/unsigned-integers-and-why-to-avoid-them/)），我们通常要避免使用无符号类型来保存数量。

当我们的下标是一个非 `constexpr` 有符号值时，我们会遇到问题：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    int index { 3 };                   // non-constexpr
    std::cout << prime[index] << '\n'; // possible warning: index implicitly converted to std::size_t, narrowing conversion

    return 0;
}
```

在此示例中，`index`是非 `constexpr` 有符号整数。`operator[]`定义为 的一部分的下标`std::vector`具有类型`size_type`（ 的别名`std::size_t`）。因此，当我们调用 时`prime[index]`，我们的有符号整数必须转换为`std::size_t`。

这样的转换不应该是危险的（因为 a 的索引`std::vector`应该是非负的，并且非负有符号值将安全地转换为无符号值）。但是在运行时执行时，这被视为收缩转换，并且您的编译器应该发出警告，指出这是一种不安全的转换（如果没有，您应该考虑修改警告以使其发出警告）。

由于数组下标很常见，并且每次这样的转换都会生成警告，这很容易使你的编译日志充斥着虚假警告。或者，如果你启用了“将警告视为错误”，它将停止你的编译。

有很多方法可以避免这个问题（例如，每次索引数组时都将`static_cast`其`int`转换为 a `std::size_t`），但所有这些方法最终都会以某种方式使代码变得混乱或复杂。在这种情况下，最简单的方法是使用 std::size_t 类型的变量作为索引，并且不要将此变量用于除索引之外的任何用途。这样，您首先就可以避免任何非 `constexpr` 转换。

### 提示

另一个好的选择是，不索引其`std::vector`本身，而是索引成员函数的结果`data()`：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    int index { 3 };                          // non-constexpr signed value
    std::cout << prime.data()[index] << '\n'; // okay: no sign conversion warnings

    return 0;
}
```



在底层，`std::vector`它将其元素保存在 C 样式数组中。`data()`成员函数返回指向此底层 C 样式数组的指针，然后我们可以对其进行索引。由于 C 样式数组允许使用有符号和无符号类型进行索引，因此我们不会遇到任何符号转换问题。我们将在课程[17.7 — C 样式数组简介](https://www.learncpp.com/cpp-tutorial/introduction-to-c-style-arrays/)和[17.8 — C 样式数组衰减](https://www.learncpp.com/cpp-tutorial/c-style-array-decay/)中进一步讨论 C 样式数组。

### 测验时间

#### 问题 #1

`std::vector`使用以下值初始化 a ：'h'、'e'、'l'、'l'、'o'。然后打印数组的长度（使用`std::size()`）。最后，使用下标运算符和成员函数打印索引为 1 的元素的值`at()`。

该程序应输出以下内容：

```
The array has 5 elements.
ee
```

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector arr { 'h', 'e', 'l', 'l', 'o' };
    std::cout << "The array has " << std::size(arr) << " elements.\n";
    std::cout << arr[1] << arr.at(1) << '\n';

    return 0;
}
```

#### 问题 #2

a) 它是什么`size_type`以及它有何用途？

`size_type`是一个嵌套的 typedef，它是用于存储标准库容器的长度（和索引，如果支持的话）的类型的别名。

b) 默认类型是什么`size_type`？是有符号的还是无符号的？

`std::size_t`，它是无符号类型。

c) 哪些函数可以获取容器返回的长度`size_type`？

成员函数`size()`和`std::size`都返回`size_type`。

## 16.4 — 传递 std::vector

类型的对象`std::vector`可以像任何其他对象一样传递给函数。这意味着如果我们`std::vector`按值传递，则会进行昂贵的复制。因此，我们通常`std::vector`通过 (const) 引用传递以避免此类复制。

对于 a 来说`std::vector`，元素类型是对象类型信息的一部分。因此，当我们使用 a`std::vector`作为函数参数时，我们必须明确指定元素类型：

```c++
#include <iostream>
#include <vector>

void passByRef(const std::vector<int>& arr) // we must explicitly specify <int> here
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes);

    return 0;
}
```

传递`std::vector`不同的元素类型

因为我们的`passByRef()`函数需要一个`std::vector<int>`，所以我们无法传递具有不同元素类型的向量：

```cpp
#include <iostream>
#include <vector>

void passByRef(const std::vector<int>& arr)
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes);  // ok: this is a std::vector<int>

    std::vector dbl{ 1.1, 2.2, 3.3 };
    passByRef(dbl); // compile error: std::vector<double> is not convertible to std::vector<int>

    return 0;
}
```

在 C++17 或更新版本中，您可以尝试使用 CTAD 来解决此问题：

```c++
#include <iostream>
#include <vector>

void passByRef(const std::vector& arr) // compile error: CTAD can't be used to infer function parameters
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 }; // okay: use CTAD to infer std::vector<int>
    passByRef(primes);

    return 0;
}
```

尽管 CTAD 会在定义向量时从初始化器中推断出向量元素的类型，但 CTAD 目前还不适用于函数参数。

我们以前见过这种问题，即我们重载了仅在参数类型上不同的函数。这是使用函数模板的好地方！我们可以创建一个参数化元素类型的函数模板，然后 C++ 将使用该函数模板实例化具有实际类型的函数。

我们可以创建一个使用相同模板参数声明的函数模板：

```cpp
#include <iostream>
#include <vector>

template <typename T>
void passByRef(const std::vector<T>& arr)
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes); // ok: compiler will instantiate passByRef(const std::vector<int>&)

    std::vector dbl{ 1.1, 2.2, 3.3 };
    passByRef(dbl);    // ok: compiler will instantiate passByRef(const std::vector<double>&)

    return 0;
}
```

在上面的例子中，我们创建了一个名为的单函数模板`passByRef()`，它有一个名为 的参数类型`const std::vector<T>&`。`T`它在上一行的模板参数声明中定义：`template <typename T`。`T`是一个标准类型模板参数，允许调用者指定元素类型。

因此，当我们调用`passByRef(primes)`from `main()`（其中`primes`定义为`std::vector<int>`）时，编译器将实例化并调用`void passByRef(const std::vector<int>& arr)`。

当我们调用`passByRef(dbl)`from `main()`（其中`dbl`定义为`std::vector<double>`）时，编译器将实例化并调用`void passByRef(const std::vector<double>& arr)`。

因此，我们创建了一个单一函数模板，可以实例化函数来处理`std::vector`任何元素类型和长度的参数！
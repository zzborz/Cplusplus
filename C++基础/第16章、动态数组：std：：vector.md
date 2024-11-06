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

### 传递`std::vector`不同的元素类型

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

### 传递`std::vector`使用通用模板或缩写函数模板

我们还可以创建一个接受任何类型对象的函数模板：

```cpp
#include <iostream>
#include <vector>

template <typename T>
void passByRef(const T& arr) // will accept any type of object that has an overloaded operator[]
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

在 C++20 中，我们可以使用缩写函数模板（通过`auto`参数）来做同样的事情：

```cpp
#include <iostream>
#include <vector>

void passByRef(const auto& arr) // abbreviated function template
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



*这两个函数都可以接受任何*可以编译的类型的参数。当我们编写函数时，我们可能想要操作的不仅仅是 a ，这很有必要`std::vector`。例如，上面的函数也可以操作 a `std::array`、 a `std::string`，或者我们可能甚至没有考虑过的其他类型。

该方法的潜在缺点是，如果向函数传递一个编译但语义上没有意义的类型的对象，则可能会导致错误。

### 断言数组长度

考虑以下模板函数，它与上面介绍的函数类似：

```cpp
#include <iostream>
#include <vector>

template <typename T>
void printElement3(const std::vector<T>& arr)
{
    std::cout << arr[3] << '\n';
}

int main()
{
    std::vector arr{ 9, 7, 5, 3, 1 };
    printElement3(arr);

    return 0;
}
```



虽然在`printElement3(arr)`这种情况下运行良好，但这个程序中有一个潜在的错误，等待着粗心的程序员。看到了吗？

上述程序打印索引为 3 的数组元素的值。只要数组具有索引为 3 的有效元素，这就可以了。但是，编译器很乐意让您传入索引 3 超出范围的数组。例如：

```cpp
#include <iostream>
#include <vector>

template <typename T>
void printElement3(const std::vector<T>& arr)
{
    std::cout << arr[3] << '\n';
}

int main()
{
    std::vector arr{ 9, 7 }; // a 2-element array (valid indexes 0 and 1)
    printElement3(arr);

    return 0;
}
```

这会导致未定义的行为。

这里的一个选项是断言`arr.size()`，它将在调试构建配置中运行时捕获此类错误。由于`std::vector::size()`是非 constexpr 函数，因此我们只能在此处执行运行时断言。

**提示**

**更好的选择是避免`std::vector`在需要断言数组长度的情况下使用。使用支持`constexpr`数组的类型（例如`std::array`）可能是更好的选择，因为您可以断言 `constexpr` 数组的长度。我们将在以后的课程[17.3——传递和返回 std::array]`static_assert`中介绍这一点。**

最好的选择是避免编写依赖于用户首先传递具有最小长度的向量的函数。

### 测验时间

#### 问题 #1

编写一个函数，该函数接受两个参数：a`std::vector`和索引。如果索引超出范围，则打印错误。如果索引在范围内，则打印元素的值。

以下示例程序应该可以编译：

```cpp
#include <iostream>
#include <vector>

// Write your printElement function here

int main()
{
    std::vector v1 { 0, 1, 2, 3, 4 };
    printElement(v1, 2);
    printElement(v1, 5);

    std::vector v2 { 1.1, 2.2, 3.3 };
    printElement(v2, 0);
    printElement(v2, -1);

    return 0;
```

```
The element has value 2
Invalid index
The element has value 1.1
Invalid index
```

```cpp
#include <iostream>
#include <vector>

// index needs to be an int, not a std::size_t, otherwise we won't be able to detect if the user passes in a negative index
template <typename T>
void printElement(const std::vector<T>& arr, int index)
{
    if (index < 0 || index >= static_cast<int>(arr.size())) // In C++20, could use std::ssize(arr) to avoid the cast
        std::cout << "Invalid index\n";
    else
        std::cout << "The element has value " << arr[static_cast<std::size_t>(index)] << '\n';
}

int main()
{
    std::vector v1 { 0, 1, 2, 3, 4 };
    printElement(v1, 2);
    printElement(v1, 5);

    std::vector v2 { 1.1, 2.2, 3.3 };
    printElement(v2, 0);
    printElement(v2, -1);

    return 0;
}
```

## 16.5 — 返回 std::vector，并介绍移动语义

当我们需要将一个传递`std::vector`给函数时，我们通过（const）引用传递它，这样我们就不会对数组数据进行昂贵的复制。

因此，您可能会惊讶地发现`std::vector`按值返回是可以的。

### 复制语义

考虑以下程序：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector arr1 { 1, 2, 3, 4, 5 }; // copies { 1, 2, 3, 4, 5 } into arr1
    std::vector arr2 { arr1 };          // copies arr1 into arr2

    arr1[0] = 6; // We can continue to use arr1
    arr2[0] = 7; // and we can continue to use arr2

    std::cout << arr1[0] << arr2[0] << '\n';

    return 0;
}
```

当`arr2`用 初始化时`arr1`， 的复制构造函数`std::vector`被调用，该复制构造函数复制`arr1`到 中`arr2`。

在这种情况下，制作副本是唯一合理的做法，因为我们需要`arr1`和`arr2`独立存在。此示例最终制作了两个副本，每个初始化一个副本。

术语**“复制语义”**是指确定如何复制对象的规则。当我们说某个类型支持复制语义时，我们的意思是该类型的对象是可复制的，因为制作此类复制的规则已经定义。当我们说正在调用复制语义时，这意味着我们已经做了一些将复制对象的事情。

对于类类型，复制语义通常通过复制构造函数（和复制赋值运算符）实现，它定义了如何复制该类型的对象。通常，这会导致复制类类型的每个数据成员。在前面的示例中，该语句`std::vector arr2 { arr1 };`调用复制语义，从而调用 的复制构造函数`std::vector`，然后将 的每个数据成员复制`arr1`到 中`arr2`。最终结果是`arr1`等同于（但独立于）`arr2`。

### 当复制语义不是最佳时

现在考虑这个相关的例子：

```cpp
#include <iostream>
#include <vector>

std::vector<int> generate() // return by value
{
    // We're intentionally using a named object here so mandatory copy elision doesn't apply
    std::vector arr1 { 1, 2, 3, 4, 5 }; // copies { 1, 2, 3, 4, 5 } into arr1
    return arr1;
}

int main()
{
    std::vector arr2 { generate() }; // the return value of generate() dies at the end of the expression

    // There is no way to use the return value of generate() here
    arr2[0] = 7; // we only have access to arr2

    std::cout << arr2[0] << '\n';

    return 0;
}
```

`arr2`这次初始化时，它是使用从函数返回的临时对象进行初始化的`generate()`。与之前的情况不同，在之前的情况下，初始化器是一个可以在将来的语句中使用的左值，而在这种情况下，临时对象是一个右值，将在初始化表达式的末尾被销毁。临时对象不能在该点之后使用。因为临时对象（及其数据）将在表达式的末尾被销毁，所以我们需要某种方法将数据从临时对象中取出并放入`arr2`。

这里通常要做的事情与上一个示例相同：使用复制语义并进行可能昂贵的复制。这样就`arr2`可以获得自己的数据副本，即使临时文件（及其数据）被销毁后也可以使用。

但是，这种情况与上一个示例的不同之处在于，临时文件无论如何都会被销毁。初始化完成后，临时文件不再需要其数据（这就是我们可以销毁它的原因）。我们不需要两组数据同时存在。在这种情况下，制作可能昂贵的副本然后销毁原始数据并不是最理想的选择。

### 移动语义简介

相反，如果有一种方法可以`arr2`“窃取”临时数据而不是复制它，会怎么样？`arr2`那么将成为数据的新所有者，并且不需要复制数据。 当数据的所有权从一个对象转移到另一个对象时，我们说数据已被**移动**。 这种移动的成本通常微不足道（通常只有两三个指针赋值，这比复制数据数组要快得多！）。

另外一个好处是，当临时变量在表达式末尾被销毁时，它将不再有任何数据需要销毁，因此我们也不必付出这种代价。

**这就是移动语义**的本质，它指的是确定数据如何从一个对象移动到另一个对象的规则。当调用移动语义时，任何可以移动的数据成员都会被移动，而任何不能移动的数据成员都会被复制。移动数据而不是复制数据的能力可以使移动语义比复制语义更高效，尤其是当我们可以用廉价的移动代替昂贵的复制时。

**关键见解**

**移动语义是一种优化，它允许我们在某些情况下以低成本将某些数据成员的所有权从一个对象转移到另一个对象（而不是进行更昂贵的复制）。**

**无法移动的数据成员将被复制。**

### 如何调用移动语义

通常，当使用相同类型的对象初始化（或分配）对象时，将使用复制语义（假设复制没有被省略）。

但是，当以下所有情况都为真时，将调用移动语义：

- 该对象的类型支持移动语义。
- 正在使用相同类型的右值（临时）对象初始化（或分配）。
- 此举并未被省略。

坏消息是：支持移动语义的类型并不多。不过，`std::vector`两者`std::string`都支持！

### `std::vector`我们可以按值返回可移动类型

因为按值返回会返回一个右值，所以如果返回的类型支持移动语义，则可以移动返回值，而不是将其复制到目标对象中。这使得按值返回对于这些类型来说非常便宜！

**关键见解**

**我们可以通过值返回可移动类型（如`std::vector`和`std::string`）。此类类型将以低成本移动其值，而不是进行昂贵的复制。**

**此类类型仍应通过 const 引用传递。**

### 复制成本高的类型不应该通过值传递，但如果它们具有移动能力，那么它们可以通过值返回吗？

正确的。

以下讨论是可选的，但可以帮助您理解为什么会出现这种情况。

我们在 C++ 中做的最常见事情之一是将一个值传递给某个函数，然后返回不同的值。当传递的值是类类型时，该过程涉及 4 个步骤：

1. 构造要传递的值。
2. 实际将值传递给函数。
3. 构造要返回的值。
4. 实际上是将返回值传回给调用者。

以下是使用上述过程的一个示例`std::vector`：

```cpp
#include <iostream>
#include <vector>

std::vector<int> doSomething(std::vector<int> v2)
{
    std::vector v3 { v2[0] + v2[0] }; // 3 -- construct value to be returned to caller
    return v3; // 4 -- actually return value
}

int main()
{
    std::vector v1 { 5 }; // 1 -- construct value to be passed to function
    std::cout << doSomething(v1)[0] << '\n'; // 2 -- actually pass value

    std::cout << v1[0] << '\n';

    return 0;
}
```

首先，我们假设`std::vector`它不具备移动功能。在这种情况下，上述程序会生成 4 个副本：

1. 构造要传递的值将初始化列表复制到`v1`
2. 实际上将值传递给函数是将参数复制`v1`到函数参数中`v2`。
3. 构造要返回的值将初始化器复制到`v3`
4. 实际上将返回给调用者的值复制`v3`回给调用者。

现在让我们讨论如何优化上述内容。我们有很多工具可供使用：通过引用或地址传递、省略、移动语义和输出参数。

我们根本无法优化副本 1 和 3。我们需要`std::vector`将一个传递给函数，并且我们需要一个`std::vector`返回 - 这些对象必须被构造。`std::vector`是其数据的所有者，因此它必然会复制其初始化程序。

我们能够影响的是副本 2 和 4。

进行复制 2 是因为我们将值从调用者传递到被调用函数。我们还有什么其他选择？

- 我们可以通过引用或地址传递吗？可以。我们可以保证参数在整个函数调用期间都存在——调用者不必担心传递的对象意外超出范围。
- 可以省略此复制吗？不可以。省略仅在进行冗余复制或移动时有效。此处没有冗余复制或移动。
- 我们可以在这里使用输出参数吗？不可以。我们正在向函数传递一个值，而不是取回一个值。
- 我们可以在这里使用移动语义吗？不可以。参数是左值。如果我们将数据从移动`v1`到`v2`，`v1`将变成一个空向量，随后的打印`v1[0]`将导致未定义的行为。

显然，通过 const 引用传递是我们这里最好的选择，因为它避免了复制，避免了空指针问题，并且适用于左值和右值参数。

进行复制 4 是因为我们将值从被调用函数传递回调用者。这里我们还有什么其他选择？

- 我们可以通过引用或地址返回吗？不可以。我们返回的对象是作为函数内部的局部变量创建的，并将在函数返回时被销毁。返回引用或指针将导致调用者收到悬空指针或引用。
- 可以省略此副本吗？是的，有可能。如果编译器很聪明，它会意识到我们正在被调用函数的范围内构造一个对象并返回它。通过重写代码（在 as-if 规则下），使其`v3`在调用方的范围内构造，我们可以避免在返回时进行的复制。但是，我们依赖于编译器意识到它可以做到这一点，因此不能保证。
- 我们可以在这里使用 out 参数吗？可以。`v3`我们可以在调用方的范围内构造一个空对象，并通过非常量引用将其传递给函数，而不是构造为局部变量`std::vector`。然后函数可以用数据填充此参数。当函数返回时，此对象仍将存在。这避免了复制，但也有一些明显的缺点和限制：丑陋的调用语义，不适用于不支持赋值的对象，并且编写可以同时使用左值和右值参数的此类函数具有挑战性。
- 我们可以在这里使用移动语义吗？是的。`v3`当函数返回时将被销毁，因此`v3`我们可以使用移动语义将其数据移动到调用者，而不是复制回调用者，从而避免复制。

省略是这里的最佳选择，但它是否会发生是我们无法控制的。对于可移动类型，下一个最佳选择是移动语义，它可以在编译器不省略复制的情况下使用。对于可移动类型，在按值返回时会自动调用移动语义。

总而言之，对于可移动类型，我们更喜欢通过 const 引用传递，并按值返回。

## 16.6 — 数组和循环

重新审视变量可扩展性挑战

假设我们想找出一个班学生的平均考试成绩。为了使这些例子简洁，我们假设这个班只有 5 名学生。

以下是我们利用单个变量来解决这个问题的方法：

```cpp
#include <iostream>

int main()
{
    // allocate 5 integer variables (each with a different name)
    int testScore1{ 84 };
    int testScore2{ 92 };
    int testScore3{ 76 };
    int testScore4{ 81 };
    int testScore5{ 56 };

    int average { (testScore1 + testScore2 + testScore3 + testScore4 + testScore5) / 5 };

    std::cout << "The class average is: " << average << '\n';

    return 0;
}
```

这需要很多变量和大量输入。想象一下，对于 30 名或 600 名学生，我们需要做多少工作。此外，如果添加了新的测试分数，则必须声明、初始化新变量并将其添加到平均值计算中。您是否记得更新除数？如果您忘记了，那么您现在就会出现语义错误。每当您必须修改现有代码时，您都面临着引入错误的风险。

现在，你知道当我们有一堆相关变量时，我们应该使用数组。因此，让我们用以下方法替换单个变量`std::vector`：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector testScore { 84, 92, 76, 81, 56 };
    std::size_t length { testScore.size() };

    int average { (testScore[0] + testScore[1] + testScore[2] + testScore[3] + testScore[4])
        / static_cast<int>(length) };

    std::cout << "The class average is: " << average << '\n';

    return 0;
}
```

这样更好——我们大大减少了定义的变量数量，并且平均值计算的除数现在直接由数组的长度确定。

但平均值计算仍然是一个问题，因为我们必须手动逐个列出每个元素。而且因为我们必须明确列出每个元素，所以我们的平均值计算仅适用于元素数量与我们列出的完全相同的数组。如果我们还想对其他长度的数组进行平均，我们需要为每个不同的数组长度编写一个新的平均值计算。

我们真正需要的是一种方法来访问每个数组元素，而不必明确列出每个元素。

### 数组和循环

在之前的课程中，我们注意到数组下标不必是常量表达式——它们可以是运行时表达式。这意味着我们可以使用变量的值作为索引。

还要注意，上例中平均值计算中使用的数组索引是升序序列：0、1、2、3、4。因此，如果我们有办法按顺序将变量设置为值 0、1、2、3 和 4，那么我们可以将该变量用作数组索引，而不是文字。我们已经知道如何做到这一点——使用 for 循环。

让我们使用 for 循环重写上面的例子，其中循环变量用作数组索引：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector testScore { 84, 92, 76, 81, 56 };
    std::size_t length { testScore.size() };

    int average { 0 };
    for (std::size_t index{ 0 }; index < length; ++index) // index from 0 to length-1
        average += testScore[index];                      // add the value of element with index `index`
    average /= static_cast<int>(length);                  // calculate the average

    std::cout << "The class average is: " << average << '\n';

    return 0;
}
```

这应该相当简单。`index`从 开始`0`，`testScore[0]`添加到`average`，并`index`增加到`1`。`testScore[1]`添加到`average`，并`index`增加到`2`。最终，当`index`增加到时为`5`假`index < length`，循环终止。

此时，循环已将`testScore[0]`、`testScore[1]`、`testScore[2]`、`testScore[3]`和的值添加`testScore[4]`到`average`。

最后，我们通过将累积值除以数组长度来计算平均值。![生态学](./assets/ezoicbwa-1730857601088-1.png)

这种解决方案在可维护性方面非常理想。循环迭代的次数由数组的长度决定，循环变量用于执行所有数组索引。我们不再需要手动列出每个数组元素。

如果我们想添加或删除测试分数，我们只需修改数组初始化器的数量，其余代码仍可工作而无需进一步更改！

按某种顺序访问容器中的每个元素称为**traversal**，即**遍历**容器。traversal 通常称为**iteration**，即**在容器上迭代**或**遍历**容器。

**作者注**

**由于容器类使用类型`size_t`来表示长度和索引，因此在本课中，我们将这样做。我们将在即将到来的课程[16.7 -- 数组、循环和符号挑战解决方案]中讨论使用有符号长度和索引。**

### 模板、数组和循环解锁可扩展性

数组提供了一种存储多个对象的方法，而无需命名每个元素。

循环提供了一种遍历数组的方法，而无需明确列出每个元素。

模板提供了一种参数化元素类型的方法。

模板、数组和循环共同允许我们编写可对元素容器进行操作的代码，而不管容器中的元素类型或元素数量！

为了进一步说明这一点，让我们重写上面的例子，将平均值计算重构为函数模板：

```cpp
#include <iostream>
#include <vector>

// Function template to calculate the average of the values in a std::vector
template <typename T>
T calculateAverage(const std::vector<T>& arr)
{
    std::size_t length { arr.size() };

    T average { 0 };                                      // if our array has elements of type T, our average should have type T too
    for (std::size_t index{ 0 }; index < length; ++index) // iterate through all the elements
        average += arr[index];                            // sum up all the elements
    average /= static_cast<int>(length);

    return average;
}

int main()
{
    std::vector class1 { 84, 92, 76, 81, 56 };
    std::cout << "The class 1 average is: " << calculateAverage(class1) << '\n'; // calc average of 5 ints

    std::vector class2 { 93.2, 88.6, 64.2, 81.0 };
    std::cout << "The class 2 average is: " << calculateAverage(class2) << '\n'; // calc average of 4 doubles

    return 0;
}
```

这将打印：

```
The class 1 average is: 77
The class 2 average is: 81.75
```

在上面的例子中，我们创建了函数模板`calculateAverage()`，它接受`std::vector`任意元素类型和任意长度的，并返回平均值。在中，我们演示了当使用 5 个元素的数组`int`或 4 个元素的数组`double``main()`调用此函数时，它同样有效！

`calculateAverage()`适用于支持函数内部使用的运算符（`operator+=(T)`, `operator/=(int)`）的任何类型 T。如果您尝试使用不支持这些运算符的 T，则编译器在尝试编译实例化的函数模板时会出错。

### 我们可以用数组和循环做什么

现在我们知道了如何使用循环遍历元素容器，让我们看看可以使用容器遍历的最常见用途。我们通常遍历容器以执行以下四件事之一：

1. 根据现有元素的值（例如平均值、值的总和）计算新值。
2. 搜索现有元素（例如，完全匹配、计算匹配数、查找最高值）。
3. 对每个元素进行操作（例如输出每个元素、将所有元素乘以 2）。
4. 对元素重新排序（例如，按升序对元素进行排序）。

前三个相当简单。我们可以使用单个循环来遍历数组，根据需要检查或修改每个元素。

重新排序容器中的元素要复杂得多，因为这样做通常需要在另一个循环中使用一个循环。虽然我们可以手动执行此操作，但通常最好使用标准库中的现有算法来执行此操作。我们将在以后讨论算法的章节中更详细地介绍这一点。

### 数组和 off-by-one 错误

使用索引遍历容器时，必须小心确保循环执行的次数正确。很容易出现一次错误（循环体执行的次数过多或过少）。

通常，当使用索引遍历容器时，我们将从索引处开始`0`并循环直到`index < length`。

新手程序员有时会不小心使用`index <= length`作为循环条件。这将导致循环在 时执行`index == length`，从而导致下标越界和未定义的行为。

### 测验时间

#### 问题 #1

编写一个简短的程序，使用循环将以下向量的元素打印到屏幕上：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    // Add your code here

    return 0;
}
```

输出应如下所示：

```
4 6 7 3 8 2 1 9
```

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    for (std::size_t index{ 0 }; index < arr.size(); ++index)
    {
        std::cout << arr[index] << ' ';
    }

    if (arr.size() > 0)
        std::cout << '\n';

    return 0;
}
```

#### 问题 #2

更新先前测验解决方案的代码，以便以下程序编译并具有相同的输出：

```cpp
#include <iostream>
#include <vector>

// Implement printArray() here

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    printArray(arr); // use function template to print array

    return 0;
```

```cpp
#include <iostream>
#include <vector>

template <typename T>
void printArray(const std::vector<T>& arr)
{
    for (std::size_t index{ 0 }; index < arr.size(); ++index)
    {
        std::cout << arr[index] << ' ';
    }

    if (arr.size() > 0)
        std::cout << '\n';
}

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    printArray(arr);

    return 0;
}
```

#### 问题 #3

给出测验 2 的解决方案，请执行以下操作：

- 要求用户输入一个介于 1 和 9 之间的值。如果用户没有输入介于 1 和 9 之间的值，则反复要求输入一个整数值，直到用户输入为止。如果用户输入数字后跟无关的输入，则忽略无关的输入。
- 打印数组。
- 编写一个函数模板来搜索数组以查找用户输入的值。如果该值在数组中，则返回该元素的索引。如果该值不在数组中，则返回适当的值。
- 如果找到了值，则打印该值和索引。如果未找到该值，则打印该值以及未找到该值。

我们在第 9.5 课中介绍了如何处理无效输入[——std::cin 和处理无效输入](https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/)。

以下是该程序的两个运行示例：

```
Enter a number between 1 and 9: d
Enter a number between 1 and 9: 6
4 6 7 3 8 2 1 9
The number 6 has index 1
Enter a number between 1 and 9: 5
4 6 7 3 8 2 1 9
The number 5 was not found
```

```cpp
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
void printArray(const std::vector<T>& arr)
{
    for (std::size_t index{ 0 }; index < arr.size(); ++index)
    {
        std::cout << arr[index] << ' ';
    }

    if (arr.size() > 0)
        std::cout << '\n';
}

template <typename T>
int findIndex(const std::vector<T>& arr, T val)
{
    for (std::size_t index{ 0 }; index < arr.size(); ++index)
    {
        if (arr[index] == val)
            return static_cast<int>(index);
    }

    return -1; // -1 is not a valid index, so we can use it as an error return value
}


int getValidNumber()
{
    // First, read in valid input from user
    int num {};
    do
    {
        std::cout << "Enter a number between 1 and 9: ";
        std::cin >> num;

        // if the user entered an invalid character
        if (!std::cin)
            std::cin.clear(); // reset any error flags

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any extra characters in the input buffer (regardless of whether we had an error or not)

    } while (num < 1 || num > 9);

    return num;
}

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    int num { getValidNumber() };

    printArray(arr);

    int index { findIndex(arr, num) };

    if (index != -1)
        std::cout << "The number " << num << " has index " << index << '\n';
    else
        std::cout << "The number " << num << " was not found\n";

    return 0;
}
```

#### 问题 #4

额外加分：修改前面的程序，使得它可以处理`std::vector`包含非 int 数值的，例如`std::vector arr{ 4.4, 6.6, 7.7, 3.3, 8.8, 2.2, 1.1, 9.9 };`。

```cpp
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
void printArray(const std::vector<T>& arr)
{
    for (std::size_t index{ 0 }; index < arr.size(); ++index)
    {
        std::cout << arr[index] << ' ';
    }

    if (arr.size() > 0)
        std::cout << '\n';
}

template <typename T>
int findIndex(const std::vector<T>& arr, T val)
{
    for (std::size_t index{ 0 }; index < arr.size(); ++index)
    {
        if (arr[index] == val)
            return static_cast<int>(index);
    }

    return -1; // -1 is not a valid index, so we can use it as an error return value
}

// Passing in low and high allows the compiler to infer the type of the input we want
template <typename T>
T getValidNumber(std::string_view prompt, T low, T high)
{
    // First, read in valid input from user
    T val {};
    do
    {
        std::cout << prompt;
        std::cin >> val;

        // if the user entered an invalid character
        if (!std::cin)
            std::cin.clear(); // reset any error flags

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any extra characters in the input buffer (regardless of whether we had an error or not)

    } while (val < low || val > high);

    return val;
}

int main()
{
    std::vector arr{ 4.4, 6.6, 7.7, 3.3, 8.8, 2.2, 1.1, 9.9 };

    auto num { getValidNumber("Enter a number between 1 and 9: ", 1.0, 9.0) };

    printArray(arr);

    int index { findIndex(arr, num) };

    if (index != -1)
        std::cout << "The number " << num << " has index " << index << '\n';
    else
        std::cout << "The number " << num << " was not found\n";

    return 0;
}
```

#### 问题 #5

编写一个函数模板来查找 a 中的最大值`std::vector`。如果向量为空，则返回元素类型的默认值。

应执行以下代码：

```cpp
int main()
{
    std::vector data1 { 84, 92, 76, 81, 56 };
    std::cout << findMax(data1) << '\n';

    std::vector data2 { -13.0, -26.7, -105.5, -14.8 };
    std::cout << findMax(data2) << '\n';

    std::vector<int> data3 { };
    std::cout << findMax(data3) << '\n';

    return 0;
}
```

并打印以下结果：

```
92 
-13 
0
```

```cpp
#include <iostream>
#include <vector>

template <typename T>
T findMax(const std::vector<T>& arr)
{
    std::size_t length { arr.size() };

    if (length==0)
        return T{};

    T max { arr[0] }; // Set the max seen to the first element

    // Iterate through any remaining elements looking for a larger value
    for (std::size_t index{ 1 }; index < length; ++index)
    {
        if (arr[index] > max)
            max = arr[index];
    }

    return max;
}

int main()
{
    std::vector data1 { 84, 92, 76, 81, 56 };
    std::cout << findMax(data1) << '\n';

    std::vector data2 { -13.0, -26.7, -105.5, -14.8 };
    std::cout << findMax(data2) << '\n';

    std::vector<int> data3 { };
    std::cout << findMax(data3) << '\n';

    return 0;
}
```

在此示例中，我们使用名为 的非循环变量`max`来跟踪我们看到的最高分数。我们使用`max`第一个元素的值进行初始化，以便它以合法值开始。值初始化可能很诱人，但如果数组仅包含负值，则会导致函数返回错误值。

然后我们遍历数组中的每个元素，如果我们发现一个分数比我们之前见过的任何分数都高，我们就将其设置`max`为该值。因此，`max`始终代表迄今为止我们搜索过的所有元素中的最高分数。当我们到达数组末尾时，`max`保存整个数组中的最高分数，然后我们可以将其返回给调用者。

#### 问题 #6

[在第8.10 课——For 语句](https://www.learncpp.com/cpp-tutorial/for-statements/)的测验中，我们针对数字三、五和七实现了一个名为 FizzBuzz 的游戏。

在这个测验中，游戏的实现如下：

- Numbers divisible by only 3 should print “fizz”.
- Numbers divisible by only 5 should print “buzz”.
- Numbers divisible by only 7 should print “pop”.
- Numbers divisible by only 11 should print “bang”.
- Numbers divisible by only 13 should print “jazz”.
- Numbers divisible by only 17 should print “pow”.
- Numbers divisible by only 19 should print “boom”.
- Numbers divisible by more than one of the above should print each of the words associated with its divisors.
- Numbers not divisible by any of the above should just print the number.

使用 a`std::vector`保存除数，另一个`std::vector`保存单词（类型为`std::string_view`）。如果数组的长度不同，程序应该断言。输出 150 个数字。

Here’s the expected output from the first 21 iterations:

```
1
2
fizz
4
buzz
fizz
pop
8
fizz
buzz
bang
fizz
jazz
pop
fizzbuzz
16
pow
fizz
boom
buzz
fizzpop
```

```cpp
// h/t to reader Waldo for suggesting this quiz
#include <cassert>
#include <iostream>
#include <string_view>
#include <vector>

void fizzbuzz(int count)
{
	// We'll make these static so we only have to do initialization once
	static const std::vector divisors                { 3, 5, 7, 11, 13, 17, 19 };
	static const std::vector<std::string_view> words { "fizz", "buzz", "pop", "bang", "jazz", "pow", "boom" };
	assert(std::size(divisors) == std::size(words) && "fizzbuzz: array sizes don't match");

	// Loop through each number between 1 and count (inclusive)
	for (int i{ 1 }; i <= count; ++i)
	{
		bool printed{ false };

		// Check the current number against each possible divisor
		for (std::size_t j{ 0 }; j < divisors.size(); ++j)
		{
			if (i % divisors[j] == 0)
			{
				std::cout << words[j];
				printed = true;
			}
		}

		// If there were no divisors
		if (!printed)
			std::cout << i;

		std::cout << '\n';
	}
}

int main()
{
	fizzbuzz(150);

	return 0;
}
```

## 16.7 — 数组、循环和符号挑战解决方案

在课程[4.5 — 无符号整数，以及为什么要避免使用它们](https://www.learncpp.com/cpp-tutorial/unsigned-integers-and-why-to-avoid-them/)中，我们指出我们通常更喜欢使用有符号值来保存数量，因为无符号值的行为方式可能令人惊讶。然而，在课程[16.3 — std::vector 和无符号长度和下标问题](https://www.learncpp.com/cpp-tutorial/stdvector-and-the-unsigned-length-and-subscript-problem/)中，我们讨论了`std::vector`（以及其他容器类）如何将无符号整数类型`std::size_t`用于长度和索引。

这可能会导致如下问题：

```cpp
#include <iostream>
#include <vector>

template <typename T>
void printReverse(const std::vector<T>& arr)
{
    for (std::size_t index{ arr.size() - 1 }; index >= 0; --index) // index is unsigned
    {
        std::cout << arr[index] << ' ';
    }

    std::cout << '\n';
}

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    printReverse(arr);

    return 0;
}
```

此代码首先反向打印数组：

```
9 1 2 8 3 7 6 4
```

然后表现出未定义的行为。它可能会打印垃圾值，或者使应用程序崩溃。

这里有两个问题。首先，我们的循环执行的时间是`index >= 0`（换句话说，只要`index`是正数），当是无符号时，它始终为真`index`。因此，循环永远不会终止。

`index`其次，当我们在有值时减少时`0`，它会回绕到一个较大的正值，然后我们在下一次迭代中使用该值对数组进行索引。这是一个越界索引，会导致未定义的行为。如果我们的向量为空，我们也会遇到同样的问题。

尽管有很多方法可以解决这些特定问题，但这些问题很容易引发错误。

使用有符号类型作为循环变量更容易避免此类问题，但也有其自身的挑战。以下是使用有符号索引的上述问题的一个版本：

```cpp
#include <iostream>
#include <vector>

template <typename T>
void printReverse(const std::vector<T>& arr)
{
    for (int index{ static_cast<int>(arr.size()) - 1}; index >= 0; --index) // index is signed
    {
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';
    }

    std::cout << '\n';
}

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    printReverse(arr);

    return 0;
}
```

虽然此版本按预期运行，但由于添加了两个静态强制类型转换，代码也变得混乱。`arr[static_cast<std::size_t>(index)]`特别难以阅读。在这种情况下，我们以可读性为代价提高了安全性。

以下是使用有符号索引的另一个示例：

```cpp
#include <iostream>
#include <vector>

// Function template to calculate the average value in a std::vector
template <typename T>
T calculateAverage(const std::vector<T>& arr)
{
    int length{ static_cast<int>(arr.size()) };

    T average{ 0 };
    for (int index{ 0 }; index < length; ++index)
        average += arr[static_cast<std::size_t>(index)];
    average /= length;

    return average;
}

int main()
{
    std::vector testScore1 { 84, 92, 76, 81, 56 };
    std::cout << "The class 1 average is: " << calculateAverage(testScore1) << '\n';

    return 0;
}
```

静态转换使我们的代码变得非常混乱。

那么我们该怎么办呢？这是一个还没有理想解决方案的领域。

这里有很多可行的选择，我们将按照我们认为从最差到最好的顺序介绍它们。您可能会在其他人编写的代码中遇到所有这些。

**作者注**

**虽然我们将在 的背景下讨论这个问题`std::vector`，但所有标准库容器（例如`std::array`）的工作原理都类似，并且面临相同的挑战。以下讨论适用于其中任何一个。**

### 关闭有符号/无符号转换警告

如果您想知道为什么有符号/无符号转换警告通常默认被禁用，那么本主题就是主要原因之一。每次我们使用有符号索引对标准库容器进行下标时，都会生成一个符号转换警告。这会很快用虚假警告填满您的编译日志，淹没可能真正合法的警告。

因此，避免处理大量有符号/无符号转换警告的一种方法是关闭这些警告。

这是最简单的解决方案，但我们不推荐，因为这也会抑制合法符号转换警告的生成，如果不解决可能会导致错误。

### 使用无符号循环变量

许多开发人员认为，既然标准库数组类型设计为使用无符号索引，那么我们也应该使用无符号索引！这是一个完全合理的立场。我们只需要格外小心，不要在这样做时遇到有符号/无符号不匹配的情况。如果可能的话，避免将索引循环变量用于除索引之外的任何用途。

如果我们决定使用这种方法，我们实际上应该使用哪种无符号类型？

在课程[16.3 — std::vector 和无符号长度和下标问题](https://www.learncpp.com/cpp-tutorial/stdvector-and-the-unsigned-length-and-subscript-problem/#size_type)中，我们注意到标准库容器类定义了嵌套的 typedef `size_type`，它是用于数组长度和索引的无符号整数类型。`size()`成员函数返回`size_type`，并`operator[]`使用`size_type`作为索引，因此使用`size_type`作为索引的类型在技术上是最一致和最安全的无符号类型（因为它在所有情况下都有效，即使在极为罕见的情况下，`size_type`是除 之外的其他内容`size_t`）。例如：

```cpp
#include <iostream>
#include <vector>

int main()
{
	std::vector arr { 1, 2, 3, 4, 5 };

	for (std::vector<int>::size_type index { 0 }; index < arr.size(); ++index)
		std::cout << arr[index] << ' ';

	return 0;
}
```

但是，使用`size_type`有一个很大的缺点：因为它是一个嵌套类型，所以要使用它，我们必须在名称前明确加上容器的完全模板化名称（这意味着我们必须输入`std::vector<int>::size_type`而不是仅仅输入`std::size_type`）。这需要大量的输入，难以阅读，并且根据容器和元素类型而有所不同。

在函数模板中使用时，我们可以使用`T`模板参数。但我们还需要在类型前加上`typename`关键字：

```cpp
#include <iostream>
#include <vector>

template <typename T>
void printArray(const std::vector<T>& arr)
{
	// typename keyword prefix required for dependent type
	for (typename std::vector<T>::size_type index { 0 }; index < arr.size(); ++index)
		std::cout << arr[index] << ' ';
}

int main()
{
	std::vector arr { 9, 7, 5, 3, 1 };

	printArray(arr);

	return 0;
}
```

如果您忘记了`typename`关键字，您的编译器可能会提醒您添加它。

**对于高级读者**

**任何依赖于包含模板参数的类型的名称都称为依赖名称。依赖名称必须以关键字作为前缀`typename`才能用作类型。**

**在上面的例子中，`std::vector<T>`是带有模板参数的类型，因此嵌套类型`std::vector<T>::size_type`是一个依赖名称，并且必须以 为前缀`typename`才能用作类型。**

您可能偶尔会看到数组类型别名，以使循环更易于阅读：

```cpp
using arrayi = std::vector<int>;
for (arrayi::size_type index { 0 }; index < arr.size(); ++index)
```

更通用的解决方案是让编译器为我们获取数组类型对象的类型，这样我们就不必显式指定容器类型或模板参数。为此，我们可以使用**`decltype`**关键字，它返回其参数的类型。

```cpp
// arr is some non-reference type
for (decltype(arr)::size_type index { 0 }; index < arr.size(); ++index) // decltype(arr) resolves to std::vector<int>
```

但是，如果`arr`是引用类型（例如通过引用传递的数组），则上述方法不起作用。我们需要首先从中删除引用`arr`：

```cpp
template <typename T>
void printArray(const std::vector<T>& arr)
{
	// arr can be a reference or non-reference type
	for (typename std::remove_reference_t<decltype(arr)>::size_type index { 0 }; index < arr.size(); ++index)
		std::cout << arr[index] << ' ';
}
```

不幸的是，这不再非常简洁或容易记住。

因为`size_type`几乎总是的 typedef `size_t`，所以许多程序员干脆跳过使用`size_type`，而使用更容易记住的`std::size_t`直接输入：

```cpp
for (std::size_t index { 0 }; index < arr.size(); ++index)
```

除非您使用自定义分配器（您可能没有使用），否则我们认为这是一种合理的方法。

### 使用有符号循环变量

尽管使用有符号循环变量会让使用标准库容器类型变得有些困难，但它与我们其余代码中采用的最佳实践是一致的（倾向于使用有符号值作为数量）。而且，我们越能始终如一地应用我们的最佳实践，总体而言，错误就越少。

如果我们要使用有符号循环变量，则需要解决三个问题：

- 我们应该使用什么符号类型？
- 获取数组的长度作为有符号值
- 将有符号循环变量转换为无符号索引

### 我们应该使用什么符号类型？

这里有三个（有时四个）不错的选择。

1. 除非您正在处理非常大的数组，否则使用`int`应该没问题（特别是在 int 为 4 个字节的体系结构上）。`int`是当我们并不真正关心类型时对所有内容使用的默认有符号整数类型，并且在这里没有理由做其他事情。
2. 如果你正在处理非常大的数组，或者如果你想要更谨慎一些，你可以使用名字奇怪的`std::ptrdiff_t`。这个 typedef 通常用作 的有符号对应部分`std::size_t`。
3. 因为`std::ptrdiff_t`名字很奇怪，所以另一个好方法是为索引定义自己的类型别名：

```cpp
using Index = std::ptrdiff_t;

// Sample loop using index
for (Index index{ 0 }; index < static_cast<Index>(arr.size()); ++index)
```

我们将在下一节展示一个完整的示例。

定义自己的类型别名也具有潜在的未来好处：如果 C++ 标准库发布了一种旨在用作有符号索引的类型，则可以很容易地修改`Index`为该类型的别名，或者查找/替换`Index`为该类型的名称。

1. 如果您可以从初始化程序中派生出循环变量的类型，则可以用`auto`编译器推断类型：

```cpp
for (auto index{ static_cast<std::ptrdiff_t>(arr.size())-1 }; index >= 0; --index)
```

复制在 C++23 中，`Z`后缀可用于定义与以下内容有符号对应的类型的文字`std::size_t`（可能是`std::ptrdiff_t`）：

```cpp
for (auto index{ 0Z }; index < static_cast<std::ptrdiff_t>(arr.size()); ++index)
```

### 获取数组的长度作为有符号值

1. 在 C++20 之前，最好的选择是成员函数`static_cast`的返回值`size()`或`std::size()`有符号类型：

```cpp
#include <iostream>
#include <vector>

using Index = std::ptrdiff_t;

int main()
{
    std::vector arr{ 9, 7, 5, 3, 1 };

    for (auto index{ static_cast<Index>(arr.size())-1 }; index >= 0; --index)
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';

    return 0;
}
```

这样，返回的无符号值`arr.size()`将转换为有符号类型，因此我们的比较运算符将有两个有符号操作数。而且由于有符号索引在变为负数时不会溢出，因此我们不会遇到使用无符号索引时遇到的回绕问题。

这种方法的缺点是它使我们的循环变得混乱，使其更难阅读。我们可以通过将长度移出循环来解决这个问题：

```cpp
#include <iostream>
#include <vector>

using Index = std::ptrdiff_t;

int main()
{
    std::vector arr{ 9, 7, 5, 3, 1 };

    auto length{ static_cast<Index>(arr.size()) };
    for (auto index{ length-1 }; index >= 0; --index)
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';

    return 0;
}
```

2.在 C++20 中，使用`std::ssize()`：

如果您想要更多证据来证明 C++ 的设计者现在相信有符号索引是可行的方法，请考虑在 C++20 中引入`std::ssize()`。此函数以有符号类型（可能是）的形式返回数组类型的大小`ptrdiff_t`。

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector arr{ 9, 7, 5, 3, 1 };

    for (auto index{ std::ssize(arr)-1 }; index >= 0; --index) // std::ssize introduced in C++20
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';

    return 0;
}
```

### 将有符号循环变量转换为无符号索引

一旦我们有了有符号循环变量，每当我们尝试将该有符号循环变量用作索引时，我们都会遇到隐式符号转换警告。因此，无论我们打算在哪里将其用作索引，我们都需要某种方法将有符号循环变量转换为无符号值。

1. 显而易见的选择是将有符号循环变量静态转换为无符号索引。我们在前面的例子中展示了这一点。不幸的是，我们需要在数组下标的任何地方都这样做，这使得我们的数组索引难以读取。
2. 使用具有短名称的转换函数：

```cpp
#include <iostream>
#include <type_traits> // for std::is_integral and std::is_enum
#include <vector>

using Index = std::ptrdiff_t;

// Helper function to convert `value` into an object of type std::size_t
// UZ is the suffix for literals of type std::size_t.
template <typename T>
constexpr std::size_t toUZ(T value)
{
    // make sure T is an integral type
    static_assert(std::is_integral<T>() || std::is_enum<T>());

    return static_cast<std::size_t>(value);
}

int main()
{
    std::vector arr{ 9, 7, 5, 3, 1 };

    auto length { static_cast<Index>(arr.size()) };  // in C++20, prefer std::ssize()
    for (auto index{ length-1 }; index >= 0; --index)
        std::cout << arr[toUZ(index)] << ' '; // use toUZ() to avoid sign conversion warning

    return 0;
}
```

在上面的例子中，我们创建了一个名为的函数`toUZ()`，用于将整数值转换为类型的值`std::size_t`。这允许我们将数组索引为`arr[toUZ(index)]`，这非常易读。

3.使用自定义视图

在之前的课程中，我们讨论了如何`std::string`拥有一个字符串，而`std::string_view`是查看存在于其他地方的字符串。 的巧妙之处在于`std::string_view`它可以查看不同类型的字符串（C 样式字符串文字、`std::string`和其他`std::string_view`），但保持一致的接口供我们使用。

虽然我们无法修改标准库容器以接受有符号整数索引，但我们可以创建自己的自定义视图类来“查看”标准库容器类。这样，我们就可以定义自己的接口来按照我们想要的方式工作。

在以下示例中，我们定义一个自定义视图类，该类可以查看任何支持索引的标准库容器。我们的界面将做两件事：

- `operator[]`允许我们使用有符号整数类型访问元素。
- 将容器的长度获取为有符号整数类型（因为`std::ssize()`仅在 C++20 上可用）。

这使用运算符重载（我们在第[13.5 课-I/O 运算符重载简介](https://www.learncpp.com/cpp-tutorial/introduction-to-overloading-the-i-o-operators/)中简要介绍过）来实现`operator[]`。您无需了解如何`SignedArrayView`实现即可使用它。

SignedArrayView.h：

```cpp
#ifndef SIGNED_ARRAY_VIEW_H
#define SIGNED_ARRAY_VIEW_H

#include <cstddef> // for std::size_t and std::ptrdiff_t

// SignedArrayView provides a view into a container that supports indexing
// allowing us to work with these types using signed indices
template <typename T>
class SignedArrayView // requires C++17
{
private:
    T& m_array;

public:
    using Index = std::ptrdiff_t;

    SignedArrayView(T& array)
        : m_array{ array } {}

    // Overload operator[] to take a signed index
    constexpr auto& operator[](Index index) { return m_array[static_cast<typename T::size_type>(index)]; }
    constexpr const auto& operator[](Index index) const { return m_array[static_cast<typename T::size_type>(index)]; }
    constexpr auto ssize() const { return static_cast<Index>(m_array.size()); }
};

#endif
```

主程序：

```cpp
#include <iostream>
#include <vector>
#include "SignedArrayView.h"

int main()
{
    std::vector arr{ 9, 7, 5, 3, 1 };
    SignedArrayView sarr{ arr }; // Create a signed view of our std::vector

    for (auto index{ sarr.ssize() - 1 }; index >= 0; --index)
        std::cout << sarr[index] << ' '; // index using a signed type

    return 0;
}
```

### 索引底层 C 样式数组

在课程[16.3 — std::vector 和无符号长度和下标问题](https://www.learncpp.com/cpp-tutorial/stdvector-and-the-unsigned-length-and-subscript-problem/)中，我们注意到，我们可以调用`data()`成员函数并对其进行索引，而不是对标准库容器进行索引。由于`data()`将数组数据作为 C 样式数组返回，并且 C 样式数组允许使用有符号和无符号值进行索引，因此可以避免符号转换问题。

```cpp
int main()
{
    std::vector arr{ 9, 7, 5, 3, 1 };

    auto length { static_cast<Index>(arr.size()) };  // in C++20, prefer std::ssize()
    for (auto index{ length - 1 }; index >= 0; --index)
        std::cout << arr.data()[index] << ' ';       // use data() to avoid sign conversion warning

    return 0;
}
```

我们认为这种方法是最好的索引选项：

- 我们可以使用有符号的循环变量和索引。
- 我们不必定义任何自定义类型或类型别名。
- 使用对可读性的影响`data()`不是很大。
- 优化的代码不应该对性能造成影响。

### 唯一明智的选择：完全避免索引！

上面介绍的所有选项都有各自的缺点，因此很难推荐其中一种方法。不过，有一种选择比其他选择更明智：完全避免使用整数值进行索引。

C++ 提供了其他几种不使用索引来遍历数组的方法。如果我们没有索引，那么我们就不会遇到所有这些有符号/无符号转换问题。

两种常见的无索引数组遍历方法包括基于范围的循环和迭代器。

**相关内容**

**我们将在下一课（[16.8 -- 基于范围的 for 循环 (for-each)]中介绍范围 for 循环。**
**我们将在即将到来的课程[18.2 -- 迭代器简介]中介绍迭代器。**

如果您仅使用索引变量来遍历数组，那么最好使用不使用索引的方法。

**最佳实践**

**尽可能避免使用整数值进行数组索引。**

## 16.8 — 基于范围的 for 循环（for-each）

在课程[16.6 — 数组和循环](https://www.learncpp.com/cpp-tutorial/arrays-and-loops/)中，我们展示了使用 for 循环遍历数组的每个元素的示例，使用循环变量作为索引。下面是另一个示例：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

    std::size_t length { fibonacci.size() };
    for (std::size_t index { 0 }; index < length; ++index)
       std::cout << fibonacci[index] << ' ';

    std::cout << '\n';

    return 0;
}
```

尽管 for 循环提供了一种方便灵活的方式来迭代数组，但它们也容易出错，容易出现偏差一 (off-by-one) 错误，并且容易出现数组索引符号问题（在第[16.7 课——数组、循环和符号挑战解决方案](https://www.learncpp.com/cpp-tutorial/arrays-loops-and-sign-challenge-solutions/)中讨论）。

由于遍历（向前）数组是一种常见的操作，因此 C++ 支持另一种类型的 for 循环，称为**基于范围的 for 循环**（有时也称为**for-each 循环**），这种循环允许遍历容器而无需进行显式索引。基于范围的 for 循环更简单、更安全，并且适用于 C++ 中的所有常见数组类型（包括`std::vector`、`std::array`和 C 样式数组）。

### 基于范围的 for 循环

基于范围*的 for*语句的语法如下：

```
for (element_declaration : array_object)
   statement;
```

当遇到基于范围的 for 循环时，循环会遍历 中的每个元素`array_object`，每次迭代都会将当前数组元素的值赋给 中声明的变量`element_declaration`，然后`statement`执行。

为了获得最佳效果，`element_declaration`应该具有与数组元素相同的类型，否则将发生类型转换。

这是一个简单的例子，它使用*基于范围的 for*循环来打印名为的数组中的所有元素`fibonacci`：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

    for (int num : fibonacci) // iterate over array fibonacci and copy each value into `num`
       std::cout << num << ' '; // print the current value of `num`

    std::cout << '\n';

    return 0;
}
```

这将打印：

```
0 1 1 2 3 5 8 13 21 34 55 89
```

请注意，此示例不需要我们使用数组的长度，也不需要我们对数组进行索引！

让我们仔细看看它是如何工作的。这个基于范围的 for 循环将执行 的所有元素`fibonacci`。对于第一次迭代，变量`num`被赋予第一个元素的值（`0`）。然后程序执行关联语句，将 的值`num`（`0`）打印到控制台。对于第二次迭代，`num`被赋予第二个元素的值（`1`）。再次执行关联语句，打印`1`。基于范围的 for 循环继续依次迭代每个数组元素，对每个元素执行关联语句，直到数组中没有元素可迭代。此时，循环终止，程序继续执行（打印换行符然后返回`0`操作系统）。

**关键见解**

**声明的元素（`num`在上例中）不是数组索引。相反，它被赋予了正在迭代的数组元素的值。**

因为`num`被分配了数组元素的值，这确实意味着数组元素被复制（这对于某些类型来说可能很昂贵）。

**最佳实践**

**遍历容器时，优先使用基于范围的 for 循环，而不是常规的 for 循环。**

### `auto`使用关键字进行基于范围的循环和类型推断

因为`element_declaration`应该具有与数组元素相同的类型（以防止发生类型转换），所以这是使用关键字的理想情况`auto`，并让编译器为我们推断数组元素的类型。这样我们就不必重复指定类型，并且不会有意外输入错误的风险（和“输入错误”，哈哈！）

下面是与上面相同的例子，但是使用`auto`的类型为`num`：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

    for (auto num : fibonacci) // compiler will deduce type of num to be `int`
       std::cout << num << ' ';

    std::cout << '\n';

    return 0;
}
```

因为`std::vector fibonacci`具有类型的元素`int`，`num`将被推断为`int`。

**最佳实践**

**`auto`使用基于范围的 for 循环的类型推断（ ）让编译器推断数组元素的类型。**

使用的另一个好处`auto`是，如果数组的元素类型发生更新（例如从`int`到`long`），`auto`将自动推断更新后的元素类型，确保它们保持同步（并防止发生类型转换）。

### 避免使用引用复制元素

考虑以下基于范围的 for 循环，它迭代数组`std::string`：

```cpp
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words{ "peter", "likes", "frozen", "yogurt" };

    for (auto word : words)
        std::cout << word << ' ';

    std::cout << '\n';

    return 0;
}
```

对于此循环的每次迭代，数组中的下一个`std::string`元素`words`将被分配（复制）到变量中`word`。复制 a的`std::string`代价很高，这就是为什么我们通常`std::string`通过 const 引用传递给函数。除非我们真的需要副本，否则我们希望避免复制那些代价高昂的东西。在这种情况下，我们只是打印副本的值，然后副本被销毁。如果我们可以避免复制而只引用实际的数组元素，那就更好了。

幸运的是，我们可以通过创建`element_declaration`一个 (const) 引用来做到这一点：

```cpp
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words{ "peter", "likes", "frozen", "yogurt" };

    for (const auto& word : words) // word is now a const reference
        std::cout << word << ' ';

    std::cout << '\n';

    return 0;
}
```

在上面的例子中，`word`现在是一个 const 引用。随着此循环的每次迭代，`word`将绑定到下一个数组元素。这使我们能够访问数组元素的值，而无需进行昂贵的复制。

如果引用是非 const 的，它也可以用于更改数组中的值（如果我们`element_declaration`是值的副本，则不可能）。

### 何时使用`auto`vs `auto&`vs`const auto&`

通常，当我们想要`auto`修改元素时，我们会使用`auto&`复制成本低的类型，以及`const auto&`复制成本高的类型。但是对于基于范围的 for 循环，许多开发人员认为最好始终使用它`const auto&`，因为它更具前瞻性。

例如，考虑以下示例：

```cpp
#include <iostream>
#include <string_view>
#include <vector>

int main()
{
    std::vector<std::string_view> words{ "peter", "likes", "frozen", "yogurt" }; // elements are type std::string_view

    for (auto word : words) // We normally pass string_view by value, so we'll use auto here
        std::cout << word << ' ';

    std::cout << '\n';

    return 0;
}
```

在此示例中，我们有一个`std::vector`包含`std::string_view`对象的。由于`std::string_view`通常是通过值传递的，因此使用`auto`似乎是合适的。

但是考虑一下如果`words`稍后将其更新为数组会发生什么情况`std::string`。

```cpp
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words{ "peter", "likes", "frozen", "yogurt" }; // obvious we should update this

    for (auto word : words) // Probably not obvious we should update this too
        std::cout << word << ' ';

    std::cout << '\n';

    return 0;
}
```

基于范围的 for 循环可以顺利编译和执行，但`word`现在将被推断为`std::string`，并且由于我们使用`auto`，我们的循环将默默地复制昂贵的`std::string`元素。我们只是遭受了巨大的性能损失！

有几种合理的方法可以确保这种情况不会发生：

- 不要在基于范围的 for 循环中使用类型推断。如果我们明确指定元素类型为`std::string_view`，那么当数组稍后更新为时`std::string`，`std::string`元素将隐式转换为`std::string_view`，这没有问题。如果数组更新为其他不可转换的类型，编译器将出错，我们可以找出此时应该做什么。但如果元素类型是可转换的，那么编译器将默默执行转换，我们可能没有意识到我们正在做一些次优的事情。
- 当您不想使用副本时，在基于范围的 for 循环中使用类型推断时，请使用`const auto&`而不是。通过引用而不是按值访问元素的性能损失可能很小，并且如果元素类型后来更改为复制成本高昂的类型，这可以使我们避免将来可能出现的重大性能损失。`auto`

**最佳实践**

**对于基于范围的 for 循环，最好将元素类型定义为：**

- **`auto`当您想要修改元素的副本时。**
- **`auto&`当你想要修改原始元素时。**
- **`const auto&`否则（当您只需要查看原始元素时）。**

### 基于范围的 for 循环和其他标准容器类型

基于范围的 for 循环适用于多种数组类型，包括（非衰减）C 样式数组、、、`std::array`链接`std::vector`列表、树和映射。我们尚未介绍其中任何一种，因此如果您不知道它们是什么，请不要担心。只需记住，*基于范围的 for*循环提供了一种灵活且通用的方法来迭代不仅仅是`std::vector`：

```cpp
#include <array>
#include <iostream>

int main()
{
    std::array fibonacci{ 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 }; // note use of std::array here

    for (auto number : fibonacci)
    {
        std::cout << number << ' ';
    }

    std::cout << '\n';

    return 0;
}
```

**对于高级读者**

**基于范围的 for 循环不适用于衰减的 C 样式数组。这是因为基于范围的 for 循环需要知道数组的长度才能知道遍历何时完成，而衰减的 C 样式数组不包含此信息。**

**基于范围的 for 循环也不适用于枚举。我们在第[17.6 课——std::array 和枚举]中展示了一种解决此问题的方法。**

### 获取当前元素的索引

基于范围的 for 循环不*提供*直接方法来获取当前元素的数组索引。这是因为基于范围的 for 循环可以迭代的许多结构（例如`std::list`）不支持索引。

但是，由于基于范围的 for 循环始终向前迭代并且不会跳过元素，因此您始终可以声明（并增加）自己的计数器。但是，如果您要这样做，则应考虑是否最好使用普通的 for 循环而不是基于范围的 for 循环。

### 反向C++20中的基于范围的 for 循环

基于范围的 for 循环仅按正向顺序迭代。但是，有些情况下我们想要以相反的顺序遍历数组。在 C++20 之前，基于范围的 for 循环不能轻易用于此目的，必须采用其他解决方案（通常是普通的 for 循环）。

但是，从 C++20 开始，你可以使用`std::views::reverse`Ranges 库的功能来创建可遍历元素的反向视图：

```cpp
#include <iostream>
#include <ranges> // C++20
#include <string_view>
#include <vector>

int main()
{
    std::vector<std::string_view> words{ "Alex", "Bobby", "Chad", "Dave" }; // sorted in alphabetical order

    for (const auto& word : std::views::reverse(words)) // create a reverse view
        std::cout << word << ' ';

    std::cout << '\n';

    return 0;
}
```

这将打印：

```cpp
Dave
Chad
Bobby
Alex
```

我们还没有介绍范围库，所以现在就把它看作是一个有用的魔法。

### **测验时间**

#### 问题 #1

定义一个`std::vector`包含以下名称的数组：“Alex”、“Betty”、“Caroline”、“Dave”、“Emily”、“Fred”、“Greg”和“Holly”。要求用户输入一个名称。使用基于范围的 for 循环查看用户输入的名称是否在数组中。

示例输出：

```
Enter a name: Betty
Betty was found.
Enter a name: Megatron
Megatron was not found.
```

```cpp
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int main()
{
    std::vector<std::string_view> names{ "Alex", "Betty", "Caroline", "Dave",
        "Emily", "Fred", "Greg", "Holly" };

    std::cout << "Enter a name: ";
    std::string username{};
    std::cin >> username;

    bool found{ false };

    // We will be explicit about expecting `name` to be a std::string_view here
    // That way if `names` is ever changed to an expensive to copy type
    // (like std::string), we won't end up making expensive copies.
    for (std::string_view name : names)
    {
        if (name == username)
        {
            found = true;
            break;
        }
    }

    if (found)
        std::cout << username << " was found.\n";
    else
        std::cout << username << " was not found.\n";

    return 0;
}
```

### 问题 #2

修改你的答案以完成测验 1。在此版本中，创建一个名为 的函数模板（不是普通函数），`isValueInArray()`该模板接受两个参数：a和一个值。如果值在数组中，则`std::vector`函数应返回，否则返回。从 调用该函数并将名称数组和用户输入的名称传递给它。`true``false``main()`

提醒：

- 使用模板参数推导的函数模板（当未明确指定模板类型参数时）不会进行转换以匹配模板类型参数。调用要么匹配模板（并且可以推导模板类型），要么不匹配。
- 具有明确指定的模板类型参数的函数模板将转换参数以匹配参数类型（因为类型是已知的）。

```c++
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

template <typename T>
bool isValueInArray(const std::vector<T>& arr, const T& value )
{
    // we'll use a reference since we don't know if T is expensive to copy
    for (const auto& a : arr)
    {
        if (a == value)
            return true;
    }

    return false;
}

int main()
{
    std::vector<std::string_view> names{ "Alex", "Betty", "Caroline", "Dave",
        "Emily", "Fred", "Greg", "Holly" };

    std::cout << "Enter a name: ";
    std::string username{};
    std::cin >> username;

    // By explicitly specifying std::string_view as a function template argument,
    // the compiler will implicitly convert username to `std::string_view` to match the parameter type.
    bool found{ isValueInArray<std::string_view>(names, username) };

    // The following is also okay.  If we rely on template argument deduction instead, the compiler
    // won't do implicit conversions, so we need to make sure `username` has the expected type.
    // bool found{ isValueInArray(names, static_cast<std::string_view>(username)) };

    if (found)
        std::cout << username << " was found.\n";
    else
        std::cout << username << " was not found.\n";

    return 0;
}
```

## 16.9 — 使用枚举器进行数组索引和长度

数组的一个较大的文档问题是整数索引没有向程序员提供有关索引含义的任何信息。

考虑一个包含 5 个测试分数的数组：

该学生代表是谁`testScores[2]`？尚不清楚。

### 使用无范围枚举器进行索引

在课程[16.3 -- std::vector 和无符号长度和下标问题](https://www.learncpp.com/cpp-tutorial/stdvector-and-the-unsigned-length-and-subscript-problem/)中，我们花了很多时间讨论 的索引`std::vector<T>::operator[]`（以及其他可以下标的 C++ 容器类）的类型`size_type`为 ，它通常是 的别名`std::size_t`。因此，我们的索引要么需要是 类型`std::size_t`，要么是可以转换为 的类型`std::size_t`。

由于无范围枚举将隐式转换为`std::size_t`，这意味着我们可以使用无范围枚举作为数组索引来帮助记录索引的含义：

```cpp
#include <vector>

namespace Students
{
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        max_students // 5
    };
}

int main()
{
    std::vector testScores { 78, 94, 66, 77, 14 };

    testScores[Students::stan] = 76; // we are now updating the test score belonging to stan

    return 0;
}
```

这样，数组中每个元素代表什么就更加清楚了。

因为枚举器是隐式 constexpr，所以将枚举器转换为无符号整数类型不被视为收缩转换，从而避免了有符号/无符号索引问题。

### 使用非 `constexpr` 无范围枚举进行索引

无范围枚举的底层类型是实现定义的（因此，可以是有符号或无符号整数类型）。因为枚举器是隐式 `constexpr`，所以只要我们坚持使用无范围枚举器进行索引，就不会遇到符号转换问题。

但是，如果我们定义一个枚举类型的非 constexpr 变量，然后尝试`std::vector`使用该变量来索引，则在任何将无范围枚举默认为有符号类型的平台上，我们可能会收到符号转换警告：

```cpp
#include <vector>

namespace Students
{
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        max_students // 5
    };
}

int main()
{
    std::vector testScores { 78, 94, 66, 77, 14 };
    Students::Names name { Students::stan }; // non-constexpr

    testScores[name] = 76; // may trigger a sign conversion warning if Student::Names defaults to a signed underlying type

    return 0;
}
```

在这个特定情况下，我们可以创建`name`constexpr（这样从 constexpr 有符号整数类型到 的转换`std::size_t`就不会变窄）。但是，当我们的初始化器不是常量表达式时，这种方法就行不通了。

另一种选择是明确指定枚举的底层类型为无符号整数：

```cpp
#include <vector>

namespace Students
{
    enum Names : unsigned int // explicitly specifies the underlying type is unsigned int
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        max_students // 5
    };
}

int main()
{
    std::vector testScores { 78, 94, 66, 77, 14 };
    Students::Names name { Students::stan }; // non-constexpr

    testScores[name] = 76; // not a sign conversion since name is unsigned

    return 0;
}
```

在上面的例子中，由于`name`现在保证为`unsigned int`，因此可以将其转换为`std::size_t`没有符号转换问题。

### 使用计数枚举器

请注意，我们在枚举器列表末尾定义了一个名为 的额外枚举器`max_students`。如果所有先前的枚举器都使用默认值（建议这样做），则此枚举器的默认值将与前面的枚举器的数量相匹配。在上面的示例中，`max_students`的值为`5`，因为先前定义了 5 个枚举器。非正式地，我们将其称为**计数枚举器**，因为它的值代表先前定义的枚举器的数量。

然后，我们可以在任何需要计数先前枚举器的地方使用此计数枚举器。例如：

```cpp
#include <iostream>
#include <vector>

namespace Students
{
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        // add future enumerators here
        max_students // 5
    };
}

int main()
{
    std::vector<int> testScores(Students::max_students); // Create a vector with 5 elements

    testScores[Students::stan] = 76; // we are now updating the test score belonging to stan

    std::cout << "The class has " << Students::max_students << " students\n";

    return 0;
}
```

`max_students`我们在两个地方使用：首先，我们创建一个`std::vector`长度为 的向量`max_students`，因此每个学生的向量都有一个元素。我们还使用它`max_students`来打印学生人数。

这种技术也很好，因为如果稍后（就在之前）添加了另一个枚举器`max_students`，那么`max_students`它将自动变得更大，并且我们使用的所有数组都`max_students`将更新以使用新的长度而无需进一步修改。

```cpp
#include <vector>
#include <iostream>

namespace Students
{
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        wendy, // 5 (added)
        // add future enumerators here
        max_students // now 6
    };
}

int main()
{
    std::vector<int> testScores(Students::max_students); // will now allocate 6 elements

    testScores[Students::stan] = 76; // still works

    std::cout << "The class has " << Students::max_students << " students\n";

    return 0;
}
```

### 使用计数枚举器断言数组长度

更常见的情况是，我们使用初始化值列表创建数组，目的是用枚举器索引该数组。在这种情况下，断言容器的大小等于计数枚举器会很有用。如果触发此断言，则我们的枚举器列表在某种程度上不正确，或者我们提供了错误数量的初始化值。当将新枚举器添加到枚举中，但未将新的初始化值添加到数组时，很容易发生这种情况。

例如：

```cpp
#include <cassert>
#include <iostream>
#include <vector>

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
    std::vector testScores { 78, 94, 66, 77, 14 };

    // Ensure the number of test scores is the same as the number of students
    assert(std::size(testScores) == max_students);

    return 0;
}
```

**提示**

**如果您的数组是 `constexpr`，那么您应该`static_assert`改为。`std::vector`不支持 constexpr，但是`std::array`（和 C 样式数组）支持。**

**我们将在第[17.3 课“传递和返回 std::array”](https://www.learncpp.com/cpp-tutorial/passing-and-returning-stdarray/)中进一步讨论这一点。**

**最佳实践**

**使用 a`static_assert`来确保 `constexpr` 数组的长度与计数枚举器匹配。**
**使用 an`assert`来确保非 `constexpr` 数组的长度与计数枚举器匹配。**

### 数组和枚举类

由于无范围枚举会通过其枚举器污染它们定义所在的命名空间，因此在枚举尚未包含在其他范围区域（例如命名空间或类）中的情况下，最好使用枚举类。

但是，由于枚举类没有隐式转换为整数类型，因此当我们尝试使用它们的枚举器作为数组索引时会遇到问题：

```cpp
#include <iostream>
#include <vector>

enum class StudentNames // now an enum class
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
    // compile error: no conversion from StudentNames to std::size_t
    std::vector<int> testScores(StudentNames::max_students);

    // compile error: no conversion from StudentNames to std::size_t
    testScores[StudentNames::stan] = 76;

    // compile error: no conversion from StudentNames to any type that operator<< can output
    std::cout << "The class has " << StudentNames::max_students << " students\n";

    return 0;
}
```

有几种方法可以解决这个问题。最明显的是，我们可以将`static_cast`枚举器转换为整数：

```cpp
#include <iostream>
#include <vector>

enum class StudentNames
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
    std::vector<int> testScores(static_cast<int>(StudentNames::max_students));

    testScores[static_cast<int>(StudentNames::stan)] = 76;

    std::cout << "The class has " << static_cast<int>(StudentNames::max_students) << " students\n";

    return 0;
}
```

然而，这不仅输入起来很麻烦，而且还会使我们的代码变得非常混乱。

[更好的选择是使用我们在第13.6 课——范围枚举（枚举类）]中介绍的辅助函数，它允许我们使用一元将枚举类的枚举器转换为整数值`operator+`。

```cpp
#include <iostream>
#include <type_traits> // for std::underlying_type_t
#include <vector>

enum class StudentNames
{
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    max_students // 5
};

// Overload the unary + operator to convert StudentNames to the underlying type
constexpr auto operator+(StudentNames a) noexcept
{
    return static_cast<std::underlying_type_t<StudentNames>>(a);
}

int main()
{
    std::vector<int> testScores(+StudentNames::max_students);

    testScores[+StudentNames::stan] = 76;

    std::cout << "The class has " << +StudentNames::max_students << " students\n";

    return 0;
}
```

但是，如果要进行大量枚举器到整数的转换，那么最好只使用命名空间（或类）内的标准枚举。

### 测验时间

#### 问题 #1

创建一个程序定义的枚举（在命名空间内），其中包含以下动物的名称：鸡、狗、猫、大象、鸭子和蛇。为这些动物中的每一个定义一个包含一个元素的数组，并使用初始化列表初始化每个元素以保存该动物的腿数。断言数组具有正确数量的初始化器。

编写一个 main() 函数，使用枚举器打印大象的腿数。

```c++
#include <cassert>
#include <iostream>
#include <vector>

namespace Animals
{
    enum Animals
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        max_animals
    };

    const std::vector legs{ 2, 4, 4, 4, 2, 0 };
}

int main()
{
    // Ensure the number of legs is the same as the number of animals
    assert(std::size(Animals::legs) == Animals::max_animals);

    std::cout << "An elephant has " << Animals::legs[Animals::elephant] << " legs.\n";

    return 0;
}
```

## 16.10 — std::vector 的大小和容量调整

在本章的前几节课中，我们介绍了容器、数组和`std::vector`。我们还讨论了如何访问数组元素、获取数组的长度以及如何遍历数组等主题。虽然我们`std::vector`在示例中使用了，但我们讨论的概念通常适用于所有数组类型。

在本章的剩余课程中，我们将重点关注`std::vector`与大多数其他数组类型有显著不同的一件事：实例化后调整自身大小的能力。

固定大小数组与动态数组

大多数数组类型都有一个明显的限制：在实例化时必须知道数组的长度，并且不能更改。这样的数组称为**固定大小数组**或**固定长度数组**。`std::array`和`C-style arrays`都是固定大小数组类型。我们将在下一章进一步讨论这些。

另一方面，`std::vector`是动态数组。**动态数组**（也称为**可调整大小数组**）是实例化后可以更改大小的数组。这种可调整大小的能力是其特殊之处`std::vector`。

### `std::vector`在运行时调整大小

实例化之后，`std::vector`可以通过调用具有新所需长度的成员函数`resize()`来调整A 的大小：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector v{ 0, 1, 2 }; // create vector with 3 elements
    std::cout << "The length is: " << v.size() << '\n';

    v.resize(5);              // resize to 5 elements
    std::cout << "The length is: " << v.size() << '\n';

    for (auto i : v)
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```

这将打印：

```
The length is: 3
The length is: 5
0 1 2 0 0
```

这里有两点需要注意。首先，当我们调整向量的大小时，现有的元素值被保留了下来！其次，新元素被初始化为值（对类类型执行默认初始化，对其他类型执行零初始化）。因此，两个类型的新元素`int`被初始化为零`0`。

向量也可以调整大小以使其更小：

```cpp
#include <iostream>
#include <vector>

void printLength(const std::vector<int>& v)
{
	std::cout << "The length is: "	<< v.size() << '\n';
}

int main()
{
    std::vector v{ 0, 1, 2, 3, 4 }; // length is initially 5
    printLength(v);

    v.resize(3);                    // resize to 3 elements
    printLength(v);

    for (int i : v)
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```

这将打印：

```
The length is: 5
The length is: 3
0 1 2
```

### 长度与容量`std::vector`

考虑一排 12 栋房子。我们会说房子的数量（或房子排的长度）是 12。如果我们想知道其中哪些房子目前有人居住……我们必须以其他方式确定（例如按门铃，看看是否有人回应）。当我们只有长度时，我们只知道有多少东西存在。

现在考虑一盒鸡蛋，里面目前有 5 只鸡蛋。我们会说鸡蛋的数量是 5。但在这种情况下，我们关心的另一个维度是：如果盒子装满了，可以容纳多少只鸡蛋。我们会说这盒鸡蛋的容量是 12。盒子可以容纳 12 只鸡蛋，但只使用了 5 只——因此，我们可以再添加 7 只鸡蛋而不会溢出盒子。当我们同时拥有长度和容量时，我们可以区分当前存在的东西数量和可以容纳的东西数量。

到目前为止，我们只讨论了 的长度`std::vector`。但`std::vector`它也有容量。在 的上下文中`std::vector`，**容量**`std::vector`是分配了多少个元素的存储空间，而**长度**是当前正在使用的元素数量。

容量为 5 的向量`std::vector`已分配 5 个元素的空间。如果向量包含 2 个正在使用的元素，则向量的长度（大小）为 2。其余 3 个元素已分配内存，但它们不被视为正在使用。它们可以在以后使用而不会溢出向量。

**关键见解**

**向量的长度表示有多少元素正在使用。**
**向量的容量表示有多少元素已在内存中分配。**

### 获取`std::vector`

`std::vector`我们可以通过成员函数询问它的容量`capacity()`。

例如：

```cpp
#include <iostream>
#include <vector>

void printCapLen(const std::vector<int>& v)
{
	std::cout << "Capacity: " << v.capacity() << " Length:"	<< v.size() << '\n';
}

int main()
{
    std::vector v{ 0, 1, 2 }; // length is initially 3

    printCapLen(v);

    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    v.resize(5); // resize to 5 elements

    printCapLen(v);

    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}
```

在作者的机器上，这将打印以下内容：

```
Capacity: 3  Length: 3
0 1 2
Capacity: 5  Length: 5
0 1 2 0 0
```

首先，我们用 3 个元素初始化了向量。这会导致向量为 3 个元素分配存储空间（容量为 3），并且所有 3 个元素都被视为处于活动状态（长度 = 3）。

然后我们调用`resize(5)`，这意味着我们现在想要一个长度为 5 的向量。由于向量只能存储 3 个元素，但它需要 5 个，所以向量需要获得更多的存储空间来容纳额外的元素。

调用`resize()`完成后，我们可以看到向量现在有 5 个元素的空间（容量为 5），并且所有 5 个元素现在都被视为正在使用（长度为 5）。

大多数时候您不需要使用该`capacity()`函数，但我们会在以下示例中多次使用它，以便我们可以看到向量存储发生的情况。

### 存储重新分配及其成本高昂的原因

当`std::vector`更改其管理的存储量时，此过程称为**重新分配**。非正式地，重新分配过程如下：

- 获取`std::vector`具有所需元素数量容量的新内存。这些元素已进行值初始化。
- 旧内存中的元素被复制（或移动，如果可能）到新内存中。然后旧内存被返回到系统。
- 容量和长度`std::vector`被设置为新值。

从外观上看，它似乎`std::vector`已经调整了大小。但从内部来看，内存（以及所有元素）实际上已被替换！

**相关内容**

**在运行时获取新内存的过程称为动态内存分配。我们将在第[19.1 课“使用 new 和 delete 进行动态内存分配”](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/)中介绍这一点。**

由于重新分配通常需要复制数组中的每个元素，因此重新分配是一个昂贵的过程。因此，我们希望尽可能避免重新分配。

**关键见解**

**重新分配通常代价高昂。请避免不必要的重新分配。**

### 为什么要区分长度和容量？

如果需要的话， A`std::vector`会重新分配它的存储空间，但是和梅尔维尔的巴特比一样，它不愿意这样做，因为重新分配存储空间的计算成本很高。

如果 a`std::vector`只跟踪其长度，那么每次`resize()`请求都会导致昂贵的重新分配到新长度。将长度和容量分开可以使 a`std::vector`能够更智能地判断何时需要重新分配。

下面的例子说明了这一点：

```cpp
#include <iostream>
#include <vector>

void printCapLen(const std::vector<int>& v)
{
	std::cout << "Capacity: " << v.capacity() << " Length:"	<< v.size() << '\n';
}

int main()
{
    // Create a vector with length 5
    std::vector v{ 0, 1, 2, 3, 4 };
    v = { 0, 1, 2, 3, 4 }; // okay, array length = 5
    printCapLen(v);

    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    // Resize vector to 3 elements
    v.resize(3); // we could also assign a list of 3 elements here
    printCapLen(v);

    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    // Resize vector back to 5 elements
    v.resize(5);
    printCapLen(v);

    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}
```

这将产生以下内容：

```
Capacity: 5  Length: 5
0 1 2 3 4 
Capacity: 5  Length: 3
0 1 2 
Capacity: 5  Length: 5
0 1 2 0 0
```

当我们用 5 个元素初始化向量时，容量设置为 5，表示向量最初为 5 个元素分配了空间。长度也设置为 5，表示所有这些元素都在使用中。

调用 之后`v.resize(3)`，长度变为 3，以满足我们对较小数组的要求。但是，请注意，容量仍为 5，这意味着向量没有进行重新分配！

最后，我们调用`v.resize(5)`。由于向量的容量已经为 5，因此无需重新分配。它只是将长度改回 5，并对最后两个元素进行值初始化。

通过分离长度和容量，我们在本例中避免了 2 次原本会发生的重新分配。在下一课中，我们将看到逐个向向量添加元素的示例。在这种情况下，每次长度发生变化时不重新分配的能力就显得更为重要。

**关键见解**

**单独跟踪容量和长度可以避免`std::vector`长度改变时的一些重新分配。**

### 向量索引基于长度，而不是容量

您可能会惊讶地发现下标运算符（`operator[]`）和`at()`成员函数的有效索引是基于向量的长度，而不是容量。

在上面的例子中，当`v`容量为 5 且长度为 3 时，只有索引从 0 到 2 是有效的。即使索引在长度为 3（含）和容量为 5（不含）之间的元素存在，它们的索引也被视为超出范围。

**警告**

**下标仅当其位于 0 和向量的长度（而不是其容量）之间时才有效！**

### 缩小`std::vector`

将向量的大小调整得更大将增加向量的长度，并在需要时增加其容量。但是，将向量的大小调整得更小只会减少其长度，而不会减少其容量。

重新分配向量只是为了从不再需要的少数元素中回收内存，这是一个糟糕的选择。但是，如果我们的向量包含大量不再需要的元素，内存浪费可能会非常严重。

为了帮助解决这种情况，`std::vector`有一个成员函数调用`shrink_to_fit()`，它请求向量缩小其容量以匹配其长度。此请求不具约束力，这意味着实现可以自由地忽略它。根据实现认为最好的方式，实现可以决定满足请求，可以部分满足请求（例如减少容量但不是全部），也可以完全忽略请求。

以下是一个例子：

```cpp
#include <iostream>
#include <vector>

void printCapLen(const std::vector<int>& v)
{
	std::cout << "Capacity: " << v.capacity() << " Length:"	<< v.size() << '\n';
}

int main()
{

	std::vector<int> v(1000); // allocate room for 1000 elements
	printCapLen(v);

	v.resize(0); // resize to 0 elements
	printCapLen(v);

	v.shrink_to_fit();
	printCapLen(v);

	return 0;
}
```

在作者的机器上，这会产生以下结果：

```
Capacity: 1000  Length: 1000
Capacity: 1000  Length: 0
Capacity: 0  Length: 0
```

如您所见，当`v.shrink_to_fit()`被调用时，向量将其容量重新分配为 0，释放了 1000 个元素的内存

### 测验时间

#### 问题 #1

std::vector 的长度和容量代表什么？

长度是当前正在使用的元素数量。
       容量是已分配存储空间的元素数量。

为什么长度和容量是不同的值？

容量是单独跟踪的，以便向量可以在长度改变时避免一些重新分配。

有效指标是`std::vector`基于长度还是容量？

长度。

## 16.11 — std::vector 和堆栈行为

假设您正在编写一个程序，用户将在其中输入一系列值（例如一组测试分数）。在这种情况下，他们将输入的值的数量在编译时是未知的，并且每次运行程序时都可能有所不同。您将将这些值存储在一个中`std::vector`以供显示和/或处理。

根据我们目前所讨论的内容，您可以采用以下几种方法来解决这个问题：

首先，您可以询问用户有多少个条目，创建具有该长度的向量，然后要求用户输入该数量的值。

这不是一种坏方法，但它要求用户提前确切知道他们有多少条目，并且不能在计数时犯错误。手动计数超过十或二十个项目可能很乏味——既然我们应该为用户计算输入的值的数量，为什么还要要求用户计算呢？

或者，我们可以假设用户不想输入超过一定数量的值（例如 30），并创建（或调整大小）具有那么多元素的向量。然后我们可以要求用户输入数据，直到他们完成（或直到他们输入的值达到 30 个）。因为向量的长度意味着使用的元素数量，所以我们可以将向量的大小调整为用户实际输入的值的数量。

这种方法的缺点是用户只能输入 30 个值，我们不知道这个数字是太多还是太少。如果用户想输入更多值，那就太糟糕了。

我们可以通过添加一些逻辑来解决这个问题，即当用户达到最大值时，将向量的大小调整得更大。但这意味着我们现在必须将数组大小管理与程序逻辑混合在一起，这将大大增加程序的复杂性（这将不可避免地导致错误）。

这里真正的问题是我们试图猜测用户可能输入多少个元素，以便我们能够适当地管理向量的大小。对于事先确实不知道要输入的元素数量的情况，有一种更好的方法。

但在我们到达那里之前，我们需要先进行简短的侧边栏讨论。

### 什么是堆栈？

类比时间到了！考虑一下自助餐厅里的一堆盘子。由于某种未知的原因，这些盘子特别重，一次只能抬起一个。由于盘子堆叠在一起而且很重，因此您只能通过以下两种方式之一来修改盘子堆：

1. 将新盘子放在堆顶（如果存在，则隐藏下面的盘子）
2. 从堆栈中取出顶板（如果存在，则露出下面的板）

不允许从盘子堆的中间或底部添加或移除盘子，因为那样需要一次抬起多个盘子。

物品添加到堆栈和从堆栈中移除的顺序可以描述为**后进先出 (LIFO)**。最后一个添加到堆栈的盘子将是第一个被移除的盘子。

### 编程中的堆栈

在编程中，**堆栈**是一种容器数据类型，其中元素的插入和删除以 LIFO 方式进行。这通常通过名为**push**和**pop 的**两个操作实现：

| 操作名称 | 行为                 | 必需的？ | 笔记                          |
| :------- | :------------------- | :------- | :---------------------------- |
| Push     | 将新元素放入堆栈顶部 | 是的     |                               |
| Pop      | 从堆栈中移除顶部元素 | 是的     | 可能返回被移除的元素或者 void |

许多堆栈实现也可以选择支持其他有用的操作：

| 操作名称    | 行为                 | 必需的？ | 笔记       |
| :---------- | :------------------- | :------- | :--------- |
| Top or Peek | 获取堆栈顶部元素     | 选修的   | 不移除物品 |
| Empty       | 判断堆栈是否没有元素 | 选修的   |            |
| Size        | 计算堆栈中元素的数量 | 选修的   |            |

堆栈在编程中很常见。在课程[3.9——使用集成调试器：调用堆栈中](https://www.learncpp.com/cpp-tutorial/using-an-integrated-debugger-the-call-stack/)，我们讨论了调用堆栈，它跟踪已调用的函数。调用堆栈是……一个堆栈！（我知道，这个揭示令人失望）。当调用一个函数时，包含有关该函数的信息的条目将添加到调用堆栈的顶部。当函数返回时，包含有关该函数的信息的条目将从调用堆栈的顶部删除。这样，调用堆栈的顶部始终代表当前正在执行的函数，而每个后续条目代表先前正在执行的函数。

例如，这里有一个简短的序列，展示了堆栈的推送和弹出方式：

```
(Stack: empty)
Push 1 (Stack: 1)
Push 2 (Stack: 1 2)
Push 3 (Stack: 1 2 3)
Pop    (Stack: 1 2)
Push 4 (Stack: 1 2 4)
Pop    (Stack: 1 2)
Pop    (Stack: 1)
Pop    (Stack: empty)
```

### C++ 中的堆栈

在某些语言中，堆栈被实现为其自己的离散容器类型（与其他容器分开）。然而，这可能非常有限。考虑一下我们想要打印堆栈中的所有值而不修改堆栈的情况。纯堆栈接口不提供直接方法来执行此操作。

在 C++ 中，类似堆栈的操作被添加到现有的标准库容器类中（作为成员函数），这些容器类支持在一端（`std::vector`、`std::deque`和`std::list`）高效地插入和移除元素。这允许这些容器中的任何一个除了其原生功能外，还可以用作堆栈。

#### 顺便说一下……

**盘子堆的类比很恰当，但我们可以做一个更好的类比，以帮助我们理解如何使用数组实现堆栈。与其考虑一叠盘子（其当前容纳的盘子数量可能不同），不如考虑一列邮箱，所有邮箱都堆叠在一起。每个邮箱只能容纳一件物品，并且所有邮箱一开始都是空的。每个邮箱都钉在它下面的邮箱上，并且柱子的顶部覆盖着有毒的尖刺，因此任何地方都不能插入新的邮箱。**

**如果我们不能改变邮箱的数量，我们如何获得类似堆栈的行为？**

**首先，我们使用记号笔（如便利贴）来标记堆顶的位置——这始终是最低的空邮箱。开始时，堆是空的，因此记号笔放在最底下的邮箱上。**

**当我们将一个项目推送到邮箱堆栈时，我们会将其放入标记的邮箱（即最低的空邮箱），并将标记向上移动一个邮箱。当我们从堆栈中弹出一个项目时，我们会将标记向下移动一个邮箱（因此它指向顶部非空邮箱）并从该邮箱中删除该项目，以便现在邮箱为空。**

**标记下方的项目被视为“在堆栈上”。标记处或上方的项目不在堆栈上。**

**现在，呼叫标记`length`，以及邮箱数量`capacity`……**

在本课的剩余部分，我们将研究堆栈接口的`std::vector`工作原理，然后总结展示它如何帮助我们解决课程开始处介绍的挑战。

### 堆栈行为`std::vector`

堆栈行为`std::vector`通过以下成员函数实现：

| 函数名称         | 堆栈操作    | 行为                                       | 笔记                          |
| :--------------- | :---------- | :----------------------------------------- | :---------------------------- |
| push_back()      | Push        | 将新元素放入堆栈顶部                       | 将元素添加到向量末尾          |
| pop_back()       | Pop         | 从堆栈中移除顶部元素                       | 返回 void，删除向量末尾的元素 |
| back()           | Top or Peek | 获取堆栈顶部元素                           | 不移除物品                    |
| emplace_back（） | Push        | push_back() 的替代形式可能更有效（见下文） | 将元素添加到向量末尾          |

让我们看一个使用其中一些函数的示例：

```cpp
#include <iostream>
#include <vector>

void printStack(const std::vector<int>& stack)
{
	if (stack.empty()) // if stack.size == 0
		std::cout << "Empty";

	for (auto element : stack)
		std::cout << element << ' ';

	// \t is a tab character, to help align the text
	std::cout << "\tCapacity: " << stack.capacity() << "  Length " << stack.size() << "\n";
}

int main()
{
	std::vector<int> stack{}; // empty stack

	printStack(stack);

	stack.push_back(1); // push_back() pushes an element on the stack
	printStack(stack);

	stack.push_back(2);
	printStack(stack);

	stack.push_back(3);
	printStack(stack);

	std::cout << "Top: " << stack.back() << '\n'; // back() returns the last element

	stack.pop_back(); // pop_back() pops an element off the stack
	printStack(stack);

	stack.pop_back();
	printStack(stack);

	stack.pop_back();
	printStack(stack);

	return 0;
}
```

在 GCC 或 Clang 上，这将打印：

```
Empty   Capacity: 0  Length: 0
1       Capacity: 1  Length: 1
1 2     Capacity: 2  Length: 2
1 2 3   Capacity: 4  Length: 3
Top:3
1 2     Capacity: 4  Length: 2
1       Capacity: 4  Length: 1
Empty   Capacity: 4  Length: 0
```

请记住，长度是向量中元素的数量，在本例中，就是堆栈上元素的数量。

与下标运算符`operator[]`或`at()`成员函数不同，`push_back()`(和`emplace_back()`) 将增加向量的长度，并且如果容量不足以插入值，将导致重新分配。

在上面的例子中，向量被重新分配了 3 次（从容量 0 到 1、从 1 到 2、从 2 到 4）。

**关键见解**

**`push_back()`并将`emplace_back()`增加 a 的长度`std::vector`，并且如果容量不足以插入值，将导致重新分配。**

### 推动带来的额外能力

在上面的输出中，请注意，当发生三次重新分配中的最后一次时，容量从 2 跳升至 4（尽管我们只推送了一个元素）。当推送触发重新分配时，`std::vector`通常会分配一些额外的容量以允许添加其他元素，而不会在下次添加元素时触发另一次重新分配。

分配多少额外容量取决于编译器的实现`std::vector`，不同的编译器通常会做不同的事情：

- GCC 和 Clang 将当前容量加倍。触发最后一次调整大小时，容量将从 2 加倍到 4。
- Visual Studio 2022 将当前容量乘以 1.5。触发最后一次调整大小时，容量从 2 变为 3。

因此，根据您使用的编译器，先前的程序的输出可能会略有不同。

### 调整向量大小不适用于堆栈行为

重新分配向量的计算成本很高（与向量的长度成正比），因此我们希望在合理的情况下避免重新分配。在上面的例子中，如果我们在程序开始时手动将向量的大小调整为容量 3，则可以避免对向量进行 3 次重新分配。

让我们看看如果我们将上面例子中的第 18 行更改为以下内容会发生什么：

```cpp
std::vector<int> stack(3); // parenthesis init to set vector's capacity to 3
```

现在当我们再次运行该程序时，我们得到以下输出：

```
0 0 0 	Capacity: 3  Length 3
0 0 0 1 	Capacity: 6  Length 4
0 0 0 1 2 	Capacity: 6  Length 5
0 0 0 1 2 3 	Capacity: 6  Length 6
Top: 3
0 0 0 1 2 	Capacity: 6  Length 5
0 0 0 1 	Capacity: 6  Length 4
0 0 0 	Capacity: 6  Length 3
```

这不对——不知何故，我们的堆栈开头有一堆`0`值！这里的问题是括号初始化（设置向量的初始大小）和`resize()`函数同时设置了容量和长度。我们的向量以 3 的容量开始（这是我们想要的），但长度也被设置为 3。所以我们的向量以 3 个值为 0 的元素开始。我们稍后推送的元素被推送到这些初始元素之上。

当我们打算使用下标来访问元素时，成员函数`resize()`改变向量的长度是可以的（因为我们的索引需要小于长度才有效），但是当我们将向量用作堆栈时，它会导致问题。

我们真正想要的是通过某种方式来改变容量（以避免将来的重新分配）而不改变长度（这会产生向堆栈添加新元素的副作用）。

### 成员函数`reserve()`改变容量（但不改变长度）

成员函数`reserve()`可用于重新分配`std::vector`而不改变当前长度。

`reserve()`下面是与之前相同的例子，但增加了设置容量的调用：

```cpp
#include <iostream>
#include <vector>

void printStack(const std::vector<int>& stack)
{
	if (stack.empty()) // if stack.size == 0
		std::cout << "Empty";

	for (auto element : stack)
		std::cout << element << ' ';

	// \t is a tab character, to help align the text
	std::cout << "\tCapacity: " << stack.capacity() << "  Length " << stack.size() << "\n";
}

int main()
{
	std::vector<int> stack{};

	printStack(stack);

	stack.reserve(6); // reserve space for 6 elements (but do not change length)
	printStack(stack);

	stack.push_back(1);
	printStack(stack);

	stack.push_back(2);
	printStack(stack);

	stack.push_back(3);
	printStack(stack);

	std::cout << "Top: " << stack.back() << '\n';

	stack.pop_back();
	printStack(stack);

	stack.pop_back();
	printStack(stack);

	stack.pop_back();
	printStack(stack);

	return 0;
}
```

在作者的机器上，打印出以下内容：

```
Empty   Capacity: 0  Length: 0
Empty   Capacity: 6  Length: 0
1       Capacity: 6  Length: 1
1 2     Capacity: 6  Length: 2
1 2 3   Capacity: 6  Length: 3
Top: 3
1 2     Capacity: 6  Length: 2
1       Capacity: 6  Length: 1
Empty   Capacity: 6  Length: 0
```

您可以看到，调用`reserve(6)`将容量更改为 6，但不会影响长度。不再发生重新分配，因为 std::vector 足够大，可以容纳我们要推送的所有元素。

**关键见解**

**成员函数`resize()`会改变向量的长度和容量（如果需要）。**
**成员`reserve()`函数只会改变容量（如果需要）**

提示

要增加元素数量`std::vector`：通过索引访问向量时
使用`resize()`。这会更改向量的长度，因此您的索引将有效。使用堆栈操作访问向量时
使用`reserve()`。这会增加容量而不改变向量的长度。

### push_back()`对比`emplace_back()

`push_back()`和都`emplace_back()`将元素推送到堆栈。如果要推送的对象已经存在，`push_back()`则和`emplace_back()`是等效的，并且`push_back()`应该优先使用和。

但是，如果我们要创建一个临时对象（与向量的元素类型相同）以便将其推送到向量上，`emplace_back()`那么效率会更高：

```cpp
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

class Foo
{
private:
    std::string m_a{};
    int m_b{};

public:
    Foo(std::string_view a, int b)
        : m_a { a }, m_b { b }
        {}

    explicit Foo(int b)
        : m_a {}, m_b { b }
        {};
};

int main()
{
	std::vector<Foo> stack{};

	// When we already have an object, push_back and emplace_back are similar in efficiency
	Foo f{ "a", 2 };
	stack.push_back(f);    // prefer this one
	stack.emplace_back(f);

	// When we need to create a temporary object to push, emplace_back is more efficient
	stack.push_back({ "a", 2 }); // creates a temporary object, and then copies it into the vector
	stack.emplace_back("a", 2);  // forwards the arguments so the object can be created directly in the vector (no copy made)

	// push_back won't use explicit constructors, emplace_back will
	stack.push_back({ 2 }); // compile error: Foo(int) is explicit
	stack.emplace_back(2);  // ok

	return 0;
}
```

在上面的例子中，我们有一个`Foo`对象向量。使用`push_back({ "a", 2 })`，我们创建并初始化一个临时`Foo`对象，然后将其复制到向量中。对于复制成本高昂的类型（如`std::string`），此复制可能会导致性能下降。

使用`emplace_back()`，我们不需要创建要传递的临时对象。相反，我们传递用于创建临时对象的参数，并将`emplace_back()`它们转发（使用称为完美转发的功能）到向量，在那里它们用于创建和初始化向量内的对象。这避免了本来会进行的复制。

值得注意的是，`push_back()`不会使用显式构造函数，而`emplace_back()`会。这`emplace_back`更加危险，因为更容易意外调用显式构造函数来执行一些没有意义的转换。

在 C++20 之前，`emplace_back()`不适用于聚合初始化。

**最佳实践**

**`emplace_back()`在创建新的临时对象添加到容器中时，或者当您需要访问显式构造函数时，优先选择此方法。**

**更喜欢`push_back()`其他的。**

**[本文](https://abseil.io/tips/112)对此最佳实践进行了更多解释。**

### 使用堆栈操作解决我们的挑战

现在，我们应该如何应对课程开头介绍的挑战已经很明显了。如果我们事先不知道要向 中添加多少元素`std::vector`，那么使用堆栈函数插入这些元素就是可行的方法。

以下是一个例子：

```cpp
#include <iostream>
#include <limits>
#include <vector>

int main()
{
	std::vector<int> scoreList{};

	while (true)
	{
		std::cout << "Enter a score (or -1 to finish): ";
		int x{};
		std::cin >> x;

		if (!std::cin) // handle bad input
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		// If we're done, break out of loop
		if (x == -1)
			break;

		// The user entered a valid element, so let's push it on the vector
		scoreList.push_back(x);
	}

	std::cout << "Your list of scores: \n";

	for (const auto& score : scoreList)
		std::cout << score << ' ';

	return 0;
}
```

此程序让用户输入测试分数，并将每个分数添加到向量中。用户完成添加分数后，将打印向量中的所有值。

请注意，在这个程序中，我们根本不需要进行任何计数、索引或处理数组长度！我们可以只关注我们希望程序执行的逻辑，并让向量处理所有存储问题！

### 测验时间

#### 问题 #1

编写一个程序，推送和弹出值，并输出以下序列：

```
 (Stack: empty)
Push 1 (Stack: 1)
Push 2 (Stack: 1 2)
Push 3 (Stack: 1 2 3)
Pop    (Stack: 1 2)
Push 4 (Stack: 1 2 4)
Pop    (Stack: 1 2)
Pop    (Stack: 1)
Pop    (Stack: empty)
```

```cpp
#include <iostream>
#include <vector>

void printStackValues(const std::vector<int>& v)
{
    std::cout << "\t(Stack:";

    for (auto e : v)
        std::cout << ' ' << e;

    if (v.empty()) // if v.size == 0
        std::cout << " empty";

    std::cout << ")\n";
}

void pushAndPrint(std::vector<int>& v, int val)
{
    v.push_back(val);
    std::cout << "Push " << val;
    printStackValues(v);
}

void popAndPrint(std::vector<int>& v)
{
    v.pop_back();
    std::cout << "Pop ";
    printStackValues(v);
}

int main()
{
    std::vector<int> v {};

    printStackValues(v);

    pushAndPrint(v, 1);
    pushAndPrint(v, 2);
    pushAndPrint(v, 3);
    popAndPrint(v);
    pushAndPrint(v, 4);
    popAndPrint(v);
    popAndPrint(v);
    popAndPrint(v);

    return 0;
}
```

## 16.12 — std::vector<bool>

在课程[O.1 — 通过 std::bitset 进行位标志和位操作](https://www.learncpp.com/cpp-tutorial/bit-flags-and-bit-manipulation-via-stdbitset/)中，我们讨论了如何`std::bitset`将 8 个布尔值压缩为一个字节。然后可以通过 的成员函数修改这些位`std::bitset`。

`std::vector`有一个有趣的技巧。有一个特殊的实现`std::vector<bool>`，可以通过类似地将 8 个布尔值压缩为一个字节来提高布尔值的空间效率。

**对于高级读者**

**当模板类针对特定模板类型参数有不同的实现时，这称为类模板特化。我们将在第[26.4](https://www.learncpp.com/cpp-tutorial/class-template-specialization/)课“类模板特化”中进一步讨论这个主题。**

`std::bitset`与为位操作而设计的不同的是，它`std::vector<bool>`缺少位操作成员函数。

### 使用`std::vector<bool>`

大多数情况下，`std::vector<bool>`其工作原理与正常一样`std::vector`：

```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<bool> v { true, false, false, true, true };

    for (int i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    // Change the Boolean value with index 4 to false
    v[4] = false;

    for (int i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}
```

在作者的 64 位机器上，打印内容如下：

```
1 0 0 1 1
1 0 0 1 0
```

### `std::vector<bool>`权衡

然而，`std::vector<bool>`用户应该注意一些权衡。

首先，`std::vector<bool>`具有相当高的开销（`sizeof(std::vector<bool>)`在作者的机器上为 40 字节），因此，除非您分配的布尔值多于架构的开销，否则不会节省内存。

其次，的性能`std::vector<bool>`高度依赖于实现（因为实现甚至不需要进行优化，更不用说做好了）。根据[这篇文章](https://isocpp.org/blog/2012/11/on-vectorbool)，高度优化的实现可以比其他方案快得多。然而，优化不佳的实现会更慢。

第三，也是最重要的一点，`std::vector<bool>`它不是一个向量（它不需要在内存中连续），也不保存`bool`值（它保存的是位的集合），也不符合 C++ 对容器的定义。

尽管`std::vector<bool>`在大多数情况下其行为类似于向量，但它与标准库的其余部分并不完全兼容。适用于其他元素类型的代码可能无法与 兼容`std::vector<bool>`。

例如，以下代码在`T`是除 之外的任何类型时都能正常工作`bool`：

```cpp
template<typename T>
void foo( std::vector<T>& v )
{
    T& first = v[0]; // get a reference to the first element
    // Do something with first
}
```

### 避免`std::vector<bool>`

现代的共识是`std::vector<bool>`通常应该避免这种情况，因为它不是一个合适的容器，因此性能提升不太可能值得不兼容的麻烦。

不幸的是，这个优化版本的`std::vector<bool>`是默认启用的，并且无法禁用它，转而使用实际上是容器的非优化版本。有人呼吁弃用`std::vector<bool>`，目前正在研究 的替代压缩向量`bool`可能是什么样子（也许作为未来的`std::dynamic_bitset`）。

我们的建议如下：

- `std::bitset`当您在编译时知道所需的位数、需要存储的布尔值数量不超过中等数量（例如，低于 64k）并且有限的运算符和成员函数集（例如，缺少迭代器支持）满足您的要求时，请使用（constexpr）。
- `std::vector<char>`当您需要一个可调整大小的布尔值容器且不需要节省空间时，此类型是首选。此类型的行为类似于普通容器。
- 当您需要动态位集来执行位操作时，请优先使用动态位集的第三方实现（例如`boost::dynamic_bitset`）。此类类型不会假装是标准库容器，而实际上它们并不是。

**最佳实践**

**青睐`constexpr std::bitset`、`std::vector<char>`或第三方动态位集`std::vector<bool>`。**

## 16.x — 第 16 章总结和测验

### 章节回顾

容器是一种数据类型，用于存储一组未命名的对象（称为**元素**）。当我们需要处理一组相关值时，我们通常会使用容器**。**

容器中元素的数量通常称为其**长度**（有时也称为**计数**）。在 C++ 中，术语**大小**也常用于表示容器中元素的数量。在大多数编程语言（包括 C++）中，容器都是**同质的**，这意味着容器中的元素必须具有相同的类型。

容器**库**是 C++ 标准库的一部分，其中包含实现一些常见容器类型的各种类类型。实现容器的类类型有时称为**容器类**。

数组是一种容器数据类型，用于**连续**存储一系列值（即每个元素都放置在相邻的内存位置，没有间隙）。数组允许快速、直接地访问任何元素**。**

C++ 包含三种主要数组类型：（C 风格）数组、`std::vector`容器类和`std::array`容器类。

`std::vector`是 C++ 标准容器库中实现数组的容器类之一。`std::vector`在 <vector> 标头中定义为类模板，带有定义元素类型的模板类型参数。因此，`std::vector<int>`声明一个`std::vector`元素类型为 的`int`。

**容器通常具有一个称为列表构造函数的**特殊构造函数，它允许我们使用初始化列表构造容器的实例。使用带有初始化值列表的列表初始化来构造具有这些元素值的容器。

在 C++ 中，访问数组元素的最常见方式是使用数组名称和下标运算符 ( `operator[]`)。要选择特定元素，请在下标运算符的方括号内提供一个整数值，该整数值标识要选择的元素。此整数值称为**下标**（或非正式地称为**索引**）。使用索引 0 访问第一个元素，使用索引 1 访问第二个元素，依此类推…因为索引从 0 开始而不是从 1 开始，所以我们说 C++ 中的数组是**从零开始的**。

`operator[]`不进行任何类型的**边界检查**，这意味着它不会检查索引是否在 0 到 N-1（含）的范围内。传递无效索引`operator[]`将导致未定义的行为。

**数组是少数允许随机访问**的容器类型之一，这意味着无论容器中元素的数量有多少，都可以直接且以相同的速度访问容器中的每个元素。

构造类类型对象时，会从其他匹配的构造函数中选择匹配的列表构造函数。构造容器（或任何具有列表构造函数的类型）时，如果初始化器不是元素值，请使用直接初始化。

```cpp
std::vector v1 { 5 }; // defines a 1 element vector containing value `5`.
std::vector v2 ( 5 ); // defines a 5 element vector where elements are value-initialized.
```

`std::vector`可以是 const，但不能是 constexpr。

每个标准库容器类都定义了一个嵌套的 typedef 成员，名为`size_type`（有时写作`T::size_type`），它是容器长度（和索引，如果支持）所用类型的别名。`size_type`几乎总是 的别名`std::size_t`，但可以重写（在极少数情况下）以使用其他类型。 我们可以合理地假设`size_type`是 的别名`std::size_t`。

访问`size_type`容器类的成员时，我们必须使用容器类的完全模板名称限定其范围。例如，`std::vector<int>::size_type`。

我们可以使用成员函数向容器类对象询问其长度`size()`，该函数将长度返回为 unsigned `size_type`。在 C++17 中，我们还可以使用`std::size()`非成员函数。

在 C++20 中，`std::ssize()`非成员函数将长度作为大的*有符号*整数类型返回（通常为`std::ptrdiff_t`，该类型通常用作 的有符号对应部分`std::size_t`）。

使用成员函数访问数组元素会进行运行时边界检查（如果边界超出范围，则会`at()`引发类型的异常）。如果未捕获异常，应用程序将被终止。`std::out_of_range`

`operator[]`和成员函数都`at()`支持使用非常量索引进行索引。但是，两者都要求索引为类型`size_type`，即无符号整数类型。当索引为非常量时，这会导致符号转换问题。

类型的对象`std::vector`可以像任何其他对象一样传递给函数。这意味着如果我们`std::vector`按值传递，则会进行昂贵的复制。因此，我们通常`std::vector`通过 (const) 引用传递以避免此类复制。

我们可以使用函数模板将`std::vector`具有任何元素类型的 传递给函数。您可以使用`assert()`来确保传入的向量具有正确的长度。

术语**“复制语义”**是指确定如何复制对象的规则。当我们说调用复制语义时，这意味着我们已经做了一些将复制对象的事情。

当数据的所有权从一个对象转移到另一个对象时，我们说数据已被**移动**。

**移动语义**是指确定如何将数据从一个对象移动到另一个对象的规则。调用移动语义时，可以移动的任何数据成员都会被移动，而不能移动的任何数据成员都会被复制。移动数据而不是复制数据的能力可以使移动语义比复制语义更高效，尤其是当我们可以用廉价的移动代替昂贵的复制时。

通常，当使用相同类型的对象初始化对象或为其分配对象时，将使用复制语义（假设未省略复制）。当对象的类型支持移动语义，并且初始化器或分配的对象是右值时，将自动使用移动语义。

我们可以通过值返回可移动类型（如`std::vector`和`std::string`）。此类类型将以低成本移动其值，而不是进行昂贵的复制。

按某种顺序访问容器中的每个元素称为**遍历**或**遍历**容器。遍历有时也称为**迭代**或**迭代通过**容器。

循环通常用于遍历数组，循环变量用作索引。请注意“一次错误”，即循环体执行的次数过多或过少。

**基于范围的 for 循环**（有时也称为**for-each 循环**）允许遍历容器而无需进行显式索引。遍历容器时，优先使用基于范围的 for 循环，而不是常规 for 循环。

使用类型推导 ( `auto`) 和基于范围的 for 循环让编译器推导数组元素的类型。每当您通常通过 (const) 引用传递该元素类型时，元素声明都应使用 (const) 引用。`const auto&`除非您需要使用副本，否则请考虑始终使用。这将确保即使元素类型后来发生变化也不会进行复制。

无范围枚举可用作索引，并有助于提供有关索引含义的任何信息。

当我们需要一个表示数组长度的枚举器时，添加额外的“计数”枚举器很有用。您可以断言或 static_assert 数组的长度等于计数枚举器，以确保使用预期数量的初始化器初始化数组。

数组长度必须在实例化时定义，并且不能更改的数组称为**固定大小数组**或**固定长度数组**。**动态数组**（也称为**可调整大小数组**）是实例化后可以更改大小的数组。这种可调整大小的能力是其特殊之处`std::vector`。

实例化之后，可以通过调用具有新所需长度的成员函数`std::vector`来调整A 的大小。`resize()`

在 a 的上下文中`std::vector`，**容量**是指已分配存储空间的元素数量`std::vector`，**长度**是指当前正在使用的元素数量。我们可以`std::vector`通过成员函数询问 a 的容量`capacity()`。

当`std::vector`更改其管理的存储量时，此过程称为**重新分配**。由于重新分配通常需要复制数组中的每个元素，因此重新分配是一个昂贵的过程。因此，我们希望尽可能避免重新分配。

下标运算符（`operator[]`）和`at()`成员函数的有效索引基于向量的长度，而不是容量。

`std::vector`有一个成员函数`shrink_to_fit()`，要求向量缩小其容量以匹配其长度。此请求不具约束力。

堆栈中添加和移除元素的顺序可以描述为**后进先出 (LIFO)**。最后添加到堆栈中的盘子将是第一个被移除的盘子。在编程中，**堆栈**是一种容器数据类型，其中元素的插入和移除以 LIFO 方式进行。这通常通过名为**push**和**pop 的**两个操作来实现。

`std::vector`成员函数和`push_back()`将`emplace_back()`增加 的长度`std::vector`，并且如果容量不足以插入值，将导致重新分配。当推送触发重新分配时，`std::vector`通常会分配一些额外的容量以允许添加其他元素，而不会在下次添加元素时触发另一次重新分配。

成员函数`resize()`会改变向量的长度和容量（如果需要）。
成员`reserve()`函数只会改变容量（如果需要）

要增加中的元素数量`std::vector`：

- 通过索引访问向量时使用`resize()`。这会改变向量的长度，以使索引有效。
- 使用堆栈操作访问向量时使用`reserve()`。这会增加容量而不改变向量的长度。

`push_back()`和都`emplace_back()`将元素推送到堆栈上。如果要推送的对象已经存在，`push_back()`和`emplace_back()`是等效的。但是，在我们创建临时对象以将其推送到向量上的情况下，`emplace_back()`可能会更有效。当创建新的临时对象以添加到容器中时，或者当您需要访问显式构造函数时，首选 emplace_back()。否则，首选 push_back()。

有一个特殊的实现`std::vector<bool>`，可以通过将 8 个布尔值压缩为一个字节来提高布尔值的空间效率。

`std::vector<bool>`不是向量（它不需要在内存中连续），也不保存`bool`值（它保存的是位的集合），也不符合 C++ 对容器的定义。虽然`std::vector<bool>`在大多数情况下表现得像向量，但它与标准库的其余部分并不完全兼容。适用于其他元素类型的代码可能无法与 一起使用`std::vector<bool>`。因此，`std::vector<bool>`通常应避免使用 。

### 测验时间

#### 问题 #1

写出下列内容的定义。尽可能使用 CTAD（[13.14 -- 类模板参数推导（CTAD）和推导指南](https://www.learncpp.com/cpp-tutorial/class-template-argument-deduction-ctad-and-deduction-guides/)）。

a)`std::vector`用前 6 个偶数初始化A。

```cpp
std::vector evens { 2, 4, 6, 8, 10, 12 };
```

b)`std::vector`用值`1.2`、`3.4`、`5.6`和初始化的常数`7.8`。

```cpp
const std::vector d { 1.2, 3.4, 5.6, 7.8 }; // reminder: std::vector can't be constexpr
```

c)使用名称“Alex”、“Brad”、“Charles”和“Dave”初始化`std::vector`的常量。`std::string_view`

```cpp
using namespace std::literals::string_view_literals; // for sv suffix
const std::vector names { "Alex"sv, "Brad"sv, "Charles"sv, "Dave"sv }; // sv suffix needed for CTAD to infer std::string_view
```

d）具有`std::vector`单个元素值的A。

```cpp
std::vector v { 12 };
```

e）A`std::vector`包含 12 个 int 元素，初始化为默认值。

```cpp
std::vector<int> v( 12 );
```

当使用初始长度初始化 a 时`std::vector`，我们必须使用直接初始化。我们还必须明确指定类型模板参数，因为没有初始化器可以从中推断元素类型。

#### 问题 #2

假设您正在编写一款游戏，玩家可以持有 3 种类型的物品：生命药水、火把和箭。

##### \> 步骤#1

在命名空间中定义一个无作用域枚举来识别不同类型的物品。定义一个`std::vector`来存储玩家携带的每种物品类型的数量。玩家应该从 1 个生命药水、5 个火把和 10 支箭开始。断言以确保数组具有正确数量的初始化器。

提示：定义一个计数枚举器并在断言内部使用它。

该程序应输出以下内容：

```cpp
You have 16 total items
```

```c++
#include <cassert>
#include <iostream>
#include <vector>

namespace Items
{
    enum Type
    {
        health_potion,
        torch,
        arrow,
        max_items
    };
}

// Inventory items should have integral quantities, so we don't need a function template here
int countTotalItems(const std::vector<int>& inventory)
{
    int sum { 0 };
    for (auto e: inventory)
        sum += e;
    return sum;
}

int main()
{
    std::vector inventory { 1, 5, 10 };
    assert(std::size(inventory) == Items::max_items); // make sure our inventory has the correct number of initializers

    std::cout << "You have " << countTotalItems(inventory) << " total items\n";

    return 0;
}
```

##### \> 步骤#2

修改上一步中的程序，使其现在输出：

```
You have 1 health potion
You have 5 torches
You have 10 arrows
You have 16 total items
```

使用循环打印出每个库存物品的数量和物品名称。处理名称的正确复数形式。

```c++
#include <cassert>
#include <iostream>
#include <string_view>
#include <type_traits> // for std::is_integral and std::is_enum
#include <vector>

namespace Items
{
    enum Type: int
    {
        health_potion,
        torch,
        arrow,
        max_items
    };
}

std::string_view getItemNamePlural(Items::Type type)
{
    switch (type)
    {
        case Items::health_potion:  return "health potions";
        case Items::torch:          return "torches";
        case Items::arrow:          return "arrows";

        default:                    return "???";
    }
}

std::string_view getItemNameSingular(Items::Type type)
{
    switch (type)
    {
        case Items::health_potion:  return "health potion";
        case Items::torch:          return "torch";
        case Items::arrow:          return "arrow";

        default:                    return "???";
    }
}

// Helper function to convert `value` into an object of type std::size_t
// UZ is the suffix for literals of type std::size_t.
template <typename T>
constexpr std::size_t toUZ(T value)
{
    // make sure T is an integral type
    static_assert(std::is_integral<T>() || std::is_enum<T>());

    return static_cast<std::size_t>(value);
}


void printInventoryItem(const std::vector<int>& inventory, Items::Type type)
{
    bool plural { inventory[toUZ(type)] != 1 };
    std::cout << "You have " << inventory[toUZ(type)] << ' ';
    std::cout << (plural ? getItemNamePlural(type) : getItemNameSingular(type)) << '\n';
}

// Inventory items should have integral quantities, so we don't need a function template here
int countTotalItems(const std::vector<int>& inventory)
{
    int sum { 0 };
    for (auto e: inventory)
        sum += e;
    return sum;
}

int main()
{
    std::vector inventory { 1, 5, 10 };
    assert(std::size(inventory) == Items::max_items); // make sure our inventory has the correct number of initializers

    // Since we can't iterate over an enumerated type using a ranged-for, we'll need to use a traditional for-loop here
    for (int i=0; i < Items::max_items; ++i)
    {
        auto item { static_cast<Items::Type>(i) };
        printInventoryItem(inventory, item);
    }

    std::cout << "You have " << countTotalItems(inventory) << " total items\n";

    return 0;
}
```

#### 问题 #3

编写一个函数，该函数接受一个`std::vector`，返回一个`std::pair`包含数组中具有最小值和最大值的元素的索引的函数。 的文档可以[在这里](https://en.cppreference.com/w/cpp/utility/pair)`std::pair`找到。 在以下两个向量上调用该函数：

```cpp
std::vector v1 { 3, 8, 2, 5, 7, 8, 3 };
std::vector v2 { 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };
```

该程序应输出以下内容：

```
With array ( 3, 8, 2, 5, 7, 8, 3 ):
The min element has index 2 and value 2
The max element has index 1 and value 8

With array ( 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 ):
The min element has index 4 and value 1.2
The max element has index 5 and value 8.8
```

```c++
#include <iostream>
#include <vector>

template <typename T>
std::pair<std::size_t, std::size_t> findMinMaxIndices(const std::vector<T>& v)
{
    std::size_t min { 0 };
    std::size_t max { 0 };
    for (std::size_t index { 0 }; index < v.size(); ++index)
    {
        if (v[index] < v[min])
            min = index;
        if (v[index] > v[max])
            max = index;
    }

    return { min, max };
}

template <typename T>
void printArray(const std::vector<T>& v)
{
    bool comma { false };
    std::cout << "With array ( ";
    for (const auto& e: v)
    {
        if (comma)
            std::cout << ", ";

        std::cout << e;
        comma = true;
    }
    std::cout << " ):\n";
}

int main()
{
    std::vector v1 { 3, 8, 2, 5, 7, 8, 3 };
    printArray(v1);

    auto m1 { findMinMaxIndices(v1) };
    std::cout << "The min element has index " << m1.first << " and value " << v1[m1.first] << '\n';
    std::cout << "The max element has index " << m1.second << " and value " << v1[m1.second] << '\n';

    std::cout << '\n';

    std::vector v2 { 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };
    printArray(v2);

    auto m2 { findMinMaxIndices(v2) };
    std::cout << "The min element has index " << m2.first << " and value " << v2[m2.first] << '\n';
    std::cout << "The max element has index " << m2.second << " and value " << v2[m2.second] << '\n';

    return 0;
}
```

#### 问题 #4

修改上述程序，使用户可以输入任意多个整数。当用户输入时停止接受输入`-1`。

打印向量并找出最小和最大元素。

当使用输入运行时`3 8 5 2 3 7 -1`，程序应产生以下输出：

```
Enter numbers to add (use -1 to stop): 3 8 5 2 3 7 -1
With array ( 3, 8, 5, 2, 3, 7 ):
The min element has index 3 and value 2
The max element has index 1 and value 8
```

当用户`-1`第一次输入时做一些合理的事情。

```C++
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
std::pair<std::size_t, std::size_t> findMinMaxIndices(const std::vector<T>& v)
{
    std::size_t min { 0 };
    std::size_t max { 0 };
    for (std::size_t index { 0 }; index < v.size(); ++index)
    {
        if (v[index] < v[min])
            min = index;
        if (v[index] > v[max])
            max = index;
    }

    return { min, max };
}

template <typename T>
void printArray(const std::vector<T>& v)
{
    bool comma { false };
    std::cout << "With array ( ";
    for (const auto& e: v)
    {
        if (comma)
            std::cout << ", ";

        std::cout << e;
        comma = true;
    }
    std::cout << " ):\n";
}

int main()
{
    std::vector<int> v1 { };
    std::cout << "Enter numbers to add (use -1 to stop): ";

    while (true)
    {
        int input{};
        std::cin >> input;
        if (input == -1)
            break;

        if (!std::cin) // if the previous extraction failed
        {
            std::cin.clear(); // put us back in 'normal' operation mode
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // and remove the bad input
            continue;
        }

        v1.push_back(input);
    }

    // If the array is empty
    if (v1.size() == 0)
    {
        std::cout << "The array has no elements\n";
    }
    else
    {
        printArray(v1);

        auto m1 { findMinMaxIndices(v1) };
        std::cout << "The min element has index " << m1.first << " and value " << v1[m1.first] << '\n';
        std::cout << "The max element has index " << m1.second << " and value " << v1[m1.second] << '\n';
    }

    return 0;
}
```

#### 问题 #5

让我们实现游戏 C++man（这将是经典儿童私刑游戏[Hangman](https://en.wikipedia.org/wiki/Hangman_(game))的我们的版本）。

如果你以前没有玩过，以下是简要规则：

高级：

- 计算机将随机选择一个单词，并为该单词中的每个字母画一条下划线。
- 如果玩家在猜错 X 次（其中 X 是可配置的）之前猜出单词中的所有字母，则玩家获胜。

每回合：

- 玩家将猜一个字母。
- 如果玩家已经猜出了该字母，则不算数，游戏继续。
- 如果任何下划线代表该字母，则这些下划线将被替换为该字母，然后继续游戏。
- 如果没有下划线代表该字母，则玩家将用掉一次错误的猜测。

地位：

- 玩家应该知道他们还剩下多少次错误的猜测。
- 玩家应该知道他们猜错了哪些字母（按字母顺序）。

因为这是 C++man，所以我们将使用一个`+`符号来表示剩余的错误猜测次数。如果符号用完`+`，您就输了。

以下是完成的游戏的示例输出：

```
Welcome to C++man (a variant of Hangman)
To win: guess the word.  To lose: run out of pluses.

The word: ________   Wrong guesses: ++++++
Enter your next letter: a
No, 'a' is not in the word!

The word: ________   Wrong guesses: +++++a
Enter your next letter: b
Yes, 'b' is in the word!

The word: b_______   Wrong guesses: +++++a
Enter your next letter: c
Yes, 'c' is in the word!

The word: b__cc___   Wrong guesses: +++++a
Enter your next letter: d
No, 'd' is not in the word!

The word: b__cc___   Wrong guesses: ++++ad
Enter your next letter: %
That wasn't a valid input.  Try again.

The word: b__cc___   Wrong guesses: ++++ad
Enter your next letter: d
You already guessed that.  Try again.

The word: b__cc___   Wrong guesses: ++++ad
Enter your next letter: e
No, 'e' is not in the word!

The word: b__cc___   Wrong guesses: +++ade
Enter your next letter: f
No, 'f' is not in the word!

The word: b__cc___   Wrong guesses: ++adef
Enter your next letter: g
No, 'g' is not in the word!

The word: b__cc___   Wrong guesses: +adefg
Enter your next letter: h
No, 'h' is not in the word!

The word: b__cc___   Wrong guesses: adefgh
You lost!  The word was: broccoli
```

##### \> 步骤#1

目标：

- 我们将首先定义单词列表并编写一个随机单词选择器。您可以使用第[8.15 课中的 Random.h——全局随机数 (Random.h)](https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/#RandomH)来提供帮助。

任务：

- 首先定义一个名为 的命名空间`WordList`。初始单词列表为：“mystery”、“broccoli”、“account”、“almost”、“spaghetti”、“opinion”、“beautiful”、“distance”、“luggage”。您可以根据需要添加其他单词。
- 编写一个函数来随机选择一个单词并显示所选的单词。运行该程序几次以确保单词是随机的。

以下是此步骤的示例输出：

```
Welcome to C++man (a variant of Hangman)
To win: guess the word.  To lose: run out of pluses.

The word is: broccoli
```

```cpp
#include <iostream>
#include <vector>
#include "Random.h"

namespace WordList
{
    // Define your list of words here
    std::vector<std::string_view> words { "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage" };

    std::string_view getRandomWord()
    {
        return words[Random::get<std::size_t>(0, words.size()-1)];
    }
}

int main()
{
    std::cout << "Welcome to C++man (a variant of Hangman)\n";
    std::cout << "To win: guess the word.  To lose: run out of pluses.\n";

    std::cout << "The word is: " << WordList::getRandomWord();

    return 0;
}
```

##### 步骤#2

在开发复杂程序时，我们希望逐步进行，每次添加一两个功能，然后确保它们正常工作。接下来添加什么才有意义？

目标：

- 能够绘制游戏的基本状态，将单词显示为下划线。
- 接受用户输入的字母，并进行基本的错误验证。

在此步骤中，我们不会跟踪用户输入了哪些字母。

以下是此步骤的示例输出：

```
Welcome to C++man (a variant of Hangman)
To win: guess the word.  To lose: run out of pluses.

The word: ________
Enter your next letter: %
That wasn't a valid input.  Try again.
Enter your next letter: a
You entered: a
```

任务：

- 创建一个名为的类`Session`，用于存储游戏会话中需要管理的所有数据。目前，我们只需要知道随机单词是什么。

- 创建一个函数来显示游戏的基本状态，其中单词显示为下划线。

- 创建一个函数来接受用户的字母输入。进行基本的输入验证以过滤掉非字母或无关的输入。

  ```C++
  #include <iostream>
  #include <string_view>
  #include <vector>
  #include "Random.h"
  
  namespace WordList
  {
      // Define your list of words here
      std::vector<std::string_view> words { "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage" };
  
      std::string_view getRandomWord()
      {
          return words[Random::get<std::size_t>(0, words.size()-1)];
      }
  }
  
  class Session
  {
  private:
      // Game session data
      std::string_view m_word { WordList::getRandomWord() };
  
  public:
      std::string_view getWord() const { return m_word; }
  };
  
  void draw(const Session& s)
  {
      std::cout << '\n';
  
      std::cout << "The word: ";
      for ([[maybe_unused]] auto c: s.getWord()) // step through each letter of word
      {
          std::cout << '_';
      }
  
      std::cout << '\n';
  }
  
  char getGuess()
  {
      while (true)
      {
          std::cout << "Enter your next letter: ";
  
          char c{};
          std::cin >> c;
  
          // If user did something bad, try again
          if (!std::cin)
          {
              // Fix it
              std::cin.clear();
              std::cout << "That wasn't a valid input.  Try again.\n";
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              continue;
          }
  
          // Clear out any extraneous input
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  
          // If the user entered an invalid char, try again
          if (c < 'a' || c > 'z')
          {
              std::cout << "That wasn't a valid input.  Try again.\n";
              continue;
          }
  
          return c;
      }
  }
  
  int main()
  {
      std::cout << "Welcome to C++man (a variant of Hangman)\n";
      std::cout << "To win: guess the word.  To lose: run out of pluses.\n";
  
      Session s{};
  
      draw(s);
      char c { getGuess() };
      std::cout << "You guessed: " << c << '\n';
  
      return 0;
  }
  ```

  

##### 步骤#3

现在我们可以显示一些游戏状态并获取用户的输入，让我们将用户输入集成到游戏中。

目标：

- 跟踪用户猜中的字母。
- 显示正确猜出的字母。
- 实现基本的游戏循环。

任务：

- 更新 Session 类来追踪到目前为止已经猜到的字母。
- 修改游戏状态函数以同时显示下划线和正确猜出的字母。
- 更新输入程序以拒绝已经猜到的字母。
- 编写一个循环，在退出之前执行 6 次（以便我们可以测试上述内容）。

在这一步中，我们不会告诉用户他们猜测的字母是否在单词中（但我们会将其作为游戏状态显示的一部分显示出来）。

此步骤的棘手部分是决定如何存储用户猜出的字母信息。有几种不同的可行方法可以做到这一点。提示：字母数量是固定的，而且你会经常这样做。

以下是此步骤的示例输出：

```
Welcome to C++man (a variant of Hangman)
To win: guess the word.  To lose: run out of pluses.

The word: ________
Enter your next letter: a

The word: ____a___
Enter your next letter: a
You already guessed that.  Try again.
Enter your next letter: b

The word: ____a___
Enter your next letter: c

The word: ____a___
Enter your next letter: d

The word: d___a___
Enter your next letter: e

The word: d___a__e
Enter your next letter: f

The word: d___a__e
Enter your next letter: g
```

```CPP
#include <iostream>
#include <string_view>
#include <vector>
#include "Random.h"

namespace WordList
{
    // Define your list of words here
    std::vector<std::string_view> words { "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage" };

    std::string_view getRandomWord()
    {
        return words[Random::get<std::size_t>(0, words.size()-1)];
    }
}

class Session
{
private:
    // Game session data
    std::string_view m_word { WordList::getRandomWord() };
    std::vector<bool> m_letterGuessed { std::vector<bool>(26) };

    std::size_t toIndex(char c) const { return static_cast<std::size_t>((c % 32)-1); }

public:
    std::string_view getWord() const { return m_word; }

    bool isLetterGuessed(char c) const { return m_letterGuessed[toIndex(c)]; }
    void setLetterGuessed(char c) { m_letterGuessed[toIndex(c)] = true; }
};

void draw(const Session& s)
{
    std::cout << '\n';

    std::cout << "The word: ";
    for (auto c: s.getWord()) // step through each letter of word
    {
        if (s.isLetterGuessed(c))
            std::cout << c;
        else
            std::cout << '_';
    }

    std::cout << '\n';
}

char getGuess(const Session& s)
{
    while (true)
    {
        std::cout << "Enter your next letter: ";

        char c{};
        std::cin >> c;

        // If user did something bad, try again
        if (!std::cin)
        {
            // Fix it
            std::cin.clear();
            std::cout << "That wasn't a valid input.  Try again.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Clear out any extraneous input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // If the user entered an invalid char, try again
        if (c < 'a' || c > 'z')
        {
            std::cout << "That wasn't a valid input.  Try again.\n";
            continue;
        }

        // If the letter was already guessed, try again
        if (s.isLetterGuessed(c))
        {
            std::cout << "You already guessed that.  Try again.\n";
            continue;
        }

        // If we got here, this must be a valid guess
        return c;
    }
}

int main()
{
    std::cout << "Welcome to C++man (a variant of Hangman)\n";
    std::cout << "To win: guess the word.  To lose: run out of pluses.\n";

    Session s {};

    int count { 6 };
    while (--count)
    {
        draw(s);
        char c { getGuess(s) };
        s.setLetterGuessed(c);
    }

    // Draw the final state of the game
    draw(s);

    return 0;
}
```

##### \> 步骤#4

目标：完成游戏。

任务：

- 添加显示剩余错误猜测总数

- 添加猜错字母的显示

- 添加胜利/失败条件和胜利/失败文本。

  ```CPP
  #include <iostream>
  #include <string_view>
  #include <vector>
  #include "Random.h"
  
  namespace Settings
  {
      constexpr int wrongGuessesAllowed { 6 };
  }
  
  namespace WordList
  {
      // Define your list of words here
      std::vector<std::string_view> words { "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage" };
  
      std::string_view getRandomWord()
      {
          return words[Random::get<std::size_t>(0, words.size()-1)];
      }
  }
  
  class Session
  {
  private:
      // Game session data
      std::string_view m_word { WordList::getRandomWord() };
      int m_wrongGuessesLeft { Settings::wrongGuessesAllowed };
      std::vector<bool> m_letterGuessed { std::vector<bool>(26) };
  
      std::size_t toIndex(char c) const { return static_cast<std::size_t>((c % 32)-1); }
  
  public:
      std::string_view getWord() const { return m_word; }
  
      int wrongGuessesLeft() const { return m_wrongGuessesLeft; }
      void removeGuess() { --m_wrongGuessesLeft; }
  
      bool isLetterGuessed(char c) const { return m_letterGuessed[toIndex(c)]; }
      void setLetterGuessed(char c) { m_letterGuessed[toIndex(c)] = true; }
  
      bool isLetterInWord(char c) const
      {
          for (auto ch: m_word) // step through each letter of word
          {
              if (ch == c)
                  return true;
          }
  
          return false;
      }
  
      bool won()
      {
          for (auto c: m_word) // step through each letter of word
          {
              if (!isLetterGuessed(c))
                  return false;
          }
  
          return true;
      }
  };
  
  void draw(const Session& s)
  {
      std::cout << '\n';
  
      std::cout << "The word: ";
      for (auto c: s.getWord()) // step through each letter of word
      {
          if (s.isLetterGuessed(c))
              std::cout << c;
          else
              std::cout << '_';
      }
  
      std::cout << "   Wrong guesses: ";
      for (int i=0; i < s.wrongGuessesLeft(); ++i)
          std::cout << '+';
  
  
      for (char c='a'; c <= 'z'; ++c)
          if (s.isLetterGuessed(c) && !s.isLetterInWord(c))
              std::cout << c;
  
      std::cout << '\n';
  }
  
  char getGuess(const Session& s)
  {
      while (true)
      {
          std::cout << "Enter your next letter: ";
  
          char c{};
          std::cin >> c;
  
          // If user did something bad, try again
          if (!std::cin)
          {
              // Fix it
              std::cin.clear();
              std::cout << "That wasn't a valid input.  Try again.\n";
              std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
              continue;
          }
  
          // Clear out any extraneous input
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  
          // If the user entered an invalid char, try again
          if (c < 'a' || c > 'z')
          {
              std::cout << "That wasn't a valid input.  Try again.\n";
              continue;
          }
  
          // If the letter was already guessed, try again
          if (s.isLetterGuessed(c))
          {
              std::cout << "You already guessed that.  Try again.\n";
              continue;
          }
  
          // If we got here, this must be a valid guess
          return c;
      }
  }
  
  void handleGuess(Session &s, char c)
  {
      s.setLetterGuessed(c);
  
      if (s.isLetterInWord(c))
      {
          std::cout << "Yes, '" << c << "' is in the word!\n";
          return;
      }
  
      std::cout << "No, '" << c << "' is not in the word!\n";
      s.removeGuess();
  }
  
  int main()
  {
      std::cout << "Welcome to C++man (a variant of Hangman)\n";
      std::cout << "To win: guess the word.  To lose: run out of pluses.\n";
  
      Session s{};
  
      while (s.wrongGuessesLeft() && !s.won())
      {
          draw(s);
          char c { getGuess(s) };
          handleGuess(s, c);
      }
  
      // Draw the final state of the game
      draw(s);
  
      if (!s.wrongGuessesLeft())
          std::cout << "You lost!  The word was: " << s.getWord() << '\n';
      else
          std::cout << "You won!\n";
  
      return 0;
  }
  ```

  
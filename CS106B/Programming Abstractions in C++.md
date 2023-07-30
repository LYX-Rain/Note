# Programming Abstractions in C++

## Overview of C++

### First C++ program

C++ 是 C 语言的扩展，学习任何语言的第一个程序，输出“hello world”

```C++
#include <iostream>
using namespace std;

int main() {
    cout << "hello, world" << endl;
    return 0;
}
```

### The history of C++

早期程序是用机器语言写的，机器语言是可以由机器直接执行的原始指令，其结构主要反映了硬件的设计，而不是程序员的需求。此外，每种类型的机器都有自己的机器语言
IBM 的 John Backus 提出了高级语言的想法

#### The object-oriented paradigm

programs are viewed as a collection of data objects that embody particular characteristics and behavior.

#### The compilation process

用 C++ 编写程序的第一步是创建一个包含程序的文本文件，称之为源文件（source file）。在运行前需要将源文件翻译成可执行的形式，这个过程首先调用编译器（compiler）将源文件转换为包含机器语言指令的目标文件（object file），然后将多个目标文件组合在一起，生成可在系统运行的可执行文件（executable file）。其它目标文件通常包括库（libraries）的预定义目标文件，其中包含程序需要的各种操作的机器语言指令。将所有独立的目标文件组合成一个可执行文件的过程称之为链接（linking），编译过程如图所示
When you write a program in C++, your first step is to create a file that contains the text of the program, which is called a **source file**. Before you can run your program, you need to translate the source file into an executable form. The first step in that process is to invoke a program called a **compiler**, which translates the source file into an **object file** containing the corresponding machine-language instructions. This object file is then combined with other object files to produce an **executable file** that can be run on the system. The other object files typically include predefined object files called **libraries** that contain the machine-language instructions for various operations commonly required by programs. The process of combining all the individual object files into an executable file is called **linking**.

![The compilation process](./images/The%20compilation%20process.png "The compilation process")

### The structure of a C++ program

hello world 程序过于简单，为了展示 C++ 的更多特性，这里给出了一个计算2的幂的程序

![The structure of a C++ program](images/The%20structure%20of%20a%20C%2B%2B%20program.png)

如图中注释所示，PowerOfTwo 程序由以下几部分组成

#### Comments

图中大部分文本为英文注释，注释是编译器将忽略的文本，它用于向其他程序员传递信息。多行注释由标记 /* 和 */ 
A **comment** is text that is ignored by the compiler but which nonetheless conveys information to other programmers. A comment consists of text enclosed between the markers /* and */ and may continue over several lines. Alternatively, you can also specify single-line comments, which begin with the characters // and extend through the end of the line.

#### Library inclusions

Modern programs are never written without using **libraries**, which are collections of previously written tools that perform useful operations. C++ defines a number of standard libraries, of which one of the most important is **iostream** . This library defines a set of simple input and output operations based on a data structure called a **stream**, which is a data structure used to manage the flow of information to or from some data source, such as the console or a file.
To gain access to the iostream library, your program must contain the line

```C++
#include <iostream>
```

This line instructs the C++ compiler to read the relevant definitions from what is called a **header file**. The angle brackets in this line indicate that the header file is a system library that is part of standard C++.
Those header files typically end with the suffix .h and are enclosed in quotation marks instead of angle brackets.

In C++, reading in a header file using **#include** is often not sufficient by itself to use a system library. To ensure that the names defined in different parts of a large system do not interfere with one another, the designers of C++ made it possible to segment code into structures called ***namespaces***, each of which keeps track of its own set of names. The standard C++ libraries use a namespace called **std** , whic means that you cannot refer to the names defined in standard header files like **iostream** unless you let the compiler know to which namespace those definitions belong.

Increasingly, professional C++ programmers specify the namespace explicitly by adding the prefix **std::** before each name to which it applies. Using this approach, the first line of the HelloWorld program becomes

> std::cout << "hello, world" << std::endl;

Why don't using namespace std
不同库对同一类、方法有不同的实现，不使用 namespace 可以很方便的看出哪些函数或类来自于 std 标准库

C 语言没有名称空间，因此 C 库需要将库名或某种id嵌入到函数名中，从而区分属于该库的函数
C++ 中使用 namespace（名称空间、命名空间）来解决这个问题，名称空间的主要目的是避免命名冲突

```C++

namespace apple {
    void print(const char* text)
    {
        std::cout << text << std::endl;
    }
}

namespace orange {
    void print(const char* text)
    {
        std::string temp = text;
        std::reverse(temp.begin(), temp.end());
        std::cout << temp << std::endl;
    }
}

int main()
{
    using namespace apple;
    using apple::print;         // 也可指定从名称空间引入的函数
    print("Hello");             // Hello

    orange::print("Hello");     // olleH
}
```

名称空间可以嵌套，class 类也是一种名称空间
namespace 只在限定的作用域下有效，使用的时候应尽量限制在小的作用域内，而不是顶层文件上
C++ 标准库中的所有东西都位于 std 名称空间内

#### Function prototypes

Computation in a C++ program is carried out in the context of ***functions***. A function is a named section of code that performs a specific operation. The **PowersOfTwo** program contains two functions—**main** and **raiseToPower**—each of which is described in more detail in one of the sections that follow. Although the definitions of these functions appear toward the end of the file, the **owersOfTwo** program provides a concise description of the **raiseToPower** function just after the library inclusions. This concise form is called a ***prototype*** and makes it possible to make calls to that function before its actual definition appears.

A C++ prototype consists of the first line of the function definition followed by a semicolon

> int raiseToPower(int n, int k);

This prototype tells the compiler everything it needs to know about how to call that function when it appears in the code. The prototype for raiseToPower indicates that the function takes two integers as arguments and returns an integer as its result.

You must provide the declaration or definition of each function before making any calls to that function. C++ requires such prototype declarations so the compiler can check whether calls to functions are compatible with the function definitions. If you accidentally supply the wrong number of arguments or if the arguments are of the wrong type, the compiler reports an error, which makes it easier to find such problems in your code.

#### The main program

Every C++ program must contain a function with the name main . This function specifies the starting point for the computation and is called when the program starts up. When main has finished its work and returns, execution of the program ends.

The first line of the main function in the PowersOfTwo program is an example of a variable declaration, which reserves space for a value used by the program. In this case, the line

#### Function definitions

### Variables

Variables declarations

In C++, you must ***declare*** each variable before you use it. The primary function of declaring a variable is to make an association between the ***name*** of the variable and the ***type*** of value that variable contains. The placement of the declaration in a program also determines the ***scope*** of the variable, which is the region in which that variable is accessible.

### Data type

#### Integer types

#### Floating-point types

#### Boolean type

#### Characters

#### Strings

字符通常被用作字符序列的形式，在编程中，字符序列被称为*字符串*。在C++中编写字符串常量时，要将所有字符用双引号括起来。与字符一样，C++ 使用转义序列来表示特殊字符。

所有现代编程语言都包含处理字符串的特殊功能。遗憾的是，C++ 定义了两种不同的字符串类型，从而使问题变得复杂：一种是从 C 语言继承下来的老式字符串类型，另一种是支持面向对象范例的更复杂的字符串库。大多数情况下，使用字符串库。可以认为 C++ 提供了一种名为 string 的内置数据类型，它的域是所有字符序列的集合。可以声明字符串类型的变量，并在函数之间来回传递字符串值作为参数和结果。

事实上字符串是一种库类型，而不是内置功能。如果在程序中使用字符串类型，就需要将字符串库添加到 #include 行列表中

```C++
#include <string>
```

此外，由于字符串类型是标准命名空间的一部分，编译器只有在包含以下行时才能识别该类型名称

```C++
using namespace std;
```

#### Enumerated types

正如 ASCII 码，计算机通过为每个字符分配一个数字，将字符数据存储为整数。这种通过给域中的元素编号来将数据编码为整数的想法实际上是一种更为普遍的原则。C++允许通过列出其域中的元素来定义新类型，这种类型被称为***枚举类型***

定义枚举类型的语法是

```C++
enum typename { namelist };
```

其中 typename 是新类型的名称，namelist 是域中常量的列表，以逗号分隔
当C++编译器遇到这个定义时，它会从0开始连续编号的方式为常量列表名赋值。C++也允许手动为枚举类型的每个常量分配明确的基础值

```C++
enum Coin {
    PENNY = 1,
    NICKEL = 5,
    DIME = 10,
    QUARTER = 25,
    HALF_DOLLAR = 50,
    DOLLAR = 100
};
```

如果为某些常量提供了值，但没有为其他常量提供值，C++ 编译器将自动为未指定的常量选择值，并在所提供的最后一个值之后连续编号


#### Compound types

#### keyword

const

const 称之为伪关键字，因为它不改变生成的代码。
有点像类和结构体的可见性，它是一个机制，对开发人员写代码强制特定的规则
const 是一种保证，保证某些东西是不变的，但这只是一个保证，你可以不遵守它
使用 const 的原因是因为这个保证可以简化代码

```C++
int main()
{
    int a = 5;
    a = 2;
    const int b = 5;
    b = 2;      // Error
    // const 在 * 之前的指针可以修改指针的指向，但是不能修改该指针所指向的内容，内容是只可读的
    const int* c = new int;
    int const* c = new int;     // 等价
    *c = 2;     // Error

    // const 在 * 之后表示可以修改指针指向的内容，但不可以修改指针的指向
    int * const d = new int;
    d = &a;     // Error

    const int* const e = new int;   // 所有都不可修改
}
```

const in class
在类中方法名后表示，该方法不能修改类成员变量（通常用于getter方法）
但 C++ 提供了一个关键字 mutable 可以打破这个规则，其修饰的变量可以在常量方法中被修改，通常用于 debug

```C++
class Entity
{
private:
    int m_X, m_Y;
    mutable int m_DebugCount = 0;
public:
    int GetX() const
    {
        m_X = 2;    // Error
        m_DebugCount++;      // ok
        return m_X;
    }
    void SetX(int x)
    {
        m_X = x;
    }
}

void printEntity(const Entity& e)   //此处加了 const 后，函数内部仅能调用类的 const 方法
{
    e.SetX(3);      // Error
    cout << e.GetX() << endl;   
}
```

另一个使用 mutable 的场合是 lambda，labbda 像是也个一次性的小函数

```C++
int main()
{
    int x = 8;
    auto f = [=]() mutable  // 传递的是值 = 而不是引用 &，添加 mutable 使得可以直接修改值，但不影响外部
    {
        x++;
        std::cout << x << std::endl;
    }

    f();
    // x = 8
}
```

#### auto

C++ 中所有变量都有类型，auto 可以由编译器推断出数据类型

```C++
std::string GetName()
{
    return "Cherno";
}

int main()
{
    // 不推荐的用法
    auto name = GetName();  // std::string

    int a = 5;
    auto b = a;             // int

    // 推荐用法
    std::vector<std::string> strings;
    strings.push_back("Apple");
    strings.push_back("Orange");

    for (std::vector<std::string>::iterator it = strings.begin();
        it != strings.end(); it++)
    {

    }

    for (auto it = strings.begin(); it != strings.end; it++)
    {

    }
}
```

### Expressions

#### 三元运算符

实际上是 if 语句的语法糖

```C++
int main()
{
    int s_Level = 1;
    int s_Speed = 2;

    if (s_Level > 5)
        s_Speed = 10;
    else
        s_Speed = 5;
    
    s_Speed = s_Level > 5 ? 10 : 5;
}
```

#### 运算符及其重载

运算符是用一个符号，代替一个函数来执行一些事情，其本质就是函数
重载（overlodaing）术语本质是给运算符重新赋予新的含义（或添加参数，或创建）
运算符重载允许在程序中定义或更改运算符的行为
应该尽量减少使用运算符重载，只在完全有意义的情况下使用

```C++
struct Vector2
{
    float x, y;

    Vector2(float x, float y)
        : x(x), y(y) {}
    
    Vector2 Add(const Vector2& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }
    Vector2 operator+(const Vector2& other) const
    {
        return Add(other);
    }

    Vector2 Multiply(const Vector2& other) const
    {
        return Vector2(x * other.x, y * other.y);
    }
    Vector2 operator*(const Vector2& other) const
    {
        return Multiply(other);
    }

    bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }
};

// 为了直接打印对象，可以重载 cout 的左移运算符
std::ostream& operator<<(std::ostream& stream, const Vector2& other)
{
    stream << other.x << ", " << other.y;
    return stream;
}

int main()
{
    Vector2 position(4.0f, 4.0f);
    Vector2 speed(0.5f, 0.5f);
    Vector2 powerup(1.1f, 1.1f);

    Vector2 result1 = position.Add(speed.Multiply(powerup));
    Vector2 result2 = position + speed * powerup;

    std::cout << result2 << std::endl;
}
```

Java 中实现打印对象是通过重写对象的 toString() 方法，print 函数会直接到用对象的 toString() 方法
== 符号也可以通过重载来实现判断对象是否相等（Java中通过重写类的 equals 方法实现）

### Statements

### macro

在 C++ 中使用预处理器来“宏”化某些操作，在某种程度上实现自动化
当编译 C++ 代码时，首先预处理器会扫面代码中一 # 开头的语句（这是预编译指令符号），当预编译器评估完代码之后，会将评估后的代码给到编译器进行实际的编译
预处理阶段基本上是一个文本编辑阶段，在这个阶段，我们可以控制什么代码会实际给到编译器，这就是宏的用武之地
可以通过宏将代码中的文本替换为其他东西，它与模板是不一样的，因为他们发生的时间不同，模板是在实际编译过程中起作用
宏只是在预处理阶段进行纯文本的替换

```C++
#include <iostream>

#define LOG(x) std::cout << x << endl
#define WAIT std::cin.get()

int main()
{
    LOG("Hello");
    WAIT;
}
```

## Functions and Libraries

### lambda

lambda 本质上就是一个普通函数，只是它不像普通函数一样声明，它在代码的过程中生成，用完即弃
lambda 是定义匿名函数的一种方式
只要有一个函数指针，就可以在使用 lambda

```C++
void ForEach(const std::vector<int>& values, void(*func)(int))
{
    for (int value : values)
        func(value);
}

int main()
{
    std::vector<int> values = {1, 4, 2, 5, 3};
    auto lambda = [](int value) { std::cout << value << std::endl; };
    ForEach(values, [](int value) { std::cout << value << std::endl; });
}
```

多类型返回值

一种做法是在调用函数前创建对应变量的指针作为返回数据的地址，并引用传递给函数
在main 栈帧中预先分配了内存和地址
建议使用结构体

tuple pair

tuple 是一个类，它可以包含多个变量，并不关心其数据类型

```C++
#include <tuple>

std::tuple<std::string, int, double> function()
{
    return std::make_pair(str, num, num2);
}

int main()
{
    auto data = function();
    std::string str = std::get<0>(data);
}
```

Library

导入头文件使用引号还是尖括号实际上没有区别
引号会见检查相对路径，再去检查编译器的 include 路径
如果这个源文件在项目文件夹中（是自己写的代码），使用引号。如果它是一个完全的外部依赖，则使用尖括号，表示来源于外部

在 C++ 中应保留本地库，而不是依赖于包管理器
对于大型项目，推荐从源码构建，对于临时项目，更倾向于链接二进制文件

链接二进制

库通常包含两部分：include 和 library。
include 目录下是一堆头文件，通过它就可以使用预构建的二进制文件中的函数的声明
lib 目录下是预构建的二进制文件，通常有两部分：动态库（dynamic library）和静态库（static library），从而可以选择是静态链接还是动态链接
静态链接会将这个库放到生成的可执行文件中（exe），而动态库是在运行时被链接的(dll)，主要区别是库文件是否被编译到（或链接到）exe文件中
静态链接是在编译时发生的，会更快，因为编译器或链接器知道实际进入应用程序的代码，因此可以进行优化
动态链接发生在运行时，只有真正启动可执行文件时，动态链接库才会被加载到内存中，所以它实际上不是可执行文件的一部分
在 windows 启用一个程序时可能会弹出错误消息：需要 xxx.dll
使用动态链接需要保证在一个可访问的地方（搜索路径上）有对应的 dll 文件

## String

String 本质上是字符数组(character array)
因为 string 是一个固定分配的内存块，是不可变的，因此通常将其声明为常量 const

```C++
int main()
{
    char* name = "Rain";                    // string
    char name2[5] = {'R', 'a', 'i', 'n', 0};   // char array

}
```

在内存中，每个字符串的结束都有一个值为 0 的 null 终止字符(\0)来标记字符串的结束位置。因为我们只有一个char指针，并不知道整个字符串的大小（size），所以用终止字符标记字符串结束位置
也因此 string 字符数组的长度是字符数+1

C++ 的标准库中有一个 string 类，它是一个模板类，它有一个构造函数，接受char指针或const char 指针，并且具有一系列常用函数

```C++
#include <string>

int main()
{
    std::string name = "Rain";
    name.size();

    "Lyx"+"Rain"    // 这只是两个字符串字面量，实际上是数组指针，不能把两个指针向加
    name += "Lyx";  // += 会在字符串类中重载
    //或者使用构造函数将其包围起来，使其成为一个 string 对象
    std::string temp = std::string("Lyx") + "Rain";
    // stdlib 提供了一种更便捷的方法
    std::string temp = "Lyx"s + "Rain";
}
```

传递字符串参数时应使用引用传递

字符串字面量是在两个双引号之间的一串字符，它是一个 const char 数组，长度为字符数+1（因为字符串的最后有一个额外的字符 null）
字符串字面量永远保存在内存的只读区域内，如果要通过字符数组的方式修改它，它会复制一个新的字符串，修改后重新复制给该变量
当需要修改字符串中的某个字符时，应将其定义为字符数组，而不是指针

```C++
#include <stdlib.h>

int main()
{
    const char* name = "Rain";
    char name1[5] = "Rain";
    strlen(name)    //5
}
```

## Streams

## Collections

数据结构可以被组装以形成层次结构。原子数据类型，如 int、char、double和枚举类型，在层次结构中占据最低级别。为了表示更复杂的信息，可以将原子类型组合起来形成更大的结构，这些组合统称为*数据结构*
根据其行为而不是表示形式定义的类型称为*抽象数据类型*，通常缩写为 ADT。抽象数据类型是面向对象编程风格的核心，它鼓励程序员以整体方式思考数据结构。

C++ 标准模板库，容器的底层数据类型由自己决定，所有东西由模板组成

### The Vector class

Vector 的名字背后有一个故事，它不应被成为 Vector，应该叫做 ArrayList，因为其本质是一个动态数组。与数组不同的是，它可以调整数组大小
vector 中使用对象还是对象指针是需要视情况而定的，使用对象便于访问，使用指针便于扩容（一般情况下，优先使用对象）

```C++
struct Vectex
{
    float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex)
{
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
    return stream;
}

int main()
{
    std::vector<Vertex> vertices;
    vertices.push_back(Vectex(1, 2, 3));  // add
    vertices.push_back({4, 5, 6});  // add

    for (int i = 0; i < vertices.size(); i++)
        std::cout << vertices[i] << endl;
    
    vertices.erase(vertices.begin() + 1);   // remove second element
    
    for (Vertex& v : vertices)
        std::cout << v << endl;
}
```

在尝试 push_back 时如果 Vector 不够大，它会重新分配一块更大的内存，然后将原来位置的数据复制到新内存里，然后删除旧位置的内存
这会严重影响性能，应尽量避免（也是优化的重点），特别是基于存储的是对象时

```C++
int main()
{
    std::vector<Vertex> vertices;
    vertices.reserve(3);                    // 提前分配计划的内存
    vertices.emplace_back(1, 2, 3);         // 在 vector 内存中直接构造对象
    vertices.emplace_back(4, 5, 6);
    vertices.emplace_back(7, 8, 9);
}
```

push_back 会先在main函数栈帧中创建对象，然后再复制到 vector 的内存空间中
使用 emplace_back 替代 push_back，emplace_back 函数使用传递给它的参数在分配好的内存中直接构造对象


### The Stack class

```C++
Stack<type> ()

size()
isEmpty()
push(value)
pop()
peek()
clear()
```

### The Queue class

```C++
Queue<type> ()
size()
isEmpty()
enqueue(value)
dequeue()
peek()
clear()
```

### The Map class

A collection that stores pairs, where each pair consists of a first half called a ***key*** and a second half called a ***value***

- sometimes called a "dictionary"
- usage: add(key, value) pairs; look up a value by supplying a key;

Map implementation

- Map: implemented using a linked structure called a *binary search tree*
  - pretty fast for all operations; keys are stored in **sorted order**
  - both kinds of maps implement exactly the same operations

- HashMap: implemented using a special array called a *hash table*.
  - very fast, but keys are stored in unpredictable order

```C++
Map<key type, value type> ()

size()
isEmpty()
put(key, value)
get(key)
remove(key)
containsKey(key)
clear()

map[key]    //重载运算符
```

### The Set class

Set: A collection of unique values (no duplicates allowed)

Set: implemented using a linked structure called a ***binary tree***
- pretty fast; elements are stored in sorted order
- values must have a < operation

HashSet: implemented using a special array called a hash table
- vary fast; elements are stored in unpredictable order
- values must have a hashCode function (provided for most standard types)
  - variant: LinkedHashSet (slightly slower, but remembers insertion order)

Looping over a set

```C++
for (type name : collection) {
    statements;
}
```

```C++
Set<type> ()

size()
isEmpty()
add(value)
remove(value)
constains(value)
clear()
isSubsetOf(set)
first()

s1+s2   // 返回二者的合集
s1*s2   // 返回二者的交集
s1-s2   // 去除s1中s2也有的部分
s1+=s2  // 直接修改s1
s1-=s2
s1*=s2
```

## Designing Classes

从语义上来说类和结构体没有区别，二者唯一的不同是：默认情况下类内的所有东西都是私有 private 的，而结构体默认是 public 的
C++ 中存在结构体的唯一原因是因为它要维持与 C 之间的兼容性

static

类或结构体外的 static 修饰的符号在 link 阶段是局部的，在 link 的时候只在这个编译单元 (.obj) 内可见
extern 关键字会使 linker 在其他的编译单元里寻找其修饰的变量或函数的定义（也称为 外部连接）
如果在头文件（head file）中定义了 static 变量，然后在两个 cpp 文件里包含了该头文件，实际上就是在两个文件都创建了 static 变量（头文件只是复制到头部）

类或结构体内的 static 关键字
几乎所有面向对象的语言中，static 在类中的具有相同的含义：

- 如果修饰变量，意味着所有类的实例共享该变量，称为静态变量，因此没有必要通过类的实例来引用这个变量
- 如果修饰方法，称为静态方法，静态方法可以在没有类实例的情况下被调用，并且在静态方法不能访问非静态变量（没有 this 指针）
  - 每一个非静态方法都会自动获得当前类的实例作为参数（this）

### Constructor

constructor is a special method, which run every time instance object

如果不写构造函数，编译器会提供一个默认的构造函数，但它不做任何事
Java 会帮我们初始化参数（0），但 C++ 不会，必须手动初始化所有内存空间。
构造函数可以带参数也可以不带，可以同时写多个构造函数（重载 overload）
当你使用 static 声明的函数时，并不会调用构造函数
如果只是用静态方法时，可以通过禁止构造函数来禁止实例化

```C++
class Log {
public:
    Log() = delete;

    static void Write() {}
}
```

### Destructor

当销毁一个对象时，会调用 destructor 方法
构造函数通常用于初始化类的成员变量，类似地，当对象即将结束生命周期时，destructor 其所使用的内存
析构函数同时应用于分配到栈和堆的对象，当你使用new给对象分配的存储空间，需要调用delete运算符进行释放

在堆上分配的内存需要手动释放。

```C++
class Entity:
{
public:
    Entity() {
        // Created Entity
    }
    ~Entity() {
        // destroyed Entity
    }
};
```

Inheritance

```C++
class Entity
{
public:
    double X, Y;
}
```

### Vitual Function

虚函数允许在子类中重写（override）父类的方法
虚函数引入动态分配，通过VTable（虚函数表）来实现此编译
VTable 包含基类中所有虚函数的映射，以便能在运行时映射到其重写的函数
如果要 override 函数，必须要在基类中将函数标记为虚函数
C++ 11 中引入 override 关键字用于标记 override 的函数，显式地告诉编译器去寻找基类的虚函数，但这不是必须的，仅为增加代码的可读性和便于检查错误

```C++
class Entity
{
public:
    virtual std::string GetName() { return "Entity";}
};

class Player : public Entity
{
private:
    std::string m_Name;
public:
    Player(const std::string& name) : m_Name(name) {}

    std::string GetName() override { return m_name; }
};

void PrintName(Entity* entity)
{
    std::cout << entity->GetName() << std::endl;
}

int main()
{
    Entity* e = new Entity();
    PrintName(e);       // Entity

    Player* p = new Player("player");
    PrintName(p);       // player
}
```

有两个运行时间损耗与虚函数有关，首先需要额外的内存存储 VTable，其中包含实际基类中指向虚函数表的成员指针
每次调用虚函数需要遍历 VTable 以查看其实际指向的函数 

### Pure Virtual Function

纯虚函数本质上类似与其他语言中的抽象方法和接口 Interface（Java、C#）
原理上纯虚函数允许我们定义一个在基类中没有实现的函数，然后强制子类实现它
不能实例化具有纯虚函数的类

```C++
class Entity
{
public:
    virtual std::string GetName() = 0;  // Pure Virtual Function
};

class Player : public Entity
{
private:
    std::string m_Name;
public:
    Player(const std::string& name) : m_Name(name) {}

    std::string GetName() override { return m_name; }   // must override
};
```

C++ 中没有接口 Interface 关键字，接口只是一种规定：只有纯虚函数，没有成员变量的类

```C++
class Printable
{
public:
    virtual std::string GetClassName() = 0;
}

class Entity : public Printable
{
public:
    virtual std::string GetName() { return "Entity"; };
    std::string GetClassName() { return "Entity"; };
};

class Player : public Entity
{
private:
    std::string m_Name;
public:
    Player(const std::string& name) : m_Name(name) {}

    std::string GetName() override { return m_name; }   // must override
    std::string GetClassName() override { return "Player"; }
};

void Print(Printable* obj)
{
    std:: cout << obj->GetClassName() << std::endl;
}

int main()
{
    Entity* e = new Entity();
    Print(e);   // Entity

    Player* p = new Player("PlayerName");
    Print(p);   // Player
}

```

继承了 Printable 就保证了该类实现了 GetClassName 函数，不实现就无法实例化

### Visibility

访问控制属于面向对象编程的概念，其指的是类中的成员变量和方法的可访问性
C++ 中有三个基本的访问控制修饰符：public、protected、private
类中成员默认是 private 的，结构体默认是 public 的

private 意味着只有*类内才能访问（C++ 中还有 friend 关键字称作友元，可以标记一个类或函数作为Entity类的友元，友元可以访问类中的私有成员）
protected 意味着类内以及所有继承体系中的派生类都可以访问
public 可以在任何地方访问

Local static 局部静态变量

```C++
#include <iostream>

void Function() {
    static int i = 0;
    i++;
    std::cout << i << std::endl;
}

int main() {
    Function();     // 1
    Function();     // 2
    Function();     // 3
    Function();     // 4
}
```

只有一个 i 但是只能在 Function 中访问
单例模式

```C++
class Singleton
{
public:
    static Singleton& Get() {
        static Singleton instance;
        return instance;
    }

    void Hello() {}
}

int main() {
    Singleton::Get().Hello();
}
```

可以用来实现初始化函数，为程序创建所有对象

### 初始化列表

构造函数初始化列表是在构造函数中初始化类成员变量的一种方式
要确保做成员初始化列表时，要与成员变量声明顺序一致

```C++
class Entity
{
private:
    std::string m_Name;
    int m_Score;
public:
    Entity()
        : m_Name("Unknown"), m_Score(0)
    {

    }

    Entity(const std::string& name)
    {
        m_Name = name;
    }
}
```

初始化列表与在构造函数内初始化参数在功能上有一个区别：
在使用类的情况下，对象会被创建两次

```C++
class Entity
{
private:
    std::string m_Name;
    int x, y, z;
public:
    Entity()
        : x(0), y(0), z(0)
    {
        m_Name = "Unknown";
    }
}
```

m_Name 对象会被构造两次，一次是使用默认构造函数，然后是用初始化的构造函数的“Unknown”参数
因为实际发生的是

> m_Name = std::string("Unknown");

创建了两个字符串，一个被直接丢弃

### 创建并初始化对象

内存主要分为两部分：stack 栈和 heap 堆，在创建对象时要选择对象存放的位置
栈上的对象有一个自动的生命周期，由它声明的地方的作用域决定，只要变量超出作用域，就意味着内存被释放了，因为当作用域结束时，栈会弹出，作用域里的东西会被释放
堆中的对象一旦创建就会一直存在，直到手动释放

```C++
#include <iostream>
#include <string>

using String = std::string

class Entity
{
private:
    String m_Name;
public:
    Entity() : m_Name("Unknown") {}
    Entity(const String& name) : m_Name(name) {}

    const String& GetName() const {return m_Name; }
};

int main()
{
    // create on stack
    Entity entity;  // call default constructor
    entity.GetName();   // Unknown
    // create on heap
    Entity* entity1 = new Entity("name");
    (*entity1).GetName();
    entity1->GetName();
    delete entity1;
}
```

如果能在栈上创建对象，就选择在栈上创建，因为这是 C++ 中最快的方法（“管控”）
如果对象很大或很多，应该分配到堆中，栈内存通常较小
如果要将对象放到函数生存期之外，则需要将其分配在堆中

在堆上分配要比在栈上花费更长的时间，并且需要手动释放内存
使用智能指针（smartpointer）可以在堆上创建对象并且当指针超出作用域或没有引用时，对象会被自动删除

### new 关键字

new 是一个操作符，其主要目的是在堆上分配内存，
根据 new 后的数据类型类、基本类型或数组，以字节为单位决定分配内存大小
找到足够大的内存块后，返回其地址，给出指向那块内存的指针
使用 new 创建对象，在分配内存后，它会调用构造函数

空闲列表（free list）会维护有空闲字节的地址

通常调用 new 会调用 C 的 malloc 函数来分配内存

```C++
Entity* e = new Entity();
Entity* e = (Entity*) malloc(sozeof(Entity));
```

二者的区别仅在于 new 在分配完内存后会调用构造函数，而第二行仅分配内存

使用 new 后必须使用 delete 关键字手动释放内存
delete 也是一个操作符，它调用了 C 的 free 函数，并调用了 destructor
如果使用 new[] 分配的内存，也需要使用 delete[] 释放

placement new 要决定前面的内存来自哪里，并没有真正分配内存，只是调用构造函数，并在一个特定的内存地址中初始化对象，可以通过写 new()

```C++
int* b = new int[50];
Entity* e = new(b) Entity();
```

隐式转换（隐式构造函数）与explicit关键字

C++ 允许编译器对代码执行一次隐式转换

```C++
class Entity
{
private:
    std::string m_Name;
    int m_Age;
public:
    Entity(const std::string& name)
        : m_Name(name), m_Age(-1) {}
    
    Entity(int age)
        : m_Name("Unknown"), m_Age(age) {}
};

void PrintEntity(const Entity& entity)
{
    // Printing
}

int main()
{
    // Entity a("Cherno");  Entity a = Entity("Cherno");
    Entity a = "Cherno";

    // Entity b(22);        Entity b = Entity(22);
    Entity b = 22;

    PrintEntity(22);        // 可以运行，因为C++认为 22 可以转换成一个 Entity，因为可以调用一个构造函数，22是其唯一参数
    PrintEntity("Cherno");  // 不可运行，因为 “Cherno” 不是 std::string 而是 char 数组，
    // 如果要运行，C++需要做2次转换 const char array -> std::string 和 std::string -> Entity
    // 但C++ 只允许做一次隐式转换，因此需要将其改为：
    PrintEntity(std::string("Cherno"));
    // or
    PrintEntity(Entity("Cherno"));
}
```

它隐式地将 “Cherno” 和 22 转换成一个 Entity，因为有一个Entity的构造函数接受一个string参数，另一个接受int参数

explicit 禁用这个隐式 implicit 功能
explicit 关键字放在构造函数前意味着该构造函数不能通过隐式转换调用，它只能被显式地调用

#### this 关键字

一个非 static 方法必须用一个有效的对象来调用，this 是指向该对象的指针

```C++

void printEntity(const Entity& e);

class Entity
{
public:
    int x, y;

    Entity(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    printEntity(*this);
}
```

### 对象生命周期

在 C++ 中，每次进入一个作用域，本质上是在push栈帧（stack farme），在此作用域下声明的变量和创建的对象（在栈上的）会被封装进栈帧内
一旦作用域结束，该栈帧会被丢弃，其中的所有变量和对象都会消失
作用域可以是任何东西（函数、if、for、while或者空作用域）只要在 { } 内
在局部创建数组是一个典型的错误（在函数中创建基于栈的变量，然后返回它的指针）

作用域指针
它本质是一个类，该类是指针的包装器，在构造时用堆分配指针，然后在析构时删除指针，可以在超出作用域时自动删除堆上的对象

```C++
class Entity
{

};

class ScopedPtr
{
private:
    Entity* m_Ptr;
public:
    ScopedPtr(Entity* ptr)
        : m_Ptr(ptr) {}
    
    ~ScopedPtr()
    {
        delete m_Ptr;
    }
}

int main()
{
    {
        ScopedPtr e = new Entity(); // 隐式转换
    }
}
```

e 是在栈上分配的，当 e 被自动删除时，会调用其析构函数，会 delete 这个被包装的 entity 指针

### 智能指针

智能指针是实现 new 和 delete 过程的自动化的一种方式
当你调用 new 后，不需要手动调用 delete（甚至不需要调用 new）
智能指针本质上是一个原始指针的包装

#### unique_ptr

作用域指针，超出作用域时会自动销毁（delete）
因为该指针是唯一的（不能被复制），所以是 unique

```C++
#include <memory>   // all smart pointer head file

class Entity
{
public:
    Entity()
    {
        std::cout << "Create Entity" << std::endl;
    }

    ~Entity()
    {
        std::cout << "Destroted Entity" << std::endl;
    }
};

int main()
{
    {   // 空作用域
        std::unique_ptr<Entity> entity(new Entity());   // 只能显示地调用构造函数
        std::unique_ptr<Entity> entity = std::make_unique(Entity());    // 这种方式更安全，它会处理构造函数抛出的异常
    }
    // 当作用域结束时，entity 会被自动摧毁
}
```

#### share_ptr

如果要将指针传递到一个函数中或另一类中，则要使用共享指针
share_ptr 的实现方式取决于编译器及其使用的标准库，大多数使用的是**引用计数**跟踪指针有多少个引用，一旦引用数为 0，它就会被删除

```C++
std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
std::shared_ptr<Entity> new_ptr = sharedEntity;
```

share_ptr 需要分配另一块内存，叫作控制块，用来存储引用计数。
如果首先创建一个 new Entity，然后将其传递给 shared_ptr 构造函数，它必须做2次内存分配。而使用 make_shared 函数可以将两次组合起来，一起分配，效率更高

#### weak_ptr

弱指针，和共享指针类似，但数不会增加引用计数（不拥有对象的所有权），仅仅声明该指针还活着
对 Entity 列表排序时，不关心它们是否有效

```C++
std::weak_ptr<Entity> weakEntity = sharedEntity;
```

#### 复制与拷贝构造函数

```C++
struct Vector2
{
    float x, y;
};

int main()
{
    int a = 2;
    int b = a;  // b 创建了一个 a 的副本，a和b是两个独立的变量，有不同的内存地址

    Vector2 a = {2, 3};
    Vector2 b = a   // 类和结构体也是同样的
    // 当对象是指针时，情况就不同了
    Vector2* a = new Vector2();
    Vector2* b = a;     // 实际复制的不是 Vector2 对象，而是其指针，两个指针有相同的值，指向同一块内存
    b->x = 2;   // 会同时影响 a 和 b
}
```

每当将一个变量赋值给另一个变量时，总是在复制
复制指针时，实际复制的是内存地址，而不是指针所指向的实际内存

在赋值对象时，默认会使用浅拷贝（创建一个新的对象并复制原对象的成员变量），当成员变量中有指针时，浅拷贝只会复制指针的值（地址），而不会复制指针所指向的内容，因此两个对象中的指针会指向同一块内存
当要销毁两个对象时，同一块内存会被删除两次，这会导致程序崩溃，因此复制对象时，应使用深拷贝
C++ 中对象的深拷贝通过拷贝构造函数实现，拷贝构造函数是一种特殊的构造函数，当其被拷贝时会被调用
拷贝构造函数名与类名相同，但接收的参数是（const 类名& other）
C++ 提供的默认的拷贝构造函数是浅拷贝的方式，要进行深拷贝需要重写该函数并手动分配内存

使用函数传递参数时应尽量使用 const+引用传递，避免复制

### 箭头运算符

```C++
class Entity
{
public:
    int x;
public:
    void Print() const { std::cout << "Hello" << std::endl; }
};

int main()
{
    Entity e;
    e.Print();

    Entity* ptr = &e;
    ptr.Print();         // 指针本质是一个数值（不是对象）不能调用方法，需要逆向引用(*ptr)
    Entity& entity = *ptr;
    entity.Print();
    // or
    (*ptr).Print();
    // 箭头运算符实际上相当于逆向引用了 Entity 指针，只是一个快捷方式
    ptr->Print();
    ptr->x = 2;
}
```

以上是最常用的做法，但是作为一个运算符，C++ 可以重载它，并在自定义类中使用
例如在使用智能指针时，使其更像一个普通的指针

```C++
class ScopedPtr
{
private:
    Entity* m_Obj;
public:
    ScopedPtr(Entity* entity)
        : m_Obj(entity) {}
    
    ~ScopedPtr()
    {
        delete m_Obj;
    }

    Entity* operator->()
    {
        return m_Obj;
    }
}

int main()
{
    ScopedPtr entity = new Entity();
    entity->Print();
}
```

## Recurision

The definition of an operation in terms of itself.

- Solving a problem using recursion depends on solving smaller occurrences of the same problem.
- Key question: "*How is this problem self-similar?*"



## Backtracking

## Algorithmic Analysis

## Pointers and Arrays

### The structure of memory

### Pointers

#### function pointer

raw function pointer（原始函数指针）来自 C 语言
函数指针是将一个函数赋值给一个变量的方法（也可以将函数作为参数传递给其他函数）
auto 关键字对于函数指针非常有用

```C++
void Print(int a)
{
    std::cout << "Hello" << a << endl;
}

int main()
{
    typedef void(*PrintFunction)(int); // 通常会取个别名
    PrintFunction function = Print;

    Print(3);                // () means call function 
    auto function = Print;  // just name means get function pointer
    void(*func)(int)           // 实际的类型
    func = Print;
    
    function(3);             // call Print function
}
```

函数只是 CPU 指令，当编译完成后，它就在二进制文件的某个地方
当函数被调用时，检索要执行的指令的位置

### Arrays

In C++, an ***array*** is a low-level collection of individual data values with two distinguishing characteristics:

1. *An array is ordered*.
2. *An array is homogeneous*.

使用 new 关键字创建的数组会分配在堆内存中，需要手动释放。与直接创建的区别在于生命周期不同。
如果需要返回某个数组，则应使用 new 关键字创建它，并通过引用传递内存地址。

```C++
int main()
{
    int example[5];             // create on stack
    int* another = new int[5];  // create on heap, need destroy by hand
    delete[] another;
}
```

C++ 11 中引入了标准数组（standard array），相较于原始数组具有很多优点（边界检测和跟踪数组大小）并且语言风格与原始数组一致，并且同样存储在栈上
此外还可以将它作为一个迭代器（有 begin、end），可以使用 foreach 循环遍历，由于它支持迭代器，所以可以使用大量的 STL（标准模板库）算法
在 Debug 模式下会做边界检测，在 release 下实际性能和数组差不多，并且数组的大小是通过预编译在代码段里的，运行时的栈是没有对应变量的

```C++
#include <array>

int main()
{
    std::array<int, 5> data;
    data[0] = 2;

    for (int i = 0; i < data.size(); i++)
    {

    }
}
```

## Dynamic Memory Management

目前为止已经看到了两种为变量分配内存的方式。
静态分配：声明全局变量时，编译器会将其分配在整个程序中持续存在的内存空间，变量被分配到的内存位置在程序的整个生命周期中都不会改变
自动分配（automatic allocation）：在函数中声明局部变量时，该变量会在堆栈中分配。调用函数时会为变量分配内存，函数返回时会释放该内存
动态分配：在程序运行时获取新内存

在程序启动后，操作系统会将整个程序加载到内存中，并分配一堆物理 ram，以便程序的运行
stack 和 heap 是 ram 中实际存在的两个区域，用于存储运行时的数据
stack 通常是一个预定大小的内存区域（通常为 2M byte 左右）
heap 也是一个预定义了默认大小的区域，但是它可以根据程序的运行扩增
stack 和 heap 分配内存的方式是不同的
使用 new 关键字在 heap 上分配内存

```C++
struct Vactor3
{
    float x, y, z;
};

int main()
{
    // in stack
    int value = 5;
    int array[5];
    Vector3 vector;

    // in heap
    int* hvalue = new int;
    *hvalue = 5;        // dereference
    int* harray = new int[5];
    Vector3* hvector = new Vector3();

    delete hvalue;
    delete[] harray;
    delete hvector;
}
```

当在 stack 分配变量时，栈指针基本上就是移动对应大小的字节，按照声明的顺序叠加，因此栈分配内存非常快（就是移动栈指针并返回其地址）
目前大多数的实现方式栈是倒着来的，栈指针从高到低移动

在 heap 中分配的内存需要手动释放，而在 stack 中分配的内存在其对应的作用域结束时，会自动被弹出（释放），
栈内存的释放也非常快，就是将栈指针反向移动到作用域开始之前，一条 CPU 的删除指令就可以释放所有东西

new 关键字实际上调用了 malloc 函数（memory allocate 的缩写），该函数会调用底层操作系统的特定函数为程序在 heap 上分配内存
具体做法是，在程序启动时，操作系统会分配一定大小的物理 ram 给程序，程序会维护一个空闲列表（free list）用于跟踪哪些内存块是空闲的
当调用 malloc 请求堆内存时，它会扫描空闲列表，找到对应大小的空闲内存，并返回一个指针，同时记录一些东西

在 stack 上分配的内存或存储的变量，由于它们在内存中挨得很近，因此可以放到 CPU cache line 上，从而实现更高的 cache 命中率，而在 heap 上的内存可能是 cache miss

### Linked list

```C++
#include <iostream>
#include <string>

struct LinkNode {
    string name;
    LinkNode* next;
}
```

## Efficiency and Representation

## Linear Structures

### Templates

在其他语言中它会被说成是“泛型”，但 C++ 的templates 更强大，它有点像宏，可以做很多事，而泛型受制于类型系统以及其他因素
模板允许你定义一个可以根据用途进行编译的模板，可以让编译器基于你给的规则为你写代码
一般而言，要实现一个函数可以接受不同类型的参数需要通过重载的方式，为每种类型提供各自的实现，但模板提供了一种更高效的方式

```C++

template<typename T>
void Print(T value)
{
    std::cout << value << endl;
}

int main()
{
    Print<int>(5);
    Print("Hello");
    Print(5.5f);
}
```

template 关键字声明了 Print 是一个模板，它会在编译时被评估，它不是一个真的函数，只有实际调用它的时候，这个函数才会被真的创建
当调用这个函数的时候，基于传递的参数，这个函数才被创建出来，并作为源代码被编译
此处使用 typename 作为模板参数的类型，使用 T 作为名字，这个名字实际上是模板的参数名称，可以在整个模板代码中使用它替换出现的数据类型
typename 也可以写为 class，其实是一样的
在使用时，数据类型可以显式地指定，也可以省略，编译器会根据传递的参数推断出类型

模板并不局限于函数，可以通过模板创建一整个类，大量的 C++ 标准模板库同样完全使用了模板
可以通过模板实现在栈上创建一个动态大小的类，在栈上创建对象必须提前知道其大小

```C++
template<typename T, int N>
class Array
{
private:
    T m_Array[N];
public:
    int GetSize() const { return N; }
}
// 实际生成的代码
class Array
{
private:
    std::string m_Array[5];
public:
    int GetSize() const { return 5; }
}

int main()
{
    Array<std::string, 5> array;
}
```

这种创建数组的方式与标准数组类在 C++ 标准模板库中的工作方式相似，这有点像 C++ 的 meta programming（元编程），编译器在编译时实际在进行编程

## Maps

## Trees

## Sets

## Graphs

## Inheritance

## Strategies for iteration

## Thread


```C++
#include <iostream>
#include <thread>

void DoWork()
{

}

int main()
{
    // 启动一个线程执行传入的函数
    std::thread worker(DoWork)      // function pointer
    // 程序会继续执行，直到我们等待它推出，等待一个线程完成它的工作
    work.join()
    // 阻塞当前线程，直到另一个线程完成
}
```

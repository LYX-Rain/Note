# C++ Basics

C++ 是 C 语言的扩展，学习任何语言的第一个程序，输出“hello world”

```C++
#include <iostream>
using namespace std;

int main() {
    cout << "hello, world" << endl;
    return 0;
}
```
## Variables and Basic Types

### 基本内置类型

### 变量



默认初始化

如果定义变量时没有指定初始值，则变量被默认初始化，此时变量被赋予了“默认值”。默认值是什么由变量类型决定，同时也受定义变量的位置影响

定义于任何函数体之外的变量被初始化为0

定义在函数体内部的内置类型变量将**不被初始化**。一个未被初始化的内置类型变量的值是未定义的，如果试图拷贝或以其他形式访问此类值将引发错误

### compound type 复合类型

复合类型是指基于其他类型定义的类型

#### reference 引用

引用为对象起了另外一个名字，引用类型引用（refers to）另一种类型。通过将声明符写成 `&d` 的形式来定义引用类型，其中 `d` 是声明的变量名：

```C++
int ival = 1024;
int &refVal = ival; // refVal 指向 ival（是 ival 的另一个名字）
int $refVal2;       // 报错：引用必须初始化
```

一般在初始化变量时，初始值会被拷贝到新建的对象中。然而定义引用时，程序把引用和它的初始值**绑定（bind）**在一起，而不是将初始值拷贝给引用。一旦初始化完成，引用将和它的初始值对象一直绑定在一起。因此无法令引用重新绑定到另一个对象，因此引用必须初始化

引用即别名：引用并非对象，相反的，它只是为一个已经存在的对象所起的另外一个名字

定义了一个引用之后，对齐进行的所有操作都是在与之绑定的对象上进行的

#### pointer 指针

指针是“指向（point to）”另外一种类型的复合类型。
与引用不同的是
指针本身就是一个对象，允许对指针赋值或拷贝，而且在指针的生命周期内它可以先后指向几个不同的对象
指针无须在定义时赋值。和其他内置类型一样，在块作用域内定义的指针如果没有被初始化，也将拥有一个不确定的值

### const 限定符

#### const 的引用

#### 指针和 const

#### constexpr 和常量表达式

**常量表达式**（const expression）是指值不会改变并且在编译过程就能得到计算结果的表达式。显然，字面量属于常量表达式，用常量表达式初始化的 const 对象也是常量表达式

一个对象（或表达式）是不是常量表达式由它的数据类型和初始值共同决定，例如：

```C++
const int max_files = 20;           // 是
const int limit = max_files + 1;    // 是
int staff_size = 27;                // 不是
const int sz = get_size()           // 不是
```

constexpr 变量

C++ 11 允许将变量声明为 `constexpr` 类型以便由编译器来验证变量的值是否是一个常量表达式。声明为 `constexpr` 的变量一定是一个常量，而且必须用常量表达式初始化：

```C++
constexpr int mf = 20;
constexpr int limit = mf + 1;
constexpr int sz = size();      // 只有当size是一个 constexpr 函数时，才是一条正确的声明语句
```

在 constexpr 声明中如果定义了一个指针，限定符 constexpr 仅对指针有效，与指针所指的对象无关

### 处理类型

## Strings, Vectors, and Arrays

### 标准库类型 string

### 标准库类型 vector

### 迭代器

### 数组

## Expressions



### 成员访问运算符

点运算符和箭头运算符都可用于访问成员，其中，点运算符获取类对象的一个成员；箭头运算符有关，表达式 `ptr->mem` 等价于 `(*ptr).mem`：

```C++
string s1 = "a string", *p = &s1;
auto n = s1.size();
n = (*p).size();
n = p->size();
```

因为解引用运算符的优先级低于点运算符，所以执行解引用运算的子表达式两端必须加上括号

### sizeof 运算符

`sizeof` 运算符返回一条表达式或一个类型名字所占的字节数。`sizeof` 运算符满足右结合律，其所得的值是一个 `size_t` 类型的常量表达式。运算符的运算对象有两种形式：

```C++
sizeof(type)
sizeof expr
```

在第二种形式中，sizeof 返回的是表达式结果类型的大小。
sizeof 并不实际计算其运算对象的值：

sizeof 运算符的结果部分地依赖于其作用的类型

- 对 `char` 或者类型为 `char` 的表达式执行，结果为1
- 对引用类型执行得到被引用对象所占空间的大小
- 对指针执行得到指针本身所占空间的大小
- 对解引用指针执行得到指针指向的对象所占空间的大小，指针不需有效
- 对数组执行得到整个数组所占空间的大小，等价于对数组中所有的元素各执行一次运算并求和。注意：sizeof 运算不会把数组转换成指针来处理
- 对 string 对象或 vector 对象执行只返回该类型固定部分的大小，不会计算对象中的元素占用了多少空间

因为执行 sizeof 运算能得到整个数组的大小，所以可以用数组的大小除以单个元素的大小得到数组中元素的个数：

```C++
constexpr size_t sz = sizeof(ia) / sizeof(*ia);
int arr2[sz];
```

因为 sizeof 的返回是一个常量表达式，所以可以用  sizeof 的结果声明数组的维度

## Statements

## Funcitons

## Classes

# C++ Standard Library

## The IO Library

## Sequential Containers

## Generic Algorithms

## Associative Containers

## Dynamic Memory

### 动态内存与智能指针

#### shared_ptr

#### 直接管理内存

#### unique_ptr

# Computer Systems: A Programmer's Perspective

## A Tour of Computer System

从某种意义上来说，本书的目的就是要帮助你了解当你的系统上执行 hello 程序时，系统发生了什么以及为什么会这样

```C
#include <stdio.h>

int main()
{
    printf("hello, world\n");
    return 0;
}
```

通过跟踪 hello 程序的生命周期来开始对系统的学习——从它被程序员创建开始，到在系统上运行，输出简单的消息，然后终止

### 信息就是位+上下文

hello 程序的生命周期是从一个*源程序*（或源文件）开始的，即程序员通过编辑器创建并保存的文本文件，文件名是 hello.c
源程序实际上就是一个由值0和1组成的位（比特 bit），8个位被组织成一组，称为*字节*
每个字节表示程序中的某些文本字符

大部分现代计算机系统都使用ASCII标准来表示文本字符，这种方式实际上就是用一个唯一的单字节大小的整数值来表示每个字符

hello.c 程序是以字节序列的方式存储在文件中的。每个字节都有一个整数值，对应于某些字符。像 hello.c 这样只由 ASCII 字符构成的文件称为文本文件，所有其他文件都称为*二进制文件*

hello.c 的表示方法说明链一个基本思想：系统中所有的信息都是由一串比特表示的。区分不同数据对象的唯一方法是这些数据的上下文。在不同的上下文中，一个同样的字节序列可能表示一个整数、浮点数、字符串或者机器指令

### 程序被其他程序翻译成不同的格式


预处理阶段：预处理器（cpp）根据以字符 # 开头的命令，修改原始的C程序，得到另一个C程序，通常是以 .i 作为文件扩展名
编译阶段：编译器（ccl）将文本文件 hello.i 翻译成文本文件 hello.s，它包含一个汇编语言程序。

汇编阶段：汇编器（ss）将 hello.s 翻译成机器语言指令，把这些指令打包成一种叫做*可重定位目标程序*（relocatable object program）的格式，并将结果保存在目标文件 hello.o 中。hello.o 文件是一个二进制文件
链接阶段：hello 程序调用了 printf 函数，它是每个C编译器都提供的标准C库中的一个函数。printf 函数存在于一个名为 printf.o 的单独的预编译好了的目标文件中，而这个文件必须以某种方式合并到 hello.o 程序中。链接器（ld）就负责处理这种合并。结果就得到 hello 文件，它是一个*可执行目标文件*（或简称未可执行文件），可以被加载到内存中，由系统执行

## Representing and Manipulating Information

这里主要研究三种重要的数字表示
**无符号**（unsigned）编码基于传统的二进制表示法，表示大于或等于零的数字
**补码**（tow's-complement）编码是表示有符号整数的最常见的方式
**浮点数**（floating-point）编码是表示实数的科学记数法的以2为基数的版本
计算机的表示法是用有限数量的位来对一个数组编码，因此当结果太大以至不能表示时，某些运算就会*溢出*（overflow）
由于表示的精度有限，浮点运算是不可组合的
整数的表示虽然只能编码一个相对较小的数值范围，但是这种表示是精确的，而浮点数只是近似的

### Information Storage

大多数计算机使用8位的块，或者*字节*（byte），作为最小的可寻址的内存单位，而不是访问内存中独立的位。

#### 字数据大小

每台计算机都有一个*字长*（Word size），指明指针数据的标称大小（nominal size）
因为虚拟地址是以这样的一个字来编码的，所以字长决定的最重要的系统参数就是虚拟地址空间的最大大小
32位字长限制虚拟地址空间位4GB（因此32位系统不支持4G以上内存），64位则为16EB

大多数 64 位机器也可以运行 32 位机器编译的程序（向下兼容）

```bash
linux> gcc -m32 prog.c  #可以在 32 位或 64 位机器上运行 
linux> gcc -m64 prog.c  #只能在 64 位机器上运行
```

| C Data Type | 32-bit | 64-bit |
|---|---|--|
| char | 1 | 1 |
| short | 2 | 2 |
| int | 4 | 4 |
| long | 4 | 8 |
| float | 4 | 4 |
| double | 8 | 8 |
| printer | 4 | 8 |

#### 寻址和字节顺序

对于跨越多字节的程序对象必须建立两个规则：这个对象的地址是什么，以及在内存中如何排列这些字节
在几乎所有的机器上，多字节对象都被存储为连续的字节序列，对象的地址为所使用字节中最小的地址

大端法

小端法

### Integer(整数表示)

#### 整数数据类型

#### 无符号数的编码

#### 补码编码

#### 有符号数和无符号数之间的转换

### Integer Arithmetic(整数运算)

#### 无符号加法

#### 补码加法

#### 无符号乘法

#### 补码乘法

#### 乘以常数

#### 除以 2 的幂


计算机执行的“整数”运算实际上是一种模运算形式。表示数字的有限字长限制链可能的值的取值范围，运算结果可能溢出
补码表示提供了一种表示正负数的灵活方法，同时使用了与执行无符号算术相同的位级实现，无论运算数是以无符号形式还是以补码形式表示的，都有完全一样或者非常类似的位级行为

### Floating Point(浮点数)

#### 二进制小数



#### IEEE浮点表示

IEEE 浮点标准用 $ V=(-1)^s \times M \times 2^E $ 的形式来表示一个数：

- 符号（sign）：s 决定这数是负数（s=1）还是正数（s=0），而对于数值 0 的符号位解释作为特殊情况处理
- 尾数（significand）：$M$ 是一个二进制小数，它的范围是 $ 1 \sim 2-\epsilon$ 或者是 $ 0 \sim 1-\epsilon $
- 阶码（exponent）：$E$ 的作用是对浮点数加权，这个权重是 2 的 $E$ 次幂（可能是负数）

将浮点数的位表示划分为三个字段，分别对这些值进行编码：

- 一个单独的符号位 s 直接编码符号 s
- $k$ 位的阶码字段 $exp=e_{k-1}...e_1 e_0$ 编码阶码 $E$
- $n$ 位小数字段 $frac=f_{n-1}...f_1 f_0$ 编码尾数 $M$，但是编码出来的值也依赖于阶码的值是否等于 0

下图给出了将这三个字段装进字中两种最常见的格式。
在单精度浮点格式（C语言中的float）中，s、exp和frac字段分别为 1 位、$k=8$ 位和 $n=23$ 位，得到一个32位的表示
在双精度浮点格式（C语言中的double）中，s、exp和frac字段分别为 1 位、$k=11$ 位和 $n=52$ 位，得到一个64位的表示

![](images/floating%20Point.png)

#### 数字实例

#### rounding(舍入)

#### 浮点运算

## Machine-Level Representation of Programs

1978 年，Intel 发布了第一款 x86 指令集的微处理器 8086，以此拉开了 Intal x86 系列发展的序幕。但 AMD 开发了 x86-64 架构（AMD64）

从 C 到机器代码

机器代码是处理器能够直接执行的字节层面

### 程序编码

### 数据格式

### Accessing Information(访问信息)

一个 x86_64 的CPU包含一组16个存储64bit值的*通用目的寄存器*，这些寄存器用来存储整数数据和指针

### 算术和逻辑操作

### 控制

#### 条件码

#### 访问条件码

#### 跳转指令

#### 跳转指令的编码

#### 用条件控制来实现条件分支

#### 循环

#### switch 语句

### 过程

#### 运行时栈

#### 控制转移

#### 数据传送

#### 栈上的局部存储

#### 递归过程

### 数组分配和访问

## Optimizing Program Performance(优化程序性能)

### Capabilities and Limitations of Optimizing Compilers

编译器并不能真正理解你使用的数字，当定义一个 int，但实际它的取值范围是比 int 小很多的子集
编译器也很难理解内存引用模式和过程调用的影响
一般来说，编译器有一整套优化策略，但总的来说，编译器对不确定能否进行优化的地方不会进行优化

### Eliminating Loop Inefficiencies(消除循环的低效率)

### Reducing Procedure Calls(减少过程调用)

### Eliminating Unneeded Memory References(消除不必要的内存引用)

## The Memory Hierarchy

内存实际上叫做 Random-Access Memory (RAM)，它一般被封装成芯片，多个芯片组合构成主存（main memory）
最基本的存储单位称为单元（call），一个单元存储一个 bit

RAM 根据存储单元的实现方式可以分为两种

|   | Tans. per bit | Access time | Needs refresh? | Needs EDC? | Application |
|---|---|
|   |   |


- SRAM（Static RAM）：需要4或6个晶体管存储 1 bit，访问速度几个时钟周期
- DRAM（Dynamic RAM）：只需要一个晶体管存储 1 bit，

I/O Bus

磁盘、USB等设备通过 I/O 桥链接到 CPU 和内存，I/O 桥和各个外部设备通过 I/O 总线链接，每根线路一个时钟周期传输1 bit 的信息
以前的PCI总线对于各个设备是共享的，如果总线上任何设备修改了某个值，该总线上的每个设备都可以看到，称为广播总线
现代系统使用 PCI Express 的总线结构，它是点对点的，可以达到更快的速度

直接内存访问（direct memory access，DMA）：磁盘控制器通过 I/O 桥直接将数据复制到内存中，而无需经过 CPU，当数据传输完成，使用中断（interrupt）机制通知 CPU，它实际上是 CPU 芯片上的一个引脚
对于 CPU 来说，某处有某个程序正在等待数据读入内存，受到中断通知后就可继续执行该程序，并处理该内存数据

在 CPU 看来固态硬盘与机械硬盘完全相同，具有一样的接口和包装

由于 CPU 频率的不断提升，CPU和内存之间速度的差距成为限制 CPU 程序速度的主要因素

### Locakity

The key to bridging this CPU-Memory gap is a fundamental property of computer programs known as locality
弥合 CPU 和内存之间差距的关键是根本的程序的基本属性——程序的局部性

Principle of Locality: Programs tend to use data and instructions with addresses near or equal to those they have used recently
程序的局部性：程序倾向于使用其地址接近或等于最近使用过的数据和指令的那些数据和地址

temporal locality：recently referenced items are likely to be referenced again in the near future
时间局部性：最近引用的内存位置可能在不久的将来再次被引用
Spatial locality：Items with nearby addresses tend to be referenced close together in time
空间局部性：被访问过的地址的附近地址更可能被访问

Qualitative Estimates of Locality

利用局部性：
按行访问二维数组，而不是按列

### Cache Memories

Cache: A smaller, faster storage device that acts as a staging area for a subset of the data in a larger, slower device
Cache：
Big Idea: The memory hierarchy creates a large pool of storage that costs as much as the cheap storage near the bottom, but that serves data to programs at the rate of the fast storage near the top
内存层次结构创建了一个大型存储池

当 CPU 需要访问内存中的一块数据时，会先查看 Cache 中是否有该数据，如果有（cache hit），则直接使用，如果没有（cache miss），则将内存中的数据复制到 Cache 中，这将花费更多时间

Types of Cache Misses:
Cold (compulsory) miss
- the cache is empty (最初缓存是空的，将数据加载到空的缓存中称为缓存的暖身)
Conflict miss
- 组相连，需要使用的数据块在位置上冲突
Capacity miss
- 缓存的大小有限，Occurs when the set of active cache blocks (working set) is larger than the cache

## Linking

链接（linking）是将各种代码和数据片段收集并合成为一个单一文件的过程，这个文件可被加载（复制）到内存并执行
链接可以执行于编译时（compile time）；也可以执行于加载时（load time）；甚至执行于运行时（run time）


### Compiler Drivers(编译器驱动程序)

以下例程将作为贯穿本章的运行示例，帮助说明关于链接是如何工作的

```C
// main.c
int sum(int *a, int n);

int array[2] = {1, 2};

int main()
{
  int val = sum(array, 2);
  return val;
}
```

```C
// sum.c
int sum(int *a, int n)
{
  int i, s = 0;

  for (i = 0; i < n; i++) {
    s += a[i];
  }
  return s;
}
```

大多数编译系统提供**编译驱动程序**（compiler driver），它代表用户在需要时调用语言预处理器、编译器、汇编器和链接器

linux> gcc -Og -o prog main.c sum.c

![Static Linking](images/Static%20Linking.png)

Why Linkers？
Reason 1: Modularity

- Program can be written as a collection of smaller source files, rather than one monolithic mass.
- Can build libraries of common functions (more on this later)

Reason 2:

- Time: Separate compilation
  - Change one source file, compile, and then relink.
  - No need to recompile other source files
- Space: Libraries
  - Common functions can be aggregated into a single file..
  - Yet executable files and running memory images contain only code for the functions they actually use

### Static Linking(静态链接)

为了构造可执行文件，链接器必须完成两个主要任务：

- 符号解析（symbol resolution）
  - 目标文件定义和引用**符号**，每个符号对应于一个函数、全局变量或*静态变量*（C 语言中以 static 属性声明的变量）
  - 符号解析的目的是将每个符号**引用**正好和一个符号**定义**关联起来
- 重定位（relocation）
  - 编译器和汇编器生成从地址 0 开始的代码和数据节。链接器通过把每个符号定义与一个内存位置关联起来，从而**重定位**这些节，然后修改所有对这些符号的引用，使得它们指向这个内存位置
  - 链接器使用汇编器产生的**重定位条目**（relocation entry）的详细指令，不加甄别地执行这样的重定位

What Do Linker Do?
Step 1: Symbol resolution (符号解析)

- Programs define and reference *symbols* (global varibales and functions):
  - void swap() {}      // define symbol swap
  - swap();             // reference symbol swap
  - int *xp = &x;       // define symbol xp, reference x
- Symbol definitions are stored in object file (by assembler) in *symbol table*
  - Symbol table is an array of **structs**
  - Each entry includes name, size, and location of symbol
- During symbol resolution step, the linker associates each symbol reference with exactly one symbol defintion.

Step 2: Relocation

- Merges separate code and data sections into single sections
- Relocations symbols from their relative locations in the .o files to their final absolute memory locations in the executable
- Updates all references to these symbols to reflect their new postitons

### Object Files(目标文件)

Three Kinds of Object Files (Modules)
目标文件有三种形式

Relocationable object file (.o file)
可重定位文件

- Contains code and data in a form that can be combined with other relocation object files to from executable object file
- Each .o file is produced from exactly one source (.c) file by assembler
- 它是二进制文件，但是不能直接加载到内存中，在实际使用前还需要链接

Executable object file (a.out file)

- Contains code and data in a form that can be copied directly into momory and then executed
- generated by linker
- 是历史上第一个 Linux 操作系统就是可执行的，Unix 开发人员使用的默认名称 a.out

Shared object file (.so file)

- Special type of relocatable object file that can be loaded into memory and linked dynamically, at either load time or run-time
- 用于创建共享库，Called *Dynamic link libraries* (DLLs) by Windows

目标文件是按照特定的格式来组织的，各个系统的目标文件格式都不相同
从贝尔实验室诞生的第一个 Unix 系统使用的是 a.out 格式（直到今天）
Windows使用可移植可执行（Portable Executable，PE）格式；Mac OS 使用 Mach-O 格式；现代 x86_64 Linux 和 Unix 系统使用**可执行可链接格式**（Executable and Linkable Format，ELF）。它们的基本概念都是相似的

### Executable and Linkable Format (ELF)

Standard binary format for object files
目前模块采用 ELF 格式的标准格式，是以上三种文件的通用格式

One unified format for

- Relocatable object files (.o)
- Executable object file (a.out)
- Share object files (.so)

Generic name: ELF binaries

ELF Object File Format

1. ELF header
   - Word size, byte ordering, file type(.o, exec, .so), machine type, etc
   - 提供关于这个二进制文件的一般信息
2. Segment header table
   - Page size, virtual addresses memory segments (sections), segment sizes
   - 段头部表，只在可执行目标文件中存在，用于指明程序中所有段在内存中的位置
3. .text section
   - Code
4. .rodata section
   - Read only data: jump tables, ...
5. .data section
   - Initialized global varizbles
   - 包含所有初始化全局变量的空间
6. .bss section
   - Uninitialized global varizbles
   - "Block Started by Symbol"
   - "Better Save Space"
   - Has section header but occupies no space
   - 定义了未初始化的全局变量，实际上并没有占用任何的实际空间，仅仅是占位符
7. .symtab section
   - Symbol table
   - Procedure and static variable names
   - Section names and locations
   - 符号表，包含程序全局变量的结构数组以及使用 static 属性定义的任何内容
8. .rel .text section
   - Relocation info for .text section
   - Addresses of instructions that will need to be modified in the executable
   - Instructions for modifying
   - 一个记录，包含重定位信息，当链接器识别所有对符号的引用时，它会记下一些记录，在生成可执行文件时，根据记录处理符号引用
   - 汇编器让链接器去修改这些引用
9. .rel .data section
   - Relocation info for .data section
   - Addresses of instructions that will need to be modified in the executable
10. .debug section
    - Info for symbolic debugging (gcc -g)
    - 包含了将源代码中的行号与机器码中的行号相关联的信息
11. Section header table
    - Offsets and sizes of each section

### Symbols and Symbol Tables(符号和符号表)

每个可重定位目标模块 *m* 都有一个符号表，它包含 *m* 定义和引用的符号信息
在链接器的上下文中，有三种不同的符号：

- Global symbols(全局符号)
  - Symbols defined by module *m* that can be referenced by other modules
  - 由模块 *m* 定义并能被其他模块引用，对应于非静态的 C 函数和全局变量
  - E.g.: non-**static** C functions and non-**static** global variables
- External symbols(外部符号)
  - Global symbol that are referenced by module *m* but defined by some other module
- Local symbols(局部符号)
  - Symbols that are defined and referenced exclusively by module *m*
  - E.g.: C functions and global variables defined with the **static** attribute
  - Local linker symbols are *not* local program variables

Local non-static C variables: stored on the stack
local static C variables: stored in either .bss, or .data

### Symbol Resolution(符号解析)

当编译器遇到一个不是在当前模块中定义的符号（变量或函数名）时，会假设该符号是在其他某个模块中定义的，生成一个链接器符号表条目，并把它交给链接器处理
如果链接器在它的任何输入模块中都找不到这个被引用符号的定义，就会报错
多个目标文件可能会定义相同名字的全局符号。在这种情况下，链接器必须要么标志一个错误，要么以某种方法选出一个定义并抛弃其他定义

#### 链接器如何解析多重定义的全局符号

Linux 编译系统在编译时，编译器向汇编器输出每个全局符号，或者是**强**或者是**弱**，而汇编器把这个信息隐含地编码在可重定位目标文件的符号表里。函数和已初始化的全局变量是强符号，未初始化的全局变量是弱符号

根据强弱符号的定义，Linux 链接器使用以下规则来处理多重定义的符号名：
Linker's Symbol Rules

- Rule 1: Multiple strong symbols are not allowed
  - Each item can be defined only once
  - OtherwiseL Linker error
- Rule 2: Given a strong symbol and multiple weak symbols, choose the strong symbol
  - References to the weak symbol resolve to the strong symbol
- Rule 3: If there are multiple weak symbols, pick an arbitrary one
  - Can override this with **gcc -fno-common**

Global Variables

Avoid if you can
Otherwise
    use **static** if you can
    Initialize if you define a global variable
    Use extern if you reference an external global variable

编译器会在需要链接的地方设置 Relocation Entries 以便链接器在重定位并合并到可执行文件中时识别和修改地址

### Relocation(重定位)

一旦链接器完成了符号解析，就把代码中的每个符号引用和正好一个符号定义（即它的一个输入目标模块中的一个符号表条目）关联起来。此时，链接器就知道它的输入目标模块中的代码节和数据节的确切大小。现在接可以开始重定位了，在这个步骤中，将合并输入模块，并为每个符号分配运行时地址。重定位由两步组成：

### Loading Executable Object Files

一旦链接器创建了一个目标文件，该对象文件可以加载代码和数据，并且该对象文件可以直接加载到内存中


### Packaging Commonly Used Functions

链接的一个真正优势是允许我们创建库
程序员总是想抽象定义 api，打包这些 api 将其提供给其他程序员

Static libraries（.a archive files）
    - Concatenate related relocatable object files into a single file with an index (called an *archive*)
.o 文件的集合，其中每个 .o 文件都包含一个函数

Linker's algorithm for resolving external references:
    - Scan .o file and .a files in the command line order
    - During the scan, keep a list of the current unresolved references
    - As each new .o or .a file, obj, is encountered, try to resolve each ubresolved reference in the list against the symbols defined in obj
    - If any entries in the unresolved list at end of scan, then error

链接器将尝试在命令行上从左到右解析这些引用，文件在命令行上的顺序有要求

### Modern Solution: Shared Libraies

Static libraries have the following disadvantages:
    - Duplication in the stored executables(every function needs libc)
    - Duplication in the running executables
    - Minor bug fixed of system libraries require each application to explicitly relink

Shared Libraries
    - Object files that contain code and data that are loaded and linked into an application *dynamically*, at either *load-time* or *run-time*
    - Also called: dynamic link libraries, DLLs, .so files

### Library Interpositioning(库打桩机制)

Linux 链接器支持一个很强大的技术，称为**库打桩**（library interpositioning），它可以截获对共享库函数的调用，取而代之执行自己的代码
通过打桩机制可以追踪对某个特殊库函数的调用次数，验证和追踪它的输入和输出值，或者甚至把它替换成一个完全不同的实现

它的基本思想是：给需要打桩的*目标函数*创建一个*包装函数*，当程序调用目标函数时，实际执行它的包装函数，包装函数通常会先执行它自己的逻辑（例如记录调用信息），然后调用目标函数，再将目标函数的返回值传递给调用者

Library interpositioning: powerful linking technique that allows programmers to intercept calls to arbitrary functions
Interposi7oning can occur at:
    - Compile time: When the source code is compiled
    - Link time: When the relocatable object files are statically linked to form an executable object file
    - Load/run time: When an executable object file is loaded into memory, dynamically linked, and then executed.

Some Interpositioning Applications

- Security
  - Confinement(sandboxing)
  - Behind the scenes encryption
- Debugging
- Monitoring and Profiling
  - Count number of calls to functions
  - Characterize call sites and arguments to functions
  - Malloc tracing
    - Detecting memory leaks
    - **Generating address traces**

Example program

Goal: trace the addresses and sizes of the allocated and freed blocks, without breaking the program, and without modifying the source code.
Three solutions: interpose on the lib malloc and free functions at compile time, link time, and load/run time.

```C
// int.c
#include <stdio.h>
#include <malloc.h>

int main()
{
    int *p = malloc(32);
    free(p);
    return 0;
}
```

Compile-time Interpositioning

```C
//mymalloc.c

#ifdef COMPILETIME
#include <stdio.h>
#include <malloc.h>
/* malloc wrapper function */
void *mymalloc(size_t size)
{
    void *ptr = malloc(size);
    printf("malloc(%d)=%p\n",
    (int)size, ptr);
    return ptr;
}
/* free wrapper function */
void myfree(void *ptr)
{
    free(ptr);
    printf("free(%p)\n", ptr);
}
#endif
```

```C
// malloc.h

#define malloc(size) mymalloc(size)
#define free(ptr) myfree(ptr)
void *mymalloc(size_t size);
void myfree(void *ptr);
```

```C
// mymalloc.c

#ifdef LINKTIME
#include <stdio.h>
void *__real_malloc(size_t size);
void __real_free(void *ptr);
/* malloc wrapper function */
void *__wrap_malloc(size_t size)
{
    void *ptr = __real_malloc(size); /* Call libc malloc */
    printf("malloc(%d) = %p\n", (int)size, ptr);
    return ptr;
}
/* free wrapper function */
void __wrap_free(void *ptr)
{
    __real_free(ptr); /* Call libc free */
    printf("free(%p)\n", ptr);
}
#endif
```

## Exceptional Control Flow

指令序列称为控制流（control flow）
改变控制流的机制：
- 分支和跳转（Jumps and branches）
- 过程调用和返回（Call and return）
这些都是对程序状态（program state）变化的处理
但是真正的操作系统需要能够处理系统级的变化（system state）:
- Data arrives from a disk or a network adapter
- Instruction divides by zero
- User hits Ctrl-C at the keyboard
- System timer expires

系统需要“异常控制流”的机制，因为它超出链程序中的正常控制进程

系统中所有级别都存在ECF
底层机制
1. Exceptions（异常）
   - 响应某些底层系统事件的控制流的变化
   - 由硬件和操作系统软件组合实现
高层机制
2. Process context switch（上下文切换）
   - 由操作系统和硬件计时器实现
3. Signals
   - 由操作系统实现
4. Nonlocal jumps: setjmp() and longjmp()
   - 由 C 运行库实现
   - 允许你非本地跳转，允许违背正常的调用和返回模式

### Exceptions

An *exception* is a transfer of control to the OS *kernel* in response to some *event*
异常是将控制权转移到操作系统内核
- kernel is the memory-resident part of the OS, 内核是操作系统中始终驻留在内存中的一部分

异常是异常控制流的一种形式，它一部分由硬件实现，一部分由操作系统实现，实际转移控制权，程序技术器或 %rip 的更改由硬件完成。但是由于该异常而执行的代码是由操作系统内核设定的
每种类型的事件都有一个唯一的**异常编号**，用作跳转表的索引（**异常表**）。当事件k发生时，硬件使用k作为此表的索引，得到该异常的处理程序的地址

异常分为同步和异步异常
Asynchronous Exceptions(interrupts)，异步异常又称为**中断**，是由于处理器外部发生的状态变化而引起的，通过处理器的引脚来通知处理器其状态变化
直接内存访问（DMA）就是这样通知处理器它已经完成复制了的
在发生中断后，处理程序返回到下一条指令，它通常在后台完成，不会影响程序的进行
最常见的中断是定时器（看门狗）中断。所有系统都有一个内置计时器，每隔几毫秒就会关闭一次。当它关闭时，会将中断引脚设置为高电平，并且有一个特殊的异常编号用于定时器中断
它的作用是让内核再次获得对系统的控制，以防止用户程序陷入死循环中导致死机
来自外部设备的 I/O 中断也是常见的

#### 异常的类别

异常可以分为四类：

| 类别 | 原因 |  | 返回行为 |
|---|---|--|--|
| 中断 | 来自I/O设备的信号 | 异步 | 总是返回到下一条指令 |
| 陷阱 | 有意的异常 | 同步 | 总是返回到下一条指令 |
| 故障 | 潜在可恢复的错误 | 同步 | 可能返回到当前指令 |
| 终止 | 不可恢复的错误 | 同步 | 不会返回 |

Synchronous Exceptions，同步异常有三类：

- Traps（陷阱）
  - 陷阱是由程序故意引起的异常
  - 最常见的形式是*系统调用*，
  - 用户程序无法直接访问内核中的数据，内核提供一个响应用户程序发出请求的接口，调用内核中的函数并发出各种服务请求，此接口称为系统调用
  - 内核响应程序的请求后将控制权返回给程序
- Faults（故障）
  - 故障是无意的，但是可能是可以恢复的
  - 像“页缺失（page faults）”是可恢复的；保护故障（protection faults）是不可恢复的（尝试访问未分配的内存部分）；浮点数异常是可恢复的
  - 在任何一种情况下，当出现故障时，要么重新执行当前指令，要么中止（aborts）
- Aborts（中止）
  - 无意且不可恢复的异常
  - 执行非法指令；内存存在问题

### System Calls（系统调用）

不同类型的系统调用有其唯一的编号
Linux：
| Number | Name | Description |
|---|---| --- |
| 0 | read | Read file |
| 1 | write | Write file |
| 2 | open | Open file |
| 3 | close | Close file |
| 4 | stat | Get info about file |
| 57 | fork | Create process |
| 59 | execve | Execute a program |
| 57 | _exit | Terminate process |
| 57 | kill | Send signal to process |

有一个 syscall 指令实际执行系统调用
通常不需要在自己的程序中直接使用系统调用，并触发 syscall 指令，Linux 将这些函数包装在系统级函数中

### Processes（进程）

definition: A *process* is an instance of a running program
定义：进程是正在运行的程序的实例
它与“程序”或“过程”不同，程序可以存在于多种不同的地方，它可以是.c 文件中以文本形式保存的程序；可以作为二进制文件的 .text 部分存在；可以作为已加载到内存中的字节存在

Process provides each program with two key abstractions
进行提供了两个关键的抽象：

- Logical control flow(逻辑控制流)
  - Each program seems to have exclusive use of the CPU
  - 它提供一个假象，程序独占使用CPU和寄存器
  - provided by kernel mechanism called *context switching*
- Private address space(私有的地址空间)
  - Each program seems to have exclusive use of main memory
  - 它提供一个假象，程序拥有独立的内存地址空间
  - Provided by kernel mechanism called *virtue memory*

进程给程序一种错觉：每个运行的程序都有自己的代码、数据、堆栈，拥有所有内存和CPU的独占访问权限
但实际上多个进程共享使用系统的一个核心

系统中实际上同时运行链多个进程，多个进程在同一时间并发运行，操作系统就是管理共享
Linux 上使用 top 命令可以查看所有进程
由于定时器中断或某种故障或陷阱而引发的异常，让操作系统可以控制系统，并决定是否要运行另一个进程
它将当前寄存器值保存到内存中，然后安排下一个待执行的进程，并且加载上次运行该进程时保存的寄存器，然后将地址空间切换到此进程的地址空间
这个寄存器值和地址空间是“上下文（context）”，上下文切换是寄存器和地址空间的变化

在具有多个核心的现代系统上，操作系统在多个核心上安排进程

#### Concurrent Processes

Each process is a logical control flow
可以认为每个进程代表一个“逻辑控制流”
两个进程同时运行concurrently（并发），否则它们是连续的（sequential）
即使有多个核心，只要逻辑流在时间上重叠，它们就是并发的

#### Context Switching（上下文切换）

processes are managed by a shared chunk of memory-resident OS code called the *kernel*
上下文切换由内核管理
Important: the kernel is not a separate process, but rather runs as part of some existing process
内核不想是一个正在运行的独立进程，它始终在某些现有进程的上下文中运行
它只是位于地址空间顶部的代码

Control flow passes from one process to another via a context switch

System Call Error Handling

Linux 提供了许多函数，可以用用户程序调用来操作进程，这个操作进程的过程称为“进程控制”
On error, Linux system-level functions typically return -1 and set global variable errno to indicate cause
如果出现错误，Linux系统级函数通常会返回 -1，然后设置一个名为 errno 的全局变量来指示原因
当调用系统级函数时有一条硬性规则：必须检查所使用函数的返回值，唯一的例外是有些函数返回 void
Hard and fast rule:

- You must check the return status of every system-level function
- Only exception is the handful of functions that return void

```C
if ((pid = fork()) < 0) {
    fprintf(stderr, "fork error: %s\n", strerror(errno));
}
```

Can simplify somewhat using a *error-reporting function*:

```C
void unix_error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

if ((pid = fork()) < 0)
    unix_error("fork error");
```

We simplify the code we present to you even further by using Stevens-style error-handling Wrappers:

```C
pid_t Fork(void)
{
    pid_t pid;
    if ((pid = fork()) < 0)
        unix_error("fork error");
    return pid;
}

pid = Fork();
```

在函数中处理错误形成一个包装器，它具有与原始函数相同的接口，只不过它的第一个字母大写
这个包装器调用原始函数并检查错误，如果没有错误，将原始函数结果返回；如果有错误，就以某种方式处理它并打印消息
这使我们能够在不违反规范的情况下使代码真正的紧凑

### Process Control(进程控制)

#### Creating and Terminating Processes(创建和终止进程)

Linux 提供了创建和终止进程的方法
从程序员的角度来看，可以将进程视为处于以下三种运行状态之一：
Running
进程正在运行并执行指令，或者它可以被调度，也许并没有运行，但可以在稍后时间调度
Stopped
执行被暂停，在进一步通知之前不会被调度（通常是因为收到了某种“信号”）
Terminated
永久停止

终止一个进程有三个原因：
- 接收一个信号，其默认操作是终止它
- 从 main routine 返回
- 显式调用 exit 函数

void exit(int status)
- terminates with an *exit status* of status
- 退出程序，其退出状态为其参数
- convention: normal return status is 0, nonzero on error
- 惯例的正常返回是返回0，非0就是错误
- Another way to explicity set the exit status is to return an integer value from the main routine
- 另一种方法是从主函数中返回一个整数，将设置退出状态

exit is called **once** but **never** returns

父进程可以通过调用 fork 函数来创建子进程

int fork(void)
- Return 0 to the child process, child's PID to parent process
- Child is *almost* identical to parent
- 子进程与父进程几乎相同，拥有相同的虚拟空间（但不是同一个）、堆栈、寄存器、文件描述符
  - Child get an identical(but separate) copy of the parent's virtual address space
  - Child get identical copies of the parent's open file descriptors
  - Child has a different PID than the parent

fork is interesting(and often confusing) because it is called once but returns twice

Example

```C
int main()
{
    pid_t pid;
    int x = 1;
    pid = Fork();
    if(pid == 0) {  /* Child */
        printf("child: x=%d\n", ++x);
        exit(0);
    }

    /* Parent */
    printf("parent: x=%d\n", --x);
    exit(0)
}

parent: x=0
child: x=2
```

区分父进程还是子进程的唯一方法是检查返回值
无法保证子进程先执行还是父进程先执行

Modeling fork with Process Graphs

A *process graph* is a useful tool for capturing the partial ordering of statement in a concurrent program

Any *topological sort* of the graph corresponds to a feasible total ordering

#### Reaping Child Processes(回收子进程)

When process terminates, it still consumes system resources: Exit status, various OS tables
当一个进程因任何原因终止时，系统实际上一直保持它直到它被父进程回收（reaped）
这样做的原因是，父进程可能想知道子进程的退出状态，它可能希望等待子进程完成并检查其退出状态
当子进程已近停止但并没有消失时，被称为僵尸进程（zombie）

Reaping
父进程使用 wait 或 waitpid 函数 回收子进程，这两个函数会返回子进程退出状态信息，然后内核会删除僵尸进程

如果父进程没有回收它的僵尸子进程
在父进程终止时，系统会安排一个 init 进程（pid=1）来回收子进程，init 进程总是会回收这样的孤儿进程
在长时间运行的进程（例如 shell 和 服务器）中，必须显式地回收子进程，不然僵尸进程可能会填满内存空间并导致内核崩溃

wait: Synchronizing with Children

Parent reaps a child by calling the wait function

int wait(int *child_status)
- Suspends current process until one of its children terminates
- Return value is the **pid** of the child process that terminated
- If **child_status != NULL**, then the integer it points to will be set to a value that indicates reason the child terminated and the exit status:
  - Checked using macros defined in wait.h

wait 需要一个可选状态，在哪里可以获得检查子进程的退出状态
wait 会暂停执行调用它的进程直到一个或其中一个子进程终止，它并没有指定它在等待哪一个子进程终止，任何一个都可以
如果子进程状态不为空（child_status != NULL），它(child_status)指向的整数将被设置为某个值，该值指示了进程终止的原因及其退出状态

```C
void fork9() {
    int child_status;

    if (fork() == 0) {
        printf("Hello from child\n");
        exit(0);
    } else {
        printf("Hello from parent\n");
        wait(&child_status);
        printf("child has terminated\n");
    }
    printf("Bye\n");
}
```

pid_t waitpid(pid_t pid, int &status, int options)
- Suspends current process until specific process terminates
- waitpid 类似于 wait，但它可以等待特定子进程，以终止具有特定进程ID的特定子进程

execve: Loading and Running Programs

fork 只是创建的子进程只是父进程的一个精确副本，运行相同的代码，拥有相同的变量
要在进程内运行不同的程序，要使用 execve 函数

```C
int execve(char *filename, char *argv[], char *envp[])
```

该函数在当前流程中加载并运行传入的第一个参数可执行文件
Loads and runs in the current process:
- Executable file **filename**
  - Can be object file or script file beginning with #!interpreter(e.g., #!/bin/bash)
- with argument list **argv**
  - By convention argv[0]==filename
- and environment variable list **envp**
  - "name=value" strings

execve 所有代码、数据和堆栈会完全覆盖虚拟地址空间，一旦在一个进程中调用 execve 它会打破当前的程序，但它仍然是原来的进程，会保留PID
overwrites code, data, and stack
- Retains PID, open files and signal context

Called once and never returns
- except if there is an error

### Signals

Linux 信号是一种更高层的软件形式的异常，它允许进程和内核中断其他进程
kernel software and application software

Linux Process Hierarchy
在 Linux 下只有一种方法创建进程：使用 fork 调用
事实上，系统上的所有程序形成了一个层次结构。当启动系统时，第一个创建的进程是 init 进程，它的进程 id 是 1，系统上其他所有的进程都是 init 进程的子进程
init 进程启动时会创建守护进程（daemon），守护进程一般是一个长期运行的程序，通常用来提供服务，例如 web 服务器
最后会创建登录进程，也就是登录 shell（Login shell），它为用户提供了命令行接口，登录shell会以你的身份创建子进程来执行程序

Shell Program

A *shell* is an application program that runs programs on behalf of the user
Shell 程序和其他程序没什么区别，它们以用户的身份执行程序。Linux 的默认shell是bash
execution is a sequence of read/evaluate steps
执行程序就是在shell中的一系列读/求值的步骤
首先，shell打印一个提示符，然后等待你在命令行中输入命令，然后敲击回车
通常来说，输入的第一个东西是命令，然后再跟上用空格分隔开的可选参数
在输入完并按下回车后，shell会检查文件末尾的字符，对终端（terminal）来说如果是ctrl-d，则退出，否则计算此命令行
求值由以下几个步骤
首先解析命令行
命令行会被解析成一个 argv 数组
在shell中有个约定：如果命令行以 & 符号结尾，那么可以使 shell 在后台运行此命令，shell不会等待这个命令完成，而是继续读取新命令
否则shell将在前台运行此命令，shell会等待命令的完成
shell 实现链一些内建命令：jons、bg、fg 等
shell会先检查 argv[0] 是否是一个内建shell命令，如果是，它会直接执行，如果不是，意味着要求shell运行一些其他程序，这种情况下 shell 会 fork 一个子进程，这个子进程会使用 execve 调用来运行这个程序
如果不是后台进程，父进程通过调用 waitpid 等待结束进程，一旦程序执行完成，父进程将回收它
如果是后台进程，shell不会调用 waitpid，而是直接等待下条命令。如果有过多的后台进程，就可能引起内存泄露，导致系统崩溃
异常控制流可以用于解决此问题
Solution: Exceptional control flow

- The kernel will interrupt regular processing to alert us when a background process completes
- In Unix, the alert mechanism is called a **signal**

内核会在shell的子进程结束时告知shell，然后shell会对此作出反应，并调用 waitpid。这个通知机制就是信号（signal）

A *signal* is a small message that motifies a process that an event of some type has occurred in the system
信号就是一条小的消息，用于通知进程系统中发生链一次某种类型的事件（它与异常机制很像，但是它完全由软件实现）
- Akin to exceptions and interrupts
- Send from the kernel（sometimes at the request of another process）to a process
- Signal type is identified by small integer ID's(1-30)
- Only information in a signal is its ID and the fact that it arrived

| ID  | Name  | Default Action | Corresponding Event |
|---|---|---|---|
| 2 | SIGINT | Terminate | User typed ctrl-c |
| 9 | SIGKILL | Terminate | Kill program (connot override or ignore) |
| 11 | SIGSEGV | Terminate | Segmentation violation |
| 14 | SIGALRM | Terminate | Timer signal |
| 17 | SIGCHLD | Terminate | Child stopped or terminated |

每当子进程被终止或结束时 kernel 会通过 SIGCHLD 信号通知父进程，这就是shell回收进程的做法

#### Signal Concepts

传送一个信号到目的进程是由两个不同步骤组成的：

- 发送信号（Sending a Signal）：
Kernel *sends* (delivers) a signal to a *destination process* by updating some state in the context of the destination process
内核通过更新目标进程上下文中的某个状态来发送或传递信号

Kernel sends a signal for one of the following reason
发送信号可以有如下两种原因：

1. Kernel has detected a system event such as divide-by-zero (SIGFPE) or the termination of a child process (SIGCHLD)
内核检测到一个系统事件，比如除零错误或者子进程终止
2. Another process has invoked the **kill** system call to explicitly request the kernel to send a signal to the destination process
一个进程调用链 kill 函数，显式地要求内核发送一个信号给目的进程

- 接收信号（Receiving a Signal）
A destination process *receives* a signal when it is forced by the kernel to react in some way yo the dlivery of the signal
当目的进程被内核强迫以某种方式对信号的发送做出反应时，它就接收了信号


目标进程收到一个信号，内核会强制它在收到信号作出应答，应答有几个可行的方式
Some possible ways to react
- Ignore the signal 忽略此信号
- Terminate the process (with optional core dump) 终止进程
- Catch the signal by executing a user-level function called *signal handler* 使用一个用户级函数“信号处理程序”捕获信号
- 这很像响应某些系统级事件的异常处理程序，它们的区别在与异常处理是内核级别的，信号处理实际上是在你的 C 代码里

A signal is *pending* if sent but not yet received
一个发出而没有被接收的信号叫做*待处理信号*（pending signal）
There are be at most one pending signal of any particular type
在任何时可，一种类型至多只会有一个待处理信号
Important: Signals are not queued
- If a process has a pending signal of type k, then subsequent signals of type k that are sent to that process are discarded
如果一个进程有一个类型为 k 的待处理信号，那么任何接下来发送到这个进程的类型为 k 的信号都*不会*排队等待；它们只是被简单地丢弃

A process can *block* the receipt of certain signals
- Blocked signals can be delivered, but will not be received until the signal is unblocked
一个进程可以有选择性地*阻塞*接收某种信号。当一种信号被阻塞时，它仍可以被发送，但是产生的待处理信号不会被接收，直到进程取消对这种信号的阻塞

A pending signal is received at most once
一个待处理信号最多只能被接收一次

Kernel maintains pending and blocked bit vectors in the context of each process
内核为每个进程在 pending 位向量中维护着待处理信号的集合，而在 blocked 位向量中维护着被阻塞的信号集合

- **pending**: represents the set of pending signals
  - kernel sets bit k in **pending** when a signal of type k is delivered
  - kernel clears bit k in **pending** when a signal of type k is received
只要传送了一个类型为 k 的信号，内核就会设置 pending 中的第 k 位，而只要接收了一个类型为 k 的信号，内核就会清除 pending 中的第 k 位

- **blocked**: represents the set of blocked signals
  - Can be set and cleared by using the **sigprocmask** function
  - Also referred to ad the *signal mask*

通过系统调用 sigprocmask 设置和清零它
阻塞位向量也被称为信号掩码
阻塞位向量和待处理位向量基本相同，都是一个32位的int类型

#### Sending Signals

Unix 系统提供了大量向进程发送信号的机制。所有这些机制都是基于**进程组**（process groups）这个概念的
Every process belongs to exactly one process group
每个进程都只属于一个进程组，进程组由一个正整数进程组ID 来标识
getpgrp 函数返回当前进程的进程组ID
默认地，一个子进程和它的父进程同属于一个进程组。一个进程可以通过 setpgid 函数来改变自己或其他进程的进程组

```C
#include <unistd.h>

pid_t getpgrp(void);

int setpgid(pid_t pid, pid_t pgid);
```

setpgid 函数将进程 pid 的进程组改为 pgid。如果 pid 是 0，那么就使用当前进程的 PID。如果 pgid 是 0，那么就用 pid 指定的进程的 PID 作为进程组 ID

1. 用 /bin/kill 程序发送信号

/bin/kill 程序可以向另外的进程发送任意的信号

```bash
kill -9 24818   # Send SIGKILL to process 24818
kill -9 -24817  # Send SIGKILL to every process in process group 24817
```

2. 从键盘发送信号

Unix shell 使用**作业**（job）这个抽象概念来表示为对一条命令行求值而创建的进程
在任何时刻，至多只有一个前台作业和0个或多个后台作业

Typing ctrl-c(ctrl-z) causes the kernel to send a SIGINT(SIGTSTP) to every job in the foreground process group
通过键盘输入 Ctrl-c 会导致内核发送一个 SIGINT 信号到前台进程组中的每个进程

- SIGINT: default action is to terminate each process
- SIGTSTP: default action is to stop(suspend) each process

在命令行中使用 ctrl-c 或 ctrl-z 会使内核向前台进程组下的所有任务（job）发送 SIGINT 或 SIGTSTP 信号
SIGINT 的默认行为是终止进程，SIGTSTP 的默认行为是挂起进程，直到收到 SIGCOUT 信号（使用 shell 内建指令 fg 把被挂起的进程恢复到前台运行）

3. 用 kill 函数发送信号

进程通过调用 kill 函数发送信号给其他进程（包括自己）

```C
#include <sys/types.h>
#include <signal.h>

int kill(pid_t pid, int sig);
```

如果 pid 大于零，那么 kill 函数发送信号号码 sig 给进程 pid
如果 pid 等于零，那么 kill 发送信号 sig 给调用进程所在进程组中的每个进程（包括调用进程自己）
如果 pid 小于零，kill 发送信号 sig 给进程组 |pid|（pid的绝对值）中的每个进程

```C
#include "csapp.h"

int main()
{
    pid_t pid;

    /* Child sleeps untill SIGKILL signal received, then dies */
    if ((pid = Fork()) == 0) {
        Pause();
        printf("control should never reach here!\n");
        exit(0);
    }

    /* Parent sends a SIGKILL signal to a child */
    Kill(pid, SIGKILL);
    exit(0)
}
```

4. 用 alarm 函数发送信号

进程可以通过调用 alarm 函数向它自己发送 SIGALRM 信号

```C
#include <unistd.h>

unsiged int alarm(unsigned int secs);
// 返回：前一次闹钟剩余的秒数，若以前没有设定闹钟，则为 0
```

alarm 函数安排内核在 secs 秒后发送一个 SIGALRM 信号给调用进程

#### Receiving Signals

Suppose kernel is returning from an exception handler and is ready to pass control to process *p*
当内核把进程*p*从内核模式切换到用户模式时（例如，从系统调用返回或是完成了一次上下文切换），它会检查进程*p*的未被阻塞的待处理信号的集合 pnb
kernel computes pnb = pending & ~blocked
pnb 是所有未阻塞待处理信号的列表，这样所有的待处理信号都应该被接收了

如果 pnb==0 说明没有待处理的信号，那么内核将控制传递到*p*的逻辑控制流中的下一条指令
否则内核会选择 pnb 中的某个信号 k（通常是最小的非零位），并且强制*p*接收信号 k
信号的接收会触发进程的一些行为，一旦进程完成了这个行为
然后对 pnb 中的每个非零位对应的信号重复此过程，直到处理完所有的非零位
最后将控制权移交给进程继续执行下一条指令

每个信号类型都有一个预定的*默认行为*

- 进程终止
- 进程终止并转储内存
- 进程停止（挂起）直到被 SIGCONT 信号重启
- 进程忽略这个信号

但是可以使用一个叫做 signal 的系统调用来修改默认行为

Install Signal Handlers

```C
handler_t *signal(int signum, handler_t *handler)
```

它接收一个信号编号 signum，在指定对此信号默认行为的更改

Signals Handlers as Concurrent Flows

A signal handler is a separate logical flow (not process) that runs concurrently with the main program
信号处理是一个和主函数并发的逻辑流，在信号处理函数执行完，最终会返回到主函数
信号棘手的原因之一就是这个重叠的并发流，因为信号处理程序与main程序运行在同一个进程里，所以它们共享程序中的所有全局变量

信号处理程序可以被其他处理程序中断

#### Blocking and Unblocking Signals

Linux 提供阻塞信号的隐式和显式的机制：

- **隐式阻塞机制**：内核默认阻塞任何当前处理程序正在处理信号类型的待处理的信号
  - A SIGINT handler can't be interrupted by another SIGINT
- **显式阻塞机制**：应用程序可以使用 sigprocmask 函数和它的辅助函数，明确地阻塞和解除阻塞选定的信号





### Nonlocal jumps(非本地跳转)

C 语言提供了一种用户级异常控制流形式，称为**非本地跳转**（nonlocal jump），它将控制直接从一个函数转移到另一个当前正在执行的函数，而不需要经过正常的调用-返回序列
非本地跳转是通过 setjmp 和 longjmp 函数来提供的

```C
#include <setjmp.h>

int setjmp(jmp_buf env);
int sigsetjmp(sigjmp_buf env, int savesigs);
// setjmp 返回0，longjmp 返回非零
```

## Virtual Memory

现代系统提供了一种对内存的抽象概念，叫做虚拟内存（VM）。虚拟内存是硬件异常、硬件地址翻译、主存、磁盘文件和内核软件的完美交互，它为每个进程提供了一个大的、一致的和私有的地址空间
虚拟内存提供了三个重要能力：

1. 它将主存看成是一个存储在磁盘上的地址空间的高速缓存，在主存中只保存活动区域，并根据需要在磁盘和主存之间来回传送数据
2. 它为每个进程提供了一致的内存空间，从而简化了内存管理
3. 它保护了每个进程的地址空间不被其他进程破坏

### 物理地址和虚拟地址（Physical and Virtual Addressing）

计算机系统的主存被组织成一个由M个连续的字节大小的单元组成的数组。每个字节都有一个唯一的*物理地址*（Physical Address，PA）
第一个字节的地址为0，接下来为1，依次类推。CPU 访问内存的最自然的方式是使用物理地址，称之为*物理寻址*（physical addressing）
现代处理器使用的是一种称为*虚拟寻址*（virtual addressing）的寻址方式
CPU 通过生成一个*虚拟地址*（Virtual Address，VA）来访问主存，这个虚拟地址通过CPU 芯片上的*内存管理单元*（Memory Management Unit，MMU）转换为物理地址，该过程叫做地址翻译（address translation）
MMU 利用放在主存中的查询表来动态翻译虚拟地址，该表的内容由操作系统管理

### 地址空间（Address Spaces）

### 虚拟内存作为缓存的工具（VM as a Tool for Caching）

概念上，虚拟内存被组织为一个由存放在磁盘上的*N*个连续的字节大小的单元组成的数组。每字节都有一个唯一的虚拟地址，作为到数组的索引。
磁盘上数组的内容被缓存在主存中。和存储器层次结构中其他缓存一样，磁盘（较低层）上的数据被分割成块，这些块作为磁盘和主存（较高层）之间的传输单元。
VM 系统通过将虚拟内存分割为称为*虚拟页*（Virtual Page，VP）的大小固定的块来处理这个问题。每个虚拟页的大小为 $ P=2^p $ 字节。
类似地，物理内存被分割为物理页（Physical Page，PP），大小也为 P 字节（物理页也被称为页帧（page france））。
在任意时刻，虚拟页面的集合都分为三个不相交的子集：

- 未分配的：VM 系统还未分配（或者创建）的页。未分配的块没有任何数据和它们相关联，因此也就不占用任何磁盘空间
- 缓存的：当前已缓存在物理内存中的已分配页
- 未缓存的：未缓存在物理内存中的已分配页

#### 页表

同任何缓存一样，虚拟内存系统必须有某种方法来判定一个虚拟页是否缓存在 DRAM 中的某个地方。如果是，系统还必须确定这个虚拟页存放在哪个物理页中。如果不命中，系统必须判断这个虚拟页存放在磁盘的哪个位置，在物理内存中选择一个牺牲页，并将虚拟页从磁盘复制到 DRAM 中，替换这个牺牲页
这些功能是由软硬件联合提供的，包括操作系统软件、MMU中的地址翻译硬件和一个存放在物理内存中叫做**页表**（page table）的数据结构，页表将虚拟页映射到物理页。每次地址翻译硬件将一个虚拟地址转换为物理地址时，都会读取页表。操作系统负责维护页表的内容，以及在磁盘与 DRAM 之间来回传送页

页表就是一个*页表条目*（Page Table Entry，PTE）的数组。虚拟地址空间中的每个页在页表中一个固定偏移量处都有一个PTE。
假设每个PTE是由一个有效位（valid bit）和一个*n*位地址字段组成的。有效位表明了该虚拟页当前是否被缓存在 DRAM 中。
如果设置了有效位，那么地址字段就表示 DRAM 中相应的物理页的起始地址，这个物理页中缓存了该虚拟页。如果没有设置有效位，那么一个空地址表示这个虚拟页还未被分配。否则，这个地址就指向该虚拟页在磁盘上的起始位置。

![](images/page%20table.png)

图中展示了一个有8个虚拟页和4个物理页的系统的页表。四个虚拟页（VP1、VP2、VP4和VP7）当前被缓存在 DRAM 中。两个页（VP0和VP5）还未被分配，而剩下的页（VP3和VP6）已经被分配了，但是当前还未被缓存。
因为 DRAM 缓存是全相联的，所以任意物理页都可以包含任意虚拟页

#### 页命中

当CPU 想要读取包含在 VP2 中的虚拟内存的一个字时，VP2 被缓存在 DRAM 中，地址翻译硬件将虚拟地址作为一个索引来定位 PTE2，并从内存中读取它
因为设置了有效位，那么地址翻译硬件就知道 VP2 是缓存在内存中的了。所以它使用 PTE 中的物理内存地址（该地址指向 PP1 中缓存页的起始位置），构造出这个字的物理地址

![](images/page%20hit.png)

#### 缺页

DRAM 缓存不命中称为缺页（page fault）
CPU 引用了 VP3 中的一个字，VP3 并未缓存在 DRAM 中。地址翻译硬件从内存中读其 PTE3，从有效位推断处 VP3 未被缓存，并且触发一个缺页异常。
缺页异常调用内核中的缺页异常处理程序，该程序会选择一个牺牲页，在此例中就是存放在 PP3中的 VP4。如果 VP4 已经被修改了，那么内核就会将它复制回磁盘
无论哪种情况，内核都会修改 VP4 的页表条目，反映出 VP4 不再缓存在主存中这一事实

![](images/page%20fault.png)

接下来，内核从磁盘复制 VP3 到内存中的 PP3，更新 PTE3，随后返回。当异常处理程序时，它会重启导致缺页的指令，该指令会把导致缺页的虚拟地址重发送到地址翻译硬件。
但是现在，VP3已经缓存在主存中了，那么页命中也能由地址翻译硬件正常处理了

![](images/handling%20page%20fault.png)

在虚拟内存的习惯说法中，块被称为页。在磁盘和内存之间传递页的活动叫做交换（swapping）或者页面调度（pagging）。页从磁盘换入（或者页面调入）DRAM 和从 DRAM 换出（或者页面调出）磁盘。一直等待，直到最后时刻，也就是当有不命中发生时，才换入页面的这种策略称为按需页面调度（demand pagging）

#### 分配页面

当操作系统分配一个新的虚拟内存页时对我们示例页表的影响，例如，调用 malloc 的结果
VP5 的分配过程是在磁盘上创建空间并更新 PTE5，使它指向磁盘上这个新创建的页面

![](images/allocating%20pages.png)

#### 局部性

尽管在整个运行过程中程序引用的不同页面的总数可能超出物理内存总的大小，但是局部性原则保证了在任意时刻，程序将趋向于在一个较小的活动页面（active page）集合上工作，这个集合叫做工作集（working set）或者常驻集合（resident set）。在初始开销，也就是将工作集页面调度到内存中之后，接下来对这个工作集的引用将命中，而不会产生额外的磁盘流量

### 虚拟内存作为内存管理的工具

操作系统为每个进程提供一个独立的页表，也就是独立的虚拟地址空间

![](images/process%20page.png)

多个虚拟页面可以映射到同一个共享物理页面上

按需页面调度和独立的虚拟地址空间的结合，极大地提升了内存使用效率

- *简化链接*：独立的地址空间允许每个进程的内存映像使用相同的基本格式，而不管代码和数据实际存放在物理内存的何处。
  - Linux 系统上每个进程都使用类似的内存格式，对于64为位地址空间，代码段总是从虚拟地址 0x400000 开始。数据段跟在代码段之后，中间有一段符和要求的对齐空白。栈占据用户进程地址空间最高的部分，并向下生长
  - 这样的一致性极大地简化了链接器的设计和实现，允许链接器生成完全链接的可执行文件，这些可执行文件是独立于物理内存中代码和数据的最终位置的
- *简化加载*：虚拟内存还使得容易向内存中加载可执行文件和共享对象文件
  - 要把目标文件中 .text 和 .data 节加载到一个新创建的进程中，Linux 加载器为代码和数据段分配虚拟页，把它们标记为无效的（未被缓存的），将页表条目指向目标文件中适当的位置
  - 加载器从不从磁盘到内存实际复制任何数据。在每个页初次被引用时，要么是 CPU 取指令时引用的，要么是一条正在执行的指令引用一个内存位置时引用的，虚拟内存系统会按照需要自动地调入数据页
- *简化共享*：独立地址空间为操作系统提供了一个管理用户进程和操作系统自身之间共享的一致机制。
  - 一般而言，每个进程都有自己私有的代码、数据、堆以及栈区域，是不和其他进程共享的。在这种情况中，操作系统创建页表，将相应的虚拟页映射到不连续的物理页面

操作系统通过将不同进程中适当的虚拟页面映射到相同的物理页面，从而安排多个进程共享这部分代码的一个副本，而不是在每个进程中都包括单独的内核和 C 标准库的副本

- *简化内存分配*：
  - 当一个运行在用户进程中的程序要求额外的堆空间时（如调用malloc），操作系统分配一个适当数字（k）个连续的虚拟内存页面，并且将它们映射到物理内存中任意位置的 k 个任意的物理页面，而不是 k 个连续的物理页面。

### 虚拟内存作为内存保护的工具

提供独立的地址空间使得区分不同进程的私有内存变得容易。而且，地址翻译机制可以以一种自然的方式扩展到提供更好的访问控制。因为每次 CPU 生成一个地址时，地址翻译硬件都会读一个 PTE，所以通过在 PTE 上添加一些额外的许可位来控制对一个虚拟页面内容的访问十分简单

![](images/memory%20protection.png)

如果一条指令违反了这些许可条件，那么 CPU 就触发一个一般保护故障，将控制传递给一个内核中的异常处理程序。Linux shell 一般将这种异常报告为“段错误（segmentation fault）”

### 地址翻译

- 基本参数
  - $ N=2^n $ 虚拟地址空间中的地址数量
  - $ M=2^m $ 物理地址空间中的地址数量
  - $ P=2^p $ 页的大小（字节）
- 虚拟地址（VA）的组成部分
  - VPO 虚拟页面偏移量（字节）
  - VPN 虚拟页号
  - TLBI TLB索引
  - TLBT TLB标记
- 物理地址（PA）的组成部分
  - PPO 物理页面偏移量（字节）
  - PPN 物理页号
  - CO 缓冲块内的字节偏移量
  - CI 高速缓存索引
  - CT 高速缓存标记

形式上来说，地址翻译是一个 N 元素的虚拟地址空间（VAS）中的元素和一个 M 元素的物理地址空间（PAS）中元素之间的映射

$$ MAP:VAS -> PAS U /null $$

MMU 如何利用页表来实现这种映射。CPU 中的一个控制寄存器，页表基址寄存器（page table base register，PTBR）指向当前页表，n位的虚拟地址包含两个部分

![](images/address%20translation.png)

## System-Level I/O

输入/输出（I/O）是在主存和外部设备（例如磁盘驱动器、终端和网络）之间复制数据的过程

### Unix I/O

一个 Linux 文件就是一个*m*个字节的序列，所有的I/O设备（网络、磁盘和终端）都被模型化为文件，而所有的输入和输出都被当作对相应文件的读和写来执行。
这种将设备优雅地映射为文件地方式，允许 Linux 内核引出一个简单、低级地应用接口，称为 Unix I/O，这使得所有的输入和输出都能以一种统一且一致的方式来执行：

- 打开文件：
- Linux shell
- 改变当前的文件位值
- 读写文件
- 关闭文件

### File(文件)

普通文件（regular file）包含任意数据。应用程序常常要区分文本文件（text file）和二进制文件（binary file），文本文件只含有 ASCII 或 Unicode 字符的普通文件；二进制文件是所有其他文件
对内核而言二者没有区别
Linux 文本文件由一系列文本行（text line）组成，其中每一行以一个新行符（“\n”）结束。新行符与 ASCII 的换行符（LF）一样，其数字值为 0x0a
Windows 和网络协议中，文本行的结尾需要两个字符表示（“\r\n”）

目录（directory）是包含一组链接（link）的文件，其中每个链接都将一个文件名（filename）映射到一个文件，这个文件也可以是一个目录
每个目录至少含有两个条目：“.”是到该目录自身的链接，以及“..”是到目录层次结构中父目录（parent directory）的链接

Linux 内核将所有文件都组织成一个目录层次结构（directory hierarchy），由 /（斜杠）的根目录确定。系统中的每个文件都是根目录的直接或间接的后代

套接字（socket）是用来与另一个进程进行跨网络通信的文件

### 打开和关闭文件

进程通过调用 open 函数来打开一个已存在的文件或者创建一个新文件

```C
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(char *filename, int flags, mode_t mode);
// 成功则返回新文件描述符，错误则返回-1
```

- returns a small identifing integer file descriptor
  - fd == -1 indicates that an error occurred
open 函数将 filename 转换为一个文件描述符，并且返回描述符数字
返回的描述符总是在进程中当前没有打开地最小描述符
flags 参数指明了进程打算如何访问这个文件：

- O_RDONLY：只读
- O_WRONLY：只写
- O_RDWR：读写

```C
int fd;
if ((fd = open("/etc/hosts", "r"))<0) {
  perror("open");
  exit(1);
}
```

mode 参数指定新文件地访问权限位

Each process created by a Linux shell begins life with three open files associated with a terminal:

- 0: standard input(stdin)
- 1: standard output(stdout)
- 2: standard error(stderr)

Closing a file informs the kernel that you are finished accessing that file

```C
#include <unistd.h>

int close(int fd);
// 成功返回0 出错返回-1
```

### 读和写文件

调用 read 和 write 函数来执行输入和输出

```C
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t n);
// 成功返回读的字节数，若EOF则为0，出错返回-1
ssize_t write(int fd, const void *buf, size_t n);
// 成功返回写的字节数，出错返回-1
```

read 函数从描述符为 fd 的当前文件位置复制最读多 *n* 个字节到内存位值buf
write 函数从内存位置buf复制至多*n*个字节到描述符fd的当前文件位置

通过调用 lseek 函数显式地修改当前文件的位置

在 x86-64 系统中，size_t 被定义为 unsigned long，而 ssize_t（有符号的大小）被定义为 long
read 函数返回一个有符号的大小，因为出错时必须返回-1，这浪费了一半数值范围

#### On Short Counts

在某些情况下，read 和 write 传递地字节比应用程序要求的要少。这些不足值（short count）不表示有错误。出现这样情况的原因有：
Short counts can occur in there situations:

- Encounter(end-of-file)EOF on reads 读时遇到 EOF
  - 当读取的字节数超过文件所包含的字节数，例如以50个字节地片读取一个只有20个字节地文件，read返回地不足值为20，此后地 read 将返回不足值0来发出EOF信号
- Reading text lines from a terminal 从终端读文本行
  - 如果打开文件是与终端相关联的（如键盘和显示器），那么每个 read 函数将一次传送一个文本行，返回的不足值等于文本行的大小
- Reading and writing network sockets 读和写网络套接字（socket）
  - 如果打开的文件对应于网络套接字，那么内部缓冲约束和较长的网络延迟会引起 read 和 write 返回不足值
  - 对 Linux 管道（pipe）调用 read 和 write 时，也有可能出现不足值

### 读取文件元数据

应用程序能够通过调用 stat 和 fstat 函数，检索到关于文件的信息（元数据（matedata））

```C
#include <unistd.h>
#include <sys/stat.h>

int stat(const char *filename, struct stat *buf);
int fstat(int fd, struct stat *buf);
// 成功返回0，出错返回-1
```

stat 函数以一个文件名作为输入，并填写一个 stat 数据结构中的各个成员
fstat 函数是相似的，只不过是以文件描述符而不是文件名作为输入

```C
// statbuf.h(included by sys/stat.h)

struct stat {
  dev_t         st_dev;     /* Device */
  ino_t         st_ino;     /* inode */
  mode_t        st_mode;    /* Protection and file type */
  nlink_t       st_nlink;   /* Number of hard links */
  uid_t         st_uid;     /* User ID of owner */
  gid_t         st_gid;     /* Group ID of owner */
  dev_t         st_rdev;    /* Device type (if inode device) */
  off_t         st_size;    /* Total size, in bytes */
  unsigned long st_blksize; /* Blocksize for filesystem I/O */
  unsigned long st_blocks;  /* Number of blocks allocated */
  time_t        st_atime;   /* Time of last access */
  time_t        st_mtime;   /* Time of last modification */
  time_t        st_ctime;   /* Time of last change */
}
```

### 读取目录内容

用 readdir 系列函数来读取目录的内容

```C
#include <sys/types.h>
#include <dirent.h>

DIR *opendir(const char *name);
// 若成功，则返回处理的指针，若出错，则返回 NULL
```

函数 opendir 以路径名为参数，返回指向目录流（directory stream）的指针。流是对条目有序列表的抽象，在这里是指目录项的列表

```C
#include <dirent.h>

struct dirent *readdir(DIR *dirp);
// 若成功，则返回指向下一个目录项的指针；若没有更多的目录项或出错，则返回 NULL
```

每次对 readdir 的调用返回的都是指向流 dirp 中下一个目录项的指针，或者，如果没有更多目录项则返回 NULL
每个目录项都是一个结构，形式如下：

```C
struct dirent {
  ino_t d_ino;        // inode number
  char  d_name[256];  // Filename
}
```

虽然有些 Linux 版本包含了其他的结构成员，但是只有这两个对所有系统来说都是标准的
成员 d_name 是文件名，d_ino 是文件位值
如果出错，则 readdir 返回 NULL，并设置 errno。可惜的是，唯一能区分错误和流结束情况的方法是检查自调用 readdir 以来 errno 是否被修改过

```C
#include <dirent.h>

int closedir(DIR *dirp);
// 成功返回0，错误返回-1
```

函数 closedir 关闭流并释放其所有的资源

### 共享文件（File Sharing）

内核用三个相关的数据结构来表示打开的文件：

- 描述符表（descriptor table）：每个进程都有它独立的描述符表，它的表项是由进程打开的文件描述符来索引的。每个打开的描述符表项指向*文件表*的一个表项
- 文件表（file table）：打开文件的集合是由一张文件表来表示的，所有的进程共享这张表。每个文件表的表项组成（针对我们的目的）包括当前的文件位置、引用计数（reference count）（即当前指向该表项的描述符表项数），以及一个指向 v-node 表中对应表项的指针。关闭一个描述符会减少相应的文件表表项中的引用计数。内核不会删除这个文件表表项，直到它的引用计数为零
- v-node 表（v-node table）：同文件表一样，所有的进程共享这张 v-node 表。每个表项包含 stat 结构中的大多数信息，包括 st_mode 和 st_size 成员

下图展示了一种典型情况，描述符1和4通过不同的打开文件表表项来引用两个不同的文件。没有共享文件，并且每个描述符对应一个不同的文件

![](images/no_share_file.png)

Two distinct descriptors sharing the same disk file through two distinct open file table entries
下图展示多个描述符通过不同的文件表表项来引用同一个文件。如果以同一个 filename 调用 open 函数两次，就会发生这种情况
关键思想是每个描述符都有它自己的文件位置，所以对不同描述符的读操作可以从文件的不同位置获取数据

![](images/share_file.png)

理解父子进程是如何共享文件的：假设在调用 fork 之前，父进程有如图所示的打开文件。下图展示了调用 fork 后的情况。
子进程有一个父进程描述符表的副本。父子进程共享相同的打开文件表集合，因此共享相同的文件位置。一个很重要的结果是，在内核删除相应文件表表项之前，父子进程必须都关闭了它们的描述符

![](images/after%20fork.png)

### I/O 重定向

Linux shell 提供了 I/O 重定向操作符，允许用户将磁盘文件和标准输入输出联系起来

```bash
ls > foo.txt
```

使得 shell 加载和执行 ls 程序，将标准输出重定向到磁盘文件 foo.txt。
I/O 重定向是通过 dup2 函数是项

```C
#include <unistd.h>

int dup2(int oldfd, int newfd);
// 成功返回非负的描述符，出错返回-1
```

dup2 函数复制描述符表表项 oldfd 到描述符表表项 newfd，覆盖描述符表表项 newfd 以前的内容。如果 newfd 已经打开了，dup2 会在复制 oldfd 之前关闭 newfd

### 标准 I/O

C 语言定义了一组高级输入输出函数，称为标准I/O库，为程序员提供了 Unix I/O 的较高级别的替代。这个库（libc）提供了打开和关闭文件的函数（fopen和fclose）、读和写子接的函数（fread和fwrite）、读和写字符串的函数（fgets 和 fputs），以及复杂的格式化的 I/O 函数（scanf 和 printf）
标准 I/O 库将一个打开的文件模型化为一个*流*。对于程序员而言，一个流就是一个指向 FILE 类型的结构的指针。每个 ANSI C 程序开始时都有三个打开的流 stdin、stdout和strerr，分别对应于标准输入、标准输出和标准错误

```C
#include <stdio.h>
extern FILE *stdin;   // Standard input (descriptor 0)
extern FILE *stdout;  // Standard output (descriptor 1)
extern FILE *stderr;  // Standard error (descriptor 2)
```

类型为 FILE 的流是对文件描述符和*流缓冲区*的抽象。流缓冲区的目的和 RIO 读缓冲区的一样：就是使开销较高的 Linux I/O 系统调用的数量尽可能得小

## Network Programming

## Concurrent Programming

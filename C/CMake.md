
make
自动化编译工具

make 只能在 Linux 环境使用

CMake is designed to be used in conjunction with the native build environment.
CMake 被设计来连接本地构建环境（例如 make）的
CMake 脚本会根据平台的不同生成编译脚本（makefile or vs studio 项目文件），实现跨平台编译

make VERBOSE=1
显式编译详情

## 运行 CMake

### 构建项目

除非另行说明，始终应该建立一个专用于构建的目录并在那里构建项目。从技术上来讲，可以进行内部构建（即在源代码目录下执行 CMake 构建命令），但是必须注意不要覆盖文件或者把它们添加到 git

经典的 CMake 构建流程 （TM）：

```bash
mkdir build
cd build
cmake ..
make
```

可以用 cmake --build . 替换 make 这一行。它会调用 make 或者任何你正在使用的构建工具。如果你正在使用版本比较新的 CMake（除非你正在检查对于老版本 CMake 的兼容性，否则应该使用较新的版本），你也可以这样做：

```bash
cmake -S . -B build
cmake --build build
```

以下任何一条命令都能够执行安装：

```bash
# From the build directory (pick one)
make install
cmake --build . --target install
cmake --install . # CMake 3.15+ only

# From the source directory (pick one)
make -C build install
cmake --build build --target install
cmake --install build # CMake 3.15+ only
```

只要别忘记输入构建目录作为参数，在构建目录之外的时间较短，并且从源代码目录更改源代码比较方便就行。应该试着习惯使用 --build，因为它能让你免于只用 make 来构建。需要注意的是，在构建目录下进行工作一直都非常普遍，并且一些工具和命令（包括 CTest）仍然需要在 build 目录中才能工作。

额外解释一下，可以指定 CMake 工作在来自构建目录的源代码目录，也可以工作在任何现有的构建目录。

如果使用 `cmake --build` 而不是直接调用更底层的构建系统（比如直接使用 `make`），你可以用 `-v` 参数在构建时获得详细的输出（CMake 3.14+），用 `-j N` 指定用 N 个 CPU 核心并行构建项目（CMake 3.12+），以及用 `--target`（任意版本的 CMake）或 `-t`（CMake 3.15+）来选择一个目标进行部分地构建。这些命令因不同的构建系统而异，例如 `VERBOSE=1 make` 和 `ninja -v`。你也可以使用环境变量替代它们，例如 `CMAKE_BUILD_PARALLEL_LEVEL` (CMake 3.12+) 和 `VERBOSE` (CMake 3.14+)。

### 指定编译器

指定编译器必须在第一次运行时在空目录中进行。这种命令并不属于 CMake 语法，但你仍可能不太熟悉它。如果要选择 Clang：

```bash
CC=clang CXX=clang++ cmake ..
```

这条命令设置了 bash 里的环境变量 CC 和 CXX，并且 CMake 会使用这些参数。这一行命令就够了，只需要调用一次；之后 CMake 会继续使用从这些变量里推导出来的路径。

### 指定生成器

可以选择的构建工具有很多；通常默认的是 make。要显示在你的系统上 CMake 可以调用的所有构建工具，运行：

```bash
cmake --help
```

也可以用 `-G"My Tool"`（仅当构建工具的名字中包含空格时才需要引号）来指定构建工具。像指定编译器一样，你应该在一个目录中第一次调用 CMake 时就指定构建工具。如果有好几个构建目录也没关系，比如 `build/` 和 `buildXcode`。你可以用环境变量 `CMAKE_GENERATOR` 来指定默认的生成器（CMake 3.15+）。需要注意的是，makefiles 只会在你明确地指出线程数目之时才会并行运行，比如 `make -j2`，而 Ninja 却会自动地并行运行。在较新版本的 CMake 中，你能直接传递并行选项，比如`-j2`，到命令 `cmake --build`。

### 设置选项

在 CMake 中，你可以使用 `-D` 设置选项。你能使用 `-L` 列出所有选项，或者用 `-LH` 列出人类更易读的选项列表。如果你没有列出源代码目录或构建目录，这条命令将不会重新运行 CMake（使用 `cmake -L` 而不是 `cmake -L .`）。

### 详细和部分的构建

同样，这不属于 CMake，如果你正使用像 `make` 一样的命令行构建工具，你能获得详细的输出：

```bash
~/package/build $ VERBOSE=1 make96

# 我们已经提到了在构建时可以有详细输出，但你也可以看到详细的 CMake 配置输出。`--trace` 选项能够打印出运行的 CMake 的每一行。由于它过于冗长，CMake 3.7 添加了 `--trace-source="filename"` 选项，这让你可以打印出你想看的特定文件运行时执行的每一行。如果你选择了要调试的文件的名称（在调试一个 CMakeLists.txt 时通常选择父目录，因为它们名字都一样），你就会只看到这个文件里运行的那些行。这很实用！
```

实际上你写成 `make VERBOSE=1`，make 也能正确工作，但这是 `make` 的一个特性而不是命令行的惯用写法。

你也可以通过指定一个目标来仅构建一部分，例如指定你已经在 CMake 中定义的库或可执行文件的名称，然后 make 将会只构建这一个目标。

### 选项

CMake 支持缓存选项。CMake 中的变量可以被标记为 "cached"，这意味着它会被写入缓存（构建目录中名为 `CMakeCache.txt` 的文件）。你可以在命令行中用 -D 预先设定（或更改）缓存选项的值。CMake 查找一个缓存的变量时，它就会使用已有的值并且不会覆盖这个值。

### 标准选项

大部分软件包中都会用到以下的 CMake 选项：

- `-DCMAKE_BUILD_TYPE=` 从 Release， RelWithDebInfo， Debug， 或者可能存在的更多参数中选择。
- `-DCMAKE_INSTALL_PREFIX=` 这是安装位置。UNIX 系统默认的位置是 `/usr/local`，用户目录是 `~/.local`，也可以是你自己指定的文件夹。
- `-DBUILD_SHARED_LIBS=` 你可以把这里设置为 `ON` 或 `OFF` 来控制共享库的默认值（不过，你也可以明确选择其他值而不是默认值）
- `-DBUILD_TESTING=` 这是启用测试的通用名称，当然不会所有软件包都会使用它，有时这样做确实不错。

### 调试你的 CMake 文件

我们已经提到了在构建时可以有详细输出，但你也可以看到详细的 CMake 配置输出。`--trace` 选项能够打印出运行的 CMake 的每一行。由于它过于冗长，CMake 3.7 添加了 `--trace-source="filename"` 选项，这让你可以打印出你想看的特定文件运行时执行的每一行。如果你选择了要调试的文件的名称（在调试 CMakeLists.txt 时通常选择父目录，因为它的名字在任何项目中都一样），你就会只看到这个文件里运行的那些行。这很实用！

## 基础知识

### 最低版本要求

这是每个 CMakeLists.txt 都必须包含的第一行

```cmake
cmake_minimum_required(VERSION 3.1)
```

关于 CMake 的语法。命令 [cmake_minimum_required](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html) 是不区分大小写的，所以常用的做法是使用小写。 `VERSION` 和它后面的版本号是这个函数的特殊关键字。

这一行很特殊！ CMake 的版本与它的特性（policies）相互关联，这意味着它也定义了 CMake 行为的变化。因此，如果你将 `cmake_minimum_required` 中的 `VERSION` 设定为 `2.8`，那么你将会在 macOS 上产生链接错误，例如，即使在 CMake 最新的版本中，如果你将它设置为 3.3 或者更低，那么你将会得到一个隐藏的标志行为(symbols behaviour)错误等。你可以在 policies 中得到一系列 policies 与 versions 的说明。

从 CMake 3.12 开始，版本号可以声明为一个范围，例如 `VERSION 3.1...3.15`；这意味着这个工程最低可以支持 `3.1` 版本，但是也最高在 `3.15` 版本上测试成功过。这对需要更精确(better)设置的用户体验很好，并且由于一个语法上的小技巧，它可以向后兼容更低版本的 CMake （尽管在这里例子中虽然声明为 `CMake 3.1-3.15` 实际只会设置为 `3.1` 版本的特性，因为这些版本处理这个工程没有什么差异）。新的版本特性往往对 macOS 和 Windows 用户是最重要的，他们通常使用非常新版本的 CMake。

当你开始一个新项目，起始推荐这么写：

```cmake
cmake_minimum_required(VERSION 3.7...3.21)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()
```

如果 CMake 的版本低于3.12，`if` 块条件为真，CMake 将会被设置为当前版本。如果 CMake 版本是 3.12 或者更高，`if` 块条件为假，将会遵守 `cmake_minimum_required` 中的规定，程序将继续正常运行。

### 设置一个项目

现在，每一个顶层 CMakelists 文件都应该有下面这一行：

```cmake
project(MyProject VERSION 1.0
                  DESCRIPTION "Very nice project"
                  LANGUAGES CXX)
```

这里的字符串是带引号的，因此内容中可以带有空格。项目名称是这里的第一个参数。所有的关键字参数都可选的。`VERSION` 设置了一系列变量，例如 `MyProject_VERSION` 和 `PROJECT_VERSION`。语言可以是 `C`,`CXX`,`Fortran`,`ASM`,`CUDA`(CMake 3.8+),`CSharp`(3.8+),`SWIFT`(CMake 3.15+ experimental)，默认是`C CXX`。在 CMake 3.9，可以通过`DESCRIPTION` 关键词来添加项目的描述。这个关于 [project](https://cmake.org/cmake/help/latest/command/project.html) 的文档可能会有用。

项目名称没有什么特别的用处。这里没有添加任何的目标(target)。

### 生成一个可执行文件

```cmake
add_executable(one two.cpp three.h)
```

`one` 既是生成的可执行文件的名称，也是创建的 `CMake` 目标(target)的名称(我保证，你很快会听到更多关于目标的内容)。紧接着的是源文件的列表，你想列多少个都可以。CMake 很聪明 ，它根据拓展名只编译源文件。在大多数情况下，头文件将会被忽略；列出他们的唯一原因是为了让他们在 IDE 中被展示出来，目标文件在许多 IDE 中被显示为文件夹。你可以在 [buildsystem](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html) 中找到更多关于一般构建系统与目标的信息。

### 生成一个库

制作一个库是通过 add_library 命令完成的，并且非常简单：

```cmake
add_library(one STATIC two.cpp three.h)
```

你可以选择库的类型，可以是 `STATIC`,`SHARED`, 或者`MODULE`.如果你不选择它，CMake 将会通过 `BUILD_SHARED_LIBS` 的值来选择构建 `STATIC` 还是 `SHARED` 类型的库。

在下面的章节中你将会看到，你经常需要生成一个虚构的目标，也就是说，一个不需要编译的目标。例如，只有一个头文件的库。这被叫做 `INTERFACE` 库，这是另一种选择，和上面唯一的区别是后面不能有文件名。

你也可以用一个现有的库做一个 `ALIAS` 库，这只是给已有的目标起一个别名。这么做的一个好处是，你可以制作名称中带有 `::` 的库。

### 目标时常伴随着你

现在我们已经指定了一个目标，那我们如何添加关于它的信息呢？例如，它可能需要包含一个目录：

```cmake
target_include_directories(one PUBLIC include)
```

`target_include_directories` 为目标添加了一个目录。 `PUBLIC` 对于一个二进制目标没有什么含义；但对于库来说，它让 CMake 知道，任何链接到这个目标的目标也必须包含这个目录。其他选项还有 `PRIVATE`（只影响当前目标，不影响依赖），以及 `INTERFACE`（只影响依赖）。

接下来我们可以将目标之间链接起来：

```cmake
add_library(another STATIC another.cpp another.h)
target_link_libraries(another PUBLIC one)
```

`target_link_libraries` 可能是 CMake 中最有用也最令人迷惑的命令。它指定一个目标，并且在给出目标的情况下添加一个依赖关系。如果不存在名称为 `one` 的目标，那他会添加一个链接到你路径中 `one` 库（这也是命令叫 `target_link_libraries` 的原因）。或者你可以给定一个库的完整路径，或者是链接器标志。最后再说一个有些迷惑性的知识：），经典的 CMake 允许你省略 `PUBLIC` 关键字，但是你在目标链中省略与不省略混用，那么 CMake 会报出错误。

只要记得在任何使用目标的地方都指定关键字，那么就不会有问题。

目标可以有包含的目录、链接库（或链接目标）、编译选项、编译定义、编译特性（见C++11 章节）等等。正如你将在之后的两个项目章节中看到的，你经常可以得到目标（并且经常是指定目标）来代表所有你使用的库。甚至有些不是真正的库，像 `OpenMP`，就可以用目标来表示。这也是为什么现代 CMake 如此的棒！

### 更进一步

看看你是否能理解以下文件。它生成了一个简单的 C++11 的库并且在程序中使用了它。没有依赖。我将在之后讨论更多的 C++ 标准选项，代码中使用的是 CMake 3.8。

```cmake
cmake_minimum_required(VERSION 3.8)

project(Calculator LANGUAGES CXX)

add_library(calclib STATIC src/calclib.cpp include/calc/lib.hpp)
target_include_directories(calclib PUBLIC include)
target_compile_features(calclib PUBLIC cxx_std_11)

add_executable(calc apps/calc.cpp)
target_link_libraries(calc PUBLIC calclib)
```

### 变量与缓存

#### 本地变量

可以这样声明一个本地 ( local ) 变量：

```cmake
set(MY_VARIABLE "value")
```

变量名通常全部用大写，变量值跟在其后。你可以通过 `${}` 来解析一个变量，例如 `${MY_VARIABLE}`. CMake 有作用域的概念，在声明一个变量后，你只可以在它的作用域内访问这个变量。如果你将一个函数或一个文件放到一个子目录中，这个变量将不再被定义。你可以通过在变量声明末尾添加 `PARENT_SCOPE` 来将它的作用域置定为当前的上一级作用域。

列表就是简单地包含一系列变量：

```cmake
set(MY_LIST "one" "two")
```

你也可以通过 `;` 分隔变量，这和空格的作用是一样的：

```cmake
set(MY_LIST "one;two")
```

有一些和 `list(` 进行协同的命令， `separate_arguments` 可以把一个以空格分隔的字符串分割成一个列表。需要注意的是，在 CMake 中如果一个值没有空格，那么加和不加引号的效果是一样的。这使你可以在处理知道不可能含有空格的值时不加引号。

当一个变量用 `${}` 括起来的时候，空格的解析规则和上述相同。对于路径来说要特别小心，路径很有可能会包含空格，因此你应该总是将解析变量得到的值用引号括起来，也就是，应该这样 `"${MY_PATH}"` 。

#### 缓存变量

CMake 提供了一个缓存变量来允许你从命令行中设置变量。CMake 中已经有一些预置的变量，像 `CMAKE_BUILD_TYPE` 。如果一个变量还没有被定义，你可以这样声明并设置它。

```cmake
set(MY_CACHE_VARIABLE "VALUE" CACHE STRING "Description")
```

这么写**不会覆盖**已定义的值。这是为了让你只能在命令行中设置这些变量，而不会在 CMake 文件执行的时候被重新覆盖。如果你想把这些变量作为一个临时的全局变量，你可以这样做：

```cmake
set(MY_CACHE_VARIABLE "VALUE" CACHE STRING "" FORCE)
mark_as_advanced(MY_CACHE_VARIABLE)
```

第一行将会强制设置该变量的值，第二行将使得用户运行 `cmake -L ..` 或使用 GUI 界面的时候不会列出该变量。此外，你也可以通过 `INTERNAL` 这个类型来达到同样的目的（尽管在技术上他会强制使用 STRING 类型，这不会产生任何的影响）：

```cmake
set(MY_CACHE_VARIABLE "VALUE" CACHE INTERNAL "")
```

因为 `BOOL` 类型非常常见，你可以这样非常容易的设置它：

```cmake
option(MY_OPTION "This is settable from the command line" OFF)
```

对于 BOOL 这种数据类型，对于它的 ON 和 OFF 有几种不同的说辞 (wordings) 。

你可以查看 [cmake-variables](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html) 来查看 CMake 中已知变量的清单。

CMake 有一些特殊的变量，它们有些是在幕后创建的，有些是在项目代码中设置的。其中许多变量以 `CMAKE_` 开头。在为项目创建变量时，应避免使用这种命名约定。
其中两个特殊的用户可设置变量是 `CMAKE_CXX_STANDARD` 和 `CMAKE_CXX_STANDARD_REQUIRED` 这两个变量可以一起使用，以指定构建项目所需的 C++ 标准库。

```cmake
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
```

有时，在 CMakelists.txt 文件中定义的变量也可以在源代码中使用。比如我们想要打印项目版本。
实现这一目的的方法之一是使用配置头文件。首先创建一个输入文件，其中包含一个或多个要替换的变量。这些变量有特殊的语法，看起来像 `@VAR@`。然后，使用 `configure_file()` 命令将输入文件复制到给定的输出文件，并用 CMakelists.txt 文件中 `VAR` 的当前值替换这些变量。

虽然可以直接在源代码中编辑版本，但更倾向于使用这一功能，因为它可以创建一个单一的真实源，并避免重复。

调用 project() 命令时，CMake 会在幕后定义 `Tutorial_VERSION_MAJOR` 和 `Tutorial_VERSION_MINOR`。
使用 `configure_file()` 复制输入文件，并替换指定的 CMake 变量

```cmake
project(Tutorial VERSION 1.0)
configure_file(TutorialConfig.h.in TutorialConfig.h)
```

由于配置文件将写入项目二进制目录，我们必须将该目录添加到搜索 `include` 文件的路径列表中。使用 `target_include_directories()` 来指定可执行目标应在何处查找 `include` 文件。

```cmake
target_include_directories(Tutorial PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )
```

TutorialConfig.h.in 是要配置的输入头文件。当从 CMakeLists.txt 调用 configure_file() 时，@Tutorial_VERSION_MAJOR@ 和 @Tutorial_VERSION_MINOR@ 的值将被替换为 TutorialConfig.h 中项目的相应版本号。

```c++
// the configured options and settings for Tutorial
#define Tutorial_VERSION_MAJOR @Tutorial_VERSION_MAJOR@
#define Tutorial_VERSION_MINOR @Tutorial_VERSION_MINOR@
```

#### 环境变量

你也可以通过 `set(ENV{variable_name} value)` 和 `$ENV{variable_name}` 来设置和获取环境变量，不过一般来说，我们最好避免这么用。

#### 缓存

缓存实际上就是个文本文件，`CMakeCache.txt` ，当你运行 CMake 构建目录时会创建它。 CMake 可以通过它来记住你设置的所有东西，因此你可以不必在重新运行 CMake 的时候再次列出所有的选项。

#### 属性

CMake 也可以通过属性来存储信息。这就像是一个变量，但它被附加到一些其他的物体 ( item ) 上，像是一个目录或者是一个目标。一个全局的属性可以是一个有用的非缓存的全局变量。许多目标属性都是被以 `CMAKE_` 为前缀的变量来初始化的。例如你设置 `CMAKE_CXX_STANDARD` 这个变量，这意味着你之后创建的所有目标的 `CXX_STANDARD` 都将被设为`CMAKE_CXX_STANDARD` 变量的值。

你可以这样来设置属性：

```cmake
set_property(TARGET TargetName
             PROPERTY CXX_STANDARD 11)

set_target_properties(TargetName PROPERTIES
                      CXX_STANDARD 11)
```

第一种方式更加通用 ( general ) ，它可以一次性设置多个目标、文件、或测试，并且有一些非常有用的选项。第二种方式是为一个目标设置多个属性的快捷方式。此外，你可以通过类似于下面的方式来获得属性：

```cmake
get_property(ResultVariable TARGET TargetName PROPERTY CXX_STANDARD)
```

可以查看 [cmake-properties](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html) 获得所有已知属性的列表。在某些情况下，你也可以自己定义一些属性。

### 用 CMake 进行编程

#### 控制流程

CMake 有一个 [if](https://cmake.org/cmake/help/latest/command/if.html) 语句，尽管经过多次版本迭代它已经变得非常复杂。这里有一些全大写的变量你可以在 `if` 语句中使用，并且你既可以直接引用也可以利用 `${}` 来对他进行解析（ `if` 语句在历史上比变量拓展出现的更早 ）。这是一个 `if` 语句的例子：

```cmake
if(variable)
    # If variable is `ON`, `YES`, `TRUE`, `Y`, or non zero number
else()
    # If variable is `0`, `OFF`, `NO`, `FALSE`, `N`, `IGNORE`, `NOTFOUND`, `""`, or ends in `-NOTFOUND`
endif()
# If variable does not expand to one of the above, CMake will expand it then try again
```

如果你在这里使用 `${variable}` 可能会有一些奇怪，因为看起来它好像 `variable` 被展开 ( expansion ) 了两次。在 CMake 3.1+ 版本中加入了一个新的特性 ( [CMP0054](https://cmake.org/cmake/help/latest/policy/CMP0054.html) ) ，CMake 不会再展开已经被引号括起来的展开变量。也就是说，如果你的 CMake 版本大于 `3.1` ，那么你可以这么写：

```cmake
if("${variable}")
    # True if variable is not false-like
else()
    # Note that undefined variables would be `""` thus false
endif()
```

这里还有一些关键字可以设置，例如：

- 一元的: `NOT`, `TARGET`, `EXISTS` (文件), `DEFINED`, 等。
- 二元的: `STREQUAL`, `AND`, `OR`, `MATCHES` ( 正则表达式 ), `VERSION_LESS`, `VERSION_LESS_EQUAL` ( CMake 3.7+ ), 等。
- 括号可以用来分组

#### generator-expressions

[generator-expressions](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html)语句十分强大，不过有点奇怪和专业 ( specialized ) 。大多数 CMake 命令在配置的时候执行，包括我们上面看到的 `if` 语句。但是如果你想要他们在构建或者安装的时候运行呢，应该怎么写？ 生成器表达式就是为此而生。它们在目标属性中被评估（ evaluate ）：

最简单的生成器表达式是信息表达式，其形式为 `$<KEYWORD>`；它会评估和当前配置相关的一系列信息。信息表达式的另一个形式是 `$<KEYWORD:value>`，其中 `KEYWORD` 是一个控制评估的关键字，而 `value` 则是被评估的对象（ 这里的 `value` 中也允许使用信息表达式，如下面的 `${CMAKE_CURRENT_SOURCE_DIR}/include` ）。如果 `KEYWORD` 是一个可以被评估为0或1的生成器表达式或者变量，如果（`KEYWORD`被评估）为1则 `value` 会在这里被保留下来，而反之则不会。你可以使用嵌套的生成器表达式，你也可以使用变量来使得自己更容易理解嵌套的变量。一些表达式也可以有多个值，值之间通过逗号分隔。

如果你有一个只想在配置阶段的 DEBUG 模式下开启的编译标志（ flag ），你可以这样做：

```cmake
target_compile_options(MyTarget PRIVATE "$<$<CONFIG:Debug>:--my-flag>")
```

注：这里有点迷惑性，这里其实包含了两种 generator-expression，分别是 configuration-expression 和 conditional-expression，前者使用的形式是 `$<CONFIG:cfgs>`，这里的 cfgs 是一个 List，如果 CONFIG 满足 cfgs 列表中的任何一个值，这个表达式会被评估（evaluate）为 1，否则为 0。后者使用的形式是 `$<condition:true_string>`，如果 condition 值为 1，则表达式被评估为 true_string，否则为空值。因此这里表达的含义是，如果这里是一个 DEBUG 的 configuration，就设置 --my-flag。可参见[官方文档](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:condition)。

这是一个相比与指定一些形如 `*_DEBUG` 这样的变量更加新颖并且更加优雅的方式，并且这对所有支持生成器表达式的设置都通用。需要注意的是，你永远不要在配置阶段（configuration phase）使用配置有关值（configure time value），因为在使用像 IDE 这种多配置生成器时你没法在配置阶段获取到这些值，只有在构建阶段使用生成器表达式或者形如 `*_<CONFIG>` 的变量才能获得。

一些生成器表达式的其他用途：

- 限制某个项目的语言，例如可以限制其语言为 CXX 来避免它和 CUDA 等语言混在一起，或者可以通过封装它来使得他对不同的语言有不同的表现。
- 获得与属性相关的配置，例如文件的位置。
- 为构建和安装生成不同的位置。

最后一个是常见的。你几乎会在所有支持安装的软件包中看到如下代码：

注：表示在目标对于直接 BUILD 使用的目标包含的头文件目录为 `${CMAKE_CURRENT_SOURCE_DIR}/include`，而安装的目标包含的头文件目录为 `include`，是一个相对位置（同时需要 install 对应的头文件才可以）。

```cmake
target_include_directories(
    MyTarget
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
```

#### 宏定义与函数

你可以轻松地定义你自己的 CMake [function](https://cmake.org/cmake/help/latest/command/function.html) 或 [macro](https://cmake.org/cmake/help/latest/command/macro.html) 。函数和宏只有作用域上存在区别，宏没有作用域的限制。所以说，如果你想让函数中定义的变量对外部可见，你需要使用 `PARENT_SCOPE` 来改变其作用域。如果是在嵌套函数中，这会变得异常繁琐，因为你必须在想要变量对外的可见的所有函数中添加 `PARENT_SCOPE` 标志。但是这样也有好处，函数不会像宏那样对外“泄漏”所有的变量。接下来用函数举一个例子：

下面是一个简单的函数的例子：

```cmake
function(SIMPLE REQUIRED_ARG)
    message(STATUS "Simple arguments: ${REQUIRED_ARG}, followed by ${ARGN}")
    set(${REQUIRED_ARG} "From SIMPLE" PARENT_SCOPE)
endfunction()

simple(This Foo Bar)
message("Output: ${This}")
```

输出如下：

```bash
-- Simple arguments: This, followed by Foo;Bar
Output: From SIMPLE
```

如果你想要有一个指定的参数，你应该在列表中明确的列出，除此之外的所有参数都会被存储在 `ARGN` 这个变量中（ `ARGV` 中存储了所有的变量，包括你明确列出的 ）。CMake 的函数没有返回值，你可以通过设定变量值的形式来达到同样地目的。在上面的例子中，你可以通过指定变量名来设置一个变量的值。

#### 参数的控制

你应该已经在很多 CMake 函数中见到过，CMake 拥有一个变量命名系统。你可以通过 [cmake_parse_arguments](https://cmake.org/cmake/help/latest/command/cmake_parse_arguments.html) 函数来对变量进行命名与解析。如果你想在低于 3.5 版本的CMake 系统中使用它，你应该包含 [CMakeParseArguments](https://cmake.org/cmake/help/latest/module/CMakeParseArguments.html) 模块，此函数在 CMake 3.5 之前一直存在与上述模块中。这是使用它的一个例子：

```cmake
function(COMPLEX)
    cmake_parse_arguments(
        COMPLEX_PREFIX
        "SINGLE;ANOTHER"
        "ONE_VALUE;ALSO_ONE_VALUE"
        "MULTI_VALUES"
        ${ARGN}
    )
endfunction()

complex(SINGLE ONE_VALUE value MULTI_VALUES some other values)
```

在调用这个函数后，会生成以下变量：

```cmake
COMPLEX_PREFIX_SINGLE = TRUE
COMPLEX_PREFIX_ANOTHER = FALSE
COMPLEX_PREFIX_ONE_VALUE = "value"
COMPLEX_PREFIX_ALSO_ONE_VALUE = <UNDEFINED>
COMPLEX_PREFIX_MULTI_VALUES = "some;other;values"
```

如果你查看了官方文档，你会发现可以通过 set 来避免在 list 中使用分号，你可以根据个人喜好来确定使用哪种结构。你可以在上面列出的位置参数中混用这两种写法。此外，其他剩余的参数（因此参数的指定是可选的）都会被保存在 `COMPLEX_PREFIX_UNPARSED_ARGUMENTS` 变量中。

### 添加库

使用 `add_library()` 命令添加一个库，并指定组成该库的源文件。可以用一个或多个子目录来组织项目，而不是将所有源文件放在一个目录中。
在本例中，我们将专门为库创建一个子目录。在这里，我们可以添加一个新的 CMakeLists.txt 文件和一个或多个源文件。在顶层 CMakeLists.txt 文件中，我们将使用 `add_subdirectory()` 命令将子目录添加到构建中。

一旦创建了库，它就会通过 `target_include_directories()` 和 `target_link_libraries()` 连接到我们的可执行目标。

MathFunctions 文件夹下的 CmakeLists.txt：

```cmake
# 创建 MathFunctions 库
add_library(MathFunctions MathFunctions.cxx mysqrt.cxx)
```

根目录的 CmakeList.txt：

```cmake
# 编译该库
add_subdirectory(MathFunctions)
# 将该库链接到可执行目标（target）上
target_link_libraries(Tutorial PUBLIC MathFunctions)
# 将该库的头文件添加到搜索路径上
# 注：${PROJECT_SOURCE_DIR} 是项目源代码路径
target_include_directories(Tutorial PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/MathFunctions"
                          )
```

现在就可以在源代码中引入 MathFunctions 库的头文件，并使用库函数了

```c++
#include "MathFunctions.h"

double outputValue = MathFunctions::sqrt(inputValue);
```

现在，让我们在 MathFunctions 库中添加一个选项，允许开发人员选择自定义平方根实现或内置标准实现。虽然在教程中确实不需要这样做，但对于大型项目来说，这是经常发生的事情。

CMake 可以使用 option() 命令实现这一功能。这将为用户提供一个变量，他们可以在配置 cmake 编译时对其进行更改。该设置将保存在缓存中，因此用户无需每次在构建目录上运行 CMake 时都设置该值。

首先在 MathFunctions/CMakeLists.txt 中使用 option() 命令创建变量 USE_MYMATH。在同一文件中，使用该选项将编译定义传递给 MathFunctions 库。
然后，更新 MathFunctions.cxx，根据 USE_MYMATH 重定向编译。
最后，通过在 MathFunctions/CMakeLists.txt 的 USE_MYMATH 块内将 mysqrt.cxx 设为自己的库，防止在 USE_MYMATH 启用时编译 mysqrt.cxx。

MathFunctions/CMakeLists.txt：

```cmake
option(USE_MYMATH "Use tutorial provided math implementation" ON)

# 使用这一新选项使我们的程序库与 mysqrt 函数的构建和链接成为有条件的。
# 创建一条 if() 语句，检查 USE_MYMATH 的值。在 if() 块中，将 target_compile_definitions() 命令与编译定义 USE_MYMATH 放在一起。
if (USE_MYMATH)
  target_compile_definitions(MathFunctions PRIVATE "USE_MYMATH")
endif()
```

当 USE_MYMATH 开启时，编译定义 USE_MYMATH 将被设置。然后，我们就可以使用该编译定义来启用或禁用源代码的各个部分。

MathFunctions/MathFunctions.cxx
```c++
#include <cmath>

#ifdef USE_MYMATH
#  include "mysqrt.h"
#endif

#ifdef USE_MYMATH
  return detail::mysqrt(x);
#else
  return std::sqrt(x);
#endif
```

此时，如果关闭 USE_MYMATH，就不会使用 mysqrt.cxx，但它仍会被编译，因为 MathFunctions 目标程序的源代码中列出了 mysqrt.cxx。

有几种方法可以解决这个问题。第一种方法是使用 target_sources()，在 USE_MYMATH 代码块中添加 mysqrt.cxx。另一种方法是在 USE_MYMATH 代码块中创建一个额外的库，负责编译 mysqrt.cxx。在本教程中，我们将创建一个附加库。

```cmake
# 首先创建 SqrtLibrary 库，该库包含 mysqrt.cxx
add_library(SqrtLibrary STATIC
            mysqrt.cxx
            )
# 然后将该库链接到 MathFunctions
target_link_libraries(MathFunctions PUBLIC SqrtLibrary)
# 最后从MathFunctions 库源代码列表中删除 mysqrt.cxx
add_library(MathFunctions MathFunctions.cxx)
```

有了这些更改，mysqrt 函数现在对于构建和使用 MathFunctions 函数库的用户来说完全是可选的了。用户可以切换 USE_MYMATH 来控制在构建过程中使用哪个库。

### 为库添加使用要求（usage requirement）

目标参数（target parameters）的使用要求（usage requirements）可以更好地控制库或可执行文件的链接和包含（include）行，同时还能在 CMake 内部更好地控制目标的传递属性。利用使用要求的主要命令有

- target_compile_definitions(): Add compile definitions to a target
  - 指定编译 target 时要用的编译定义。被指定的 target 必须是通过 `add_executable()` 或 `add_library()` 命令创建的，而且不能是 ALIAS　target
  - 需要使用 `INTERFACE`、`PUBLIC` 和 `PRIVATE` 关键字来指定以下参数的范围。`PRIVATE` 和 `PUBLIC` 项将填充 `target` 的 `COMPILE_DEFINITIONS` 属性。`PUBLIC` 和 `INTERFACE` 项将填充 `target` 的 `INTERFACE_COMPILE_DEFINITIONS` 属性。以下参数指定了编译定义。对同一 `target` 的重复调用将按调用顺序追加项目。
- target_compile_options(): Add compile options to a target
- target_include_directories(): Add include directories to a target
- target_link_directories(): Add link directories to a target
- target_link_options(): Add options to the link step for an executable, shared library or module library target
- target_precompile_headers(): Add a list of header files to precompile
  - 预编译头文件可以加快编译速度，方法是创建某些头文件的部分处理版本，然后在编译过程中使用该版本，而不是反复解析原始头文件
- target_sources(): Add sources to a target

在本练习中，我们将重构添加库中的代码，以使用现代 CMake 方法。我们将让我们的库定义自己的使用要求，以便在必要时将它们传递给其他目标。在这种情况下，`MathFunctions` 将自行指定所需的包含目录。然后，目标 `Tutorial` 只需链接到 `MathFunctions`，而不必担心任何额外的 include 目录。
首先，在 `MathFunctions/CMakeLists` 中添加对 `target_include_directories()` 的调用。请记住，`CMAKE_CURRENT_SOURCE_DIR` 是当前正在处理的源代码目录的路径。
然后，更新（并简化！）顶层 CMakeLists.txt 中对 `target_include_directories()` 的调用。

要说明的是，链接到 `MathFunctions` 的任何人都需要包含当前源代码目录，而 `MathFunctions` 本身则不需要。这可以用 `INTERFACE` 使用要求来表达。请记住，`INTERFACE` 意味着消费者需要但生产者不需要的东西。

```cmake
target_include_directories(MathFunctions
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           )
```

既然我们已经指定了 MathFunctions 的使用要求，就可以放心地从顶层的 CMakeLists.txt 删除 EXTRA_INCLUDES 变量的使用了。

```cmake

```

请注意，使用这种技术，我们的可执行目标要使用我们的库，唯一要做的就是调用 `target_link_libraries()`，并输入目标库的名称。在大型项目中，手动指定库依赖关系的传统方法很快就会变得非常复杂。


既然我们已经将代码转换为更现代的方法，那么让我们来演示一下为多个目标设置属性的现代技术。

让我们重构现有代码，使用 INTERFACE 库。下一步我们将使用该库演示生成器表达式的常用用法。




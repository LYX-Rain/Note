
make
自动化编译工具

make 只能在 Linux 环境使用

CMake is designed to be used in conjunction with the native build environment.
CMake 被设计来连接本地构建环境（例如 make）的
CMake 脚本会根据平台的不同生成编译脚本（makefile or vs studio 项目文件），实现跨平台编译

make VERBOSE=1
显式编译详情


## CMakeLists.txt

### 基础

虽然 CMake 支持大写、小写和混合大小写命令，但小写命令时首选

任何项目的 CmakeLists.txt 文件都必须首先使用 `cmake_minimum_required()` 指定 CMake 最低版本。这将建立策略设置，并确保后续 CMake 函数在兼容的 CMake 版本下运行。

要启动一个项目，使用 `project()` 命令来设置项目名称。每个项目都需要调用该命令，而且应该在`cmake_minimum_required()` 之后尽快调用。该命令还可用于指定其他项目级信息，如语言或版本号 

最后 `add_executable()` 命令告诉 CMake 使用指定的源代码文件创建一个可执行文件

```cmake
cmake_minimum_required(VERSION 3.10)
project(Tutorial)
add_executable(Tutorial tutorial.cxx)
```

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




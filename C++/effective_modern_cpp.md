# Effective Modern C++

## 简介

C++98缺少并发的支持（只对C++98和C++03正确），C++11支持lambda表达式（对C++11和C++14正确），C++14提供了普遍的函数返回类型推导（只对C++14正确）。

最遍布C++11各处的特性可能是移动语义了，移动语义的基础是区分右值和左值表达式。那是因为右值表明这个对象适合移动操作，而左值一般不适合。概念上（尽管不经常在实际上用），右值对应于从函数返回的临时对象，而左值对应于你可以引用的（can refer to）对象，或者通过名字，或者通过指针或左值引用。

对于判断一个表达式是否是左值的一个有用的启发就是，看看能否取得它的地址。如果能取地址，那么通常就是左值。如果不能，则通常是右值。这个启发的好处就是帮你记住，一个表达式的类型与它是左值还是右值无关。也就是说，有个类型T，你可以有类型T的左值和右值。当你碰到右值引用类型的形参时，记住这一点非常重要，因为形参本身是个左值：

```c++
class Widget {
public:
    Widget(Widget&& rhs);   //rhs是个左值，
    …                       //尽管它有个右值引用的类型
};

```

在这里，在Widget移动构造函数里取rhs的地址非常合理，所以rhs是左值，尽管它的类型是右值引用。（由于相似的原因，所有形参都是左值。）

那一小段代码揭示了我通常遵循的惯用法：

- 类的名字是Widget。每当我想指代任意的用户定义的类型时，我用Widget来代表。除非我需要展示类中的特定细节，否则我都直接使用Widget而不声明它。
- 我使用形参名rhs（“right-hand side”）。这是我喜欢的移动操作（即移动构造函数和移动赋值运算符）和拷贝操作（拷贝构造函数和拷贝赋值运算符）的形参名。我也在双目运算符的右侧形参用它：
  
  ```C++
  Matrix operator+(const Matrix& lhs, const Matrix& rhs);

  ```

当使用另一个同类型的对象来初始化一个对象时，新的对象被称为是用来初始化的对象（译者注：initializing object，即源对象）的一个副本（copy），尽管这个副本是通过移动构造函数创建的。很抱歉地说，C++中没有术语来区别一个对象是拷贝构造的副本还是移动构造的副本（译者注：此处为了区别拷贝这个“动作”与拷贝得到的“东西”，将copy按语境译为拷贝（动作）和副本（东西），此处及接下来几段按此方式翻译。在后面的条款中可能会不加区别地全部翻译为“拷贝”。）：

```C++
void someFunc(Widget w);        //someFunc的形参w是传值过来

Widget wid;                     //wid是个Widget

someFunc(wid);                  //在这个someFunc调用中，w是通过拷贝构造函数
                                //创建的副本

someFunc(std::move(wid));       //在这个someFunc调用中，w是通过移动构造函数
                                //创建的副本
```

右值副本通常由移动构造产生，左值副本通常由拷贝构造产生。如果你仅仅知道一个对象是其他对象的副本，构造这个副本需要花费多大代价是没法说的。比如在上面的代码中，在不知道是用左值还是右值传给someFunc情况下，没法说来创建形参w花费代价有多大。（你必须还要知道移动和拷贝Widget的代价。）

在函数调用中，调用地传入的表达式称为函数的**实参**（argument）。实参被用来初始化函数的**形参**（parameter）。在上面第一次调用someFunc中，实参为wid。在第二次调用中，实参是std::move(wid)。两个调用中，形参都是w。实参和形参的区别非常重要，因为形参是左值，而用来初始化形参的实参可能是左值或者右值。这一点尤其与**完美转发**（perfect forwarding）过程有关，被传给函数的实参以原实参的右值性（rvalueness）或左值性（lvalueness），再被传给第二个函数。（完美转发讨论细节在Item30。）

设计优良的函数是异常安全（exception safe）的，意味着他们至少提供基本的异常安全保证（即基本保证basic guarantee）。这样的函数保证调用者在异常抛出时，程序不变量保持完整（即没有数据结构是毁坏的），且没有资源泄漏。有强异常安全保证的函数确保调用者在异常产生时，程序保持在调用前的状态。

当我提到“**函数对象**”时，我通常指的是某个支持operator()成员函数的类型的对象。换句话说，这个对象的行为像函数一样。偶尔我用稍微更普遍一些的术语，表示可以用非成员函数语法调用的任何东西（即“fuctionName(arguments)”）。这个广泛定义包括的不仅有支持operator()的对象，还有函数和类似C的函数指针。（较窄的定义来自于C++98，广泛点的定义来自于C++11。）将成员函数指针加进来的更深的普遍化产生了我们所知的**可调用对象**（callable objects）。你通常可以忽略其中的微小区别，简单地认为函数对象和可调用对象为C++中可以用函数调用语法调用的东西。

通过lambda表达式创建的函数对象称为**闭包**（closures）。没什么必要去区别lambda表达式和它们创建的闭包，所以我经常把它们统称lambdas。类似地，我几乎不区分**函数模板**（function templates）（即产生函数的模板）和**模板函数**（template functions）（即从函数模板产生的函数）。**类模板**（class templates）和**模板类**（template classes）同上。

C++中的许多东西都可被声明和定义。声明（declarations）引入名字和类型，并不给出比如存放在哪或者怎样实现等的细节：

```C++
extern int x;                       //对象声明

class Widget;                       //类声明

bool func(const Widget& w);         //函数声明

enum class Color;                   //限域enum声明（见条款10）
```

定义（definitions）提供存储位置或者实现细节：

```C++
int x;                              //对象定义

class Widget {                      //类定义
    …
};

bool func(const Widget& w)
{ return w.size() < 10; }           //函数定义

enum class Color
{ Yellow, Red, Blue };              //限域enum定义
```

定义也有资格称为声明，所以我倾向于只有声明，除非这个东西有个定义非常重要。

我定义一个函数的**签名**（signature）为它声明的一部分，这个声明指定了形参类型和返回类型。函数名和形参名不是签名的一部分。在上面的例子中，func的签名是bool(const Widget&)。函数声明中除了形参类型和返回类型之外的元素（比如noexcept或者constexpr，如果存在的话）都被排除在外。（noexcept和constexpr在Item14和15叙述。）“签名”的官方定义和我的有点不一样，但是对本书来说，我的定义更有用。（官方定义有时排除返回类型。）

新的C++标准保持了旧标准写的代码的有效性，但是偶尔标准化委员会废弃（deprecate）一些特性。这些特性在标准化的“死囚区”中，可能在未来的标准中被移除。编译器可能警告也可能不警告这些废弃特性的使用，但是你应当尽量避免使用它们。它们不仅可能导致将来对移植的头痛，也通常不如来替代它们的新特性。例如，std::auto_ptr在C++11中被废弃，因为std::unique_ptr可以做同样的工作，而且只会做的更好。

有时标准说一个操作的结果有**未定义的行为**（undefined behavior）。这意味着运行时表现是不可预测的，不用说你也想避开这种不确定性。有未定义行为的行动的例子是，在std::vector范围外使用方括号（“[]”），解引用未初始化的迭代器，或者引入数据竞争（即有两个或以上线程，至少一个是writer，同时访问相同的内存位置）。

我将那些比如从new返回的内置指针（build-in pointers）称为原始指针（raw pointers）。原始指针的“反义词”是智能指针（smart pointers）。智能指针通常重载指针解引用运算符（operator->和operator*），但在Item20中解释看std::weak_ptr是个例外。

在源代码注释中，我有时将“constructor”（构造函数）缩写为ctor，将“destructor”（析构函数）缩写为dtor。（译者注：但译文中基本都完整翻译了而没使用缩写。）

## 类型推导

C++98有一套类型推导的规则：用于函数模板的规则。C++11修改了其中的一些规则并增加了两套规则，一套用于auto，一套用于decltype。C++14扩展了auto和decltype可能使用的范围。类型推导的广泛应用，让你从拼写那些或明显或冗杂的类型名的暴行中脱离出来。它让C++程序更具适应性，因为在源代码某处修改类型会通过类型推导自动传播到其它地方。但是类型推导也会让代码更复杂，因为由编译器进行的类型推导并不总是如我们期望的那样进行。

如果对于类型推导操作没有一个扎实的理解，要想写出有现代感的C++程序是不可能的。类型推导随处可见：在函数模板调用中，在大多数auto出现的地方，在decltype表达式出现的地方，以及C++14中令人费解的应用decltype(auto)的地方。

这一章是每个C++程序员都应该掌握的知识。它解释了模板类型推导是如何工作的，auto是如何依赖类型推导的，以及decltype是如何按照它自己那套独特的规则工作的。它甚至解释了你该如何强制编译器使类型推导的结果可视，这能让你确认编译器的类型推导是否按照你期望的那样进行。

### Item 1: Understand template type deduction

对于一个复杂系统的用户来说，很多时候他们最关心的是它做了什么而不是它怎么做的。在这一点上，C++中的模板类型推导表现得非常出色。数百万的程序员只需要向模板函数传递实参，就能通过编译器的类型推导获得令人满意的结果，尽管他们中的大多数在被逼无奈的情况下，对于传递给函数的那些实参是如何引导编译器进行类型推导的，也只能给出非常模糊的描述。

如果那些人中包括你，我有一个好消息和一个坏消息。好消息是现在C++最重要最吸引人的特性auto是建立在模板类型推导的基础上的。如果你满意C++98的模板类型推导，那么你也会满意C++11的auto类型推导。坏消息是当模板类型推导规则应用于auto环境时，有时不如应用于template时那么直观。由于这个原因，真正理解auto基于的模板类型推导的方方面面非常重要。这项条款便包含了你需要知道的东西。

如果你不介意浏览少许伪代码，我们可以考虑像这样一个函数模板：

```C++
template<typename T>
void f(ParamType param);
```

它的调用看起来像这样

```C++
f(expr);                        //使用表达式调用f
```

在编译期间，编译器使用expr进行两个类型推导：一个是针对T的，另一个是针对ParamType的。这两个类型通常是不同的，因为ParamType包含一些修饰，比如const和引用修饰符。举个例子，如果模板这样声明：

```C++
template<typename T>
void f(const T& param);         //ParamType是const T&
```

然后这样进行调用

```C++
int x = 0;
f(x);                           //用一个int类型的变量调用f
```

T被推导为int，ParamType却被推导为const int&


- 在模板类型推导时，有引用的实参会被视为无引用，他们的引用会被忽略
- 对于通用引用的推导，左值实参会被特殊对待
- 对于传值类型推导，const和/或volatile实参会被认为是non-const的和non-volatile的
- 在模板类型推导时，数组名或者函数名实参会退化为指针，除非它们被用于初始化引用


### 条款二：理解auto类型推导

Item 2: Understand auto type deduction

- auto类型推导通常和模板类型推导相同，但是auto类型推导假定花括号初始化代表std::initializer_list，而模板类型推导不这样做
- 在C++14中auto允许出现在函数返回值或者lambda函数形参中，但是它的工作机制是模板类型推导那一套方案，而不是auto类型推导

### 条款三：理解decltype

Item 3: Understand decltype

`decltype`是一个奇怪的东西。给它一个名字或者表达式decltype就会告诉你这个名字或者表达式的类型。通常，它会精确的告诉你你想要的结果。但有时候它得出的结果也会让你挠头半天，最后只能求助网上问答或参考资料寻求启示。

相比模板类型推导和auto类型推导（参见Item1和Item2），decltype只是简单的返回名字或者表达式的类型：

```C++
const int i = 0;                //decltype(i)是const int

bool f(const Widget& w);        //decltype(w)是const Widget&
                                //decltype(f)是bool(const Widget&)

struct Point{
    int x,y;                    //decltype(Point::x)是int
};                              //decltype(Point::y)是int

Widget w;                       //decltype(w)是Widget

if (f(w))…                      //decltype(f(w))是bool

template<typename T>            //std::vector的简化版本
class vector{
public:
    …
    T& operator[](std::size_t index);
    …
};

vector<int> v;                  //decltype(v)是vector<int>
…
if (v[0] == 0)…                 //decltype(v[0])是int&
```

在C++11中，decltype最主要的用途就是用于声明函数模板，而这个函数返回类型依赖于形参类型。举个例子，假定我们写一个函数，一个形参为容器，一个形参为索引值，这个函数支持使用方括号的方式（也就是使用“[]”）访问容器中指定索引值的数据，然后在返回索引操作的结果前执行认证用户操作。函数的返回类型应该和索引操作返回的类型相同。

对一个T类型的容器使用operator[] 通常会返回一个T&对象，比如std::deque就是这样。但是std::vector有一个例外，对于std::vector<bool>，operator[]不会返回bool&，它会返回一个全新的对象（译注：MSVC的STL实现中返回的是std::_Vb_reference<std::_Wrap_alloc<std::allocator<unsigned int>>>对象）。关于这个问题的详细讨论请参见Item6，这里重要的是我们可以看到对一个容器进行operator[]操作返回的类型取决于容器本身。

## 第3章 移步现代C++

条款七：区别使用()和{}创建对象
Item 7: Distinguish between () and {} when creating objects

取决于你看问题的角度，C++11对象初始化的语法可能会让你觉得丰富的让人难以选择，亦或是乱的一塌糊涂。一般来说，初始化值要用圆括号()或者花括号{}括起来，或者放到等号"="的右边：

```C++
int x(0);               //使用圆括号初始化

int y = 0;              //使用"="初始化

int z{ 0 };             //使用花括号初始化
```

在很多情况下，你可以使用"="和花括号的组合：

```C++
int z = { 0 };          //使用"="和花括号
```

在这个条款的剩下部分，我通常会忽略"="和花括号组合初始化的语法，因为C++通常把它视作和只有花括号一样。

“乱的一塌糊涂”是指在初始化中使用"="可能会误导C++新手，使他们以为这里发生了赋值运算，然而实际并没有。对于像int这样的内置类型，研究两者区别就像在做学术，但是对于用户定义的类型而言，区别赋值运算符和初始化就非常重要了，因为它们涉及不同的函数调用：

```C++
Widget w1;              //调用默认构造函数

Widget w2 = w1;         //不是赋值运算，调用拷贝构造函数

w1 = w2;                //是赋值运算，调用拷贝赋值运算符（copy operator=）
```

甚至对于一些初始化语法，在一些情况下C++98没有办法表达预期的初始化行为。举个例子，要想直接创建并初始化一个存放一些特殊值的STL容器是不可能的（比如1,3,5）。

C++11使用统一初始化（uniform initialization）来整合这些混乱且不适于所有情景的初始化语法，所谓统一初始化是指在任何涉及初始化的地方都使用单一的初始化语法。 它基于花括号，出于这个原因我更喜欢称之为括号初始化。（译注：注意，这里的括号初始化指的是花括号初始化，在没有歧义的情况下下文的括号初始化指的都是用花括号进行初始化；当与圆括号初始化同时存在并可能产生歧义时我会直接指出。）统一初始化是一个概念上的东西，而括号初始化是一个具体语法结构。

括号初始化让你可以表达以前表达不出的东西。使用花括号，创建并指定一个容器的初始元素变得很容易：

```C++
std::vector<int> v{ 1, 3, 5 };  //v初始内容为1,3,5
```

括号初始化也能被用于为非静态数据成员指定默认初始值。C++11允许"="初始化不加花括号也拥有这种能力：

```C++
class Widget{
    …

private:
    int x{ 0 };                 //没问题，x初始值为0
    int y = 0;                  //也可以
    int z(0);                   //错误！
}
```

另一方面，不可拷贝的对象（例如std::atomic——见Item40）可以使用花括号初始化或者圆括号初始化，但是不能使用"="初始化：

```C++
std::atomic<int> ai1{ 0 };      //没问题
std::atomic<int> ai2(0);        //没问题
std::atomic<int> ai3 = 0;       //错误！
```

因此我们很容易理解为什么括号初始化又叫统一初始化，在C++中这三种方式都被看做是初始化表达式，但是只有花括号任何地方都能被使用。

括号表达式还有一个少见的特性，即它不允许内置类型间隐式的变窄转换（narrowing conversion）。如果一个使用了括号初始化的表达式的值，不能保证由被初始化的对象的类型来表示，代码就不会通过编译：

```C++
double x, y, z;

int sum1{ x + y + z };          //错误！double的和可能不能表示为int
```

使用圆括号和"="的初始化不检查是否转换为变窄转换，因为由于历史遗留问题它们必须要兼容老旧代码：

```C++
int sum2(x + y +z);             //可以（表达式的值被截为int）

int sum3 = x + y + z;           //同上
```

另一个值得注意的特性是括号表达式对于C++最令人头疼的解析问题有天生的免疫性。（译注：所谓最令人头疼的解析即most vexing parse，更多信息请参见https://en.wikipedia.org/wiki/Most_vexing_parse。）
C++规定任何可以被解析为一个声明的东西必须被解析为声明。这个规则的副作用是让很多程序员备受折磨：他们可能想创建一个使用默认构造函数构造的对象，却不小心变成了函数声明。问题的根源是如果你调用带参构造函数，你可以这样做：

```C++
Widget w1(10);                  //使用实参10调用Widget的一个构造函数
```

但是如果你尝试使用相似的语法调用Widget无参构造函数，它就会变成函数声明：

```C++
Widget w2();                    //最令人头疼的解析！声明一个函数w2，返回Widget
```

由于函数声明中形参列表不能带花括号，所以使用花括号初始化表明你想调用默认构造函数构造对象就没有问题：

```C++
Widget w3{};                    //调用没有参数的构造函数构造对象
```

关于括号初始化还有很多要说的。它的语法能用于各种不同的上下文，它防止了隐式的变窄转换，而且对于C++最令人头疼的解析也天生免疫。既然好到这个程度那为什么这个条款不叫“优先考虑括号初始化语法”呢？

括号初始化的缺点是有时它有一些令人惊讶的行为。这些行为使得括号初始化、std::initializer_list和构造函数参与重载决议时本来就不清不楚的暧昧关系进一步混乱。把它们放到一起会让看起来应该左转的代码右转。举个例子，Item2解释了当auto声明的变量使用花括号初始化，变量类型会被推导为std::initializer_list，但是使用相同内容的其他初始化方式会产生更符合直觉的结果。所以，你越喜欢用auto，你就越不能用括号初始化。

在构造函数调用中，只要不包含std::initializer_list形参，那么花括号初始化和圆括号初始化都会产生一样的结果：

```C++
class Widget { 
public:  
    Widget(int i, bool b);      //构造函数未声明
    Widget(int i, double d);    //std::initializer_list这个形参 
    …
};
Widget w1(10, true);            //调用第一个构造函数
Widget w2{10, true};            //也调用第一个构造函数
Widget w3(10, 5.0);             //调用第二个构造函数
Widget w4{10, 5.0};             //也调用第二个构造函数
```

然而，如果有一个或者多个构造函数的声明包含一个std::initializer_list形参，那么使用括号初始化语法的调用更倾向于选择带std::initializer_list的那个构造函数。如果编译器遇到一个括号初始化并且有一个带std::initializer_list的构造函数，那么它一定会选择该构造函数。如果上面的Widget类有一个std::initializer_list<long double>作为参数的构造函数，就像这样：

```C++
class Widget { 
public:  
    Widget(int i, bool b);      //同上
    Widget(int i, double d);    //同上
    Widget(std::initializer_list<long double> il);      //新添加的
    …
}; 
```

w2和w4将会使用新添加的构造函数，即使另一个非std::initializer_list构造函数和实参更匹配：

```C++
Widget w1(10, true);    //使用圆括号初始化，同之前一样
                        //调用第一个构造函数

Widget w2{10, true};    //使用花括号初始化，但是现在
                        //调用带std::initializer_list的构造函数
                        //(10 和 true 转化为long double)

Widget w3(10, 5.0);     //使用圆括号初始化，同之前一样
                        //调用第二个构造函数 

Widget w4{10, 5.0};     //使用花括号初始化，但是现在
                        //调用带std::initializer_list的构造函数
                        //(10 和 5.0 转化为long double)
```

甚至普通构造函数和移动构造函数都会被带std::initializer_list的构造函数劫持：

```C++
class Widget { 
public:  
    Widget(int i, bool b);                              //同之前一样
    Widget(int i, double d);                            //同之前一样
    Widget(std::initializer_list<long double> il);      //同之前一样
    operator float() const;                             //转换为float
    …
};

Widget w5(w4);                  //使用圆括号，调用拷贝构造函数

Widget w6{w4};                  //使用花括号，调用std::initializer_list构造
                                //函数（w4转换为float，float转换为double）

Widget w7(std::move(w4));       //使用圆括号，调用移动构造函数

Widget w8{std::move(w4)};       //使用花括号，调用std::initializer_list构造
                                //函数（与w6相同原因）
```

编译器一遇到括号初始化就选择带std::initializer_list的构造函数的决心是如此强烈，以至于就算带std::initializer_list的构造函数不能被调用，它也会硬选。

```C++
class Widget { 
public: 
    Widget(int i, bool b);                      //同之前一样
    Widget(int i, double d);                    //同之前一样
    Widget(std::initializer_list<bool> il);     //现在元素类型为bool
    …                                           //没有隐式转换函数
};

Widget w{10, 5.0};              //错误！要求变窄转换
```

这里，编译器会直接忽略前面两个构造函数（其中第二个构造函数是所有实参类型的最佳匹配），然后尝试调用std::initializer_list<bool>构造函数。调用这个函数将会把int(10)和double(5.0)转换为bool，由于会产生变窄转换（bool不能准确表示其中任何一个值），括号初始化拒绝变窄转换，所以这个调用无效，代码无法通过编译。

只有当没办法把括号初始化中实参的类型转化为std::initializer_list时，编译器才会回到正常的函数决议流程中。比如我们在构造函数中用std::initializer_list<std::string>代替std::initializer_list<bool>，这时非std::initializer_list构造函数将再次成为函数决议的候选者，因为没有办法把int和bool转换为std::string:

```C++
class Widget { 
public:  
    Widget(int i, bool b);                              //同之前一样
    Widget(int i, double d);                            //同之前一样
    //现在std::initializer_list元素类型为std::string
    Widget(std::initializer_list<std::string> il);
    …                                                   //没有隐式转换函数
};

Widget w1(10, true);     // 使用圆括号初始化，调用第一个构造函数
Widget w2{10, true};     // 使用花括号初始化，现在调用第一个构造函数
Widget w3(10, 5.0);      // 使用圆括号初始化，调用第二个构造函数
Widget w4{10, 5.0};      // 使用花括号初始化，现在调用第二个构造函数
```

代码的行为和我们刚刚的论述如出一辙。这里还有一个有趣的边缘情况。假如你使用的花括号初始化是空集，并且你欲构建的对象有默认构造函数，也有std::initializer_list构造函数。你的空的花括号意味着什么？如果它们意味着没有实参，就该使用默认构造函数，但如果它意味着一个空的std::initializer_list，就该调用std::initializer_list构造函数。

最终会调用默认构造函数。空的花括号意味着没有实参，不是一个空的std::initializer_list：

```C++
class Widget { 
public:  
    Widget();                                   //默认构造函数
    Widget(std::initializer_list<int> il);      //std::initializer_list构造函数

    …                                           //没有隐式转换函数
};

Widget w1;                      //调用默认构造函数
Widget w2{};                    //也调用默认构造函数
Widget w3();                    //最令人头疼的解析！声明一个函数
```

如果你想用空std::initializer来调用std::initializer_list构造函数，你就得创建一个空花括号作为函数实参——把空花括号放在圆括号或者另一个花括号内来界定你想传递的东西。

```C++
Widget w4({});                  //使用空花括号列表调用std::initializer_list构造函数
Widget w5{{}};                  //同上
```

此时，括号初始化，std::initializer_list和构造函数重载的晦涩规则就会一下子涌进你的脑袋，你可能会想研究半天这些东西在你的日常编程中到底占多大比例。可能比你想象的要有用。因为std::vector作为受众之一会直接受到影响。std::vector有一个非std::initializer_list构造函数允许你去指定容器的初始大小，以及使用一个值填满你的容器。但它也有一个std::initializer_list构造函数允许你使用花括号里面的值初始化容器。如果你创建一个数值类型的std::vector（比如std::vector<int>），然后你传递两个实参，把这两个实参放到圆括号和放到花括号中有天壤之别：

```C++
std::vector<int> v1(10, 20);    //使用非std::initializer_list构造函数
                                //创建一个包含10个元素的std::vector，
                                //所有的元素的值都是20
std::vector<int> v2{10, 20};    //使用std::initializer_list构造函数
                                //创建包含两个元素的std::vector，
                                //元素的值为10和20
```

让我们回到之前的话题。从以上讨论中我们得出两个重要结论。第一，作为一个类库作者，你需要意识到如果一堆重载的构造函数中有一个或者多个含有std::initializer_list形参，用户代码如果使用了括号初始化，可能只会看到你std::initializer_list版本的重载的构造函数。因此，你最好把你的构造函数设计为不管用户是使用圆括号还是使用花括号进行初始化都不会有什么影响。换句话说，了解了std::vector设计缺点后，你以后设计类的时候应该避免诸如此类的问题。

这里的暗语是如果一个类没有std::initializer_list构造函数，然后你添加一个，用户代码中如果使用括号初始化，可能会发现过去被决议为非std::initializer_list构造函数而现在被决议为新的函数。当然，这种事情也可能发生在你添加一个函数到那堆重载函数的时候：过去被决议为旧的重载函数而现在调用了新的函数。std::initializer_list重载不会和其他重载函数比较，它直接盖过了其它重载函数，其它重载函数几乎不会被考虑。所以如果你要加入std::initializer_list构造函数，请三思而后行。

第二，作为一个类库使用者，你必须认真的在花括号和圆括号之间选择一个来创建对象。大多数开发者都使用其中一种作为默认情况，只有当他们不能使用这种的时候才会考虑另一种。默认使用花括号初始化的开发者主要被适用面广、禁止变窄转换、免疫C++最令人头疼的解析这些优点所吸引。这些开发者知道在一些情况下（比如给定一个容器大小和一个初始值创建std::vector）要使用圆括号。默认使用圆括号初始化的开发者主要被C++98语法一致性、避免std::initializer_list自动类型推导、避免不会不经意间调用std::initializer_list构造函数这些优点所吸引。这些开发者也承认有时候只能使用花括号（比如创建一个包含着特定值的容器）。关于花括号初始化和圆括号初始化哪种更好大家没有达成一致，所以我的建议是选择一种并坚持使用它。

- 花括号初始化是最广泛使用的初始化语法，它防止变窄转换，并且对于C++最令人头疼的解析有天生的免疫性
- 在构造函数重载决议中，编译器会尽最大努力将括号初始化与std::initializer_list参数匹配，即便其他构造函数看起来是更好的选择
- 对于数值类型的std::vector来说使用花括号初始化和圆括号初始化会造成巨大的不同
- 在模板类选择使用圆括号初始化或使用花括号初始化创建对象是一个挑战。
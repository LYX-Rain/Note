# 设计模式

- [设计模式](#设计模式)
  - [正交四原则和SOLID原则](#正交四原则和solid原则)
    - [正交四原则](#正交四原则)
    - [SOLID 原则](#solid-原则)
  - [创建型模式](#创建型模式)
    - [工厂方法模式](#工厂方法模式)
    - [抽象工厂模式](#抽象工厂模式)
    - [生成器](#生成器)
    - [原型](#原型)
    - [单例](#单例)
  - [结构型模式](#结构型模式)
    - [适配器](#适配器)
    - [桥接](#桥接)
      - [举例](#举例)
    - [装饰器](#装饰器)
    - [组合](#组合)
    - [外观](#外观)
    - [代理](#代理)
  - [行为模式](#行为模式)
    - [责任链](#责任链)
    - [观察者](#观察者)
    - [访问者](#访问者)
    - [中介者](#中介者)
    - [策略模式](#策略模式)

## 正交四原则和SOLID原则

### 正交四原则

1. 最小化重复：当重复的代码需要修改时，容易出现漏改的情况
2. 分离变化：**识别变化方向并对变化预留扩展接口**。而这个扩展接口也必需反映这个变化方向的本质特点（稳定接口）
3. 缩小依赖范围：最小化知识原则；依赖接口，不要依赖实现
4. 向稳定方向依赖：定义 API 的时候应该关注 What，而不是 How

### SOLID 原则

- 单一职责：一个类，引起它变化的原因只有一个。如果一个变化导致多处修改，则存在重复
  - 这个原则意味着一个类只能有一个职责并且只完成为它设计的功能任务。
  - 否则，如果我们的类承担的职责多于一个，那么我们的代码就具有高度的耦合性，并会导致它对于任何改变都很脆弱。
- 开闭原则：对扩展开放，对修改关闭。多个变化导致一处修改，则对变化的识别不准
- 里氏替换原则：程序里的对象都应该可以被它的子类实例替换而不用更改程序.
  - 基类设定一系列的规范和契约，子类需要遵守
- 接口分离原则：多个专用的接口比一个通用接口好。
  - 这个原则定义了一个类绝不要实现不会用到的接口。
  - 不遵循这个原则意味着在我们在实现里会依赖很多我们并不需要的方法，但又不得不去定义。
- 依赖倒置原则：接口为稳定的契约，双方都依赖于抽象，不依赖于具体实现；上层定义接口，下层实现接口
  - 一个特定的类不应该直接依赖于另外一个类，但是可以依赖于这个类的抽象（接口）。

## 创建型模式

### 工厂方法模式

在父类中提供一个创建对象的方法， 允许子类决定实例化对象的类型。

使用特殊的工厂方法代替对于对象构造函数的直接调用 （即使用 new运算符）。 对象仍将通过 new 运算符创建，只是该运算符改在工厂方法中调用罢了。 工厂方法返回的对象通常被称作 “产品”。

在子类中重写工厂方法， 从而改变其创建产品的类型。

意图：定义一个创建对象的接口，让其子类自己决定实例化哪一个工厂类，工厂模式使其创建过程延迟到子类进行。

主要解决：主要解决接口选择的问题。

何时使用：我们明确地计划不同条件下创建不同实例时。

如何解决：让其子类实现工厂接口，返回的也是一个抽象的产品。

```python
class Application is
    field dialog: Dialog

    // 程序根据当前配置或环境设定选择创建者的类型。
    method initialize() is
        config = readApplicationConfigFile()

        if (config.OS == "Windows") then
            dialog = new WindowsDialog()
        else if (config.OS == "Web") then
            dialog = new WebDialog()
        else
            throw new Exception("错误！未知的操作系统。")

    // 当前客户端代码会与具体创建者的实例进行交互，但是必须通过其基本接口
    // 进行。只要客户端通过基本接口与创建者进行交互，你就可将任何创建者子
    // 类传递给客户端。
    method main() is
        this.initialize()
        dialog.render()
```

### 抽象工厂模式

意图：提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。

主要解决：主要解决接口选择的问题。

何时使用：系统的产品有多于一个的产品族，而系统只消费其中某一族的产品。

如何解决：在一个产品族里面，定义多个产品。

### 生成器

### 原型

### 单例

## 结构型模式

### 适配器

适配器模式（Adapter Pattern）是作为两个不兼容的接口之间的桥梁。这种类型的设计模式属于结构型模式，它结合了两个独立接口的功能。

这种模式涉及到一个单一的类，该类负责加入独立的或不兼容的接口功能。举个真实的例子，读卡器是作为内存卡和笔记本之间的适配器。将内存卡插入读卡器，再将读卡器插入笔记本，这样就可以通过笔记本来读取内存卡。

意图：将一个类的接口转换成客户希望的另外一个接口。适配器模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。

主要解决：主要解决在软件系统中，常常要将一些"现存的对象"放到新的环境中，而新环境要求的接口是现对象不能满足的。

何时使用： 1、系统需要使用现有的类，而此类的接口不符合系统的需要。 2、想要建立一个可以重复使用的类，用于与一些彼此之间没有太大关联的一些类，包括一些可能在将来引进的类一起工作，这些源类不一定有一致的接口。 3、通过接口转换，将一个类插入另一个类系中。（比如老虎和飞禽，现在多了一个飞虎，在不增加实体的需求下，增加一个适配器，在里面包容一个虎对象，实现飞的接口。）

如何解决：继承或依赖（推荐）。

### 桥接

桥接（Bridge）是用于把抽象化与实现化解耦，使得二者可以独立变化。这种类型的设计模式属于结构型模式，它通过提供抽象化和实现化之间的桥接结构，来实现二者的解耦。

这种模式涉及到一个作为桥接的接口，使得实体类的功能独立于接口实现类，这两种类型的类可被结构化改变而互不影响。

桥接模式的目的是将抽象与实现分离，使它们可以独立地变化，该模式通过将一个对象的抽象部分与它的实现部分分离，使它们可以独立地改变。它通过组合的方式，而不是继承的方式，将抽象和实现的部分连接起来。

意图：将抽象部分与实现部分分离，使它们都可以独立的变化。

主要解决：在有多种可能会变化的情况下，用继承会造成类爆炸问题，扩展起来不灵活。

何时使用：实现系统可能有多个角度分类，每一种角度都可能变化。

如何解决：把这种多角度分类分离出来，让它们独立变化，减少它们之间耦合。

如果你想要拆分或重组一个具有多重功能的庞杂类 （例如能与多个数据库服务器进行交互的类）， 可以使用桥接模式。
如果你希望在几个独立维度上扩展一个类， 可使用该模式
如果你需要在运行时切换不同实现方法， 可使用桥接模式。

#### 举例

假如你有一个几何 形状Shape类， 从它能扩展出两个子类： ​ 圆形Circle和 方形Square 。 你希望对这样的类层次结构进行扩展以使其包含颜色， 所以你打算创建名为 红色Red和 蓝色Blue的形状子类。 但是， 由于你已有两个子类， 所以总共需要创建四个类才能覆盖所有组合， 例如 蓝色圆形Blue­Circle和 红色方形Red­Square 。

![](https://refactoringguru.cn/images/patterns/diagrams/bridge/problem-zh.png)

在层次结构中新增形状和颜色将导致代码复杂程度指数增长。 例如添加三角形状， 你需要新增两个子类， 也就是每种颜色一个； 此后新增一种新颜色需要新增三个子类， 即每种形状一个。 如此以往， 情况会越来越糟糕。

解决方案

问题的根本原因是我们试图在两个独立的维度——形状与颜色——上扩展形状类。 这在处理类继承时是很常见的问题。

桥接模式通过**将继承改为组合**的方式来解决这个问题。 具体来说， 就是抽取其中一个维度并使之成为独立的类层次， 这样就可以在初始类中引用这个新层次的对象， 从而使得一个类不必拥有所有的状态和行为。

![](https://refactoringguru.cn/images/patterns/diagrams/bridge/solution-zh.png)

根据该方法， 我们可以将颜色相关的代码抽取到拥有 红色和 蓝色两个子类的颜色类中， 然后在 形状类中添加一个指向某一颜色对象的引用成员变量。 现在， 形状类可以将所有与颜色相关的工作委派给连入的颜色对象。 这样的引用就成为了 形状和 颜色之间的桥梁。 此后， 新增颜色将不再需要修改形状的类层次， 反之亦然。

### 装饰器

装饰器模式（Decorator Pattern）允许向一个现有的对象添加新的功能，同时又不改变其结构。这种类型的设计模式属于结构型模式，它是作为现有的类的一个包装。

装饰器模式通过将对象包装在装饰器类中，以便动态地修改其行为。

这种模式创建了一个装饰类，用来包装原有的类，并在保持类方法签名完整性的前提下，提供了额外的功能。

意图：动态地给一个对象添加一些额外的职责。就增加功能来说，装饰器模式相比生成子类更为灵活。

主要解决：一般的，我们为了扩展一个类经常使用继承方式实现，由于继承为类引入静态特征，并且随着扩展功能的增多，子类会很膨胀。

何时使用：在不想增加很多子类的情况下扩展类。

如何解决：将具体功能职责划分，同时继承装饰者模式。

### 组合

### 外观

### 代理

在代理模式（Proxy Pattern）中，一个类代表另一个类的功能。这种类型的设计模式属于结构型模式。

在代理模式中，我们创建具有现有对象的对象，以便向外界提供功能接口。

意图：为其他对象提供一种代理以控制对这个对象的访问。

主要解决：在直接访问对象时带来的问题，比如说：要访问的对象在远程的机器上。在面向对象系统中，有些对象由于某些原因（比如对象创建开销很大，或者某些操作需要安全控制，或者需要进程外的访问），直接访问会给使用者或者系统结构带来很多麻烦，我们可以在访问此对象时加上一个对此对象的访问层。

何时使用：想在访问一个类时做一些控制。

如何解决：增加中间层。

## 行为模式

### 责任链

### 观察者

观察者模式是一种行为型设计模式，它定义了一种一对多的依赖关系，当一个对象的状态发生改变时，其所有依赖者都会收到通知并自动更新。

当对象间存在一对多关系时，则使用观察者模式（Observer Pattern）。比如，当一个对象被修改时，则会自动通知依赖它的对象。观察者模式属于行为型模式。

意图：定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。

主要解决：一个对象状态改变给其他对象通知的问题，而且要考虑到易用和低耦合，保证高度的协作。

何时使用：一个对象（目标对象）的状态发生改变，所有的依赖对象（观察者对象）都将得到通知，进行广播通知。

如何解决：使用面向对象技术，可以将这种依赖关系弱化。

### 访问者

### 中介者

### 策略模式

在策略模式（Strategy Pattern）中一个类的行为或其算法可以在运行时更改。这种类型的设计模式属于行为型模式。

在策略模式定义了一系列算法或策略，并将每个算法封装在独立的类中，使得它们可以互相替换。通过使用策略模式，可以在运行时根据需要选择不同的算法，而不需要修改客户端代码。

意图：定义一系列的算法,把它们一个个封装起来, 并且使它们可相互替换。

主要解决：在有多种算法相似的情况下，使用 if...else 所带来的复杂和难以维护。

何时使用：一个系统有许多许多类，而区分它们的只是他们直接的行为。

如何解决：将这些算法封装成一个一个的类，任意地替换。

关键代码：实现同一个接口。
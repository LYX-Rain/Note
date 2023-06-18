## 命名系统

```python
lower_underscore = 0    # 变量、函数和 module
UPPER_UNDERSCORE = 1    # 命名常量
CamelCase = 2           # 命名类
mixedCase = 3           # 不使用
```

### 下划线

单下划线表示占位符，语法上有一个变量，但该变量没有用

```python
for _ in range(10):
    print(random.random())
```

一个前置下划线表示“弱私有”，它在语义上尝试表达 private 性质，但也可强行使用
实际对程序的运行也有影响，使用 form xxx import * 时，并不会 import 单下划线开头的全局变量

```python
class MyClass:
    def _get_raw(self):
        print("Hello")

o = MyClass()
o._get_raw()    # Hello        
```

在 python 的类定义里，两个下划线开头表示“强私有”，无法在该 class 之外访问强私有的内容
但 python 这部分的实现防君子不防小人，它实际上是在类定义里对双下划线开头的变量进行了 name mumbling，也就是偷偷的将该变量改名，将该变量名前增加了一个下划线 calss 名

```python
class MyClass:
    def __init__(self):
        self.__secret = 0
    def __get_raw(self):
        print("Hello")

o = MyClass()
o.__get_raw()               # error        
print(o.__secret)           # error
print(o._MyClass__secret)   # 0
```

前后都有两个下划线叫做 dunderscore，专门表示 python 中的魔术方法（magic method）
不要定义这种形式的方法

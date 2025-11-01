# 哈希中我的错误

- value+=(int)singleword;第一次自己写的时候没有考虑到word中的顺序问题，询问ai后改进，我的改进方法是乘单词所在的位置，然后我询问ai有没有更优化的方法，从而我了解到了

### 更稳健的哈希函数（推荐的乘法滚动哈希）

在哈希表中，我们通常使用一种**滚动哈希** (Rolling Hash) 的方式，它能更均匀地分布哈希值，并且保证每个字符的贡献都与其位置密切相关。

**推荐的实现（最常见的改进）：**

codeC

`unsigned int hash(const char *word) { unsigned long hash_value = 5381; // 初始值通常是一个非零的质数，如 5381

```
for (int i = 0; word[i] != '\\0'; i++)
{
    // 1. 获取小写字符
    char c = tolower(word[i]);
    
    // 2. 滚动哈希：将当前哈希值“左移”或乘以一个质数，然后加上新字符
    // 这是 DJB2 算法的简洁形式，性能和散列效果都很好
    hash_value = ((hash_value << 5) + hash_value) + c; 
}

// 3. 对桶的数量 N 取模
return hash_value % N; 
```

}`

- 对于 unsigned int

我之前只知道它代表了无符号整型，不知道具体有什么用，也基本不用，这次我通过lab2知道了（问了ai）

**如果使用 int (有符号整数)：**

- int 通常是 32 位有符号整数。它可以存储一个非常大的正数（大约到 21 亿）。
- **风险：** 虽然您的 hash 函数的结果是 hash_value % N，通常会很小（小于 N），但在理论上，如果 hash 函数返回一个超过 INT_MAX 的值（虽然您用 unsigned long 解决了），或者最重要的是，如果 N 的值超过 INT_MAX 的一半（极不可能），它可能导致**隐式类型转换**和**符号错误**。
- **最大风险：** 当您将一个 unsigned int 赋值给一个 int 时，如果原值超过 INT_MAX，将发生溢出，并可能变成一个负数。虽然在这个特定的 hash 场景下，结果通常在 [0, N-1] 范围内且 N 很小，但遵循类型一致性是最佳实践。

**如果使用 unsigned int (无符号整数)：**

- 这是最佳实践，因为它与 hash 函数的**返回类型完全一致**。
- 它消除了任何潜在的类型转换警告或运行时意想不到的行为。
- 在写哈希代码中解决的疑惑

在 C 语言中，函数原型或定义中括号里的 void 表示这个函数**不接受任何参数**

- 为什么 size() 使用 void？
  - size() 函数的作用是返回已加载的单词总数。
  - 这个计数是一个**全局状态**，它不需要依赖任何传入的特定参数就能计算或获取。
  - 因此，为了清晰地表明它是一个**无参数**的函数，标准 C 编程实践要求在括号内使用 void。

我之前认为load要在check前面

从**逻辑依赖关系**来看，您是对的：check 函数依赖于 load 函数来填充哈希表，所以从程序执行顺序上看，load 必须在 check 之前调用。

但是，在 C 语言的**模块化编程**中，**函数的定义顺序并不重要**，只要它们的原型（函数签名）在头文件 (dictionary.h) 中声明了即可。

### 为什么 check 可以写在 load 前面？

1. C 语言的编译机制：
   - C 语言的编译器在处理 dictionary.c 时，会先看到 #include "dictionary.h"。
   - dictionary.h 中包含了所有函数的**原型** （例如 bool check(const char *word); 和 bool load(const char *dictionary); ）。
   - **原型**告诉编译器：“有一个名为 load 的函数，它接受一个 const char* 并返回 bool”。
   - 有了原型，编译器就知道如何正确地处理对这些函数的**调用**，而**不需要知道函数的具体实现代码在哪里**。
2. speller.c 的调用顺序：
   - 在 speller.c 中，确实是先调用了 load()，然后才在循环中调用 check()。主程序保证了执行顺序。
3. dictionary.c 中的函数顺序：
   - 在 dictionary.c 中，check 函数的实现代码可以放在 load 函数的实现代码前面，编译器会分别编译它们。在链接阶段，链接器会将 speller.c 对 load 和 check 的调用与 dictionary.c 中它们的实际实现代码连接起来。







最后以下是我的代码的测试结果

![](C:\Users\wbyqj\Pictures\Screenshots\屏幕截图 2025-11-01 192423.png)
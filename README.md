# speller

一个 C 语言拼写检查器作业（源自 CS50 Pset5 的精简版），使用 CMake 构建。

## 作业要做什么？

你需要在 `dictionary.c` 中完成字典模块的 5 个函数，使得主程序 `speller.c` 能够：

- load(dictionary)：加载词典文件到内存数据结构。
- check(word)：判断单词是否在词典中（大小写不敏感，允许撇号 `'`）。
- hash(word)：把单词映射到 [0, N) 的桶索引。
- size(void)：返回已加载的单词总数。
- unload(void)：释放所有动态内存。

我们已给出一个基于“哈希表 + 链地址法”的骨架：

- 结构体 `node { char word[LENGTH + 1]; struct node* next; }` 已定义。
- 你可以修改桶的数量 `#define N ...`（`dictionary.c` 顶部），以平衡时间与空间。
- 允许你自由设计更好的 `hash` 实现，但请保持函数签名不变，并确保返回值在 `[0, N)`。

程序输入输出说明：

- 运行 `speller` 时，主程序会扫描文本文件中的“单词”，并输出所有拼写错误（不在词典中的单词）。
- 统计信息（load/check/size/unload 用时）会在程序末尾打印，方便你评估性能。
- 文本解析规则已在 `speller.c` 中实现：只把字母和内部撇号 `'` 视为单词，含数字的串会被整体跳过，超过 `LENGTH=45` 的超长“词”会被跳过。

目录说明：

- `dictionaries/` 提供了 `small` 与 `large` 两个词典（每行一个小写单词）。
- `texts/` 是待检查的文本。
- `keys/` 是“标准输出”（期望的拼写错误列表），可用来对拍你的输出。

实现建议：

- 先写一个可用的 `hash` 并选择合理的 `N`（保证散列尽量均匀）。
- 完成 `load`/`size`：加载词典并统计单词总数。
- 完成 `check`：按与 `hash` 一致的规则查找（大小写不敏感）。
- 完成 `unload`：释放全部动态内存。

常见注意点：

- 比较时大小写要统一（例如把字符用 `tolower` 正规化再比较）。
- 单词可能包含内部撇号（如 `can't`）。
- 请不要修改 `dictionary.h` 的函数原型，也不要改动 `speller.c`（除非你在本地调试打印）。

完成度与评分建议（供参考）：

- 功能正确：能在 `dictionaries/large` + 各种 `texts/` 上输出与 `keys/` 一致的结果。
- 性能与可扩展：`hash` 分布较均匀，`N` 合理，`check` 总耗时可接受。
- 代码质量：清晰、注释合理、无未定义行为和内存泄漏。

如何自测（对拍输出）：

```sh
# 生成你的输出并保存到文件
./build/speller texts/austen.txt > my_out.txt

# 与标准答案对比（无输出代表完全一致）
diff -u my_out.txt keys/austen.txt
```

> 现在仓库中的 `dictionary.c` 未实现，直接运行会提示“Could not load ...”。请先完成 `dictionary.c` 再进行对拍与性能测试。

## 构建（Build）

使用 CMake（推荐）：

```sh
# 在仓库根目录 speller 下执行
cmake -S . -B build
cmake --build build --config Release
```

生成的可执行文件位于 `build/speller`（Windows 使用 MSVC 时可能在 `build/Release/speller.exe`）。

如偏好 Unix 下的 Make，可自行使用，但为了跨平台一致性更推荐 CMake。

### Windows（MSVC）工具链安装与构建

> 使用 Visual Studio IDE：直接在 VS 中通过 File > Open > Folder 打开本仓库根目录（包含 `CMakeLists.txt`），VS 会自动配置（Configure）并生成缓存；在工具栏选择 `x64-Release` 后即可 Build/Run。下方命令行步骤主要面向“开发者命令行/CI”或不使用 VS IDE 的情况。

1) 安装工具链（二选一）：

- Visual Studio 2022（Community 版即可），勾选“使用 C++ 的桌面开发”工作负载，确保包含 CMake 工具与 Windows SDK。
- 或仅安装 Visual Studio Build Tools 2022，并勾选 MSVC、Windows 10/11 SDK、C++ CMake 工具。

2) 打开开发者环境：

- 从开始菜单打开“x64 Native Tools Command Prompt for VS 2022”（或相应版本）。该环境会自动配置 `cl`、`cmake` 等路径。

3) 生成与构建（两种常见方式）：

- 使用 Visual Studio 生成器（多配置）：

```bat
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

- 使用 Ninja + MSVC（单配置）：

```bat
cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

4) 运行：

- 可执行文件通常位于 `build/Release/speller.exe`（VS 生成器）或 `build/speller.exe`（Ninja 单配置）。

5) 常见问题排查：

- CMake 报“未找到 C 编译器/找不到 cl”：请确认是在“x64 Native Tools Command Prompt”中执行；若在 PowerShell，可先运行 `VsDevCmd.bat` 初始化环境。
- 生成器名称与 VS 版本对应，如不确定可执行 `cmake -G` 查看可用生成器。
- 路径包含空格时请加引号；推荐在工程根目录执行上述命令。

## 运行（Run）

```sh
# 使用默认词典（dictionaries/large）
./build/speller texts/lalaland.txt

# 指定词典
./build/speller dictionaries/small texts/cat.txt
```



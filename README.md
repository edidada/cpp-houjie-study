# cpp-houjie-study

侯捷 C++ 系列课程的学习仓库。

**重点不是收集资料，而是把思路理顺**：先搞清楚「这门课到底难在哪、该按什么顺序学」，
再用现代 C++（C++17）把课件里的例子重新写一遍，用编译器和 CTest 逼自己把
「看懂」变成「写对」。资料存一堆、脑子还是空的，是最常见的结局。

> 说明：文中一律作「侯捷」（输入法常误作「侯姐」）。

## 一句话结论

侯捷难，不是因为语法多，而是因为他把提问的层次从「这个 API 怎么用」换成了
「这套机制为什么必须这样设计」：对象在内存里怎么摆、STL 源码为什么这么写、
模板在编译期到底算了什么。完整拆解见
[docs/02-为什么侯捷难.md](docs/02-为什么侯捷难.md)。

## 目录

| 路径 | 作用 |
| --- | --- |
| `docs/` | 学习路线、难点分析、源码阅读方法、仓库结构说明（自己写的笔记） |
| `src/` | 按课程阶段重写的 C++17 示例，每个例子一个可执行程序 + CTest |
| `third_party/` | 以 `git submodule` 挂载的侯捷资料仓库（视频 / PPT / 源码 / 笔记） |
| `.github/workflows/cmake.yml` | GitHub Actions：cmake 配置 → 编译 → ctest |

## 快速开始

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

子模块不参与构建（里面是几百 MB 的视频/PPT，编译用不到），想看资料时再拉：

```bash
git submodule update --init --depth 1
```

## 学习顺序（详见 [docs/01](docs/01-学习路线图.md)）

1. C++ 面向对象高级编程（上）—— `Complex` / `String`，把「类」写对
2. C++ 面向对象高级编程（下）· 对象模型 —— vptr/vtbl、this、构造析构顺序、模板
3. STL 标准库与泛型编程 —— 容器、迭代器、算法、traits、适配器
4. C++11/14 新标准
5. 内存管理机制 —— `new`/`delete`、allocator、内存池
6. C++ Startup（程序的生前死后）
7. 设计模式

主线只有一条：**数据放在哪 → 谁负责生死 → 怎么抽象成类型 → 怎么复用而不重复**。

## 资料来源（均已 fork 到 edidada 后作为子模块挂载）

| 子模块 | 上游 | 内容 |
| --- | --- | --- |
| `third_party/bilibili-plus` | `ZachL1/Bilibili-plus` | 侯捷全系列视频、PPT、源代码 |
| `third_party/houjie-course` | `TaoLu52/-C-HouJie` | 侯捷 C++ 系列课程资料 |
| `third_party/houjie-notes` | `smzztx/HoujieCppNotes` | 侯捷 C++ 视频学习笔记（Markdown） |

> `TaoLu52/-C-HouJie` 与 `ZachL1/Bilibili-plus` 属同一 fork 网络，
> GitHub 限制单账号每网络只能有一个同名 fork，故用 `--fork-name` 改名另建
> `edidada/houjie-course` 保留独立路径。详见 [docs/04](docs/04-仓库结构与构建.md)。

## 文档索引

- [01 · 学习路线图](docs/01-学习路线图.md)
- [02 · 为什么侯捷难](docs/02-为什么侯捷难.md) ← 重点
- [03 · 源码阅读与笔记方法](docs/03-源码阅读与笔记方法.md)
- [04 · 仓库结构与构建](docs/04-仓库结构与构建.md)

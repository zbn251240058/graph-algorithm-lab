# Graph Algorithm Lab

一个基于 C++17 实现的图论与图算法学习项目。

本项目用于整理《图论与算法》课程中学习的各种图数据结构和算法。
项目采用模块化设计，所有图算法尽量基于统一的 `Graph` 类实现，
逐步构建一个属于自己的 Graph Algorithm Library。

---

## 1. 项目目标

本项目主要有以下几个目标：

- 掌握图的数据结构设计
- 熟悉 C++ 面向对象编程
- 实现常见图论算法
- 将不同算法模块化组织
- 建立统一的 Graph 接口
- 通过测试代码验证算法正确性
- 逐步形成一个完整的图算法库

---

## 2. 项目结构

```text
graph-algorithm-lab/
│
├── src/
│   │
│   ├── graph/
│   │   ├── Edge.h
│   │   └── Graph.h
│   │
│   ├── graph_operation/
│   │   ├── subgraph.h
│   │   └── set_operation.h
│   │
│   ├── traverse/
│   │   ├── dfs.h
│   │   └── bfs.h
│   │
│   ├── connectivity/
│       ├── connected.h
│       └── cut.h
|
│
├── test/
│   └── test.cpp
│
├── README.md
└── .gitignore
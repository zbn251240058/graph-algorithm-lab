# Graph‑Algorithm‑Lab
图算法课程实验，实现常见图论算法。

## 已实现算法
- 图存储：邻接表
- 遍历：BFS、DFS
- 最短路径：Dijkstra、Floyd‑Warshall
- 最小生成树：Prim、Kruskal
- 拓扑排序

## 运行环境
Python 3.8+

## 运行测试
```bash
python test/test_graph.py
```


## 项目结构
```
├── src/        # 算法源码
├── test/       # 测试用例
├── README.md
├── .gitignore
└── LICENSE
```

## 算法复杂度

表格

| BFS | \(O(V+E)\) |
| --- | --- |
| DFS | \(O(V+E)\) |
| Dijkstra (堆优化) | \(O(E\log V)\) |
| Floyd | \(O(V^3)\) |
| Kruskal | \(O(E\log E)\) |
| Prim | \(O(E\log V)\) |

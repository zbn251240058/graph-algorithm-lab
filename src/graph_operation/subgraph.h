#ifndef GRAPH_SUBGRAPH_H
#define GRAPH_SUBGRAPH_H

#include "../graph/Graph.h"

// ============================================================
// 点诱导子图
// ============================================================

inline Graph vertexInducedSubgraph(
    const Graph &g,
    const std::vector<int> &vertices)
{
    Graph result;

    std::unordered_map<int, bool> selected;

    // 添加顶点
    for (int label : vertices)
    {
        if (!g.hasVertex(label))
        {
            throw std::out_of_range(
                "vertex does not exist");
        }

        if (!selected[label])
        {
            selected[label] = true;
            result.addVertex(label);
        }
    }

    // 保留两个端点都被选中的边
    for (const Edge &e : g.edges())
    {
        if (!e.active)
            continue;

        int u = g.labelOf(e.from);
        int v = g.labelOf(e.to);

        if (selected[u] && selected[v])
        {
            result.addEdge(u, v);
        }
    }

    return result;
}

// ============================================================
// 边导出子图
// ============================================================

inline Graph edgeInducedSubgraph(
    const Graph &g,
    const std::vector<int> &edgeIds)
{
    Graph result;

    // 边导出子图中保留原图所有顶点
    for (int v : g.vertices())
    {
        result.addVertex(v);
    }

    for (int edgeId : edgeIds)
    {
        const Edge &e = g.getEdge(edgeId);

        int u = g.labelOf(e.from);
        int v = g.labelOf(e.to);

        result.addEdge(u, v);
    }

    return result;
}

#endif
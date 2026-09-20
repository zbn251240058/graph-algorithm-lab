#ifndef GRAPH_SET_OPERATION_H
#define GRAPH_SET_OPERATION_H

#include "../graph/Graph.h"
#include <stdexcept>

// ============================================================
// 图并
//
// V = V1 ∪ V2
// E = E1 ∪ E2
// ============================================================

inline Graph graphUnion(
    const Graph &g1,
    const Graph &g2)
{
    Graph result;

    // 加入 g1 的所有顶点
    for (int v : g1.vertices())
    {
        result.addVertex(v);
    }

    // 加入 g2 的所有顶点
    for (int v : g2.vertices())
    {
        result.addVertex(v);
    }

    // 加入 g1 的边
    for (const Edge &e : g1.edges())
    {
        if (!e.active)
            continue;

        int u = g1.labelOf(e.from);
        int v = g1.labelOf(e.to);

        result.addEdge(u, v);
    }

    // 加入 g2 的边
    for (const Edge &e : g2.edges())
    {
        if (!e.active)
            continue;

        int u = g2.labelOf(e.from);
        int v = g2.labelOf(e.to);

        result.addEdge(u, v);
    }

    return result;
}

// ============================================================
// 图交
//
// V = V1 ∩ V2
// E = E1 ∩ E2
// ============================================================

inline Graph graphIntersection(
    const Graph &g1,
    const Graph &g2)
{
    Graph result;

    // 交集顶点
    for (int v : g1.vertices())
    {
        if (g2.hasVertex(v))
        {
            result.addVertex(v);
        }
    }

    // 交集边
    for (const Edge &e : g1.edges())
    {
        if (!e.active)
            continue;

        int u = g1.labelOf(e.from);
        int v = g1.labelOf(e.to);

        if (result.hasVertex(u) &&
            result.hasVertex(v) &&
            g2.hasEdge(u, v))
        {
            result.addEdge(u, v);
        }
    }

    return result;
}

// ============================================================
// 补图
//
// 只针对无向简单图
// ============================================================

inline Graph graphComplement(
    const Graph &g)
{
    Graph result;

    std::vector<int> vertices = g.vertices();

    // 保留全部顶点
    for (int v : vertices)
    {
        result.addVertex(v);
    }

    // 任意两个不同顶点
    // 如果原图没有边，则补图有边
    for (int i = 0;
         i < static_cast<int>(vertices.size());
         ++i)
    {
        for (int j = i + 1;
             j < static_cast<int>(vertices.size());
             ++j)
        {
            int u = vertices[i];
            int v = vertices[j];

            if (!g.hasEdge(u, v))
            {
                result.addEdge(u, v);
            }
        }
    }

    return result;
}

// ============================================================
// 图联
//
// G1 ∨ G2
//
// 要求两个图的顶点编号不相交。
// 首先取不交并，然后把 G1 与 G2 的所有点两两连接。
// ============================================================

inline Graph graphJoin(
    const Graph &g1,
    const Graph &g2)
{
    Graph result;

    std::vector<int> v1 = g1.vertices();
    std::vector<int> v2 = g2.vertices();

    // 检查顶点编号是否冲突
    for (int u : v1)
    {
        if (g2.hasVertex(u))
        {
            throw std::invalid_argument(
                "graph join requires disjoint vertex labels");
        }
    }

    // 加入两个图的顶点
    for (int v : v1)
    {
        result.addVertex(v);
    }

    for (int v : v2)
    {
        result.addVertex(v);
    }

    // 加入 G1 的边
    for (const Edge &e : g1.edges())
    {
        if (!e.active)
            continue;

        result.addEdge(
            g1.labelOf(e.from),
            g1.labelOf(e.to));
    }

    // 加入 G2 的边
    for (const Edge &e : g2.edges())
    {
        if (!e.active)
            continue;

        result.addEdge(
            g2.labelOf(e.from),
            g2.labelOf(e.to));
    }

    // G1 与 G2 之间全部连边
    for (int u : v1)
    {
        for (int v : v2)
        {
            result.addEdge(u, v);
        }
    }

    return result;
}

#endif
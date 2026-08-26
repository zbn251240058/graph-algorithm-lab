#include "graph_op.h"
#include <algorithm>

// 点导出子图
Graph vertexInducedSubgraph(const Graph &g, const std::vector<int> &S)
{
    Graph res;
    // 添加全部S内顶点
    for (size_t i = 0; i < S.size(); ++i)
        res.addVertex();

    // 建立映射：原图顶点 -> 新图顶点id
    std::vector<int> old2new(g.vertexCount(), -1);
    for (size_t newId = 0; newId < S.size(); newId++)
    {
        int oldV = S[newId];
        old2new[oldV] = static_cast<int>(newId);
    }

    // 遍历S中每对点，原图存在边则新图加边
    for (size_t i = 0; i < S.size(); i++)
    {
        int u_old = S[i];
        for (size_t j = i + 1; j < S.size(); j++)
        {
            int v_old = S[j];
            if (g.visitEdge(u_old, v_old))
            {
                int u_new = old2new[u_old];
                int v_new = old2new[v_old];
                res.addEdge(u_new, v_new);
            }
        }
    }
    return res;
}

// 边导出子图
Graph edgeInducedSubgraph(const Graph &g, const std::vector<std::pair<int, int>> &edgeSet)
{
    Graph res;
    std::vector<bool> used(g.vertexCount(), false);
    std::vector<int> old2new(g.vertexCount(), -1);

    // 收集所有出现过的顶点
    for (auto &e : edgeSet)
    {
        int u = e.first;
        int v = e.second;
        used[u] = true;
        used[v] = true;
    }

    // 分配新id
    for (int v = 0; v < g.vertexCount(); v++)
    {
        if (used[v])
        {
            old2new[v] = res.vertexCount();
            res.addVertex();
        }
    }

    // 添加指定边
    for (auto &e : edgeSet)
    {
        int u = e.first;
        int v = e.second;
        int nu = old2new[u];
        int nv = old2new[v];
        res.addEdge(nu, nv);
    }
    return res;
}

// 补图
Graph complementGraph(const Graph &g)
{
    Graph res;
    int n = g.vertexCount();
    for (int i = 0; i < n; i++)
        res.addVertex();

    for (int u = 0; u < n; u++)
    {
        for (int v = u + 1; v < n; v++)
        {
            if (!g.visitEdge(u, v))
            {
                res.addEdge(u, v);
            }
        }
    }
    return res;
}

// 图的并
Graph graphUnion(const Graph &g1, const Graph &g2)
{
    Graph res;
    int maxV = std::max(g1.vertexCount(), g2.vertexCount());
    for (int i = 0; i < maxV; i++)
        res.addVertex();

    for (int u = 0; u < maxV; u++)
    {
        for (int v = u + 1; v < maxV; v++)
        {
            bool e1 = (u < g1.vertexCount() && v < g1.vertexCount()) ? g1.visitEdge(u, v) : false;
            bool e2 = (u < g2.vertexCount() && v < g2.vertexCount()) ? g2.visitEdge(u, v) : false;
            if (e1 || e2)
                res.addEdge(u, v);
        }
    }
    return res;
}

// 图的交
Graph graphIntersection(const Graph &g1, const Graph &g2)
{
    Graph res;
    int minV = std::min(g1.vertexCount(), g2.vertexCount());
    for (int i = 0; i < minV; i++)
        res.addVertex();

    for (int u = 0; u < minV; u++)
    {
        for (int v = u + 1; v < minV; v++)
        {
            if (g1.visitEdge(u, v) && g2.visitEdge(u, v))
            {
                res.addEdge(u, v);
            }
        }
    }
    return res;
}

// 不交并，g2顶点全部偏移 g1.vertexCount()
Graph graphDisjointUnion(const Graph &g1, const Graph &g2)
{
    Graph res;
    // 复制g1
    int n1 = g1.vertexCount();
    int n2 = g2.vertexCount();
    for (int i = 0; i < n1 + n2; i++)
        res.addVertex();

    for (int u = 0; u < n1; u++)
    {
        for (int v = u + 1; v < n1; v++)
        {
            if (g1.visitEdge(u, v))
                res.addEdge(u, v);
        }
    }
    // g2顶点偏移n1
    for (int u = 0; u < n2; u++)
    {
        for (int v = u + 1; v < n2; v++)
        {
            if (g2.visitEdge(u, v))
                res.addEdge(u + n1, v + n1);
        }
    }
    return res;
}

// 联运算 join：不交并基础，g1全部顶点连向g2全部顶点
Graph graphJoin(const Graph &g1, const Graph &g2)
{
    Graph res = graphDisjointUnion(g1, g2);
    int n1 = g1.vertexCount();
    int n2 = g2.vertexCount();
    for (int u = 0; u < n1; u++)
    {
        for (int v = 0; v < n2; v++)
        {
            res.addEdge(u, v + n1);
        }
    }
    return res;
}

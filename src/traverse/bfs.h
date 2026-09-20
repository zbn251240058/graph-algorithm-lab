#ifndef GRAPH_BFS_H
#define GRAPH_BFS_H

#include "../graph/Graph.h"

#include <vector>
#include <queue>
#include <algorithm>

struct BFSResult
{
    std::vector<int> order;

    // 内部编号下的距离
    std::vector<int> distance;

    // 内部编号下的父节点
    std::vector<int> parent;
};

// ============================================================
// BFS
// ============================================================

inline BFSResult BFS(
    const Graph &g,
    int start)
{
    BFSResult result;

    if (!g.hasVertex(start))
    {
        return result;
    }

    int maxIndex = 0;

    for (int v : g.vertices())
    {
        maxIndex =
            std::max(
                maxIndex,
                g.indexOf(v));
    }

    result.distance.assign(
        maxIndex + 1,
        -1);

    result.parent.assign(
        maxIndex + 1,
        -1);

    std::vector<bool> visited(
        maxIndex + 1,
        false);

    std::queue<int> q;

    int s = g.indexOf(start);

    visited[s] = true;
    result.distance[s] = 0;

    q.push(s);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        result.order.push_back(
            g.labelOf(u));

        for (const Edge &e :
             g.neighbors(g.labelOf(u)))
        {
            if (!e.active)
                continue;

            int v = e.to;

            if (!visited[v])
            {
                visited[v] = true;

                result.distance[v] =
                    result.distance[u] + 1;

                result.parent[v] = u;

                q.push(v);
            }
        }
    }

    return result;
}

#endif
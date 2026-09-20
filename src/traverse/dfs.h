#ifndef DFS_H
#define DFS_H

#include <vector>
#include <queue>
#include "src/graph/Graph.h"

// DFS入口
vector<int> DFS(const Graph &g, int start)
{
    vector<bool> visited(g.get_vertex_num() + 1, false);
    vector<int> result;

    dfs(g, start, visited, result);
    return result;
}

void dfs(const Graph &g, int start, vector<bool> &visited, vector<int> &result)
{
    visited[start] = true;
    result.push_back(start);

    for (int v : g.get_neighbors(start))
    {
        if (!visited[v])
        {
            dfs(g, v, visited, result);
        }
    }
}

#endif
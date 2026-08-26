#include "graph_mat.h"
#include <algorithm>

Graph::Graph() {}

void Graph::addVertex()
{
    int n = static_cast<int>(mat.size());
    mat.resize(n + 1, std::vector<int>(n + 1, 0));
    for (int i = 0; i < n; i++)
    {
        mat[i].resize(n + 1, 0);
    }
}

void Graph::addEdge(int u, int v)
{
    int maxId = std::max(u, v);
    while (mat.size() <= static_cast<size_t>(maxId))
    {
        addVertex();
    }
    mat[u][v] = 1;
    mat[v][u] = 1;
}

void Graph::removeVertex(int v)
{
    if (v >= static_cast<int>(mat.size()))
        return;
    mat.erase(mat.begin() + v);
    for (auto &row : mat)
    {
        row.erase(row.begin() + v);
    }
}

void Graph::removeEdge(int u, int v)
{
    if (u >= static_cast<int>(mat.size()) || v >= static_cast<int>(mat.size()))
        return;
    mat[u][v] = 0;
    mat[v][u] = 0;
}

int Graph::visitEdge(int u, int v) const
{
    if (u >= static_cast<int>(mat.size()) || v >= static_cast<int>(mat.size()))
        return 0;
    return mat[u][v];
}

int Graph::degree(int v) const
{
    if (v >= static_cast<int>(mat.size()))
        return 0;
    int cnt = 0;
    for (auto x : mat[v])
    {
        if (x == 1)
            cnt++;
    }
    return cnt;
}

int Graph::vertexCount() const
{
    return static_cast<int>(mat.size());
}

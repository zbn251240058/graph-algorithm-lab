#include <iostream>
#include <vector>

using namespace std;

class Graph
{
private:
    vector<vector<int>> adj;

public:
    Graph() {}

    void addVertex()
    {
        adj.push_back(vector<int>());
    }

    void addEdge(int u, int v)
    {
        int maxId = max(u, v);
        while (adj.size() <= maxId)
        {
            addVertex();
        }
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void deleteEdge(int u, int v)
    {
        if (u >= adj.size() || v >= adj.size())
            return;
        auto &vecU = adj[u];
        auto &vecV = adj[v];
        vecU.erase(remove(vecU.begin(), vecU.end(), v), vecU.end());
        vecV.erase(remove(vecV.begin(), vecV.end(), u), vecV.end());
    }

    int visitEdge(int u, int v)
    {
        if (u >= adj.size() || v >= adj.size())
            return 0;
        for (auto x : adj[u])
        {
            if (x == v)
                return x;
        }
        return 0;
    }

    int degree(int v)
    {
        if (v >= adj.size())
            return 0;
        return adj[v].size();
    }
};

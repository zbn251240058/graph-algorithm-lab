#include <iostream>
#include <vector>

using namespace std;

class Graph
{
private:
    vector<vector<int>> mat;

public:
    Graph() {}

    void addVertex()
    {
        int n = mat.size();
        // 矩阵扩容
        mat.resize(n + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < n; i++)
        {
            mat[i].resize(n + 1, 0);
        }
    }

    void addEdge(int u, int v)
    {
        int maxId = max(u, v);
        // 如果顶点编号超出当前矩阵，自动扩容
        while (mat.size() <= maxId)
        {
            addVertex();
        }
        mat[u][v] = 1;
        mat[v][u] = 1;
    }

    int visitEdge(int u, int v)
    {
        if (u >= mat.size() || v >= mat.size())
            return 0;
        return mat[u][v];
    }

    int degree(int v)
    {
        if (v >= mat.size())
            return 0;
        int cnt = 0;
        for (auto x : mat[v])
        {
            if (x == 1)
                cnt++;
        }
        return cnt;
    }
};

struct node
{
    int id;
    node *next;
};

class graphadj
{
private:
    vector<node *> adj;

public:
    graphadj() {}

    void addVertex()
    {
        adj.push_back(nullptr);
    }

    void addEdge(int u, int v)
    {
        int maxId = max(u, v);
        while (adj.size() <= maxId)
        {
            addVertex();
        }
        node *newNodeU = new node{v, adj[u]};
        adj[u] = newNodeU;

        node *newNodeV = new node{u, adj[v]};
        adj[v] = newNodeV;
    }

    int visitEdge(int u, int v)
    {
        if (u >= adj.size() || v >= adj.size())
            return 0;
        node *curr = adj[u];
        while (curr != nullptr)
        {
            if (curr->id == v)
                return 1;
            curr = curr->next;
        }
        return 0;
    }

    int degree(int v)
    {
        if (v >= adj.size())
            return 0;
        int cnt = 0;
        node *curr = adj[v];
        while (curr != nullptr)
        {
            cnt++;
            curr = curr->next;
        }
        return cnt;
    }
};

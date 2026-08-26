#pragma once
#include <iostream>
#include <vector>

class Graph
{
private:
    std::vector<std::vector<int>> mat;

public:
    Graph();
    void addVertex();
    void addEdge(int u, int v);
    void removeVertex(int v);
    void removeEdge(int u, int v);
    int visitEdge(int u, int v) const;
    int degree(int v) const;
    int vertexCount() const;
};

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include "Edge.h"

class Graph
{
private:
    // ============================================================
    // 顶点编号映射
    // ============================================================

    // 外部编号 -> 内部编号
    std::unordered_map<int, int> labelToIndex;

    // 内部编号 -> 外部编号
    // indexToLabel[0] 不使用
    std::vector<int> indexToLabel;

    // 顶点是否存在
    // active[0] 不使用
    std::vector<bool> active;

    // 当前存在的顶点数量
    int vertexNum;

    // 下一个内部编号
    int nextIndex;

    // ============================================================
    // 边
    // ============================================================

    // 当前有效边数量
    int edgeNum;

    // 边编号从 1 开始
    // edgeList[id - 1] 对应 id
    std::vector<Edge> edgeList;

    // 邻接表
    // adj[u] 中保存所有与 u 关联的 Edge
    std::vector<std::vector<Edge>> adj;

private:
    bool validIndex(int index) const
    {
        return index >= 1 &&
               index < static_cast<int>(active.size()) &&
               active[index];
    }

    bool validLabel(int label) const
    {
        auto it = labelToIndex.find(label);

        if (it == labelToIndex.end())
            return false;

        return validIndex(it->second);
    }

    int getIndex(int label) const
    {
        auto it = labelToIndex.find(label);

        if (it == labelToIndex.end())
        {
            throw std::out_of_range("vertex does not exist");
        }

        if (!validIndex(it->second))
        {
            throw std::out_of_range("vertex has been deleted");
        }

        return it->second;
    }

public:
    // ============================================================
    // 构造
    // ============================================================

    Graph()
        : vertexNum(0),
          nextIndex(1),
          edgeNum(0)
    {
        indexToLabel.push_back(0);
        active.push_back(false);
        adj.resize(1);
    }

    // ============================================================
    // 顶点操作
    // ============================================================

    // 添加指定编号的顶点
    // 成功返回 true
    // 如果编号已经存在，返回 false
    bool addVertex(int label)
    {
        if (labelToIndex.find(label) != labelToIndex.end())
        {
            return false;
        }

        int index = nextIndex++;

        labelToIndex[label] = index;

        indexToLabel.push_back(label);
        active.push_back(true);
        adj.emplace_back();

        ++vertexNum;

        return true;
    }

    // 删除顶点
    // 同时删除所有与它关联的边
    bool removeVertex(int label)
    {
        if (!validLabel(label))
        {
            return false;
        }

        int index = getIndex(label);

        // 删除所有关联边
        for (Edge &e : adj[index])
        {
            if (!e.active)
                continue;

            int edgeId = e.id;

            if (edgeId >= 1 &&
                edgeId <= static_cast<int>(edgeList.size()))
            {
                Edge &original = edgeList[edgeId - 1];

                if (original.active)
                {
                    original.active = false;
                    --edgeNum;
                }
            }
        }

        active[index] = false;
        --vertexNum;

        return true;
    }

    // 判断顶点是否存在
    bool hasVertex(int label) const
    {
        return validLabel(label);
    }

    // 外部编号 -> 内部编号
    int indexOf(int label) const
    {
        return getIndex(label);
    }

    // 内部编号 -> 外部编号
    int labelOf(int index) const
    {
        if (index <= 0 ||
            index >= static_cast<int>(indexToLabel.size()))
        {
            throw std::out_of_range("invalid vertex index");
        }

        return indexToLabel[index];
    }

    // 获取所有当前存在的顶点
    std::vector<int> vertices() const
    {
        std::vector<int> result;

        for (int i = 1;
             i < static_cast<int>(indexToLabel.size());
             ++i)
        {
            if (active[i])
            {
                result.push_back(indexToLabel[i]);
            }
        }

        return result;
    }

    // 顶点数量
    int vertexCount() const
    {
        return vertexNum;
    }

    // 是否为空图
    bool empty() const
    {
        return vertexNum == 0;
    }

    // ============================================================
    // 边操作
    // ============================================================

    // 添加边
    // 返回新边的 Edge ID
    int addEdge(int uLabel, int vLabel)
    {
        int u = getIndex(uLabel);
        int v = getIndex(vLabel);

        // 简单图：禁止重边
        if (hasEdge(uLabel, vLabel))
        {
            return -1;
        }

        int edgeId =
            static_cast<int>(edgeList.size()) + 1;

        Edge original(
            edgeId,
            u,
            v,
            true);

        edgeList.push_back(original);

        // u -> v
        adj[u].emplace_back(
            edgeId,
            u,
            v,
            true);

        // v -> u
        adj[v].emplace_back(
            edgeId,
            v,
            u,
            true);

        ++edgeNum;

        return edgeId;
    }

    // 删除指定 Edge ID 的边
    bool removeEdge(int edgeId)
    {
        if (edgeId < 1 ||
            edgeId > static_cast<int>(edgeList.size()))
        {
            return false;
        }

        Edge &e = edgeList[edgeId - 1];

        if (!e.active)
        {
            return false;
        }

        e.active = false;

        --edgeNum;

        return true;
    }

    // 边数量
    int edgeCount() const
    {
        return edgeNum;
    }

    // 获取指定边
    const Edge &getEdge(int edgeId) const
    {
        if (edgeId < 1 ||
            edgeId > static_cast<int>(edgeList.size()))
        {
            throw std::out_of_range("invalid edge id");
        }

        const Edge &e = edgeList[edgeId - 1];

        if (!e.active)
        {
            throw std::out_of_range("edge has been deleted");
        }

        return e;
    }

    // 所有边
    const std::vector<Edge> &edges() const
    {
        return edgeList;
    }

    // ============================================================
    // 邻接关系
    // ============================================================

    // 判断两点之间是否存在边
    bool hasEdge(int uLabel, int vLabel) const
    {
        int u = getIndex(uLabel);
        int v = getIndex(vLabel);

        for (const Edge &e : adj[u])
        {
            if (e.active && e.to == v)
            {
                return true;
            }
        }

        return false;
    }

    // 简单图中只有 0 / 1
    int edgeMultiplicity(
        int uLabel,
        int vLabel) const
    {
        return hasEdge(uLabel, vLabel) ? 1 : 0;
    }

    // 返回某个顶点的邻接表
    // Edge::to 是内部编号
    const std::vector<Edge> &neighbors(int label) const
    {
        int index = getIndex(label);

        return adj[index];
    }

    // 返回度数
    int degree(int label) const
    {
        int index = getIndex(label);

        int result = 0;

        for (const Edge &e : adj[index])
        {
            if (e.active)
            {
                ++result;
            }
        }

        return result;
    }

    // ============================================================
    // 调试输出
    // ============================================================

    void print() const
    {
        for (int u : vertices())
        {
            int index = getIndex(u);

            std::cout << u << ":";

            for (const Edge &e : adj[index])
            {
                if (!e.active)
                    continue;

                int v = labelOf(e.to);

                std::cout
                    << " "
                    << v;
            }

            std::cout << '\n';
        }
    }
};

#endif
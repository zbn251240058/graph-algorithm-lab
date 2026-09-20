#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H

struct Edge
{
    int id;      // 边编号
    int from;    // 内部顶点编号
    int to;      // 内部顶点编号
    bool active; // 是否有效

    Edge(int id = 0,
         int from = 0,
         int to = 0,
         bool active = true)
        : id(id),
          from(from),
          to(to),
          active(active)
    {
    }
};

#endif
#pragma once
#include "graph_mat.h"
#include <vector>

Graph vertexInducedSubgraph(const Graph &g, const std::vector<int> &S);
Graph edgeInducedSubgraph(const Graph &g, const std::vector<std::pair<int, int>> &edgeSet);
Graph complementGraph(const Graph &g);
Graph graphUnion(const Graph &g1, const Graph &g2);
Graph graphIntersection(const Graph &g1, const Graph &g2);
Graph graphDisjointUnion(const Graph &g1, const Graph &g2);
Graph graphJoin(const Graph &g1, const Graph &g2);

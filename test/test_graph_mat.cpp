#include "../src/graph_mat.h"
#include <iostream>

void test_basic()
{
    std::cout << "===== 邻接矩阵基础测试 =====\n";
    Graph g;

    // 添加3个顶点：0,1,2
    g.addVertex();
    g.addVertex();
    g.addVertex();
    std::cout << "顶点总数:" << g.vertexCount() << "\n";

    // 添加边
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    std::cout << "0‑1边:" << g.visitEdge(0, 1) << " 预期1\n";
    std::cout << "1‑2边:" << g.visitEdge(1, 2) << " 预期0\n";
    std::cout << "顶点0度:" << g.degree(0) << " 预期2\n";
    std::cout << "顶点1度:" << g.degree(1) << " 预期1\n";

    // 删除边
    g.removeEdge(0, 1);
    std::cout << "\n删除边0‑1之后\n";
    std::cout << "0‑1边:" << g.visitEdge(0, 1) << " 预期0\n";
    std::cout << "顶点0度:" << g.degree(0) << " 预期1\n";

    // 自动扩容测试，不手动addVertex直接加边2‑3
    g.addEdge(2, 3);
    std::cout << "\n自动扩容，增加边2‑3\n";
    std::cout << "顶点总数:" << g.vertexCount() << "\n";
    std::cout << "顶点3度:" << g.degree(3) << " 预期1\n";

    // 越界访问测试
    std::cout << "\n越界访问 99‑100:" << g.visitEdge(99, 100) << " 预期0\n";
    std::cout << "顶点99的度:" << g.degree(99) << " 预期0\n";
}

int main()
{
    test_basic();
    return 0;
}

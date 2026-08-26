# test/test_graph.py
import sys
from pathlib import Path

# 自动拿到项目根目录，再定位src，不依赖当前工作目录
project_root = Path(__file__).parent.parent
src_path = project_root / "src"
sys.path.append(str(src_path))

from graph_mat import Graph      #邻接矩阵
from graph_adj import GraphAdj   #链表邻接表

def test_matrix():
    print("=====测试邻接矩阵=====")
    g = Graph()
    g.addVertex()
    g.addVertex()
    g.addVertex()
    g.addEdge(0,1)
    g.addEdge(0,2)
    print(f"0‑1 edge: {g.visitEdge(0,1)}")
    print(f"deg(0): {g.degree(0)}")

def test_adj_link():
    print("\n=====测试链表邻接表=====")
    g = GraphAdj()
    g.addVertex()
    g.addVertex()
    g.addVertex()
    g.addEdge(0,1)
    g.addEdge(0,2)
    print(f"0‑1 edge: {g.visitEdge(0,1)}")
    print(f"deg(0): {g.degree(0)}")

if __name__ == "__main__":
    test_matrix()
    test_adj_link()

class Graph:
    def __init__(self):
        # mat 邻接矩阵，二维列表
        self.mat = []

    def addVertex(self):
        n = len(self.mat)
        # 新增一行：长度 n+1，全部0
        self.mat.append([0] * (n + 1))
        # 旧的每一行，向后扩充一列填0
        for i in range(n):
            self.mat[i].resize(n + 1, 0)

    def addEdge(self, u: int, v: int):
        maxId = max(u, v)
        # 顶点不够就持续增加顶点
        while len(self.mat) <= maxId:
            self.addVertex()
        # 无向图双向赋值
        self.mat[u][v] = 1
        self.mat[v][u] = 1

    def visitEdge(self, u: int, v: int) -> int:
        if u >= len(self.mat) or v >= len(self.mat):
            return 0
        return self.mat[u][v]

    def degree(self, v: int) -> int:
        if v >= len(self.mat):
            return 0
        cnt = 0
        for x in self.mat[v]:
            if x == 1:
                cnt += 1
        return cnt

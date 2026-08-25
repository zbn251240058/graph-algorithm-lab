class GraphListAdj:
    def __init__(self):
        self.adj = []

    def add_vertex(self):
        self.adj.append([])

    def add_edge(self, u, v):
        max_id = max(u, v)
        while len(self.adj) <= max_id:
            self.add_vertex()
        self.adj[u].append(v)
        self.adj[v].append(u)

    def visit_edge(self, u, v):
        if u >= len(self.adj) or v >= len(self.adj):
            return 0
        return 1 if v in self.adj[u] else 0

    def degree(self, v):
        if v >= len(self.adj):
            return 0
        return len(self.adj[v])

    def remove_edge(self, u, v):
        if self.visit_edge(u, v):
            self.adj[u].remove(v)
            self.adj[v].remove(u)

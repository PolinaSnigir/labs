class Queue:
    def __init__(self):
        self.items = []

    def is_empty(self):
        return len(self.items) == 0

    def put(self, item):
        self.items.append(item)

    def get(self):
        if not self.is_empty():
            return self.items.pop(0)
        else:
            raise IndexError("Queue is empty")

    def size(self):
        return len(self.items)


class Graph:
    def __init__(self, vertices, vertex_names):
        self.vertices = vertices
        self.graph = []
        self.adjacency_list = [[] for _ in range(vertices)]
        self.adjacency_matrix = [[0] * vertices for _ in range(vertices)]
        self.incidence_matrix = []
        self.vertex_names = vertex_names

    def add_edge(self, u, v, w):
        self.graph.append([self.vertex_names[u], self.vertex_names[v], w])
        self.adjacency_list[u].append((v, w))
        self.adjacency_matrix[u][v] = w

        incident_row = next((row for row in self.incidence_matrix if row[u] != 0 and row[v] != 0), None)

        if incident_row is not None:
            incident_row[u] = w
            incident_row[v] = w
        else:
            incident_row = [0] * self.vertices
            incident_row[u] = w
            incident_row[v] = w
            self.incidence_matrix.append(incident_row)

    def bubble_sort(self):
        n = len(self.graph)
        for i in range(n - 1):
            for j in range(0, n - i - 1):
                if self.graph[j][2] > self.graph[j + 1][2]:
                    self.graph[j], self.graph[j + 1] = self.graph[j + 1], self.graph[j]

    def find_parent(self, parent, i):
        if parent[i] == i:
            return i
        return self.find_parent(parent, parent[i])

    def union(self, parent, rank, x, y):
        x_root = self.find_parent(parent, x)
        y_root = self.find_parent(parent, y)

        if rank[x_root] < rank[y_root]:
            parent[x_root] = y_root
        elif rank[x_root] > rank[y_root]:
            parent[y_root] = x_root
        else:
            parent[y_root] = x_root
            rank[x_root] += 1

    def kruskal(self):
        result = []
        i, e = 0, 0
        self.bubble_sort()

        parent = list(range(self.vertices))
        rank = [0] * self.vertices

        while e < self.vertices - 1 and i < len(self.graph):
            u, v, w = self.graph[i]
            i += 1
            x = self.find_parent(parent, self.vertex_names.index(u))
            y = self.find_parent(parent, self.vertex_names.index(v))

            if x != y:
                e += 1
                result.append([u, v, w])
                self.union(parent, rank, x, y)

        return result

    def dfs(self, start):
        visited = [False] * self.vertices
        stack = [start]

        while stack:
            current = stack.pop()
            if not visited[current]:
                print(self.vertex_names[current], end=' ')
                visited[current] = True
                stack.extend(neighbor[0] for neighbor in self.adjacency_list[current] if not visited[neighbor[0]])

    def bfs(self, start):
        visited = [False] * self.vertices
        queue = Queue()

        queue.put(start)
        visited[start] = True

        while not queue.is_empty():
            current = queue.get()
            print(self.vertex_names[current], end=' ')

            for neighbor in self.adjacency_list[current]:
                v, _ = neighbor
                if not visited[v]:
                    queue.put(v)
                    visited[v] = True

    def print_adjacency_list(self):
        print("Adjacency List:")
        for vertex in range(self.vertices):
            neighbors = [f"({self.vertex_names[v]}, {weight})" for v, weight in self.adjacency_list[vertex]]
            print(f"{self.vertex_names[vertex]}: {neighbors}")

    def print_adjacency_matrix(self):
        print("\nAdjacency Matrix:")
        for row in self.adjacency_matrix:
            print(row)

    def print_incidence_matrix(self):
        print("\nIncidence Matrix:")
        for row in self.incidence_matrix:
            print(row)


def print_result(result):
    total_weight = 0
    for u, v, w in result:
        print(f"{u} {v} {w}")
        total_weight += w
    print("Total Weight:", total_weight)


if __name__ == "__main__":
    with open("/Users/polinasnigir/Downloads/Документ.txt", "r") as file:
        vertices_line = file.readline().strip()
        edges_lines = [line.strip() for line in file]

    vertices = vertices_line.split()
    if len(vertices) > 50:
        print("Слишком много вершин. Максимальное количество - 50.")
    else:
        g = Graph(len(vertices), vertices)

        for i, edge_line in enumerate(edges_lines):
            edge_data = list(map(int, edge_line.split()))
            for j, weight in enumerate(edge_data):
                if i != j and 1 <= weight <= 1023:
                    g.add_edge(i, j, weight)

        g.print_adjacency_list()
        g.print_adjacency_matrix()
        g.print_incidence_matrix()

        print("\nDFS:")
        start_vertex = 0
        g.dfs(start_vertex)
        print("\nBFS:")
        g.bfs(start_vertex)

        print("\nKruskal's Algorithm:")
        result = g.kruskal()
        print_result(result)

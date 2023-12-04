#include <iostream>
#include <vector>

std::vector<std::vector<int>> matrix1 = {
    {0, 2, 0, 6, 0},
    {2, 0, 3, 8, 5},
    {0, 3, 0, 0, 7},
    {6, 8, 0, 0, 9},
    {0, 5, 7, 9, 0}
};

std::vector<std::vector<int>> matrix2 = {
    {0, 9, 75, 0, 0},
    {9, 0, 95, 19, 42},
    {75, 95, 0, 51, 66},
    {0, 19, 51, 0, 31},
    {0, 42, 66, 31, 0}
};

std::vector<std::vector<int>> matrix3 = {
    {0, 19, 5, 0, 0},
    {19, 0, 5, 9, 2},
    {5, 5, 0, 1, 6},
    {0, 9, 1, 0, 1},
    {0, 2, 6, 1, 0}
};

std::vector<std::vector<int>> matrix4 = {
    {0, 4, 0, 0, 0, 0, 0, 8, 0},
    {4, 0, 8, 0, 0, 0, 0, 11, 0},
    {0, 8, 0, 7, 0, 4, 0, 0, 2},
    {0, 0, 7, 0, 9, 14, 0, 0, 0},
    {0, 0, 0, 9, 0, 10, 0, 0, 0},
    {0, 0, 4, 14, 10, 0, 2, 0, 0},
    {0, 0, 0, 0, 0, 2, 0, 1, 6},
    {8, 11, 0, 0, 0, 0, 1, 0, 7},
    {0, 0, 2, 0, 0, 0, 6, 7, 0}
};

int infinity = 7777;

void dijkstra(std::vector<std::vector<int>> &graph, int src) {
    int size = graph.size();
    std::vector<int> dist(size, infinity);
    std::vector<bool> included(size, false);
    dist[src] = 0;

    for (int neighbors = 0; neighbors < size - 1; neighbors++) {
        int u = -1;

        for (int i = 0; i < size; i++) {
            if (!included[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        included[u] = true;

        for (int i = 0; i < size; i++) {
            if (!included[i] && graph[u][i] && dist[u] != infinity && dist[u] + graph[u][i] < dist[i]) {
                dist[i] = dist[u] + graph[u][i];
            }
        }
    }

    std::cout << "Vertex  Distance from Source\n";
    for (int i = 0; i < size; i++) {
        std::cout << i << "\t" << (dist[i] == -1 ? -1 : dist[i]) << "\n";
    }
}

int main(){
    std::cout<<"\n0: \n";
    dijkstra(matrix1, 0);
    dijkstra(matrix2, 0);
    dijkstra(matrix3, 0);
    dijkstra(matrix4, 0);

    std::cout<<"\n4: \n";
    dijkstra(matrix1, 4);
    dijkstra(matrix2, 4);
    dijkstra(matrix3, 4);
    dijkstra(matrix4, 4);
    
    return 0;
}
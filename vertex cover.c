#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MAX_V 100
#define INF 99999

int graph[MAX_V][MAX_V];
int V;

bool isCover(int subset[], int size) {
    bool covered[MAX_V][MAX_V] = {false};
    
    for (int i = 0; i < size; i++) {
        int v = subset[i];
        for (int u = 0; u < V; u++) {
            if (graph[v][u]) {
                covered[v][u] = true;
                covered[u][v] = true;
            }
        }
    }
    
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] && !covered[i][j]) {
                return false;
            }
        }
    }
    
    return true;
}

int findMinimumVertexCover(int vertices[], int n) {
    int minCover = INF;
    
    for (int i = 1; i < (1 << V); i++) {
        int subset[MAX_V], size = 0;
        
        for (int j = 0; j < V; j++) {
            if (i & (1 << j)) {
                subset[size++] = vertices[j];
            }
        }
        
        if (isCover(subset, size) && size < minCover) {
            minCover = size;
        }
    }
    
    return minCover;
}

int main() {
    FILE *file = fopen("test_input.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "無法打開文件\n");
        return 1;
    }

    fscanf(file, "%d", &V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }
    fclose(file);

    int vertices[MAX_V];
    for (int i = 0; i < V; i++) {
        vertices[i] = i;
    }
    
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int minCover = findMinimumVertexCover(vertices, V);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("最小頂點覆蓋大小: %d\n", minCover);
    printf("運行時間: %f 秒\n", cpu_time_used);
    
    return 0;
}

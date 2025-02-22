#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100
#define INF INT_MAX


typedef struct {
    int weight[MAX_NODES][MAX_NODES];
    int num_nodes;
} Graph;


void init_graph(Graph *g, int nodes) {
    g->num_nodes = nodes;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            g->weight[i][j] = INF; 
        }
    }
}

void add_edge(Graph *g, int u, int v, int weight) {
    g->weight[u-1][v-1] = weight; 
    g->weight[v-1][u-1] = weight; 
}


void dijkstra(Graph *g, int start, int target) {
    int dist[MAX_NODES], visited[MAX_NODES], prev[MAX_NODES];
    for (int i = 0; i < g->num_nodes; i++) {
        dist[i] = INF;
        visited[i] = 0;
        prev[i] = -1;
    }
    dist[start-1] = 0; 

    for (int i = 0; i < g->num_nodes; i++) {
        int min_dist = INF, u = -1;
        for (int j = 0; j < g->num_nodes; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u = j;
            }
        }

        if (u == -1 || u == target-1) break; 
        visited[u] = 1;

        for (int v = 0; v < g->num_nodes; v++) {
            if (g->weight[u][v] != INF && !visited[v]) {
                int new_dist = dist[u] + g->weight[u][v];
                if (new_dist < dist[v]) {
                    dist[v] = new_dist;
                    prev[v] = u;
                }
            }
        }
    }

    
    printf("En kisa yol (Dijkstra) %d -> %d: ", start, target);
    if (dist[target-1] == INF) {
        printf("Yol yok\n");
    } else {
        int path[MAX_NODES], path_length = 0, current = target-1; 
        while (current != -1) {
            path[path_length++] = current + 1; 
            current = prev[current];
        }
        for (int i = path_length - 1; i >= 0; i--) {
            printf("%d ", path[i]);
        }
        printf("\nMesafe: %d\n", dist[target-1]); 
    }
}


void prim(Graph *g, int start) {
    printf("MST (Prim) başlangic dugumu %d:\n", start);
    int mst[MAX_NODES][2], mst_size = 0, in_mst[MAX_NODES], key[MAX_NODES];
    int parent[MAX_NODES]; 
    for (int i = 0; i < g->num_nodes; i++) {
        in_mst[i] = 0;
        key[i] = INF;
        parent[i] = -1;
    }
    key[start-1] = 0; 

    for (int i = 0; i < g->num_nodes; i++) {
        int min_key = INF, u = -1;
        for (int j = 0; j < g->num_nodes; j++) {
            if (!in_mst[j] && key[j] < min_key) {
                min_key = key[j];
                u = j;
            }
        }

        if (u == -1) break; 
        in_mst[u] = 1;

        
        if (parent[u] != -1) {
            mst[mst_size][0] = parent[u] + 1; 
            mst[mst_size][1] = u + 1; 
            printf("%d - %d - agirlik %d\n", mst[mst_size][0], mst[mst_size][1], g->weight[parent[u]][u]);
            mst_size++;
        }

        
        for (int v = 0; v < g->num_nodes; v++) {
            if (g->weight[u][v] != INF && !in_mst[v] && g->weight[u][v] < key[v]) {
                key[v] = g->weight[u][v];
                parent[v] = u; 
            }
        }
    }

    
    
    if (mst_size == 0) {
        printf("MST oluşturulamadi.\n");
    }
}


int main() {
    Graph g;
    init_graph(&g, 7); 

    
    add_edge(&g, 1, 2, 3);
    add_edge(&g, 2, 4, 2);
    add_edge(&g, 2, 3, 1);
    add_edge(&g, 3, 4, 3);
    add_edge(&g, 4, 6, 4);
    add_edge(&g, 5, 6, 1);
    add_edge(&g, 7, 5, 3);
    add_edge(&g, 7, 3, 2);

    
    dijkstra(&g, 6, 2);
    dijkstra(&g, 7, 4);
    dijkstra(&g, 1, 5);

    
    prim(&g, 6);
    prim(&g, 7);
    prim(&g, 1);

    return 0;
}

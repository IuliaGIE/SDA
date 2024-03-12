#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct node {
    int val;
    int cost;
    struct node* next;
} node;

typedef struct graph {
    int nr_nodes;
    node** neighbours;
} graph;

void add_edge(graph* g, int u, int v, int cost) {
    node* n = (node*) malloc(sizeof(node));
    n->val = v;
    n->cost = cost;
    n->next = g->neighbours[u];
    g->neighbours[u] = n;
}

void print_distances(int* distances, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", distances[i]);
    }
    printf("\n");
}

void dijkstra(graph* g, int start) {
    int* distances = (int*) malloc(g->nr_nodes * sizeof(int));
    bool* visited = (bool*) malloc(g->nr_nodes * sizeof(bool));
    for (int i = 0; i < g->nr_nodes; i++) {
        distances[i] = INT_MAX;
        visited[i] = false;
    }
    distances[start] = 0;
    visited[start] = true;
    node* current = g->neighbours[start];
    while (current != NULL) {
        distances[current->val] = current->cost;
        current = current->next;
    }
    for (int i = 1; i < g->nr_nodes; i++) {
        int min_dist = INT_MAX;
        int u;
        for (int j = 0; j < g->nr_nodes; j++) {
            if (!visited[j] && distances[j] < min_dist) {
                min_dist = distances[j];
                u = j;
            }
        }
        visited[u] = true;
        node* current = g->neighbours[u];
        while (current != NULL) {
            int alt = distances[u] + current->cost;
            if (alt < distances[current->val]) {
                distances[current->val] = alt;
            }
            current = current->next;
        }
    }
    printf("Distances from node %d:\n", start);
    print_distances(distances, g->nr_nodes);
}

int main() {
    int n, m;
    printf("Enter the number of nodes and edges:\n");
    scanf("%d %d", &n, &m);
    graph* g = (graph*) malloc(sizeof(graph));
    g->nr_nodes = n;
    g->neighbours = (node**) malloc(n * sizeof(node*));
    for (int i = 0; i < n; i++) {
        g->neighbours[i] = NULL;
    }
    printf("Enter the edges (u, v, cost):\n");
    for (int i = 0; i < m; i++) {
        int u, v, cost;
        scanf("%d %d %d", &u, &v, &cost);
        add_edge(g, u, v, cost);
        add_edge(g, v, u, cost); // for undirected graph
    }
    int start;
    printf("Enter the starting node:\n");
    scanf("%d", &start);
    dijkstra(g, start);
    return 0;
}

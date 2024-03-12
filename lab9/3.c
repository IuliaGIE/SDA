#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct graph {
    int nr_nodes;
    node** neighbours;
} graph;

typedef struct node {
    int val;
    struct node* next;
} node;

void add_edge(graph* g, int u, int v) {
    node* n = (node*) malloc(sizeof(node));
    n->val = v;
    n->next = g->neighbours[u];
    g->neighbours[u] = n;
}

void dfs(graph* g, int node, bool* visited, node** stack) {
    visited[node] = true;
    node* current = g->neighbours[node];
    while (current != NULL) {
        int neighbour = current->val;
        if (!visited[neighbour]) {
            dfs(g, neighbour, visited, stack);
        }
        current = current->next;
    }
    node* n = (node*) malloc(sizeof(node));
    n->val = node;
    n->next = *stack;
    *stack = n;
}

void dfs_transpose(graph* g, int node, bool* visited) {
    visited[node] = true;
    printf("%d ", node);
    node* current = g->neighbours[node];
    while (current != NULL) {
        int neighbour = current->val;
        if (!visited[neighbour]) {
            dfs_transpose(g, neighbour, visited);
        }
        current = current->next;
    }
}

graph* transpose(graph* g) {
    graph* t = (graph*) malloc(sizeof(graph));
    t->nr_nodes = g->nr_nodes;
    t->neighbours = (node**) malloc(g->nr_nodes * sizeof(node*));
    for (int i = 0; i < g->nr_nodes; i++) {
        t->neighbours[i] = NULL;
    }
    for (int i = 0; i < g->nr_nodes; i++) {
        node* current = g->neighbours[i];
        while (current != NULL) {
            add_edge(t, current->val, i);
            current = current->next;
        }
    }
    return t;
}

void kosaraju(graph* g) {
    bool* visited = (bool*) malloc(g->nr_nodes * sizeof(bool));
    for (int i = 0; i < g->nr_nodes; i++) {
        visited[i] = false;
    }
    node* stack = NULL;
    for (int i = 0; i < g->nr_nodes; i++) {
        if (!visited[i]) {
            dfs(g, i, visited, &stack);
        }
    }
    graph* t = transpose(g);
    for (int i = 0; i < g->nr_nodes; i++) {
            visited[i] = false;
}
int count = 0;
while (stack != NULL) {
    int node = stack->val;
    stack = stack->next;
    if (!visited[node]) {
        count++;
        printf("Componenta conexa %d: ", count);
        dfs_transpose(t, node, visited);
        printf("\n");
    }
}
free(visited);
node* current;
for (int i = 0; i < g->nr_nodes; i++) {
    current = g->neighbours[i];
    while (current != NULL) {
        node* tmp = current;
        current = current->next;
        free(tmp);
    }
    current = t->neighbours[i];
    while (current != NULL) {
        node* tmp = current;
        current = current->next;
        free(tmp);
    }
}
free(g->neighbours);
free(t->neighbours);
free(g);
free(t);
}

int main() {
FILE* f = fopen("graf.in", "r");
int n, m;
fscanf(f, "%d%d", &n, &m);
graph* g = (graph*) malloc(sizeof(graph));
g->nr_nodes = n;
g->neighbours = (node**) malloc(n * sizeof(node*));
for (int i = 0; i < n; i++) {
g->neighbours[i] = NULL;
}
for (int i = 0; i < m; i++) {
int u, v;
fscanf(f, "%d%d", &u, &v);
add_edge(g, u, v);
}
fclose(f);
kosaraju(g);
return 0;
}
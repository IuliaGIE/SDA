#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node* next;
} node;

typedef struct graph {
    int nr_nodes;
    node** neighbours;
} graph;

void add_edge(graph* g, int u, int v) {
    node* n = malloc(sizeof(node));
    n->val = v;
    n->next = g->neighbours[u];
    g->neighbours[u] = n;
}

graph* build_graph(int n, int m, FILE* in) {
    graph* g = malloc(sizeof(graph));
    g->nr_nodes = n;
    g->neighbours = calloc(n, sizeof(node*));

    for (int i = 0; i < m; i++) {
        int u, v;
        fscanf(in, "%d%d", &u, &v);
        add_edge(g, u, v);
        add_edge(g, v, u);
    }

    return g;
}

void free_graph(graph* g) {
    for (int i = 0; i < g->nr_nodes; i++) {
        node* curr = g->neighbours[i];
        while (curr != NULL) {
            node* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    free(g->neighbours);
    free(g);
}

void print_graph(graph* g) {
    for (int i = 0; i < g->nr_nodes; i++) {
        printf("%d: ", i);
        node* curr = g->neighbours[i];
        while (curr != NULL) {
            printf("%d ", curr->val);
            curr = curr->next;
        }
        printf("\n");
    }
}

int main() {
    FILE* in = fopen("graf.in", "r");
    if (in == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    int n, m;
    fscanf(in, "%d%d", &n, &m);
    graph* g = build_graph(n, m, in);
    fclose(in);

    print_graph(g);
    free_graph(g);
    return 0;
}

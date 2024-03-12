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

void bfs(graph* g, int start_node, int* dist) {
    int queue[g->nr_nodes];
    int front = 0, rear = 0;
    queue[rear++] = start_node;
    dist[start_node] = 0;

    while (front != rear) {
        int curr_node = queue[front++];
        node* neighbours = g->neighbours[curr_node];

        while (neighbours != NULL) {
            int neighbour_node = neighbours->val;
            if (dist[neighbour_node] == -1) {
                queue[rear++] = neighbour_node;
                dist[neighbour_node] = dist[curr_node] + 1;
            }
            neighbours = neighbours->next;
        }
    }
}
void DFS_visit(graph* G, int node, int* visited, int* time, int* finish_time, int* stack, int* stack_top) {
    visited[node] = 1;
    time[node] = ++(*time);
    node *current = G->neighbours[node];
    while (current != NULL) {
        int neighbour = current->val;
        if (!visited[neighbour]) {
            DFS_visit(G, neighbour, visited, time, finish_time, stack, stack_top);
        }
        current = current->next;
    }
    finish_time[node] = ++(*time);
    stack[++(*stack_top)] = node;
}

void DFS(graph* G, int* visited, int* time, int* finish_time, int* stack, int* stack_top) {
    int i;
    for (i = 0; i < G->nr_nodes; i++) {
        visited[i] = 0;
        time[i] = 0;
        finish_time[i] = 0;
    }
    int t = 0;
    for (i = 0; i < G->nr_nodes; i++) {
        if (!visited[i]) {
            DFS_visit(G, i, visited, &t, finish_time, stack, stack_top);
        }
    }
}

void topological_sort(graph* G) {
    int* visited = malloc(G->nr_nodes * sizeof(int));
    int* time = malloc(G->nr_nodes * sizeof(int));
    int* finish_time = malloc(G->nr_nodes * sizeof(int));
    int* stack = malloc(G->nr_nodes * sizeof(int));
    int stack_top = -1;

    DFS(G, visited, time, finish_time, stack, &stack_top);

    while (stack_top >= 0) {
        printf("%d ", stack[stack_top--]);
    }
    printf("\n");

    free(visited);
    free(time);
    free(finish_time);
    free(stack);
}


int main() {
    FILE* fp = fopen("graf.in", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Read number of nodes and edges
    int n, m;
    fscanf(fp, "%d %d", &n, &m);

    // Initialize the graph
    graph* g = (graph*)malloc(sizeof(graph));
    g->nr_nodes = n;
    g->neighbours = (node**)malloc(sizeof(node*) * n);

    for (int i = 0; i < n; i++) {
        g->neighbours[i] = NULL;
    }

    // Read the edges
    for (int i = 0; i < m; i++) {
        int u, v;
        fscanf(fp, "%d %d", &u, &v);

        node* new_node = (node*)malloc(sizeof(node));
        new_node->val = v;
        new_node->next = g->neighbours[u];
        g->neighbours[u] = new_node;

        // Add the reverse edge for an undirected graph
        new_node = (node*)malloc(sizeof(node));
        new_node->val = u;
        new_node->next = g->neighbours[v];
        g->neighbours[v] = new_node;
    }

    fclose(fp);

    // Run BFS from node 1
    int dist[n];
    for (int i = 0; i < n; i++) {
        dist[i] = -1;
    }

    bfs(g, 1, dist);

    // Print the distances
    for (int i = 0; i < n; i++) {
        printf("Distance from node 1 to node %d is %d\n", i, dist[i]);
    }

    // Free the memory
    for (int i = 0; i < n; i++) {
        node* curr = g->neighbours[i];
        while (curr != NULL) {
            node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(g->neighbours);
    free(g);

    return 0;
}

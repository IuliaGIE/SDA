#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 9999

typedef struct node
{
    int val;
    int cost;
    struct node *next;
} node;

typedef struct graph
{
    int nr_nodes;
    node **neighbours;
} graph;

void add_edge(graph *g, int u, int v, int cost)
{
    node *n = (node *)malloc(sizeof(node));
    n->val = v;
    n->cost = cost;
    n->next = g->neighbours[u];
    g->neighbours[u] = n;
}

void print_array(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_matrix(int **matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] == INF)
            {
                printf("INF ");
            }
            else
            {
                printf("%d ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

void bellman_ford(graph *g, int source)
{
    int **cost = (int **)malloc(g->nr_nodes * sizeof(int *));
    for (int i = 0; i < g->nr_nodes; i++)
    {
        cost[i] = (int *)malloc(g->nr_nodes * sizeof(int));
    }
    for (int i = 0; i < g->nr_nodes; i++)
    {
        for (int j = 0; j < g->nr_nodes; j++)
        {
            if (i == j)
            {
                cost[i][j] = 0;
            }
            else
            {
                cost[i][j] = INF;
            }
        }
    }
    for (int i = 0; i < g->nr_nodes; i++)
    {
        node *current = g->neighbours[i];
        while (current != NULL)
        {
            cost[i][current->val] = current->cost;
            current = current->next;
        }
    }
    printf("Initial matrix of costs:\n");
    print_matrix(cost, g->nr_nodes);

    // Algoritmul Bellman-Ford fără coadă
    int *distances = (int *)malloc(g->nr_nodes * sizeof(int));
    for (int i = 0; i < g->nr_nodes; i++)
    {
        distances[i] = INF;
    }
    distances[source] = 0;
    bool changed;
    for (int i = 0; i < g->nr_nodes; i++)
    {
        changed = false;
        for (int j = 0; j < g->nr_nodes; j++)
        {
            for (int k = 0; k < g->nr_nodes; k++)
            {
                if (distances[j] + cost[j][k] < distances[k])
                {
                    distances[k] = distances[j] + cost[j][k];
                    changed = true;
                }
            }
        }
        if (!changed)
        {
            break;
        }
    }

    printf("Shortest distances from source node %d:\n", source);
    print_array(distances, g->nr_nodes);
}

int main()
{
    int n, m;
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &n, &m);
    graph *g = (graph *)malloc(sizeof(graph));
    g->nr_nodes = n;
    g->neighbours = (node **)malloc(n * sizeof(node *));
    for (int i = 0; i < n; i++)
    {
        g->neighbours[i] = NULL;
    }
    printf("Enter the edges and costs:\n");
    for (int i = 0; i < m; i++)
    {
        int u, v, cost;
        scanf("%d %d %d", &u, &v, &cost);
        add_edge(g, u, v, cost);
    }
    int source;
    printf("Enter the source node: ");
    scanf("%d", &source);
    bellman_ford(g, source);
    return 0;
}
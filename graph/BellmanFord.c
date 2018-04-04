#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct edge
{
    int u, v, weight;
} edge;

unsigned short infinity = ~0;
int n;
int edge_count = 0;

void read(int graph[][n]);
void initialize(int distance[], int src[]);
void create_edgelist(int graph[][n], edge edgelist[]);
void bellman_ford(int v, edge edgelist[], int distance[], int src[]);
void print_out(short start_vertex, int distance[]);

int main()
{

    printf("How many vertices in graph : ");
    scanf("%d", &n);

    int max_edge = n * (n - 1);
    int graph[n][n];
    int distance[n]; // store the closest distance from start_vertex
    int src[n];      // check who updates the distance last
    short start_vertex;
    edge edgelist[max_edge];

    printf("Which vertex do you want to start from : ");
    scanf("%hu", &start_vertex);

    read(graph);
    create_edgelist(graph, edgelist);
    initialize(distance, src);
    bellman_ford(start_vertex, edgelist, distance, src);
    print_out(start_vertex, distance);
}

void read(int graph[][n])
{
    printf("Enter adjacency matrix : ");
    printf("\n");
    int i, j;
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            scanf("%d", &graph[i][j]);
}

void create_edgelist(int graph[][n], edge edgelist[])
{
    int i, j;
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            if (graph[i][j] != 0)
            {
                edgelist[edge_count].u = i;
                edgelist[edge_count].v = j;
                edgelist[edge_count++].weight = graph[i][j];
            }
}

void initialize(int distance[], int src[])
{
    int i;

    for (i = 0; i < n; ++i)
    {
        distance[i] = infinity;
        src[i] = -1;
    }
}

void bellman_ford(int v, edge edgelist[], int distance[], int src[])
{
    distance[v] = 0;

    int i, j;

    // check if there is distance[] updated,
    // if there is not vertex updated , stop iteration
    int flag = TRUE; 

    for (i = 0; i < n - 1 && flag; ++i)
    {
        flag = FALSE;
        for (j = 0; j < edge_count; ++j)
        {
            if (distance[edgelist[j].u] + edgelist[j].weight < distance[edgelist[j].v] && distance[edgelist[j].u] != infinity)
            {
                distance[edgelist[j].v] = distance[edgelist[j].u] + edgelist[j].weight;
                src[edgelist[j].v] = edgelist[j].u;
                flag = TRUE;
            }
        }
    }
}

void print_out(short start_vertex, int distance[])
{
    int i;

    printf("\n");

    for (i = 0; i < n; ++i)
    {
        printf("Minimum cost from %d to %d = ", start_vertex, i);
        if (distance[i] != infinity)
            printf("%d\n", distance[i]);
        else
            printf("unreachable ... \n");
    }
}
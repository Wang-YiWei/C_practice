#include <stdio.h>

typedef struct edge
{
    int u, v, weight;
} edge;

int n;
int edge_count = 0;

void read(int graph[][n]);
void initialize(int ancestor[]);
void create_edgelist(int graph[][n], edge edgelist[]);
void sort_edgelist(int graph[][n], edge edgelist[]);
void kruskal(int ancestor[], edge edgelist[], edge spanning_list[]);
void union_group(int ancestor[], int vertex1, int vertex2);
void print_out(edge spanning_list[]);

int main()
{

    printf("How many vertices in graph : ");
    scanf("%d", &n);

    int max_edge = n * (n - 1);
    int graph[n][n];
    int ancestor[n];
    edge edgelist[max_edge];
    edge spanning_list[n];

    read(graph);
    create_edgelist(graph, edgelist);
    sort_edgelist(graph, edgelist);
    initialize(ancestor);
    kruskal(ancestor, edgelist, spanning_list);
    print_out(spanning_list);
}

void kruskal(int ancestor[], edge edgelist[], edge spanning_list[])
{

    int i;
    int ancestor_u, ancestor_v;
    int spanning_edge_count = 0;

    for (i = 0; i < edge_count; ++i)
    {
        // vertex u and vertex v belongs to different group, no cycle
        if (ancestor[edgelist[i].u] != ancestor[edgelist[i].v])
        {
            union_group(ancestor, edgelist[i].u, edgelist[i].v);

            // push to spanning_list
            spanning_list[spanning_edge_count++] = edgelist[i];
        }
    }
}

void union_group(int ancestor[], int vertex1, int vertex2)
{
    int i;

    for (i = 0; i < n; ++i)
        if (ancestor[i] == vertex2)
            ancestor[i] = vertex1;
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

void initialize(int ancestor[])
{
    int i;

    // each vertex's ancestor is itself
    for (i = 0; i < n; ++i)
        ancestor[i] = i;
}

void create_edgelist(int graph[][n], edge edgelist[])
{
    int i, j;
    for (i = 0; i < n; ++i)
        for (j = i; j < n; ++j)
            if (graph[i][j] != 0)
            {
                edgelist[edge_count].u = i;
                edgelist[edge_count].v = j;
                edgelist[edge_count++].weight = graph[i][j];
            }
}

void sort_edgelist(int graph[][n], edge edgelist[])
{
    int i, j;
    int min = edgelist[0].weight;
    edge tmp;

    for (i = 0; i < edge_count; ++i)
    {
        for (j = 0; j < edge_count - i - 1; ++j)
        {
            if (edgelist[j].weight > edgelist[j + 1].weight)
            {
                tmp = edgelist[j];
                edgelist[j] = edgelist[j + 1];
                edgelist[j + 1] = tmp;
            }
        }
    }
}

void print_out(edge spanning_list[])
{
    int i;
    int cost = 0;

    printf("\nspanning edges : \n");
    for (i = 0; i < n - 1; ++i)
    {
        cost += spanning_list[i].weight;
        printf("%d -> %d\n", spanning_list[i].u,spanning_list[i].v);
    }

    printf("\ncost = ");
    for (i = 0; i < n - 1; ++i)
    {
        cost += spanning_list[i].weight;
        printf("%d", spanning_list[i].weight);
        if (i != n - 2)
            printf(" + ");
        else
            printf(" = %d\n", cost);
    }
}

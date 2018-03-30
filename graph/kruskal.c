#include <stdio.h>

typedef struct edge
{
    int u, v, weight;
} edge;

int n;
int edge_count = 0;
int spanning_edge_count = 0;

void read(int graph[][n]);
void initialize(int ancestor[], int subset[]);
void create_edgelist(int graph[][n], edge edgelist[]);
void sort_edgelist(int graph[][n], edge edgelist[]);
void kruskal(int ancestor[], int subset[], edge edgelist[], edge spanning_list[]);
void union_sets(int ancestor[], edge spanning_list[], edge new_edge);
void print_out(edge spanning_list[]);

int main()
{

    printf("How many vertices in graph : ");
    scanf("%d", &n);

    int max_edge = n * (n - 1);
    int graph[n][n];
    int ancestor[n];
    int subset[n];
    edge edgelist[max_edge];
    edge spanning_list[n];

    read(graph);
    create_edgelist(graph, edgelist);
    sort_edgelist(graph, edgelist);
    initialize(ancestor, subset);
    kruskal(ancestor, subset, edgelist, spanning_list);
    print_out(spanning_list);
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

void initialize(int ancestor[], int subset[])
{
    int i;

    // each vertex's ancestor is itself
    for (i = 0; i < n; ++i)
    {
        ancestor[i] = i;
        subset[i] = -1;
    }
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

void kruskal(int ancestor[], int subset[], edge edgelist[], edge spanning_list[])
{

    int i;
    int ancestor_u, ancestor_v;

    for (i = 0; i < edge_count; ++i)
    {
        // vertex u and vertex v belongs to different group, no cycle
        if (ancestor[edgelist[i].u] != ancestor[edgelist[i].v])
        {
            union_sets(ancestor, spanning_list, edgelist[i]);

            // push to spanning_list
            spanning_list[spanning_edge_count++] = edgelist[i];
        }
    }
}

void union_sets(int ancestor[], edge spanning_list[], edge new_edge)
{
    int i;
    for (i = 0; i < n; ++i)
        if (ancestor[i] == new_edge.v)
            ancestor[i] = ancestor[new_edge.u];
}

void print_out(edge spanning_list[])
{
    int i;
    int cost = 0;

    printf("\nspanning edges : \n");
    for (i = 0; i < n - 1; ++i)
    {
        printf("%d -> %d\n", spanning_list[i].u, spanning_list[i].v);
    }

    printf("\ncost : \n");
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

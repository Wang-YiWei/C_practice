#include <stdio.h>

typedef struct edge
{
    int u, v, weight;
} edge;

unsigned short infinity = ~0;
int n;
int edge_count = 0;
int spanning_vertex_count = 0;

void read(int graph[][n]);
void initialize(int start_vertex, int predecessor[], int key[], int visited[]);
void create_edgelist(int graph[][n], edge edgelist[]);
void prim(int vertex, int predecessor[], int key[], int visited[], edge edgelist[]);
void compare_with_adjacent_vertices(int vertex, int predecessor[], int key[], int visited[], edge edgelist[]);
void print_out(int key[], int predecessor[]);

int main()
{

    printf("How many vertices in graph : ");
    scanf("%d", &n);

    int max_edge = n * (n - 1);
    int graph[n][n];
    int predecessor[n];
    int key[n];
    int visited[n];
    int start_vertex;
    edge edgelist[max_edge];

    printf("Which vertex do you want to start from : ");
    scanf("%d", &start_vertex);

    read(graph);
    create_edgelist(graph, edgelist);
    initialize(start_vertex, predecessor, key, visited);
    prim(start_vertex, predecessor, key, visited, edgelist);
    print_out(key, predecessor);
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

void initialize(int start_vertex, int predecessor[], int key[], int visited[])
{
    int i;

    // each vertex's predecessor is itself
    for (i = 0; i < n; ++i)
    {
        predecessor[i] = -1;
        key[i] = infinity;
        visited[i] = 0;
    }

    key[start_vertex] = 0;
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

void prim(int vertex, int predecessor[], int key[], int visited[], edge edgelist[])
{

    int i;
    int min_vertex;
    int min_key;

    while (spanning_vertex_count != n)
    {
        min_key = infinity;
        for (i = 0; i < n; ++i)
        {
            if (visited[i] != 1 && key[i] < min_key)
            {
                min_vertex = i;
                min_key = key[i];
            }
        }

        visited[min_vertex] = (min_key == infinity) ? 0 : 1;
        spanning_vertex_count++;
        compare_with_adjacent_vertices(min_vertex, predecessor, key, visited, edgelist);
    }
}

void compare_with_adjacent_vertices(int vertex, int predecessor[], int key[], int visited[], edge edgelist[])
{
    int i;
    int adjacent_min_vertex, adjacent_min_key = infinity;
    edge min_edge;

    for (i = 0; i < edge_count; ++i)
    {
        if (edgelist[i].u == vertex)
        {
            if (!visited[edgelist[i].v] && edgelist[i].weight < key[edgelist[i].v])
            {
                predecessor[edgelist[i].v] = vertex;
                key[edgelist[i].v] = edgelist[i].weight;
                if (adjacent_min_key > key[edgelist[i].v])
                {
                    adjacent_min_key = key[edgelist[i].v];
                    adjacent_min_vertex = edgelist[i].v;
                }
            }
        }
        else if (edgelist[i].v == vertex)
        {
            if (!visited[edgelist[i].u] && edgelist[i].weight < key[edgelist[i].u])
            {
                predecessor[edgelist[i].u] = vertex;
                key[edgelist[i].u] = edgelist[i].weight;
                if (adjacent_min_key > key[edgelist[i].u])
                {
                    adjacent_min_key = key[edgelist[i].u];
                    adjacent_min_vertex = edgelist[i].u;
                }
            }
        }
    }
}

void print_out(int key[], int predecessor[])
{
    int i = 0, j = 0;
    int parent = -1;
    int times = 0;
    int cost = 0;

    printf("\npaths : \n");
    while (i < n - 1)
    {
        times = 0;
        for (j = 0; j < n; ++j)
            if (predecessor[j] == parent)
            {
                parent = j;
                printf("%d - ", parent);
                break;
            }

        for (j = 0; j < n; ++j)
            if (predecessor[j] == parent)
            {
                if (times == 0)
                    printf("%d\n", j);
                else
                    printf("%d - %d\n", parent, j);
                i++;
                times++;
            }
    }

    printf("\ncost : \n");
    for (i = 0; i < n; ++i)
    {
        cost += key[i];
        printf("%d", key[i]);
        if (i != n - 1)
            printf(" + ");
        else
            printf(" = %d\n", cost);
    }
}

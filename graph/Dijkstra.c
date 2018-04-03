#include <stdio.h>

#define TRUE 1
#define FALSE 0

typedef struct edge
{
    int u, v, weight;
} edge;

unsigned short infinity = ~0;
int n;

void read(int graph[][n]);
void dijkstra(int v, int graph[][n], int distance[], short found[]);
int choose(int distance[], short found[]);
void print_out(short start_vertex, int distance[]);

int main()
{

    printf("How many vertices in graph : ");
    scanf("%d", &n);

    int graph[n][n];
    int distance[n]; // store the closest distance from start_vertex
    short found[n];
    short start_vertex;

    printf("Which vertex do you want to start from : ");
    scanf("%hu", &start_vertex);

    read(graph);

    dijkstra(start_vertex, graph, distance, found);
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

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
        {
            if (i == j)
                graph[i][j] = -infinity;
            else if (graph[i][j] == 0)
                graph[i][j] = infinity >> 1; // to avoid overflow when doing addition , shift right
        }
}

void dijkstra(int v, int graph[][n], int distance[], short found[])
{
    int i;
    int u; // the closest vertex (not found yet) to start vertex
    int w; // iterate for every vertex after a vertex is found

    // initialize
    for (i = 0; i < n; ++i)
    {
        found[i] = FALSE;
        distance[i] = graph[v][i];
    }

    found[v] = TRUE;
    distance[v] = 0;

    // from start vertex to target vertex ,
    // the shortest path can only go through another n-2 verticies
    for (i = 0; i < n - 2; ++i)
    {
        // find the closest vertex that is not found yet
        u = choose(distance, found);

        found[u] = TRUE;

        // update distance[] after find a new vertex
        for (w = 0; w < n; ++w)
        {
            if (!found[w])
            {
                if (distance[u] + graph[u][w] < distance[w])
                    distance[w] = distance[u] + graph[u][w];
            }
        }
    }
}

// return a vertex U (not found yet) that is closest to vertex V
int choose(int distance[], short found[])
{
    int i, min, minpos;
    min = infinity;
    minpos = -1;

    for (i = 0; i < n; ++i)
    {
        if (distance[i] < min && !found[i])
        {
            min = distance[i];
            minpos = i;
        }
    }

    return minpos;
}

void print_out(short start_vertex, int distance[])
{
    int i;

    printf("\n");

    for (i = 0; i < n; ++i)
    {
        printf("Minimum cost from %d to %d = ", start_vertex, i);
        if (distance[i] != infinity >> 1)
            printf("%d\n", distance[i]);
        else
            printf("unreachable ... \n");
    }
}
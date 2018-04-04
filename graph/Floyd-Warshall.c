#include <stdio.h>

unsigned short infinity = ~0;
int n;
int edge_count = 0;

void read(int graph[][n]);
void initialize(int src[][n]);
void floyd_warshall(int graph[][n], int src[][n]);
void print_out(int graph[][n]);

int main()
{

    printf("How many vertices in graph : ");
    scanf("%d", &n);

    int max_edge = n * (n - 1);
    int graph[n][n];
    int src[n][n]; // check who updates the distance last

    read(graph);
    initialize(src);
    floyd_warshall(graph, src);
    print_out(graph);
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
            if (graph[i][j] == 0 && i != j)
                graph[i][j] = infinity;
}

void initialize(int src[][])
{
    int i;

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            src[i][j] = -1;
}

void floyd_warshall(int graph[][n], int src[][n])
{

    int i, j, k;

    for (k = 0; k < n; ++k)
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                if (i == j || j == k || i == k)
                    continue;
                if (graph[i][k] + graph[k][j] < graph[i][j])
                {
                    graph[i][j] = graph[i][k] + graph[k][j];
                    src[i][j] = k;
                }
            }
        }
    }
}

void print_out(int graph[][n])
{
    int i, j;

    printf("\n");
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}
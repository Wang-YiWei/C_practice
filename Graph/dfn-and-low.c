#include <stdio.h>

#define MIN2(x, y) ((x) < (y) ? (x) : (y))

#define exist 1
#define back_edge 2

int n;
int num = 0;
int startVertex = 3;

void initialize(int dfn[], int low[]);
void read(int graph[][n]);
void DFS(int child, int parent, int graph[][n], int dfn[], int low[]);
void printOut(int dfn[], int low[]);

void main()
{

	printf("Enter number of vertices:");
	scanf("%d", &n);

	int graph[n][n];
	int dfn[n];
	int low[n];

	initialize(dfn, low);

	printf("\nEnter adjecency matrix of the graph:\n");
	read(graph);
	printf("\n");

	printf("Traversal order : ");
	DFS(startVertex, -1, graph, dfn, low);
	printf("\n\n");
	printOut(dfn, low);
}

void initialize(int dfn[], int low[])
{
	int i;
	for (i = 0; i < n; i++)
		dfn[i] = low[i] = -1;
	
}

void read(int graph[][n])
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &graph[i][j]);
}

void DFS(int child, int parent, int graph[][n], int dfn[], int low[])
{
	int adj_vertex;
	int new_child;
	if(child == startVertex) printf("%d", child);
	else printf(" => %d", child);

	// assign value to dfn and low
	dfn[child] = low[child] = num++;

	for (new_child = 0; new_child < n; new_child++)
		// if not visited and there exists a path to the vertex
		if (dfn[new_child] < 0 && graph[child][new_child] == exist)
		{
			DFS(new_child, child, graph, dfn, low);

			// calculate value of low when going back
			for (adj_vertex = 0; adj_vertex < n; ++adj_vertex)
				// if there exists a back edge to my ancestor vertex
				if (graph[child][adj_vertex] == back_edge && dfn[child] > dfn[adj_vertex])
					low[child] = dfn[adj_vertex];

			// if my child has lower value of low , update my value of low
			low[child] = MIN2(low[child], low[new_child]);
		}
}

void printOut(int dfn[], int low[])
{
	int i;
	printf("vertex : ");
	for (i = 0; i < n; ++i)
		printf("%d ",i);
	printf("\n");
	
	printf("dfn :    ");
	for (i = 0; i < n; ++i)
		printf("%d ", dfn[i]);
	printf("\n");

	printf("low :    ");
	for (i = 0; i < n; ++i)
		printf("%d ", low[i]);
	printf("\n");
}
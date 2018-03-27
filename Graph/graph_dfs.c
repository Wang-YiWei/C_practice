#include <stdio.h>

int num;
void initialize(int visited[]);
void read(int graph[][num]);
void DFS(int i,int visited[],int graph[][num]);

void main()
{

	printf("Enter number of vertices:");
	scanf("%d", &num);

	int graph[num][num];
	int visited[num];
	
	initialize(visited);

	printf("\nEnter adjecency matrix of the graph:\n");
	read(graph);
	printf("\n");

	DFS(0,visited,graph);
}

void initialize(int visited[])
{
	int i;
	for (i = 0; i < num; i++)
		visited[i] = 0;
}

void read(int graph[][num])
{
	int i, j;
	for (i = 0; i < num; i++)
		for (j = 0; j < num; j++)
			scanf("%d", &graph[i][j]);
}

void DFS(int i, int visited[],int graph[][num])
{
	int j;
	printf("%d\n", i);
	visited[i] = 1;

	for (j = 0; j < num; j++)
		if (!visited[j] && graph[i][j] == 1)
			DFS(j,visited,graph);
}

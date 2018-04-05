#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int vertex;
	struct node *next;
} node;

int num;

node *top = NULL;

void initialize(int visited[]);
void read(int graph[][num]);
void DFS(int i, int visited[], int graph[][num]);
void search(int visited[], int graph[][num]);
void push(int v);
void list_stack();

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

	search(visited, graph);
	list_stack();
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

void DFS(int i, int visited[], int graph[][num])
{
	int j;

	visited[i] = 1;

	for (j = 0; j < num; j++)
		if (!visited[j] && graph[i][j] == 1)
		{
			DFS(j, visited, graph);
			push(j);
		}
}

void search(int visited[], int graph[][num])
{
	int i;
	for (i = 0; i < num; ++i)
	{
		if (!visited[i])
		{
			DFS(i, visited, graph);
			push(i);
		}
	}
}

void push(int v)
{
	node *new_node = (node *)malloc(sizeof(node));
	new_node->next = top;
	new_node->vertex = v;
	top = new_node;
}

void list_stack()
{
	printf("Topological order : ");
	node *ptr = top;
	for (; ptr; ptr = ptr->next)
		printf("%d ", ptr->vertex);
	printf("\n");
}
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int src_vertex;
    int dest_vertex;
    struct node *next;
} node;

typedef struct headNode
{
    int count;
    struct headNode *next;
} headNode;

int n;

void initialize(headNode graph[], node *front[], node *rear[]);
void create_queue(headNode graph[], node *rear[]);
void push(int u, int v, headNode graph[], node *rear[]);
void top_sort(headNode graph[], node *rear[]);

int main()
{
    printf("How many vertices in graph : ");
    scanf("%d", &n);

    headNode graph[n];

    node *front[n];
    node *rear[n];

    initialize(graph, front, rear);
    create_queue(graph, rear);
    top_sort(graph, rear);

    return 0;
}

void initialize(headNode graph[], node *front[], node *rear[])
{
    int i;
    for (i = 0; i < n; ++i)
    {
        graph[i].count = 0;
        graph[i].next = NULL;

        front[i] = rear[i] = (node *)&graph[i];
        front[i]->next = rear[i]->next = NULL;
    }
}

void create_queue(headNode graph[], node *rear[])
{
    int i;
    int u, v;

    printf("Please enter predecessor and successor: ( Enter -1 -1 to stop)\n");
    do
    {
        scanf("%d %d", &u, &v);
        if (u >= 0 && v >= 0)
            push(u, v, graph, rear);

    } while (u != -1 && v != -1);
}

void push(int u, int v, headNode graph[], node *rear[])
{
    node *new_node = (node *)malloc(sizeof(node));

    new_node->src_vertex = u;
    new_node->dest_vertex = v;
    new_node->next = NULL;

    graph[v].count++;
    rear[u]->next = new_node;
    rear[u] = new_node;
}

void top_sort(headNode graph[], node *rear[])
{
    int i;
    int get_top;
    int successor;
    int top = -1;

    // check if every vertex has predecessor
    for (i = 0; i < n; ++i)
        if (graph[i].count == 0)
        {
            graph[i].count = top;
            top = i;
        }

    printf("Sorted order : ");
    for (i = 0; i < n; ++i)
    {
        // every vertex has predecessor
        if (top == -1)
        {
            fprintf(stderr, "\nNetwork has a cycle. Sort terminated.\n");
            exit(EXIT_FAILURE);
        }
        else
        {
            get_top = top;
            top = graph[top].count;
            // printf("current top = %d \n", top);
            printf("%d ", get_top);

            // update the count of vertex(i)'s successors
            node *ptr;
            for (ptr = (node *)graph[get_top].next; ptr; ptr = ptr->next)
            {
                successor = ptr->dest_vertex;
                graph[successor].count--;
                if (!graph[successor].count)
                {
                    graph[successor].count = top;
                    top = successor;
                    // printf("update top = %d \n", top);
                }
            }
            // printf("next top = %d \n", top);
        }
    }

    printf("\n");
}
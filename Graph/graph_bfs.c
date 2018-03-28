#include <stdio.h>
#include <stdlib.h>

#define MAX 10

#define exist 1
#define initial 2
#define in_queue 3
#define visited 4

int n;
int adj[MAX][MAX];
int state[MAX];
int queue[MAX];
int front = -1, rear = -1;

void create_graph();
void BFS(int v);
void append(int vertex);
int pop();
int isEmpty();

int main()
{
    create_graph();

    int v;

    for (v = 0; v < n; ++v)
        state[v] = initial;

    printf("Which vertex do u want to start from for BFS ? \n");
    scanf("%d", &v);
    BFS(v);

    return 0;
}

void BFS(int v)
{
    int i;

    append(v);
    state[v] = in_queue;

    while (!isEmpty()){
        v = pop();
        printf("%d ", v);
        state[v] = visited;

        for (i = 0; i < n; ++i){
            if (adj[v][i] == exist && state[i] == initial){
                append(i);
                state[i] = in_queue;
            }
        }
    }
    printf("\n");
}

void append(int vertex)
{
    if (rear == MAX - 1)
        printf("Queue out of range\n");
    else{
        if (front == -1)
            front = 0;
        rear++;
        queue[rear] = vertex;
    }
}

int isEmpty()
{
    if (front == -1 || front > rear)
        return 1;
    else
        return 0;
}

int pop()
{
    if (front == -1 || front > rear)
        printf("Queue out of range\n");

    int head;
    head = queue[front];
    front++;
    return head;
}

void create_graph()
{
    int count, max_edge;
    int src, dest;

    printf("How many vertices ? ");
    scanf("%d", &n);
    max_edge = n * (n - 1);

    for (count = 1; count <= max_edge; ++count){
        printf("Enter edge %d (-1 -1 to quit ) : ", count);
        scanf("%d %d", &src, &dest);

        if ((src == -1) && (dest == -1))
            break;
        else
            adj[src][dest] = exist;
    }
}
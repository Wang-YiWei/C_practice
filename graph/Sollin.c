#include <stdio.h>
#include <string.h>

typedef struct edge
{
    int u, v, weight;
} edge;

unsigned short infinity = ~0;
int n;
int edge_count = 0;
int current_edge_count = 0;
int spanning_edge_count = 0;
int rounds = 0;

void read_input(int graph[][n]);
void initialize(int ancestor[], int current_ancestor[]);
void create_edgelist(int graph[][n], edge edgelist[]);
void sollin(edge edgelist[], edge spanning_list[], edge current_list[], int ancestor[], int current_ancestor[]);
void compare_with_adjacent_vertices(int vertex, edge edgelist[], edge spanning_list[], edge current_list[], int ancestor[], int current_ancestor[]);
int is_edge_in_list(edge list[], int adjacent_min_vertex, int vertex, int spanning);
int is_vertex_in_current_list(edge spanning_list[], int vertex);
void push(int ancestor[], int current_ancestor[], int parent, int child, int adjacent_min_weight, edge current_list[]);
int find_ancestor(int ancestor[], int i);
void union_subtrees(edge edgelist[], edge spanning_list[], edge current_list[], int ancestor[], int current_ancestor[]);
edge extract_min_edge(int vertex, edge edgelist[], edge spanning_list[]);
void transfer(edge spanning_list[], edge current_list[], int ancestor[], int current_ancestor[]);
void print_out(edge spanning_list[]);

int main()
{

    printf("How many vertices in graph : ");
    scanf("%d", &n);

    int max_edge = n * (n - 1);
    int graph[n][n];
    int ancestor[n];
    edge edgelist[max_edge];
    edge spanning_list[n - 1];

    // each round
    int current_ancestor[n];
    edge current_list[n - 1];

    read_input(graph);
    initialize(ancestor, current_ancestor);
    create_edgelist(graph, edgelist);
    sollin(edgelist, spanning_list, current_list, ancestor, current_ancestor);
    print_out(spanning_list);
}

void read_input(int graph[][n])
{
    printf("Enter adjacency matrix : ");
    printf("\n");
    int i, j;
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            scanf("%d", &graph[i][j]);
}

void initialize(int ancestor[], int current_ancestor[])
{
    int i;

    // each vertex's is a subtree containing itself
    for (i = 0; i < n; ++i)
    {
        ancestor[i] = -1;
        current_ancestor[i] = -1;
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

void sollin(edge edgelist[], edge spanning_list[], edge current_list[], int ancestor[], int current_ancestor[])
{
    int i;

    // create subtrees which containing not only itself but also other vertices
    for (i = 0; i < n; ++i)
        compare_with_adjacent_vertices(i, edgelist, spanning_list, current_list, ancestor, current_ancestor);

    transfer(spanning_list, current_list, ancestor, current_ancestor);
    rounds++;

    // union subtrees
    while (spanning_edge_count != n - 1)
    {
        union_subtrees(edgelist, spanning_list, current_list, ancestor, current_ancestor);
        transfer(spanning_list, current_list, ancestor, current_ancestor);
        rounds++;
    }
}

void compare_with_adjacent_vertices(int vertex, edge edgelist[], edge spanning_list[], edge current_list[], int ancestor[], int current_ancestor[])
{
    edge min_edge;
    min_edge = extract_min_edge(vertex, edgelist, spanning_list);
    int adjacent_min_vertex = (min_edge.u == vertex) ? min_edge.v : min_edge.u;

    if (min_edge.weight != infinity)
    {
        // if minimun edge is already in current or spanning list , ignore it .
        if (!is_edge_in_list(current_list, vertex, adjacent_min_vertex, 0) &&
            !is_edge_in_list(spanning_list, vertex, adjacent_min_vertex, 1))
        {
            // add edge in correct direction (a->b , b->c , c->d ...)
            if (!is_vertex_in_current_list(current_list, adjacent_min_vertex))
                push(ancestor, current_ancestor, vertex, adjacent_min_vertex, min_edge.weight, current_list);
            else
                push(ancestor, current_ancestor, adjacent_min_vertex, vertex, min_edge.weight, current_list);
        }
    }
}

edge extract_min_edge(int vertex, edge edgelist[], edge spanning_list[])
{
    int i;
    edge min_edge;
    min_edge.weight = infinity;
    for (i = 0; i < edge_count; ++i)
    {
        // if in spanning list , ignore it
        if (!is_edge_in_list(spanning_list, edgelist[i].u, edgelist[i].v, 1))
        {
            if (edgelist[i].u == vertex)
            {
                if (edgelist[i].weight < min_edge.weight)
                {
                    min_edge.weight = edgelist[i].weight;
                    min_edge.v = edgelist[i].v;
                    min_edge.u = vertex;
                }
            }
            else if (edgelist[i].v == vertex)
            {
                if (edgelist[i].weight < min_edge.weight)
                {
                    min_edge.weight = edgelist[i].weight;
                    min_edge.u = edgelist[i].u;
                    min_edge.v = vertex;
                }
            }
        }
    }

    return min_edge;
}

void union_subtrees(edge edgelist[], edge spanning_list[], edge current_list[], int ancestor[], int current_ancestor[])
{
    int i, j;
    int subtree;
    int min_edges_count = 0;
    int checked[n];
    edge min_edges[n - 1];
    edge min_edge;
    min_edge.weight = infinity;

    memset(checked, 0, sizeof(checked));

    for (i = 0; i < n; ++i)
    {
        if (!checked[i] && ancestor[i] >= 0)
        {
            // check every verticies in this subtree
            subtree = ancestor[i];
            min_edges[min_edges_count++] = extract_min_edge(subtree, edgelist, spanning_list);
            checked[subtree] = 1;

            for (j = 0; j < n; ++j)
            {
                if (ancestor[j] == subtree)
                {
                    min_edges[min_edges_count++] = extract_min_edge(j, edgelist, spanning_list);
                    checked[j] = 1;
                }
            }

            // extract min edge in this subtree
            for (j = 0; j < min_edges_count; ++j)
            {
                if (min_edge.weight > min_edges[j].weight)
                {
                    min_edge.u = min_edges[j].u;
                    min_edge.v = min_edges[j].v;
                    min_edge.weight = min_edges[j].weight;
                }
            }

            // push min edge if not in list yet
            if (!is_edge_in_list(current_list, min_edge.u, min_edge.v, 0) && !is_edge_in_list(spanning_list, min_edge.u, min_edge.v, 1))
            {
                push(ancestor, current_ancestor, min_edge.u, min_edge.v, min_edge.weight, current_list);
            }

            // update for next iteration
            min_edges_count = 0;
            min_edge.weight = infinity;
        }
    }
}

int is_edge_in_list(edge list[], int vertex_src, int vertex_dest, int spanning)
{
    int i;
    int count = (spanning) ? spanning_edge_count : current_edge_count;
    for (i = 0; i < count; ++i)
    {
        if (list[i].u == vertex_src && list[i].v == vertex_dest ||
            list[i].v == vertex_src && list[i].u == vertex_dest)
        {
            return 1;
        }
    }
    return 0;
}

int is_vertex_in_current_list(edge current_list[], int vertex)
{
    int i;
    for (i = 0; i < current_edge_count; ++i)
    {
        if (current_list[i].u == vertex || current_list[i].v == vertex)
            return 1;
    }
    return 0;
}

void push(int ancestor[], int current_ancestor[], int parent, int child, int adjacent_min_weight, edge current_list[])
{
    edge new_edge;
    if (rounds == 0)
    {
        ancestor[child] = find_ancestor(ancestor, parent);
        ancestor[ancestor[child]]--;
        current_ancestor[child] = find_ancestor(current_ancestor, parent);
        current_ancestor[current_ancestor[child]]--;
    }
    else
    {
        int i;
        int ancestor_of_child;
        ancestor_of_child = find_ancestor(current_ancestor, child);
        for (i = 0; i < n; ++i)
        {
            if (current_ancestor[i] == ancestor_of_child)
            {
                current_ancestor[i] = find_ancestor(current_ancestor, parent);
                current_ancestor[current_ancestor[i]]--;
            }
        }

        current_ancestor[find_ancestor(current_ancestor, ancestor_of_child)] = find_ancestor(current_ancestor, parent);
        current_ancestor[find_ancestor(current_ancestor, parent)]--;
    }

    new_edge.u = parent;
    new_edge.v = child;
    new_edge.weight = adjacent_min_weight;
    current_list[current_edge_count++] = new_edge;
}

int find_ancestor(int ancestor[], int vertex)
{
    if (ancestor[vertex] < 0)
        return vertex;
    else
        find_ancestor(ancestor, ancestor[vertex]);
}

void transfer(edge spanning_list[], edge current_list[], int ancestor[], int current_ancestor[])
{
    int i;
    int count = spanning_edge_count;

    // update spanning_list
    for (i = count; i < count + current_edge_count; ++i)
    {
        spanning_list[i] = current_list[i - count];
        spanning_edge_count++;
    }

    // update ancestor
    for (i = 0; i < n; ++i)
        ancestor[i] = current_ancestor[i];
    

    current_edge_count = 0;
}

void print_out(edge spanning_list[])
{
    int i;
    int cost = 0;

    printf("\npaths : \n");
    for (i = 0; i < spanning_edge_count; ++i)
    {
        printf("%d - %d : %d\n", spanning_list[i].u, spanning_list[i].v, spanning_list[i].weight);
    }

    printf("\ncost : \n");
    for (i = 0; i < spanning_edge_count; ++i)
    {
        cost += spanning_list[i].weight;
        printf("%d", spanning_list[i].weight);
        if (i != spanning_edge_count - 1)
            printf(" + ");
        else
            printf(" = %d\n", cost);
    }
}

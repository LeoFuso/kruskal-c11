#include <stdio.h>
#include <stdlib.h>

//Leonardo Fuso  Nuzzo 31500129

typedef struct {
  int node_a;
  int node_b;
  int distance;
} Path;

typedef struct {

  int n_path, n_node;
  Path **path;
  int **nodes;
  int *disjoint_set;

} Graph;

/* Builder functions */
Graph *mount_initial_graph_1 ();
Graph *mount_initial_graph_2 ();
Graph *create_graph (int n_path, int n_node);
void insert_path (Graph *graph, int node_a, int node_b, int distance);

/* Print functions */
void print_graph (Graph *graph);
void print_paths (Graph *graph);
void print_disjoint_set (Graph *graph);

/* structural functions */
int compare (const void *s1, const void *s2);

/* main test */
void execute (Graph *);

/* logic functions */
void kruskal (Graph *);
int find (Graph *, int);
void merge (Graph *, int, int);
void remove_cycle_element (Graph *graph, int, int);

int main (void)
{
    Graph * graph = mount_initial_graph_1();
    execute (graph);
    return 0;
}

void kruskal (Graph *graph)
{
    for (int i = 0; i < graph->n_path; ++i)
    {
        int node_a = graph->path[i]->node_a;
        int node_b = graph->path[i]->node_b;

        int x_parent = find (graph, node_a);
        int y_parent = find (graph, node_b);

        if (x_parent == y_parent)
            remove_cycle_element (graph, node_a, node_b);
        else
            merge (graph, x_parent, y_parent);
    }
}

/* Searches for a Node in Disjoint Set by its index */
int find (Graph *graph, int index)
{
    int found = graph->disjoint_set[index];
    if (found < 0)
        return index;
    else
        return find (graph, found);
}

/* Will merge Nodes of different tress */
void merge (Graph *graph, int node_a, int node_b)
{
    int x_set = graph->disjoint_set[node_a];
    int y_set = graph->disjoint_set[node_b];

    if (x_set < y_set)
    {
        graph->disjoint_set[node_b] = node_a;
        graph->disjoint_set[node_a] = x_set + y_set;
        return;
    }

    graph->disjoint_set[node_a] = node_b;
    graph->disjoint_set[node_b] = x_set + y_set;
}

/* Will remove cycle element from the graph */
void remove_cycle_element (Graph *graph, int node_a, int node_b)
{
    graph->nodes[node_a][node_b] = 0;
    graph->nodes[node_b][node_a] = 0;
}

void execute (Graph * graph)
{
    printf ("\n\nORIGINAL GRAPH: \n");
    printf ("%d NODES \n", graph->n_node);
    printf ("%d PATHS \n", graph->n_path);

    print_graph (graph);
    print_paths (graph);
    print_disjoint_set (graph);

    qsort (graph->path, graph->n_path, sizeof (Path *), compare);

    printf ("\n\nSORTED PATH: \n");
    print_paths (graph);

    kruskal (graph);

    printf ("\n\nKRUSKAL TREE: \n");
    print_graph (graph);
    print_disjoint_set (graph);
}

/* Create an empty Graph */
Graph *create_graph (int n_path, int n_node)
{

    Graph *graph = (Graph *) malloc (sizeof (Graph));

    /* initialize the path number as zero */
    graph->n_path = 0;

    /* the node will never change, so we can keep it like that */
    graph->n_node = n_node;

    /* we need to allocate sufficient memory for all the paths and all the nodes to be inserted */
    graph->path = (Path **) calloc (n_path, sizeof (Path *));
    graph->nodes = (int **) calloc (n_node, sizeof (int *));
    graph->disjoint_set = (int *) calloc (n_node, sizeof (int));

    for (int i = 0; i < n_node; ++i)
    {
        graph->path[i] = (Path *) calloc (n_node, sizeof (Path));
        graph->nodes[i] = (int *) calloc (n_node, sizeof (int));
        graph->disjoint_set[i] = -1;
    }

    return graph;
}

void insert_path (Graph *graph, int node_a, int node_b, int distance)
{
    Path *path = (Path *) calloc (1, sizeof (Path));
    path->node_a = node_a;
    path->node_b = node_b;
    path->distance = distance;

    graph->path[graph->n_path] = path;

    graph->nodes[node_a][node_b] = distance;
    graph->nodes[node_b][node_a] = distance;

    graph->n_path++;
}

Graph * mount_initial_graph_1 ()
{

    int nodes_qtd = 7;
    int path_size = 12;

    Graph *graph = create_graph (path_size, nodes_qtd);

    //0 --> 2 = 5
    insert_path (graph, 0, 2, 5);

    //0 --> 3 = 8
    insert_path (graph, 0, 3, 8);

    //2 --> 3 = 10
    insert_path (graph, 2, 3, 10);

    //2 --> 1 = 16
    insert_path (graph, 2, 1, 16);

    //2 --> 4 = 3
    insert_path (graph, 2, 4, 3);

    //3 --> 4 = 2
    insert_path (graph, 3, 4, 2);

    //3 --> 5 = 18
    insert_path (graph, 3, 5, 18);

    //4 --> 1 = 30
    insert_path (graph, 4, 1, 30);

    //4 --> 5 = 12
    insert_path (graph, 4, 5, 12);

    //4 --> 6 = 14
    insert_path (graph, 4, 6, 14);

    //1 --> 6 = 26
    insert_path (graph, 1, 6, 26);

    //5 --> 6 = 4
    insert_path (graph, 5, 6, 4);

    return graph;
}

Graph *mount_initial_graph_2 ()
{
    int nodes_qtd = 8;
    int path_size = 10;

    Graph *graph = create_graph (path_size, nodes_qtd);

    insert_path (graph, 0, 4, 4);
    insert_path (graph, 0, 3, 6);
    insert_path (graph, 1, 3, 7);
    insert_path (graph, 1, 2, 3);
    insert_path (graph, 2, 4, 8);
    insert_path (graph, 2, 6, 3);
    insert_path (graph, 2, 5, 9);
    insert_path (graph, 4, 6, 5);
    insert_path (graph, 4, 7, 5);
    insert_path (graph, 3, 7, 7);

    return graph;
}

void print_graph (Graph *graph)
{
    printf ("\n");
    for (int i = 0; i < graph->n_node; i++)
    {
        for (int j = 0; j < graph->n_node; j++)
        {
            printf ("%3d ", graph->nodes[j][i]);
        }
        printf ("\n");
    }
    printf ("\n");
}

void print_paths (Graph *graph)
{
    printf ("\n");
    for (int i = 0; i < graph->n_path; ++i)
    {
        Path *p = graph->path[i];
        printf ("\n%d --> %d = %d", p->node_a, p->node_b, p->distance);
    }
    printf ("\n");
}

void print_disjoint_set (Graph *graph)
{
    printf ("\n\nDISJOINT SET: \n");
    for (int i = 0; i < graph->n_node; i++)
    {
        printf (" [ %2d ] ", graph->disjoint_set[i]);
    }
    printf ("\n");
    for (int i = 0; i < graph->n_node; i++)
    {
        printf ("   %2d   ", i);
    }
    printf ("\n");
}

int compare (const void *s1, const void *s2)
{
    Path *p1 = *(Path **) s1;
    Path *p2 = *(Path **) s2;

    if (p1->distance != p2->distance)
        return p1->distance - p2->distance;
    else if (p1->node_a != p2->node_a)
        return p1->node_a - p2->node_a;
    else
        return p1->node_b - p2->node_b;
}
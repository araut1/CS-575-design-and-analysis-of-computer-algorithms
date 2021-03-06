#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#define DEBUG

// GLobal variable will go here
int no_of_vertices = -1;
int size_of_heap;
int adj_matrix[10][10];

//Data Structure for graph representation
struct edge
{
    int source, dest, weight;
};

struct graph
{
    int no_of_vertices, no_of_edges;
    struct edge *edges;
};

struct set
{
    int root;
    int height;
};

//Data Structure to hold cost and vertex for prim's algo
struct cost_vertex
{
    int cost;
    int vertex;
};

// creates graph
void initialiseGraph()
{
    int i, j, temp;
    no_of_vertices = rand() % 6 + 5;
    for (i = 0; i < no_of_vertices; i++)
    {
        for (j = 0; j <= i; j++)
        {
            if (i == j)
            {
                adj_matrix[i][j] = 0;
            }
            else
            {
                temp = rand() % 10 + 1;
                adj_matrix[i][j] = temp;
                adj_matrix[j][i] = temp;
            }
        }
    }
}

// function to pront the graph to console
void printGraph()
{
    int i, j;
    printf("\nNumber of vertices: %d\n", no_of_vertices);
    printf("Adjacency matrix:\n");
    for (i = 0; i < no_of_vertices; i++)
    {
        for (j = 0; j < no_of_vertices; j++)
        {
            printf("%2d ", adj_matrix[i][j]);
        }
        printf("\n");
    }
}

//  Function used if Implementing Prim’s minimum spanning tree algorithm by 
//  programing priority queue either as array
// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int min_key(int *key, int *mst)
{
    int min = INT_MAX, min_index, i;
    for (i = 0; i < no_of_vertices; i++)
    {
        if (mst[i] == 0 && key[i] < min)
        {
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}

//print MST for prim's algo from  stored in parent[]
void printMST(int *parent)
{
    int i, total = 0;
    printf("\nMST edges:\n");
    
    // index 2nd is started from as parent[0] will always be zero
    for (i = 1; i < no_of_vertices; i++)
    {
        printf("Edge: %d - %d\t Weight: %d\n", i, parent[i], adj_matrix[i][parent[i]]);
    }   
}

// Heap Data Structure used for Prim's algo
void swap(struct cost_vertex *arr, int i, int j)
{
    struct cost_vertex temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// builts a binary tree such that, the data contained in each node is less than (or equal to) the data in that node's children
void min_heapify(struct cost_vertex *arr, int size, int current)
{
    int left = 2 * current + 1;
    int right = left + 1;
    int smallest = current;
    if (left < size && arr[left].cost < arr[smallest].cost)
    {
        smallest = left;
    }
    if (right < size && arr[right].cost < arr[smallest].cost)
    {
        smallest = right;
    }
    if (smallest != current)
    {
        swap(arr, smallest, current);
        min_heapify(arr, size, smallest);
    }
}

// perform heap sort
void heapSort(struct cost_vertex *arr, int size)
{
    int i, j, current_size_heap;
    size_of_heap = size;
    for (i = size / 2; i >= 0; i--)
    {
        min_heapify(arr, size, i);
    }

}

//arr reference to element with reduced key
void decrease_key(struct cost_vertex *arr, int i)
{
    int parent = ((i - 1) / 2);
    
    if (arr[parent].cost > arr[i].cost)
    {
        swap(arr, parent, i);
    }
    else
    {
        return;
    }
    if (i == 0)
    {
        return;
    }
    else
    {
        decrease_key(arr, parent);
    }
}

int delete_min(struct cost_vertex *heap)
{
    int min = heap[0].vertex;
    heap[0] = heap[--size_of_heap];
    min_heapify(heap, size_of_heap, 0);
    return min;
}

int find_and_update_cost(struct cost_vertex *arr, int vertex_to_find, int new_cost)
{
    int i = 0;
    for (i = 0; i < size_of_heap; i++)
    {
        if (arr[i].vertex == vertex_to_find)
        {
            arr[i].cost = new_cost;
            return i;
        }
    }
}

void printheap(struct cost_vertex *heap)
{
    int i;
    printf("vertex");
    for (i = 0; i < size_of_heap; i++)
    {
        printf("%d ", heap[i].vertex);
    }
    printf("\n==cost");
    for (i = 0; i < size_of_heap; i++)
    {
        printf("%d ", heap[i].cost);
    }
}

int find_vertex_index(struct cost_vertex *heap, int vertex_to_find)
{
    int i;
    for (i = 0; i < size_of_heap; i++)
    {
        if (heap[i].vertex == vertex_to_find)
        {
            return i;
        }
    }
}

//using heap prim's algo
void primsMSTheap()
{
    int i, j, u;
    int heap_loc_to_reduce;
    int parent[no_of_vertices];
    struct cost_vertex heap[no_of_vertices];
    int mst[no_of_vertices];
    memset(parent, -1, no_of_vertices * sizeof(int));
    memset(mst, 0, no_of_vertices * sizeof(int)); //0 false, 1 true
    for (i = 0; i < no_of_vertices; i++)
    {
        heap[i].vertex = i;
        heap[i].cost = INT_MAX;
    }
    
    //set starting point at vertex 0
    heap[0].cost = 0;
    heapSort(heap, no_of_vertices);
    parent[0] = -1;
    while (size_of_heap != 0)
    {

        u = delete_min(heap);
        for (j = 0; j < no_of_vertices; j++)
        {
            if (adj_matrix[u][j] != 0 && adj_matrix[u][j] < heap[find_vertex_index(heap, j)].cost && mst[j] == 0)
            {
                parent[j] = u;
                heap_loc_to_reduce = find_and_update_cost(heap, j, adj_matrix[u][j]);
                decrease_key(heap, heap_loc_to_reduce);
            }
        }
        mst[u] = 1;
    }
    printMST(parent);
}

//using array prim's algo
void primsMSTarray()
{
    int i, j, u;
    int parent[no_of_vertices];
    int key[no_of_vertices];
    int mst[no_of_vertices];
    memset(parent, 0, no_of_vertices * sizeof(int));
    memset(mst, 0, no_of_vertices * sizeof(int)); //0 false, 1 true
    
    for (i = 0; i < no_of_vertices; i++)
    {
        key[i] = INT_MAX;
    }

    //set starting point at vertex 0
    key[0] = 0;
    parent[0] = -1;
    for (i = 0; i < no_of_vertices - 1; i++)
    {
        u = min_key(key, mst);
        for (j = 0; j < no_of_vertices; j++)
        {
            if (adj_matrix[u][j] != 0 && mst[j] == 0 && adj_matrix[u][j] < key[j])
            {
                parent[j] = u;
                key[j] = adj_matrix[u][j];
            }
        }
        mst[u] = 1;
    }
    printMST(parent);
}

// Kruskal's MST algo implementation
struct graph *createGraph(int v, int e)
{
    struct graph *g = NULL;
    g = (struct graph *)malloc(sizeof(struct graph));
    if (g == NULL)
    {
        return NULL;
    }
    g->no_of_vertices = v;
    g->no_of_edges = e;
    g->edges = (struct edge *)malloc(sizeof(struct edge) * e);
    return g;
}

// find3 as discussed in notes
int find3(struct set *sets, int i)
{

    if (sets[i].root != i)
    {
        sets[i].root = find3(sets, sets[i].root);
    }
    return sets[i].root;
}

// union3 as discussed in notes
void union3(struct set *sets, int a, int b)
{
    int a_root = find3(sets, a);
    int b_root = find3(sets, b);
    if (sets[a_root].height < sets[b_root].height)
    {
        sets[a_root].root = b_root;
    }
    else if (sets[a_root].height > sets[b_root].height)
    {
        sets[b_root].root = a_root;
    }
    else
    {
        sets[b_root].root = a_root;
        sets[a_root].height++;
    }
}

void print_edges(struct edge *edges, int n)
{
    int i;
    printf("Source Dest Weight\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\n", edges[i].source, edges[i].dest, edges[i].weight);
    }
}

void convert_adjmatrix_to_edges(struct graph *graph)
{
    int i = 0, j = 0, k = 0;
    for (i = 0; i < no_of_vertices; i++)
    {
        for (j = 0; j < i; j++)
        {
            {
                graph->edges[k].source = i;
                graph->edges[k].dest = j;
                graph->edges[k].weight = adj_matrix[i][j];
                k++;
            }
        }
    }
}

int comparator(const void *x, const void *y)
{
    int x_weight = ((struct edge *)x)->weight;
    int y_weight = ((struct edge *)y)->weight;
    return x_weight > y_weight;
}


void kruskalsMST()
{
    int i, j, k;
    int root_a, root_b;
    struct edge current_edge;
    struct graph *graph = createGraph(no_of_vertices, (no_of_vertices * (no_of_vertices - 1)) / 2);
    if (graph == NULL)
    {
        printf("Memory allocation failed\n");
        exit(-1);
    }
    convert_adjmatrix_to_edges(graph);
    struct edge MST[no_of_vertices];
    qsort(graph->edges, graph->no_of_edges, sizeof(struct edge), comparator);
    struct set sets[graph->no_of_vertices];
    for (i = 0; i < graph->no_of_vertices; i++)
    {
        sets[i].root = i;
        sets[i].height = 0;
    }
    j = 0; //iterate through sorted edges
    k = 0; //result array
    for (i = 0; i < graph->no_of_edges && j < (graph->no_of_vertices - 1); i++)
    { 
        //iterate for MST
        current_edge = graph->edges[i];
        root_a = find3(sets, current_edge.source);
        root_b = find3(sets, current_edge.dest);

        if (root_a != root_b)
        {
            MST[j] = current_edge;
            union3(sets, root_a, root_b);
            j++;
        }
    }
    printf("\nEdges in MST\n");
    print_edges(MST, no_of_vertices - 1);
}

// GUI and driver utilities
void printDialog()
{
    printf("\nSelect minimum-spanning-tree Algorithm:\n");
    printf("1. Prim's MST\n");
    printf("2. Kruskal's MST\n");
    printf("3. Exit\n");
    printf("Enter  your choice:\n\n");
}

int getInput()
{
    int algorithmId = -1;
    char ch;
    if (scanf("%d", &algorithmId) != 1)
    {
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
        printf("\nPlease Enter a number!\n");
        return getInput();
    }
    return algorithmId;
}

int validateChoice(int algorithmId)
{
    // error for out of choice number
    if (algorithmId <= 0 || algorithmId >= 4)
    {
        return 1;
    }
    return 0;
}

// user wants to exit
void checkForExit(int algorithmId)
{
    if (algorithmId == 3)
    {
        printf("\nExiting...\n");
        exit(0);
    }
}

// driver program to test MST algo
// *** didn’t pass any parameter to main() function
int main(void)
{
    int algorithmId = -1; //Algorithm selection 
    srand(time(NULL));
    
    while (1)
    {
        printDialog();
        algorithmId = getInput();
        
        if (validateChoice(algorithmId))
        {
            printf("\nImproper Input! Enter the choice again!\n\n");
            continue;
        }

        checkForExit(algorithmId);
        
        // if everything is validated
        initialiseGraph();
        printGraph();
        switch (algorithmId)
        {
        case 1:
            printf("\nPrim’s minimum spanning tree algorithm selected!\n");
            primsMSTheap(); //  Prim’s minimum spanning tree algorithm by programing priority queue either as heap data structure
            //primsMSTarray(); //  Prim’s minimum spanning tree algorithm by programing priority queue either as array data structure
            break;
        case 2:
            printf("\nKruskal’s minimum spanning tree algorithm selected!\n");
            kruskalsMST();
            break;

        default:
            printf("Improper Input!\n");
            break;
        }
    }
    return 0;
}

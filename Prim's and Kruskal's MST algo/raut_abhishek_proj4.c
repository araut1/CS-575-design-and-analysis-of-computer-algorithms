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

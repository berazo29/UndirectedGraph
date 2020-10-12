#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;
};

// A structure to represent a graph. A graph
// is an array of adjacency lists.
// Size of array will be V (number of vertices
// in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};

// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists.  Size of
    // array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by
    // making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is
    // added to the adjacency list of src.  The node
    // is added at the beginning
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since graph is undirected, add an edge from
    // dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// A utility function to print the adjacency list
// representation of graph
void printGraph(struct Graph* graph, char **arr)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %s\n head ", arr[v]);
        while (pCrawl)
        {
            printf("-> %s", arr[pCrawl->dest]);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

int letterToNumberMapping(char **str,int size, char *input){
    for (int i = 0; i < size; i++){
        if ( strcmp(str[i], input ) == 0){
            return i;
        }
    }
    return -1;
}

void deleteArray(char **str, int size){
    // Deallocate the memory
    for ( int i = 0; i < size; i++ )
    {
        free(str[i]);
    }
    free(str);
}

void deleteGraph(struct Graph *g, int V){
    for (int i=0; i < V; i++ ){
        free(g->array[i].head);
    }
    free(g);
}

int counterAdjNodes(struct Graph *g, int V, char d){

    // Check for degree
    if ( d != 'd'){
        return -1;
    }
    // Graph is empty
    if ( g == NULL){
        return -1;
    }

    int counter = 0;
    // Pointer to the linked list of the graph
    struct AdjList ptr = g->array[V];
    if ( ptr.head == NULL){
        return -1;
    }
    while ( ptr.head != NULL){
        counter++;
        ptr.head = ptr.head->next;
    }
    return counter;
}

int main( int argc, char *argv[argc+1]) {

    //File name from arguments
    if (argc != 3 ){
        printf("no file");
        return EXIT_SUCCESS;
    }

    // Declare the read file
    FILE *fp;

    fp = fopen( argv[1], "r");

    // Check if the file is empty
    if ( fp == NULL ){
        printf("Unable to read");
        return EXIT_SUCCESS;
    }
    // Get the data FREE later
    int size;
    fscanf( fp, "%d", &size );
    printf("%d\n", size);
    char **indexArr = malloc(size * sizeof(char *));

    for (int i = 0; i < size; ++i) {
        char tmp[10];
        unsigned len = strlen(tmp);
        indexArr[i] = malloc(len);
        fscanf( fp, "%s", tmp );
        strcpy(indexArr[i], tmp);
        printf("a[%d]:%s\n",i,indexArr[i]);
    }
    char tmp0[10];
    char tmp1[10];
    struct Graph* graph = createGraph(size);
    while (fscanf( fp, "%s %s", tmp0, tmp1 ) != EOF) {
        int indexMapSource = letterToNumberMapping(indexArr,size, tmp0);
        int indexMapDestination = letterToNumberMapping(indexArr,size, tmp1);
        addEdge(graph, indexMapSource, indexMapDestination);
    }

    // Close the file and destroy memory allocations
    fclose(fp);

    // NEXT CODE
    printf("TRUE d %d",counterAdjNodes(graph,1,'d'));

    // print the adjacency list representation of the above graph
    printGraph(graph,indexArr);

    // Deallocate memory and graph
    deleteArray(indexArr,size);
    deleteGraph(graph,size);




    return EXIT_SUCCESS;
}

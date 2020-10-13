#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

struct AdjList
{
    struct AdjListNode *head;
};

struct Graph
{
    int V;
    struct AdjList* array;
};

// Create a new adj list node
struct AdjListNode* newAdjListNode(int vertexDestination)
{
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = vertexDestination;
    newNode->next = NULL;
    return newNode;
}

// Creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    // Allocate memory for an  array
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

    // Initialized adjancent
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int u, int v){
    // Create a new node and add it on the beginning
    struct AdjListNode* newNode = newAdjListNode(v);
    newNode->next = graph->array[u].head;
    graph->array[u].head = newNode;

    // Adds an edge from v to u in the graph
    newNode = newAdjListNode(u);
    newNode->next = graph->array[v].head;
    graph->array[v].head = newNode;
}

// Print the graph unsorted
void printGraph(struct Graph* g, char **arr)
{
    for (int v = 0; v < g->V; ++v){
        struct AdjListNode* ptr = g->array[v].head;
        printf("\n Adjacency list of vertex %s %d\n head ", arr[v], v);
        while (ptr){
            printf("-> %s %d", arr[ptr->dest], ptr->dest );
            ptr = ptr->next;
        }
        printf("\n");
    }
}

int letterToNumberMapping(char **matrix,int size, char *input){
    for (int i = 0; i <= size; i++){
        if ( strcmp(matrix[i], input ) == 0){
            return i;
        }
    }
    return -1;
}

void deleteArray(char **arr, int size){
    // Deallocate the memory
    for ( int i = 0; i < size; i++ )
    {
        free(arr[i]);
    }
    free(arr);
}

void deleteGraph(struct Graph *g, int V){
    for (int i=0; i < V; i++ ){
        free(g->array[i].head);
    }
    free(g);
}

int getDegreeVertex(struct Graph *g, int V, char *option){

    // Check for degree
    if ( strcmp(option,"d") != 0){
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
        return counter;
    }
    while ( ptr.head != NULL){
        counter++;
        ptr.head = ptr.head->next;
    }
    return counter;
}

// Create a 2D array
char **createArray(int row, int col){
    // Allocate memory for 2D array
    char **arr = (char**) malloc(row*sizeof(char*));
    for ( int i = 0; i < row; i++ ){
        arr[i] = (char*) malloc(col*sizeof(char));
    }
    return arr;
}

// Return a sorted adjacent list from the graph at V vertex populated by letters Nodes
char** sortedAdjList(struct Graph *g, int V, char **matrix){

    // Error check
    if (V < 0){
        return NULL;
    }
    if ( g == NULL){
        return NULL;
    }

    // Create and initialize an array and degree as the size
    int degree = getDegreeVertex(g,V,"d");
    char **arr = createArray(degree,10);
    struct AdjListNode* head = g->array[V].head;
    int i = 0;

    if ( head == NULL){
        return NULL;
    }
    // Traverse the adjacent list and copy to the matrix
    while (head){
        strcpy(arr[i], matrix[head->dest]);
        i++;
        head = head->next;
    }

    // Sort the adjacent list lexicographically
    char temp[10];
    for(int p=0;p<degree-1;p++){
        for(int q=p+1;q<degree;q++){
            if(strcmp(arr[p],arr[q])>0){
                strcpy(temp,arr[p]);
                strcpy(arr[p],arr[q]);
                strcpy(arr[q],temp);
            }
        }
    }
    return arr;
}

// Prints the lexicographically sorted adjacent list from the graph
void printAdjVertexSorted( struct Graph *g, int V, char **indexArr){
    char **sortedlist = sortedAdjList(g, V,indexArr);
    //printf("degree: %d\n", getDegreeVertex(graph,vertex,"d"));
    for (int i = 0; i < getDegreeVertex(g,V,"d"); ++i) {
        printf("%s ",sortedlist[i]);
    }
    printf("\n");
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
    //printf("SIZE LINKEDLIST%d\n", size);
    char **indexArr = malloc(size * sizeof(char *));

    for (int i = 0; i < size; ++i) {
        char tmp[10];
        unsigned len = strlen(tmp);
        indexArr[i] = malloc(len);
        fscanf( fp, "%s", tmp );
        strcpy(indexArr[i], tmp);
        //printf("a[%d]:%s\n",i,indexArr[i]);
    }
    char tmp0[10];
    char tmp1[10];
    struct Graph* graph = createGraph(size);
    while (fscanf( fp, "%s %s", tmp0, tmp1 ) != EOF) {
        int indexMapSource = letterToNumberMapping(indexArr,size, tmp0);
        int indexMapDestination = letterToNumberMapping(indexArr,size, tmp1);
        addEdge(graph, indexMapSource, indexMapDestination);
    }

    // Close the file 1
    fclose(fp);

    // NEXT FILE
    fp = fopen( argv[2], "r");
    if ( fp == NULL ){
        printf("Unable to read");
        return EXIT_SUCCESS;
    }
    while ( fscanf( fp, "%s %s", tmp0, tmp1 ) != EOF ){
        char *option = tmp0;
        int vertex = letterToNumberMapping(indexArr,size,tmp1);
        if ( vertex < 0 ){
            printf("Error Vertex does not exist\n");
            continue;
        }
        if (strcmp(option,"d") == 0){
            printf("%d\n", getDegreeVertex(graph, vertex, option));
        } else if (strcmp(option,"a") == 0){
            printAdjVertexSorted(graph,vertex,indexArr);
        } else{
            printf("Error input format\n");
        }

    }
    // Close the file 2
    fclose(fp);

    //printGraph(graph,indexArr);

    // Deallocate memory and graph
    deleteArray(indexArr,size);
    deleteGraph(graph,size);

    return EXIT_SUCCESS;
}

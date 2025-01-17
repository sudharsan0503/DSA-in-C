#include<stdio.h>
#include<stdlib.h>
#define max 10

struct node{
    int data;
    struct node* next;
};

struct list{
    struct node* head;
};

struct graph{
    int V;
    struct list* array;
};

struct stack{
    int top;
    int capacity;
    int* array;
};

typedef struct node NODE;
typedef struct list LIST;
typedef struct graph GRAPH;
typedef struct stack STACK;

NODE* createnode(int x){
    NODE* nn=(NODE*)malloc(sizeof(NODE));
    nn->data=x;
    nn->next=NULL;
    return nn;
}

GRAPH* creategraph(int vertices){
    GRAPH* g=(GRAPH*)malloc(sizeof(GRAPH));
    g->V=vertices;
    g->array=(LIST*)malloc(vertices*sizeof(LIST)); //creating an array of size vertices

    //initializing list as empty and setting head as null
    for(int i=0;i<vertices;i++){
        g->array[i].head=NULL;
    }
    return g;
}

void addedge(GRAPH* g,int src,int dest){
    NODE* nn=createnode(dest);
    nn->next= g->array[src].head;
    g->array[src].head=nn;
    
    nn=createnode(src);
    nn->next=g->array[dest].head;
    g->array[dest].head=nn;
}

STACK* createstack(int capacity){
    STACK* S=(STACK*)malloc(sizeof(STACK));
    S->capacity=capacity;
    S->top=-1;
    S->array=(int*)malloc((S->capacity*sizeof(int)));//very very important S
    return S;
}

int isfull(STACK* S){
    return S->top == S->capacity -1;
}

int isempty(STACK* S){
    return S->top == -1;
}

void push(STACK* S, int item) {
    if (isfull(S)){
        return;
    }
    S->array[++S->top] = item;
}

int pop(STACK* S){
    if(isempty(S)){
        return -1;
    }
    return S->array[S->top--];
}

void dfs(GRAPH* g,int startvertex){
     //CReating a stack
     STACK* S=createstack(startvertex);
    
    //Marking visted as 0 for all vertices
    int* visit=(int*)malloc(g->V*sizeof(int));   //important g->v
    for(int i=0;i<g->V;i++){
        visit[i]=0;
    }
    push(S,startvertex);

    while (!isempty(S)) {
        // Pop a vertex from stack and print it
        startvertex = pop(S);

        // Stack may contain same vertex twice. So we need to print the popped item only if it is not visited.
        if (!visit[startvertex]) {
            printf("%d ", startvertex);
            visit[startvertex] = 1;
        }

        // Get all adjacent vertices of the popped vertex v. If an adjacent has not been visited, then push it to the stack.
        NODE* temp = g->array[startvertex].head;
        while (temp) {
            if (!visit[temp->data]){
                push(S, temp->data);
            }
            temp = temp->next;
        }
    }
    free(visit);
    free(S->array);
    free(S);
}

int main() {
    int V, E;          // Number of vertices and edges


    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    // Create a graph
    GRAPH* graph = creategraph(V);

    printf("Enter the edges (source destination):\n");
    for (int i = 0; i < E; ++i) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        addedge(graph, src, dest);
    }

    int startingVertex;
    printf("Enter the starting vertex for DFS traversal: ");
    scanf("%d", &startingVertex);

    printf("Depth First Traversal (starting from vertex %d): ", startingVertex);
    dfs(graph, startingVertex);

    // Free allocated memory
    for (int i = 0; i < V; ++i) {
        NODE* temp = graph->array[i].head;
        while (temp) {
            NODE* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->array);      /*Deallocate once used*/
    free(graph);

    return 0;
}

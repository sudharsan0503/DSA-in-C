#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_vertices 10
#define max_filename 100

struct node{
    int data;
    struct node* next;
};

struct adjlist{
    struct node* head;
};

struct graph{
    int V;
    struct adjlist* array;
};

typedef struct node NODE;
typedef struct adjlist LIST;
typedef struct graph GRAPH;

NODE* createnode(int x){
    NODE* nn=(NODE*)malloc(sizeof(NODE));
    nn->data=x;
    nn->next=NULL;
    return nn;
}

GRAPH* creategraph(int vertices){
    GRAPH* g=(GRAPH*)malloc(sizeof(GRAPH));
    g->V=vertices;
    g->array=(LIST*)malloc(vertices*sizeof(LIST));
    for(int i=0;i<vertices;i++){
        g->array[i].head=NULL;
    }
    return g;
}

void addedge(GRAPH* g,int src,int dest){
    NODE* nn=createnode(dest);
    nn->next=g->array[src].head;
    g->array[src].head=nn;

    nn=createnode(src);
    nn->next=g->array[dest].head;
    g->array[dest].head=nn;    
}

void printgraph(GRAPH* g){
    for(int i=0;i<g->V;i++){
        NODE* current=g->array[i].head;
        printf("Adjacency list of vertex %d:\n head",i);
        while(current){
            printf("->%d",current->data);
            current=current->next;
        }
    printf("\n");
    }
}

void storegraph(GRAPH* g,const char* filename){
    FILE* fh;
    fh=fopen(filename,"w");
     if(fh!=NULL){
        fprintf(fh,"%d\n",g->V);
        for(int i=0;i<g->V;i++){
            NODE* current=g->array[i].head;
            fprintf(fh,"%d:",i);
            while(current){
                fprintf(fh,"%d->",current->data);
                current=current->next;
            }
            fprintf(fh,"\n");
        }
      fclose(fh);
      printf("Graph stored successfully\n");
    }
    else{
        printf("Error in opening the file\n");
    }
}

GRAPH* loadgraph(const char* filename){
    FILE* fh=fopen(filename,"r");

    if(fh!=NULL){
          int V;
          fscanf(fh,"%d",&V);
          
          GRAPH* g=creategraph(V);

          int v,dest;             //v-vertex number,dest-destination vertex and c can be ':' or \n
          char c;

          while(!feof(fh)){
                fscanf(fh,"%d%c",&v,&c);
                while(c != '\n'){    //note only single quotes
                    fscanf(fh,"%d%c",&dest,&c);
                    addedge(g,v,dest);
                }
          }
    fclose(fh);
    printf("Graph loaded succesfully in %s\n",filename);
    printgraph(g);
    return g;
    }
    else{
          printf("Error in opening the file\n");
          return NULL;
    }
}

/*GRAPH* loadGraphFromFile(const char* filename) {
    FILE* fh = fopen(filename, "r");
    if (fh == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(1);
    }

    int V;
    fscanf(fh, "%d", &V);

    struct Graph* graph = createGraph(V);

    int src, dest;
    while (fscanf(fh, "%d:", &src) != EOF) {
        while (fscanf(fh, " %d", &dest) && dest != '\n') {
            addEdge(graph, src, dest);
        }
    }

    fclose(fh);
    return graph;
}*/

int main() {
    int choice;
    int numVertices, numEdges;
    char filename[max_filename];
    GRAPH* graph = NULL;

    do {
        printf("\nMenu:\n");
        printf("1. Create graph\n");
        printf("2. Print graph\n");
        printf("3. Store graph to file\n");
        printf("4. Load graph from file\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of vertices in the graph: ");
                scanf("%d", &numVertices);
                graph = creategraph(numVertices);
                printf("Enter the number of edges: ");
                scanf("%d", &numEdges);
                printf("Enter the edges (source destination):\n");
                for (int i = 0; i < numEdges; ++i) {
                    int src, dest;
                    scanf("%d %d",&src,&dest);
                    addedge(graph, src, dest);
                }
                break;
            case 2:
                if (graph != NULL) {
                    printf("Graph:\n");
                    printgraph(graph);
                } else {
                    printf("Graph is not created yet.\n");
                }
                break;
            case 3:
                if (graph != NULL) {
                    printf("Enter the filename to store the graph: ");
                    scanf("%s", filename);
                    storegraph(graph, filename);
                } else {
                    printf("Graph is not created yet.\n");
                }
                break;
            case 4:
                printf("Enter the filename to load the graph from: ");
                scanf("%s", filename);
                graph=loadgraph(filename);
                break;
            case 5:
                printf("Exiting...\n");
                break;
        }
    } while (choice != 5);
return 0;
}
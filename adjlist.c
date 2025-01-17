#include<stdio.h>
#include<stdlib.h>

struct adjnode{
    int dest;                     
    struct adjnode* next;
};

struct adjlist{
    struct adjnode* head;
};

struct adjgraph{
      int V;
      struct adjlist* array;
};

typedef struct adjnode NODE;
typedef struct adjlist LIST;
typedef struct adjgraph GRAPH;

NODE* createadjnode(int dest){
    NODE* nn=(NODE*)malloc(sizeof(NODE));
    nn->dest=dest;
    nn->next=NULL;
    return nn;
}

GRAPH* creategraph(int V){
    GRAPH* graph=(GRAPH*)malloc(sizeof(GRAPH));
    graph->V=V;
    graph->array=(LIST*)malloc(V*sizeof(LIST));
    for(int i=0;i<V;i++){                        //initialization of head to null befor assignment
        graph->array[i].head=NULL;
    }
    return graph;
}

void addedge(GRAPH* graph,int src,int dest){
    NODE* nn;

    nn=createadjnode(dest);
    nn->next = graph->array[src].head;
    graph->array[src].head =nn;

    nn=createadjnode(src);
    nn->next=graph->array[dest].head;
    graph->array[dest].head=nn;
}

void printgraph(GRAPH* g){
    int v;
    for(v=0;v<g->V;v++){                  //note it is '<' and not '='
        NODE* temp=g->array[v].head;
        printf("Adjacency list of vertex %d\n head",v);
        while(temp!=NULL){
            printf("->%d",temp->dest);
            temp=temp->next;
        }
        printf("\n");
    }
}

int main(){
    int V,E,i,source,dest;
    
    printf("Enter number of vertices:");
    scanf("%d",&V);
    printf("Enter number of edges:");
    scanf("%d",&E);

    GRAPH* graph= creategraph(V);
    printf("Enter the edges in the form of source and destination:");
    for(i=0;i<E;i++){
        scanf("%d %d",&source,&dest);
        addedge(graph,source,dest);
    }

    printgraph(graph);
    
    return 0;
}
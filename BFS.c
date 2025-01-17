#include<stdio.h>
#include<stdlib.h>
#define max 50

struct node{
    int data;
    struct node* next;
};

struct graph{
    int numberofvertices;
    int* number;
    char** label;   //important **
    int* visit;
    int* dist;
    struct node** adjlist;  //important **
};

struct queue{
     int size[max];
     int front;
     int rear;
};

typedef struct node NODE;
typedef struct graph GRAPH;
typedef struct queue QUEUE;

QUEUE* createqueue(){
    QUEUE* q=(QUEUE*)malloc(sizeof(QUEUE));
    q->front=-1;
    q->rear=-1;
    return q;
}

void enqueue(QUEUE* q,int val){
       if(q->rear == max-1){           //cheeck q is full
          printf("Queue is full\n");
       }
       else{
           if(q->front == -1){         //if first element then update front
              q->front=0;
           }
           q->rear++;                //increment rear to add val at that position
           q->size[q->rear]=val;   //value is added
       }
}

int isempty(QUEUE* q){
    return q->rear==-1;
}

int dequeue(QUEUE* q){
     int store_variable;
     if(isempty(q)){
        printf("Queue is empty\n");
        store_variable=-1;
     }
     else{
     store_variable=q->size[q->front];
     q->front++;
     if(q->front>q->rear){
        q->front=q->rear=-1;
      }
     }
    return store_variable;
}

NODE* createnode(int x){
    NODE* nn=(NODE*)malloc(sizeof(NODE));
    nn->data=x;
    nn->next=NULL;
    return nn;
}

GRAPH* creategraph(int V){

    GRAPH* g=(GRAPH*)malloc(sizeof(GRAPH));
    g->numberofvertices=V;
    g->number=(int*)malloc(V*sizeof(int*));
    g->label=(char**)malloc(V*sizeof(char**));
    g->visit=(int*)malloc(V*sizeof(int*));
    g->dist=(int*)malloc(V*sizeof(int*));
    g->adjlist=(NODE**)malloc(V*sizeof(NODE*)); //NOTE: ** in node and V*size...

    //Initialization of everything to null
    for(int i=0;i<V;i++){
         g->number[i]=i;          // Assigning numbers from 0 to vertices-1
         g->label[i]=NULL;        // Initialize labels to NULL
         g->visit[i]=0;           // Initialize visit status to 0
         g->dist[i]=-1;            // Initialize distance to -1 (indicating unreachable)
         g->adjlist[i]=NULL;
    }
     return g;
}

void addedge(GRAPH* g,int src,int dest){
    NODE* nn=createnode(dest);
    nn->next=g->adjlist[src];
    g->adjlist[src]=nn;
    
    nn=createnode(src);
    nn->next=g->adjlist[dest];
    g->adjlist[dest]=nn;
}

void bfs(GRAPH* g, int start_vertex){
       NODE* temp;
       int visit[max]={0};        //creating a array of size max and assign visit as 0 for everything
       QUEUE* q = createqueue();

       visit[start_vertex]=1; //marking the current node as visited and enqueueing it.eg:if st_ver=4 then q[4]=1
       enqueue(q,start_vertex);
       g->dist[start_vertex]=0; //starting vertex has distance 0

       while(!isempty(q)){
          
          // Dequeue a vertex from queue and print it
          int currentVertex = dequeue(q);
          printf("%d ", currentVertex);

        // Get all adjacent vertices of the dequeued vertex currentVertex
        // If an adjacent vertex has not been visited, then mark it visited, update distance, and enqueue it
        for (temp = g->adjlist[currentVertex]; temp != NULL; temp = temp->next) {
            int adjVertex = temp->data;
            if (!visit[adjVertex]) {
                visit[adjVertex] = 1;
                enqueue(q, adjVertex);
                g->dist[adjVertex] = g->dist[currentVertex] + 1; // Update distance
            }
        }
    }
} 
       
int main(){
    int vertices,edges;
    
    printf("Enter number of vertices:");
    scanf("%d",&vertices);

    printf("Enter number of edges:");
    scanf("%d",&edges);

    GRAPH* g=creategraph(vertices);

    printf("ENter the edges in the form of source and destination:\n");
    for(int i=0;i<edges;i++){
        int src,dest;
        scanf("%d %d",&src,&dest);
        addedge(g,src,dest);
    }

    int startvertex;
    printf("Enter starting vertex of bfs:");
    scanf("%d",&startvertex);

    printf("BFS traversal strating from vertex %d: ",startvertex);
    bfs(g,startvertex);

    return 0;
}

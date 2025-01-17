#include<stdio.h>
#include<stdlib.h>
 
struct node{
    int data;
    struct node* next;
};

struct vertex{
    int adjlist;
    char name[50];
    struct node* ptr;
};

struct graph{
     int V;
     struct vertex array[100];
};

typedef struct node NODE;
typedef struct vertex VERTEX;
typedef struct graph GRAPH;

NODE* createnode(int x){
    NODE* nn=(NODE*)malloc(sizeof(NODE));
    nn->data=x;
    nn->next=NULL;
    return nn;
}

void storegraph(FILE* fh,GRAPH g){
    int i;
    fprintf(fh,"%d\n",g.V);
    for(i=0;i<g.V;i++){
        fprintf(fh,"%s\n",g.array[i].name);
        fprintf(fh,"%d\n",g.array[i].adjlist);
        NODE* temp=g.array[i].ptr;
        while(temp!=NULL){
            fprintf(fh,"%d\n",temp->data);
            temp=temp->next;
        }
    }
}

GRAPH loadgraph(char file[]){
    FILE* fh=fopen(file,"r");

    if(fh == NULL){
        printf("Error in opening the file\n");
        exit(1);
    }
        GRAPH g;
        int i,j;
        fscanf(fh,"%d\n",&g.V);
        for(i=0;i<g.V;i++){
            fscanf(fh,"%s\n",g.array[i].name);
            fscanf(fh,"%d\n",&g.array[i].adjlist);
            g.array[i].ptr=NULL;

            for(j=0;j<g.array[i].adjlist;j++){
                   int data;
                   fscanf(fh,"%d",&data);
                   NODE* nn=createnode(data);
                   nn->next=g.array[i].ptr;
                   g.array[i].ptr=nn;
            }
        }
      fclose(fh);
      return g;
}


void displaygraph(GRAPH g){
    printf("Number\tName\tAdjacent Node List\n");
    for (int i = 0; i < g.V; i++) {
        printf("%d\t%s\t", i + 1, g.array[i].name);
        NODE* temp = g.array[i].ptr;
        while(temp != NULL) {
            printf("-> %d", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main(){
    GRAPH g;
    char filename[50];

    printf("Enter the filename to save the graph: ");
    scanf("%s", filename);
    printf("Enter the number of vertices: ");
    scanf("%d", &g.V);

    for(int i = 0; i < g.V; i++){
        printf("Enter the name of the vertex: ");
        scanf(" %s", g.array[i].name);
        printf("Enter the number of adjacent vertices: ");
        scanf("%d", &g.array[i].adjlist);

        g.array[i].ptr = NULL;
        for(int j = 0; j < g.array[i].adjlist; j++){
            int adj;
            printf("Enter the adjacent vertex %d: ", j+1);
            scanf("%d", &adj);
            NODE* nn = createnode(adj);
            nn->next =  g.array[i].ptr;
            g.array[i].ptr = nn;
        }
    }

    FILE *fh;
    fh= fopen(filename, "w");

    if (fh == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    
    storegraph(fh, g);
    fclose(fh);
    printf("Graph saved successfully!\n");
    printf("Enter the filename to load the graph: ");
    scanf("%s", filename);
    g = loadgraph(filename);
    printf("Graph loaded from file:\n");
    displaygraph(g);

return 0;
}
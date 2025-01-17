#include<stdio.h>
#define max 50

int ADJMATRIX[max][max];

void initializematrix(int v){
    int i,j;
    for(i=0;i<v;i++){
        for(j=0;j<v;j++){
            ADJMATRIX[i][j]=0;
        }
    }
}

void addedge(int m,int n){
    ADJMATRIX[m][n]=1;
    ADJMATRIX[n][m]=1;
}

void printmatrix(int v){
    int i,j;
    printf("Adjacency matrix is:\n");
    for(i=0;i<v;i++){
        for(j=0;j<v;j++){
            printf("%d ",ADJMATRIX[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int v,e;

    printf("Enter number of vertices:");
    scanf("%d",&v);
    printf("Enter number of edges:");
    scanf("%d",&e);

    initializematrix(v);

    int i,m,n;
    for(i=0;i<e;i++){
       printf("Enter the edges in the form of source and head:");
       scanf("%d %d",&m,&n);
       addedge(m,n);
    }
printmatrix(v);
return 0;
}
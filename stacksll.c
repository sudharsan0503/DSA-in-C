#include<Stdio.h>

typedef struct node{
    int data;
    struct node* link;
}NODE;

NODE* createnode(int x){
    NODE* nn=(NODE*)malloc(sizeof(NODE));
    nn->data=x;
    nn->link=NULL;
    return nn;
}

void push(NODE* top,int data){
    NODE* nn=createnode(data);
    nn->link=top;
    return nn;
}

int pop(NODE* top){
    if(top==NULL){
        printf("Stack underflow\n");
        return -1;
    }
    
}
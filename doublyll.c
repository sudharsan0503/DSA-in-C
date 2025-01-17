#include<stdio.h>
#include<stdlib.h>

struct node{
    struct node* llink;
    int data;
    struct node* rlink;
};
typedef struct node NODE;

NODE* createnode(int x){
    NODE* nn=(NODE*)malloc(sizeof(NODE));
    nn->data=x;
    nn->llink=NULL;
    nn->rlink=NULL;
    return nn;
}

void traverse(NODE* head) {
    NODE* temp = head;

    if (head == NULL) {
        printf("Empty list\n");
        return;
    }

    printf("Head -> ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->rlink;
    }
    printf("NULL\n");
}


/*void traverse(NODE* head){
    NODE* temp=head;
    printf("NULL<->");
    while(temp!=NULL){
         printf("%d<->",temp->data);
         temp=temp->rlink;
    }
    printf("NULL\n");
}*/

NODE* delete(NODE* head, int value) {
    // Handle empty list case
    if (head == NULL) {
        return NULL; // Indicate deletion failure
    }

    // Handle deletion of the head node
    if (head->data == value) {
        NODE* temp = head;
        head = head->rlink; // Update head to point to the next node
        free(temp);
        return head;
    }

    // Traverse the list to find the node to delete
    NODE* current = head;
    NODE* previous = NULL; // Keep track of the previous node

    while (current != NULL && current->data != value) {
        previous = current;
        current = current->rlink;
    }

    // Node not found
    if (current == NULL) {
        return head; // No change to the list
    }

    // Delete the found node
    previous->rlink = current->rlink;
    free(current);

    return head;
}


/*NODE* delete(NODE* head,int x,int index){
    NODE* temp;
    NODE* current,*previous;
    temp=head;
    int i;
    while(i!=index){
        temp=temp->rlink;
        i++;
    }
    previous->rlink=temp->rlink;
    free(temp);
    traverse(head);
    return head;
}*/

int main(){
    int n,i,val;
    printf("Enter number of nodes:");
    scanf("%d",&n);

    NODE* ptr[n];

    for(i=0;i<n;i++){
        printf("Enter node value:");
        scanf("%d",&val);
        ptr[i]=createnode(val);
    }

    for(i=0;i<n;i++){
        if(i==0){                               //first node
            ptr[i]->llink=NULL;
            ptr[i]->rlink=(n>1)?ptr[i+1]:NULL;  //if not last node then ptr[i+1]else null
        }
        if(i==(n-1)){                          //last node
            ptr[i]->llink=ptr[i-1];
            ptr[i]->rlink=NULL;
        }
        else{
            ptr[i]->llink=ptr[i-1];
            ptr[i]->rlink=ptr[i+1];
        }
    }

    NODE* head;
    head=ptr[0];
    traverse(head);

    int ch,val1,pos;
    do{
        printf("\n1.Traverse\n2.Deleteion\n");
        printf("Enter your choice:");
        scanf("%d",&ch);
        switch(ch){
            case 1: 
                    printf("Traversal:\n");
                    traverse(head);
                    break;
            case 2: 
                    printf("Enter value to delete:");
                    scanf("%d",&val1);
                    //printf("Enter position to delete:");
                    //scanf("%d",&pos);
                    delete(head,val1);
                    break;
        }
    }while(ch<=2);

return 0;
}
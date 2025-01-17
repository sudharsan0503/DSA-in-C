#include<stdio.h>
#include<stdlib.h>

struct node{  
    int data;
    struct node* lchild;
    struct node* rchild;
};

typedef struct node NODE;

NODE* insertBST(NODE* root,int x){                 // t is pointer of root node and x is data to be inserted
   //creation of node to be inserted
   NODE* T=(NODE*)malloc(sizeof(NODE));
   T->data=x;
   T->lchild=T->rchild=NULL;
   //dont give return T;
   //Below is checking if tree is empty or not
   if(root==NULL){
       root=T;
       return root;
   }
   //insertion of node
   NODE* parent=NULL;
   NODE* cur=root;                 //creating a temporary pointer 'cur' with root to access and creating a pointer parent
   while(cur!=NULL){               //TRaversing to insert
        parent=cur;                //MOST important step.Mostly we will forget to assign.
        if(x < cur->data){
            cur=cur->lchild;
        }
        else if(x > cur->data){
            cur=cur->rchild;
        }
        else{
            printf("Duplicate value cannot be inserted\n");
            return root;
        }
   }
   //Above one is traversing to see where to insert.Now we are inserting
   if(x < parent->data){
    parent->lchild=T;
   }
   else{
     parent->rchild=T;
   }
   return root;   //not return T
} 

void searchBST(NODE* root,int x){
    if(root==NULL){
        printf("Empty tree\n");
        return;
    }
    NODE* cur=root;
    while(cur!=NULL){
        if(x < cur->data){           //if element is less ,then move left
            cur=cur->lchild;
        }
        else if(x > cur->data){      //if element is greater,move right
            cur=cur->rchild;
        }
        else{                        //if element is equal then print element found
            printf("Element found\n");
            return ;
        }
    }
    printf("Elemrnt not found\n");
    return ;
}

void preorderBST(NODE* T) {
    if (T != NULL) {
        printf("%d ", T->data); // Print the data of the current node
        preorderBST(T->lchild); // Traverse left subtree
        preorderBST(T->rchild); // Traverse right subtree
    }
}

void postorderBST(NODE* T) {
    if (T != NULL) {
        postorderBST(T->lchild); // Traverse left subtree
        postorderBST(T->rchild); // Traverse right subtree
        printf("%d ", T->data); // Print the data of the current node
    }
}

void inorderBST(NODE* T) {
    if (T != NULL) {
        inorderBST(T->lchild); // Traverse left subtree
        printf("%d ", T->data); // Print the data of the current node
        inorderBST(T->rchild); // Traverse right subtree
    }
}


int minimumBST(NODE* root){
    NODE* T=root;
    while(T->lchild!=NULL){
        T=T->lchild;
    }
    return T->data;
}

int maximumBST(NODE* root){
    NODE* T=root;
    while(T->rchild!=NULL){
        T=T->rchild;
    }
    return T->data;
}

NODE* deleteBST(NODE* T,int x){                  //x is data to be deleted
   if(T==NULL){
    printf("Element not found!Deletion cannot be performed\n");
    return T;
   }
   if(x < T->data){
    T->lchild=deleteBST(T->lchild,x);
   }
   else if(x > T->data){
    T->rchild=deleteBST(T->rchild,x);
   }
   else{                                  //if element is equal then deletion will be performed
        NODE* dltptr;
        if(T->lchild==NULL){              //if there is no left child,ie,null
            dltptr=T;                     //assigning T to deleting pointer
            T=T->rchild;                  //NOw moving T to right as we delete left
            free(dltptr);
            printf("Element %d deleted",x);
        }
        else if (T->rchild==NULL){            //if there is no right child
             dltptr=T;
             T=T->lchild;
             free(dltptr);
             printf("Element %d deleted",x);
        }
        else{                                // there is no both left and right child
           dltptr=T->lchild;
           while(dltptr->rchild!=NULL){
               dltptr=dltptr->rchild;
           }
           T->data=dltptr->data;
           dltptr->lchild=deleteBST(dltptr->lchild,dltptr->data);
        }
   }
   return T;
}

int main(){
    int val,choice;
    NODE* ROOT=NULL;
    do{
        printf("\n1)Insert\n2)Search\n3)Traverse\n4)Delete\n5)Minimum\n6)maximum\n7)Exit\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                 printf("Enter data to be inserted:");
                 scanf("%d",&val);
                 ROOT=insertBST(ROOT,val);
                 break;
            case 2:
                 printf("Enter data to be searched:");
                 scanf("%d",&val);
                 searchBST(ROOT,val);
                 break;
            case 3:
                printf("\nPreorder traversal:\n");
                preorderBST(ROOT);
                printf("\nPostorder traversal:\n");
                postorderBST(ROOT);
                printf("\nInorder traversal:\n");
                inorderBST(ROOT);
                printf("\n");
                break;
            case 4:
                printf("Enter value to be deleted:");
                scanf("%d",&val);
                ROOT=deleteBST(ROOT,val);
                break;
            case 5:
                 printf("Minimum value is:%d",minimumBST(ROOT));
                 break;
            case 6:
                 printf("Maximum value is:%d",maximumBST(ROOT));
                 break;
        }
    }while(choice<=6);
return 0;
}
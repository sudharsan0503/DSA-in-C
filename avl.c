#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    struct node* lchild,*rchild;
};
typedef struct node NODE;
int bf;  //balance factor

int getheight(NODE* T){
    int hl,hr;
    if(T==NULL){
        return 0;
    }
    else{
        hl=getheight(T->lchild);
        hr=getheight(T->rchild);
    }
    if(hl>hr||hl==hr){
         return hl+1;
    }
    else{
        return hr+1;
     }
}

int getbalancefactor(NODE* T){   //balancefactor=height of left-heighrof right
    if(T==NULL){
        return 0;
    }
    int hl=getheight(T->lchild);
    int hr=getheight(T->rchild);
    return hl-hr;
}

NODE* leftrotate(NODE*T){
    NODE* Y;
    Y=T->rchild;
    T->rchild=Y->lchild;
    Y->lchild=T;
    return Y;
}

NODE* rightrotate(NODE*T){
    NODE* Y;
    Y=T->lchild;
    T->lchild=Y->rchild;
    Y->rchild=T;
    return Y;
}

NODE* insertavl(NODE* T,int x){
    if(T==NULL){
         NODE* T=(NODE*)malloc(sizeof(NODE));
         T->data=x;
         T->lchild=T->rchild=NULL;
         return T;
    }
    if(x < T->data){
        T->lchild=insertavl(T->lchild,x);
    }
    else if(x > T->data){
        T->rchild=insertavl(T->rchild,x);
    }
    else{
        printf("Duplicate value cannot be inserted!!\n");
        return T;
    }
    bf=getbalancefactor(T);
    if(bf==2 && x < T->lchild->data){
            return rightrotate(T);
    }
    if(bf==-2 && x<T->rchild->data){
            return leftrotate(T);
    }
    if(bf==2 && x>T->lchild->data){
            T->lchild=leftrotate(T->lchild);
             return rightrotate(T);
    }
    if(bf==-2 && x>T->rchild->data){
            T->rchild=rightrotate(T->rchild);
            return leftrotate(T);
    }
    return T;
    }

void inorder(NODE* T){
    if(T!=NULL){
        inorder(T->lchild);
        printf("%d ",T->data);
        inorder(T->rchild);
    }
}

void preorder(NODE* T){
    if(T!=NULL){
        printf("%d ",T->data);
        preorder(T->lchild);
        preorder(T->rchild);
    }
}

void postorder(NODE* T){
    if(T!=NULL){
        postorder(T->lchild);
        postorder(T->rchild);
        printf("%d ",T->data);
    }
}

void search(NODE* root,int x){
    if(root==NULL){
        printf("Empty BST!!!\n");
        return;
    }
    NODE* cur=root;
    while(cur!=NULL){
        if(x < cur->data){
            cur=cur->lchild;
        }
        else if(x > cur->data){
            cur=cur->rchild;
        }
        else{
            printf("ELement found %d\n",x);
            return;
        }
    }
    printf("Element not found!!\n");
    return;
}

NODE* minValueNode(NODE* node) {
    NODE* current = node;
    while (current && current->lchild != NULL) {
        current = current->lchild;
    }
    return current;
}

NODE* deleteavl(NODE* T, int x) {
    if (T == NULL) {
        printf("Element not found!!");
        return T;
    }
    if (x < T->data) {
        T->lchild = deleteavl(T->lchild, x);
    }
    else if (x > T->data) {
        T->rchild = deleteavl(T->rchild, x);
    }
    else {
        if (T->lchild == NULL || T->rchild == NULL) {
            NODE* temp = T->lchild ? T->lchild : T->rchild;      /*Case 1: Node with one child or no child
                                                                       If the node has one child or no child, it directly deletes the node and adjusts the tree.
                                                                       It assigns the left child (T->lchild) if it exists, or the right child (T->rchild), to the variable temp.
                                                                       If temp is NULL, it means T has no children, so it deletes T and sets it to NULL.
                                                                       Otherwise, it copies the contents of temp to T and then deletes temp.
                                                                       Case 2: Node with two children
                                                                       If the node has two children, it finds the minimum value node (temp) in its right subtree.
                                                                       It copies the data of temp to the current node (T).
                                                                       Then, it recursively deletes temp from the right subtree.*/
                                                                       
       if (temp == NULL) {
                temp = T;
                T = NULL;
            }
            else {
                *T = *temp;
                free(temp);
            }
            printf("Element %d deleted successfully\n",x);
        }
        else {
            NODE*temp = minValueNode(T->rchild);
            T->data = temp->data;
            T->rchild = deleteavl(T->rchild, temp->data);
        }
    
    }

    if (T == NULL) {
        return T;
    }

    bf = getbalancefactor(T);

    if (bf == 2 && getbalancefactor(T->lchild) >= 0) {
        return rightrotate(T);
    }
    if (bf == 2 && getbalancefactor(T->lchild) < 0) {
        T->lchild = leftrotate(T->lchild);
        return rightrotate(T);
    }
    if (bf == -2 && getbalancefactor(T->rchild) <= 0) {
        return leftrotate(T);
    }
    if (bf == -2 && getbalancefactor(T->rchild) >= 0) {
        T->rchild = rightrotate(T->rchild);
        return leftrotate(T);
    }

    return T;
}

int main(){
    NODE* root=NULL;
    int ch,val;
    do{
        printf("\n1)InsertAVL\n2)Search\n3)Traversal\n4)Delete\n");
        printf("Enter your choice:");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                  printf("Enter value to be inserted:");
                  scanf("%d",&val);
                  root=insertavl(root,val);
                  break;
            case 2:
                  printf("Enter value to be searched:");
                  scanf("%d",&val);
                  search(root,val);
                  break;
            case 3:
                 printf("\nInoreder:\n");
                 inorder(root);
                 printf("\nPreoreder:\n");
                 preorder(root);
                 printf("\nPostoreder:\n");
                 postorder(root);
                 printf("\n");
                 break;
            case 4:
                 printf("Enter value to be deleted:");
                 scanf("%d",&val);
                 root=deleteavl(root,val);
                 break;
         }
    }while(ch<=4);
return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    char data[50];
    struct node* lchild;
    struct node* rchild;
};
typedef struct node NODE;

NODE* insertbst(NODE* root,char* str){
    NODE* T=(NODE*)malloc(sizeof(NODE));
    strcpy(T->data,str);
    T->lchild=NULL;
    T->rchild=NULL;

    if(root==NULL){
        root=T;
        return root;
    }
    NODE* parent=NULL;
    NODE* cur=root;
    while(cur!=NULL){
        parent=cur;;
        if(strcmp(str,cur->data)<0){
            cur=cur->lchild;
        }
        else if(strcmp(str,cur->data)>0){
            cur=cur->rchild;
        }
        else{
            printf("Duplicate element cannot be inserted\n");
            return root;
        }
    }
    if(strcmp(str,parent->data)<0){
        parent->lchild=T;
    }
    else{
        parent->rchild=T;
    }
return root;
}

void searchbst(NODE* root,char* str){
    if(root==NULL){
        printf("Empty bst\n");
        return ;
    }
    NODE* cur=root;
    while(cur!=NULL){
        if(strcmp(str,cur->data)<0){
            cur=cur->lchild;
        }
        else if(strcmp(str,cur->data)>0){
            cur=cur->rchild;
        }
        else{
            printf("string %s found\n",str);
            return ;
        }
    }
    printf("String not found\n");
    return ;
}

void preorderbst(NODE* root){
    NODE* temp=root;
    if(temp!=NULL){                      //if you use while instead of if then infinite loop
        printf("%s ",temp->data);
        preorderbst(temp->lchild);
        preorderbst(temp->rchild);
    }
}

void inorderbst(NODE* root){
    NODE* temp=root;
    if(temp!=NULL){                        //if you use while instead of if then infinite loop
        inorderbst(temp->lchild);
        printf("%s ",temp->data);
        inorderbst(temp->rchild);
    }
}

void postorderbst(NODE* root){
    NODE* temp=root;
    if(temp!=NULL){                     //if you use while instead of if then infinite loop
        postorderbst(temp->lchild);
        postorderbst(temp->rchild);
        printf("%s ",temp->data);
    }
}

char* minimumbst(NODE* root){       //not int minimumbst(NODE* root),It is char*.
    NODE* temp=root;
    while(temp->lchild!=NULL){
        temp=temp->lchild;
    }
    char* newstr=(char*)malloc(sizeof(char));   //returning temp->data directly may cause issues because temp->data is an array.
    strcpy(newstr,temp->data);                 //To return the minimum and maximum strings from the BST, you should allocate memory
    return newstr;                             // for a new string and copy the content of temp->data into it.
}

char* maximumbst(NODE* root){
    NODE* temp=root;
    while(temp->rchild!=NULL){
        temp=temp->rchild;
    }
    char* newstr=(char*)malloc(sizeof(char));
    strcpy(newstr,temp->data);
    return newstr;
}

NODE* delete(NODE* root,char* str){
    if(root==NULL){
        printf("Deleteion cannot be performed\n");
        return root;
    }
    if(strcmp(str,root->data)<0){
        root->lchild=delete(root->lchild,str);
    }
    else if(strcmp(str,root->data)>0){
        root->rchild=delete(root->rchild,str);
    }
    else{
        NODE* dltptr;
        if(root->lchild==NULL){
            dltptr=root;
            root=root->rchild;
            free(dltptr);
            printf("Deleted %s\n",str);
        }
        else if(root->rchild==NULL){
            dltptr=root;
            root=root->lchild;
            free(dltptr);
            printf("Deleted %s\n",str);
        }
        else{
            dltptr=root->lchild;
            while(dltptr->rchild!=NULL){
                dltptr=dltptr->rchild;
            }
            strcpy(root->data,dltptr->data);
            dltptr->lchild=delete(dltptr->lchild,dltptr->data);
        }
    }
    return root;
}

int main(){
    int ch;
    NODE* ROOT=NULL;
    char str[50];
    do{
        printf("1.Insert string\n2)Search\n3)Traversal\n4)Minimum string\n5)Maximum string\n6)Delete\n");
        printf("Enter your choice:");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                printf("Enter string to insert:");
                scanf("%s",&str);
                ROOT=insertbst(ROOT,str);
                break;
            case 2:
                printf("ENter string to search:");
                scanf("%s",&str);
                searchbst(ROOT,str);
                break;
            case 3:
                 printf("Inorder traversal:");
                 inorderbst(ROOT);
                 printf("\n");
                 printf("Preorder traversal:");
                 preorderbst(ROOT);
                 printf("\n");
                 printf("Postorder traversal:");
                 postorderbst(ROOT);
                 printf("\n");
                 break;
            case 4:         
                printf("The minimum string is:%s",minimumbst(ROOT)); //The issue with minimumbst and maximumbst functions is that u r not assigning the result of these fns to any 
                free(minimumbst(ROOT));                              // variable in your main function. Additionally, you need to free the memory 
                printf("\n");                                        //allocated for the new strings returned by these functions
                break;
            case 5:
                printf("The maximum string is:%s",maximumbst(ROOT));
                free(maximumbst(ROOT));
                printf("\n");
                break;
            case 6:
                printf("Enter string to delete:");
                scanf("%s",&str);
                delete(ROOT,str);
                break;
        }
    }while(ch<7);
return 0;
}
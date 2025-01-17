#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    char data[50];
    struct node* next;
};

typedef struct node NODE;

NODE* createnode(char* data){                      //most mistakes in char instead of char*.char* variable holds the memory address of the first character in a sequence
    NODE* nn=(NODE*)malloc(sizeof(NODE));
    strcpy(nn->data,data);
    nn->next=NULL;
    return nn;
}

void traverse(NODE* head){
    NODE* temp;
    temp=head;
    while(temp!=NULL){
        if(temp->next==NULL){
            printf("%s->NULL",temp->data);
        }
        else{
            printf("%s->",temp->data);
        }
    temp=temp->next;
    }
}

NODE* insertbeg(NODE* head,char* data){
    NODE* temp;
    NODE* nn=createnode(data);
    temp=head;
    nn->next=temp;
    head=nn;
    traverse(head);
}

NODE* insertend(NODE* head,char* data){
    NODE* temp;
    NODE* nn=createnode(data);
    temp=head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=nn;
    nn->next=NULL;
    traverse(head);
}

NODE* insertpos(NODE* head,char* data,int index){
    int i=1;
    NODE* temp;
    NODE* nn=createnode(data);
    temp=head;
    while(i!=index-1){
        temp=temp->next;
        i++;
    }
    nn->next=temp->next;     //updating link part of new node
    temp->next=nn;           //updating new node after temp
    traverse(head);
}

void search(NODE* head,int n,char* data){
    NODE* temp=head;
    while(temp!=NULL){
        if(strcmp(temp->data,data)==0){      //dont forget to use strcmp
            printf("Data found!!\n");          
            return;
        }
        temp=temp->next;
    }
    printf("Element not found!!\n");
}

NODE* deletestring(NODE* head,char* string){
    NODE* temp=head;
    NODE* current,*previous;
    previous=NULL;
    int found=0;
    while(temp!=NULL){
        if(strcmp(temp->data,string)==0){
               if(temp==head){              //if it is first node to be deleted
                  head=temp->next;
                  free(temp);
                  found=1;
                  printf("Deleted\n");
                  traverse(head);
                  temp=head;
               }
               else{
                   found=1;
                   previous->next=temp->next;
                   free(temp);
                   printf("Deleted\n");
                   traverse(head);
                   temp=previous->next;
               }
        }
        else{                                      //else part is must.otherwise we will not have a pointer to to connect the node before and after node to be  deleted
            previous = temp;
            temp=temp->next;
        }
    
    }
    if(!found){
        printf("Element not found.deletion cannot be performed\n");
    }
  return head;
}

NODE* deletechar(NODE* head,char c){
    NODE* temp=head;
    NODE* current,*previous;
    previous=NULL;
    int found=0;
    while(temp!=NULL){
        if(temp->data[0]==c){
               if(temp==head){              //if it is first node to be deleted
                  head=temp->next;
                  free(temp);
                  found=1;
                  printf("Deleted\n");
                  traverse(head);
                  temp=head;
               }
               else{
                   found=1;
                   previous->next=temp->next;
                   free(temp);
                   printf("Deleted\n");
                   traverse(head);
                   temp=previous->next;
               }
        }
        else{                                      //else part is must.otherwise we will not have a pointer to to connect the node before and after node to be  deleted
            previous = temp;
            temp=temp->next;
        }
    
    }
    if(!found){
        printf("Element not found.deletion cannot be performed\n");
    }
  return head;
}

int main(){
    int n,ch,i;
    char str[50];      //important paranthesis[50].otherwise it will take inly array

    printf("Enter number of nodes:");
    scanf("%d",&n);
    NODE* ptr[n];

    for(i=0;i<n;i++){
        printf("Enter data:");
        scanf("%s",&str);
        ptr[i]=createnode(str);
    }

    for(i=0;i<n;i++){
        if(i==(n-1)){
            ptr[i]->next=NULL;
        }
        else{
            ptr[i]->next=ptr[i+1];
        }
    }
    NODE* head;
    head=ptr[0];
    traverse(head);

    do{
        
        printf("\n1)Insert at beginning\n2)Insert at the end\n3)Insert at any position\n4)Search\n5)Delete string\n6)Delete character\n7)Exit\n");
        printf("ENter your choice:");
        scanf("%d",&ch);

        if(ch==1){
            char str1[50];
            printf("Enter data to be inserted:");
            scanf("%s",&str1);
            insertbeg(head,str1);
        }
        if(ch==2){
            char str1[50];
            printf("Enter data to be inserted:");
            scanf("%s",&str1);
            insertend(head,str1);
        }
        if(ch==3){
            char str1[50];
            int index;
            printf("Enter data to be inserted:");
            scanf("%s",&str1);
            printf("ENter position number:");
            scanf("%d",&index);
            insertpos(head,str1,index);
        }
        if(ch==4){
            char str1[50];
            printf("Enter data to be searched:");
            scanf("%s",&str1);
            search(head,n,str1);
        }
        if(ch==5){
            char string[50];
            printf("Enter the string to delete:");
            scanf(" %s",&string);    //space before %c is very very important.....
            head=deletestring(head,string);
        }
        if(ch==6){
            char c;
            printf("Enter the starting character to delete:");
            scanf(" %c",&c);    //space before %c is very very important.....
            head=deletechar(head,c);
        }

    }while(ch<7);
return 0;
}
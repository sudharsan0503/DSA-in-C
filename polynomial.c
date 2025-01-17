#include<stdio.h>
#include<stdlib.h>

struct node{
    float coeff;
    int expo;
    struct node* link;
};

struct node* insert(struct node* head,float co,int ex){
    struct node* nn=(struct node*)malloc(sizeof(struct node));  //creating a new node consisting of coeff,expo,link ad giving them values
    nn->coeff=co;
    nn->expo=ex;
    nn->link=NULL;           //NO return statements
    //To arrange in decreasing order.if there is no list or the exponent of given is greater then alread then it will inserted at the beginning node
    //We can also say as insert at beginning
    if(head==NULL){
        head=nn;
    }
    else if(ex > head->expo){
        nn->link=head->link;   //giving value to new node link part and bringing back head to first node
        head=nn;
    }
    else{
        struct node* temp=head;
        while(temp->link!=NULL && temp->link->expo > ex){
            temp=temp->link;
        }
        nn->link=temp->link;
        temp->link=nn;
    }
return head;
}

struct node* create(struct node* head){
    int n,expo;
    float coeff;
    printf("Enter the number of terms:");
    scanf("%d",&n);
    
    for(int i=0;i<n;i++){
        printf("Enter the coefficient of term %d:",i+1);
        scanf("%f",&coeff);
        
        printf("Enter the exponent of term %d:",i+1);
        scanf("%d",&expo);

        head=insert(head,coeff,expo);
    }
    return head;
}

void print(struct node* head){
    if(head==NULL){
        printf("No polynomial\n");
    }
    else{
        struct node* temp=head;
        while(temp!=NULL){
            printf("%4.1fx^%d",temp->coeff,temp->expo);
            temp=temp->link;
            if(temp->link!=NULL)
                printf("+");
            else
                printf("\n");        
        }
    }
}

void polyadd(struct node*head1,struct node* head2){
    struct node* ptr1=head1;
    struct node* ptr2=head2;
    struct node* head3=NULL;          //to store the resultant
    while(ptr1!=NULL && ptr2!=NULL){
        if(ptr1->expo==ptr2->expo){
            head3=insert(head3,ptr1->coeff+ptr2->coeff,ptr1->expo);
            ptr1=ptr1->link;
            ptr2=ptr2->link;
        }
        else if(ptr1->expo > ptr2->expo){
            head3=insert(head3,ptr1->coeff,ptr1->expo);
            ptr1=ptr1->link;
        }
        else if(ptr2->expo > ptr1->expo){
            head3=insert(head3,ptr2->coeff,ptr2->expo);
            ptr2=ptr2->link;
        }
    }
    while(ptr1!=NULL){
         head3=insert(head3,ptr1->coeff,ptr1->expo);
         ptr1=ptr1->link;
    }
    while(ptr2!=NULL){
        head3=insert(head3,ptr2->coeff,ptr2->expo);
        ptr2=ptr2->link;
    }
    printf("Added Polynomial is:");
    print(head3);
}

void polymul(struct node* head1,struct node* head2){
      struct node* ptr1=head1;
      struct node* ptr2=head2;
      struct node* head3=NULL;
      float res1;
      int res2;

      if(head1==NULL||head2==NULL){
        printf("NO polynomial\n");
        return;
      }

      while(ptr1 != NULL){
        ptr2=head2;
        while(ptr2 != NULL){
              res1=ptr1->coeff*ptr2->coeff;
              res2=ptr1->expo+ptr2->expo;
              head3=insert(head3,res1,res2);
              ptr2=ptr2->link;
        }
        ptr1=ptr1->link;
      }
      printf("The multiplied polynomial is:\n");
      print(head3);
}
    
int main(){
    int ch;
    struct node* head1=NULL;
    struct node* head2=NULL;
    printf("Enter the first polynomial\n");
    head1=create(head1);
    printf("Enter the second polynomial\n");
    head2=create(head2);
    polyadd(head1,head2);
    polymul(head1,head2);
    return 0;
}
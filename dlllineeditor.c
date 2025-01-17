#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_LEN 100

struct dllnode{
    struct dllnode* prev;    
    char word[50];
    struct dllnode* next;
};
typedef struct dllnode NODE;

struct linehead{
     struct linehead* P;                //P-Previous line, WC-Word count , N-Next line , first-first node
     int WC;
     struct dllnode* first;             //Use dllnode as it is linked to dllnode 
     struct linehead* N;
};
typedef struct linehead LINEHEAD;

typedef struct{
    struct linehead* start;             //start-starting linehead,LC-Line count,TWC-Total word count,end-last linehead
    int LC;
    int TWC;
    struct linehead* end;
}HEAD;

//To create new node
NODE* createnode(char* data){
    NODE* nn=(NODE*)malloc(sizeof(NODE));             //nn-newnode  
    nn->prev=NULL;
    strcpy(nn->word,data);
    nn->next=NULL;
    return nn;
}

//To create line head
LINEHEAD* createlinehead(){
    LINEHEAD* nll=(LINEHEAD*)malloc(sizeof(LINEHEAD)); //nll-newlinehead
    nll->P=NULL;
    nll->WC=0;
    nll->first=NULL;
    nll->N=NULL;
    return nll;
}

HEAD* createhead(){
    HEAD* nh=(HEAD*)malloc(sizeof(HEAD));  //nh-new head
    nh->start=NULL;
    nh->LC=0;
    nh->TWC=0;
    nh->end=NULL;
    return nh;
}

void append(HEAD* head,char line[100]){
    LINEHEAD* lh=createlinehead();
    
    if(head->end==NULL){
          head->start=lh;
          head->end=lh;
          lh->P=lh;
          lh->N=lh;
    }
    else{
        lh->P=head->end;
        lh->N=head->end->N;
        head->end->N=lh;
        head->end=lh;
        head->start->P;
    }
    
    char word[50];
    int i,k;
    i=0;k=0;
    while(line[i]!='\0'){
        while(!isspace(line[i])){     //to extract single word
            word[k++]=line[i++];     //inside the loop, each non-space character (line[i]) is copied to the word array at index k
            if(line[i]=='\0'){       //be careful if u give = inswtead of == then infinite loop
                break;
            }
        }
            word[k]='\0';      /*After extracting a word from the line, the character array word is null-terminated by placing '\0' at the end.This ensures that the word array is treated as a C-style string, making it compatible with functions that expect null-terminated strings, such as strcpy()*/
            (lh->WC)++;
            NODE*nn=createnode(word);
            NODE* last;
            if(lh->first==NULL){   //if linehead is empth
                lh->first=nn;
                nn->next=NULL;
                nn->prev=NULL;
                last=nn;
            }
            else{                  //if linehead has nodes then nn is appended at the end by using current last node(last)
                nn->prev=last;
                last->next=nn;
                last=nn;
            }
        while(isspace(line[i])) i++;
        }
    head->TWC+=lh->WC;    //word count
    (head->LC)++;         //line count
}


void insertatloc(HEAD* head,int loc,char line[100]){
    LINEHEAD* lh=createlinehead();

    char word[50];
    int i,k;
    i=0;k=0;
    while(line[i]!='\0'){
        while(!isspace(line[i])){
            word[k++]=line[i++];
            if(line[i]=='\0')
                break;
            }
            word[k]='\0';
            (lh->WC)++;
            NODE* nn=createnode(word);
            NODE* last=NULL;
            if(lh->first==NULL){
                lh->first=nn;
                nn->prev=NULL;
                nn->next=NULL;
                last=nn;
            }
            else{
                 nn->prev=last;
                 last->next=nn;
                 last=nn;
            }
        while(isspace(line[i])) i++;
    }
    if(loc==1){
        lh->P = head->end;
        lh->N = head->start;
        head->start->P=lh;
        head->end->N=lh;
        head->start=lh;
    }
    else{
        LINEHEAD* cur_line;
        cur_line =head->start;
        k=1;
        while(k<loc-1 && cur_line->N!=head->start){
            cur_line = cur_line->N;
            k++;
        }
        lh->P=cur_line;
        lh->N=cur_line->N;
        cur_line->N->P=lh;
        cur_line->N=lh;
        if(head->end == cur_line){
            head->end=lh;
        }
    }
    head->TWC+=lh->WC;
    (head->LC)++;
    return;
}

void deleteatloc(HEAD* head,int loc){
    int i=1;
    LINEHEAD* cur_line;
    
    if(head->start==NULL){
        printf("\nEmpty Text.\n");
        return;
    }
    if(head->LC < loc){
        printf("No such line exists in the text.\n");
        return;
    }
    cur_line=head->start;
    while(cur_line != head->end && i<loc){
        cur_line = cur_line->N;
        i++;
    }
    if(cur_line->P != head->end){
          cur_line->P->N = cur_line->N;
    }
    else{
        head->start = cur_line->N;    //delete first node
    }
    if (cur_line->N != head->start){
        cur_line->N->P = cur_line->P;
    }
    else{
        head->end = cur_line->P;     //delete last node
    }

    head->LC--;
    head->TWC -= cur_line->WC;
    NODE* cur_word = cur_line->first;
    while(cur_word != NULL){
        NODE* t = cur_word;
        cur_word = cur_word->next;
        free(t);
    }
    free(cur_line);
    return;
}

void find(HEAD* head,char word[]){
    int flag,pos,i;
    flag=0;
    i=1;
    LINEHEAD* cur_line;
    NODE* cur_word;
    if(head->start == NULL){
        printf("\nEmpty Text\n");
        return;
    }
    cur_line=head->start;
    while(cur_line != head->end){
        pos=0;
        cur_word = cur_line->first;
        while(cur_word != NULL){
            pos++;
            if(strcmp(cur_word->word,word)==0){
                flag=1;
                printf("\nOccurence of %s is in line - %d at position %d",word,i,pos);
                
            }
            cur_word = cur_word->next;
        }
        cur_line = cur_line->N;
        i++;
    }
    cur_word = head->end->first;
    pos=0;
    while(cur_word != NULL){
        pos++;
        if(strcmp(cur_word->word,word)==0){
             flag=1;
             printf("\nOccurence of %s is in line - %d at position %d",word,i,pos);
        }
    cur_word = cur_word->next;
    }
    if(!flag){
        printf("\n%s is not present in the text.",word);
    }
}

void display(HEAD* head){
    int i;
    i=1;
    LINEHEAD* lh = head->start;
    while(lh != head->end){
        NODE* cur = lh->first;
        printf("\n%d. ",i);
        while(cur != NULL){
            printf("%s ",cur->word);
            cur=cur->next;
        }
        i++;
        lh=lh->N;
    }
    NODE* cur = lh->first;
    printf("\n%d. ",i);
    while(cur != NULL){
        printf("%s ",cur->word);
        cur=cur->next;
    }
    printf("\nNO. of lines = %d \nNO. of words = %d \n",head->LC,head->TWC);
}

HEAD* readfromfile(char filename[]){
    int i;
    char line[100];
    FILE* fp = fopen(filename,"r");
    HEAD* head = createhead();
    do{
        fgets(line,MAX_LEN,fp);
        if(!feof(fp)){
            append(head,line);
        }
    }
    while(!feof(fp));
    fclose(fp);
    return head;
}

void savefile(HEAD* head,char filename[]){
    int i;
    FILE* fp=fopen(filename,"w");
    LINEHEAD* cur=head->start;;
    while(cur  != head->end){
        NODE* cur_word = cur->first;
        while(cur_word != NULL){
            fprintf(fp, "%s ",cur_word->word);
            cur_word = cur_word->next;
        }
      cur = cur->N;
      fprintf(fp, "\n");
    }
    NODE* cur_word = cur->first;
    while(cur_word != NULL){
        fprintf(fp, "%s ",cur_word->word);
        cur_word = cur_word->next;
    }
    fprintf(fp,"\n");
    fclose(fp);
}


int main(){
    int op,lcount,lno;
    lcount=0;
    char line[100],filename[25],word[25],rword[25];
    char* t;
    HEAD* head=NULL;
    do{
    printf("\n1)New file\n2)Read from file\n3)Save to file\n4)Display contents\n");
    printf("5)Insert a new line\n6)Find word\n7)Delete a line\n");
    printf("Enter your option:");
    scanf("%d",&op);
    switch(op){
        case 1: 
                 getchar();
                 head = createhead();
                 lcount = 0;
         	     do{
         	       printf("\n%d. ",++lcount);
                   if (gets(line)!= NULL){
                      if (strcmp(line, "END")==0)
                            break;
                    append(head, line);}
         	     }
         	     while (!feof(stdin));
       		     break;
        case 2:  
                 printf("\nEnter filename :  ");
                 scanf("%s", filename);
                 head = readfromfile(filename);
                 break;
        case 3: 
                 if (head != NULL){
                    printf("\nEnter filename :  ");
                     scanf("%s", filename);
                     savefile(head, filename);
                 }
                 break;
        case 4:  
                if (head != NULL){
       		       printf("\nCurrent contents : \n");
        	       display(head);
        	     }
        	     break;
        case 5: if (head != NULL){
       		       printf("Enter the line number : ");
        	       scanf("%d", &lno);
        	       getchar();
        	       printf("Enter the text to insert : ");
        	       if (gets(line) != NULL)
        	           insertatloc(head, lno, line);
        	    }
        	    break;
       case 6:  
       
                 if (head != NULL){
       		        printf("Enter the word to search : ");
                    scanf("%s", word);
        	        find(head, word);
        	    }
        	    break;
       case 7:  
                if (head != NULL){
       		        printf("Enter the line number to delete : ");
                    scanf("%d", &lno);
        	        deleteatloc(head,lno);
        	    }        	
        	    break;    
      }
  return 0;
    }while(op <= 7);
}
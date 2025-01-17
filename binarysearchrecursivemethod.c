#include<stdio.h>
int n;
int binsearch(int array[],int low,int high,int key);

int main(){
    printf("This is recursive method\n");
    int key;
    printf("Enter size of array:");
    scanf("%d",&n);

    int array[n];

    for(int i=0;i<n;i++){
        printf("Enter array element in sorted:");
        scanf("%d",&array[i]);
    }

    printf("Enter element to search:");
    scanf("%d",&key);
    
   int result=binsearch(array,0,n-1,key);

   if(result!=-1){
    printf("The element is at index %d\n",result);
   }
   else{
    printf("Element not found\n");
   }
   return 0;
}

int binsearch(int array[],int low,int high,int key){
    if(low>high){
        return -1;
    }
    int mid=(low+high)/2;
    if(array[mid]==key){
         return mid;
    }
    else if(array[mid]>key){
        binsearch(array,low,mid-1,key);
    }
    else if(array[mid]<key){
        binsearch(array,mid+1,high,key);
    }
 }
    

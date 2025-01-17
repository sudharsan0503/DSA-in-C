#include<stdio.h>
int n;
int binsearch(int array[],int,int);

int main(){
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
    
   int result=binsearch(array,n,key);

   if(result!=-1){
    printf("The element is at index %d\n",result);
   }
   else{
    printf("Element not found\n");
   }
   return 0;
}

int binsearch(int array[],int n,int key){
    int i,low,high,mid;
    low=0;
    high=n-1;
    while(low<=high){
          mid=(low+high)/2;
          if(array[mid]==key){
            return mid;
          }
          if(array[mid]>key){
            high=mid-1;
          }
          if(array[mid]<key){
            low=mid+1;
          }
    }
    return -1;
}
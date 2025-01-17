#include<stdio.h>
void insertionsort(int array[],int n);

int main(){
    int n,i;
    printf("Enter size of array:");
    scanf("%d",&n);
    
    int array[n];                      // very very important .declaration of array.

    for(i=0;i<n;i++){
       printf("Enter array elements:");
       scanf("%d",&array[i]);            //remember array[i]
    }

    insertionsort(array,n);

    printf("Sorted array is:");
    for(i=0;i<n;i++){
       printf("%d ",array[i]);
    }

    return 0;
}

void insertionsort(int array[],int n){
       int i,j,temp;                   //not taking from i=0 as 1st element will always considered to be sorted
       for(i=1;i<n;i++){              //note that not <=n it is <n
          temp=array[i];                        //stores current element
          j=i-1;
              while(j>=0 && array[j]>temp){
                   array[j+1]=array[j];         //if greater then greater element will go front and smaller will come back
                   j--;                        //decrementation to go till index 0
                   }
        array[j+1]=temp;  //inserts temp into the correct position in the sorted list
       }
}
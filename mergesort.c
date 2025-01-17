#include<stdio.h>

void mergesort(int array[],int low,int mid,int high);
void merge(int array[],int,int);
int n;

int main(){

    printf("Enter size of array:");
    scanf("%d",&n);

    int array[n];

    for(int i=0;i<n;i++){
        printf("Enter array elements:");
        scanf("%d",&array[i]);
    }

    int low = 0; 
    int high = n-1;
    merge(array,low,high);

    return 0;
}

void merge(int array[],int low,int high){
        if(low<high){
            int mid=(low+high)/2;
            merge(array,low,mid);
            merge(array,mid+1,high);
            mergesort(array,low,mid,high);
        }
}

void mergesort(int array[],int low,int mid,int high){
    int i,j,k,temp[n];

    i=low;          //1st sorted array low
    j=mid+1;        //2nd sorted array low
    k=low;          //new array low
    
    //for merging both 1st and 2nd sorted array
    while(i<=mid && j<=high){           //checking if it comes till last element of their respective array's
           if(array[i]<=array[j]){
                 temp[k]=array[i];
                 i++;
                 k++;
            }
            else{                     //array[i]>=array[j]
               temp[k]=array[j];
               j++;
               k++;
            }
    }

    if(i>mid){             //if i exceeds mid value
       while(j<=high){     //then insert only 2nd array's sorted elements
          temp[k]=array[j];
          k++;
          j++;
       }    
    }
    else{                  //if j exceeds mid value 
        while(i<=mid){      //then insert only 1st array's sorted elements
            temp[k]=array[i];
            i++;
            k++;
        }
    }

    for(int i=low;i<=high;i++){
         array[i]=temp[i];
    }

    printf("Sorted array is: ");
    for(i=low;i<=high;i++){
        printf("%d ",array[i]);
    }
    printf("\n");
}
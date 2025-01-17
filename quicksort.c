#include<stdio.h>

int quicksort(int array[],int lb,int hb);
int partition(int array[],int lb,int hb);
int swap(int array[],int,int);
int n;

int main(){
    printf("This is Quick sort\n");
    int i,lb,hb;                            //lb-lower bound,hb-higher bound
    printf("Enter size of array:");
    scanf("%d",&n);

    int array[n];

    for(i=0;i<n;i++){
        printf("Enter array value:");
        scanf("%d",&array[i]);
    }
    
    lb=0;
    hb=n-1;
    quicksort(array,lb,hb);

    printf("The sorted array is:");
    for(i=0;i<n;i++){
        printf("%d ",array[i]);
    }
    return 0;
}

int quicksort(int array[],int lb,int hb){
    if(lb<hb){
        int loc=partition(array,lb,hb);
        quicksort(array,lb,loc-1);
        quicksort(array,loc+1,hb);
    }
return 0;
}

int partition(int array[],int lb,int hb){
    int pivot,start,end;
    pivot=array[lb];
    start=lb,end=hb;
    while(start<end){
        while(array[start]<=pivot){
            start++;
        }
        while(array[end]>pivot){
            end--;
        }
        if(start<end){             
            swap(array,start,end);
            start++;       //after swapping updating
            end--;
        }
    }
    swap(array,lb,end);
    return end;
}

int swap(int array[],int low,int high){
       int temp=array[low];
       array[low]=array[high];
       array[high]=temp;
       return 0;
}
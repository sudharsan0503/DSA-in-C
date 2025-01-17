#include<stdio.h>

int selectionsort(int array[]);
int swap(int array[],int,int);
int n;

int main(){
    printf("This is selection sort\n");
    int i;
    printf("Enter size of array:");
    scanf("%d",&n);

    int array[n];

    for(i=0;i<n;i++){
        printf("Enter array value:");
        scanf("%d",&array[i]);
    }

    selectionsort(array);

    printf("The sorted array is:");
    for(i=0;i<n;i++){
        printf("%d ",array[i]);
    }
    return 0;
}

int selectionsort(int array[]){
    int i,j,min;
    for(i=0;i<n-1;i++){    //n-1 as n-1 passes
        min=i;
        for(j=i+1;j<n;j++){
            if(array[j]<array[min]){
                min=j;
            }
        }
    if(min!=i){
        swap(array,i,min);
    }
    }
return 0; 
}

int swap(int array[],int first,int min){
    int temp=array[first];
    array[first]=array[min];
    array[min]=temp;
    return 0;
}

#include<stdio.h>

void TOH(int n,char source,char auxillary,char destination){
    if(n==1){
        printf("Move disk 1 from %c to %c\n",source,destination);
        return;
    }
    TOH(n-1,source,destination,auxillary);
    printf("Move disk %d from %c to %c\n",n,source,auxillary);
    TOH(n-1,auxillary,source,destination);
}

int main(){
    int n;
    printf("Enter number of disks:");
    scanf("%d",&n);

    printf("Steps to solve tower of hanoi with %d disks:\n",n);
    TOH(n,'A','B','C');
    return 0;
}
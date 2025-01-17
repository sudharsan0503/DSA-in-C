#include<stdio.h>
#define max 50

int queue[max];
int front=-1;
int rear=-1;

int isfull(){
    return rear==max-1;
}

int isempty(){
    return front==-1 && rear==-1;
}

void enqueue(int val){
    if(isfull()){
        printf("Stack overflow\n");
        return;
    }
    else if(isempty()){
        rear=front=0;
    }
    else{
        rear++;
    }
    queue[rear]=val;
}

int dequeue(){
    if(isempty()){
        printf("Stack underflow\n");
        return -1;
    }
    int val=queue[front];
    if(rear==front){
        rear=front=-1;
    }
    else{
        front++;
    }
    return val;
}

int peek(){
    if (isempty()) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue[front];
}

void display() {
    if (isempty()) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main() {
    int choice,value;
    do {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                value = dequeue();
                if (value != -1)
                    printf("Dequeued value: %d\n", value);
                break;
            case 3:
                value =peek();
                if (value != -1)
                    printf("Front element: %d\n", value);
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 5);
    return 0;
}







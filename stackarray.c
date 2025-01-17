#include<stdio.h>
#define max 50

int stack[max];
int top=-1;

void push(int val){
    if(top==max-1){
        printf("Stack overflow\n");
        return;
    }
    top++;
    stack[top]=val;
}

int pop(){
    if(top==-1){
        printf("Stack underflow\n");
        return -1;
    }
    int val=stack[top];
    top--;
    return val;
}

int peek(){
    if(top==-1){
        printf("Stack is empty");
        return-1;
    }
    return stack[top];
}

void display(){
     if(top==-1){
        printf("Stack is empty\n");
        return ;
     }
     printf("Stack: ");
     for(int i=top;i>=0;i--){
        printf("%d ",stack[i]);
     }
}

int main() {
    int choice, value;

    do {
        printf("\nStack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(value);
                break;
            case 2:
                value = pop();
                if (value != -1)
                    printf("Popped value: %d\n", value);
                break;
            case 3:
                value = peek();
                if (value != -1)
                    printf("Top element: %d\n", value);
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
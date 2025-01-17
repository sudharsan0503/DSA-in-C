#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node* llink;
    int data;
    struct node* rlink;
};

typedef struct node NODE;

NODE* createnode(int x) {
    NODE* nn = (NODE*)malloc(sizeof(NODE));
    nn->data = x;
    nn->llink = NULL;
    nn->rlink = NULL;
    return nn;
}

void traverse(NODE* head) {
    NODE* temp = head;

    if (head == NULL) {
        printf("Empty list\n");
        return;
    }

    printf("Head <-> ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->rlink;
    }
    printf("NULL\n");
}

NODE* delete(NODE* head, int value) {
    // Handle empty list case
    if (head == NULL) {
        return NULL; // Indicate deletion failure
    }

    // Handle deletion of the head node
    if (head->data == value) {
        NODE* temp = head;
        head = head->rlink; // Update head to point to the next node
        free(temp);
        return head;
    }

    // Traverse the list to find the node to delete
    NODE* current = head;
    NODE* previous = NULL; // Keep track of the previous node

    while (current != NULL && current->data != value) {
        previous = current;
        current = current->rlink;
    }

    // Node not found
    if (current == NULL) {
        return head; // No change to the list
    }

    // Delete the found node
    previous->rlink = current->rlink;
    free(current);

    return head;
}

int main() {
    int ch, val;
    NODE* head = NULL; // Initially, the list is empty

    do {
        printf("\n1. Create Node\n");
        printf("2. Traverse\n");
        printf("3. Delete\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Enter value for the new node: ");
                scanf("%d", &val);
                NODE* new_node = createnode(val);
                if (head == NULL) { // If list is empty, set new node as head
                    head = new_node;
                } else {
                    // Find the last node and link the new node to it
                    NODE* temp = head;
                    while (temp->rlink != NULL) {
                        temp = temp->rlink;
                    }
                    temp->rlink = new_node;
                }
                break;
            case 2:
                traverse(head);
                break;
            case 3:
                if (head == NULL) {
                    printf("List is empty. Cannot delete.\n");
                } else {
                    printf("Enter value to delete: ");
                    scanf("%d", &val);
                    head = delete(head, val);
                }
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (ch != 4);

    // Free remaining nodes when the list becomes empty
    while (head != NULL) {
        NODE* temp = head;
        head = head->rlink;
        free(temp);
    }

    return 0;
}

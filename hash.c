#include <stdio.h>
#include <stdlib.h>

// Structure for each element in the linked list
typedef struct Node {
    int key;
    struct Node* next;
} Node;

// Structure for the hash table
typedef struct {
    Node* table; // Changed to Node* instead of Node**
    int size;
} HashTable;

// Function prototypes
void initializeHashTable(HashTable* table, int size);
int hashFunction(int key, int size);
void insert(HashTable* table, int key);
int search(HashTable* table, int key);
void display(HashTable* table);
void freeHashTable(HashTable* table);

int main() {
    HashTable table;
    int size, choice, key;

    printf("Enter the size of the hash table: ");
    scanf("%d", &size);

    initializeHashTable(&table, size);

    do {
        printf("\n-- Hash Table Operations --\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(&table, key);
                break;
            case 2:
                printf("Enter the key to search: ");
                scanf("%d", &key);
                if (search(&table, key)) {
                    printf("Key found: %d\n", key);
                } else {
                    printf("Key not found.\n");
                }
                break;
            case 3:
                display(&table);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    freeHashTable(&table);

    return 0;
}

// Initialize the hash table
void initializeHashTable(HashTable* table, int size) {
    table->table = (Node*)malloc(sizeof(Node) * size); // Changed allocation
    table->size = size;
    // Initialize each slot with NULL (empty linked list)
    for (int i = 0; i < size; i++) {
        table->table[i].next = NULL; // Initialize next pointer of each node
    }
}

// Hash function
int hashFunction(int key, int size) {
    return key % size;
}

// Insert a key into the hash table
void insert(HashTable* table, int key) {
    int index = hashFunction(key, table->size);
    // Create a new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;
    // Insert into the linked list at the calculated index
    Node* current = &table->table[index]; // Get the head node of the list
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// Search for a key in the hash table
int search(HashTable* table, int key) {
    int index = hashFunction(key, table->size);
    // Traverse the linked list at the calculated index
    Node* current = table->table[index].next; // Skip the head node
    while (current != NULL) {
        if (current->key == key) {
            return 1; // Key found
        }
        current = current->next;
    }
    return 0; // Key not found
}

// Display the contents of the hash table
void display(HashTable* table) {
    printf("Hash Table Contents:\n");
    for (int i = 0; i < table->size; i++) {
        printf("Index %d:", i);
        Node* current = table->table[i].next; // Skip the head node
        while (current != NULL) {
            printf(" -> Key: %d", current->key);
            current = current->next;
        }
        printf("\n");
    }
}

// Free memory allocated for hash table and linked lists
void freeHashTable(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        Node* current = table->table[i].next; // Skip the head node
        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->table);
}

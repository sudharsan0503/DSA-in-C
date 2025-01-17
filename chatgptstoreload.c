#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 10
#define MAX_FILENAME_LENGTH 100

struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

struct AdjList {
    struct AdjListNode* head;
};

struct Graph {
    int V;
    struct AdjList* array;
};

struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        struct AdjListNode* currentNode = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (currentNode) {
            printf("-> %d", currentNode->dest);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}

void storeGraph(struct Graph* graph, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "%d\n", graph->V);

        for (int v = 0; v < graph->V; ++v) {
            struct AdjListNode* currentNode = graph->array[v].head;
            fprintf(file, "%d:", v);
            while (currentNode) {
                fprintf(file, " %d", currentNode->dest);
                currentNode = currentNode->next;
            }
            fprintf(file, "\n");
        }
        fclose(file);
        printf("Graph stored to file '%s'.\n", filename);
    } else {
        printf("Error opening file.\n");
    }
}

struct Graph* loadGraph(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        int V;
        fscanf(file, "%d", &V);
        struct Graph* graph = createGraph(V);
        int v, dest;
        char c;
        while (!feof(file)) {
            fscanf(file, "%d%c", &v, &c);
            while (c != '\n') {
                fscanf(file, "%d%c", &dest, &c);
                addEdge(graph, v, dest);
            }
        }
        fclose(file);
        printf("Graph loaded from file '%s'.\n", filename);
        return graph;
    } else {
        printf("Error opening file.\n");
        return NULL;
    }
}

int main() {
    int choice;
    int numVertices, numEdges;
    char filename[MAX_FILENAME_LENGTH];
    struct Graph* graph = NULL;

    do {
        printf("\nMenu:\n");
        printf("1. Create graph\n");
        printf("2. Print graph\n");
        printf("3. Store graph to file\n");
        printf("4. Load graph from file\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of vertices in the graph: ");
                scanf("%d", &numVertices);
                graph = createGraph(numVertices);
                printf("Enter the number of edges: ");
                scanf("%d", &numEdges);
                printf("Enter the edges (source destination):\n");
                for (int i = 0; i < numEdges; ++i) {
                    int src, dest;
                    scanf("%d %d", &src, &dest);
                    addEdge(graph, src, dest);
                }
                break;
            case 2:
                if (graph != NULL) {
                    printf("Graph:\n");
                    printGraph(graph);
                } else {
                    printf("Graph is not created yet.\n");
                }
                break;
            case 3:
                if (graph != NULL) {
                    printf("Enter the filename to store the graph: ");
                    scanf("%s", filename);
                    storeGraph(graph, filename);
                } else {
                    printf("Graph is not created yet.\n");
                }
                break;
            case 4:
                printf("Enter the filename to load the graph from: ");
                scanf("%s", filename);
                graph = loadGraph(filename);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}

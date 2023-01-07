#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 65535

// Define a node structure
typedef struct node {
    int data;
    struct node* next;
} node;

// Function prototypes
int Member(node* head, int data);
int Insert(node** head, int data);
int Delete(node** head, int data);
void print_list(node* head);
pthread_mutex_t mutex_lock;

int main() {
    // Seed the random number generator
    srand(time(0));

    // Create the head of the list
    node* head = NULL;

    // Populate the list with n random values
    int n = 10;
    for (int i = 0; i < n; i++) {
        int data = rand() % MAX_VALUE;
        Insert(&head, data);
    }

    // Perform m random operations on the list
    int m = 100;

    caseNumber = 1;
    int memberOperations;
    int insertOperations;
    int deleteOperations;
    switch (caseNumber) {
        case 0:
            memberOperations = n * 0.99;
            insertOperations = n * 0.005;
            deleteOperations = n * 0.005;
        case 1:
            memberOperations = n * 0.9;
            insertOperations = n * 0.05;
            deleteOperations = n * 0.05;
        case 2:
            memberOperations = n * 0.5;
            insertOperations = n * 0.25;
            deleteOperations = n * 0.25;
    }

    while (memberOperations + insertOperations + deleteOperations > 0) {
        int op = rand() % 3;
        int data = rand() % MAX_VALUE;
        switch (op) {
            case 0:
                if (memberOperations > 0) {
                    Member(head, data);
                    memberOperations --;
                }
                break;
            case 1:
                if (insertOperations > 0) {
                    Insert(&head, data);
                    insertOperations--;
                }
                break;
            case 2:
                if (deleteOperations > 0) {
                    Delete(&head, data);
                    deleteOperations--;
                }
                break;
        }
    }
    // Print the final list
    print_list(head);

    return 0;
}

// Check if a value is in the list
int Member(node* head, int data) {
    node* current = head;
    while (current != NULL) {
        if (current->data == data) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Insert a new value into the list
int Insert(node** head, int data) {
    if (Member(*head, data)) {
        return 0;
    }

    node* new_node = (node*) malloc(sizeof(node));
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
    return 1;
}

// Delete a value from the list
int Delete(node** head, int data) {
    node* current = *head;
    node* prev = NULL;
    while (current != NULL) {
        if (current->data == data) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

// Print the contents of the list
void print_list(node* head) {
    printf("List: ");
    node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

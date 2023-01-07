#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

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

struct thread_args
{
    long numOperations;
    unsigned short threadId;
    long numThreads;
    short unsigned seed;
    struct list_node_s **head;
};

int main() {
    // Seed the random number generator
    srand(time(0));

    // Create the head of the list
    node* head = NULL;

    // Populate the list with n random values
    int n = 1000;
    for (int i = 0; i < n; i++) {
        int data = rand() % MAX_VALUE;
        Insert(&head, data);
    }

    // Perform m random operations on the list
    int m = 10000;

    int caseNumber = 1;
    int threadCount = 8;

    int memberOperations;
    int insertOperations;
    int deleteOperations;
    switch (caseNumber) {
        case 0:
            memberOperations = m * 0.99;
            insertOperations = m * 0.005;
            deleteOperations = m * 0.005;
        case 1:
            memberOperations = m * 0.9;
            insertOperations = m * 0.05;
            deleteOperations = m * 0.05;
        case 2:
            memberOperations = m * 0.5;
            insertOperations = m * 0.25;
            deleteOperations = m * 0.25;
    }
    clock_t start, end;
    double execution_time;

    start = clock();
    
    pthread_t *threadHandles;
    pthread_mutex_init(&mutex_lock, NULL);
    threadHandles = malloc(threadCount * sizeof(pthread_t));
    for (int t = 0; t < threadCount; t++) {
        struct thread_args *thread_args_struct = malloc(sizeof(struct thread_args));
        thread_args_struct->numOperations = m;
        thread_args_struct->head = head;
        thread_args_struct->threadId = t;
        thread_args_struct->numThreads = threadCount;
        thread_args_struct->seed = t + 1000;
        pthread_create(&threadHandles[thread], NULL, threadOperation, (void *)thread_args_struct);
    }
    for (int t = 0; t < threadCount; ++t)
    {
        pthread_join(threadHandles[t], NULL);
    }
    
    end = clock();
    free(threadHandles);
    pthread_mutex_destroy(&mutex_lock);

    execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("execution_time is %f\n", execution_time);

    



    return 0;
}

void *threadOperation() {
    while (memberOperations + insertOperations + deleteOperations > 0) {
        int op = rand() % 3;
        int data = rand() % MAX_VALUE;
        switch (op) {
            case 0:
                pthread_mutex_lock(&mutex_lock);
                if (memberOperations > 0) {                   
                    Member(head, data);
                    memberOperations --;
                }
                pthread_mutex_unlock(&mutex_lock);
                break;
            case 1:
                pthread_mutex_lock(&mutex_lock);
                if (insertOperations > 0) {                   
                    Insert(&head, data);
                    insertOperations--;
                }
                pthread_mutex_unlock(&mutex_lock);
                break;
            case 2:
                pthread_mutex_lock(&mutex_lock);
                if (deleteOperations > 0) {                    
                    Delete(&head, data);                    
                    deleteOperations--;
                }
                pthread_mutex_unlock(&mutex_lock);
                break;
        }
    }
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
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
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

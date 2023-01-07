#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#define MAX_VALUE 65535
#define NUM_THREADS 1

// Define a node structure
typedef struct node {
    int data;
    struct node* next;
} node;

struct thread_args
{
    long memberOps;
    long insertOps;
    long deleteOps;
    node* head;
};

// Function prototypes
int Member(node* head, int data);
void Insert(node** head, int data);
void Delete(node** head, int data);
void print_list(node* head);
pthread_mutex_t mutex_lock;
pthread_t *threadHandles;
int memberOperations;
int insertOperations;
int deleteOperations;

void *threadOperation(void* thread_args) {
    struct thread_args *args = (struct thread_args *)thread_args;
    long memberOps = args->memberOps;
    long insertOps = args->insertOps;
    long deleteOps = args->deleteOps;
    node* head = args->head;
    while (memberOps + insertOps + deleteOps > 0) {
        int op = rand() % 3;
        int data = rand() % 10000;
        switch (op) {
            case 0:
                if (memberOps > 0) {
                    pthread_mutex_lock(&mutex_lock);
                    Member(head, data);
                    pthread_mutex_unlock(&mutex_lock);
                    memberOps --;
                }
                break;
            case 1:
                if (insertOps > 0) {
                    pthread_mutex_lock(&mutex_lock);
                    Insert(&head, data);
                    pthread_mutex_unlock(&mutex_lock);
                    insertOps--;
                }
                break;
            case 2:
                if (deleteOps > 0) {
                    pthread_mutex_lock(&mutex_lock);
                    Delete(&head, data);
                    pthread_mutex_unlock(&mutex_lock);
                    deleteOps--;
                }
                break;
        }
    }
}

int main() {
    int num_samples=97;
    float *timeResults = malloc(sizeof(int) * num_samples);
    int caseNumber = 0;
    while (caseNumber < 3) {
        for (int r = 0; r < num_samples; r++)
        {
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

            int threadCount = 8;
            pthread_mutex_init(&mutex_lock, NULL);
            threadHandles = malloc(threadCount * sizeof(pthread_t));
            for (int t = 0; t < threadCount; t++) {
                struct thread_args *thread_args_struct = malloc(sizeof(struct thread_args));
                thread_args_struct->memberOps = memberOperations / threadCount;
                thread_args_struct->insertOps = insertOperations / threadCount;
                thread_args_struct->deleteOps = deleteOperations / threadCount;
                thread_args_struct->head = head;
                pthread_create(&threadHandles[t], NULL, threadOperation, (void *)thread_args_struct);
            }

            for (int t = 0; t < threadCount; ++t)
            {
                pthread_join(threadHandles[t], NULL);
            }
            free(threadHandles);
            pthread_mutex_destroy(&mutex_lock);

            end = clock();
            execution_time = ((double)(end - start)) / CLOCKS_PER_SEC *1000;
            // printf("execution_time is %f\n", execution_time);
            timeResults[r]=execution_time;
        }
        // Print the final list
        // print_list(head);
        double sum;
        for (int t = 0; t < num_samples; t++)
        {
            sum = sum + timeResults[t];
        }
        double mean = sum / num_samples;
        printf("Mean is %f\n", mean);
        double sd = 0;
        for (int q = 0; q < num_samples; q++)
            sd += pow(timeResults[q] - mean, 2);
        sd = sqrt(sd / num_samples);
        printf("Standard Deviation is %f\n", sd);
        caseNumber++;
    }
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
void Insert(node** head, int data) {
    if (Member(*head, data)) {
        return;
    }

    node* new_node = (node*) malloc(sizeof(node));
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}

// Delete a value from the list
void Delete(node** head, int data) {
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
    // printf("List: ");
    node* current = head;
    while (current != NULL) {
        // printf("%d ", current->data);
        current = current->next;
    }
    // printf("\n");
}

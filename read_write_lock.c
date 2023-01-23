#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <pthread.h>

#define MAX_VALUE 65535
#define NUM_THREADS 1
int *operationsArray;
int *dataResults;

// Define a node structure
typedef struct node {
    int data;
    struct node* next;
} node;

struct thread_args
{
    unsigned short threadId;
    long threadOperations;
    long threadCount;
    node* head;
};

int Member(node* head_p, int data);
int Insert(node** head_pp, int data);
int Delete(node** head_pp, int data);
pthread_rwlock_t rwlock;
pthread_t *threadHandles;
int memberOperations;
int insertOperations;
int deleteOperations;

void *threadOperation(void* thread_args) {
    struct thread_args *args = (struct thread_args *)thread_args;
    long threadOperations = args->threadOperations;
    node* head = args->head;
    unsigned short threadId = args->threadId;
    long threadCount = args->threadCount;

    while(threadId < threadOperations) {
        int data = dataResults[threadId];
        if (operationsArray[threadId] == 0)
        {   
            pthread_rwlock_rdlock(&rwlock);
            Member(head,data);
            pthread_rwlock_unlock(&rwlock);
        }
        else if (operationsArray[threadId] == 1)
        {   
            pthread_rwlock_rdlock(&rwlock);
            Insert(&head,data);
            pthread_rwlock_unlock(&rwlock);
        }
        else if (operationsArray[threadId] == 2)
        {   
            pthread_rwlock_rdlock(&rwlock);
            Delete(&head,data);
            pthread_rwlock_unlock(&rwlock);
        }
        threadId += threadCount;
    }
}

void setOrderOfOperations(long memberOperations,long insertOperations,long deleteOperations, int* operationsArray) {
    int i=0;
    while (memberOperations + insertOperations + deleteOperations > 0) {
        int operationType = rand() % 3;
        switch (operationType) {
            case 0:
                if (memberOperations > 0) {
                    operationsArray[i] = 0;
                    memberOperations--;
                    i++;
                }
                break;
            case 1:
                if (insertOperations > 0) {
                    operationsArray[i] = 1;
                    insertOperations--;
                    i++;
                }
                break;
            case 2:
                if (deleteOperations > 0) {
                    operationsArray[i] = 2;
                    deleteOperations--;
                    i++;
                }
                break;
            }
    }    
}

int main() {
    int num_samples=385;
    for (int caseNumber = 0; caseNumber < 3; caseNumber++) {
        float *timeResults = malloc(sizeof(int) * num_samples);
        for (int sample = 0; sample < num_samples; sample++)
        {
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

            dataResults = malloc(sizeof(int) * m);
            for (int i = 0; i < m; i++) {
                int data = rand() % MAX_VALUE;
                dataResults[i]=data;
            }

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
            operationsArray = malloc(sizeof(int) * m);
            setOrderOfOperations(memberOperations, insertOperations, deleteOperations, operationsArray);

            int threadCount = 8;
            int threadOperations = m;
            clock_t start, end;
            double execution_time;
            threadHandles = malloc(threadCount * sizeof(pthread_t));

            
            start = clock();
            pthread_rwlock_init(&rwlock, NULL);
            
            for (int t = 0; t < threadCount; t++) {
                struct thread_args *thread_args_struct = malloc(sizeof(struct thread_args));
                thread_args_struct->threadOperations = threadOperations;
                thread_args_struct->head = head;
                thread_args_struct->threadId = t;
                thread_args_struct->threadCount = threadCount;
                pthread_create(&threadHandles[t], NULL, threadOperation, (void *)thread_args_struct);
            }

            for (int t = 0; t < threadCount; ++t)
            {
                pthread_join(threadHandles[t], NULL);
            }
            free(threadHandles);
            pthread_rwlock_destroy(&rwlock);

            end = clock();


            execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
            timeResults[sample]=execution_time;
        }
 
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
    }
    return 0;
}

int Member(node* head_p, int value )
{
    node *curr_p = head_p;

    while (curr_p != NULL && curr_p->data < value)
        curr_p = curr_p->next;

    if (curr_p == NULL || curr_p->data > value)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int Insert(node** head_pp,int value)
{
    node *curr_p = *head_pp;
    node *pred_p = NULL;
    node *temp_p;

    while (curr_p != NULL && curr_p->data < value)
    {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }
    if (curr_p == NULL || curr_p->data > value)
    {
        temp_p = malloc(sizeof(struct node));
        temp_p->data = value;
        temp_p->next = curr_p;
        if (pred_p == NULL)
            *head_pp = temp_p;
        else
            pred_p->next = temp_p;
        return 1;
    }
    else
    {
        return 0;
    }
}

int Delete(node** head_pp,int value)
{
    node *curr_p = *head_pp;
    node *pred_p = NULL;

    while (curr_p != NULL && curr_p->data < value)
    {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p != NULL && curr_p->data == value)
    {
        if (pred_p == NULL)
        {
            *head_pp = curr_p->next;
            free(curr_p);
        }
        else
        {
            pred_p->next = curr_p->next;
            free(curr_p);
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

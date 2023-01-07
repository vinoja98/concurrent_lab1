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
unsigned bit;

typedef struct list_node_s
{
    int data;
    struct list_node_s *next;
}list_node_s;

struct thread_args
{
    long memberOps;
    long insertOps;
    long deleteOps;
    short unsigned seed;
    list_node_s* head;
};

int Member(list_node_s* head_p, int data);
int Insert(list_node_s** head_pp, int data);
int Delete(list_node_s** head_pp, int data);
pthread_mutex_t mutex_lock;
pthread_t *threadHandles;
int memberOperations;
int insertOperations;
int deleteOperations;

unsigned genUniqueRandNum(unsigned short *lfsr)
{
    bit = ((*lfsr >> 0) ^ (*lfsr >> 2) ^ (*lfsr >> 3) ^ (*lfsr >> 5)) & 1;
    return *lfsr = (*lfsr >> 1) | (bit << 15);
}

void *threadOperation(void* thread_args) {
    struct thread_args *args = (struct thread_args *)thread_args;
    long memberOps = args->memberOps;
    long insertOps = args->insertOps;
    long deleteOps = args->deleteOps;
    short unsigned seed = args->seed;
    list_node_s* head = args->head;

    clock_t start, end;
    double execution_time;
    start = clock();
    for (int i = 0; i < memberOps+insertOps+deleteOps; ++i){
        int data = dataResults[i];
        if (operationsArray[i] == 0)
        {   
            pthread_mutex_lock(&mutex_lock);
            Member(head,data);
            pthread_mutex_unlock(&mutex_lock);
        }
        else if (operationsArray[i] == 1)
        {   
            pthread_mutex_lock(&mutex_lock);
            Insert(&head,data);
            pthread_mutex_unlock(&mutex_lock);
        }
        else if (operationsArray[i] == 2)
        {   
            pthread_mutex_lock(&mutex_lock);
            Delete(&head,data);
            pthread_mutex_unlock(&mutex_lock);
        }
    }
}

int main() {
    int num_samples=97;
    
    int caseNumber = 0;
    while (caseNumber < 3) {
        float *timeResults = malloc(sizeof(int) * num_samples);
        for (int r = 0; r < num_samples; r++)
        {
            // Create the head of the list
            list_node_s* head = NULL;

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
            // operationsArray = malloc(sizeof(int) * m);
            // for (int i = 0; i < memberOperations; i++)
            // {
            //     operationsArray[i] = 0;
            // }
            // for (int i = memberOperations; i < memberOperations + insertOperations; i++)
            // {
            //     operationsArray[i] = 1;
            // }
            // for (int i = memberOperations + insertOperations; i < memberOperations + insertOperations + deleteOperations; i++)
            // {
            //     operationsArray[i] = 2;
            // }
            
            // struct timeval tv;
            // gettimeofday(&tv, NULL);
            // int usec = tv.tv_usec;
            // srand48(usec);
            // if (num_samples > 1)
            // {
            //     int i;
            //     for (i = num_samples - 1; i > 0; i--)
            //     {
            //         size_t j = (unsigned int)(drand48() * (i + 1));
            //         int t = operationsArray[j];
            //         operationsArray[j] = operationsArray[i];
            //         operationsArray[i] = t;
            //     }
            // }
            operationsArray = malloc(sizeof(int) * m);
            int i=0;
            while (memberOperations + insertOperations + deleteOperations > 0) {
                int op = rand() % 3;
                int data = rand() % MAX_VALUE;
                switch (op) {
                    case 0:
                        if (memberOperations > 0) {
                            operationsArray[i] = 0;
                            memberOperations--;
                            // printf("op is %d\n", operationsArray[i]);
                            i++;
                        }
                        break;
                    case 1:
                        if (insertOperations > 0) {
                            operationsArray[i] = 1;
                            // printf("op is %d\n", operationsArray[i]);
                            insertOperations--;
                            i++;
                        }
                        break;
                    case 2:
                        if (deleteOperations > 0) {
                            operationsArray[i] = 2;
                            // printf("op is %d\n", operationsArray[i]);
                            deleteOperations--;
                            i++;
                        }
                        break;
                    }
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
            clock_t start, end;
            double execution_time;
            start = clock();

            int threadCount = 1;
            pthread_mutex_init(&mutex_lock, NULL);
            threadHandles = malloc(threadCount * sizeof(pthread_t));
            for (int t = 0; t < threadCount; t++) {
                struct thread_args *thread_args_struct = malloc(sizeof(struct thread_args));
                thread_args_struct->memberOps = memberOperations / threadCount;
                thread_args_struct->insertOps = insertOperations / threadCount;
                thread_args_struct->deleteOps = deleteOperations / threadCount;
                thread_args_struct->head = head;
                thread_args_struct->seed = t + 1000;
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
int Member(list_node_s* head_p, int value )
{
    list_node_s *curr_p = head_p;

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

int Insert(list_node_s** head_pp,int value)
{
    list_node_s *curr_p = *head_pp;
    list_node_s *pred_p = NULL;
    list_node_s *temp_p;

    while (curr_p != NULL && curr_p->data < value)
    {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }
    if (curr_p == NULL || curr_p->data > value)
    {
        temp_p = malloc(sizeof(struct list_node_s));
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

int Delete(list_node_s** head_pp,int value)
{
    list_node_s *curr_p = *head_pp;
    list_node_s *pred_p = NULL;

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
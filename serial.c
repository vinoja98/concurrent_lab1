#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
// #include <plot.h>

#define MAX_VALUE 65535
#define NUM_THREADS 1
int *operationsArray;
float *timeResults;

typedef struct list_node_s
{
    int data;
    struct list_node_s *next;
}list_node_s;

int Member(list_node_s* head_p, int data);
int Insert(list_node_s** head_pp, int data);
int Delete(list_node_s** head_pp, int data);

int main() {
    int num_samples=97;
    // timeResults = malloc(sizeof(int) * num_samples);
    int caseNumber = 0;
    while (caseNumber < 3) {
        timeResults = malloc(sizeof(int) * num_samples);
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

            int caseNumber = 1;
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
            operationsArray = malloc(sizeof(int) * m);
            int i=0;
            while (memberOperations + insertOperations + deleteOperations > 0) {
                int op = rand() % 3;
                // int data = rand() % MAX_VALUE;
                switch (op) {
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
            int *dataResults = malloc(sizeof(int) * m);
            for (int i = 0; i < m; i++) {
                int data = rand() % MAX_VALUE;
                dataResults[i]=data;
            }
            clock_t start, end;
            double execution_time;
            start = clock();
            for (int i = 0; i < m; ++i){
                // int op = rand() % 3;
                int data = dataResults[i];
                if (operationsArray[i] == 0)
                {
                    Member(head,data);
                }
                else if (operationsArray[i] == 1)
                {
                    Insert(&head,data);
                }
                else if (operationsArray[i] == 2)
                {
                    Delete(&head,data);
                }
            }
            end = clock();
            execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
            // printf("time %d\n",r);
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

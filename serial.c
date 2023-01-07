#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <plot.h>

#define MAX_VALUE 65535
#define NUM_THREADS 1

// Define a node structure
typedef struct node {
    int data;
    struct node* next;
} node;

// Function prototypes
int Member(node* head, int data);
void Insert(node** head, int data);
void Delete(node** head, int data);
void print_list(node* head);

int main() {
    // Seed the random number generator
    int num_samples=97;
    float *timeResults = malloc(sizeof(int) * num_samples);
    for (int r = 0; r < num_samples; r++)
    {
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
        end = clock();
        execution_time = ((double)(end - start)) / CLOCKS_PER_SEC *1000 ;
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
     // Open plot device
    // plottable xyplot;
    // if (plot_open(xyplot) < 0) {
    //     fprintf(stderr, "error opening plot device\n");
    //     exit(1);
    // } 
    //  // Set plot title and axis labels
    // plot_set_title(xyplot, "Average Execution Time vs. Number of Threads");
    // plot_set_xlabel(xyplot, "Number of Threads");
    // plot_set_ylabel(xyplot, "Average Execution Time (s)");

    // // Set plot range
    // plot_set_range_x(xyplot, 0, NUM_THREADS + 1);
    // plot_set_range_y(xyplot, 0, 10);

    // // Add data point to plot
    // plot_add_point(xyplot, 1, mean);

    // plot_close();
    double sd = 0;
    for (int q = 0; q < num_samples; q++)
        sd += pow(timeResults[q] - mean, 2);
    sd = sqrt(sd / num_samples);
    printf("Standard Deviation is %f\n", sd);

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

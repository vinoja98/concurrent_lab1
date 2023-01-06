#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_VALUE 65535


typedef struct list_node_s {
    int data;
    struct list_node_s* next;
} 

int Member(struct list_node_s* head_p, int value);
void Insert(node** head, int data);
void Delete(node** head, int data);
void print_list(node* head);

int main() {
    // Seed the random number generator
    srand(time(0));

    // Create the head of the list
    node* head = NULL;

    int n = 10;
    for (int i = 0; i < n; i++) {
        int data = rand() % MAX_VALUE;
        Insert(&head, data);
    }


    int m = 100;
    clock_t start = clock();
    for (int i = 0; i < m; i++) {
        int op = rand() % 3;
        int data = rand() % MAX_VALUE;
        switch (op) {
            case 0:
                Member(head, data);
                break;
            case 1:
                Insert(&head, data);
                break;
            case 2:
                Delete(&head, data);
                break;
        }
    }
    clock_t end = clock();
    double time_taken = (double) (end - start) / CLOCKS_PER_SEC * 1000;

    printf("Time taken: %f milliseconds\n", time_taken);

    print_list(head);

    return 0;
}


int Member(struct list_node_s* head_p, int value) {
    struct list_node_s* curr_p = head_p;
    while (current != NULL && curr_p->data <value)
        curr_p =curr_p->next;
    if (curr_p == NULL || curr_p->data >value) {
        return 0;
    }
    else{
        return 1;
    }
}


void Insert(node** head, int data) {
    if (Member(*head, data)) {
        return;
    }

}

void Delete(node** head, int data) {
    // node* current = *head;
    // node* prev = NULL;
    // while (current != NULL) {
    //     if (current->data == data) {
    //         if (prev == NULL) {
    //             *head = current->next;
    //         } else {
    //             prev->next = current->next;
    //         }
    //         free(current);
    //         return;
    //     }
    //     prev = current;
    //     current = current->next;
    // }
}

void print_list(node* head) {
    printf("List: ");
    node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}


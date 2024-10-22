/* 
 * Linked Queue implementation
 */

#include <stdio.h>
#include <stdlib.h>

typedef enum {
    INT,
    CHAR,
    FLOAT,
    DOUBLE,
    PTR,
} QUEUE_TYPE; 

typedef struct Queue {
	void *value;
    QUEUE_TYPE value_type;
	struct Queue *next;
	struct Queue *bottom;
} Queue;

Queue *create_queue (int value_type) {
	Queue *new_queue = (Queue *) malloc(sizeof(Queue));
    new_queue->value_type = value_type;
	new_queue->next = NULL;
	new_queue->bottom = NULL;

	return new_queue;
}

void *insert_into_queue (Queue *queue_main, void *value_ptr) {
	Queue *new_element = (Queue *) malloc(sizeof(Queue));
	new_element->value_type = queue_main->value_type;
	new_element->value = value_ptr;
	new_element->next = NULL;

	Queue *tmp_ptr = queue_main;
	while (tmp_ptr->next != NULL) {
		tmp_ptr = tmp_ptr->next;
	}

	tmp_ptr->next = new_element;

	if (queue_main->bottom == NULL) {
		queue_main->bottom = new_element;
	}

	return value_ptr;
}

void *delete_element_queue (Queue *queue_main) {
	if (queue_main->bottom == NULL) {
		return NULL;
	}
	
	Queue *btm_ptr = queue_main->bottom;
	Queue *new_btm = btm_ptr->next;

	queue_main->next = btm_ptr->next;
	queue_main->bottom = btm_ptr->next;

	return btm_ptr->value;
}

void print_queue (Queue *queue_main) {
    Queue *tmp_ptr = queue_main->next;

    if (tmp_ptr == NULL) {
        return;
    }

    char* print_format = "";

    for (int i = 0; tmp_ptr->next != NULL; i++) {
        if (i != 0) {
            fprintf(stdout, " -> ");
        }

        printf("| i: %i |", i);
        switch (tmp_ptr->value_type) {
            case INT:
                fprintf(stdout, "| val: %i |", * (int *) tmp_ptr->value);
                break;
            case CHAR:
                fprintf(stdout, "| val: %c |", * (char *) tmp_ptr->value);
                break;
            case FLOAT:
                fprintf(stdout, "| val: %.2f |", * (float *) tmp_ptr->value);
                break;
            case DOUBLE:
                fprintf(stdout, "| val: %.2lf |", * (double *) tmp_ptr->value);
                break;
            case PTR:
                fprintf(stdout, "| val: %p |", tmp_ptr->value);
                break;
        }

        tmp_ptr = tmp_ptr->next;
    }

    fprintf(stdout, " -> NULL\n");
    return;
}


int main (int nargs, char **args) {
	Queue *queue = create_queue(INT);

	int foo = 10;
	int foo2 = 11;
	int foo3 = 13;
	int foo4 = 12;
	insert_into_queue(queue, &foo);
	insert_into_queue(queue, &foo2);
	insert_into_queue(queue, &foo3);
	insert_into_queue(queue, &foo4);

    print_queue(queue);

	delete_element_queue(queue);
    print_queue(queue);
	return 0;
}

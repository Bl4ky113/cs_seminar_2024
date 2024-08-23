/* 
 * Linked Pile implementation
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Pile {
	void *value;
	int value_size;
	struct Pile *next;
	struct Pile *bottom;
} Pile;

Pile *create_pile (int value_size) {
	Pile *new_pile = (Pile *) malloc(sizeof(Pile));
	new_pile->value_size = value_size;
	new_pile->next = NULL;
	new_pile->bottom = NULL;

	return new_pile;
}

void *insert_into_pile (Pile *pile_main, void *value_ptr) {
	Pile *new_element = (Pile *) malloc(sizeof(Pile));
	new_element->value_size = pile_main->value_size;
	new_element->value = value_ptr;
	new_element->next = NULL;

	Pile *tmp_ptr = pile_main;
	while (tmp_ptr->next != NULL) {
		tmp_ptr = tmp_ptr->next;
	}

	tmp_ptr->next = new_element;

	if (pile_main->bottom == NULL) {
		pile_main->bottom = new_element;
	}

	return value_ptr;
}

void *delete_element_pile (Pile *pile_main) {
	if (pile_main->bottom == NULL) {
		return NULL;
	}
	
	Pile *btm_ptr = pile_main->bottom;
	Pile *new_btm = btm_ptr->next;

	pile_main->next = btm_ptr->next;
	pile_main->bottom = btm_ptr->next;

	return btm_ptr->value;
}


int main (int nargs, char **args) {
	Pile *pile = create_pile(sizeof(int));

	int foo = 10;
	int foo2 = 11;
	int foo3 = 13;
	int foo4 = 12;
	insert_into_pile(pile, &foo);
	insert_into_pile(pile, &foo2);
	insert_into_pile(pile, &foo3);
	insert_into_pile(pile, &foo4);
	printf("%p, %p\n", pile->bottom, pile->next);
	
	printf("%d\n", *(int *) pile->bottom->value);
	printf("%d\n", *(int *) pile->next->value);

	delete_element_pile(pile);
	printf("%d\n", *(int *) pile->bottom->value);
	printf("%d\n", *(int *) pile->next->value);

	return 0;
}

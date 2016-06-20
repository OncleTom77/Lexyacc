#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "minipseudlist.h"

t_list_chain *list_chain_create(char *var, double val) {
    
  	t_list_chain *maillon = malloc(sizeof(t_list_chain));

	maillon->name 	= strdup(var);
	maillon->value 	= val;
	maillon->next 	= NULL;

	return maillon;
}

void list_chain_append(t_list_chain **list, char *var, double val) {
  
	t_list_chain *newMaillon = list_chain_create(var, val);

	while (*list != NULL) {
		
		if (strcmp((*list)->name, var) == 0) {
			(*list)->value = val;
			return;
		}
		list = &(*list)->next;
	}

	*list = newMaillon;
}

double get_value_in_list(t_list_chain *list, char *var) {
  
	t_list_chain *elem = list;

	while (elem != NULL) {
		if (strcmp(elem->name, var) == 0) {
			return elem->value;
		}
		elem = elem->next;
	}
	return 0.0;
}
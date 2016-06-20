#include "includes.h"

t_list_chain *list_chain_create(char *name, double value) {

	t_list_chain *new 	= malloc(sizeof(t_list_chain));

	new->name 			= strdup(name);
	new->value 			= value;
	new->next 			= NULL;

	return new;
}

void list_chain_append(t_list_chain **list, char *name, double value) {

	t_list_chain *new = list_chain_create(name, value);

	while (*list) {
		if (strcmp((*list)->name, name) == 0) {
			(*list)->value = value;
			return;
		}

		list = &(*list)->next;
	}

	*list = new;
}

double get_value_in_list(t_list_chain *list, char *name) {

	t_list_chain *save = list;

	while (save) {
		if (strcmp(save->name, name) == 0) {
			return save->value;
		}
		save = save->next;
	}

	return 0.;
}

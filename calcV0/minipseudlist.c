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

	printf("Unknown var '%s'...\n", name);
	exit(EXIT_FAILURE);
}

t_list_chain_function *list_chain_function_create(char *name, Node *node) {

	t_list_chain_function *new 	= malloc(sizeof(t_list_chain_function));
	new->name					= strdup(name);
	new->node 					= node;
	new->next					= NULL;

	return new;
}

void list_chain_function_append(t_list_chain_function **list, char *name, Node *node) {

	t_list_chain_function *new = list_chain_function_create(name, node);

	while (*list) {
		if (strcmp((*list)->name, name) == 0) {
			(*list)->node = node;
			return;
		}

		list = &(*list)->next;
	}

	*list = new;
}

Node *get_node_in_list_function(t_list_chain_function *list, char *name) {

	t_list_chain_function *save = list;

	while (save) {
		if (strcmp(save->name, name) == 0) {
			return save->node;
		}
		save = save->next;
	}

	return NULL;
}

void list_chain_free(t_list_chain **list) {

	t_list_chain *to_delete;

	while (*list) {
		to_delete = *list;
		list = &((*list)->next);
		free(to_delete->name);
		free(to_delete);
	}
}

void list_chain_function_free(t_list_chain_function **list) {

	t_list_chain_function *to_delete;

	while (*list) {
		to_delete = *list;
		list = &((*list)->next);
		free(to_delete->name);
		node_free(to_delete->node);
		free(to_delete);
	}
}

void node_free(Node *node) {

	if(!node)
		return;

	if(node->type == NTVAR || node->type == NTVARFUNCT) {
		free(node->var);
	} else if(node->children != NULL && node->type != NTNUM) {
		node_free(node->children[0]);
		node_free(node->children[1]);
	}

	free(node);
}

#ifndef MINIPSEUDLIST
#define MINIPSEUDLIST

#include "includes.h"

typedef struct t_list_chain {
	char 	*name;
	double 	value;
	struct 	t_list_chain *next;
} t_list_chain;

typedef struct t_list_chain_function {
	char 	*name;
	Node	*node;
	struct 	t_list_chain_function *next;
} t_list_chain_function;

t_list_chain *list_chain_create(char *, double);

void list_chain_append(t_list_chain **, char *, double);

double get_value_in_list(t_list_chain *, char *);

t_list_chain_function *list_chain_function_create(char *, Node *);

void list_chain_function_append(t_list_chain_function **, char *, Node *);

Node *get_node_in_list_function(t_list_chain_function *, char *);

#endif

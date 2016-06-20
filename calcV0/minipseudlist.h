#ifndef MINIPSEUDLIST
#define MINIPSEUDLIST
	
	typedef struct t_list_chain {
		char 	*name;
		double 	value;
		struct 	t_list_chain *next;
	} t_list_chain;

	t_list_chain *list_chain_create(char *, double);
	void list_chain_append(t_list_chain **, char *, double);
	double get_value_in_list(t_list_chain *, char *);

#endif
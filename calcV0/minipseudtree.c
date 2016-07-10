#include "includes.h"

Node *create_node(int type) {
	Node *newnode 		= malloc(sizeof(Node));
	newnode->type 		= type;
	newnode->children 	= NULL;

	return newnode;
}

Node *add_children_to_node(Node *father, Node *child1, Node *child2) {

	father->children 	= malloc(sizeof(Node *) * 2);
	father->children[0] = child1;
	father->children[1] = child2;

	return father;
}

const char *node_to_string(Node *node) {	
	
	char *res;
	
	switch (node->type) {
		case NTEMPTY:
			return "NTEMPTY";

		case NTINSTLIST:
			return "NTINSTLIST";

		case NTINST:
			return "NTINST";

		case NTNUM:
			res = malloc(sizeof(char) * 32);
			sprintf(res, "NTNUM -> %f", node->val);
			return res;

		case NTVAR:
			res = malloc(sizeof(char) * 32);
			sprintf(res, "NTVAR -> %s", node->var);
			return res;
	
		case NTPLUS:
			return "NTPLUS";
		case NTMIN:
			return "NTMIN";
		case NTMULT:
			return "NTMULT";
		case NTDIV:
			return "NTDIV";
		case NTPOW:
			return "NTPOW";

		case NTEGAL:
			return "NTEGAL";

		case NTSI:
			return "NTSI";
		case NTALORS:
			return "NTALORS";
		case NTSINON:
			return "NTSINON";

		case NTTANTQUE:
			return "NTTANTQUE";

		case NTFOR:
			return "NTFOR";

		case NTFORTRAIT:
			return "NTFORTRAIT";

		case NTCOMPEGAL:
			return "NTCOMPEGAL";
		case NTCOMPDIFF:
			return "NTCOMPDIFF";
		case NTCOMPINF:
			return "NTCOMPINF";
		case NTCOMPSUP:
			return "NTCOMPSUP";

		case NTPRINT:
			return "NTPRINT";
		
		default:
			return "UNK";
	};
}

void recursive_graph(Node *node, int n) {
	
	int i;

	if (!node)
		return;

	for (i = 0; i < n; i++)
		printf(" ");

	printf("%s\n", node_to_string(node));
	
	// Hack : No children only if null or number or variable or PRINT
	if ((node->children != NULL) && (node->type != NTNUM) && (node->type != NTVAR)) {
		recursive_graph(node->children[0], n + 1);
		recursive_graph(node->children[1], n + 1);
	}
}

void print_graph(Node *root) {
	recursive_graph(root, 0);
}

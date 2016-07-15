#include "includes.h"

double evalExpr(Node *node, t_list_chain **list) {
	
	switch (node->type) {
		case NTEMPTY:
			return 0.;
		case NTNUM:
			return node->val;
		case NTVAR:
			return get_value_in_list(*list, node->var);
		case NTPLUS:
			return evalExpr(node->children[0], list) + evalExpr(node->children[1], list);
		case NTMIN:
			return evalExpr(node->children[0], list) - evalExpr(node->children[1], list);
		case NTMULT:
			return evalExpr(node->children[0], list) * evalExpr(node->children[1], list);
		case NTDIV:
			return evalExpr(node->children[0], list) / evalExpr(node->children[1], list);
		case NTPOW:
			return pow(evalExpr(node->children[0], list), evalExpr(node->children[1], list));
		default:
			printf("Error in evalExpr ... Wrong node type: %s\n", node_to_string(node));
			exit(EXIT_FAILURE);
	};
}

double evalInst(Node *node, t_list_chain **list, t_list_chain_function **list_function) {

	switch (node->type) {
		case NTEMPTY:
			return 0.;

		case NTINSTLIST:
			evalInst(node->children[0], list, list_function);
			evalInst(node->children[1], list, list_function);
			return 0.;

		case NTNUM:
		case NTVAR:
		case NTPLUS:
		case NTMIN:
		case NTMULT:
		case NTDIV:
		case NTPOW:
			return evalExpr(node, list);

		case NTEGAL: {
			double value = evalExpr(node->children[1], list);
			list_chain_append(list, node->children[0]->var, value);
			return value;
		}

		case NTSI:
			// SI ... ALORS ... SINON
			if (node->children[1]->type == NTALORS) {
				if (evalInst(node->children[0], list, list_function) != 0)
					evalInst(node->children[1]->children[0], list, list_function);
				else
					evalInst(node->children[1]->children[1], list, list_function);
			} else {
				// SI ... ALORS ...
				if (evalInst(node->children[0], list, list_function) != 0)
					evalInst(node->children[1], list, list_function);
			}
			return 0.;

		case NTTANTQUE:
			while (evalInst(node->children[0], list, list_function) != 0)
				evalInst(node->children[1], list, list_function);
			return 0.;

		case NTFOR:
			for (evalInst(node->children[0]->children[0], list, list_function); evalInst(node->children[0]->children[1], list, list_function) != 0; evalInst(node->children[1]->children[0], list, list_function))
				evalInst(node->children[1]->children[1], list, list_function);
			return 0.;

		case NTCOMPEGAL:
			return (evalExpr(node->children[0], list) == evalExpr(node->children[1], list)) ? 1. : 0.;

		case NTCOMPDIFF:
			return (evalExpr(node->children[0], list) != evalExpr(node->children[1], list)) ? 1. : 0.;

		case NTCOMPINF:
			return (evalExpr(node->children[0], list) < evalExpr(node->children[1], list)) ? 1. : 0.;
		
		case NTCOMPSUP:
			return (evalExpr(node->children[0], list) > evalExpr(node->children[1], list)) ? 1. : 0.;

		case NTPRINT:
			printf("%lf\n", evalExpr(node->children[0], list));
			return 0.;

		case NTFUNCTION:
			list_chain_function_append(list_function, node->children[0]->var, node->children[1]);
			return 0.;

		case NTVARFUNCT: {
			Node *funct_node = get_node_in_list_function(*list_function, node->var);
			if (funct_node != NULL) {
				return evalInst(funct_node, list, list_function);
			} else {
				printf("Unknown function '%s'...\n", node->var);
				exit(EXIT_FAILURE);
			}
		}

		default:
			printf("Error in evalInst ... Wrong node type: %s\n", node_to_string(node));
			exit(EXIT_FAILURE);
	};
}

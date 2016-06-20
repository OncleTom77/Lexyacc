#include "includes.h"

int printDepth 	= 0;
int funcDepth 	= 0;

t_list_chain **listVar = NULL;

double evalExpr(Node *node) {
	
	switch (node->type) {
		case NTEMPTY:
			return 0.;
		case NTNUM:
			return node->val;
		case NTVAR:
			return get_value_in_list(*listVar, node->var);
		case NTPLUS:
			return evalExpr(node->children[0]) + evalExpr(node->children[1]);
		case NTMIN:
			return evalExpr(node->children[0]) - evalExpr(node->children[1]);
		case NTMULT:
			return evalExpr(node->children[0]) * evalExpr(node->children[1]);
		case NTDIV:
			return evalExpr(node->children[0]) / evalExpr(node->children[1]);
		case NTPOW:
			return pow(evalExpr(node->children[0]), evalExpr(node->children[1]));
		default:
			printf("Error in evalExpr ... Wrong node type: %s\n", node_to_string(node));
			exit(EXIT_FAILURE);
	};
}

double evalInst(Node *node) {

	switch (node->type) {
		case NTEMPTY:
			return 0.;

		case NTINSTLIST:
			evalInst(node->children[0]);
			evalInst(node->children[1]);
			return 0.;

		case NTNUM:
		case NTVAR:
		case NTPLUS:
		case NTMIN:
		case NTMULT:
		case NTDIV:
		case NTPOW:
			return evalExpr(node);

		case NTEGAL: {
			double value = evalExpr(node->children[1]);
			list_chain_append(listVar, node->children[0]->var, value);
			return value;
		}

		case NTSI:
			// SI ... ALORS ... SINON
			if (node->children[1]->type == NTALORS) {
				if (evalInst(node->children[0]) != 0)
					evalInst(node->children[1]->children[0]);
				else
					evalInst(node->children[1]->children[1]);
			} else {
				// SI ... ALORS ...
				if (evalInst(node->children[0]) != 0)
					evalInst(node->children[1]);
			}
			return 0.;

		case NTTANTQUE:
			while (evalInst(node->children[0]) != 0)
				evalInst(node->children[1]);
			return 0.;

		case NTFOR:
			for(evalInst(node->children[0]->children[0]); evalInst(node->children[0]->children[1]) != 0; evalInst(node->children[1]->children[0]))
				evalInst(node->children[1]->children[1]);
			return 0.;

		case NTCOMPEGAL:
			return (evalExpr(node->children[0]) == evalExpr(node->children[1])) ? 1. : 0.;

		case NTCOMPDIFF:
			return (evalExpr(node->children[0]) != evalExpr(node->children[1])) ? 1. : 0.;

		case NTCOMPINF:
			return (evalExpr(node->children[0]) < evalExpr(node->children[1])) ? 1. : 0.;
		
		case NTCOMPSUP:
			return (evalExpr(node->children[0]) > evalExpr(node->children[1])) ? 1. : 0.;

		case NTPRINT:
			printf("%lf\n", evalExpr(node->children[0]));
			return 0.;

		default:
			printf("Error in evalInst ... Wrong node type: %s\n", node_to_string(node));
			exit(EXIT_FAILURE);
	};
}

double eval(Node *node, t_list_chain **list) {
	listVar = list;
	return evalInst(node);
}

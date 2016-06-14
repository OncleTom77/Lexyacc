#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <setjmp.h>
#include "minipseudtree.h"
#include "minipseudlist.h"

int printDepth = 0;
int funcDepth = 0;

t_list_chain** listVar = NULL;

double evalExpr(Node *node) {
	switch ( node->type ) {
		case NTEMPTY:
			return 0.0;
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
			printf("Error in evalExpr ... Wrong node type: %s\n", node2String(node));
			exit(1);
	};
}


double evalInst(Node* node) {
	double value;
	switch ( node->type ) {
		case NTEMPTY:
			return 0.0;
		case NTINSTLIST:
			evalInst(node->children[0]);
			evalInst(node->children[1]);
			return 0.0;
		case NTNUM:
		case NTVAR:
		case NTPLUS:
		case NTMIN:
		case NTMULT:
		case NTDIV:
		case NTPOW:
			value = evalExpr(node);
			//printf("%lf\n", value);
			return value;

		case NTEGAL:
			value = evalExpr(node->children[1]);
			list_chain_append(listVar, node->children[0]->var, value);
			//printf("%s = %lf\n", node->children[0]->var, value);
			return value;

		case NTCOMPEGAL:
			return;
		 
		default:
			printf("Error in evalInst ... Wrong node type: %s\n", node2String(node));
			exit (1);
	};
}

double eval(Node *node, t_list_chain** list) {
	listVar = list;
	return evalInst(node);
}
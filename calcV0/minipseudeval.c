#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <setjmp.h>
#include "minipseudtree.h"
#include "minipseudlist.h"

int printDepth = 0;
int funcDepth = 0;

t_list_chain* listVar = NULL;

double evalExpr(Node *node) {
	switch ( node->type ) {
		case NTEMPTY:
			return 0.0;
		case NTNUM:
			return node->val;
		case NTVAR:
			return get_value_in_list(listVar, node->var);
		 
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


void evalInst(Node* node) {
	double val;
	switch ( node->type ) {
		case NTEMPTY:
			return;
		case NTINSTLIST:
		case NTNUM:
		case NTVAR:
		case NTPLUS:
		case NTMIN:
		case NTMULT:
		case NTDIV:
		case NTPOW:
			printf("%f\n", evalExpr(node));
			return;

		case NTEGAL:
			printf("%s = %f\n", node->children[0]->var, node->children[1]->val);
			return;
		 
		default:
			printf("Error in evalInst ... Wrong node type: %s\n", node2String(node));
			exit (1);
	};
}

void eval(Node *node, t_list_chain* list) {
	listVar = list;
	evalInst(node);
}
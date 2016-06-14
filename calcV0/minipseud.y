%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <math.h>
	#include "minipseudtree.h"
	#include "minipseudeval.h"
	#include "minipseudlist.h"

	extern int  yyparse();
	extern FILE *yyin;

	t_list_chain* list = NULL;
%}

%union {
	struct Node *node;
}

%token   <node> VARIABLE
%token   <node> NUM
%token   <node> PLUS MIN MULT DIV POW EGAL
%token   OP_PAR CL_PAR COLON
%token   NEG
%token   EOL
%token 	 PRINT
%token	 SI ALORS SINON


%type   <node> Instlist
%type   <node> Inst
%type   <node> Expr


%left PLUS  MIN
%left MULT  DIV
%left NEG
%right  POW


%start Input
%%

Input:
	{/* Nothing ... */ }
	| Line Input { /* Nothing ... */ }
	;


Line:
	EOL {  }
	| Instlist EOL { exec($1);    }
	;

Instlist:
	Inst { $$=$1; }
	| Instlist Inst { $$=nodeChildren(createNode(NTINSTLIST), $1, $2); }
	;

Inst:
	VARIABLE EGAL Expr COLON { $$=nodeChildren($2, $1, $3); }
	| Expr COLON { $$=$1; }
	| PRINT OP_PAR Expr CL_PAR COLON { $$=$3; printf("%lf\n", eval($3, &list)); }
	| SI OP_PAR Expr CL_PAR ALORS Instlist { 
		if(eval($3) != 0) {
			$$=$5;
		}
	}
	| SI Expr ALORS Expr SINON Expr {
		if(eval($2) != 0) {
			$$=$4;
		} else {
			$$=$6;
		}
	}
	;

Expr:
	NUM						{ $$=$1; }
	| VARIABLE 				{ $$=$1; }
	| Expr PLUS Expr     	{ $$=nodeChildren($2, $1, $3); }
	| Expr MIN Expr      	{ $$=nodeChildren($2, $1, $3); }
	| Expr MULT Expr     	{ $$=nodeChildren($2, $1, $3); }
	| Expr DIV Expr      	{ $$=nodeChildren($2, $1, $3); }
	| MIN Expr %prec NEG 	{ Node* moinsUn = createNode(NTNUM); moinsUn->val = -1; $$=nodeChildren(createNode(NTMULT), moinsUn, $2); }
	| Expr POW Expr      	{ $$=nodeChildren($2, $1, $3); }
	| OP_PAR Expr CL_PAR 	{ $$=$2; }
	| Expr COMPEGAL	Expr	{ $$=nodeChildren($2, $1, $3); }
	| Expr COMPINF	Expr	{ $$=nodeChildren($2, $1, $3); }
	| Expr COMPSUP	Expr	{ $$=nodeChildren($2, $1, $3); }
	;
%%

int exec(Node *node) {
	printGraph(node);
	eval(node, &list);
}

int yyerror(char *s) {
	printf("%s\n", s);
}

int main(int arc, char **argv) {

	if ((arc == 3) && (strcmp(argv[1], "-f") == 0)) {
		FILE *fp=fopen(argv[2],"r");
		if(!fp) {
			printf("Impossible d'ouvrir le fichier à executer.\n");
			exit(0);
		}

		yyin=fp;
		yyparse();
		fclose(fp);
	}
	exit(0);
}

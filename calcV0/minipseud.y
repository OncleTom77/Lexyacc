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
%token	 <node> SI ALORS
%token	 <node> COMPEGAL COMPDIFF COMPINF COMPSUP
%token	 <node> TANTQUE
%token	 <node> FOR
%token 	 <node> PRINT
%token   OP_PAR CL_PAR COLON
%token	 SINON
%token	 FAIRE
%token   NEG
%token   EOL
%token	 FIN


%type   <node> Instlist Inst Expr


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
	| Instlist EOL { exec($1); }
	;

Instlist:
	Inst COLON { $$=$1; }
	| Instlist Inst COLON { $$=nodeChildren(createNode(NTINSTLIST), $1, $2); }
	;

Inst:
	VARIABLE EGAL Expr {
		$$ = nodeChildren($2, $1, $3);
	}
	| Expr {
		$$ = $1;
	}
	| PRINT OP_PAR Expr CL_PAR { 
		$$ = nodeChildren($1, $3, NULL);
		/*$$ = $3; printf("%lf\n", eval($3, &list));*/
	}
	| SI OP_PAR Expr CL_PAR ALORS Instlist FIN {
		$$ = nodeChildren($1, $3, $6);
	}
	| SI OP_PAR Expr CL_PAR ALORS Instlist SINON Instlist FIN {
		$$ = nodeChildren($1, $3, nodeChildren($5, $6, $8));
	}
	| TANTQUE OP_PAR Expr CL_PAR FAIRE Instlist FIN {
		$$ = nodeChildren($1, $3, $6);
	}
	| FOR OP_PAR Inst COLON Expr COLON Inst CL_PAR FAIRE Instlist FIN {
		$$ = nodeChildren($1, nodeChildren(createNode(NTFORTRAIT), $3, $5), nodeChildren(createNode(NTFORTRAIT), $7, $10));
	}
	;

Expr:
	NUM						{ $$ = $1; }
	| VARIABLE 				{ $$ = $1; }
	| Expr PLUS Expr     	{ $$ = nodeChildren($2, $1, $3); }
	| Expr MIN Expr      	{ $$ = nodeChildren($2, $1, $3); }
	| Expr MULT Expr     	{ $$ = nodeChildren($2, $1, $3); }
	| Expr DIV Expr      	{ $$ = nodeChildren($2, $1, $3); }
	| MIN Expr %prec NEG 	{ Node *moinsUn = createNode(NTNUM); moinsUn->val = -1; $$ = nodeChildren(createNode(NTMULT), moinsUn, $2); }
	| Expr POW Expr      	{ $$ = nodeChildren($2, $1, $3); }
	| OP_PAR Expr CL_PAR 	{ $$ = $2; }
	| Expr COMPEGAL	Expr	{ $$ = nodeChildren($2, $1, $3); }
	| Expr COMPDIFF	Expr	{ $$ = nodeChildren($2, $1, $3); }
	| Expr COMPINF Expr		{ $$ = nodeChildren($2, $1, $3); }
	| Expr COMPSUP Expr		{ $$ = nodeChildren($2, $1, $3); }
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
		FILE *fp = fopen(argv[2],"r");
		
		if (!fp) {
			printf("Impossible d'ouvrir le fichier à executer.\n");
			exit(0);
		}

		yyin = fp;
		yyparse();
		fclose(fp);
	}
	exit(0);
}

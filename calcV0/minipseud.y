%{
	#include "includes.h"

	extern int	yyparse();
	extern FILE *yyin;

	t_list_chain *list 						= NULL;
	t_list_chain_function *list_function 	= NULL;
%}

%union {
	struct Node *node;
}

%token	<node> VARIABLE
%token	<node> NUM
%token	<node> PLUS MIN MULT DIV POW EGAL
%token	<node> SI ALORS
%token	<node> COMPEGAL COMPDIFF COMPINF COMPSUP
%token	<node> TANTQUE
%token	<node> FOR
%token	<node> PRINT
%token	<node> FUNCTION
%token	OP_PAR CL_PAR COLON
%token	SINON
%token	FAIRE
%token	NEG
%token	EOL
%token	FIN

%type	<node> Instlist Inst Expr

%left	PLUS MIN
%left	MULT DIV
%left	NEG
%right	POW

%start Input

%%
	Input :
		{ /* Nothing ... */ }
		| Line Input { /* Nothing ... */ }
	;

	Line :
		EOL { }
		| Instlist EOL {
			exec($1);
		}
	;

	Instlist :
		Inst COLON {
			$$ = $1;
		}

		| Instlist Inst COLON {
			$$ = add_children_to_node(create_node(NTINSTLIST), $1, $2);
		}
	;

	Inst :
		VARIABLE EGAL Expr {
			$$ = add_children_to_node($2, $1, $3);
		}

		| Expr {
			$$ = $1;
		}

		| PRINT OP_PAR Expr CL_PAR { 
			$$ = add_children_to_node($1, $3, NULL);
		}

		| SI OP_PAR Expr CL_PAR ALORS Instlist FIN {
			$$ = add_children_to_node($1, $3, $6);
		}

		| SI OP_PAR Expr CL_PAR ALORS Instlist SINON Instlist FIN {
			$$ = add_children_to_node($1, $3, add_children_to_node($5, $6, $8));
		}

		| TANTQUE OP_PAR Expr CL_PAR FAIRE Instlist FIN {
			$$ = add_children_to_node($1, $3, $6);
		}

		| FOR OP_PAR Inst COLON Expr COLON Inst CL_PAR FAIRE Instlist FIN {
			$$ = add_children_to_node(
					$1,
					add_children_to_node(create_node(NTFORTRAIT), $3, $5),
					add_children_to_node(create_node(NTFORTRAIT), $7, $10)
				);
		}

		| FUNCTION VARIABLE OP_PAR CL_PAR Instlist FIN {
			$$ = add_children_to_node($1, $2, $5);
		}

		| VARIABLE OP_PAR CL_PAR {
			Node *node = create_node(NTVARFUNCT);
			node->var = strdup($1->var);
			$$ = node;
		}
	;

	Expr :
		NUM {
			$$ = $1;
		}

		| VARIABLE {
			$$ = $1;
		}

		| Expr PLUS Expr {
			$$ = add_children_to_node($2, $1, $3);
		}

		| Expr MIN Expr {
			$$ = add_children_to_node($2, $1, $3);
		}

		| Expr MULT Expr {
			$$ = add_children_to_node($2, $1, $3);
		}

		| Expr DIV Expr {
			$$ = add_children_to_node($2, $1, $3);
		}

		| MIN Expr %prec NEG {
			Node *moinsUn 	= create_node(NTNUM);
			moinsUn->val 	= -1;
			$$ = add_children_to_node(create_node(NTMULT), moinsUn, $2);
		}

		| Expr POW Expr {
			$$ = add_children_to_node($2, $1, $3);
		}

		| OP_PAR Expr CL_PAR {
			$$ = $2;
		}

		| Expr COMPEGAL	Expr {
			$$ = add_children_to_node($2, $1, $3);
		}

		| Expr COMPDIFF	Expr {
			$$ = add_children_to_node($2, $1, $3);
		}

		| Expr COMPINF Expr {
			$$ = add_children_to_node($2, $1, $3);
		}

		| Expr COMPSUP Expr {
			$$ = add_children_to_node($2, $1, $3);
		}
	;
%%

int exec(Node *node) {
	print_graph(node);
	evalInst(node, &list, &list_function);
}

int yyerror(char *s) {
	printf("%s\n", s);
}

int main(int argc, char **argv) {

	if ((argc == 3) && (strcmp(argv[1], "-f") == 0)) {
		FILE *fp = fopen(argv[2], "r");
		
		if (!fp) {
			printf("Impossible d'ouvrir le fichier à executer.\n");
			return EXIT_FAILURE;
		}

		yyin = fp;
		yyparse();
		fclose(fp);
	}

	return EXIT_SUCCESS;
}

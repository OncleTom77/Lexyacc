%option noyywrap

%{
	#include "includes.h"
%}

empty		[ \t]+

num			[0-9]
int			{num}+
exp			[eE][+-]?{int}

real		{int}("."{int})?{exp}?

variable	[a-zA-Z]+[a-zA-Z0-9]*

%%

{empty}  { /* Nothing */ }

{real} {
	yylval.node 		= create_node(NTNUM);
	yylval.node->val 	= atof(yytext);
	return NUM;
}

== {
	yylval.node = create_node(NTCOMPEGAL);
	return COMPEGAL;
}

!= {
	yylval.node = create_node(NTCOMPDIFF);
	return COMPDIFF;
}

"<" {
	yylval.node = create_node(NTCOMPINF);
	return COMPINF;
}

">" {
	yylval.node = create_node(NTCOMPSUP);
	return COMPSUP;
}

TANTQUE {
	yylval.node = create_node(NTTANTQUE);
	return TANTQUE;
}

FOR {
	yylval.node = create_node(NTFOR);
	return FOR;
}

FAIRE {
	return FAIRE;
}

FIN {
	return FIN;
}

SI {
	yylval.node = create_node(NTSI);
	return SI;
}

ALORS {
	yylval.node = create_node(NTALORS);
	return ALORS;
}

SINON {
	return SINON;
}

PRINT {
	yylval.node = create_node(NTPRINT);
	return PRINT;
}

FUNCTION {
	yylval.node = create_node(NTFUNCTION);
	return FUNCTION;
}

{variable} {
	yylval.node 		= create_node(NTVAR);
	yylval.node->var 	= strdup(yytext);
	return VARIABLE;
}


"(" {
	return OP_PAR;
}

")" {
	return CL_PAR;
}

"+" {
	yylval.node = create_node(NTPLUS);
	return PLUS;
}

"-" {
	yylval.node = create_node(NTMIN);
	return MIN;
}

"*" {
	yylval.node = create_node(NTMULT);
	return MULT;
}

"/" {
	yylval.node = create_node(NTDIV);
	return DIV;
}

"^" {
	yylval.node = create_node(NTPOW);
	return POW;
}

"=" {
	yylval.node = create_node(NTEGAL);
	return EGAL;
} 

";" {
	return COLON;
}

"\n" {
	return EOL;
}

%%

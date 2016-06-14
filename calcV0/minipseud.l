%option noyywrap
%{

#include "minipseud.h"
#include <stdlib.h>
#include "minipseudtree.h"

%}

empty 		[ \t]+

num 		[0-9]
int			{num}+
exp 		[eE][+-]?{int}

real    	{int}("."{int})?{exp}?

variable 	[a-zA-Z]+

%%

{empty}  { /* Nothing */ }

{real} {
    yylval.node = createNode(NTNUM);
    yylval.node->val = atof(yytext);
    return(NUM);
}

== {
	yylval.node = createNode(NTCOMPEGAL);
	return(COMPEGAL);
}

"<" {
	yylval.node = createNode(NTCOMPINF);
	return(COMPINF);
}

">" {
	yylval.node = createNode(NTCOMPSUP);
	return(COMPSUP);
}

SI {
	return(SI);
}

ALORS {
	return(ALORS);
}

SINON {
	return(SINON);
}

PRINT {
	return(PRINT);
}

{variable} {
	yylval.node = createNode(NTVAR);
	yylval.node->var = (char*) strdup(yytext);
	return(VARIABLE);
}


"("   	return(OP_PAR);
")"   	return(CL_PAR);

"+"   	{ yylval.node = createNode(NTPLUS); return(PLUS); }
"-"   	{ yylval.node = createNode(NTMIN); return(MIN); }
"*"   	{ yylval.node = createNode(NTMULT); return(MULT); }
"/"   	{ yylval.node = createNode(NTDIV); return(DIV); }
"^"   	{ yylval.node = createNode(NTPOW); return(POW); }

"="   	{ yylval.node = createNode(NTEGAL); return(EGAL); } 

";"   	{ return(COLON); }

"\n"  	{ return(EOL); }

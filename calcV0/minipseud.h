/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     VARIABLE = 258,
     NUM = 259,
     PLUS = 260,
     MIN = 261,
     MULT = 262,
     DIV = 263,
     POW = 264,
     EGAL = 265,
     SI = 266,
     ALORS = 267,
     COMPEGAL = 268,
     COMPDIFF = 269,
     COMPINF = 270,
     COMPSUP = 271,
     TANTQUE = 272,
     FOR = 273,
     PRINT = 274,
     FUNCTION = 275,
     OP_PAR = 276,
     CL_PAR = 277,
     COLON = 278,
     SINON = 279,
     FAIRE = 280,
     NEG = 281,
     EOL = 282,
     FIN = 283
   };
#endif
/* Tokens.  */
#define VARIABLE 258
#define NUM 259
#define PLUS 260
#define MIN 261
#define MULT 262
#define DIV 263
#define POW 264
#define EGAL 265
#define SI 266
#define ALORS 267
#define COMPEGAL 268
#define COMPDIFF 269
#define COMPINF 270
#define COMPSUP 271
#define TANTQUE 272
#define FOR 273
#define PRINT 274
#define FUNCTION 275
#define OP_PAR 276
#define CL_PAR 277
#define COLON 278
#define SINON 279
#define FAIRE 280
#define NEG 281
#define EOL 282
#define FIN 283




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 11 "minipseud.y"
{
	struct Node *node;
}
/* Line 1529 of yacc.c.  */
#line 109 "minipseud.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;


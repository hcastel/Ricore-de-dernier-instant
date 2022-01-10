/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_DECAF_TAB_H_INCLUDED
# define YY_YY_DECAF_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "decaf.y"

    #include "include/quad.h"   
    #include "include/write_code.h" 

#line 53 "decaf.tab.h"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    VIRG = 258,
    OP_PAR = 259,
    OP_CRO = 260,
    OP_BRA = 261,
    CL_BRA = 262,
    CL_CRO = 263,
    CL_PAR = 264,
    BEG = 265,
    SM = 266,
    TYPE_VOID = 267,
    U_MOINS = 268,
    IF = 269,
    ELSE = 270,
    FOR = 271,
    BREAK = 272,
    CONTINUE = 273,
    RETURN = 274,
    ID = 275,
    STRING_LIT = 276,
    HEX_LIT = 277,
    DEC_LIT = 278,
    CHAR_LIT = 279,
    WS = 280,
    BOOL_TRUE = 281,
    BOOL_FALSE = 282,
    OP_PLUS = 283,
    OP_SUB = 284,
    OP_MULT = 285,
    OP_DIV = 286,
    OP_RES = 287,
    OP_LESS = 288,
    OP_GREAT = 289,
    OP_LESS_EQ = 290,
    OP_GREAT_EQ = 291,
    OP_EQ = 292,
    OP_NOT_EQ = 293,
    OP_AND = 294,
    OP_OR = 295,
    OP_NOT = 296,
    AFF_EQ = 297,
    AFF_INC = 298,
    AFF_DEC = 299,
    TYPE_INT = 300,
    TYPE_BOOL = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 64 "decaf.y"

    char *str_val;
    long int int_val;

    // liste de types (typiquement utilisée pour les arguments de fonction)
    type_liste type_liste;
    // liste contenant l'état d'un bloc (break, return, etc...)
    control_liste control_liste;
    // expr (listes booléennes, entier, etc...)
    expr_val expr_val;

#line 123 "decaf.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void** tab_symbole, void* code_inter[], int* next_quad);

#endif /* !YY_YY_DECAF_TAB_H_INCLUDED  */

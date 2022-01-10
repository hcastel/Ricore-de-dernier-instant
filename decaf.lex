%{
#include "decaf.tab.h"
%}

%option nounput
%option noyywrap

alpha       [a-zA-Z_]
hex_digit   [0-9a-fA-F]
digit       [0-9]
char        ([\040-\176]{-}[\'\\\"])|"\\\""|"\\\\"|"\\\'"|"\\n"|"\\t"

%%

"//"[^\n]*      {}
"class"         { return BEG; }
"{"             { return OP_BRA; }
"}"             { return CL_BRA; }
"("             { return OP_PAR; }
")"             { return CL_PAR; }
"["             { return OP_CRO; }
"]"             { return CL_CRO; }
";"             { return SM; }
","             { return VIRG; }

"int"           { return TYPE_INT; }
"boolean"       { return TYPE_BOOL; }
"void"          { return TYPE_VOID; }
"if"            { return IF; }
"else"          { return ELSE; }
"for"           { return FOR; }
"break"         { return BREAK; }
"continue"      { return CONTINUE; }
"return"        { return RETURN; }
"WriteString"   { return WS; }

"<="            { return OP_LESS_EQ; }
">="            { return OP_GREAT_EQ; }
"=="            { return OP_EQ; }
"!="            { return OP_NOT_EQ; }
"<"             { return OP_LESS; }
">"             { return OP_GREAT; }

"&&"            { return OP_AND; }
"||"            { return OP_OR; }

"+"             { return OP_PLUS; }
"-"             { return OP_SUB; }
"*"             { return OP_MULT; }
"/"             { return OP_DIV; }
"%"             { return OP_RES; }
"!"             { return OP_NOT; }

"="             { return AFF_EQ; }
"+="            { return AFF_INC; }
"-="            { return AFF_DEC; }

"0x"{hex_digit}+            {   yylval.int_val=strtol(yytext, NULL, 16);
                                return HEX_LIT;
                            }
{digit}+                    {   yylval.int_val=atoll(yytext);
                                return DEC_LIT;
                            }
"true"                      {   return BOOL_TRUE; }
"false"                     {   return BOOL_FALSE; }
{alpha}({alpha}|{digit})*   {   yylval.str_val=strdup(yytext);
                                return ID;
                            }

\'{char}\'                  {   if(strcmp(yytext,"'\\n'")==0){
                                yylval.int_val = '\n';
                            }
                            else if(strcmp(yytext,"'\\\\'")==0){
                                yylval.int_val = 92;
                            }
                            else if(strcmp(yytext,"'\\\"'")==0){
                                yylval.int_val = 34;
                            }
                            else if(strcmp(yytext,"'\\t'")==0){
                                yylval.int_val = '\t';
                            }
                            else if(strcmp(yytext,"'\\\''")==0){
                                yylval.int_val = 39;
                            }
                            else {
                                yylval.int_val = yytext[1];
                            }
                                return CHAR_LIT;
                            }
\"{char}*\"                 {   yylval.str_val=strdup(yytext);
                                return STRING_LIT;
                            }

[[:space:]]                 {}
.                           {   fprintf(stderr,"caractere illegal (%d)\n",yytext[0]); }

%%
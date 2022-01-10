%{
#include "brouillon.tab.h"
%}
 //attention ordre, si = devant == alors == equivalent a = et = pour lex

%option nounput
%option noyywrap

alpha       [a-zA-Z_]
hex_digit   [0-9a-fA-F]
digit       [0-9]
char        [ -!#-&(-[]-~]
%%


"//"[^\n]*      {}
"class Program" { return BEG; }
"{"             { return OP_BRA; }            
"}"             { return CL_BRA; }
"("             { return OP_PAR; }
")"             { return CL_PAR; }
"["             { return OP_CRO; }
"]"             { return CL_CRO; }
";"             { return SM; }
","             { return VIRG; }



"WriteInt"      { return WI; }





"int"           { return TYPE_INT; }
"boolean"       { return TYPE_BOOL; }
"void"          { return TYPE_VOID; }
"if"            { return IF; }
"else"          { return ELSE; }
"for"           { return FOR; }
"break"         { return BREAK; }
"continue"      { return CONTINUE; }
"return"        { return RETURN; }

"<="            { return OP_LESS_EQ; }
">="            { return OP_GREA_EQ; } 

"<"             { return OP_LESS; }
">"             { return OP_GREA; }



"=="            { return OP_EQ; }
"!="            { return OP_NOT_EQ; }

"&&"            { return OP_AND; }
"||"            { return OP_OR; }

"="             { return AFF_EQ; }
"+="            { return AFF_INC; }
"-="            { return AFF_DEC; }

"+"             { return OP_PLUS; }
"-"             { return OP_SUB; }
"*"             { return OP_MULT; }
"/"             { return OP_DIV; }
"%"             { return OP_RES; }
"!"             { return OP_NOT; }

"0x"{hex_digit}({hex_digit})*           {   yylval.int_val=(int)strtol(yytext, NULL, 16);    
                                            return HEX_LIT; }
{digit}{digit}*                         {   yylval.int_val=atoi(yytext);  
                                            // printf("LEX: %i\n", yylval.int_val);    
                                            return DEC_LIT; }
"true"                                  { return BOOL_TRUE; }
"false"                                 { return BOOL_FALSE; }
{alpha}({alpha}|{digit})*               {   yylval.str_val=strdup(yytext);    
                                            return ID; }
\'({char}|"\t"|"\\"|"\n"|"\""|"\'")\'   {   yylval.char_val=yytext[1];         
                                            return CHAR_LIT; }
\"({char}|"\t"|"\\"|"\n"|"\""|"\'")*\"  {   yylval.str_val=strdup(yytext);    
                                            return STRING_LIT; }

[[:space:]]                             {}
.               { fprintf(stderr,"caractere illegal (%d)\n",yytext[0]); }

%%
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.h"
#include "indec.tab.h"

extern void yyerror(const char *);
extern int yylex();
%}

%option yylineno
%%

"("						{return P_L;}
")"						{return P_R;}
"{"						{return C_L;}
"}"						{return C_R;}
";"						{return DOT;}
","						{return COMMA;}
">"				        {return GT;}
"<"				        {return LT;}
">="			        {return GTE;}
"<="			        {return LTE;}
"="					    {return ASSIGN;}
"=="					{return EQ;}
"!="					{return NEQ;}
"+"					    {return ADD;}
"-"					    {return SUBTRACT;}
"*"				        {return MULTIPLY;}
"/"				        {return DIVIDE;}

int					    {return INT;}
string				    {return STRING;}

function			    {return FUNCTION;}
main					{return MAIN;}
print					{return PRINT;}

if					    {return IF;}
else					{return ELSE;}
while					{return WHILE;}

--.*$					{;}
[0-9]+					{yylval.integer = atoi(yytext); return INT;}
\"[^"]*\"				{yylval.string = strdup(yytext)+1; int z = 0; while(yylval.string[z] != '\0') z++; yylval.string[z-1] = '\0'; return STRING;}
[a-zA-Z_]+				{yylval.string = strdup(yytext); return IDENTIFIER;}

[[:space:]]+			{;}
.						{yyerror("lexer error: unexpected character");}
%%
int yywrap(void) { return 1; } 
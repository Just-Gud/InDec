%{
#include <stdio.h>
#include <vector>
#include <cstring>
#include "symbolTable.h"
#include "node.h"
#include "functions.h"
extern int yylex();
extern int yylineno;
void yyerror(const char *str)
{
	fprintf(stderr," Line: %d, error:  %s\n",yylineno-1, str);
}

NProgram * Node;

%}

%union
{
	int integer;
	char * string;

	NFunction * function;
	vector<NFunction *> * functionVector;

	NBlock * block;
	vector<NStatement *> * stmtVec;
	vector<NExpression *> * exprVec;
	NStatement * stmt;
	NDeclaration * decl;
	NAssignment * asg;
	NWhile * whileL;
	NIf * IfC;
	NFunctionCall * functionCall;
	NPrint * printSmth;
	NTerm * term;
	NExpression * expr;
	NBinaryExpression * bi;
	
}

%token DOT COMMA
%token P_L P_R C_L C_R

%token ASSIGN ADD SUBTRACT MULTIPLY DIVIDE
%token LT LTE GT GTE EQ NEQ
%token FUNCTION PRINT
%token IF ELSE
%token WHILE
%token MAIN

%token INT STRING
%token IDENTIFIER

%left ADD SUBTRACT
%left MULTIPLY DIVIDE
%left PERIOD


%type <function> mainFunction function
%type <functionVector> otherfunctions
%type <block> blockOfCode
%type <stmtVec> statementList

%type <stmt> statement
%type <decl> declaration
%type <asg> assignment
%type <whileL> whileL
%type <IfC> If
%type <functionCall> functionCall
%type <printSmth> printing

%type <term> term

%type <expr> expression
%type <bi> binaryExpression



%start program


%%
program
	:	mainFunction otherfunctions	{Node = new NProgram($1, *$2);}
	;

otherfunctions
	:					{$$ = new vector<NFunction *>();}
	|	function otherfunctions	{$<functionVector>2->push_back($1); $$ = $2;}
	;

mainFunction
	:	FUNCTION MAIN P_L P_R blockOfCode	{$$ = new NFunction((char *)"main", $5);}
	;

function
	:	FUNCTION IDENTIFIER P_L parameterList P_R blockOfCode		{$$ = new NFunction($<string>2, $6);}
	|	FUNCTION typeData IDENTIFIER P_L parameterList P_R blockOfCode	{$$ = new NFunction($<string>3, $7);}
	;

parameterList
	:	
	|	parameterList2
	;

parameterList2
	:	parameter
	|	parameter COMMA parameterList2
	;

parameter
	:	typeData IDENTIFIER
	;

typeData
	:	INT	{$<integer>$ = 0;}
	|	STRING		{$<integer>$ = 1;}
	;

blockOfCode
	:	C_L statementList C_R	{$$ = new NBlock(*$2);}
	;

statementList
	:					{$$ = new vector<NStatement *>();}
	|	statement statementList		{$<stmtVec>2->push_back($1); $$ = $2;}
	;

statement
	:	declaration	{$$ = new NStatement(0, $1);}
	|	assignment	{$$ = new NStatement(1, $1);}
	|	whileL		{$$ = new NStatement(2, $1);}
	|	If	{$$ = new NStatement(3, $1);}
	|	functionCall	{$$ = new NStatement(4, $1);}
	|	printing	{$$ = new NStatement(5, $1);}
	;

declaration
	:	typeData IDENTIFIER DOT	{$$ = new NDeclaration($<string>2, $<integer>1,0,0);}
	;
	
assignment
	:	IDENTIFIER ASSIGN expression DOT	{$$ = new NAssignment($<string>2, $3);}
	;

whileL
	:	WHILE P_L term P_R blockOfCode	{$$ = new NWhile($3, $5);}
	;

If
	:	IF P_L term P_R blockOfCode				{$$ = new NIf($3, $5, NULL); /* intended */}
	|	IF P_L term P_R blockOfCode ELSE blockOfCode	{$$ = new NIf($3, $5, $7);}
	;

term
	:	expression comparator expression	{$$ = new NTerm($<integer>2, $1, $3);}
	;

comparator
	:	LT	{$<integer>$ = 0;} /* less than */
	|	LTE	{$<integer>$ = 1;} /* Less than or equals */ 
	|	GT	{$<integer>$ = 2;} /* Greater than*/
	|	GTE	{$<integer>$ = 3;}
	|	EQ	{$<integer>$ = 4;}
	|	NEQ	{$<integer>$ = 5;}
	;

printing
	:	PRINT P_L expression P_R DOT		{$$ = new NPrint($3);}
	;

functionCall
	:	IDENTIFIER P_L P_R DOT			{$$ = new NFunctionCall($<string>1);}
	|	IDENTIFIER P_L funcParams P_R DOT	{$$ = new NFunctionCall($<string>1);}
	;

funcParams
	:	IDENTIFIER
	|	IDENTIFIER COMMA funcParams
	;

expression
	:	P_L expression P_R		{$$ = $2;}
	|	binaryExpression			{$$ = new NExpression(0, $1);}
	|	IDENTIFIER				{$$ = new NExpression(1, new NIdentifier($<string>1));	/*printf("%s ", $<string>1); */}
	|	INT					{$$ = new NExpression(2, new NInt($<integer>1));}
	|	STRING					{$$ = new NExpression(3, new NString($<string>1));}
	;

binaryExpression
	:	expression ADD expression		{$$ = new NBinaryExpression(0, $1, $3);}
	|	expression SUBTRACT expression		{$$ = new NBinaryExpression(1, $1, $3);}
	|	expression MULTIPLY expression		{$$ = new NBinaryExpression(2, $1, $3);}
	|	expression DIVIDE expression		{$$ = new NBinaryExpression(3, $1, $3);}
	|	expression PERIOD expression		{$$ = new NBinaryExpression(4, $1, $3); /* for text */ }
	;
%%


int main(void)
{
	yyparse();
	symbolTable = new SymbolTable();
	Program(Node);
}
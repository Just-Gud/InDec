#include <vector>

using namespace std;

class Node {
};


class NProgram;
class NFunction;

class NStatement;

class NIdentifier;
class NBlock;

class NComparator;
class NExpression;

class NProgram : public Node {
public:
	NFunction * main;
	vector<NFunction*> functions;

	NProgram(NFunction * m, vector<NFunction*> fnc){ main = m; functions = fnc; }
};

class NFunction : public Node {
public:
	char * identifier;
	NBlock * block;
	NFunction(char * id, NBlock * blck){ identifier = id; block = blck; }
};

class NStatement : public Node {
public:
	int type;
	Node * statement;
	NStatement(int temp, Node * st){ type = temp; statement = st; }
};

class NBlock : public Node {
public:
	vector<NStatement*> statements;
	NBlock(vector<NStatement*> stmts){ statements = stmts; }
};

class NDeclaration : public Node {
public:
	int type;
	int first;
	int second;
	char * identifier;
	NDeclaration(char * id, int temp, int fi, int sec){ identifier = id; type = temp; first=fi; second=sec;}
};

class NAssignment : public Node {
public:
	char * identifier;
	NExpression * expression;
	NAssignment(char * id, NExpression * express){ identifier = id; expression = express; }
};

class NString : public Node{
public:
	char * value;
	NString(char * v){ value = v; }
};


class NTerm : public Node {
public:
	NExpression * left;
	NExpression * right;
	int comparator;
	NTerm(int comp, NExpression * l, NExpression * r){ comparator = comp; left = l; right = r;}
};

class NIf : public Node {
public:
	NTerm * term;
	NBlock * blockTrue;
	NBlock * blockFalse;
	NIf(NTerm * t, NBlock * trueB, NBlock * falseB){ term = t; blockTrue = trueB; blockFalse = falseB; }
};

class NFunctionCall : public Node {
public:
	char * identifier;
	NFunctionCall(char * id){ identifier = id; }
};

class NWhile : public Node {
public:
	NTerm * term;
	NBlock * block;
	NWhile(NTerm * t, NBlock * blck){ term = t; block = blck; }
};

class NPrint : public Node {
public:
	//int type;
	NExpression * expression;
	NPrint(NExpression * expr){ expression = expr; }
};

class NExpression : public Node{
public:
	int type;
	Node * expression;
	NExpression(int temp, Node * expr){ type = temp, expression = expr;}
};


class NIdentifier : public Node{
public:
	char * title;
	NIdentifier(char * t){ title = t; }
};
class NInt : public Node{
public:
	int value;
	NInt(int v){ value = v; }
};

class NBinaryExpression : public Node{
public:
	int operation; 
	NExpression * left;
	NExpression * right;
	NBinaryExpression(int oper, NExpression * l, NExpression * r){ operation = oper; left = l; right = r;}
};

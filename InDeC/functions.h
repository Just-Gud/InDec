
void FFunction(NFunction *);
void Block(NBlock *);

void Statement(NStatement *);
void Declare(NDeclaration *);
void Assign(NAssignment *);
void While(NWhile *);
void If(NIf *);
void FFunctionCall(NFunctionCall *);
void Print(NPrint *);

bool Term(NTerm *);

ExpressionValue Expression(NExpression *);
ExpressionValue BinaryExpression(NBinaryExpression *);

SymbolTable * symbolTable;

void Program(NProgram * program)
{
	for (vector<NFunction *>::reverse_iterator iterator = program->functions.rbegin(); iterator != program->functions.rend(); ++iterator) {
		symbolTable->insert((**iterator).identifier, 367);
		symbolTable->modify((**iterator).identifier, *iterator);
	}
	FFunction(program->main);
}

void Statement(NStatement * statement)
{
	if (statement->type == 0){
		Declare((NDeclaration *) statement->statement);
	}
	if (statement->type == 1){
		Assign((NAssignment *) statement->statement);
	}
	if (statement->type == 2){
		While((NWhile *) statement->statement);
	}
	if (statement->type == 3){
		If((NIf *) statement->statement);
	}
	if (statement->type == 4){
		FFunctionCall((NFunctionCall *) statement->statement);
	}
	if (statement->type == 5){
		Print((NPrint *) statement->statement);
	}
}

void FFunction(NFunction * function)
{
	Block(function->block);
}

void Block(NBlock * block)
{
	for (vector<NStatement *>::reverse_iterator iterator = block->statements.rbegin(); iterator != block->statements.rend(); ++iterator) {
		Statement(*iterator);
	}
}

void Declare(NDeclaration * declaration)
{
	symbolTable->insert(declaration->identifier, declaration->type);
}
void Assign(NAssignment * assignment)
{
	ExpressionValue before = symbolTable->find(assignment->identifier);	
	ExpressionValue expr = Expression(assignment->expression);
	
	if (before.type != expr.type){
		printf("type mismatch\n");
		printf("\t[%s] is of type: [%d]; got type [%d]\n",assignment->identifier, before.type, expr.type);
	}

	void * place = expr.value;
	if(expr.type == 0){
		int number = *(int*)(expr.value);
		int * numplace = (int*) malloc(sizeof(int));
		*numplace = number;
		place = (void*) numplace;
	}
	symbolTable->modify(assignment->identifier, place);

}

void If(NIf * ifSt)
{
	bool temp = Term(ifSt->term);
	
	if (temp){
		Block(ifSt->blockTrue);
	}else{
		if (ifSt->blockFalse)
			Block(ifSt->blockFalse);
	}
}

void While(NWhile * whileL)
{
	while (true){
		bool cond = Term(whileL->term);
		if (!cond) break;
		Block(whileL->block);
	}
}

void Print(NPrint * printSmt)
{
	ExpressionValue toprint = Expression(printSmt->expression);
	//int type = printSmt->type;
	if(toprint.types == 2 ){
        printf("%d\n",toprint.val);
    }
    else if (toprint.type == 0){
        printf("%d\n", *(int*)toprint.value);
    }else if (toprint.type == 1){
        printf("%s\n", (char*)toprint.value);
    }else{
        printf("(printSmt) can't printSmt\n");
    }

}

ExpressionValue Expression(NExpression * expression)
{
	ExpressionValue result;
	if (expression->type == 0){
		result = BinaryExpression((NBinaryExpression *) expression->expression);
	}
	if (expression->type == 1){
		NIdentifier * ident = (NIdentifier *) expression->expression;
		
		result = symbolTable->find(ident->title);
	}
	if (expression->type == 2){ 
		NInt * num = (NInt *) expression->expression;
		result.type = 0;
		result.value = &(num->value);
	}
	if (expression->type == 3){
		NString * text = (NString *) expression->expression;

		result.type = 1;
		result.value = (text->value);
	}
	
	return result;
}
ExpressionValue BinaryExpression(NBinaryExpression * biex)
{
	ExpressionValue result;

	ExpressionValue left = Expression(biex->left);
	ExpressionValue right = Expression(biex->right);

	if (biex->operation >= 0 && biex->operation <= 3){ // types 0-3 - basic math operators
		if (left.type != 0){
			printf("(binaryexpression) left not number\n");
		}
		if (right.type != 0){
			printf("(binaryexpression) right not number\n");
		}

		int leftValue = *((int*)left.value);
		int rightValue = *((int*)right.value);
		int answer = 0;

		if (biex->operation == 0)
			answer = leftValue + rightValue;
		if (biex->operation == 1)
			answer = leftValue - rightValue;
		if (biex->operation == 2)
			answer = leftValue * rightValue;
		if (biex->operation == 3)
			answer = leftValue / rightValue;

		int * numplace = (int*) malloc(sizeof(int));
		*numplace = answer;

		result.type = 0;
		result.value = (void*)numplace;

	}else{
		if (left.type != 1){
			printf("(binaryexpression) left not text\n");
		}
		if (right.type != 1){
			printf("(binaryexpression) right not text\n");
		}
			
		char * leftValue = (char*)left.value;
		char * rightValue = (char*)right.value;

		int leftSize = 0;
		int rightSize = 0;
		while(leftValue[leftSize] != '\0') leftSize++;
		while(rightValue[rightSize] != '\0') rightSize++;

		char answer[leftSize+rightSize+1];
		for(int i = 0; i < leftSize; i++) answer[i] = leftValue[i];
		for(int i = 0; i < rightSize; i++) answer[leftSize+i] = rightValue[i];
		answer[leftSize+rightSize] = '\0';
		
		result.type = 1;
		result.value = answer;
	}

	return result;
}
void FFunctionCall(NFunctionCall * functionCall)
{
	ExpressionValue lookup = symbolTable->find(functionCall->identifier);
	if(lookup.type != 367){
		printf("(functionCall) [%s] is not a function\n", functionCall->identifier);
	}
	
	NFunction * function = (NFunction *) lookup.value;
	FFunction(function);
}

bool Term(NTerm * term)
{
	ExpressionValue left = Expression(term->left);
	ExpressionValue right = Expression(term->right);
	if (left.type != 0){
		printf("(term) left not number\n");
	}
	if (right.type != 0){
		printf("(term) right not number\n");
	}
	int leftValue = *(int*)left.value;
	int rightValue = *(int*)right.value;


	if (term->comparator == 0){
		if (leftValue < rightValue) return true; else return false;
	}
	if (term->comparator == 1){
		if (leftValue <= rightValue) return true; else return false;
	}
	if (term->comparator == 2){
		if (leftValue > rightValue) return true; else return false;
	}
	if (term->comparator == 3){
		if (leftValue >= rightValue) return true; else return false;
	}
	if (term->comparator == 4){
		if (leftValue == rightValue) return true; else return false;
	}
	if (term->comparator == 5){
		if (leftValue != rightValue) return true; else return false;
	}
	printf("(term) impossible term\n");
	return false;
}
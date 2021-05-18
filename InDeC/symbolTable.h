#include <string>
#include <cstdlib>

using namespace std; 
  
const int MAX = 100; 

struct ExpressionValue{
	int type;
	void * value;
	int first;
	int last;
	int val;
	int types;
};

class Nod { 
	string identifier;
	int type,first,last,val,types;
	void * value;
	Nod* next; 
  
public: 
	Nod() 
	{ 
		next = NULL; 
	} 

	Nod(string key, int type, void * value) 
	{ 
		this->identifier = key;
		this->type = type;
		this->value = value;
		this->first = 0;
		this->last = 0;
		this->val = 0;
		this->types = 0;
		next = NULL; 
	} 
	Nod(string key, int first,int second) 
	{ 
		this->first=first;
		this->last = second;
		this->identifier = key;
		this->type = 2;
		this->val = 0;

		next = NULL; 
	} 
	friend class SymbolTable; 
};

class SymbolTable {
	Nod * head[MAX];
  
public: 
	SymbolTable() 
	{ 
		for (int i = 0; i < MAX; i++) 
			head[i] = NULL; 
	} 
  
	int hashf(string id); 
	bool insert(char * id, int type); 
	bool insertstr(char * id, int type,ExpressionValue ran); 
	ExpressionValue find(char * id); 
	bool modify(char * id, void * val); 
};

bool SymbolTable::modify(char * id, void * v) 
{ 
	string str(id);
	int index = hashf(str); 
	Nod* start = head[index];
  
	if (start == NULL) 
		return false; 
  
	while (start != NULL) { 
		if (start->identifier == str) {
			start->value = v;
			return true; 
		} 
		start = start->next; 
	} 
  
	return false; 
}

ExpressionValue SymbolTable::find(char * id) 
{ 
	string str(id);
	int index = hashf(id); 
	Nod* start = head[index]; 

	ExpressionValue result;
	result.type = -1;
	result.value = NULL;
	result.first = -1;
	result.last = -1;
  
	if (start == NULL) 
		return result; 
  
	while (start != NULL) { 

		if (start->identifier == str) { 
			result.type = start->type;
			result.value = start->value;
			result.first = start->first;
			result.last = start->last;
			result.types = start->types;
			result.val = start->val;
			return result;
		} 
		start = start->next; 
	} 

	return result;
}

bool SymbolTable::insert(char * id, int Type) 
{ 
	string str(id);
	
	int index = hashf(str);
	void * val;

	if (Type == 0){
		int a = 0;
		val = (void*)&a;
	}else{
		char * a = (char *)"";
		val = (void*)&a;
	}
	Nod* p = new Nod(str, Type, val); 

	if (head[index] == NULL) { 
		head[index] = p; 

		return true; 
	} else {
		Nod* start = head[index]; 
		while (start->next != NULL) 
		start = start->next; 

		start->next = p; 

		return true; 
	} 

	return false; 
}

bool SymbolTable::insertstr(char * id, int Type, ExpressionValue ran) 
{ 
	string str(id);
	
	int index = hashf(str);

	Nod* p = new Nod(str,ran.first,ran.last); 

	if (head[index] == NULL) { 
		head[index] = p; 
		return true; 
	} else {
		Nod* start = head[index]; 
		while (start->next != NULL) 
		start = start->next; 

		start->next = p; 
		return true; 
	} 
	return false; 
}

int SymbolTable::hashf(string s)
{ 
	int asciiSum = 0;

	for (int i = 0; i < s.length(); i++) { 
		asciiSum = asciiSum + s[i];
	} 

	return (asciiSum % 100); 
}

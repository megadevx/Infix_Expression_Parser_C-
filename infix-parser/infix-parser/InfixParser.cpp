#include "InfixParser.h"


Infix_Parser::Infix_Parser()
{
}

Infix_Parser::Infix_Parser(string in)
{
	Infix_Parser::set_input_str(in);
}

void Infix_Parser::parse() 
{
	//Make sure that the expression isn't empty
	if (input_str.size() == 0) {
		cout << "Error reading the expression: expression is empty." << endl;
	}	

	//Check the first character. Print out error messages if error reading expression
	string first_char = string(1, input_str[0]);

	if (first_char == ")") {
		cout << "Expressions can't start with a closing parenthesis at char 0." << endl;
	}
	else if (unary->find(first_char) == -1) {
		cout << "Expressions can't start with a binary operator at char 0." << endl;
	}

	//Now read the rest of the expression
	
}

void Infix_Parser::set_input_str(string in)
{
	input_str = in;
}

string Infix_Parser::get_input_str()
{
	return string();
}

int Infix_Parser::evaluate()
{
	return 0;
}

int Infix_Parser::prec(string op)
{
	return 0;
}

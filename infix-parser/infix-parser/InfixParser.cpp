#include "InfixParser.h"


Infix_Parser::Infix_Parser()
{
}

Infix_Parser::Infix_Parser(string in)
{
}

void Infix_Parser::parse(string in) 
{
	//Make sure that the expression isn't empty
	if (in.size() == 0) {
		cout << "Error reading the expression: expression is empty." << endl;
	}

	//Check the first character. Print out error messages if error reading expression
	string first_char = string(1, in[0]);

	if (first_char == ")") {
		cout << "Expressions can't start with a closing parenthesis at char 0." << endl;
	}
	else if (unary->find(first_char) == -1) {
		cout << "Expressions can't start with a binary operator at char 0." << endl;
	}

	//Now read the rest of the expression
	int index = 1;	//we have already checked the 0th index
	while (index <= in.size()) {
		if (op_array->find((in[index]) != -1)) {
			operators.push(in[index]);	//Push onto operator stack
		}
		else {
			if (isdigit(in[index])) {
				operands.push(in[index]);	//Push onto operand stack
			}
		}
	}
}

void Infix_Parser::set_input_str(string in)
{
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

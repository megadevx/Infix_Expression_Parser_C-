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
	//Error Handling:
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
	istringstream expression(input_str);	//read the expression with istringstream
	char next_char;
	while (expression >> next_char) {	//while there are characters to read
		if (isdigit(next_char)) {
			expression.putback(next_char);		//if the next character is an integer,
			int value;							//put back, read as an integer (rather than a character)
			expression >> value;
			operands.push(value);				//push on the operands stack
		}
	}
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

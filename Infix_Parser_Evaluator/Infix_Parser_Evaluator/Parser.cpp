#include "Parser.h"

Parser::Parser() {
	//Default constructor
	exp = "";
}

Parser::Parser(string in) {
	//Non-default constructor
	exp = in;
}

string Parser::get_expression() {
	//Return the expression
	return exp;
}

void Parser::set_expression(string in) {
	//Set the expression to parse
	exp = in;
}

vector<Token> Parser::parse() {
	//Break the expression into a vector of tokens
	vector<Token> t_vector;

	//Read the expression as istringstream
	istringstream buffer(exp);
	int index = 0;
	char next_char;
	buffer >> next_char;
	
	Token t(next_char);

	//Error Handling
	if (next_char == ')') {
		cout << "Expression cannot begin with closing parenthesis @ char " << index << endl;
	}

	//Check for 2 character string operators
	switch (next_char) {
	case '+':{
		Token t(Parser::read_op(buffer, "+"));	//Unary ++
		}
	case '-': {
		Token t(Parser::read_op(buffer, "-"));	//Unary --
	}
	case '>': {
		Token t(Parser::read_op(buffer, ">"));	//Binary >=
	}
	case '<': {
		Token t(Parser::read_op(buffer, "<"));	//Binary <=
	}
	case '!': {
		Token t(Parser::read_op(buffer, "!"));	//Binary !=
	}
	case '=': {
		Token t(Parser::read_op(buffer, "="));	//Binary ==
	}
	case '&': {
		Token t(Parser::read_op(buffer, "&"));	//Binary &&
	}
	case '|': {
		Token t(Parser::read_op(buffer, "|"));	//Binary ||
	}
	}
	t_vector.push_back(t);
	return t_vector;
}

string Parser::read_op(istringstream &buf, string first) {
	string op = first;
	char next = ' ';
	buf >> next;
	switch (next) {
	case '+':
		op += '+';
		return op;
	case '-':
		op += '-';
		return op;
	case '=':
		op += '=';
		return op;
	case '&':
		op += '&';
		return op;
	case '|':
		op += '|';
		return op;
	}
	return op;
}
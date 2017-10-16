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
	char next_char = ' ';
	char prev = ' ';

	while (buffer >> next_char) {
		char next_next = buffer.peek();

		//Error handle
		if (t_vector.empty()) {
			Token t(next_char);
			if (next_char == ')') {
				cout << "Expression cannot begin with closing parenthesis @ char " << index << endl;
			}
			else if (t.is_binary()) {
				cout << "Expression cannot begin with binary operator @ char " << index << endl;
			}
		}

		//Check for spaces
		if (isspace(next_char)) {
			continue;
		}
		//Check for unary -
		else if (next_char == '-' && t_vector.empty()) {
			Token t('-', 'U');
			t_vector.push_back(t);
		}
		//Check for operands
		else if (isdigit(next_char)) {
			Token t(Parser::read_opd(buffer, next_char));
			t_vector.push_back(t);
		}
		//Check for 2 character string operators
		else if (next_char == '+' && next_next == '+') {
			Token t(Parser::read_opr(buffer, "+", index));	//Unary ++
			t_vector.push_back(t);
		}
		else if (next_char == '-' && next_next == '-') {
			Token t(Parser::read_opr(buffer, "-", index));	//Unary --
			t_vector.push_back(t);
		}
		else if (!isdigit(prev) && next_char == '-') {		//Unary -
			Token t('-', 'U');
			t_vector.push_back(t);
		}
		else if (next_char == '>') {
			Token t(Parser::read_opr(buffer, ">", index));	//Binary >=
			t_vector.push_back(t);
		}
		else if (next_char == '<') {
			Token t(Parser::read_opr(buffer, "<", index));	//Binary <=
			t_vector.push_back(t);
		}
		else if (next_char == '!') {
			Token t(Parser::read_opr(buffer, "!", index));	//Binary !=
			t_vector.push_back(t);
		}
		else if (next_char == '=' && next_next == '=') {
			Token t(Parser::read_opr(buffer, "=", index));	//Binary ==
			t_vector.push_back(t);
		}
		else if (next_char == '&' && next_char == '&') {
			Token t(Parser::read_opr(buffer, "&", index));	//Binary &&
			t_vector.push_back(t);
		}
		else if (next_char == '|' && next_char == '|') {
			Token t(Parser::read_opr(buffer, "|", index));	//Binary ||
			t_vector.push_back(t);
		}
		else {
			Token t(next_char);
			t_vector.push_back(t);
		}
		char prev = next_char;
		index++;
	}
	return t_vector;
}

string Parser::read_opr(istringstream &buf, string first, int index) {
	//Read multi-character operators
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
	buf.putback(next);
	return op;
}

int Parser::read_opd(istringstream &buf, char first) {
	//Read in multi-character operands
	int value;
	buf.putback(first);
	buf >> value;
	return value;
}
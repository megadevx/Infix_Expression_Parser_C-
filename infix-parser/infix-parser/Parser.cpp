#include "Parser.h"

Parser::Parser() {
	//Default constructor
	exp = "";
}

Parser::Parser(string in) {
	//Non-default constructor
	exp = in;
}

vector<Token> Parser::parse() {
	//Break the expression into a vector of tokens
}
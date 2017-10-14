#pragma once
#include <string>
#include <vector>
#include "Token.h"
using namespace std;

class Parser {
private:
	string exp;

public:
	//Default constructor
	Parser();

	//Non-default constructor
	Parser(string in);

	//Getters
	string get_expression();

	//Member Functions
	vector<Token> parse();
};
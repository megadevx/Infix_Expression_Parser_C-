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

	//Setters
	void set_expression(string in);

	//Member Functions
	string read_op(istringstream &buf, string first);
	vector<Token> parse();
};
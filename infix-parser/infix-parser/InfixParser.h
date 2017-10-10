#pragma once
#include <stack>
#include <string>
#include <iostream>
using std::stack;
using std::string;
using std::cout;
using std::cin;
using std::endl;

class Infix_Parser
{
public:
	//contructors: empty, string, copy constructor
	Infix_Parser();

	Infix_Parser(string in);

	//set input string
	void set_input_str(string in);

	//get input string
	string get_input_str();

	//read expression
	void parse(string in);

private:
	stack<char> operators;
	stack<int> operands;
	string input_str;
	string unary[4] = { "!", "++", "--", "-" };
	string op_array[20] = { "!", "++", "--", "-", "^", "*", "/", "%", "+", "-", ">", ">=", "<", "<=", "==", "!=", "&&", "||" };
};
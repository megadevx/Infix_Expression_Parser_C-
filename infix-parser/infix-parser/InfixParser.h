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
	void set_input_str(string in) {
		input_str = in;
	}

	//get input string
	string get_input_str();

<<<<<<< HEAD
	//get the 
	int evaluate();

	int prec(string op);


=======
	//read expression
	void parse(string in);
>>>>>>> d6030a0a82fa82c0be7c3a30a25d98ba41c8252e

private:
	stack<char> operators;
	stack<int> operands;
	string input_str;
	string unary[4] = { "!", "++", "--", "-" };
	string op_array[20] = { "!", "++", "--", "-", "^", "*", "/", "%", "+", "-", ">", ">=", "<", "<=", "==", "!=", "&&", "||" };
};
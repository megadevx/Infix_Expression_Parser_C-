#pragma once
#include <stack>
#include <string>
#include <iostream>
#include <vector>
using std::stack;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;

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

	//get the 
	int evaluate();

	int prec(string op);


	//read expression
	void parse();

private:
	stack<char> operators;
	stack<int> operands;
	string input_str;
	vector<string> unary = { "!", "++", "--", "-" };
	vector<string> op_array = { "!", "++", "--", "-", "^", "*", "/", "%", "+", "-", ">", ">=", "<", "<=", "==", "!=", "&&", "||" };
};
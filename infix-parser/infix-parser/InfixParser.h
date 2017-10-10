#pragma once
#include <stack>
#include <string>
using std::stack;
using std::string;

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


private:
	stack<char> operators;
	stack<int> operands;
	string input_str;
	
};
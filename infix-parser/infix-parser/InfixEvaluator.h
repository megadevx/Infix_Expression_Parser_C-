#pragma once
#include <vector>
#include "Token.h"
#include <stack>
#include <string>
using std::string;
using std::stack;
using std::vector;

class Infix_Evaluator {
public:
	//contructors
	Infix_Evaluator() { };
	Infix_Evaluator(vector<Token> input) { tokens = input; };
	//setter and getter for vector of tokens
	void set_tokens(vector<Token> new_tokens) { tokens = new_tokens; };
	vector<Token> get_tokens() { return tokens; };

	//gets the precidence of the operators
	int get_precidence(string op_to_check);
	//member function to evaluate the vector of tokens
	int evaluate();
	// do the different operations
	Token do_binary_math(Token lhs, Token opr, Token rhs);
	Token do_unary_math(Token opr, Token rhs);
private:
	vector<Token> tokens;
	stack<Token> operands;
	stack<Token> operators;
	bool pushed_number_last = false;
};


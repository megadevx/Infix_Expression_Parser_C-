#pragma once
#include <vector>
using std::vector;

template <class item_type>
class Infix_Evaluator {
public:
	//contructors
	Infix_Evaluator() { };
	Infix_Evaluator(vector<item_type> input) { tokens = input; };
	//setter and getter for vector of tokens
	void set_tokens(vector<item_type> new_tokens) { tokens = new_tokens; };
	vector<item_type> get_tokens() { return tokens; };

	//gets the precidence of the operators
	int get_precidence(item_type op_to_check);
	//member function to evaluate the vector of tokens
	int evaluate();
private:
	vector<item_type> tokens;
	stack<item_type> operands;
	stack<item_type> operators;
	bool pushed_number_last = false;
};


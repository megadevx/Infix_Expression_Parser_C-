#include "InfixEvaluator.h"
#include <iterator>
#include <vector>
using std::vector;
using std::iterator;

int Infix_Evaluator::get_precidence(string op_to_check)
{
	if (op_to_check == "!") {
		return 8;
	}
	else if(op_to_check == "++") {
		return 8;
	}
	else if (op_to_check == "--") {
		return 8;
	}
	else if (op_to_check == "-") {
		return  8;
	}
	else if (op_to_check == "^") {
		return 7;
	}
	else if (op_to_check == "*") {
		return 7;
	}
	else if (op_to_check == "/") {
		return 7;
	}
	else if (op_to_check == "%") {
		return 7;
	}
	else if (op_to_check == "+") {
		return 5;
	}
	else if (op_to_check == "-") {
		return 5;
	}
	else if (op_to_check == ">") {
		return 4;
	}
	else if (op_to_check == ">=") {
		return 4;
	}
	else if (op_to_check == "<") {
		return 4;
	}
	else if (op_to_check == "<=") {
		return 4;
	}
	else if (op_to_check == "==") {
		return 3;
	}
	else if (op_to_check == "!=") {
		return 3;
	}
	else if (op_to_check == "&&") {
		return 2;
	}
	else if (op_to_check == "||") {
		return 1;
	}
	else {
		return 0;
	}
}


int Infix_Evaluator::evaluate()
{
	// check for some beginning errors
	if (tokens[0].get_operator() == "") {
		if (tokens[0].get_operator() == ")")
			throw "Error";
		else if (tokens[0].get_type() == 'B')
			throw "Can't start with binary";
	}
	for (std::vector<Token>::iterator iter = tokens.begin(); iter != tokens.end(); iter++) {
		if (iter->get_operator() == "" && !pushed_number_last) {
			operands.push(*iter);
			pushed_number_last = true;
		}
		else if (iter->get_operator() == "" && pushed_number_last) {
			throw "Cannot have two operands in a row";
		}
		// if operator and number was pushed last and binary 
		else if (iter->get_operator() != "" && pushed_number_last && iter->get_type() == 'B') {
			//The check the precidence of current token compared to the top of the operators
			if (get_precidence(iter->get_operator()) > get_precidence(operators.top().get_operator())) {

			}
		}	
	}
	return 0;
}

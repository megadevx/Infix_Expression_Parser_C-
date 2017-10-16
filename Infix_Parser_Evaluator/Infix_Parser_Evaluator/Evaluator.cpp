#include "Evaluator.h"
#include <iterator>
#include <vector>
#include <cmath>
#include <algorithm>
using std::find;
using std::pow;
using std::vector;
using std::iterator;



int Evaluator::get_precedence(string op_to_check)
{
	if (op_to_check == "!") {
		return 8;
	}
	else if (op_to_check == "++") {
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


int Evaluator::evaluate()
{
	// check for some beginning errors
	if (tokens[0].get_operator() == ")") {
		throw "Can't start with a ) ";
	}
	else if (tokens[0].get_operator() != "" && tokens[0].get_type() == 'B') {
		throw "Can't start with binary";
	}
	for (std::vector<Token>::iterator iter = tokens.begin(); iter != tokens.end(); iter++) {
		
		std::vector<Token>::iterator next = iter;
		next++;
		if (iter->get_operator() == "/" && next->get_operator() == "" && next->get_operand() == 0) {
			throw "Division by zero error";
		}
		// if it is an operand then add the operand stack
		if (iter->get_operator() == "" && !pushed_number_last) {
			operands.push(*iter);
			pushed_number_last = true; \
				// check if unary operator was last then keep doing unary operation untill none left.
				while (!operators.empty()) {
					if (operators.empty() || operands.empty()) {
						throw "error operator and or operands stack is empty";
					}
					if (operators.top().get_type() == 'U') {
						Token opr, rhs;
						opr = operators.top();
						operators.pop();
						rhs = operands.top();
						operands.pop();
						operands.push(do_unary_math(opr, rhs));
					}
					else {
						break;
					}
				}
		}
		// cannot have two operands in a row
		else if (iter->get_operator() == "" && pushed_number_last) {
			throw "Cannot have two operands in a row";
		}

		else if (iter->get_operator() == "(") {
			if (pushed_number_last) {
				Token multi;
				multi.set_operator("*");
				operators.push(multi);
			}
			operators.push(*iter);
			pushed_number_last = false;	
		}
		else if (iter->get_operator() != "" && pushed_number_last && iter->get_type() == 'B') {

			//The check the precidence of current token compared to the top of the operators
			if (operators.empty()) {
				operators.push(*iter);
				pushed_number_last = false;
			}
			else if (get_precedence(iter->get_operator()) > get_precedence(operators.top().get_operator())) {
				operators.push(*iter);
				pushed_number_last = false;
			}
			else {
				// do binary math with the following because precidence of the top is greater
				if (operators.empty() || operands.empty()) {
					throw "error operator and or operand stack is empty";
				}
				Token lhs, rhs, opr;
				rhs = operands.top();
				operands.pop();
				lhs = operands.top();
				operands.pop();
				opr = operators.top();
				operators.pop();
				operands.push(do_binary_math(lhs, opr, rhs));
				operators.push(*iter);
				pushed_number_last = false;
			}
		}
		else if (iter->get_operator() != "" && !pushed_number_last && iter->get_type() == 'B') {
			throw "Cannot have two binary operators in a row.";
		}
		else if (iter->get_operator() != "" && iter->get_type() == 'U') {
			if (next != tokens.end()) {
				if (next->get_operator() != "" && next->get_type() == 'B') {
					throw "Cannot have a unary and then a binary operator.";
				}
				else if (next->get_operator() != "" && next->get_type() == 'U') {
					operators.push(*iter);
				}
				else if (next->get_operator() == "") {
					operators.push(*iter);
				}
				else {
					throw "Neither unary operator or number followed a unary operator";
				}
			}
		}
		else if (iter->get_operator() == ")") {
			while (!operators.empty()) {
				if (operators.empty()) {
					throw "error operator stack is empty and there is no (.";
				}
				if (operators.top().get_operator() != "(") {
					Token lhs, rhs, opr;
					rhs = operands.top();
					operands.pop();
					lhs = operands.top();
					operands.pop();
					opr = operators.top();
					operators.pop();
					operands.push(do_binary_math(lhs, opr, rhs));
				}
				else {
					break;
				}
			}
			operators.pop();
			pushed_number_last = true; // add a check to see if the parathesis match
		}
	}

		while (!operators.empty()) {
			Token lhs, rhs, opr;
			rhs = operands.top();
			operands.pop();
			lhs = operands.top();
			operands.pop();
			opr = operators.top();
			operators.pop();
			operands.push(do_binary_math(lhs, opr, rhs));
		}
		int result = operands.top().get_operand();
		operands.pop();
		if (!operands.empty()) {
			throw "The operand stack did not end up empty.";
		}
		return result;

}

Token Evaluator::do_binary_math(Token lhs, Token opr, Token rhs)
{
	Token result;
	if (opr.get_operator() == "^") {
		result.set_operand(pow(lhs.get_operand(), rhs.get_operand()));
	}
	else if (opr.get_operator() == "*") {
		result.set_operand(lhs.get_operand() * rhs.get_operand());
	}
	else if (opr.get_operator() == "/") {
		result.set_operand(lhs.get_operand() / rhs.get_operand());
	}
	else if (opr.get_operator() == "%") {
		result.set_operand(lhs.get_operand() % rhs.get_operand());
	}
	else if (opr.get_operator() == "+") {
		result.set_operand(lhs.get_operand() + rhs.get_operand());
	}
	else if (opr.get_operator() == "-") {
		result.set_operand(lhs.get_operand() - rhs.get_operand());
	}
	else if (opr.get_operator() == ">") {
		result.set_operand(lhs.get_operand() > rhs.get_operand());
	}
	else if (opr.get_operator() == ">=") {
		result.set_operand(lhs.get_operand() >= rhs.get_operand());
	}
	else if (opr.get_operator() == "<") {
		result.set_operand(lhs.get_operand() < rhs.get_operand());
	}
	else if (opr.get_operator() == "<=") {
		result.set_operand(lhs.get_operand() <= rhs.get_operand());
	}
	else if (opr.get_operator() == "==") {
		result.set_operand(lhs.get_operand() == rhs.get_operand());
	}
	else if (opr.get_operator() == "!=") {
		result.set_operand(lhs.get_operand() != rhs.get_operand());
	}
	else if (opr.get_operator() == "&&") {
		result.set_operand(lhs.get_operand() && rhs.get_operand());
	}
	else if (opr.get_operator() == "||") {
		result.set_operand(lhs.get_operand() || rhs.get_operand());
	}
	return result;
}

Token Evaluator::do_unary_math(Token opr, Token rhs)
{
	Token result;
	if (opr.get_operator() == "!") {
		result.set_operand(!rhs.get_operand());
	}
	else if (opr.get_operator() == "++") {
		result.set_operand(rhs.get_operand() + 1);
	}
	else if (opr.get_operator() == "--") {
		result.set_operand(rhs.get_operand() - 1);
	}
	else if (opr.get_operator() == "-") {
		result.set_operand(-rhs.get_operand());
	}
	return result;
}
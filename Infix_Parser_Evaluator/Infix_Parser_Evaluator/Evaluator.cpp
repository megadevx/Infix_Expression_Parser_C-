#include "Evaluator.h"
#include <iterator>
#include <vector>
#include <cmath>
#include <iostream>
using std::cout;
using std::pow;
using std::vector;
using std::iterator;



int Evaluator::get_precedence(string op_to_check)
{
	if (op_to_check == "^") {
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
	int index = 0;
	// check for some beginning errors
	if (tokens[0].get_operator() == ")") {
		cout << "Can't start with a ) @ char " << index << endl;
		exit(0);
	}
	else if (tokens[0].get_operator() != "" && tokens[0].get_type() == 'B') {
		cout << "Can't start with binary @ char " << index << endl;
		exit(0);
	}
	
	for (std::vector<Token>::iterator iter = tokens.begin(); iter != tokens.end(); iter++) {
		
		std::vector<Token>::iterator next = iter;
		next++;
		if (iter->get_operator() == "/" && next->get_operator() == "" && next->get_operand() == 0) {
			cout << "Division by zero error @ char " << index << endl;
			exit(0);
		}
		// if it is an operand then add the operand stack
		if (iter->get_operator() == "" && !pushed_number_last) {
			operands.push(*iter);
			pushed_number_last = true; \
				// check if unary operator was last then keep doing unary operation untill none left.
				while (!operators.empty()) {
					if (operators.empty() || operands.empty()) {
						cout << "Error operator and or operands stack is empty @ char" << index << endl;
						exit(0);
					}
					// check the stack for previous unary operators and do the unary math
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
			cout << "Cannot have two operands in a row @ char " << index << endl;
			exit(0);
		}
		else if (iter->get_operator() == "(") {
			// checks if the previous was a number if it was then add multiplication
			if (pushed_number_last) {
				Token multi;
				multi.set_operator("*");
				operators.push(multi);
			}
			operators.push(*iter);
			pushed_number_last = false;	
		}
		else if (iter->get_operator() != "" && pushed_number_last && iter->get_type() == 'B') {
			// do this if the operators stack is empty.
			if (operators.empty()) {
				operators.push(*iter);
				pushed_number_last = false;
			}
			//The check the precidence of current token compared to the top of the operators
			else if (get_precedence(iter->get_operator()) > get_precedence(operators.top().get_operator())) {
				operators.push(*iter);
				pushed_number_last = false;
			}
			else if (get_precedence(iter->get_operator()) <= get_precedence(operators.top().get_operator())) {
				// do binary math with the following because precidence of the top of operators is greater or equal than current
				//checks if the stacks are empty
				if (operators.empty() || operands.empty()) {
					cout << "error operator and or operand stack is empty @ char " << index << endl;
					exit(0);
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
			cout << "Cannot have two binary operators in a row @ char " << index << endl;
			exit(0);
		}
		// pushing the unary operators
		else if (iter->get_operator() != "" && iter->get_type() == 'U') {
			if (next != tokens.end()) {
				if (next->get_operator() != "" && next->get_type() == 'B') {
					cout << "Cannot have a unary and then a binary operator @ char "<< index << endl;
					exit(0);
				}
				else if (next->get_operator() != "" && next->get_type() == 'U') {
					operators.push(*iter);
				}
				else if (next->get_operator() == "") {
					operators.push(*iter);
				}
				else {
					cout << "Neither unary operator or number followed a unary operator @ char " << index << endl;
					exit(0);
				}
			}
		}
		// if it's the precidence then keep doing math until the closing parathesis is found.
		else if (iter->get_operator() == ")") {
			while (!operators.empty()) {
				if (operators.empty()) {
					cout << "Error operator stack is empty and there is no ( @ char " << index << endl;
					exit(0);
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
			pushed_number_last = true;

		}
		index += 1;
	}
	// do all the final math until only one value is left in the operands stack
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
			cout << "The operand stack did not end up empty @ char " << index << endl;
			exit(0);
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
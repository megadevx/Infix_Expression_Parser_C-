#include "Evaluator.h"
#include <iterator>
#include <vector>
using std::vector;
using std::iterator;

int Evaluator::get_precidence(string op_to_check)
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
	if (tokens[0].get_operator() == "") {
		if (tokens[0].get_operator() == ")")
			throw "Error";
		else if (tokens[0].get_type() == 'B')
			throw "Can't start with binary";
	}
	for (std::vector<Token>::iterator iter = tokens.begin(); iter != tokens.end(); iter++) {
		// if next is a ( and the current is a number add a multiplication
		std::vector<Token>::iterator next = ++iter;

		if (next->get_operator() == "(" && iter->get_operator() == "") {
			Token multi;
			multi.set_operator("*");
			operators.push(multi);
		}
		// if it is an operand then add the operand stack
		if (iter->get_operator() == "" && !pushed_number_last) {
			operands.push(*iter);
			pushed_number_last = true; \
				// check if unary operator was last then keep doing unary operation untill none left.
				while (operators.top().get_type() == 'U') {

					Token opr, rhs;
					opr = operators.top();
					operators.pop();
					rhs = operands.top();
					operands.pop();
					operands.push(do_unary_math(opr, rhs));
				}
			// if next is a ( and the current is a number add a multiplication
			if (next->get_operator() == "(") {
				Token multi;
				multi.set_operator("*");
				operators.push(multi);
			}
		}
		// cannot have two operands in a row
		else if (iter->get_operator() == "" && pushed_number_last) {
			throw "Cannot have two operands in a row";
		}
		// if operator and number was pushed last and binary 
		else if (iter->get_operator() == "(") {
			operators.push(*iter);
		}
		else if (iter->get_operator() != "" && pushed_number_last && iter->get_type() == 'B') {

			//The check the precidence of current token compared to the top of the operators
			if (get_precidence(iter->get_operator()) > get_precidence(operators.top().get_operator())) {
				operators.push(*iter);
				pushed_number_last = false;
			}
			else {
				// do binary math with the following because precidence of the top is greater
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
		else if (iter->get_operator() == ")") {
			while (operators.top().get_operator() != "(") {
				Token lhs, rhs, opr;
				rhs = operands.top();
				operands.pop();
				lhs = operands.top();
				operands.pop();
				opr = operators.top();
				operators.pop();
				operands.push(do_binary_math(lhs, opr, rhs));

			}
			operators.pop();
			pushed_number_last = true;

			if (next->get_operator() == "") {
				Token multi;
				multi.set_operator("*");
				operators.push(multi);
			}
		}
		else if (next == tokens.end()) {
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
	}
}

Token Evaluator::do_binary_math(Token lhs, Token opr, Token rhs)
{
	Token result;
	if (opr.get_operator() == "^") {
		result.set_operand(lhs.get_operand() ^ rhs.get_operand());
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
		result.set_operand(hs.get_operand() - rhs.get_operand());
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
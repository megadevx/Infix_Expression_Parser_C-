#include "Token.h"

Token::Token() {
	//Default constructor
	opr = "";
	opd = 0;
	type = 'N';
}

Token::Token(int op) {
	//Non-default constructor
	opd = op;
	opr = "";
	type = 'N';
}

Token::Token(char op) {
	//Non-default constructor
	opd = 0;
	opr = op;
	Token::set_type();
}

Token::Token(string opr) {
	//Non-default constructor
	Token::set_operator(opr);
	Token::set_type();
	
}

string Token::get_operator() {
	//Return the value of operator
	return opr;
}

int Token::get_operand() {
	//Return the value of operand
	return opd;
}

char Token::get_type() {
	//Get the type of the operator that was passed in
	return type;
}

void Token::set_operator(string op){
	//Set the operator to the passed in string
	opr = op;
}

void Token::set_operand(int op) {
	//Set the operand to the passed in string
	opd = op;
}

void Token::set_type() {
	//Set the type of the given operator
	//Check if in the vector of unary operators
	for (int i = 0; i < unary.size(); i++) {
		if (unary[i] == opr) {
			type = 'U';
		}
	}
	//Check if opr in vector of binary operators
	for (int i = 0; i < binary.size(); i++) {
		if (binary[i] == opr) {
			type = 'B';
		}
	}
}

bool Token::is_opr(string op) {
	//Check in unary vector
	for (int i = 0; i < unary.size(); i++) {
		if (unary[i] == op) {
			return true;
		}
	}

	//Check in binary vector
	for (int i = 0; i < binary.size(); i++) {
		if (binary[i] == op) {
			return true;
		}
	}
	return false;
}

bool Token::is_opd(string op) {
	int digit = 0;

	//Check if each char is a digit
	for (int i = 0; i < op.size(); i++){
		if (isdigit(i)) {
			digit++;
		}
	}
	
	if (digit == op.size()) {
		return true;
	}
	else {
		return false;
	}
}

bool Token::is_binary() {
	//Check if the string is in the binary vector
	for (int i = 0; i < binary.size(); i++) {
		if (binary[i] == opr) {
			return true;
		}
	}
	return false;
}

bool Token::is_unary(string in) {
	//Check if the string is in the unary vector
	for (int i = 0; i < unary.size(); i++) {
		if (unary[i] == in) {
			return true;
		}
	}
	return false;
}
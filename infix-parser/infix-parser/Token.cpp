#include "Token.h"

Token::Token() {
	//Default constructor
	opr = "";
	opd = 0;
	type = 'N';
}

Token::Token(int op) {
	//Non-default constructor
	Token::set_operand(op);
}

Token::Token(string opr) {
	//Non-default constructor
	if (Token::is_opd(opr)) {		//If it is an operand, set value as operand
		int value;
		istringstream buff(opr);
		buff >> value;
		Token::set_operand(value);
	}
	else if (Token::is_opr(opr)) {		//If it is an operator, set value as operator
		Token::set_operator(opr);
	}
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
	if (unary->find(opr) != -1) {	//Check if it is in array of unary operators
		return 'U';
	}
	else if (binary->find(opr) != -1) {		//Check if it is in array of binary operators
		return 'B';
	}
	else {
		throw "Invalid operator";		//Throw error if it is in neither array
		return 'N';
	}
}

void Token::set_operator(string op){
	//Set the operator to the passed in string
	opr = op;
}

void Token::set_operand(int op) {
	//Set the operand to the passed in string
	opd = op;
}

void Token::set_type(char type) {
	//Set the type of the given operator
	if (unary->find(opr) != -1) {		//if in the unary array, set type to U
		type = 'U';
	}
	else if(binary->find(opr) != -1){
		type = 'B';						//if in the binary array, set type to B
	}
	else {
		throw "Invalid operator";		//Throw error if not binary/unary
	}
}

bool Token::is_opr(string op) {
	//Check in unary/binary array
	if (unary->find(op) || binary->find(op)) {		
		return true;
	}
	else {
		return false;
	}
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

bool Token::is_binary(string in) {
	//Check if the string is in the binary array
	if (binary->find(in) != -1) {
		return true;
	}
	else {
		return false;
	}
}

bool Token::is_unary(string in) {
	//Check if the string is in the unary array
	if (unary->find(in) != -1) {
		return true;
	}
	else {
		return false;
	}
}

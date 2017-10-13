#include "Token.h"

Token::Token() {
	//Default constructor
}

Token::Token(string opr, char t) {
	//Non-default constructor
	Token::set_type(opr, t);
}

string Token::get_operator() {
	//Return the value of operator
	return opr;
}

int Token::get_operand() {
	//Return the value of operand
	return opd;
}

char Token::get_type(string in) {
	//Get the type of the operator that was passed in
	if (unary->find(in) != -1) {	//Check if it is in array of unary operators
		return 'U';
	}
	else if (binary->find(in) != -1) {		//Check if it is in array of binary operators
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

void Token::set_type(string op, char type) {
	//Set the type of the given operator
	if (unary->find(op) != -1) {		//if in the unary array, set type to U
		type = 'U';
	}
	else if(binary->find(op) != -1){
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

bool Token::is_opd(char op) {
	//Check if char is a digit
	if (isdigit(op)) {			
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
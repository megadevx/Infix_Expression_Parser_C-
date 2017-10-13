#pragma once
#include <iostream>
#include <string>
using namespace std;

class Token {
private:
	int opd;
	string opr;
	char type;
	string unary[4] = { "!", "-", "++", "--" };
	string binary[20] = { "^", "*", "/", "%", "+", "-", ">", ">=", "<", "<=", "==", "!+", "&&", "||" };

public:
	//Default constructor
	Token();

	//Non-default constructor
	Token(string opr, char type);

	//Getters
	string get_operator();
	int get_operand();
	char get_type(string opr);

	//Setters
	void set_operator(string op);
	void set_operand(int op);
	void set_type(string opr, char type);
	
	//Member Functions
	bool is_opd(char in);
	bool is_opr(string in);
	bool is_binary(string in);
	bool is_unary(string in);
};
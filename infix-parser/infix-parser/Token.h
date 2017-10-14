#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
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
	Token(int opd);
	Token(string opr);

	//Getters
	string get_operator();
	int get_operand();
	char get_type();

	//Setters
	void set_operator(string op);
	void set_operand(int op);
	void set_type(char type);
	
	//Member Functions
	bool is_opd(string in);
	bool is_opr(string in);
	bool is_binary(string in);
	bool is_unary(string in);
};
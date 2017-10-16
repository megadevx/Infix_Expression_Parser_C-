#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

class Token {
private:
	int opd;
	string opr;
	char type;
	vector<string> unary = { "!", "-", "++", "--" };
	vector<string> binary = { "^", "*", "/", "%", "+", "-", ">", ">=", "<", "<=", "==", "!=", "&&", "||" };

public:
	//Default constructor
	Token();

	//Non-default constructor
	Token(int opd);
	Token(char opr);
	Token(string opr);

	//Getters
	string get_operator();
	int get_operand();
	char get_type();

	//Setters
	void set_operator(string op);
	void set_operand(int op);
	void set_type();

	//Member Functions
	bool is_opd();
	bool is_opr();
	bool is_binary();
	bool is_unary();
};
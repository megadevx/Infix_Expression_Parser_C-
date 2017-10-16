#include <iostream>
#include "Token.h"
#include "Parser.h"
#include "Evaluator.h"
using namespace std;

void main()
{
	Parser parse("++++2-5(3^2)");
	vector<Token> v = parse.parse();
	Evaluator e(v);
	cout << e.evaluate() << endl;
	system("pause");
}
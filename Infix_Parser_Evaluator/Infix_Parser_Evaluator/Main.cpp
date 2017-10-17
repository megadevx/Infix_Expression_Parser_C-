#include <iostream>
#include "Token.h"
#include "Parser.h"
#include "Evaluator.h"
using namespace std;

int main()
{
	Parser parse("1/0");
	vector<Token> v = parse.parse();
	Evaluator e(v);
	cout << e.evaluate() << endl;
	system("pause");
	return 0;
}
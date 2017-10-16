#include <iostream>
#include "Token.h"
#include "Parser.h"
using namespace std;

void main()
{
	Parser parse("++++2-5(3^2)");
	vector<Token> v = parse.parse();
	system("pause");
}
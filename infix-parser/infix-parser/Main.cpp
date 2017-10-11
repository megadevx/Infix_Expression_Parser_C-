#include <iostream>
#include "InfixParser.h"
using namespace std;
int main()
{
	Infix_Parser ip("++++2-5(3^2)");
	ip.parse();
	system("pause");

	return 1;
}
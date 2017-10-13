#include "InfixEvaluator.h"
template<class item_type>
int Infix_Evaluator<item_type>::get_precidence(item_type op_to_check)
{
	stitch(op_to_check.get_operator())
	{
		case "!":
			return 8;
			break;
		case "++":
			return 8;
			break;
		case "--":
			return 8;
			break;
		case "-":
			return  8;
			break;
		case "^":
			return 7;
			break;
		case "*":
			return 7;
			break;
		case "/":
			return 7;
			break;
		case "%":
			return 7;
			break;
		case "+":
			return 5;
			break;
		case "-":
			return 5;
			break;
		case ">":
			return 4;
			break;
		case ">=":
			return 4;
			break;
		case "<":
			return 4;
			break;
		case "<=":
			return 4;
			break;
		case "==":
			return 3;
			break;
		case "!=":
			return 3;
			break;
		case "&&":
			return 2;
			break;
		case "||":
			return 1;
			break;
	}
}

template<class item_type>
int Infix_Evaluator<item_type>::evaluate()
{
	
	return 0;
}

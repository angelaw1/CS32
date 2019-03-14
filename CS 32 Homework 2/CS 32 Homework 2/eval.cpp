#include <string>
#include <stack>
#include <cctype>
#include <iostream>
using namespace std;


string removeSpaces(string s);

int evaluate(string infix, const bool values[], string& postfix, bool& result) {
	// Evaluates a boolean expression
	// Postcondition: If infix is a syntactically valid infix boolean
	//   expression, then postfix is set to the postfix form of that
	//   expression, result is set to the value of the expression (where
	//   in that expression, each digit k represents element k of the
	//   values array), and the function returns zero.  If infix is not a
	//   syntactically valid expression, the function returns 1.  (In that
	//   case, postfix may or may not be changed, but result must be
	//   unchanged.)

	string infixCopy = removeSpaces(infix);
	
	postfix = "";
	stack<char> charStack;
	if (infixCopy.size() == 0)
		return 1;
	for (int i = 0; i != infixCopy.size(); i++) {
		char ch = infixCopy[i];
		switch (ch) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				// can't have another digit or closing paren before digit
				if (i != 0 && isdigit(infixCopy[i - 1]) || i != 0 && infixCopy[i - 1] == ')')
					return 1;
				postfix += ch;
				break;
			case '(':
			case '!':
				// can't have digit or closing paren before (
				if (i != 0 && isdigit(infixCopy[i - 1]) || i != 0 && infixCopy[i - 1] == ')')
					return 1;
				if (i == infixCopy.size() - 1)
					return 1;
				charStack.push(ch);
				break;
			case ')':
				// can't have opening paren or ! before )
				if (i == 0)
					return 1;
				if (infixCopy[i - 1] == '(' || infixCopy[i - 1] == '!')
					return 1;
				if (charStack.empty())
					return 1;
				while (charStack.top() != '(') {
					// if there is no matching opening paren
					if (charStack.size() == 1)
						return 1;
					postfix += charStack.top();
					charStack.pop();
				}
				charStack.pop();
				break;
			case '&':
			case '|':
				// can't have operator at thestart or end of boolean expression
				if (i == 0 || i == infixCopy.size() - 1)
					return 1;
				//can't have two binary operators next to each other
				if (infixCopy[i + 1] == '&' || infixCopy[i + 1] == '|')
					return 1;
				// can't have opening paren or ! before binary operator
				if (infixCopy[i - 1] == '(' || infixCopy[i - 1] == '!')
					return 1;
				// can't have closing paren after operator
				if (infixCopy[i + 1] == ')')
					return 1;
				while (!charStack.empty()
					&& charStack.top() != '('
					&& ch >= charStack.top()) {
					postfix += charStack.top();
					charStack.pop();
				}
				charStack.push(ch);
				break;
			default:
				// if there is a character that is not a digit, paren, or operator
				return 1;
		}
	}
	while (!charStack.empty()) {
		postfix += charStack.top();
		charStack.pop();
	}
	// if there was no closing paren to match a opening paren
	for (int i = 0; i != postfix.size(); i++) {
		if (postfix[i] == '(')
			return 1;
	}

	stack<bool> operandStack;
	for (int i = 0; i != postfix.size(); i++) {
		char ch = postfix[i];
		if (isdigit(ch))
			operandStack.push(values[ch - '0']);
		else if (ch == '!') {
			bool temp = !operandStack.top();
			operandStack.pop();
			operandStack.push(temp);
		}
		else {
			bool operand2 = operandStack.top();
			operandStack.pop();
			bool operand1 = operandStack.top();
			operandStack.pop();
			if (ch == '&') {
				if (operand1 && operand2)
					operandStack.push(true);
				else {
					operandStack.push(false);
				}
			}
			else {
				if (operand1 || operand2)
					operandStack.push(true);
				else
					operandStack.push(false);
			}
		}
	}
	result = operandStack.top();
	return 0;
}

string removeSpaces(string s) {
	string noSpace = "";
	for (int i = 0; i != s.size(); i++) {
		if (s[i] != ' ') {
			noSpace += s[i];
		}
	}
	return noSpace;
}

/* #include <cassert>
int main()
{
	bool ba[10] = {
		//  0      1      2      3      4      5      6      7      8      9
		true,  true,  true,  false, false, false, true,  false, true,  false
	};
	string pf;
	bool answer;
	assert(evaluate("2| 3", ba, pf, answer) == 0 && pf == "23|" &&  answer);
	assert(evaluate("8|", ba, pf, answer) == 1);
	assert(evaluate("4 5", ba, pf, answer) == 1);
	assert(evaluate("01", ba, pf, answer) == 1);
	assert(evaluate("()", ba, pf, answer) == 1);
	assert(evaluate("2(9|8)", ba, pf, answer) == 1);
	assert(evaluate("2(&8)", ba, pf, answer) == 1);
	assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
	assert(evaluate("", ba, pf, answer) == 1);
	assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
		&& pf == "43!03&&|" && !answer); 
	assert(evaluate(" 9  ", ba, pf, answer) == 0 && pf == "9" && !answer);
	assert(evaluate("(1 & !(9 | 1 & 1 | 9) | !!!(9 & 1 & 9))", ba, pf, answer) == 0 && answer);
	assert(evaluate("2", ba, pf, answer) == 0 && answer);
	assert(evaluate("(3)", ba, pf, answer) == 0 && !answer);
	assert(evaluate("2&(3)", ba, pf, answer) == 0 && !answer);
	assert(evaluate("0 & !9", ba, pf, answer) == 0 && answer);
	assert(evaluate("!(7|8)", ba, pf, answer) == 0 && !answer);
	assert(evaluate("!7|8", ba, pf, answer) == 0 && answer);
	assert(evaluate("6|4&5", ba, pf, answer) == 0 && answer);
	ba[2] = false;
	ba[9] = true;
	assert(evaluate("((9))", ba, pf, answer) == 0 && pf == "9"  &&  answer);
	assert(evaluate("2| 3", ba, pf, answer) == 0 && pf == "23|" && !answer);
	assert(evaluate("((3!|6)", ba, pf, answer) == 1);
	assert(evaluate("&8|00", ba, pf, answer) == 1);
	assert(evaluate("|9", ba, pf, answer) == 1);
	assert(evaluate(")9(", ba, pf, answer) == 1);
	assert(evaluate("36", ba, pf, answer) == 1);
	assert(evaluate("5 (6 | 2)", ba, pf, answer) == 1);
	assert(evaluate("(6 & 2) 8", ba, pf, answer) == 1);
	assert(evaluate("6 && 8 *", ba, pf, answer) == 1);
	assert(evaluate("j", ba, pf, answer) == 1);
	assert(evaluate("9) | 8", ba, pf, answer) == 1);
	assert(evaluate("7 & (0", ba, pf, answer) == 1);
	assert(evaluate("((((()))))", ba, pf, answer) == 1);
	assert(evaluate("7 | (9 ! 7)", ba, pf, answer) == 1);
	assert(evaluate(") 9 | 8", ba, pf, answer) == 1);
	assert(evaluate("6 !& 8", ba, pf, answer) == 1);
	assert(evaluate("6 & !8", ba, pf, answer) == 0 && !answer);
	assert(evaluate("!4", ba, pf, answer) == 0 && answer);
	assert(evaluate("!(4 | 2 & 3) | (4 | 8 & 6)", ba, pf, answer) == 0 && answer);
	assert(evaluate("(4 | 5!)", ba, pf, answer) == 1);

	cout << "Passed all tests" << endl;
} */
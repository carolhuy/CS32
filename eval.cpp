#include<iostream>
#include<string>
#include<stack>
#include <cassert>

using namespace std; 

//Helper functions 

//establish precedence 
int preced(char character);

//determine if proper infix 
bool checkInfix(string infix);

//infix to postfix - return postfix string 
string infixToPostfix(string infix);

//evaluate postfix 
bool evalPostfix(string postfix);

// Evaluates a boolean expression
int evaluate(string infix, string& postfix, bool& result) {

// If infix is a syntactically valid infix boolean expression,
	if (checkInfix(infix) == true) {
		//   then set postfix to the postfix form of that expression, 
		postfix = infixToPostfix(infix);
		//set result to the value of the expression, and return zero.
		result = evalPostfix(postfix);
		return 0;
	} 

//If infix is not a syntactically valid expression, return 1; 
	else {
		//in that case, postfix may or may not be changed, but result must be unchanged.
		postfix = postfix;
		result = result;
		return 1;
	}
}

//Helper Function Implementations 

//precedence check 
int preced(char character) {
	if (character == '!') {
		return 3;
	}

	if (character == '&') {
		return 2;
	}

	if (character == '^') {
		return 1;
	}
	else {
		return 0;
	}
}

//check if the entered string is infix 
// almost all syntax errors can be detected by noting whether it is legal for the current nonblank character to 
//follow the nearest nonblank character before it;
// for example, & can follow T, but not (.
bool checkInfix(string infix) {
	char pos;
	char posRight;
	int parenOpenCount = 0; 
	int parenCloseCount = 0;

	//if string is empty 
	if (infix.length() == 0) {
		return false;
	}

	for (size_t i = 0; i < infix.length(); ++i) {
		pos = infix[i];
		posRight = infix[i + 1];
		char posLeft=' ';

		//if there is a left position
		if (i > 0) {
			posLeft = infix[i - 1];
		}
		
		//if there is a space after 
		if (posRight == ' ') {
			//evaluate the one next to it 
			posRight = infix[i + 2];
		}

		//if the last character is invalid 
		char last = infix[infix.length() - 1];
		if (last == '&' || last == '^' || last == '(' || last == '!') {
			return false;
		}

		//if have space
		if (pos == ' ') {
			continue;
		}

		//for the first character 
		if (i == 0) {
			if (pos == '&' || pos == '^' || pos == ')') {
				return false;
			}
		}

		//after the first character 
		//open paratheses case 
		switch (pos) {
		//if pos is open paren
		case '(':
			++parenOpenCount;
			//nested switch 
			switch (posRight) {
				//if to the right is & or ^ or ) 
			case '&':
				return false;
			case '^':
				return false;
			case ')':
				return false;
			case 'T':
				switch (posLeft) {
					//if to the left and right of ( is two operands, return false 
				case 'T':
					return false;
					break;
				case 'F':
					return false;
					break;
				default:
					break;
				}
				break;
			case 'F':
				switch (posLeft) {
					//if to the left of ( is two operands, return false 
				case 'T':
					return false;
					break;
				case 'F':
					return false;
					break;
				default:
					break;
				}
				break;
			default:
				continue;
			}
			break;

		//if pos is close paren
		case ')':
			++parenCloseCount;
			switch (posRight) {
			case '&':
				return false;
			case '^':
				return false;
			case '(':
				return false;
			default:
				continue;
			}
			break;

		//if pos is ^
		case '^':
			switch (posRight) {
			case '&':
				return false;
			case ')':
				return false;
			case '^':
				return false;
			default:
				continue;
			}
			break;
		//if pos is &
		case '&':
			switch (posRight) {
			case '^':
				return false;
			case '&':
				return false;
			case ')':
				return false;
			default:
				continue;
			}
			break;

		//if pos is ! 
		case '!':
			switch (posRight) {
			case '&':
				return false;
			case '^':
				return false;
			case ')':
				return false;
			case '(':
				return false;
			default:
				continue;
			}
			break;
		//if pos is T
		case 'T':
			switch (posRight) {
			case 'T':
				return false;
			case 'F':
				return false;
			case '!':
				return false;
			default:
				continue;
			}
			break;

			//if pos is F
		case 'F':
			switch (posRight) {
			case 'T':
				return false;
			case 'F':
				return false;
			case '!':
				return false;
			default:
				continue;
			}
			break;

		//not any of the seven characters 
		default:
			return false;
		}
	}
	
	//testing parentheses match 
	if (parenCloseCount != parenOpenCount) {
		return false;
	}
	//has passed all the tests 
	else {
		return true; 
	}
}

//changing infix to postfix notation 
// assumes that all operators are binary operators - need to do error checking 
//When converting infix to postfix, 
//a unary operator like ! behaves a lot more like an open parenthesis than like a binary operator.)
string infixToPostfix(string infix) {
	//Initialize postfix to empty
	string postfix;

	//Initialize the operator stack to empty
	stack<char> operators;

	//For each character ch in the infix string
	for (size_t i = 0; i < infix.length(); ++i) {
		char character = infix[i];

		//if operand is a blank 
		if (character == ' ') {
			continue;
		}
		else if (character == 'T' || character == 'F') {
			//append ch to end of postfix
			postfix += character;
		}

		//if case '('
		else if (character == '(' || character=='!') {
			//push ch onto the operator stack
			operators.push(character);
		}

		// if case ')'
		else if (character == ')') {
			// pop stack until matching '('
			while (operators.top() != '(') {
				postfix += operators.top();
				operators.pop();
			}
			//pop the '('
			operators.pop();
		}

		//if case operator 
		//if (character == '&' || character == '^')
		else {
			//stack is not empty, stack top is not '(' and precedence of ch <= precedence of stack top
			while (!operators.empty() && operators.top() != '(' && preced(character) <= preced(operators.top())) {
				//append the stack top to postfix
				postfix += operators.top();
				//pop stack 
				operators.pop();
			}
			//push ch onto the stack
			operators.push(character);
		}
	}
	//while stack not empty 
	while (!operators.empty()) {
		//append the stack top to postfix
		postfix += operators.top();
		//pop stack
		operators.pop();
	}

	return postfix;
}

//evaluating the postfix expression 
bool evalPostfix(string postfix) {
	//if postfix empty 
	if (postfix.empty()) {
		return false; 
	}
	//operand stack empty 
	stack<char> operands; 

	//For each character ch in the postfix string
	for (size_t i = 0; i < postfix.length(); ++i) {
		char ch = postfix[i];
		//if operand 
		if (ch == 'T' || ch == 'F') {
			operands.push(ch);
		}

		//unary operator - !
		else if (ch == '!') {
			char operandNot = operands.top();
			operands.pop();
			if (operandNot == 'T') {
				operands.push('F');
			}
			else {
				operands.push('T');
			}
		}


		//binary operator 
		else {
			char charOperandTwo = operands.top(); 
			operands.pop();
			char charOperandOne = operands.top();
			operands.pop();
			bool operandOne;
			bool operandTwo;

			//changing operand to bool 
			switch(charOperandOne){
			case 'T':
				operandOne = true;
				break;
			default: 
				operandOne = false;
			}

			switch (charOperandTwo) {
			case 'T':
				operandTwo = true;
				break;
			default:
				operandTwo = false;
			}

			//save result as bool 
			bool resultBool;

			switch (ch) {
			case '&':
				resultBool = operandOne & operandTwo;
				break;
			case '^':
				resultBool = operandOne ^ operandTwo;
				break;
			}

			//result must be the same as stack type (char) 
			//change bool to char 
			char result; 
			if (resultBool == true) {
				result = 'T';
			}
			//if (resultBool == false)
			else {
				result = 'F';
			}
			operands.push(result);
		}
	}
	//stack only contains the result 
	//stack.top and return different bool based on values 
	if (operands.top() == 'T') {
		return true; 
	}
	else {
		return false; 
	}
}

int main()
{
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);    	//took a while 
	assert(evaluate("T(F^T)", pf, answer) == 1); 	//failed before, check parentheses closely 
	
	assert(evaluate("T(&T)", pf, answer) == 1);

	assert(evaluate("(T&(F^F)", pf, answer) == 1);     //failed before 
	
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
	cout << "Passed all tests" << endl;
}
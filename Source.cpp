#include<iostream>
#include<string>
#include<stack>
#include<cmath>
using namespace std;



class InfixToPrefix
{
	string infix;
	string postfix;
	string prefix;
	stack<char> charStack;
	stack<int> intStack;
public:
	InfixToPrefix() :infix(""), postfix(""), prefix("") {}
	void setter();
	void getter();
	void convertToPostfix();
	int  precedence(char op);
	void  evaluation();
};
void InfixToPrefix::setter()
{
	cout << "\n Enter Infix Notation: ";
	getline(cin, infix);
}
void InfixToPrefix::getter()
{
	cout << " Prefix Notation: " << prefix << endl;
}

int InfixToPrefix::precedence(char op)
{
	switch (op)
	{
	case '^':
		return 3;
	case '/':
	case '*':
		return 2;
	case '+':
	case '-':
		return 1;
	default:
		return -1;
	}
}
string reverse(string str)
{
	int len = str.length();
	for (int i = 0; i < len / 2; i++)
	{
		swap(str[i], str[(len - 1) - i]);
	}
	return str;
}
void revrseParanthesis(string& str)
{
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		switch (str[i])
		{
		case '(':
			str[i] = ')';
			break;
		case ')':
			str[i] = '(';
			break;
		}
	}
}
void InfixToPrefix::convertToPostfix()
{
	int i = 0;
	char ch;

	infix = reverse(infix);
	revrseParanthesis(infix);

	while (infix[i] != NULL)
	{
		ch = infix[i];
		i++;
		if (isalpha(ch) || isdigit(ch))
			postfix.append(1, ch);
		else if (ch == '(')
			charStack.push(ch);
		else if (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^')
		{
			if (charStack.empty() || charStack.top() == '(')
				charStack.push(ch);
			else if (precedence(ch) > precedence(charStack.top()))
				charStack.push(ch);
			else
			{
				while (precedence(ch) <= precedence(charStack.top()))
				{

					postfix.append(1, charStack.top());
					charStack.pop();
					if (charStack.empty())
						break;
				}
				charStack.push(ch);

			}
		}
		else if (ch == ')')
		{
			while (charStack.top() != '(' && (!charStack.empty()))
			{
				postfix.append(1, charStack.top());
				charStack.pop();
			}
			charStack.pop();
		}

	}
	while (!charStack.empty())
	{
		postfix.append(1, charStack.top());
		charStack.pop();
	}

	prefix = reverse(postfix);
}
void InfixToPrefix::evaluation()
{
	int i = prefix.length() - 1;
	char ch;
	while (i >= 0)
	{
		ch = prefix[i];
		i--;
		if (isdigit(ch))
			intStack.push(ch - '0');
		else {
			int operand_1 = intStack.top();
			intStack.pop();
			int operand_2 = intStack.top();
			intStack.pop();

			switch (ch)
			{
			case '+':
				intStack.push(operand_1 + operand_2);
				break;
			case '-':
				intStack.push(operand_1 - operand_2);
				break;
			case '*':
				intStack.push(operand_1 * operand_2);
				break;
			case '/':
				intStack.push(operand_1 / operand_2);
				break;
			case '^':
				intStack.push(pow(operand_1, operand_2));
				break;
			}

		}

	}
	cout << " After Evaluation: " << intStack.top() << endl;
	intStack.pop();
}

int main()
{
	InfixToPrefix obj;
	obj.setter();
	obj.convertToPostfix();
	obj.getter();
	obj.evaluation();
}
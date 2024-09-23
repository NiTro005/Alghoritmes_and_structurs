// Copyright 2024 Kita Trofimov
#include "../lib_string/cstring.h"
#include "../lib_stack/stack.h"
#include "../lib_parser/parser.h"

bool IsCorrect(const CString& str) {
	TStack<char> stack(str.size());
	char s1 = ' ';
	for (size_t i = 0; i < str.size(); i++) {
		char s = str[i];
		if (s == '(' || s == '{' || s == '[' || (s == '|' && s1 != '|')) {
			stack.push(s);
			if (s == '|'){ s1 = s; }
		}
		else if (s == ')' || s == '}' || s == ']' || s == '|') {
			if (stack.IsEmpty()) {
				throw std::out_of_range("No bracket in stack");
			}
			char top = stack.top();
			if ((s == ')' && top == '(') ||
				(s == '}' && top == '{') ||
				(s == ']' && top == '[') ||
				(s == '|' && top == '|')) {
				stack.pop();
			} else {
				throw std::logic_error("wrong bracket");
			}

		}
		else if (!(('0' <= s && s <= '9') || ('A' <= s && s <= 'Z') || 
			('a' <= s && s <= 'z') || s == '*' || 
			s == '+' || s == '-' || s == '/')) {
			throw std::logic_error("Unexpscted symbol");
		}
	}
	if (!stack.IsEmpty()) {
		throw std::logic_error("Stack not empty");
	}
	return true;
}


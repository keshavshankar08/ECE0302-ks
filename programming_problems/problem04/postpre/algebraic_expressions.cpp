#include <string>
using std::string;
#include <iostream>
#include <stack>
#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch) {
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(string s, int last) {
  int first = 0;

  if ((first > last)) {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch)) {
    return last;
  } else {
    if (isoperator(ch)) {
      int lastEnd = endPost(s, last - 1);
      if (lastEnd > -1) {
        return endPost(s, lastEnd - 1);
      } else {
        return -1;
      }
    } else {
      return -1;
    }
  }
}

bool isPost(string s) {
  int firstChar = endPost(s, s.size() - 1);

  return (firstChar == 0);
}

void convert(string &postfix, string &prefix) {
  //if valid postfix expression
  if(isPost(postfix)){
    //get size of postfix string
    int size = postfix.size();

    //create stack
    std::stack<string> s;

    //scan postfix left to right
    for(int i = 0; i < size; i++){
      //if symbol is operator, pop 2 chars from top, push it to stack in reverse order
      if(isoperator(postfix[i])){
        string operator1 = s.top();
        s.pop();
        string operator2 = s.top();
        s.pop();
        string expression = postfix[i] + operator2 + operator1;
        s.push(expression);
      }
      //if symbol is operand, push it to stack
      else{
        string temp = string(1, postfix[i]);
        s.push(temp);
      }
    }

    //set prefix to new expression
    while(prefix.size() != size){
      prefix += s.top();
      s.pop();
    }

  }
}

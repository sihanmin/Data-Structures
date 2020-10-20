////
////  main.cpp
////  Hw2
////
////  Created by Mint MSH on 2/4/17.
////  Copyright © 2017 Mint MSH. All rights reserved.
////
//
//#include <iostream>
//#include <stdio.h>
//#include <string>
//#include <stack>
//#include <cassert>
//using namespace std;
//
////bool noGreaterThan(char ch, char curTop);
////char nextValid(string infix, int pos);
////string toPostfix(string infix);
////bool calculate(string postfix, const bool values[]);
////
////int evaluate(string infix, const bool values[], string& postfix, bool& result)
////// Evaluates a boolean expression
////// Postcondition: If infix is a syntactically valid infix boolean
//////   expression, then postfix is set to the postfix form of that
//////   expression, result is set to the value of the expression (where
//////   in that expression, each digit k represents element k of the
//////   values array), and the function returns zero.  If infix is not a
//////   syntactically valid expression, the function returns 1.  (In that
//////   case, postfix may or may not be changed, but result must be
//////   unchanged.)
////{
////    postfix = toPostfix(infix);
////    if (postfix == "")
////        return 1;
////    
////    result = calculate(postfix, values);
////    return 0;
////}
////
////bool noGreaterThan(char ch, char curTop)
////{
////    if (ch == curTop)
////        return true;
////    else if (ch == '|' && (curTop == '&' || curTop == '!'))
////        return true;
////    else if (ch == '&' && curTop == '!')
////        return true;
////    
////    return false;
////}
////
////bool nextValid(string infix, int pos, int Case)
////{
////    char next = ' ';
////    pos++;
////    while (pos != infix.size())
////    {
////        if (infix[pos] != ' ')
////        {
////            next = infix[pos];
////            break;
////        }
////        pos++;
////    }
////    if (pos == infix.size())
////        next = 'n';
////    
////    if (Case == 1)
////    {
////        if (next != '|' && next != '&' && next != ')' && next != 'n')
////            return false;
////    }
////    else if (Case == 2)
////    {
////        if (next != '(' && next != '!'&& (next < '0' || next > '9'))
////            return false;
////    }
////    return true;
////}
////
////string toPostfix(string infix)
////{
////    string postfix = "";
////    //int Operands = 0;
////    //int Operators = 0;
////    int brackets = 0;
////    stack<char> operatorStack;
////    for (int i = 0; i < infix.size(); i++)
////    {
////        switch (infix[i]) //0-9 //| & //! //() //n
////        {
////            case ('0'):
////            case ('1'):
////            case ('2'):
////            case ('3'):
////            case ('4'):
////            case ('5'):
////            case ('6'):
////            case ('7'):
////            case ('8'):
////            case ('9'): // case 1: only operators or end
////                if (!nextValid(infix, i, 1))
////                    return "";
////                postfix += infix[i];
////                break;
////            case ('('): // case 2: only operands or another () or not
////                if (!nextValid(infix, i, 2))
////                    return "";
////                brackets++;
////                operatorStack.push(infix[i]);
////                break;
////            case (')'): // case 1: only operators or end
////                if (!nextValid(infix, i, 1))
////                    return "";
////                brackets--;
////                while (operatorStack.top() != '(')
////                {
////                    postfix += operatorStack.top();
////                    operatorStack.pop();
////                }
////                operatorStack.pop();
////                break;
////            case ('!'): // case 2: only operands or another () or not
////                if (!nextValid(infix, i, 2))
////                    return "";
////                while (!operatorStack.empty() && operatorStack.top() != '('
////                       && noGreaterThan(infix[i],operatorStack.top()))
////                {
////                    postfix += operatorStack.top();
////                    operatorStack.pop();
////                }
////                operatorStack.push(infix[i]);
////                break;
////            case ('&'):
////            case ('|'): // case 2: only operands or another () or not
////                if (!nextValid(infix, i, 2))
////                    return "";
////                while (!operatorStack.empty() && operatorStack.top() != '('
////                       && noGreaterThan(infix[i],operatorStack.top()))
////                {
////                    postfix += operatorStack.top();
////                    operatorStack.pop();
////                }
////                operatorStack.push(infix[i]);
////                break;
////            case (' '):
////                break;
////            default:
////                return "";
////        }
////    }
////    if (brackets > 0)
////        return "";
////    while (!operatorStack.empty())
////    {
////        postfix += operatorStack.top();
////        operatorStack.pop();
////    }
////    
////    return postfix;
////}
////
////bool calculate(string postfix, const bool values[])
////{
////    bool operand1, operand2;
////    stack<bool> operandStack;
////    
////    for (int i = 0; i < postfix.size(); i++)
////    {
////        if (postfix[i] >= '0' && postfix[i] <= '9')
////            operandStack.push(values[postfix[i]-'0']);
////        else if (postfix[i] == '!')
////        {
////            operand2 = operandStack.top();
////            operandStack.pop();
////            operandStack.push(!operand2);
////        }
////        else
////        {
////            operand2 = operandStack.top();
////            operandStack.pop();
////            operand1 = operandStack.top();
////            operandStack.pop();
////            if (postfix[i] == '&' && operand2 == operand1)
////                operandStack.push(true);
////            else if (postfix[i] == '|')
////                operandStack.push(operand1);
////            else
////                operandStack.push(false);
////        }
////    }
////    return operandStack.top();
////}
//
//int main()
//{
//    bool ba[10] = {
//        //  0      1      2      3      4      5      6      7      8      9
//        true,  true,  true,  false, false, false, true,  false, true,  false
//    };
//    string pf;
//    bool answer;
//    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
//    assert(evaluate("8|", ba, pf, answer) == 1);
//    assert(evaluate("4 5", ba, pf, answer) == 1);
//    assert(evaluate("01", ba, pf, answer) == 1);
//    assert(evaluate("()", ba, pf, answer) == 1);
//    assert(evaluate("2(9|8)", ba, pf, answer) == 1);
//    assert(evaluate("2(&8)", ba, pf, answer) == 1);
//    assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
//    assert(evaluate("", ba, pf, answer) == 1);
//    assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
//           &&  pf == "43!03&&|"  &&  !answer);
//    assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
//    ba[2] = false;
//    ba[9] = true;
//    assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
//    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
//    cout << "Passed all tests" << endl;
//}

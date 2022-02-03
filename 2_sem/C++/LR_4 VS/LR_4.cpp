#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <map>
#include "stack.h"

typedef unsigned short us;
typedef unsigned int ui;

//#define start 48 //'0'
//#define end 57 //'9'
#define start 'a'
#define end 'z'
#define buffer temp[0]

std::map<char, int> operations
{
    {'(', 0}, {')', 0},
    {'+', 1}, {'-', 1},
    {'*', 2}, {'/', 2}
};

std::map<char, long double> operands
{
    {'a', 7.4}, {'b', 3.6},
    {'c', 2.8}, {'d', 9.5},
    {'e', 0.9}
};


std::string GetReversePolish (std::string);
long double CalculateReversePolish(std::string);

//(6+9-5)/(8+1*2)+7
//(6)(9)+(5)-(8)(1)(2)*+/(7)+
int main()
{
    std::string str = "(a+b)*(c-d)/e";

    str = GetReversePolish(str);

    std::cout << str << "\n";
    std::cout << "\nresult: " << CalculateReversePolish(str) << "\n";

    return 0;
}

std::string GetReversePolish(std::string equation)
{
    std::string str = "";
    Mstack<char> opers;

    char temp[2];
    temp[0] = equation[0]; //buffer == temp[0]
    temp[1] = '\0';

    for (us i = 0; buffer; i++, buffer = equation[i])
    {
        if (((buffer < start) || (buffer > end)) && (buffer == '+' || buffer == '-' || buffer == '*' || buffer == '/' || buffer == '(' || buffer == ')'))
        {   
            
            if (opers.Size() && buffer != '(')
            {
                while (opers.Size() && (operations.find(buffer)->second <= operations.find(opers.top())->second) && (opers.top() != '('))
                {
                    str.append(&opers.top());
                    opers.pop();
                }

                if (buffer == ')' && opers.top() == '(')
                {
                    opers.pop();
                }
            }
            if (buffer != ')')
            {
                opers.push(buffer);
            }
        }
        else
        {
            str.append(&buffer);
        }
    }

    while (opers.Size())
    {
        str.append(&opers.top());
        opers.pop();
    }

    return str;
}

long double CalculateReversePolish(std::string str)
{
    Mstack<long double> operandsForCalc;
    long double a = 0;
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (str[i] >= start && str[i] <= end)
        {
            operandsForCalc.push(operands.find(str[i])->second);
        }
        else
        {
            a = operandsForCalc.top();
            operandsForCalc.pop();

            switch (str[i])
            {
                case ('+'):
                {
                    operandsForCalc.top() += a;
                    break;
                }
                case ('-'):
                {
                    operandsForCalc.top() -= a;
                    break;
                }
                case ('*'):
                {
                    operandsForCalc.top() *= a;
                    break;
                }
                case ('/'):
                {
                    operandsForCalc.top() /= a;
                    break;
                }
            }
        }
    }

    return operandsForCalc.top();
}
#pragma once 

#include <iostream>
#include <sstream>
#include <stack>
#include <exception>
#include <climits>
#include "Colors.hpp"

class RPN
{
private:
    std::string _expression;
    std::string _token;
    std::stack<long int> _stack;
    long int _result;
    bool validToken();
    void pushNumber();
    bool performCalculation();

public:
    RPN();
    RPN(char **argv);
    ~RPN();
    void execute();
};
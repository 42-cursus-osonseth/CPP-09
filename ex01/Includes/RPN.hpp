#pragma once 

#include <iostream>
#include <sstream>
#include <stack>
#include <exception>
#include "Colors.hpp"

class RPN
{
private:
    std::string _expression;
    std::string _token;
    std::stack<long int> _stack;
    bool validToken();


public:
    RPN();
    RPN(char **argv);
    ~RPN();
    void execute();


    //--print a delete
    void printExpression();
    void printStack();
    
};


#include "RPN.hpp"

RPN::RPN() {}
RPN::~RPN() {}
RPN::RPN(char **argv) : _expression(argv[1]) {}

bool RPN::validToken()
{
    try
    {
        std::istringstream iss(_token);
        int n;
        iss >> n;
        if (_token.length() > 1 && n > 9)
            throw std::length_error("Error : number above 9 => ");
        if (_token.length() > 1)
            throw std::length_error("Error : invalid token => ");
        if ((_token[0] < '0' || _token[0] > '9') && _token[0] != '+' && _token[0] != '-' && _token[0] != '*' && _token[0] != '/')
            throw std::length_error("Error : invalid token => ");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << RED << _token << RESET << std::endl;
        return false;
    }
    return true;
}

void RPN::execute()
{
    try
    {
        std::istringstream iss(_expression);

        while (iss >> _token)
        {
            if (!validToken())
                break;
            if (_token[0] >= '0' && _token[0] <= '9')
            {
                std::istringstream iss_n(_token);
                long int n;
                iss_n >> n;
                _stack.push(n);
            }
            else
            {
                if (_stack.size() < 2)
                    throw std::logic_error("invalid format : less 2 operandes");

                long int b = _stack.top();
                _stack.pop();
                long int a = _stack.top();
                _stack.pop();
                if (_token[0] == '+')
                {
    
                    a += b;
                }
                if (_token[0] == '-')
                    a -= b;
                if (_token[0] == '*')
                    a *= b;
                if (_token[0] == '/')
                    a /= b;
                _stack.push(a);
            }
        }
        if (!_stack.empty())
        {
            long int result = _stack.top();
            std::cout << result << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

//----- print a delete
void RPN::printExpression()
{
    std::cout << _expression << std::endl;
}
void RPN::printStack()
{
    while (!_stack.empty())
    {
        std::cout << _stack.top() << std::endl;
        _stack.pop();
    }
}
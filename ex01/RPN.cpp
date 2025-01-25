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
void RPN::pushNumber()
{
    std::istringstream iss_n(_token);
    long int n;
    iss_n >> n;
    _stack.push(n);
}
bool RPN::performCalculation()
{
    try
    {
        long int b = _stack.top();
        _stack.pop();
        long int a = _stack.top();
        _stack.pop();
        switch (_token[0])
        {
        case '+':
            if (a > LONG_MAX - b)
                throw std::overflow_error("Arithmetic overflow occurred.");
            a += b;
            break;
        case '-':
            if (a < LONG_MIN + b)
                throw std::overflow_error("Arithmetic underflow occurred.");
            a -= b;
            break;
        case '*':
            if (a > LONG_MAX / b)
                throw std::overflow_error("Arithmetic overflow occurred.");
            a *= b;
            break;
        case '/':
            if (b == 0)
                throw std::invalid_argument("Division by zero is not allowed.");
            if (a == LONG_MIN && b == -1)
                throw std::overflow_error("Arithmetic overflow occurred during division.");
            a /= b;
            break;
        default:
            break;
        }
        _stack.push(a);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
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
                pushNumber();
            else
            {
                if (_stack.size() < 2)
                    throw std::logic_error("invalid format : less 2 operandes");
                if (!performCalculation())
                    break;
            }
        }
        if (!_stack.empty())
            throw std::logic_error("Error : too many operands");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

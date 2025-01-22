#include "BitcoinExchange.hpp"

const char *BitcoinExchange::OpenFileFailedException::what() const throw()
{
    return ("Open file failed ");
}

#include "BitcoinExchange.hpp"

const char *BitcoinExchange::OpenFileFailedException::what() const throw()
{
    return ("Open file failed ");
}
const char *BitcoinExchange::EmptyFileException::what() const throw()
{
    return ("The file is empty ");
}
#include "BitcoinExchange.hpp"

const char *BitcoinExchange::OpenFileFailedException::what() const throw()
{
    return ( RED "Error: could not open file" RESET);
}
const char *BitcoinExchange::BadInputException::what() const throw()
{
    return ( RED "Error: bad input (invalid date or format)     => " RESET);
}
const char *BitcoinExchange::NegativeValueException::what() const throw()
{
    return ( RED "Error: bad input (not a positive value)       => " RESET);
}
const char *BitcoinExchange::TooHighValue::what() const throw()
{
    return ( RED "Error: bad input (value above 1000)           => " RESET);
}
const char *BitcoinExchange::DatabaseLineInvalidException::what() const throw()
{
    return ( RED "Database line ignored (wrong format or invalid date/value) => " RESET);
}
const char *BitcoinExchange::NoPreviousDateException::what() const throw()
{
    return ( RED "Error : no earlier date found in the database => " RESET);
}

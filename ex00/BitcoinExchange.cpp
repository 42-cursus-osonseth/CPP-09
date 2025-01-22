#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}
BitcoinExchange::~BitcoinExchange()
{
}
BitcoinExchange::BitcoinExchange(char **argv) : _dataBase_Name("data.csv"), _inputFile_Name(argv[1]) {}
void BitcoinExchange::open_files()
{
    try
    {
        _input_File.open(_inputFile_Name.c_str(), std::ios::in);
        if (!_input_File.is_open())
            throw BitcoinExchange::OpenFileFailedException();
    }
    catch (const std::exception &e)
    {
        std::cerr << RED << e.what() << ":INPUT FILE" << RESET << std::endl;
        return;
    }

    try
    {
        _dataBase_File.open(_dataBase_Name.c_str(), std::ios::in);
        if (!_dataBase_File.is_open())
            throw BitcoinExchange::OpenFileFailedException();
    }
    catch (const std::exception &e)
    {
        std::cerr << RED << e.what() << ":DATA BASE FILE" << RESET << std::endl;
    }
}
void BitcoinExchange::close_files()
{
    if (_input_File.is_open())
        _input_File.close();
    if (_dataBase_File.is_open())
        _dataBase_File.close();
}
void BitcoinExchange::readAndStockDatabase()
{
    std::string line;
    std::getline(_dataBase_File, line);
    while (std::getline(_dataBase_File, line))
    {
        std::string key = line.substr(0, 10);
        std::istringstream iss(line.substr(11));
        float value;
        iss >> value;
        dataBase[key] = value;
    }
}
bool BitcoinExchange::isLeapYear(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        return true;
    return false;
}
int BitcoinExchange::isValidDay(std::string str)
{
    int day;
    std::istringstream iss(str);
    iss >> day;
    if (iss.fail() || !iss.eof() || day < 1 || day > 31)
        return -1;
    return day;
}
int BitcoinExchange::isValidMonth(std::string str)
{
    int month;
    std::istringstream iss(str);
    iss >> month;
    if (iss.fail() || !iss.eof() || month < 1 || month > 12)
        return -1;
    return month;
}
int BitcoinExchange::isValidYear(std::string str)
{
    int year;
    std::istringstream iss(str);
    iss >> year;
    if (iss.fail() || !iss.eof() || year < 2009 || year > 2025)
        return -1;
    return year;
}
bool BitcoinExchange::isValidDate(std::string str)
{
    int day, month, year;
    if (str[4] != '-' || str[7] != '-' || str.length() != 10)
        return false;
    day = isValidDay(str.substr(8));
    month = isValidMonth(str.substr(5, 2));
    year = isValidYear(str.substr(0, 4));
    if (day < 0 || month < 0 || year < 0)
        return false;
    if ((isLeapYear(year) && month == 2 && day > 29) || (!isLeapYear(year) && month == 2 && day > 28))
        return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;
    return true;
}
bool BitcoinExchange::isValidMiddle (std::string str)
{
    if (str[0] != ' ' || str[1] != '|' || str[2] != ' ')
        return false;
    return true;
}
bool BitcoinExchange::lineValidation(std::string str)
{
    if (!isValidDate(str.substr(0, 10)))
        return false;
    if (!isValidMiddle(str.substr(10, 3)))
        return false;
    // std::string value = str.substr(13);

    return true;
}
void BitcoinExchange::execute()
{
    open_files();
    readAndStockDatabase();
    std::string line;
    while (std::getline(_input_File, line))
    {
        if (!lineValidation(line))
            std::cout << "invalid line" << std::endl;
    }
    close_files();
}

//----------------------- print a delete------------------------------

void BitcoinExchange::print_map()
{
    for (std::map<std::string, float>::iterator it = dataBase.begin(); it != dataBase.end(); ++it)
    {
        std::cout << "Clé: " << it->first << " - Valeur: " << std::fixed << std::setprecision(2) << it->second << std::endl;
    }
}
//--------------------------------------------------------------------
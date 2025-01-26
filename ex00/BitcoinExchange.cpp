#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}
BitcoinExchange::~BitcoinExchange()
{
}
BitcoinExchange::BitcoinExchange(char **argv) : _dataBase_Name("data.csv"), _inputFile_Name(argv[1]), _value(0), _firstLine(true) {}

bool BitcoinExchange::open_files()
{
    try
    {
        _input_File.open(_inputFile_Name.c_str(), std::ios::in);
        if (!_input_File.is_open())
            throw BitcoinExchange::OpenFileFailedException();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << " => INPUT FILE" << std::endl;
        return false;
    }

    try
    {
        _dataBase_File.open(_dataBase_Name.c_str(), std::ios::in);
        if (!_dataBase_File.is_open())
            throw BitcoinExchange::OpenFileFailedException();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << " => DATA BASE FILE" << std::endl;
        return false;
    }
    return true;
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
    int i = 2;
    std::cout << YELLOW "-----------DATA BASE PROCESS -------------" << RESET << std::endl;
    while (std::getline(_dataBase_File, line))
    {
        try
        {
            if (line.empty())
                continue;
            if (!isValidDatabaseLine(line))
                throw BitcoinExchange::DatabaseLineInvalidException();
            std::string key = line.substr(0, 10);
            std::istringstream iss(line.substr(11));
            float value;
            iss >> value;
            dataBase[key] = value;
            i++;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::left << std::setw(15) << line << " / line -> " << i << std::endl;
            i++;
            continue;
        }
    }
    std::cout << YELLOW << std::string(42, '-') << RESET << std::endl;
}
bool BitcoinExchange::isValidDatabaseLine(std::string line)
{
    if (!isValidDate(line.substr(0, 10)))
        return false;
    if (line[10] != ',')
        return false;
    if (!isValidValue(line.substr(11)))
        return false;
    if (_value < 0)
        return false;
    return true;
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
bool BitcoinExchange::isValidMiddle(std::string str)
{
    if (str[0] != ' ' || str[1] != '|' || str[2] != ' ')
        return false;
    return true;
}
bool BitcoinExchange::isValidValue(std::string str)
{
    std::istringstream iss(str);
    iss >> _value;
    if (iss.fail() || !iss.eof())
        return false;
    return true;
}
bool BitcoinExchange::lineValidation(std::string str)
{
    try
    {   if (_firstLine && str == "date | value")
            return false;
        if (!isValidDate(str.substr(0, 10)))
            throw BitcoinExchange::BadInputException();
        if (!isValidMiddle(str.substr(10, 3)))
            throw BitcoinExchange::BadInputException();
        if (!isValidValue(str.substr(13)))
            throw BitcoinExchange::BadInputException();
        if (_value < 0)
            throw BitcoinExchange::NegativeValueException();
        if (_value > 1000)
            throw BitcoinExchange::TooHighValue();
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << std::left << std::setw(58) << e.what() << str << std::endl;
        return false;
    }
    return true;
}
void BitcoinExchange::execute()
{
    if (!open_files())
        return;
    readAndStockDatabase();
    std::string line;
    while (std::getline(_input_File, line))
    {
        if (line.empty() || !lineValidation(line))
            continue;
        if (_firstLine)
            _firstLine = false;
        if (dataBase.find(line.substr(0, 10)) != dataBase.end())
            printFinalValue(line);
        else
            printPreviousDateValue(line);
    }
    close_files();
}
void BitcoinExchange::printPreviousDateValue(std::string line)
{
    try
    {
        std::map<std::string, float>::iterator it = dataBase.lower_bound(line.substr(0, 10));
        if (it == dataBase.begin())
            throw BitcoinExchange::NoPreviousDateException();
        --it;
        std::istringstream iss(line.substr(13));
        float v;
        iss >> v;
        v *= it->second;
        std::cout << line.substr(0, 10) << " => " << std::right << std::setw(3) << line.substr(13) << " = " << v << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << std::left << std::setw(58) << e.what() << line << std::endl;
    }
}
void BitcoinExchange::printFinalValue(std::string line)
{
    std::istringstream iss(line.substr(13));
    float v;
    iss >> v;
    v *= dataBase[line.substr(0, 10)];
    std::cout << line.substr(0, 10) << " => " << std::right << std::setw(3) << line.substr(13) << " = " << v << std::endl;
}

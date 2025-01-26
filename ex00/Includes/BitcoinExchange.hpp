#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <exception>
#include <map>
#include "Colors.hpp"

class BitcoinExchange
{
private:
    std::string _dataBase_Name;
    std::string _inputFile_Name;
    std::fstream _input_File;
    std::fstream _dataBase_File;
    float _value;
    bool _firstLine;
    std::map<std::string, float> dataBase;
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator= (const BitcoinExchange &other);
    bool open_files();
    void close_files();
    void readAndStockDatabase();
    bool isValidDatabaseLine(std::string line);
    bool lineValidation(std::string str);
    bool isValidDate(std::string str);
    int isValidDay(std::string str);
    int isValidMonth(std::string str);
    int isValidYear(std::string str);
    bool isValidMiddle(std::string str);
    bool isValidValue(std::string str);
    bool isLeapYear(int year);
    void printFinalValue(std::string line);
    void printPreviousDateValue(std::string str);

public:
    BitcoinExchange();
    BitcoinExchange(char **argv);
    ~BitcoinExchange();
    void execute();
    class OpenFileFailedException : public std::exception
    {
        const char *what() const throw();
    };
    class BadInputException : public std::exception
    {
        const char *what() const throw();
    };
    class NegativeValueException : public std::exception
    {
        const char *what() const throw();
    };
    class TooHighValue : public std::exception
    {
        const char *what() const throw();
    };
    class DatabaseLineInvalidException : public std::exception
    {
        const char *what() const throw();
    };
    class NoPreviousDateException : public std::exception
    {
        const char *what() const throw();
    };
    
};

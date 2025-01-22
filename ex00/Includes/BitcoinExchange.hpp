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
    std::map<std::string, float> dataBase;
    void open_files();
    void close_files();
    void readAndStockDatabase();
    bool lineValidation(std::string str);
    bool isValidDate(std::string str);
    int isValidDay(std::string str);
    int isValidMonth(std::string str);
    int isValidYear(std::string str);
    bool isValidMiddle(std::string str);
    bool isLeapYear(int year);

public:
    BitcoinExchange();
    BitcoinExchange(char **argv);
    ~BitcoinExchange();
    void execute();
    class OpenFileFailedException : public std::exception
    {
        const char *what() const throw();
    };

    //------ print a delete ---------
    void print_map();
    //-------------------------------
};

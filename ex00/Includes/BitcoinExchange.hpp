#pragma once

#include <iostream>
#include <fstream>
#include <exception>
#include "Colors.hpp"

class BitcoinExchange
{
private:
    std::string _dataBase_Name;
    std::string _inputFile_Name;
    std::fstream _input_File;
    std::fstream _dataBase_File;
    void open_files();
    void close_files();
    

public:
    BitcoinExchange();
    BitcoinExchange(char **argv);
    ~BitcoinExchange();
    void execute();
    class OpenFileFailedException : public std::exception{
        const char *what() const throw();
    };
    class EmptyFileException : public std::exception{
        const char *what() const throw();
    };
};

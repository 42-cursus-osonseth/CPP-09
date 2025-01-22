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
        _input_File.seekg(0, std::ios::end);
        if (_input_File.tellg() == 0)
            throw BitcoinExchange::EmptyFileException();
        _input_File.seekg(0, std::ios::beg);
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
void BitcoinExchange::execute()
{
    open_files();
    close_files();
}
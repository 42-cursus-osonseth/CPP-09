#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    try
    {
        if (argc != 2)
            throw BitcoinExchange::OpenFileFailedException();
        BitcoinExchange btc(argv);
        btc.execute();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << YELLOW << " => INPUT FILE" << RESET << std::endl;
    }

    return 0;
}
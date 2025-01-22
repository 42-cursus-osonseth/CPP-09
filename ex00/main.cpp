#include "BitcoinExchange.hpp"

int main (int argc, char **argv)
{
    if ( argc != 2)
        return std::cout << RED << " Please, enter the name of input file as argument" << RESET << std::endl, 0;

    BitcoinExchange btc(argv);
    btc.execute();
    return 0;
}
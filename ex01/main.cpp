#include "RPN.hpp"

int main (int argc, char **argv)
{
    try
    {
        if (argc != 2)
            throw std::invalid_argument("Error : expected 1 argument");
        RPN a(argv);
        a.execute();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
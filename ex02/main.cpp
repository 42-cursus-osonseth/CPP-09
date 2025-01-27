#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    try
    {
        if (argc < 2)
            throw std::invalid_argument("Error: Invalid number of arguments");
        PmergeMe s(argv);
        // s.print_vec();
        s.execute();
        s.print_vec();
        std::cout << "comparison number : " << s.getCompNbr() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

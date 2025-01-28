#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    try
    {
        if (argc < 2)
            throw std::invalid_argument("Error: Invalid number of arguments");
        clock_t start = clock();
        PmergeMe s(argv);
        s.print_vec();
        s.execute();
        clock_t end = clock();
        double time_taken = double(end - start) / CLOCKS_PER_SEC;
        s.print_vec();
        std::cout << "comparison number : " << s.getCompNbr() << std::endl;
        std::cout << "Time to process: " << time_taken << " seconds" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

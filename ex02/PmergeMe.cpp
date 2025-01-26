#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(char **argv)
{
    for (int i = 1; argv[i]; i++)
    {
        std::istringstream iss(argv[i]);
        long int n;
        while (iss >> n)
            vec.push_back(n);
        if ((iss.fail() && !iss.eof()) || n < 0 || n > INT_MAX || !argv[i][0])
            throw std::invalid_argument("Error: Invalid arguments : " + std::string(argv[i]));
        
    }
}
void PmergeMe::execute()
{
}
//---- print a delete -------

void PmergeMe::print_arg()
{
    std::cout << arg << std::endl;
}
void PmergeMe::print_vec()
{
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
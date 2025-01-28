#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(char **argv) : size(0), comp_nbr(0)
{
    for (int i = 1; argv[i]; i++)
    {
        std::istringstream iss(argv[i]);
        long int n;
        while (iss >> n)
            vec.push_back(n);
        if ((iss.fail() && !iss.eof()) || n < 0 || n > INT_MAX || !argv[i][0])
            throw std::invalid_argument("Error: invalid arguments : " + std::string(argv[i]));
        if (set.find(n) != set.end())
            throw std::invalid_argument("Error: duplicate numbers : " + std::string(argv[i]));
        set.insert(n);
    }
    set.clear();
}
int PmergeMe::getCompNbr() { return comp_nbr; }
void PmergeMe::swap(std::vector<int>::iterator a, std::vector<int>::iterator b)
{
    if (*b > *a)
        return;
    int tmp = *b;
    *b = *a;
    *a = tmp;
}
void PmergeMe::recursive(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    int size = std::distance(begin, end);
    if (size <= 1)
        return;
    for (std::vector<int>::iterator it = begin; it != end - 1 && it != end; it += 2)
        swap(it, it + 1);

    std::vector<int> largeNbr;
    std::vector<int> smallNbr;
    if (size % 2 == 0)
    {

        for (std::vector<int>::iterator it = begin; it != end; it += 2)
            smallNbr.push_back(*it);

        for (std::vector<int>::iterator it = begin + 1; it != end; it += 2)
        {
            if (it == end - 1)
            {
                largeNbr.push_back(*it);
                break;
            }
            largeNbr.push_back(*it);
        }
        recursive(largeNbr.begin(), largeNbr.end());
    }
    else
    {
        for (std::vector<int>::iterator it = begin; it != end - 1; it += 2)
            smallNbr.push_back(*it);
        for (std::vector<int>::iterator it = begin + 1; it != end; it += 2)
            largeNbr.push_back(*it);
        smallNbr.push_back(*(end - 1));
        recursive(largeNbr.begin(), largeNbr.end());
    }
    for (std::vector<int>::iterator it = smallNbr.begin(); it != smallNbr.end(); it++)
    {
        int pos = dichotomousSearch(largeNbr, *it);
        largeNbr.insert(largeNbr.begin() + pos, *it);
    }
    std::copy(largeNbr.begin(), largeNbr.end(), begin);
}
int PmergeMe::dichotomousSearch(std::vector<int> &vector, int value)
{
    int left = 0;
    int right = vector.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (vector[mid] == value)
            return mid;
        else if (vector[mid] > value)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return left;
}

void PmergeMe::execute()
{

    recursive(vec.begin(), vec.end());
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
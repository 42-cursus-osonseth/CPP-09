#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(char **argv) : size(0), start(clock())
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
void PmergeMe::swap(std::vector<int>::iterator a, std::vector<int>::iterator b)
{
    if (*b > *a)
        return;
    int tmp = *b;
    *b = *a;
    *a = tmp;
}
void PmergeMe::sortPairs(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    for (std::vector<int>::iterator it = begin; it != end - 1 && it != end; it += 2)
        swap(it, it + 1);
}
void PmergeMe::groupSmallAndLarge(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::vector<int> &smallNbr, std::vector<int> &largeNbr)
{
    int size = std::distance(begin, end);
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
    }
    else
    {
        for (std::vector<int>::iterator it = begin; it != end - 1; it += 2)
            smallNbr.push_back(*it);
        for (std::vector<int>::iterator it = begin + 1; it != end; it += 2)
            largeNbr.push_back(*it);
        smallNbr.push_back(*(end - 1));
    }
}
void PmergeMe::insertSmall(std::vector<int>::iterator begin, std::vector<int> &smallNbr, std::vector<int> &largeNbr)
{
    for (std::vector<int>::iterator it = smallNbr.begin(); it != smallNbr.end(); it++)
    {
        int pos = dichotomousSearch(largeNbr, *it);
        largeNbr.insert(largeNbr.begin() + pos, *it);
    }
    std::copy(largeNbr.begin(), largeNbr.end(), begin);
}

void PmergeMe::recursiveMergeInsert(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    int size = std::distance(begin, end);
    if (size <= 1)
        return;
    sortPairs(begin, end);
    std::vector<int> largeNbr;
    std::vector<int> smallNbr;
    groupSmallAndLarge(begin, end, smallNbr, largeNbr);
    recursiveMergeInsert(largeNbr.begin(), largeNbr.end());
    insertSmall(begin, smallNbr, largeNbr);
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
void PmergeMe::executeVectorSort()
{
    print_vec();
    recursiveMergeInsert(vec.begin(), vec.end());
    clock_t endExecVec = clock();
    print_vec();
    double time_taken = double(endExecVec - start) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << time_taken << " seconds" << std::endl;
}

void PmergeMe::execute()
{
    executeVectorSort();
}

void PmergeMe::print_vec()
{
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl
              << std::endl;
}
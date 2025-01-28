#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(char **argv) : size(0)
{
    for (int i = 1; argv[i]; i++)
    {
        std::istringstream iss(argv[i]);
        long int n;
        while (iss >> n)
        {
            vec.push_back(n);
            deque.push_back(n);
            if (set.find(n) != set.end())
                throw std::invalid_argument("Error: duplicate numbers : " + std::string(argv[i]));
            set.insert(n);
        }
        if ((iss.fail() && !iss.eof()) || n < 0 || n > INT_MAX || !argv[i][0])
            throw std::invalid_argument("Error: invalid arguments : " + std::string(argv[i]));
    }
    set.clear();
}
void PmergeMe::swapV(std::vector<int>::iterator a, std::vector<int>::iterator b)
{
    if (*b < *a)
    {
        int tmp = *b;
        *b = *a;
        *a = tmp;
    }
}
void PmergeMe::swapD(std::deque<int>::iterator a, std::deque<int>::iterator b)
{
    if (*b < *a)
    {
        int tmp = *b;
        *b = *a;
        *a = tmp;
    }
}

void PmergeMe::sortPairsVector(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    for (std::vector<int>::iterator it = begin; it != end - 1 && it != end; it += 2)
        swapV(it, it + 1);
}
void PmergeMe::sortPairsDeque(std::deque<int>::iterator begin, std::deque<int>::iterator end)
{
    for (std::deque<int>::iterator it = begin; it != end - 1 && it != end; it += 2)
        swapD(it, it + 1);
}
void PmergeMe::groupSmallAndLargeVector(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::vector<int> &smallNbr, std::vector<int> &largeNbr)
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
void PmergeMe::groupSmallAndLargeDeque(std::deque<int>::iterator begin, std::deque<int>::iterator end, std::deque<int> &smallNbr, std::deque<int> &largeNbr)
{
    int size = std::distance(begin, end);
    if (size % 2 == 0)

    {
        for (std::deque<int>::iterator it = begin; it != end; it += 2)
            smallNbr.push_back(*it);

        for (std::deque<int>::iterator it = begin + 1; it != end; it += 2)
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
        for (std::deque<int>::iterator it = begin; it != end - 1; it += 2)
            smallNbr.push_back(*it);
        for (std::deque<int>::iterator it = begin + 1; it != end; it += 2)
            largeNbr.push_back(*it);
        smallNbr.push_back(*(end - 1));
    }
}
void PmergeMe::insertSmallVector(std::vector<int>::iterator begin, std::vector<int> &smallNbr, std::vector<int> &largeNbr)
{
    for (std::vector<int>::iterator it = smallNbr.begin(); it != smallNbr.end(); it++)
    {
        int pos = dichotomousSearchVector(largeNbr, *it);
        largeNbr.insert(largeNbr.begin() + pos, *it);
    }
    std::copy(largeNbr.begin(), largeNbr.end(), begin);
}
void PmergeMe::insertSmallDeque(std::deque<int>::iterator begin, std::deque<int> &smallNbr, std::deque<int> &largeNbr)
{
    for (std::deque<int>::iterator it = smallNbr.begin(); it != smallNbr.end(); it++)
    {
        int pos = dichotomousSearchDeque(largeNbr, *it);
        largeNbr.insert(largeNbr.begin() + pos, *it);
    }
    std::copy(largeNbr.begin(), largeNbr.end(), begin);
}

int PmergeMe::dichotomousSearchVector(std::vector<int> &vector, int value)
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
int PmergeMe::dichotomousSearchDeque(std::deque<int> &deque, int value)
{
    int left = 0;
    int right = deque.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        if (deque[mid] == value)
            return mid;
        else if (deque[mid] > value)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return left;
}
void PmergeMe::recursiveMergeInsertVector(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    int size = std::distance(begin, end);
    if (size <= 1)
        return;
    sortPairsVector(begin, end);
    std::vector<int> largeNbr;
    std::vector<int> smallNbr;
    groupSmallAndLargeVector(begin, end, smallNbr, largeNbr);
    recursiveMergeInsertVector(largeNbr.begin(), largeNbr.end());
    insertSmallVector(begin, smallNbr, largeNbr);
}
void PmergeMe::executeVectorSort()
{
    clock_t startExecVec = clock();
    print_vec();
    recursiveMergeInsertVector(vec.begin(), vec.end());
    clock_t endExecVec = clock();
    print_vec();
    double time_taken = double(endExecVec - startExecVec) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << time_taken * 1000 << " ms" << std::endl;
}
void PmergeMe::recursiveMergeInsertDeque(std::deque<int>::iterator begin, std::deque<int>::iterator end)
{
    int size = std::distance(begin, end);
    if (size <= 1)
        return;
    sortPairsDeque(begin, end);
    std::deque<int> largeNbr;
    std::deque<int> smallNbr;
    groupSmallAndLargeDeque(begin, end, smallNbr, largeNbr);
    recursiveMergeInsertDeque(largeNbr.begin(), largeNbr.end());
    insertSmallDeque(begin, smallNbr, largeNbr);
}
void PmergeMe::executeDequeSort()
{
    clock_t startExecDeque = clock();
    recursiveMergeInsertDeque(deque.begin(), deque.end());
    clock_t endExecDeque = clock();
    double time_taken = double(endExecDeque - startExecDeque) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << vec.size() << " elements with std::deque : " << time_taken * 1000 << " ms" << std::endl;
}

void PmergeMe::execute()
{
    executeVectorSort();
    executeDequeSort();
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
void PmergeMe::print_deque()
{
    for (std::deque<int>::iterator it = deque.begin(); it != deque.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl
              << std::endl;
}
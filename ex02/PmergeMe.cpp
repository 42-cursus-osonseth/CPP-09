#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}
PmergeMe::PmergeMe(char **argv) : size(0)
{
    startConstructor = clock();
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

void PmergeMe::executeVectorSort()
{
    recursiveMergeInsert<std::vector<int>::iterator, std::vector<int> >(vec.begin(), vec.end());
   
}
void PmergeMe::executeDequeSort()
{
    
    recursiveMergeInsert<std::deque<int>::iterator, std::deque<int> >(deque.begin(), deque.end());
    
    double time_taken = (double(endExecDeque - startExecDeque) / CLOCKS_PER_SEC) + (double(endConstructor - startConstructor) / CLOCKS_PER_SEC);
    std::cout << "Time to process a range of " << vec.size() << " elements with std::deque : " << time_taken * 1000 << " ms" << std::endl;
}

void PmergeMe::execute()
{
    print_vec();
    endConstructor = clock();
    clock_t startExecVec = clock();
    executeVectorSort();
    clock_t endExecVec = clock();
    clock_t startExecDeque = clock();
    executeDequeSort();
    clock_t endExecDeque = clock();
    print_vec();
    double timeTakenVecSort = (double(endExecVec - startExecVec) / CLOCKS_PER_SEC) + (double(endConstructor - startConstructor) / CLOCKS_PER_SEC);
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << timeTakenVecSort * 1000 << " ms" << std::endl;
    double timeTakenDequeSort = (double(endExecDeque - startExecDeque) / CLOCKS_PER_SEC) + (double(endConstructor - startConstructor) / CLOCKS_PER_SEC);
    std::cout << "Time to process a range of " << vec.size() << " elements with std::deque : " << timeTakenDequeSort * 1000 << " ms" << std::endl;
}

void PmergeMe::print_vec()
{
    for (std::vector<int>::reverse_iterator it = vec.rbegin(); it != vec.rend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl
              << std::endl;
}
void PmergeMe::print_deque()
{
    for (std::deque<int>::reverse_iterator it = deque.rbegin(); it != deque.rend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl
              << std::endl;
}

// void PmergeMe::print_both_vec(std::vector<int> vector)
// {
//     for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); ++it)
//     {
//         std::cout << *it << " ";
//     }
//     std::cout << std::endl
//               << std::endl;
// }

//--------------------------------------------------------------------------------------

// void PmergeMe::groupSmallAndLargeDeque(std::deque<int>::iterator begin, std::deque<int>::iterator end, std::deque<int> &smallNbr, std::deque<int> &largeNbr)
// {
//     int size = std::distance(begin, end);
//     if (size % 2 == 0)

//     {
//         for (std::deque<int>::iterator it = begin; it != end; it += 2)
//             smallNbr.push_back(*it);

//         for (std::deque<int>::iterator it = begin + 1; it != end; it += 2)
//         {
//             if (it == end - 1)
//             {
//                 largeNbr.push_back(*it);
//                 break;
//             }
//             largeNbr.push_back(*it);
//         }
//     }
//     else
//     {
//         for (std::deque<int>::iterator it = begin; it != end - 1; it += 2)
//             smallNbr.push_back(*it);
//         for (std::deque<int>::iterator it = begin + 1; it != end; it += 2)
//             largeNbr.push_back(*it);
//         smallNbr.push_back(*(end - 1));
//     }
// }

// void PmergeMe::sortPairsDeque(std::deque<int>::iterator begin, std::deque<int>::iterator end)
// {
//     for (std::deque<int>::iterator it = begin; it != end - 1 && it != end; it += 2)
//         swapD(it, it + 1);
// }

// void PmergeMe::recursiveMergeInsertDeque(std::deque<int>::iterator begin, std::deque<int>::iterator end)
// {
//     int size = std::distance(begin, end);
//     if (size <= 1)
//         return;
//     sortPairsDeque(begin, end);
//     std::deque<int> largeNbr;
//     std::deque<int> smallNbr;
//     groupSmallAndLargeDeque(begin, end, smallNbr, largeNbr);
//     recursiveMergeInsertDeque(largeNbr.begin(), largeNbr.end());
//     insertSmallDeque(begin, smallNbr, largeNbr);
// }

// int PmergeMe::binarySearchDeque(std::deque<int> &deque, int value)
// {
//     int left = 0;
//     int right = deque.size() - 1;

//     while (left <= right)
//     {
//         int mid = left + (right - left) / 2;
//         if (deque[mid] == value)
//             return mid;
//         else if (deque[mid] > value)
//             right = mid - 1;
//         else
//             left = mid + 1;
//     }
//     return left;
// }

// void PmergeMe::insertSmallDeque(std::deque<int>::iterator begin, std::deque<int> &smallNbr, std::deque<int> &largeNbr)
// {
//     for (std::deque<int>::iterator it = smallNbr.begin(); it != smallNbr.end(); it++)
//     {
//         int pos = binarySearchDeque(largeNbr, *it);
//         largeNbr.insert(largeNbr.begin() + pos, *it);
//     }
//     std::copy(largeNbr.begin(), largeNbr.end(), begin);
// }

// void PmergeMe::swapD(std::deque<int>::iterator a, std::deque<int>::iterator b)
// {
//     if (*b < *a)
//     {
//         int tmp = *b;
//         *b = *a;
//         *a = tmp;
//     }
// }
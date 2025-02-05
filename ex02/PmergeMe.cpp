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

void PmergeMe::execute()
{
    print_vec();
    endConstructor = clock();
    clock_t startExecVec = clock();
    recursiveMergeInsert<std::vector<int>::iterator, std::vector<int> >(vec.begin(), vec.end());
    clock_t endExecVec = clock();
    clock_t startExecDeque = clock();
    recursiveMergeInsert<std::deque<int>::iterator, std::deque<int> >(deque.begin(), deque.end()); 
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

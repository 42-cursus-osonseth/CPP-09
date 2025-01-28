#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <exception>
#include <climits>
#include <set>
#include <ctime>

class PmergeMe
{
private:
    std::string arg;
    std::vector<int> vec;
    std::set<int> set;
    std::deque<int> deque;
    int size;
    clock_t startExecVec;
    clock_t endExecVec;
    clock_t startExecDeque;
    clock_t endExecDeque;
    void executeVectorSort();
    void executeDequeSort();
    void recursiveMergeInsertVector(std::vector<int>::iterator begin, std::vector<int>::iterator end);
    void recursiveMergeInsertDeque(std::deque<int>::iterator begin, std::deque<int>::iterator end);
    void groupSmallAndLargeVector(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::vector<int> &smallNbr, std::vector<int> &largeNbr);
    void groupSmallAndLargeDeque(std::deque<int>::iterator begin, std::deque<int>::iterator end, std::deque<int> &smallNbr, std::deque<int> &largeNbr);
    void insertSmallVector(std::vector<int>::iterator begin, std::vector<int> &smallNbr, std::vector<int> &largeNbr);
    void insertSmallDeque(std::deque<int>::iterator begin, std::deque<int> &smallNbr, std::deque<int> &largeNbr);
    void sortPairsVector(std::vector<int>::iterator begin, std::vector<int>::iterator end);
    void sortPairsDeque(std::deque<int>::iterator begin, std::deque<int>::iterator end);
    void swapV(std::vector<int>::iterator a, std::vector<int>::iterator b);
    void swapD(std::deque<int>::iterator a, std::deque<int>::iterator b);
    int dichotomousSearchVector(std::vector<int> &vector, int value);
    int dichotomousSearchDeque(std::deque<int> &deque, int value);
    void print_vec();

public:
    PmergeMe();
    PmergeMe(char **argv);
    ~PmergeMe();
    void execute();
    void print_deque();
};

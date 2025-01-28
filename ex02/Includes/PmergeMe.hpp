#pragma once

#include <iostream>
#include <vector>
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
    int size;
    clock_t start;
    clock_t startExecVec;
    clock_t endExecVec;
    void executeVectorSort();
    void recursiveMergeInsert(std::vector<int>::iterator begin, std::vector<int>::iterator end);
    void groupSmallAndLarge(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::vector<int> &smallNbr, std::vector<int> &largeNbr);
    void insertSmall(std::vector<int>::iterator begin, std::vector<int> &smallNbr, std::vector<int> &largeNbr);
    void sortPairs(std::vector<int>::iterator begin, std::vector<int>::iterator end);
    void swap(std::vector<int>::iterator a, std::vector<int>::iterator b);
    int dichotomousSearch(std::vector<int> &vector, int value);
    void print_vec();

public:
    PmergeMe();
    PmergeMe(char **argv);
    ~PmergeMe();
    void execute();
    
};

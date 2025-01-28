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
    void execVectorSort();
    void sortPairs(std::vector<int>::iterator begin, std::vector<int>::iterator end);
    void swap(std::vector<int>::iterator a, std::vector<int>::iterator b);
    int dichotomousSearch(std::vector<int> &vector, int value);

public:
    PmergeMe();
    PmergeMe(char **argv);
    ~PmergeMe();
    void execute();
    void recursive(std::vector<int>::iterator begin, std::vector<int>::iterator end);
    //----print a delete ------
    void print_arg();
    void print_vec();
};

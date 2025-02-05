#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <exception>
#include <climits>
#include <set>
#include <ctime>
#include <algorithm>

class PmergeMe
{
private:
    std::string arg;
    std::vector<int> vec;
    std::set<int> set;
    std::deque<int> deque;
    long unsigned int size;
    long unsigned int jacob;
    long unsigned int prev;
    long unsigned int total_insert;
    long unsigned int insertCount;
    clock_t startConstructor;
    clock_t endConstructor;
    clock_t startExecVec;
    clock_t endExecVec;
    clock_t startExecDeque;
    clock_t endExecDeque;

    void print_vec();
    void print_deque();

    template <typename T>
    void sortPairs(T begin, T end);
    template <typename T>
    void swap(T a, T b);

    template <typename T, typename C>
    void groupSmallAndLarge(T begin, T end, C &smallNbr, C &largeNbr);
    template <typename T, typename C>
    void groupOdd(T begin, T end, C &smallNbr, C &largeNbr);
    template <typename T, typename C>
    void groupEven(T begin, T end, C &smallNbr, C &largeNbr);

    template <typename C>
    void linkPairs(std::set<std::pair<int, int> > &link, C &largeNbr, C &smallNbr, int size);
    template <typename C>
    void reorganizationSmallNbr(std::set<std::pair<int, int> > &link, C &largeNbr, C &smallNbr, int size);
    template <typename T, typename C>

    void insertSmallNbr(T begin, C &smallNbr, C &largeNbr);
    template <typename C>
    void initData(C &smallNbr);
    template <typename C>
    void recoveryPTR(std::vector<int *> &ptr, C &smallNbr, long unsigned size);
    template <typename C>
    void updateData(C &smallNbr, long unsigned int lastJacob);
    template <typename C>
    void insertFirstNbr(long unsigned int lastJacob, C &smallNbr, C &largeNbr);
    template <typename C>
    void insertAll(C &smallNbr, C &largeNbr);
    template <typename C>
    void insertFromJacobNumber(C &smallNbr, C &largeNbr, std::vector<int *> ptr, int i);
    template <typename C>
    int binarySearch(C &container, int value);
    
    template <typename T, typename C>
    void recursiveMergeInsert(T begin, T end);
  
   

public:
    PmergeMe();
    PmergeMe(char **argv);
    ~PmergeMe();
    void execute();
};

#include "../PmergeMe.tpp"

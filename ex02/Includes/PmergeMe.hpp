#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <exception>
#include <climits>

class PmergeMe
{
private:
    std::string arg;
    std::vector<int> vec;
public:
    PmergeMe();
    PmergeMe(char **argv);
    ~PmergeMe();
    void execute();

    //----print a delete ------
    void print_arg();
    void print_vec();
};



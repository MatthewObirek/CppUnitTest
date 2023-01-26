#include <iostream>

#include "Exam.hpp"

int main(int args, char** arg)
{
    std::cout << "you entered this File" <<arg[1] << std::endl;
    Exam exam;

    exam.BuildFromFile(arg[1]);

    return 0;
}
#include <iostream>

#include "Exam.hpp"

int main(int args, char** arg)
{
    //! List test folder
    std::cout << "you entered this File" <<arg[1] << std::endl;
    Exam exam;
    //* Build exam
    exam.buildFromFile(arg[1]);
    
    exam.printExam();
    //! Run Test
    //will print and allow answer for each test.
    
    return 0;
}
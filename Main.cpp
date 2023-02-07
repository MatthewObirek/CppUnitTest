#include <iostream>
#include <filesystem>

#include "Exam.hpp"

int main(int args, char** arg)
{
    std::string testName;
    std::string Location = "tests";
    std::vector<std::string> testlist;
    //* checks for test
    if (args > 1)
    {
        std::cout << "you entered this File" <<arg[1] << std::endl;
        testName = arg[1];
    }
    else
    {
        //* lists test folder if there are no tests.
        std::cout << "you entered No File" << std::endl;
        std::cout << "Loading Test Folder at :"<< Location << std::endl;
        int n = 1;
        for (const auto & entry : std::filesystem::directory_iterator(Location))
        {
            testlist.push_back(entry.path().filename().string());
            std::cout << "\t"<< n <<  ". " << testlist.back() << std::endl;
            n++;   
        }
        n = 0;
        std::cout << "Which test would you like to choose: ";
        std::cin >> n;
        testName = Location+"/"+testlist.at(n-1);
        std::cout << testName << std::endl;
    }
    
    Exam exam;
    //* Build exam
    exam.buildFromFile(testName);
    
    //* Run Test
    //will print and allow answer for each test.
    exam.runExam();
    return 0;
}
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Exam
{
private:
    class Question
    {
    public:
        enum Type {
            MC, TF, SA, LA
        };
        std::string Q;
        Type type;
        std::string A;
        std::string hint;
        Exam* examRef;
    public:
        //Default Constructor
        Question(std::string line, Exam* examRef);
        //Copy Constructor
        Question(const Question& source);
        //Move Constructor
        Question(Question&& source);
    public:
        std::string toString();
        std::string toString(int& mcint);
    };
    int capacity;
    std::vector<std::string>* MCAnswerList;
    std::vector<Question>* QuestionList;
public:
    //Constructors
    Exam();
    Exam(int capacity);

    //Destructor
    ~Exam();

    //getters
    inline Question getQuestionAt(int i) { return QuestionList->at(i);}
    inline int getCapacity() { return capacity; } 
    inline int getSize() { return QuestionList->size();}
    //setters
    void setCapacity(int capacity);

    //Builders
    void buildFromFile(std::string filename);

    //Run
    void printExam();
    void runExam();
};


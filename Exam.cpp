#include "Exam.hpp"


//* Question Methods
//Constructors
//Default
Exam::Question::Question(std::string line)
{
    
}
//Copy
Exam::Question::Question(const Question& source)
    :Q(source.Q), A(source.A), type(source.type), 
     hint(source.hint) {}
//Move
Exam::Question::Question(Question&& source)
    :Q(std::move(source.Q)), A(std::move(source.A)), 
     type(source.type), hint(std::move(source.hint)) {}

//Constructors
Exam::Exam() :Exam(100) {}
Exam::Exam(int capacity) : capacity(capacity)
{
    QuestionList = new std::vector<Question>;
    QuestionList->reserve(capacity);

    MCAnswerList = new std::vector<std::string>;
    MCAnswerList->reserve(capacity);
}

//Deconstructor
Exam::~Exam()
{
    //? Maybe write to file exam history??
    delete QuestionList;
    delete MCAnswerList;
}

//setters
void Exam::setCapacity(int capacity)
{
    this->capacity = capacity;
}

//Builders
void Exam::BuildFromFile(std::string filename)
{
    //! Create Array of Questions
    //Needed Variables
    std::ifstream file(filename);
    std::vector<Question> Array;

    if (file.is_open()) 
    {
        std::string line;
        while(std::getline(file, line))
        {
            Question Q(line);
            Array.push_back(Q);
        }
    }
    else
    {
        std::cout << "Unable to open file: " << filename << std::endl;
    }

}

void Exam::BuildFromList(std::vector<Question>& Array)
{
    if(Array.size()>capacity)
    {
        capacity = Array.size();
        QuestionList->reserve(capacity);
        MCAnswerList->reserve(capacity);
    }

    for (int i = 0; i < Array.size(); i++)
    {
        QuestionList->emplace_back(Array.at(i));
        if(Array.at(i).type == Question::Type::MC)
        {
            MCAnswerList->emplace_back(Array.at(i).A);
        }
    }
}
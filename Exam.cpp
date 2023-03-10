#include "Exam.hpp"
#include "Log.hpp"
#include <cstdlib>
#include <ctime>

//* Question Methods
//Constructors
//Default
Exam::Question::Question(std::string line, Exam* examRef)
    : examRef(examRef)
{
    std::string token;
    std::string del = "; ";
    size_t pos = 0;
    
    std::vector<std::string> fields;
    fields.reserve(5);
    while((pos = line.find(del)) != std::string::npos)
    {
        token = line.substr(0, pos);
        line.erase(0, pos + del.length());
        fields.emplace_back(token);
    }

    if(fields.at(0).compare("MC") == 0) 
        type = MC;
    else if (fields.at(0).compare("TF") == 0)
        type = TF;
    else 
        type = SA;

    Q = fields.at(1);
    A = fields.at(2);
    hint = fields.at(3);

    Log("\nQuestion Created");
}
//Copy
Exam::Question::Question(const Question& source)
    :Q(source.Q), A(source.A), type(source.type), 
     hint(source.hint) 
{
    examRef = source.examRef;
    Log("\nQuestion Copied");
}
//Move
Exam::Question::Question(Question&& source)
    :Q(std::move(source.Q)), A(std::move(source.A)), 
     type(source.type), hint(std::move(source.hint)) 
{
    examRef = source.examRef;
    source.examRef = nullptr;
    Log("\nQuestion Moved");
}

std::string Exam::Question::toString()
{
    int nullnum = 0;
    return toString(nullnum);
}
std::string Exam::Question::toString(int& mcint)
{
    std::string str;
    std::vector<std::string> MCA;
    MCA.reserve(3);
    switch(type)
    {
    case Type::MC:
    {       
        srand(time(0));
        mcint = rand()%3;
        for(int i = 0; i < 3; i++)
        {
            if(mcint == i)
            {
                MCA.emplace_back(A); 
            }
            else
            {
                //* Made sure correct answer is not written twice.
                int j = -1;
                do { 
                    j = rand() % examRef->MCAnswerList->size();                    
                } while ((examRef->MCAnswerList->at(j).compare(A) == 0) || compareHelper(j, MCA));

                MCA.emplace_back(examRef->MCAnswerList->at(j));
            }
        }
        str = Q + "\nHint: " + hint + "\n"
            + "\t(0)a) " + MCA[0] + "\n"
            + "\t(1)b) " + MCA[1] + "\n"
            + "\t(2)c) " + MCA[2] + "\n"; 
    }
    break;
    case Type::TF:
    {
        if (A.compare("True") == 0)
            mcint = 0;
        else if (A.compare("False") == 0)
            mcint = 1;
        else
            Log("error");
        str = Q + "\nHint: " + hint + "\n\tTrue(0) or False(1)";
    }
    break;
    case Type::SA: 
        mcint = -1;
        str = Q + "\nHint: " + hint;
    break;
    case Type::LA:
        mcint = -1;
        str = Q + "\nHint: " + hint;
    break;
    default:
        mcint == -1;
        str = Q + "\nHint: " + hint; 
    
    }

    return str;
}

bool Exam::Question::compareHelper(int j , std::vector<std::string>& MCA)
{
    for (std::string elem : MCA)
    {
        if (elem.compare(examRef->MCAnswerList->at(j)) == 0)
            return true;
    }
    return false;
}


//*Constructors
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
    if(QuestionList->size()>capacity)
    {
        capacity = QuestionList->size();
        QuestionList->reserve(capacity);
        MCAnswerList->reserve(capacity);
    }
}

//* Builders
void Exam::buildFromFile(std::string filename)
{
    //Needed Variables
    std::ifstream file(filename);
    
    if (file.is_open()) 
    {
        std::string line;
        int size = 0; 
        while(std::getline(file, line))
        {
            size++;
            QuestionList->emplace_back(line, this);
            if (QuestionList->back().type == Question::Type::MC)
                MCAnswerList->emplace_back(QuestionList->back().A);

            if (size > (capacity-5))
                Log("Text Exam is reaching size capacity");
        }
    }
    else
    {
        std::cout << "Unable to open file: " << filename << std::endl;
        return;
    }
    Log("Exam Created");
    return;
}

//* Run
void Exam::printExam()
{
    for (int i = 0; i < QuestionList->size(); i++)
    {
        std::cout << i << ") " << QuestionList->at(i).toString() << std::endl;
    }
    return;
}

void Exam::runExam()
{
    int numCorrect = 0;
    for (int i = 0; i < QuestionList->size(); i++)
    {
        int mcint = 0;
        int answer = 0;
        std::cout << i << ") " << QuestionList->at(i).toString(mcint) << std::endl;
        if (mcint == -1)
            std::cout << "This is a short or long answer question" << std::endl;
        else
        {
            std::cin >> answer;
            if(answer == mcint)
            {
                numCorrect++;
                std::cout << "Correct!" << std::endl;
            }
            else
            {
                std::cout << "Incorrect!" << std::endl;
            }
        }
    }
    std::cout << numCorrect << " out of " << QuestionList->size() << std::endl;
    return;

}
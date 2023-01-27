#include "Exam.hpp"
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

    std::cout << "\nQuestion Created" << std::endl;
}
//Copy
Exam::Question::Question(const Question& source)
    :Q(source.Q), A(source.A), type(source.type), 
     hint(source.hint) 
{
    examRef = source.examRef;
}
//Move
Exam::Question::Question(Question&& source)
    :Q(std::move(source.Q)), A(std::move(source.A)), 
     type(source.type), hint(std::move(source.hint)) 
{
    examRef = source.examRef;
    source.examRef = nullptr;
}

std::string Exam::Question::toString()
{
    std::string str;
    std::vector<std::string> MCA;
    MCA.reserve(3);
    switch(type)
    {
    case Type::MC:
    {       
        srand(time(0));
        int correctAnswer = rand()%3;
        std::cout << correctAnswer << std::endl;
        for(int i = 0; i < 3; i++)
        {
            if(correctAnswer == i)
            {
                MCA.emplace_back(A); 
            }
            else
            {
                MCA.emplace_back(examRef->MCAnswerList->at(rand() % examRef->MCAnswerList->size()));
            }
        }
        str = Q + "\nHint: " + hint + "\n"
            + "\ta) " + MCA[0] + "\n"
            + "\tb) " + MCA[1] + "\n"
            + "\tc) " + MCA[2] + "\n"; 
    }
    break;
    case Type::TF:
        str = Q + "\nHint: " + hint + "\n\tTrue or False";
    break;
    case Type::SA: str = Q + "\nHint: " + hint;
    break;
    case Type::LA: str = Q + "\nHint: " + hint;
    break;
    default:
        str = Q + "\nHint: " + hint; 
    
    }

    return str;
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
    //! Create Array of Questions
    //Needed Variables
    std::ifstream file(filename);
    
    if (file.is_open()) 
    {
        std::string line;
        int size = 0; 
        while(std::getline(file, line))
        {
            size++;
            Question Q(line, this);
            QuestionList->emplace_back(Q);
            if (Q.type == Question::Type::MC)
                MCAnswerList->emplace_back(Q.A);

            if (size > (capacity-5))
                std::cout << "Text Exam is reaching size capacity" << std::endl;
        }
    }
    else
    {
        std::cout << "Unable to open file: " << filename << std::endl;
        return;
    }
    std::cout << "Exam Created" << std::endl;
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


}
#include<iostream>
#include<list>
#include<map>

using namespace std;

class User {
    string userId;
    string userName;
    string email;
public:
    User(string id, string name, string mail) :
        userId(id), userName(name), email(mail) {}

    string getUserId() {
        return userId;
    }

    string getUserName() {
        return userName;
    }

    string getEmail() {
        return email;
    }

    void displayInfo() {
        cout<<"UserId: "<<userId<<endl;
        cout<<"UserName: "<<userName<<endl;
        cout<<"Email: "<<email<<endl;
    }
};

// Forward Declaration
class Answer;

class Question {
    string questionId;
    string title;
    string description;
    list<Answer*> answers;
    User* author;
    list<string> tags;
public:
    Question(string id, string title, string desc, User* author, list<string> tags) :
        questionId(id), title(title), description(desc), author(author), tags(tags) {}

    string getQuestionId() {
        return questionId;
    }

    string getTitle() {
        return title;
    }

    string getDescription() {
        return description;
    }

    User* getAuthor() {
        return author;
    }

    list<Answer*> listAnswers() {
        return answers;
    }

    list<string> listTags() {
        return tags;
    }

    void addAnswer(Answer* answer) {
        answers.emplace_back(answer);
    }

    void displayInfo() {
        cout<<"QuestionId: "<<questionId<<endl;
        cout<<"Title: "<<title<<endl;
        cout<<"Description: "<<description<<endl;
        cout<<"Author: "<<author->getUserName()<<endl;
    }
};

class Answer {
    string answerId;
    string description;
    User* author;
    Question* question;
public:
    Answer(string id, string desc, User* author, Question* question) :
        answerId(id), description(desc), author(author), question(question) {}

    string getAnswerId() {
        return answerId;
    }

    string getDescription() {
        return description;
    }

    User* getAuthor() {
        return author;
    }

    void displayInfo() {
        cout<<"AnswerId: "<<answerId<<endl;
        cout<<"Description: "<<description<<endl;
        cout<<"Author: "<<author->getUserName()<<endl;
    }

};


class StackOverflow {
    map<string, User*> users;
    map<string, Question*> questions;
    map<string, Answer*> answers;

    int userIdCounter = 0;
    int questionIdCounter = 0;
    int answerIdCounter = 0;
public:
    User* createUser(string name, string email) {
        User* user = new User("u" + to_string(userIdCounter), name, email);
        userIdCounter++;
        users[user->getUserId()] = user;

        return user;
    }

    void displayUserProfile(string userId) {
        User* user = users[userId];
        user->displayInfo();
    }

    Question* postQuestion(string title, string desc, User* author, list<string> tags) {
        Question* question = new Question("q" + to_string(questionIdCounter), title, desc, author, tags);
        questionIdCounter++;
        questions[question->getQuestionId()] = question;
        return question;
    }

    Answer* postAnswer(string description, string authorId, string questionId) {
        User* author = users[authorId];
        Question* question = questions[questionId];
        Answer* answer = new Answer("a" + to_string(answerIdCounter), description, author, question);
        answerIdCounter++;
        answers[answer->getAnswerId()] = answer;
        question->addAnswer(answer);
        return answer;
    }

    void displayQuestion(string questionId) {
        Question* question = questions[questionId];

        question->displayInfo();
        list<Answer*> answers = question->listAnswers();
        
        cout<<"Answers: \n";
        for(Answer* answer: answers) {
            answer->displayInfo();
        }
    }

    vector<string> searchQuestions(string tag) {
        vector<string> res;
        for(auto [_, question]: questions) {
            auto tags = question->listTags();
            for(auto tg: tags) {
                if(tg == tag) {
                    res.push_back(question->getQuestionId());
                }
            }
        }

        return res;
    }

    vector<Question*> getQuestionsByUser(string userId) {
        User* user = users[userId];
        vector<Question*> ans;
        for(auto [_, question] : questions) {
            if(question->getAuthor() == user) {
                ans.push_back(question);
            }
        }
        return ans;
    }
};


int main() {
    StackOverflow stackoverflow;
    
    // Register users
    User* user1 = stackoverflow.createUser("john_doe", "john@email.com");
    User* user2 = stackoverflow.createUser("alice_smith", "alice@email.com");
    User* user3 = stackoverflow.createUser("bob_wilson", "bob@email.com");
    
    std::cout << "Initial users:" << std::endl;
    stackoverflow.displayUserProfile(user1->getUserId());
    
    // Add questions
    // std::vector<std::string> tags = {"c++", "programming"};
    Question* question1 = stackoverflow.postQuestion(
        "Smart Pointers",
        "How do I use smart pointers in C++?",
        user1,
        {"C++", "Pointers"}
    );
    
    // Add answers
    Answer* answer1 = stackoverflow.postAnswer(
        "Smart pointers automatically manage memory for you...",
        user2->getUserId(),
        question1->getQuestionId()
    );
    
    Answer* answer2 = stackoverflow.postAnswer(
        "There are three main types of smart pointers...",
        user3->getUserId(),
        question1->getQuestionId()
    );
    
    // Add comments
    // stackoverflow.addComment(
    //     user1->getUserId(),
    //     answer1->getPostId(),
    //     "Thanks, that's helpful!"
    // );
    
    // Vote on posts
    // stackoverflow.votePost(user2->getUserId(), question1->getPostId());
    // stackoverflow.votePost(user3->getUserId(), answer1->getPostId());
    // stackoverflow.votePost(user1->getUserId(), answer2->getPostId());
    
    // Accept answer
    // stackoverflow.acceptAnswer(user1->getUserId(), answer1->getPostId());
    
    // Display results
    std::cout << "\nQuestion with answers:" << std::endl;
    stackoverflow.displayQuestion(question1->getQuestionId());

    
    std::cout << "\nUser profiles after activity:" << std::endl;
    stackoverflow.displayUserProfile(user1->getUserId());
    stackoverflow.displayUserProfile(user2->getUserId());
    
    // Search questions
    std::cout << "\nSearching for C++ questions:" << std::endl;
    auto results = stackoverflow.searchQuestions("C++");
    for (const auto& questionId : results) {
        stackoverflow.displayQuestion(questionId);
    }
    
    return 0;
}

// Question and Answer can be clubbed into Post class, with type QUESTION/ANSWER



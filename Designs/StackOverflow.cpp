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

class Tag {
    string tagId;
    string name;
public:
    Tag(string id, string name) :
        tagId(id), name(name);

    string getTagId() {
        return tagId;
    }

    string getTagName() {
        return name;
    }
};

class Question {
    string questionId;
    string title;
    string description;
    list<Answer*> answers;
    User* author;
    list<Tag*> tags;
public:
    Question(string id, string title, string desc, User* author) :
        questionId(id), title(title), description(desc), author(author) {}

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

    list<Tag*> listTags() {
        return tags;
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

};


class StackOverflow {
    map<string, User*> users;
    map<string, Question*> questions;
    map<string, Answer*> answers;
    map<string, Tag*> tags;

    int userIdCounter = 0;
    int questionIdCounter = 0;
    int answerIdCounter = 0;
public:
    void createUser(string name, string email) {
        User* user = new User("u" + to_string(userIdCounter), name, email);
        userIdCounter++;
        users[user->getUserId()] = user;
    }

    void postQuestion(string title, string desc, User* author) {
        Question* question = new Question("q" + to_string(questionIdCounter), title, desc, author);
        questionIdCounter++;
        questions[question->getQuestionId()] = question;
    }

    void PostAnswer(string description, string authorId, string questionId) {
        User* author = users[authorId];
        Question* question = questions[questionId];
        Answer* answer = new Answer("a" + to_string(answerIdCounter), description, author, question);
        answerIdCounter++;
        answers[answer->getAnswerId()] = answer;
    }

    void searchQuestions();

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






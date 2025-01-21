#include <bits/stdc++.h>
#include"Questions.h"
using namespace std;

Questions::Questions() : ID(-1), allow_anonymous_questions(-1),
                         threadID(-1), User_Name_To(""), User_Name_From(""), content("") {};

Questions::Questions(int id, string &From, string &TO, int AllAny, int threadId, string &content) : ID(id),
                               User_Name_From(From) , User_Name_To(TO) , allow_anonymous_questions(AllAny),
                               threadID(threadId) , content(content) {}

void Questions::setID(int Id) {
    this->ID = Id;
}

void Questions::set_Allow_anonymous_questions(int any) {
    this->allow_anonymous_questions = any;
}

void Questions::setThreadId(int thread) {
    this->threadID = thread;
}

void Questions::set_User_Name_From(const string &NewName) {
    this->User_Name_From = NewName;
}

void Questions::set_User_Name_To(const string &NewName) {
    this->User_Name_To = NewName;
}

void Questions::set_Content_Of_The_Questions(const string &NewContent) {
    this->content = NewContent;
}

int Questions::getID() const {
    return ID;
}

int Questions::getIsAnon() const {
    return allow_anonymous_questions;
}

int Questions::getThreadID() const {
    return threadID;
}

string Questions::getNameFrom(bool Any) const {
    if(Any && getIsAnon() == 1)
        return "Anonymous";
    return User_Name_From;
}

string Questions::getNameTO() const {
    return User_Name_To;
}

string Questions::getContentOfTheQuestion() const {
    return content;
}

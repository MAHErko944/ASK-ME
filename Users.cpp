#include<bits/stdc++.h>
#include"Users.h"
using namespace std;
Users::Users() : ID(-1), allow_anonymous_questions(-1), userName(""), password("") {}

Users::Users(int ID, int allowAno, std::string userName, std::string password) : ID(ID),
                       userName(userName), password(password){}
int Users::getId() const {
    return ID;
}
int Users::getAccountID() const {
    return ID;
}
int Users::getAnonymous() const{
    return allow_anonymous_questions;
}
const string &Users::getAccountUserName() const {
    return userName;
}
const string &Users::getAccountPassword()  const{
    return password;
}
const vector<int> &Users::getQuestionsFromMe() const {
    return questionsFromMe;
}
const map<int, vector<int>> &Users::getQuestionsThreads() const {
    return questionsThreads;
}
void Users::LogOut() {
    userName = "";
    password = "";
    ID = -1;
    allow_anonymous_questions = -1;
    questionsFromMe.clear();
    questionsThreads.clear();
}
void Users::Reload_Questions_From_Me(const vector<int> &new_My_Questions)  {
    questionsFromMe.clear();
    for (auto &i: new_My_Questions) {
        questionsFromMe.emplace_back(i);
    }
}
void Users::Reload_Questions_Threads(const map<int, vector<int>> &new_Questions_Threads) {
    questionsThreads.clear();
    for (auto &x: new_Questions_Threads) {
        for (auto &qID: x.second) {
            questionsThreads[x.first].emplace_back(qID);
        }
    }
}
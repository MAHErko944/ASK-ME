
#ifndef ASK_FM_ACCOUNT_H
#define ASK_FM_ACCOUNT_H
#include<bits/stdc++.h>
using namespace std;
class Users {
private:
    int ID;
    int allow_anonymous_questions;
    string userName;
    string password;
    vector<int> questionsFromMe;
    map<int, vector<int>> questionsThreads;
public:
    Users();

    Users(int ID, int allowAno, string userName, string password);

    int getAccountID() const;

    int getAnonymous() const;

    const string &getAccountUserName() const;

    const string &getAccountPassword() const;

    int getId() const;

    const vector<int> &getQuestionsFromMe() const;

    const map<int, vector<int>> &getQuestionsThreads() const;

    void LogOut();
    void Reload_Questions_From_Me(const vector<int> &new_My_Questions);
    void Reload_Questions_Threads(const map<int, vector<int>> &new_Questions_Threads);
};
#endif //ASK_FM_ACCOUNT_H

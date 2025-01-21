#ifndef ASK_FM_CONFIGURATION_H
#define ASK_FM_CONFIGURATION_H
#include <bits/stdc++.h>
#include "Answer.h"
#include "Questions.h"
#include "Users.h"
using namespace std;
class clsAccount {
private:
    Users myAccount;
    map<string, Users> Account;
    int LastId;
public:
    clsAccount();

    void loadAccount();

    void updateAccount();

    void registerAccount();

    void loginAccount();

    void list_Of_Account();

    void logOutAccount();

    void ReloadQuestions(const vector<int> &questions_From_Me, const map<int, vector<int>> &questions_To_Me);

    const Users &getMyAccount() const;

    map<string, Users> &getAccounts();
};
class clsQUESTION {
private:
    map<int, vector<int>> questionsThreads;
    map<int, Questions> questions;
    int lastID;
public:
    clsQUESTION();

    void loadQuestions();

    void updateQuestions();

    void showQuestionToUser(const Users &acc, const map<int, Answer> &answers) const;

    void showQuestionsFromUser(const Users &acc, const map<int, Answer> &answers) const;

    void askQuestion(const Users &acc, map<string, Users> &accounts);

    void answerQuestion(const Users &acc, map<int, Answer> &answers, int lastAnswerID);

    void deleteQuestion(const Users &acc, map<int, Answer> &answers);

    void showFeed(map<int, Answer> &answers) const;
};
class clsAnswer {
protected:
    map<int, Answer> answers;
    int lastID;
public:
    clsAnswer();

    void loadAnswers();

    void updateAnswers();

    map<int, Answer> &getAnswers();

    int getLastID();
};
class clsSystem {
private:
    clsAccount accountsSystem;
    clsQUESTION questionsSystem;
    clsAnswer answersSystem;

    void loadData(bool resetUsersQuestions);

    void updateData();

    void resetQuestions();

    void startMenu();

public:
    void run();
};
#endif //ASK_FM_CONFIGURATION_H

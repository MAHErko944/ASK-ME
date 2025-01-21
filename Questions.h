#ifndef ASK_FM_QUESTIONS_H
#define ASK_FM_QUESTIONS_H
#include <bits/stdc++.h>
using namespace std;
class Questions {
private :
    int ID;
    int allow_anonymous_questions;
    int threadID;
    string User_Name_To;
    string User_Name_From;
    string content;
public:
    Questions();

    Questions(int id, string &From, string &TO, int AllAny, int ThreadId, string &content);

    void setID(int Id);

    void set_Allow_anonymous_questions(int any);

    void setThreadId(int thread);

    void set_User_Name_From(const string &NewName);

    void set_User_Name_To(const string &NewName);

    void set_Content_Of_The_Questions(const string &NewContent);

    int getID() const;

    int getIsAnon() const;

    int getThreadID() const;

    string getNameFrom(bool Any) const;

    string getNameTO() const;

    string getContentOfTheQuestion() const;


};
#endif //ASK_FM_QUESTIONS_H

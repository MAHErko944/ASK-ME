#ifndef ASK_FM_ANSWER_H
#define ASK_FM_ANSWER_H
#include <bits/stdc++.h>
using namespace std;
class Answer {
private:
    int answerId;
    int questionId;
    string answerQuestion;
public:
    Answer();

    Answer(int answerId, int questionId, const string &content);

    void setAnswerId(int Id);

    void setQuestionId(int Id);

    void setContentAnswer(const string &content);

    int getAnswerId() const;

    int getQuestionId() const;

    string getContentAnswer() const;
};
#endif //ASK_FM_ANSWER_H

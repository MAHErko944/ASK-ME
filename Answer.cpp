#include <bits/stdc++.h>
#include "Answer.h"
using namespace std;
Answer::Answer():answerId(-1) , questionId(-1) , answerQuestion("") {}
Answer::Answer(int answerId, int questionId, const std::string &content) {
    this->questionId = questionId;
    this->answerId = answerId;
    this->answerQuestion = content;
}

void Answer::setQuestionId(int Id) {
    this->questionId = Id;
}

void Answer::setAnswerId(int Id) {
    this->answerId = Id;
}
void Answer::setContentAnswer(const std::string &content) {
    this->answerQuestion = content;
}

int Answer::getQuestionId() const {
    return questionId;
}

int Answer::getAnswerId() const {
    return answerId;
}

string Answer::getContentAnswer() const {
    return answerQuestion;
}


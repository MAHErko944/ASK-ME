#include "Configuration.h"
#include<bits/stdc++.h>
using namespace std;
#define Account_Path string("D:/ASK_fm/Account.txt.txt").c_str()
#define Questions_Path string("D:/ASK_fm/Questions.txt.txt").c_str()
#define Answer_Path string("D:/ASK_fm/Answers.txt.txt").c_str()
vector<string> split(const string &str, const string &delimiter = ";") {
    string Na = str;
    vector<string> strings;
    int pos = 0;
    string substr;
    while ((pos = (int) Na.find(delimiter)) != -1) {
        substr = Na.substr(0, pos);
        strings.push_back(substr);
        Na.erase(0, pos + delimiter.length());
    }
    strings.push_back(Na);
    return strings;
}
int toInt(const string &str) {
    istringstream iss(str);
    int number;
    iss >> number;
    return number;
}
/* _______________ALL THE CONFIGURATION THE ASK_ME SYSTEM_______-___  */
clsAccount::clsAccount():LastId(-1) {}
void clsAccount::loadAccount() {
    Account.clear();
    LastId = 0;
    ifstream accountRead(Account_Path);
    if (!accountRead) {
        cerr << "Open accounts.txt Failed\n";
        exit(0);
    }
    string line;
    while (getline(accountRead, line)) {
        vector<string> data = split(line);
        Account[data[2]] = Users(toInt(data[0]), toInt(data[1]), data[2], data[3]);
        LastId = max(LastId, toInt(data[0]));
    }
    accountRead.close();
}
void clsAccount::updateAccount() {
    ofstream output(Account_Path);
    for (auto &acc: Account) {
        string log = to_string(acc.second.getAccountID()) + ";" + to_string(acc.second.getAnonymous()) + ";" +
                     acc.second.getAccountUserName() + ";" + acc.second.getAccountPassword();
        output << log << endl;
    }
    output.close();
}
void clsAccount::registerAccount() {
    string UserName, Password;
    bool is_Correct;
    do {
        is_Correct = false;
        cout << "___________Please Enter UserName___________" << endl;
        cin >> UserName;
        if (!Account.count(UserName)) {
            cout << "_____Username is used before!..Please try another UserName...______" << endl;
        } else {
            is_Correct = true;
        }
    } while (is_Correct);
    cout << "___________Please Enter Password__________" << endl;
    cin >> Password;
    int allow_anonymous_questions;
    do {
        allow_anonymous_questions = 0;
        cin >> allow_anonymous_questions;
        if (allow_anonymous_questions != 0 && allow_anonymous_questions != 1) {
            cout << "Please enter 0 for noAnonymous or 1 for yesAnonymous..!!" << endl;
        }
    } while (allow_anonymous_questions != 0 && allow_anonymous_questions != 1);
    ++LastId;
    Account[UserName] = Users(LastId, allow_anonymous_questions, UserName, Password);
    myAccount = Account[UserName];
    cout << "Account with ID..: " << LastId << " created successfully...." << endl;
    updateAccount();
}
void clsAccount::loginAccount() {
    string UserName, Password;
    bool is_Correct;
    do {
        is_Correct = false;
        cout << "___________Please Enter UserName___________" << endl;
        cin >> UserName;
        cout << "___________Please Enter Password___________" << endl;
        cin >> Password;
        if (!Account.count(UserName))
            cout << "Username does not exist! Try Again..." << endl;
        else if (Account[UserName].getAccountPassword() != Password)
            cout << "Password does not exist! Try Again..." << endl;
        else {
            is_Correct = true;
            myAccount = Account[UserName];
        }
    } while (!is_Correct);
    cout << "___________YOU HAVE SUCCESSFULLY LOGIN....___________" << endl;
}
void clsAccount::list_Of_Account() {
    cout << "_______ Account Lists... " << endl;
    for (auto it: Account) {
        cout << "ID For Account : " << it.second.getId() << "\tUserName For Account : "
             << it.second.getAccountUserName() << endl;
    }
    cout << endl;
    int choose = 0;
    do {
        cout << "Enter -1 to go back...: ";
        cin >> choose;
        if (choose == -1) {
            break;
        }
    } while (choose != -1);
}
void clsAccount::logOutAccount() {
    myAccount.LogOut();
    cout<<"____LogOut successfully.... "<<endl;
    cout<<endl;
}
void clsAccount::ReloadQuestions(const vector<int> &questionsFromMe, const map<int, vector<int>> &questionsToMe) {
    myAccount.Reload_Questions_From_Me(questionsFromMe);
    myAccount.Reload_Questions_Threads(questionsToMe);
}
const Users &clsAccount::getMyAccount() const {
    return myAccount;
}
map<string, Users> &clsAccount::getAccounts() {
    return Account;
}
clsQUESTION::clsQUESTION() : lastID(-1) {}
void clsQUESTION::loadQuestions() {
    questions.clear();
    lastID = 0;
    ifstream questionRead(Questions_Path);
    if (!questionRead) {
        cerr << "Open questions.txt Failed\n";
        exit(0);
    }
    string line;
    while (getline(questionRead, line)) {
        vector<string> data = split(line);
        questions[toInt(data[0])] = Questions(toInt(data[0]), data[1], data[2], toInt(data[3]), toInt(data[4]), data[5]);
        if (toInt(data[4]) == -1) {
            questionsThreads[toInt(data[0])].push_back(toInt(data[0]));
        } else {
            questionsThreads[toInt(data[4])].push_back(toInt(data[0]));
        }
        lastID = max(lastID, toInt(data[0]));
    }
    questionRead.close();
}
void clsQUESTION::updateQuestions() {
    ofstream output(Questions_Path);
    for (auto &qus: questions) {
        string str =
                to_string(qus.second.getID()) + ";" + qus.second.getNameFrom(false) + ";" + qus.second.getNameTO() +
                ";" + to_string(qus.second.getIsAnon()) + ";" + to_string(qus.second.getThreadID()) + ";" +
                qus.second.getContentOfTheQuestion();
        output << str << endl;
    }
    output.close();
}
void clsQUESTION::showQuestionToUser(const Users &acc, const map<int, Answer> &answers) const {
    cout << "____ Questions Sent To "<< acc.getAccountUserName() << " ___" << endl;
    for (auto &it: questions) {
        if (it.second.getNameTO() == acc.getAccountUserName()) {
            cout << "\t" << "A Question (ID: " << it.second.getID() << "): " << it.second.getContentOfTheQuestion() << endl;
            cout << "\t" << "From: " << it.second.getNameFrom(true) << endl;
            string answerContent;
            for (auto &ans: answers) {
                if (ans.second.getQuestionId() == it.second.getID()) {
                    answerContent = ans.second.getContentAnswer();
                }
            }
            cout << "\t" << "Answer: " << answerContent << endl;
            cout << endl;
        }
    }
    int choose = 0;
    do {
        cout << "Enter -1 to go back...: ";
        cin >> choose;
        if (choose == -1) {
            break;
        }
    } while (choose != -1);
}
void clsQUESTION::showQuestionsFromUser(const Users &acc, const map<int, Answer> &answers) const {
    cout << "____ Questions Sent by "<< acc.getAccountUserName() << " ____" << endl;
    for (auto &it: questions) {
        if (it.second.getNameFrom(false) == acc.getAccountUserName()) {
            cout << "\t" << "Question (ID: " << it.second.getID() << "): " << it.second.getContentOfTheQuestion()
                 << endl;
            cout << "\t" << "To: " << it.second.getNameTO() << endl;
            string answerContent;
            for (auto &ans: answers) {
                if (ans.second.getQuestionId() == it.second.getID()) {
                    answerContent = ans.second.getAnswerId();
                }
            }
            cout << "\t" << "Answer: " << answerContent << endl;
            cout << endl;
        }
    }
    int choose = 0;
    do {
        cout << "Enter -1 to go back....: ";
        cin >> choose;
        if (choose == -1) {
            break;
        }
    } while (choose != -1);
}
void clsQUESTION::askQuestion(const Users &acc, map<string, Users> &accounts) {
    cout << "_______ Ask Question..... _________" << endl;
    string userName ;
            bool isExist;
    do {
        isExist = false;
        cout << "\t" << "Enter the username you want ask (or -1 to go back)..: ";
        cin >> userName;
        if (userName == "-1") {
            break;
        }
        if (accounts.count(userName)) {
            isExist = true;
        }
        if (!isExist) {
            cout << "\t" << "Username Not Found...! Please Try Again...." << endl;
        } else {
            if (userName == acc.getAccountUserName()) {
                cout << "\t" << "You Can't Ask Yourself! Are You Stupid?? ..." << endl;
                isExist = false;
            }
        }
    } while (!isExist);
    if (!accounts.count(userName)) {
        cout << endl;
        return;
    }
    int isAnon = 0;
    if (accounts[userName].getAnonymous() == 0) {
        cout << "\t" << "NOTE: This Person Doesn't Allow Anonymous Questions....!" << endl;
    } else {
        cout << "\t" << "Anonymous Question (1 For Yes, 0 For No)...: ";
        cin >> isAnon;
    }
    int threadID = -1;
    do {
        cout << "For Thread Question: Enter Question Id or -1 for New Question...: ";
        cin >> threadID;
        if (threadID == -1) {
            break;
        }
        if (!questionsThreads.count(threadID)) {
            cout << "No thread question with such ID. Try again...! " << endl;
            threadID = -1;
        }
    } while (threadID == -1);

    Questions newQuestion;
    lastID++;
    newQuestion.setID(lastID);
    newQuestion.setThreadId(threadID);
    string userFrom = acc.getAccountUserName();
    newQuestion.set_User_Name_From(userFrom);
    newQuestion.set_User_Name_To(userName);
    newQuestion.set_Allow_anonymous_questions(isAnon);
    cout << "\t" << "________Enter question content....: ";
    string questionContent;
    getline(cin >> ws, questionContent);
    newQuestion.set_Content_Of_The_Questions(questionContent);
    questions[lastID] = newQuestion;
    if (newQuestion.getThreadID() == -1) {
        questionsThreads[lastID].push_back(lastID);
    } else {
        questionsThreads[newQuestion.getThreadID()].push_back(lastID);
    }
    cout << "Question (ID: " << lastID << ") " << " sent successfully to " << userName << "." << endl;
    int choose = 0;
    do {
        cout << "Enter -1 to go back: ";
        cin >> choose;
        if (choose == -1) {
            break;
        }
    } while (choose != -1);
}
void clsQUESTION::answerQuestion(const Users &acc, map<int, Answer> &answers, int lastAnswerID) {
    cout << "* Answer Question *" << endl;
    int questionID = -1;
    bool isExist;
    string answerContent;
    do {
        isExist = false;
        cout << "\t" << "_____Enter question id (or -1 to go back)...:____ ";
        cin >> questionID;
        if (questionID == -1) {
            break;
        }
        if (!questions.count(questionID)) {
            cout << "_____Wrong question id. Try Again______" << endl;
            isExist = false;
        } else {
            if (questions[questionID].getNameTO() != acc.getAccountUserName()) {
                cout << "Please enter question id belongs to you! Surely you are stupid..." << endl;
                isExist = false;
            } else {
                isExist = true;
                answerContent = answers[questionID].getContentAnswer();
            }
        }
    } while (!isExist);
    if (questionID == -1) {
        cout << endl;
        return;
    }
    cout << "\t" << "Question (ID: " << questionID << "): " << questions[questionID].getContentOfTheQuestion() << endl;
    cout << "\t" << "From: " << questions[questionID].getNameFrom(true) << endl;
    cout << "\t" << "Answer: " << answerContent << endl;
    cout << endl;
    string newAnswerContent;
    cout << "Enter your answer (answer will be overwrote or -1 to go back)....: ";
    getline(cin >> ws, newAnswerContent);
    if (newAnswerContent == "-1") {
        cout << endl;
        return;
    }
    answers[questionID].setAnswerId(lastAnswerID + 1);
    answers[questionID].setQuestionId(questionID);
    answers[questionID].setContentAnswer(newAnswerContent);
    int choose = 0;
    do {
        cout << "Enter -1 to go back....: ";
        cin >> choose;
        if (choose == -1) {
            break;
        }
    } while (choose != -1);
}
void clsQUESTION::deleteQuestion(const Users &acc, map<int, Answer> &answers) {
    cout << "_________ Delete Question ________" << endl;
    int questionID = -1;
    bool isMine;
    do {
        isMine = false;
        cout << "\t" << "Enter Question ID (or -1 to go back)...: ";
        cin >> questionID;
        if (questionID == -1) {
            break;
        }
        for (auto &qs: questions) {
            if (qs.second.getID() == questionID && qs.second.getNameFrom(false) == acc.getAccountUserName()) {
                isMine = true;
                break;
            }
        }
        if (!isMine) {
            cout << "Please enter question ID belongs to you!... " << endl;
        }
    } while (!isMine);
    if (questionID == -1) {
        return;
    }
    vector<int> deletedIDs;
    if (questionsThreads.count(questionID)) {
        deletedIDs = questionsThreads[questionID];
        questionsThreads.erase(questionID);
    } else {
        deletedIDs.push_back(questionID);
        for (auto &x: questionsThreads) {
            vector<int> &v = x.second;
            for (int i = 0; i < (int) v.size(); ++i) {
                if (questionID == v[i]) {
                    answers.erase(questionID);
                    v.erase(v.begin() + i);
                    break;
                }
            }
        }
        for (const auto &x: deletedIDs) {
            answers.erase(x);
            questions.erase(x);
        }
    }
    int check = 0;
    do {
        cout << "Enter -1 to go back....: ";
        cin >> check;
        if (check == -1) {
            break;
        }
    } while (check != -1);
}
void clsQUESTION::showFeed(map<int, Answer> &answers) const {
    cout << "________ Feed _________" << endl;
    for (auto &it: questions) {
        if (it.second.getThreadID() != -1) {
            cout << "Thread ID (" << it.second.getThreadID() << ")";
        }
        cout << "\t" << "Question (ID: " << it.second.getID() << "): " << it.second.getContentOfTheQuestion() << endl;
        cout << "\t" << "From: " << it.second.getNameFrom(true) << ", To: " << it.second.getNameTO() << endl;
        string answerContent;
        for (auto &ans: answers) {
            if (ans.second.getQuestionId() == it.second.getID()) {
                answerContent = ans.second.getContentAnswer();
            }
        }
        cout << "\t" << "Answer....: " << answerContent << endl;
        cout << endl;
    }
    int choose = 0;
    do {
        cout << "Enter -1 to go back....: ";
        cin >> choose;
        if (choose == -1) {
            break;
        }
    } while (choose != -1);
}
clsAnswer::clsAnswer() : lastID(-1) {}
void clsAnswer::loadAnswers() {
    answers.clear();
    lastID = 0;
    ifstream answerRead(Answer_Path);
    if (!answerRead) {
        cerr << "Open answers.txt Failed....\n";
        exit(0);
    }
    string str;
    while (getline(answerRead, str)) {
        vector<string> data = split(str);
        answers[toInt(data[1])] = Answer(toInt(data[0]), toInt(data[1]), data[2]);
        lastID = max(lastID, toInt(data[0]));
    }
    answerRead.close();
}
void clsAnswer::updateAnswers() {
    ofstream output(Answer_Path);
    for (auto &ans: answers) {
        string log = to_string(ans.second.getAnswerId()) + ";" + to_string(ans.second.getQuestionId()) + ";" +
                     ans.second.getContentAnswer();
        output << log << endl;
    }
    output.close();
}
map<int, Answer> &clsAnswer::getAnswers() {
    return answers;
}
int clsAnswer::getLastID() {
    return lastID;
}
void clsSystem::loadData(bool resetUsersQuestions = false) {
    accountsSystem.loadAccount();
    questionsSystem.loadQuestions();
    answersSystem.loadAnswers();
    if (resetUsersQuestions) {
        resetQuestions();
    }
}
void clsSystem::updateData() {
    accountsSystem.updateAccount();
    questionsSystem.updateQuestions();
    answersSystem.updateAnswers();
}
void clsSystem::resetQuestions() {
    const auto &questionsFromMe = accountsSystem.getMyAccount().getQuestionsFromMe();
    const auto &questionsToMe = accountsSystem.getMyAccount().getQuestionsThreads();
    accountsSystem.ReloadQuestions(questionsFromMe, questionsToMe);
}
void clsSystem::startMenu() {
    cout << "______ MENU _______" << endl;
    cout << "\t" << "1: Login..." << endl;
    cout << "\t" << "2: Register..." << endl;
    string operationMsg = "Please enter operation number: ";
    int operationNumber = -1;
    do {
        cout << operationMsg;
        cin >> operationNumber;
        if (operationNumber != 1 && operationNumber != 2) {
            cout << "Invalid operation number!" << endl;
        }
    } while (operationNumber != 1 && operationNumber != 2);
    cout << endl;
    switch (operationNumber) {
        case 1: {
            accountsSystem.loginAccount();
            break;
        }
        case 2: {
            accountsSystem.registerAccount();
            break;
        }
    }
}
void clsSystem::run() {
    loadData(false);
    startMenu();
    resetQuestions();
    while (true) {
        updateData();
        loadData(true);
        cout << "Menu:" << endl;
        cout << "\t" << "1: Show questions to me..." << endl;
        cout << "\t" << "2: Show questions from me..." << endl;
        cout << "\t" << "3: Answer question..." << endl;
        cout << "\t" << "4: Delete question..." << endl;
        cout << "\t" << "5: Ask question..." << endl;
        cout << "\t" << "6: List users..." << endl;
        cout << "\t" << "7: Feed..." << endl;
        cout << "\t" << "8: Logout..." << endl;

        string operationMsg = "Please enter operation number: ";
        int operationNumber;
        do {
            cout << operationMsg;
            cin >> operationNumber;
            if (operationNumber > 8 || operationNumber < 1) {
                cout << "Invalid operation number!" << endl;
            }
        } while (operationNumber > 8 || operationNumber < 1);
        cout << endl;

        switch (operationNumber) {
            case 1: {
                questionsSystem.showQuestionToUser(accountsSystem.getMyAccount(), answersSystem.getAnswers());
                break;
            }
            case 2: {
                questionsSystem.showQuestionsFromUser(accountsSystem.getMyAccount(), answersSystem.getAnswers());
                break;
            }
            case 3: {
                questionsSystem.answerQuestion(accountsSystem.getMyAccount(), answersSystem.getAnswers(),
                                               answersSystem.getLastID());
                updateData();
                break;
            }
            case 4: {
                questionsSystem.deleteQuestion(accountsSystem.getMyAccount(), answersSystem.getAnswers());
                resetQuestions();
                updateData();
                break;
            }
            case 5: {
                questionsSystem.askQuestion(accountsSystem.getMyAccount(), accountsSystem.getAccounts());
                updateData();
                break;
            }
            case 6: {
                accountsSystem.list_Of_Account();
                break;
            }
            case 7: {
                questionsSystem.showFeed(answersSystem.getAnswers());
                break;
            }
            case 8: {
                accountsSystem.logOutAccount();
                return;
            }
        }
    }
    run();
}

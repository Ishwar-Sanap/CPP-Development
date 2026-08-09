#include <bits/stdc++.h>
using namespace std;

/*
*******************************
Design Simple StackOverflow
*******************************

Requiremens
- User should asks questions
- Other user should able to answers it
- Questions can be tagged by topic names
- User can Upvote/Downvote on questions and answers (self votting must be restricted)
- When question is marked as closed then no any more answers should be accepted
--Extra Requirement (TODO)
- Users should able to add Comments on question or answer
- Searching questions/answers by keyword or tag name

*/
enum class VoteType
{
    UPVOTE = 0,
    DOWNVOTE = 1
};

class Votable
{
public:
    virtual void upVote() = 0;
    virtual void downVote() = 0;
    virtual ~Votable() = default;
};

class Answer;
class User;

class Question : public Votable
{
private:
    int id;
    string description;
    int votesCnt{};
    vector<Answer *> answers; // Composition (Question owns answers)
    vector<string> tags;
    User *user; // Association
    bool isOpen{true};

public:
    Question(int id, User *user, const string &desc, const vector<string> &tags) : id(id), user(user), description(desc), tags(tags)
    {
    }

    ~Question(); // declare Destructor

    void upVote() override
    {
        votesCnt++;
    }
    void downVote() override
    {
        votesCnt--;
    }
    Answer *postAnswer(int id, User *user, const string &desc); // declaration
    int getId() const { return id; }
    int getVotesCnt() const { return votesCnt; }
    const string &getDescription() const { return description; }
    vector<Answer *> &getAnswers() { return answers; }
    vector<string> &getTags() { return tags; }
    User *getUser() { return user; }
    void setOpenStatus(User *user, bool status);
    bool getOpenStatus() const { return isOpen; }
};

class Answer : public Votable
{
private:
    int id;
    string description;
    int votesCnt{};
    User *user; // Association

public:
    Answer(int id, User *user, const string &desc) : id(id), user(user), description(desc)
    {
    }
    void upVote() override
    {
        votesCnt++;
    }
    void downVote() override
    {
        votesCnt--;
    }
    void updateAnswer(const string &newDesc)
    {
        description = newDesc;
    }

    int getId() const { return id; }
    int getVotesCnt() const { return votesCnt; }
    const string &getDescription() const { return description; }
    User *getUser() { return user; }
};

class User
{
private:
    int id;
    string userName;
    vector<Question *> questions; // user can post multiple questions (association)
    vector<Answer *> answers;     // Answers given by the user
    unordered_map<int, VoteType> votedQuestion;
    unordered_map<int, VoteType> votedAnswer;

public:
    User(int id, const string &uName) : id(id), userName(uName) {}
    string getUserName() const { return userName; }
    int getUserId() const { return id; }
    unordered_map<int, VoteType> &getVotedQuestions() { return votedQuestion; }
    unordered_map<int, VoteType> &getVotedAnswers() { return votedAnswer; }

    void addAnswer(Answer *answer)
    {
        answers.push_back(answer);
    }
    void addQuestion(Question *question)
    {
        questions.push_back(question);
    }
    const vector<Question *> &getPostedQuestions() const { return questions; }
    const vector<Answer *> &getPostedAnswers() const { return answers; }
};

Answer *Question::postAnswer(int id, User *user, const string &desc)
{
    if (!isOpen)
        throw invalid_argument("Question is not accepting answer anymore..");

    Answer *ans = new Answer(id, user, desc);
    answers.push_back(ans);
    user->addAnswer(ans);
    return ans;
}

Question::~Question()
{
    // to delete the object of answer class, there must be Answer class defined earlier in code
    for (auto &ans : answers)
    {
        delete ans;
        ans = nullptr;
    }
}

void Question::setOpenStatus(User *otherUser, bool status)
{
    if (!otherUser || otherUser->getUserId() != this->getUser()->getUserId())
        throw invalid_argument("Invalid User");

    isOpen = status;
}
// Singleton class to mange all the things internally
class StackOverflowManager
{
private:
    unordered_map<int, User *> mpIdToUser;
    unordered_map<int, Question *> mpIdToQuestion;
    StackOverflowManager() {};
    int userId = 1;
    int quesId = 1;
    int ansId = 1;

public:
    StackOverflowManager(const StackOverflowManager &) = delete;
    StackOverflowManager &operator=(const StackOverflowManager &) = delete;

    static StackOverflowManager &getInstance()
    {
        static StackOverflowManager obj;
        return obj;
    }

    ~StackOverflowManager()
    {
        for (auto &it : mpIdToUser)
        {
            delete it.second;
        }

        for (auto &it : mpIdToQuestion)
        {
            delete it.second;
        }
    }

    User *createUser(const string &uName)
    {
        User *usr = new User(userId, uName);
        mpIdToUser[userId] = usr;
        userId++;
        return usr;
    }

    Question *askQuestion(User *user, const string &desc, const vector<string> &tags = {})
    {
        Question *ques = new Question(quesId, user, desc, tags);
        user->addQuestion(ques);
        mpIdToQuestion[quesId] = ques;
        quesId++;

        return ques;
    }

    Answer *postAnswer(User *user, Question *ques, const string &desc)
    {
        if (ques->getOpenStatus() == false)
            throw invalid_argument("Question is not accepting answer anymore..");

        if (!user)
            throw invalid_argument("Invalid User");
        else if (!ques)
            throw invalid_argument("Invalid Question");
        else if (desc.empty())
            throw invalid_argument("Answer can not be empty");

        Answer *ans = ques->postAnswer(ansId, user, desc);
        ansId++;
        return ans;
    }

    void changeQuestionStatus(User *user, Question *ques, bool status)
    {
        if (!user || user->getUserId() != ques->getUser()->getUserId())
            throw invalid_argument("Invalid User");

        ques->setOpenStatus(user, status);
    }

    void updateVote(User *user, Question *ques, VoteType type)
    {
        if (user->getUserId() == ques->getUser()->getUserId())
        {
            throw invalid_argument("Self vote is not allowed!");
        }
        auto &votedList = user->getVotedQuestions();

        if (type == VoteType::UPVOTE)
        {
            if (votedList.find(ques->getId()) != votedList.end() && votedList[ques->getId()] == VoteType::UPVOTE)
            {
                throw invalid_argument("Already Upvoted!");
            }
            else if (votedList.find(ques->getId()) != votedList.end() && votedList[ques->getId()] == VoteType::DOWNVOTE)
            {
                // Moving from DOWNVOTE to UPVOTE -> +2
                ques->upVote();
                ques->upVote();
                votedList[ques->getId()] = VoteType::UPVOTE;
            }
            else
            {
                // New UPVOTE -> +1
                ques->upVote();
                votedList[ques->getId()] = VoteType::UPVOTE;
            }
        }
        else if (type == VoteType::DOWNVOTE)
        {
            if (votedList.find(ques->getId()) != votedList.end() && votedList[ques->getId()] == VoteType::DOWNVOTE)
            {
                throw invalid_argument("Already downvote!");
            }
            else if (votedList.find(ques->getId()) != votedList.end() && votedList[ques->getId()] == VoteType::UPVOTE)
            {
                // Moving from UPVOTE to DOWNVOTE -> -2
                ques->downVote();
                ques->downVote();
                votedList[ques->getId()] = VoteType::DOWNVOTE;
            }
            else
            {
                // New DOWNVOTE -> -1
                ques->downVote();
                votedList[ques->getId()] = VoteType::DOWNVOTE;
            }
        }
    }

    void updateVote(User *user, Answer *ans, VoteType type)
    {
        if (user->getUserId() == ans->getUser()->getUserId())
        {
            throw invalid_argument("Self vote is not allowed!");
        }

        auto &votedList = user->getVotedAnswers();

        if (type == VoteType::UPVOTE)
        {
            if (votedList.find(ans->getId()) != votedList.end() && votedList[ans->getId()] == VoteType::UPVOTE)
            {
                throw invalid_argument("Already Upvoted!");
            }
            else if (votedList.find(ans->getId()) != votedList.end() && votedList[ans->getId()] == VoteType::DOWNVOTE)
            {
                // Moving from DOWNVOTE to UPVOTE -> +2
                ans->upVote();
                ans->upVote();
                votedList[ans->getId()] = VoteType::UPVOTE;
            }
            else
            {
                // New UPVOTE -> +1
                ans->upVote();
                votedList[ans->getId()] = VoteType::UPVOTE;
            }
        }
        else if (type == VoteType::DOWNVOTE)
        {
            if (votedList.find(ans->getId()) != votedList.end() && votedList[ans->getId()] == VoteType::DOWNVOTE)
            {
                throw invalid_argument("Already downvote!");
            }
            else if (votedList.find(ans->getId()) != votedList.end() && votedList[ans->getId()] == VoteType::UPVOTE)
            {
                // Moving from UPVOTE to DOWNVOTE -> -2
                ans->downVote();
                ans->downVote();
                votedList[ans->getId()] = VoteType::DOWNVOTE;
            }
            else
            {
                // New DOWNVOTE -> -1
                ans->downVote();
                votedList[ans->getId()] = VoteType::DOWNVOTE;
            }
        }
    }
};

int main()
{
    try
    {
        StackOverflowManager &sm = StackOverflowManager::getInstance();

        User *user1 = sm.createUser("User 1");
        User *user2 = sm.createUser("User 2");
        Question *q1 = sm.askQuestion(user1, "What is copy constructor?", {"C++", "OOP"});
        Question *q2 = sm.askQuestion(user1, "What is default class size?");

        Answer *ans1 = sm.postAnswer(user2, q1, "Copy constructor create duplicate copy of given object");
        Answer *ans2 = sm.postAnswer(user2, q2, "Default size is 1Byte");
        Answer *ans3 = sm.postAnswer(user2, q2, "Default size is 1Byte, but when there is virtual function then it's 8 Byte reversed for (vptr)");
        sm.updateVote(user2, q1, VoteType::UPVOTE);
        sm.updateVote(user1, ans1, VoteType::UPVOTE);
        sm.updateVote(user1, ans1, VoteType::DOWNVOTE);
        sm.updateVote(user1, ans3, VoteType::UPVOTE);
        // sm.updateVote(user2, q1, VoteType::UPVOTE);

        cout << "List of questions asked by user1\n";
        for (auto &que : user1->getPostedQuestions())
        {
            cout << "-----------------------------------------------\n";
            cout << que->getDescription() << "[ Vote : " << que->getVotesCnt() << " ]" << endl;
            cout << "-----------------------------------------------\n";
            cout << "Received Answers : " << endl;

            for (auto &ans : que->getAnswers())
            {
                cout << ans->getDescription() << "[ Vote : " << ans->getVotesCnt() << " ]" << endl;
            }

            cout << endl;
        }

        sm.changeQuestionStatus(user1, q2, true);
        Answer *ans4 = sm.postAnswer(user2, q2, "Size is 1Byte");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
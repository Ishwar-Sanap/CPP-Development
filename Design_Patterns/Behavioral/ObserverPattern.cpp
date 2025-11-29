#include <bits/stdc++.h>
using namespace std;

/*
		- It Define a one-to-many relationship
When one object (Subject) changes state, all dependent objects (Observers) are notified automatically
*/
class Observer
{
public:
    virtual void update(string news) = 0;
};

class Subject
{
public:
    virtual void addObserver(Observer *ptr) = 0;
    virtual void removeObserver(Observer *ptr) = 0;
    virtual void notifyObserver(string news) = 0;
};

// Concreate subject
class NewsAgency : public Subject
{
    unordered_set<Observer *> m_setObserverPtr;

public:
    void addObserver(Observer *ptr) override
    {
        m_setObserverPtr.insert(ptr);
    }

    void removeObserver(Observer *ptr) override
    {
        m_setObserverPtr.erase(ptr);
    }

    void notifyObserver(string news)
    {
        for (auto it : m_setObserverPtr)
        {
            //brodcasting news to all observers
            it->update(news);
        }
    }

    void brodCastNews(string news)
    {
        notifyObserver(news);
    }
};

// Concreate Observer
class Subscriber : public Observer
{
    string m_userName;

public:
    Subscriber(string name) : m_userName(name) {}
    void update(string news) override
    {
        cout << m_userName << " got the news : " << news << endl;
    }
};

int main()
{

    Observer* user1 = new Subscriber("user1");
    Observer* user2 = new Subscriber("user2");
    Observer* user3 = new Subscriber("user3");

    NewsAgency obj;
    obj.addObserver(user1);    
    obj.addObserver(user2);    
    obj.addObserver(user3);
    
    obj.brodCastNews("Latest New C++ featured is annonced..");
    
    obj.removeObserver(user2);
    cout<<"-----------------------------------------\n";
    
    obj.brodCastNews("updates are broadcast to all..");

    delete user1;
    delete user2;
    delete user3;

    return 0;
}
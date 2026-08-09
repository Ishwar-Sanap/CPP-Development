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
            // brodcasting news to all observers
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

// Example 2
class WeatherStation; // Forward declaration

class WeatherObserver
{
public:
    virtual ~WeatherObserver() {}
    virtual void update(WeatherStation *station) = 0;
};

class WeatherStation
{
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;
    vector<WeatherObserver *> observers;

public:
    void registerObserver(WeatherObserver *observer)
    {
        observers.push_back(observer);
    }

    void removeObserver(WeatherObserver *observer)
    {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void setMeasurements(double temperature, double humidity, double pressure)
    {
        this->temperature = temperature;
        this->humidity = humidity;
        this->pressure = pressure;
        notifyObservers();
    }

    double getTemperature() const { return temperature; }
    double getHumidity() const { return humidity; }
    double getPressure() const { return pressure; }

private:
    void notifyObservers()
    {
        for (auto observer : observers)
            observer->update(this);
    }
};

class CurrentConditionsDisplay : public WeatherObserver
{
public:
    void update(WeatherStation *station) override
    {
        printf("Current Conditions -> Temp: %.1f, Humidity: %.1f%%, Pressure: %.1f hPa\n",
               station->getTemperature(), station->getHumidity(), station->getPressure());
    }
};

class StatisticsDisplay : public WeatherObserver
{
    vector<double> readings;

public:
    void update(WeatherStation *station) override
    {
        readings.push_back(station->getTemperature());
        double sum = accumulate(readings.begin(), readings.end(), 0.0);
        double avg = sum / readings.size();
        printf("Statistics -> Avg Temperature: %.1f\n", avg);
    }
};

void WeatherStationExample()
{
    WeatherStation station;
    CurrentConditionsDisplay current;
    StatisticsDisplay stats;
    station.registerObserver(&current);
    station.registerObserver(&stats);
    station.setMeasurements(25.0, 65.0, 1013.0);
    station.setMeasurements(28.0, 70.0, 1012.0);
    station.setMeasurements(22.0, 90.0, 1011.0);
}

int main()
{

    // Observer *user1 = new Subscriber("user1");
    // Observer *user2 = new Subscriber("user2");
    // Observer *user3 = new Subscriber("user3");

    // NewsAgency obj;
    // obj.addObserver(user1);
    // obj.addObserver(user2);
    // obj.addObserver(user3);

    // obj.brodCastNews("Latest New C++ featured is annonced..");

    // obj.removeObserver(user2);
    // cout << "-----------------------------------------\n";

    // obj.brodCastNews("updates are broadcast to all..");

    // delete user1;
    // delete user2;
    // delete user3;

    WeatherStationExample();

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

/*
- It provides a step-by-step approach to constructing complex objects.
- If you use a constructor with many arguments, it becomes hard to read and error-prone:
Ex: Car car("SUV", "V8", 4, true, "Black");  // what does 'true' mean here??
Builder lets you construct step by step, with more readability and flexibility.
*/

// Product
class Car
{
private:
    string m_sType;
    string m_sEngine;
    int m_iSeats;
    bool m_bSunroof;

public:
    void setType(const string &type) { this->m_sType = type; }
    void setEngine(const string &engine) { this->m_sEngine = engine; }
    void setSeats(const int &seats) { this->m_iSeats = seats; }
    void setSunRoof(const bool &sunroof) { this->m_bSunroof = sunroof; }

    void getSpecs()
    {
        cout << "\n-----------------------------------------------\n";
        cout << "Car Type : " << this->m_sType << endl;
        cout << "Engine Type : " << this->m_sEngine << endl;
        cout << "No of seats : " << this->m_iSeats << endl;
        cout << "Sunroof : " << this->m_bSunroof << endl;
        cout << "\n-----------------------------------------------\n";
    }
};

// Builder Abstract class
class CarBuilder
{
public:
    virtual void buildType() = 0;
    virtual void buildEngine() = 0;
    virtual void buildSetas() = 0;
    virtual void buildSunRoof() = 0;
    virtual Car *getCar() = 0;
};

// concreate builder
class SportsCarBuilder : public CarBuilder
{
    Car *ptrCarObj = nullptr;

public:
    SportsCarBuilder() { ptrCarObj = new Car(); }
    void buildType() override { ptrCarObj->setType("Sports"); }
    void buildEngine() override { ptrCarObj->setEngine("V8"); }
    void buildSetas() override { ptrCarObj->setSeats(2); }
    void buildSunRoof() override { ptrCarObj->setSunRoof(true); }
    Car *getCar() override
    {
        return ptrCarObj;
    }

    ~SportsCarBuilder()
    {
        delete ptrCarObj;
        ptrCarObj = nullptr;
    }
};
class SUVCarBuilder : public CarBuilder
{
    Car *ptrCarObj = nullptr;

public:
    SUVCarBuilder() { ptrCarObj = new Car(); }
    void buildType() override { ptrCarObj->setType("SUV"); }
    void buildEngine() override { ptrCarObj->setEngine("V6"); }
    void buildSetas() override { ptrCarObj->setSeats(7); }
    void buildSunRoof() override { ptrCarObj->setSunRoof(false); }
    Car *getCar() override
    {
        return ptrCarObj;
    }

    ~SUVCarBuilder()
    {
        delete ptrCarObj;
        ptrCarObj = nullptr;
    }
};

class Director
{

public:
    Car *construct(CarBuilder &builder)
    {
        builder.buildType();
        builder.buildEngine();
        builder.buildSetas();
        builder.buildSunRoof();

        return builder.getCar();
    }
};


//Client
int main()
{
    Director dir;

    SportsCarBuilder sportCarbuild;
    Car *ptrObjSportCar = dir.construct(sportCarbuild);

    ptrObjSportCar->getSpecs();

    SUVCarBuilder suvbuild;
    Car *ptrobjSuvCar = dir.construct(suvbuild);

    ptrobjSuvCar->getSpecs();

    return 0;
}
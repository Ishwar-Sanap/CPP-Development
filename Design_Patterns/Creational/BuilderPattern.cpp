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

void example1()
{
    Director dir;

    SportsCarBuilder sportCarbuild;
    Car *ptrObjSportCar = dir.construct(sportCarbuild);

    ptrObjSportCar->getSpecs();

    SUVCarBuilder suvbuild;
    Car *ptrobjSuvCar = dir.construct(suvbuild);

    ptrobjSuvCar->getSpecs();
}

// Example 2

/*
SQL QueryBuilder
A query builder that constructs SQL SELECT statements step-by-step. This is a common pattern in ORMs and database libraries*/
class SqlQuery
{
private:
    string table;
    vector<string> columns;
    vector<string> conditions;
    string orderByCol;
    string orderDir;
    int limitVal;
    int offsetVal;

    // Private constructor, since we are not allowing to create object directly
    SqlQuery(const string &table, const vector<string> &columns,
             const vector<string> &conditions, const string &orderByCol,
             const string &orderDir, int limitVal, int offsetVal)
        : table(table), columns(columns), conditions(conditions),
          orderByCol(orderByCol), orderDir(orderDir),
          limitVal(limitVal), offsetVal(offsetVal) {}

public:
    string toSql() const
    {
        string sql = "SELECT ";
        if (columns.empty())
        {
            sql += "*";
        }
        else
        {
            for (size_t i = 0; i < columns.size(); i++)
            {
                if (i > 0)
                    sql += ", ";
                sql += columns[i];
            }
        }
        sql += " FROM " + table;
        if (!conditions.empty())
        {
            sql += " WHERE ";
            for (size_t i = 0; i < conditions.size(); i++)
            {
                if (i > 0)
                    sql += " AND ";
                sql += conditions[i];
            }
        }
        if (!orderByCol.empty())
        {
            sql += " ORDER BY " + orderByCol + " " + orderDir;
        }
        if (limitVal > 0)
            sql += " LIMIT " + to_string(limitVal);
        if (offsetVal > 0)
            sql += " OFFSET " + to_string(offsetVal);
        return sql;
    }

    class Builder
    {
    private:
        string table;
        vector<string> columns;
        vector<string> conditions;
        string orderByCol;
        string orderDir = "ASC";
        int limitVal = 0;
        int offsetVal = 0;

    public:
        explicit Builder(const string &table) : table(table) {}

        Builder &select(initializer_list<string> cols)
        {
            columns.insert(columns.end(), cols.begin(), cols.end());
            return *this;
        }

        Builder &where(const string &condition)
        {
            conditions.push_back(condition);
            return *this;
        }

        Builder &orderBy(const string &col, const string &dir)
        {
            orderByCol = col;
            orderDir = dir;
            return *this;
        }

        Builder &limit(int l)
        {
            limitVal = l;
            return *this;
        }
        Builder &offset(int o)
        {
            offsetVal = o;
            return *this;
        }

        SqlQuery build() const
        {
            return SqlQuery(table, columns, conditions,
                            orderByCol, orderDir, limitVal, offsetVal);
        }
    };
};

void example2()
{

/*
    Builder is a nested class inside SqlQuery
SqlQuery::Builder("users") creates a temporary Builder object
each method like select(), where(), orderBy(), limit(), and build() returns a reference to that builder, so the chain works
So the flow is:

This creates a temporary object of the Builder class.
    */
    auto query1 = SqlQuery::Builder("users")
                      .select({"name", "email"})
                      .where("age > 18")
                      .where("active = true")
                      .orderBy("name", "ASC")
                      .limit(10)
                      .build();

    auto query2 = SqlQuery::Builder("orders")
                      .select({"id", "total", "created_at"})
                      .where("status = 'completed'")
                      .where("total > 100")
                      .orderBy("created_at", "DESC")
                      .limit(20)
                      .offset(40)
                      .build();

    cout << query1.toSql() << endl;
    cout << query2.toSql() << endl;
}

// Client

int main()
{
    example1();
    example2();

    return 0;
}
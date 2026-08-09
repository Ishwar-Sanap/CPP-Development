#include <bits/stdc++.h>
using namespace std;

/*
Proxy = a stand-in object that controls access to another object.
Instead of using the real object directly, the client interacts with a proxy that:
*/

class Image
{
public:
    virtual void showDetails() = 0;
    virtual ~Image() = default;
};

class RealImage : public Image
{
    string m_strName;

public:
    RealImage(string name) : m_strName(name)
    {
        loadImageFromDisk();
    }

    void showDetails() override
    {
        cout << "Showing deatils of " << m_strName << endl;
    }

    void loadImageFromDisk()
    {
        cout << "Loading Image from disk..." << endl;
    }

    ~RealImage()
    {
        cout << "Unloading Image " << endl;
    }
};

class ImageProxy : public Image
{
    string m_strName;
    Image *ptrRealImage;

public:
    ImageProxy(string name) : m_strName(name), ptrRealImage(nullptr) {}
    void showDetails()
    {
        if (ptrRealImage == nullptr)
        {
            ptrRealImage = new RealImage(m_strName);
        }

        ptrRealImage->showDetails();
    }

    ~ImageProxy()
    {
        delete ptrRealImage;
        ptrRealImage = nullptr;
    }
};

// Example 2
// Database Query Caching Proxy

class DatabaseService
{
public:
    virtual string query(const string &sql) = 0;
    virtual ~DatabaseService() {}
};

class RealDatabaseService : public DatabaseService
{
public:
    string query(const string &sql) override
    {
        cout << "RealDatabase: Executing query: " << sql << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
        return "Result for [" + sql + "]";
    }
};

class CachingDatabaseProxy : public DatabaseService
{
private:
    RealDatabaseService realService;
    unordered_map<string, string> cache;

public:
    string query(const string &sql) override
    {
        auto it = cache.find(sql);
        if (it != cache.end())
        {
            cout << "CachingProxy: Cache HIT for: " << sql << endl;
            return it->second;
        }
        cout << "CachingProxy: Cache MISS for: " << sql << endl;
        string result = realService.query(sql);
        cache[sql] = result;
        return result;
    }

    void clearCache()
    {
        cout << "CachingProxy: Cache cleared." << endl;
        cache.clear();
    }
};

void runDbQuery()
{
    CachingDatabaseProxy db;

    cout << "--- First query (cache miss) ---" << endl;
    cout << db.query("SELECT * FROM users") << endl;

    cout << "\n--- Same query again (cache hit) ---" << endl;
    cout << db.query("SELECT * FROM users") << endl;

    cout << "\n--- Different query (cache miss) ---" << endl;
    cout << db.query("SELECT * FROM orders WHERE status = 'pending'") << endl;

    cout << "\n--- Clear cache and retry ---" << endl;
    db.clearCache();
    cout << db.query("SELECT * FROM users") << endl;

}
int main()
{
    // ImageProxy img1("sounds.png");
    // img1.showDetails();
    // img1.showDetails();
    // img1.showDetails();

    runDbQuery();
    return 0;
}
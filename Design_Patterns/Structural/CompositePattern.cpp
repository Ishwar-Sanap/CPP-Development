#include <bits/stdc++.h>
using namespace std;

// Composite pattern:
// It allows you to treat single object or group of objects in similar way

// Interface
class FileSystem
{
public:
    virtual void showDetails() = 0;
    virtual ~FileSystem() = default;
};

class File : public FileSystem
{
    string m_strFileName;

public:
    File(string fName) : m_strFileName(fName) {}

    void showDetails() override
    {
        cout << "File : " << m_strFileName << endl;
    }
};

class Folder : public FileSystem
{
    // Composition, storing Files + Folder
    vector<FileSystem *> m_vectorPtr;
    string m_strName;

public:
    Folder(string name) : m_strName(name) {}

    void add(FileSystem *ptr)
    {
        m_vectorPtr.push_back(ptr);
    }

    void showDetails() override
    {
        cout << "Folder : " << m_strName << endl;
        for (auto ptr : m_vectorPtr)
        {
            ptr->showDetails();
        }
    }
};

// Example 2:
/*
Problem: Build a restaurant menu system where individual menu items and submenus share a common interface.
A MenuItem is a leaf with a name and price.
A SubMenu is a composite with a name that contains menu items and other submenus.
*/
class Menu
{
public:
    virtual void display(string indent) = 0;
    virtual int getItemCount() = 0;
    virtual ~Menu() {}
};

class MenuItem : public Menu
{
private:
    string name;
    double price;

public:
    MenuItem(string name, double price) : name(name), price(price) {}

    void display(string indent) override
    {
        printf("%s%s - $%.2f\n", indent.c_str(), name.c_str(), price);
    }

    int getItemCount() override { return 1; }
};

class SubMenu : public Menu
{
    string name;
    vector<Menu *> children;

public:
    SubMenu(string name) : name(name)
    {
    }

    void addItem(Menu *item)
    {
        children.push_back(item);
    }

    void display(string indent) override
    {
        cout << indent << name << ":" << endl;
        for (auto child : children)
        {
            child->display(indent + "  ");
        }
    }

    int getItemCount() override
    {
        int cnt = 0;
        for (auto child : children)
        {
            cnt += child->getItemCount();
        }

        return cnt;
    }
};

void RestaurantMenuSystem()
{
    MenuItem burger("Burger", 8.99);
    MenuItem fries("Fries", 3.99);
    MenuItem cola("Cola", 1.99);
    MenuItem water("Water", 0.99);

    SubMenu drinks("Drinks");
    drinks.addItem(&cola);
    drinks.addItem(&water);

    SubMenu mainMenu("Main Menu");
    mainMenu.addItem(&burger);
    mainMenu.addItem(&fries);
    mainMenu.addItem(&drinks);

    mainMenu.display("");
    cout << "\nTotal items: " << mainMenu.getItemCount() << endl;
}

int main()
{
    FileSystem *f1 = new File("abc.txt");
    FileSystem *f2 = new File("README.md");

    Folder *MyFiles = new Folder("MyFiles");
    MyFiles->add(f1);
    MyFiles->add(f2);

    Folder *root = new Folder("Root");

    // since Folder inherits from FileSystemItem, the compiler automatically upcasts it to FileSystemItem*.
    //  So add(FileSystemItem* item) accepts it without issues
    root->add(MyFiles);

    root->showDetails();

    delete f1;
    delete f2;
    delete MyFiles;
    delete root;

    cout<<"-------------------------------------\n";
    RestaurantMenuSystem();
    return 0;
}
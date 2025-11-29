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
    //Composition, storing Files + Folder
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

int main()
{
    FileSystem *f1 = new File("abc.txt");
    FileSystem *f2 = new File("README.md");
    
    Folder *MyFiles = new Folder("MyFiles");
    MyFiles->add(f1);
    MyFiles->add(f2);

    Folder *root = new Folder("Root");

    //since Folder inherits from FileSystemItem, the compiler automatically upcasts it to FileSystemItem*.
    // So add(FileSystemItem* item) accepts it without issues
    root->add(MyFiles); 

    root->showDetails();

    delete f1;
    delete f2;
    delete MyFiles;
    delete root;

    return 0;
}
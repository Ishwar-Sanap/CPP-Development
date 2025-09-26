#include <bits/stdc++.h>
using namespace std;

class Book
{
    string m_strTitle;

public:
    Book(string title) : m_strTitle(title) {}
    string getTitle() { return m_strTitle; }
};

class Iterator
{
public:
    virtual bool hasNext() = 0;
    virtual Book *next() = 0;
    virtual ~Iterator() = default;
};

class BooksIterator : public Iterator
{
    int indx;
    vector<Book *> m_vectBooksPtr;

public:
    BooksIterator(vector<Book *> &booksPtr) : m_vectBooksPtr(booksPtr), indx(0)
    {
    }

    bool hasNext() override
    {
        return indx < m_vectBooksPtr.size();
    }

    Book *next() override
    {
        return hasNext() ? m_vectBooksPtr[indx++] : nullptr;
    }
};
class BookCollection
{
    vector<Book *> m_vectBooksPtr;

public:
    void addBook(Book *ptr)
    {
        m_vectBooksPtr.push_back(ptr);
    }

    vector<Book *> &getBookCollection() { return m_vectBooksPtr; }
};
int main()
{
    BookCollection collection;
    Book *b1 = new Book("Clean Code");
    Book *b2 = new Book("Rich dad poor dad");
    Book *b3 = new Book("Atomic Habits");

    collection.addBook(b1);
    collection.addBook(b2);
    collection.addBook(b3);

    BooksIterator itrObj(collection.getBookCollection());

    while(itrObj.hasNext())
    {
        cout<<itrObj.next()->getTitle()<<endl;
    }

    delete b1;
    delete b2;
    delete b3;

    b1 = b2 = b3 = nullptr;

    return 0;
}
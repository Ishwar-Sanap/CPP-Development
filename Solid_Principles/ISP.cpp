#include <bits/stdc++.h>
using namespace std;

//Interface Segregation Principle (ISP)
	// - It states that a client should not be forced to depend on interfaces that it does not use. 
	// - In other words, a class should not have to implement methods that it does not need.


/*
This interface may not be suitable for all clients.
For example, a client that only needs to print plain text documents
may not want to implement the printPDF() and printHTML() methods.
*/
// Violates the LSP
class Printer
{
public:
    virtual void printPDF() = 0;
    virtual void printHTML() = 0;
    virtual void printPlainText() = 0;
};

// To adhere to the ISP, we could break down the Printer
// interface into smaller interfaces that are specific to each document format.

class Printable
{
public:
    virtual void print() = 0;
};

class PDFPrintable : public Printable
{
public:
    void print() override;
};

class HTMLPrintable : public Printable
{
public:
    void print() override;
};

class PlainTextPrintable : public Printable
{
public:
    void print() override;
};


//Client 
class PlainTextPrinter
{
public:
    void print(PlainTextPrintable &document)
    {
        document.print();
    }
};


int main()
{
    return 0;
}
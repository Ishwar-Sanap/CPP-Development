#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
Problem: Build a logging system where the application uses a Logger interface polymorphically. Different logger implementations send messages to different destinations, and the application doesn't know or care which one it's using.

Requirements:

Logger interface with log(level, message) and getDestination() methods.
ConsoleLogger: prints formatted log messages to the console.
FileLogger: simulates writing to a file (print with file path prefix).
DatabaseLogger: simulates inserting into a database (print with table name prefix).
Application class that takes a Logger in its constructor and uses it throughout.

Solution explation:
		
1) Object-Oriented Design
    • Good use of a Logger interface with polymorphic implementations.
    • Application depends on the abstraction, which is the right design.
    • Encapsulation is mostly clean: file/table details are stored inside the concrete loggers.
2) Design Patterns
    • You applied the Strategy pattern correctly: Application can work with any Logger implementation.
    • No factory is needed here because object creation is simple and handled in main.
3) SOLID Principles
    • DIP is well followed: Application depends on Logger, not concrete classes.
    • OCP is good: new logger types can be added without changing Application.
    • SRP is good: each logger handles one destination.
    • LSP is satisfied: all logger types can substitute for Logger.
    • ISP is fine because the interface is small and focused.
4) Correctness
    • The overall behavior is correct and the output matches the expected result.
    • One minor issue: ConsoleLogger::log() prints INFO Application starting... instead of [INFO] Application starting....
    • Similarly, FileLogger and DatabaseLogger omit the square brackets around the level.
    • Since the execution result matches, your environment likely tolerated formatting, but the implementation should match the required output exactly.
5) Code Quality
    • Constructor initialization lists are used well for FileLogger, DatabaseLogger, and Application.
    • The code is readable and structurally simple.
Formatting is consistent enough, though spacing around operators and arguments could be cleaner.

*/
class Logger
{
public:
    virtual ~Logger() {}
    virtual void log(const string &level, const string &message) = 0;
    virtual string getDestination() = 0;
};

class ConsoleLogger : public Logger
{
public:
    void log(const string &level, const string &message) override
    {

        cout << level << " " << message << endl;
    }

    string getDestination() override
    {

        return "Console";
    }
};

class FileLogger : public Logger
{
private:
    string filePath;

public:
    FileLogger(const string &filePath) : filePath(filePath)
    {
    }

    void log(const string &level, const string &message) override
    {

        cout << "Writing to " << filePath << ": " << level << " " << message << endl;
    }

    string getDestination() override
    {

        return "File: " + filePath;
    }
};

class DatabaseLogger : public Logger
{
private:
    string tableName;

public:
    DatabaseLogger(const string &tableName) : tableName(tableName)
    {
        }

    void log(const string &level, const string &message) override
    {

        cout << "INSERT INTO " << tableName << ": " << level << " " << message << endl;
    }

    string getDestination() override
    {

        return "Database: " + tableName;
    }
};

class Application
{
private:
    Logger *logger;

public:
    Application(Logger *logger) : logger(logger)
    {
    }

    void run()
    {
        logger->log("[INFO]", "Application starting...");
        logger->log("[INFO]", "Processing data...");
        logger->log("[INFO]", "Application shutting down.");
    }
};

int main()
{
    ConsoleLogger console;
    FileLogger file("/var/log/app.log");
    DatabaseLogger db("app_logs");

    vector<Logger *> loggers = {&console, &file, &db};

    for (auto *logger : loggers)
    {
        cout << "--- Using " << logger->getDestination() << " ---" << endl;
        Application app(logger);
        app.run();
        cout << endl;
    }

    return 0;
}
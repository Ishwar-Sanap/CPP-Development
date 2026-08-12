#include <bits/stdc++.h>
using namespace std;

enum class Symbol
{
    X,
    O,
    EMPTY
};

enum class GameStatus
{
    NOT_STARTED,
    IN_PROGRESS,
    WINNER_X,
    WINNER_O,
    DRAW
};

class Cell
{
private:
    Symbol symbol{Symbol::EMPTY};

public:
    void setSymbol(Symbol sm)
    {
        symbol = sm;
    }
    Symbol getSymbol() const { return symbol; }
    bool isEmpty() const { return symbol == Symbol::EMPTY; }
};

class WinnerFinder
{
private:
public:
    bool checkWinner(vector<vector<Cell>> &grid, int n, Symbol sm)
    {
        int leftDigSymbolsCnt = 0;
        int rightDigSymbolsCnt = 0;
        vector<int> vertSymbolsCnts(n, 0);

        for (int i = 0; i < n; i++)
        {
            int horSymbolsCnt = 0;
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j].getSymbol() == sm)
                {
                    vertSymbolsCnts[j]++;
                    horSymbolsCnt++;
                }

                if (i == j && grid[i][j].getSymbol() == sm)
                    leftDigSymbolsCnt++;

                if ((i + j) == n - 1 && grid[i][j].getSymbol() == sm)
                    rightDigSymbolsCnt++;
            }
            if (horSymbolsCnt == n)
                return true;
        }

        if (leftDigSymbolsCnt == n || rightDigSymbolsCnt == n)
            return true;

        for (int cnt : vertSymbolsCnts)
        {
            if (cnt == n)
                return true;
        }

        return false;
    }
};
class Board
{
    // N * N Cell
private:
    int size;
    int filledCells;
    vector<vector<Cell>> grid;
    WinnerFinder wf;

public:
    Board(int n) : size(n), filledCells(0)
    {
        grid.resize(n, vector<Cell>(n));
    }

    bool isValidPosition(int ri, int ci)
    {
        if (ri >= 0 && ci >= 0 && ri < size && ci < size)
            return true;

        return false;
    }

    void setCellValue(int ri, int ci, Symbol sm)
    {
        if (!isValidPosition(ri, ci))
            throw invalid_argument("Invalid Input");

        else if (!grid[ri][ci].isEmpty())
            throw invalid_argument("Can't update filled cell");

        grid[ri][ci].setSymbol(sm);
        filledCells++;
    }

    Symbol getCellValue(int ri, int ci)
    {
        if (!isValidPosition(ri, ci))
            throw invalid_argument("Invalid Input");

        return grid[ri][ci].getSymbol();
    }

    bool isFull()
    {
        return filledCells == size * size;
    }

    bool checkWinner(Symbol sm)
    {
        // definately not yet declared
        if (((filledCells + 1) / size) <= 1)
            return false;

        return wf.checkWinner(grid, size, sm);
    }
    void reset()
    {
        filledCells = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                grid[i][j].setSymbol(Symbol::EMPTY);
            }
        }
    }
    void printBoard()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                Symbol sm = grid[i][j].getSymbol();

                if (sm == Symbol::X)
                    cout << "X ";
                else if (sm == Symbol::O)
                    cout << "O ";
                else
                    cout << "- ";
            }
            cout << endl;
        }
    }
};

class Player
{
private:
    string name;
    Symbol sm;

public:
    Player(const string &name, Symbol sm) : name(name), sm(sm)
    {
    }

    const string &getPlayerName() const { return name; }
    Symbol getPlayerSymbol() const { return sm; }
};

class Game
{
private:
    Board board;
    vector<Player *> players;
    GameStatus status{GameStatus::NOT_STARTED};
    int turn;

    void changePlayerTurn()
    {
        turn = turn == 1 ? 0 : 1;
    }

    void printCurrPlayerDetails(const string &str)
    {
        char symbol = players[turn]->getPlayerSymbol() == Symbol::O ? 'O' : 'X';
        cout << str << " : " << players[turn]->getPlayerName() << " " << "[ Symbol : " << symbol << " ]" << endl;
    }

public:
    Game(Player &p1, Player &p2, int n) : board(n), turn(0)
    {
        players.push_back(&p1);
        players.push_back(&p2);
    }

    void displaySatus()
    {
        switch (status)
        {
        case GameStatus::NOT_STARTED:
            cout << "Game not yet started " << endl;
            break;

        case GameStatus::IN_PROGRESS:
            cout << "Game In Progress..." << endl;
            break;

        case GameStatus::DRAW:
            cout << "Game DRAW" << endl;
            break;

        case GameStatus::WINNER_O:
            cout << "WINNER_O" << endl;
            break;

        case GameStatus::WINNER_X:
            cout << "WINNER_X" << endl;
            break;

        default:
            cout << "Error! Invalid State" << endl;
        }
    }

    void displayBoard()
    {
        board.printBoard();
    }

    void start(int playerTurn)
    {
        if (playerTurn > 1)
            throw invalid_argument("Invalid Player Index use (0 or 1)");

        turn = playerTurn;
        status = GameStatus::IN_PROGRESS;

        while (1)
        {
            try
            {
                if (board.isFull())
                {
                    status = GameStatus::DRAW;
                    break;
                }

                int ri = 0, ci = 0;

                displayBoard();
                printCurrPlayerDetails("Playing");

                Symbol currPlyerSym = players[turn]->getPlayerSymbol();
                cout << "\nSelect cell : ";
                cin >> ri >> ci;

                if (!board.isValidPosition(ri, ci))
                    throw invalid_argument("Invalid cell position try again!!");

                board.setCellValue(ri, ci, currPlyerSym);

                if (board.checkWinner(currPlyerSym))
                {
                    printCurrPlayerDetails("Winner");
                    status = currPlyerSym == Symbol::X ? GameStatus::WINNER_X : GameStatus::WINNER_O;
                    break;
                }

                changePlayerTurn();
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        displaySatus();
        displayBoard();
    }
};
int main()
{
    Player p1("Alice", Symbol::O);
    Player p2("Bob", Symbol::X);

    Game g1(p1, p2, 5);

    g1.start(1);
    return 0;
}
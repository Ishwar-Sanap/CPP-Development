#include <bits/stdc++.h>
using namespace std;

enum class GameStatus
{
    NOT_STARTED,
    IN_PROGRESS,
    FINISHED
};

class BoardEntity
{
private:
    int start{}, end{};

public:
    BoardEntity(int start, int end) : start(start), end(end)
    {
    }

    virtual ~BoardEntity() = default;

    int getStart() const { return start; }
    int getEnd() const { return end; }
};

class Snake : public BoardEntity
{
public:
    Snake(int start, int end) : BoardEntity(start, end)
    {
        if (start <= end)
            throw invalid_argument("Snake head position must be greater than tail position");
    }
};

class Ladder : public BoardEntity
{
public:
    Ladder(int start, int end) : BoardEntity(start, end)
    {
        if (start >= end)
            throw invalid_argument("Ladder start position must be smaller than end position");
    }
};

class Player
{
private:
    string name;
    int position{1};

public:
    Player(const string &name) : name(name) {};
    const string &getName() const { return name; }
    void setPosition(int pos) { position = pos; }
    int getPosition() const { return position; }
    string getPlayerDetails()
    {
        return name + " " + " [ position : " + to_string(position) + " ]";
    }
};

class Dice
{
private:
    int minValue{}, maxValue;

    int getRandomNumber() const
    {
        this_thread::sleep_for(chrono::milliseconds(500));

        // 1. Obtain a random seed from the hardware
        std::random_device rd;

        // 2. Initialize the standard Mersenne Twister engine with the seed
        std::mt19937 gen(rd());

        // 3. Define a uniform integer distribution for your range
        std::uniform_int_distribution<int> distr(minValue, maxValue);

        // 4. Generate and print a random number
        int num = distr(gen);
        return num;
    }

public:
    Dice(int minVal, int maxVal) : minValue(minVal), maxValue(maxVal)
    {
    }

    int roll()
    {
        return getRandomNumber();
    }
};

class Board
{
private:
    int size{}; // N * N
    int endPosition{};
    vector<BoardEntity *> entities;
    unordered_map<int, int> mapSnakesAndLadders; // start to end mapping
public:
    Board(int n) : size(n)
    {
    }

    void configureBoard()
    {
        endPosition = size;

        // Add Snakes
        entities.push_back(new Snake(29, 9));
        entities.push_back(new Snake(38, 15));
        entities.push_back(new Snake(47, 5));
        entities.push_back(new Snake(53, 33));
        entities.push_back(new Snake(62, 37));
        entities.push_back(new Snake(86, 54));
        entities.push_back(new Snake(92, 70));
        entities.push_back(new Snake(97, 25));

        // Add Ladders
        entities.push_back(new Ladder(4, 22));
        entities.push_back(new Ladder(8, 34));
        entities.push_back(new Ladder(20, 77));
        entities.push_back(new Ladder(32, 68));
        entities.push_back(new Ladder(41, 79));
        entities.push_back(new Ladder(74, 88));
        entities.push_back(new Ladder(85, 95));

        for (BoardEntity *entity : entities)
        {
            mapSnakesAndLadders[entity->getStart()] = entity->getEnd();
        }
    }

    int getEndPosition() const { return endPosition; }
    const unordered_map<int, int> &getSnakesAndLadderMap() const { return mapSnakesAndLadders; }
    ~Board()
    {
        for (BoardEntity *entity : entities)
        {
            delete entity;
            entity = nullptr;
        }
    }
};

class Game
{
private:
    Board board;
    Dice dice;
    GameStatus status{GameStatus::NOT_STARTED};
    vector<Player *> players;
    int playerIndx{0};

    Game(int size, int minVal, int maxVal, const vector<Player *> &players, int startPlayerIndx) : board(size), dice(minVal, maxVal), players(move(players)), playerIndx(startPlayerIndx)
    {
        board.configureBoard();
    }

public:
    class Builder
    {
    private:
        int size{};
        int startPlayerIndx{-1};
        int minVal{};
        int maxVal{};
        vector<Player *> players;

        void validateInput()
        {
            if (size <= 0)
                throw invalid_argument("Board size must be positive");

            if (players.size() <= 1)
                throw logic_error("At least 2 players are required to play game");

            if (startPlayerIndx < 0 || startPlayerIndx >= players.size())
                throw invalid_argument("Invalid start player index");

            if (minVal >= maxVal)
                throw logic_error("Dice min value must be less than max value");
        }

    public:
        Builder &setBoardSize(int n)
        {
            size = n;
            return *this;
        }
        Builder &setStartPlayerIndx(int index)
        {
            startPlayerIndx = index;
            return *this;
        }
        Builder &setDiceMinValue(int val)
        {
            minVal = val;
            return *this;
        }
        Builder &setDiceMaxValue(int val)
        {
            maxVal = val;
            return *this;
        }
        Builder &addPlayer(Player *player)
        {
            if (!player)
                throw invalid_argument("Player can't be null");

            players.push_back(player);
            return *this;
        }

        Game *build()
        {
            // Before creating the game validate the inputs
            validateInput();

            return new Game(size, minVal, maxVal, players, startPlayerIndx);
        }
    };

    void start();
};

void Game::start()
{
    status = GameStatus::IN_PROGRESS;
    const unordered_map<int, int> &mp = board.getSnakesAndLadderMap();

    while (status == GameStatus::IN_PROGRESS)
    {
        cout << "******************************************" << endl;
        cout << "Playing : " << players[playerIndx]->getPlayerDetails() << endl;
        int steps = dice.roll();
        cout << "Moving " << steps << " steps" << endl;
        int currPos = players[playerIndx]->getPosition();

        int newPosition = currPos + steps;
        if (newPosition <= board.getEndPosition())
        {
            // On moved position check if ladder or snakes is exist or not
            if (mp.find(newPosition) != mp.end())
            {
                if (newPosition > mp.at(newPosition))
                {
                    cout << "Ooh No! snake have eaten you moving down to position : " << mp.at(newPosition) << endl;
                }
                else
                {
                    cout << "Wow! You got Ladder climbing to position : " << mp.at(newPosition) << endl;
                }

                players[playerIndx]->setPosition(mp.at(newPosition));
            }
            else
            {
                players[playerIndx]->setPosition(newPosition);
            }
        }

        if (players[playerIndx]->getPosition() == board.getEndPosition())
        {
            status = GameStatus::FINISHED;
            break;
        }

        // next player turn
        playerIndx = (playerIndx + 1) % players.size();
        cout << "******************************************" << endl;
    }

    cout << "*********** GAME FINISHED ***********" << endl;
    cout << "Winner!! : " << players[playerIndx]->getPlayerDetails() << endl;
    cout << "******************************************" << endl;
}

int main()
{
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Charli");

    Game *game1 = Game::Builder().setBoardSize(100).addPlayer(&p1).addPlayer(&p2).addPlayer(&p3).setStartPlayerIndx(1).setDiceMinValue(1).setDiceMaxValue(6).build();

    game1->start();

    delete game1;
    game1 = nullptr;

    return 0;
}
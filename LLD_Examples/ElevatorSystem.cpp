#include <bits/stdc++.h>
using namespace std;

enum class Direction
{
    UP,
    DOWN,
    IDLE
};

enum class ElevatorState
{
    MOVING,
    IDLE,
    DOOR_OPEN
};

class Elevator
{
private:
    int m_id;
    int m_currFloor;
    Direction m_eDirection;
    ElevatorState m_eElevatorState;
    set<int> m_setRequests;

public:
    Elevator(int id) : m_id(id), m_currFloor(0), m_eDirection(Direction::IDLE), m_eElevatorState(ElevatorState::IDLE)
    {
    }

    int getId() const { return m_id; }
    int getCurrFloor() const { return m_currFloor; }
    Direction getDirection() const { return m_eDirection; }
    bool isIdle() const { return m_eDirection == Direction::IDLE; }

    void addRequest(int floor)
    {
        m_setRequests.insert(floor);
    }

    void run()
    {
        if (m_setRequests.empty())
        {
            m_eDirection = Direction::IDLE;
            m_eElevatorState = ElevatorState::IDLE;
            return;
        }

        while (!m_setRequests.empty())
        {
            int target = *m_setRequests.begin();
            if (target > m_currFloor)
            {
                m_currFloor++;
                m_eDirection = Direction::UP;
                m_eElevatorState = ElevatorState::MOVING;
            }
            else if (target < m_currFloor)
            {
                m_currFloor--;
                m_eDirection = Direction::DOWN;
                m_eElevatorState = ElevatorState::MOVING;
            }
            else
            {
                cout << "Elevator " << m_id << " arrived at floor " << target << endl;
                m_eDirection = Direction::IDLE;
                m_eElevatorState = ElevatorState::DOOR_OPEN;
                m_setRequests.erase(target);
            }
        }
    }
};

// Aggregation: a Request is a simple data object used by controller/scheduler, but it does not own the elevator.
class Request
{
public:
    int m_sourceFloor;
    int m_destFloor;
    Direction m_eDirection;

    Request(int src, int dest) : m_sourceFloor(src), m_destFloor(dest)
    {
        m_eDirection = dest > src ? Direction::UP : Direction::DOWN;
    }
};

// Realization/Inheritance: this abstract strategy defines the scheduling contract for all elevator-assignment algorithms.
class ShedulerStrategy
{
public:
    virtual Elevator *assignElevator(vector<Elevator *> &elevators, int floor) = 0;
    virtual ~ShedulerStrategy() = default;
};

// Inheritance: NearestElevator is a concrete strategy that implements the scheduler contract.
class NearestElevator : public ShedulerStrategy
{
public:
    // from list of elevator assign the nearest elevator to requested floor
    Elevator *assignElevator(vector<Elevator *> &elevators, int floor)
    {
        int minDist = INT_MAX;
        Elevator *bestElevator = nullptr;
        for (auto &elevator : elevators)
        {
            int dist = abs(elevator->getCurrFloor() - floor);
            if (elevator->isIdle() && dist < minDist)
            {
                minDist = dist;
                bestElevator = elevator;
            }
        }

        return bestElevator;
    }
};

//Composition:   ElevatorController has a Composition relationship with Elevator because it owns the elevator objects and manages their lifecycle.
class ElevatorController
{
private:
    ShedulerStrategy *m_ptrShedulerStrategy;
    vector<Elevator *> m_vectPtrElevator;

public:
    ElevatorController(int elevatorsCnt)
    {
        m_ptrShedulerStrategy = new NearestElevator();

        for (int i = 1; i <= elevatorsCnt; i++)
        {
            m_vectPtrElevator.push_back(new Elevator(i));
        }
    }

    void requestElevator(int src, int dest)
    {
        Elevator *ele = m_ptrShedulerStrategy->assignElevator(m_vectPtrElevator, src);
        cout << "Elevator is assigned " << ele->getId() << endl;
        ele->addRequest(src);
        ele->addRequest(dest);
    }

    // simulate the elevators
    void simulate()
    {
        for (auto &elevator : m_vectPtrElevator)
        {
            elevator->run();
        }
    }

    ~ElevatorController()
    {
        delete m_ptrShedulerStrategy;
        m_ptrShedulerStrategy = nullptr;

        for (auto &elevator : m_vectPtrElevator)
        {
            delete elevator;
            elevator = nullptr;
        }
    }
};

// Composition: Building owns the elevator controller and controls its lifetime.
class Building
{
private:
    ElevatorController *m_ptrElevator{};

public:
    Building(int elevatorCnt)
    {
        m_ptrElevator = new ElevatorController(elevatorCnt);
    }

    ElevatorController *getElevatorController() const { return m_ptrElevator; }

    ~Building()
    {
        delete m_ptrElevator;
        m_ptrElevator = nullptr;
    }
};
int main()
{
    Building bobj(3);
    ElevatorController *ptr = bobj.getElevatorController();

    ptr->requestElevator(3, 5);
    ptr->simulate();

    ptr->requestElevator(1, 2);
    ptr->simulate();

    return 0;
}
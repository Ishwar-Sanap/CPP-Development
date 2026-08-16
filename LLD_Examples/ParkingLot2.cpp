#include <bits/stdc++.h>
using namespace std;
/*
Design Parking Lot

REQUIRMENTS :
-   Support different types of vehicles : (BIKE, CAR, TRUCK)
-   Parking space can have small, medium and large sizes and as per vehicle compatibility it should be parked
-   Multilevel/Multifloor should be there in parking lot
-   Parking level or parking spots are dynamic it should be created as per inputs
-   Parking spot must be allocated randomly based on availability
-   Entry and exit gates: right now considering 1 entry gate and 1 exit gate but design in such way that it can be Increased in future
-   Ticket should generated when vehicle is parked
-   When wants to exit shows the ticket at exit gate and collect the charges
-   Charges collection is based on how much time vehicle is parked / another strategy can also be flat rate system

*/
enum class VehicleType
{
    BIKE,
    CAR,
    TRUCK
};

enum class SpotSize
{
    SMALL,
    MEDIUM,
    LARGE
};

class Vehicle
{
protected:
    string ownerName;
    string number;
    VehicleType type;

    Vehicle(const string &owner, const string &number, VehicleType type) : ownerName(owner), number(number), type(type)
    {
    }

public:
    virtual const string &getVehicleNumber() const { return number; }
    virtual const string &getOwnerName() const { return ownerName; }
    virtual VehicleType getVehicleType() const { return type; }
    virtual ~Vehicle() = default;
};

class Car : public Vehicle
{
public:
    Car(const string &owner, const string &number, VehicleType type) : Vehicle(owner, number, type)
    {
    }
};
class Bike : public Vehicle
{
public:
    Bike(const string &owner, const string &number, VehicleType type) : Vehicle(owner, number, type)
    {
    }
};
class Truck : public Vehicle
{
public:
    Truck(const string &owner, const string &number, VehicleType type) : Vehicle(owner, number, type)
    {
    }
};

class ParkingSpot
{
private:
    static int spotIdCounter;
    int id{};
    SpotSize size;
    Vehicle *vehicle{nullptr}; // association
    int level{};
    bool isAvailable{true};

public:
    ParkingSpot(SpotSize size, int level) : size(size), level(level)
    {
        spotIdCounter++;
        id = spotIdCounter;
    }

    void park(Vehicle *ptr)
    {
        if (!ptr)
            throw invalid_argument("Invalid Vehicle");

        if (!isAvailable)
            throw logic_error("Right now this spot is unavailable");

        VehicleType vtype = ptr->getVehicleType();

        // Bike can be parked in any parking spot size
        // Car can be parked in medium  and Large size only
        // Truck can only be parked in Large size
        if (vtype == VehicleType::CAR && size == SpotSize::SMALL)
            throw logic_error("Parking spot is not compatible to CAR");

        if (vtype == VehicleType::TRUCK && (size == SpotSize::SMALL || size == SpotSize::MEDIUM))
            throw logic_error("Parking spot is not compatible to TRUCK");

        vehicle = ptr;
        isAvailable = false;
    }

    bool canFitVehicle(Vehicle *ptr)
    {
        if (!ptr || !isAvailable)
            return false;

        VehicleType vtype = ptr->getVehicleType();

        if (vtype == VehicleType::CAR && size == SpotSize::SMALL)
            return false;

        if (vtype == VehicleType::TRUCK && (size == SpotSize::SMALL || size == SpotSize::MEDIUM))
            return false;

        return true;
    }
    void unPark()
    {
        vehicle = nullptr;
        isAvailable = true;
    }

    int getSpotId() const { return id; }
    SpotSize getSpotSize() const { return size; }
    Vehicle *getParkedVehile() const { return vehicle; }
    bool isSpotAvailable() const { return isAvailable; }
    int getSpotLevel() const { return level; }
};
int ParkingSpot::spotIdCounter = 0;

class Ticket
{
private:
    static int idCounter;
    int id;
    ParkingSpot *spot;
    std::chrono::time_point<std::chrono::steady_clock> parkTime;

public:
    Ticket(ParkingSpot *ps) : spot(ps)
    {
        idCounter++;
        id = idCounter;
        parkTime = std::chrono::steady_clock::now();
    }
    int getTicketId() const { return id; }
    auto getParkTime() const { return parkTime; }
    ParkingSpot *getParkingSpot() const { return spot; }
    string showDetails()
    {
        string str = "Vehicle Number : " + spot->getParkedVehile()->getVehicleNumber() +
                     "\n" + "------------------------------" + "\n" +
                     "Ticket Id : " + to_string(id) + "\n" +
                     "Parking SpotId : " + to_string(spot->getSpotId()) + "\n" +
                     "Parking Floor : " + to_string(spot->getSpotLevel()) + "\n";

        return str;
    }
};
int Ticket::idCounter = 0;

class PricingStrategy
{
public:
    virtual double calculatePrice(Ticket *ptr) = 0;
    virtual ~PricingStrategy() = default;
};

// Strategy 1 : Flat rate System
class FlatRatePricing : public PricingStrategy
{
public:
    double calculatePrice(Ticket *ticket) override
    {
        if (!ticket || !ticket->getParkingSpot())
            throw invalid_argument("Invalid Ticket");

        VehicleType type = ticket->getParkingSpot()->getParkedVehile()->getVehicleType();

        if (type == VehicleType::BIKE)
            return 20.0;
        else if (type == VehicleType::CAR)
            return 50.0;
        else
            return 100.0;
    }
};

// Strategy 2 : Time and vehicle based pricing
class TimeBasedPricing : public PricingStrategy
{
public:
    double calculatePrice(Ticket *ticket) override
    {
        if (!ticket || !ticket->getParkingSpot())
            throw invalid_argument("Invalid Ticket");

        auto parkTime = ticket->getParkTime();
        auto currTime = std::chrono::steady_clock::now();

        auto durn = std::chrono::duration_cast<std::chrono::seconds>(currTime - parkTime);

        double mins = durn.count();
        cout << "Vehicle was parked for " << mins << " mins." << endl;

        VehicleType type = ticket->getParkingSpot()->getParkedVehile()->getVehicleType();

        if (type == VehicleType::BIKE)
            return mins * 1;
        else if (type == VehicleType::CAR)
            return mins * 2;
        else
            return mins * 3;
    }
};

class ParkingLot
{
private:
    int levels{};
    int maxSlotsPerLevel{10};
    unordered_map<int, vector<ParkingSpot *>> mapParkingSpots;
    PricingStrategy *pricingStrategy;

public:
    ParkingLot(int levelsCnt, PricingStrategy *pricingMethod) : levels(levelsCnt), pricingStrategy(pricingMethod)
    {
    }

    void setPricingStrtegy(PricingStrategy *pricingMethod)
    {
        pricingStrategy = pricingMethod;
    }

    void createSpotsForLevel(int level, int smallSize, int mediumSize, int largeSize)
    {
        if (level <= 0 || level > levels)
            throw invalid_argument("Invalid Level");

        if (mapParkingSpots.find(level) != mapParkingSpots.end())
            throw invalid_argument("Level is already filled");

        if (smallSize < 0 || mediumSize < 0 || largeSize < 0)
            throw invalid_argument("Number of spots can't be negative");

        if ((smallSize + mediumSize + largeSize) > maxSlotsPerLevel)
            throw invalid_argument("Total number of spots can't be greater than 10 per level");

        vector<ParkingSpot *> spot;

        while (smallSize--)
            spot.push_back(new ParkingSpot(SpotSize::SMALL, level));

        while (mediumSize--)
            spot.push_back(new ParkingSpot(SpotSize::MEDIUM, level));

        while (largeSize--)
            spot.push_back(new ParkingSpot(SpotSize::LARGE, level));

        mapParkingSpots[level] = move(spot);
    }

    Ticket *parkVehicle(Vehicle *vehicle)
    {
        ParkingSpot *spot = nullptr;
        // Find the compatiable empty spot to park
        for (auto &it : mapParkingSpots)
        {
            for (auto parkingSpot : it.second)
            {
                if (parkingSpot->isSpotAvailable() && parkingSpot->canFitVehicle(vehicle))
                {
                    parkingSpot->park(vehicle);
                    spot = parkingSpot;
                    break;
                }
            }

            if (spot)
                break;
        }

        if (spot == nullptr)
            throw logic_error("No parking spot is available right now");

        return new Ticket(spot);
    }

    void unParkVehicle(Ticket *ticket, Vehicle *vehicle)
    {
        if (!ticket)
            throw invalid_argument("Invalid Ticket");
        if (!vehicle)
            throw invalid_argument("Invalid Vehicle");

        Vehicle *parkedVehicle = ticket->getParkingSpot()->getParkedVehile();

        // Checking vehicle is same or not
        if (parkedVehicle->getVehicleNumber() == vehicle->getVehicleNumber())
        {
            double price = pricingStrategy->calculatePrice(ticket);
            ticket->getParkingSpot()->unPark();
            cout << "You have to pay : " << price << " Rs.\n"
                 << endl;
        }
        else
        {
            throw logic_error("Ticket and Vechile doesn't match");
        }
    }

    ~ParkingLot()
    {
        for (auto &it : mapParkingSpots)
        {
            auto &spots = it.second;
            for (int i = 0; i < spots.size(); i++)
            {
                delete spots[i];
                spots[i] = nullptr;
            }
        }
    }
};

class ParkingLotManager
{
private:
    ParkingLot *parkingLot;
    PricingStrategy *priceStrategy;
    unordered_map<int, Ticket *> mapTickets;

public:
    ParkingLotManager()
    {
        // priceStrategy = new TimeBasedPricing();
        priceStrategy = new FlatRatePricing();
        parkingLot = new ParkingLot(3, priceStrategy);

        parkingLot->createSpotsForLevel(1, 2, 3, 5);
        parkingLot->createSpotsForLevel(2, 4, 4, 0);
        parkingLot->createSpotsForLevel(3, 3, 2, 0);
    }

    int parkVehicleAndGetTicket(Vehicle *vehicle)
    {
        Ticket *ticket = parkingLot->parkVehicle(vehicle);
        mapTickets[ticket->getTicketId()] = ticket;
        return ticket->getTicketId();
    }

    void viewTicket(int tktid)
    {
        if (mapTickets.find(tktid) == mapTickets.end())
            throw invalid_argument("Ticket not found!!");

        cout << mapTickets[tktid]->showDetails() << endl;
    }
    void showTicketAndExit(int tktid, Vehicle *vehicle)
    {
        if (mapTickets.find(tktid) == mapTickets.end())
            throw invalid_argument("Ticket not found!!");

        parkingLot->unParkVehicle(mapTickets[tktid], vehicle);
        mapTickets.erase(tktid);
    }

    ~ParkingLotManager()
    {
        delete parkingLot;
        parkingLot = nullptr;

        delete priceStrategy;
        priceStrategy = nullptr;

        for (auto &it : mapTickets)
        {
            delete it.second;
            it.second = nullptr;
        }
    }
};

class VehileFactory
{
public:
    static Vehicle *getVehicle(const string &owner, const string &number, VehicleType type)
    {
        if (type == VehicleType::BIKE)
            return new Bike(owner, number, type);
        else if (type == VehicleType::CAR)
            return new Car(owner, number, type);
        else if (type == VehicleType::TRUCK)
            return new Truck(owner, number, type);
        else
            return nullptr;
    }
};
int main()
{
    Vehicle *v1Bike;
    Vehicle *v2Bike;
    Vehicle *v3Car;
    Vehicle *v4Truck;

    try
    {
        v1Bike = VehileFactory::getVehicle("Alice", "MH16AN0001", VehicleType::BIKE);
        v2Bike = VehileFactory::getVehicle("Bob", "MH16AN0002", VehicleType::BIKE);
        v3Car = VehileFactory::getVehicle("Charls", "MH16AN0003", VehicleType::CAR);
        v4Truck = VehileFactory::getVehicle("Dency", "MH16AN0004", VehicleType::TRUCK);

        ParkingLotManager pm;
        int tkt1 = pm.parkVehicleAndGetTicket(v1Bike);
        pm.viewTicket(tkt1);
        pm.showTicketAndExit(tkt1, v1Bike);

        int t3 = pm.parkVehicleAndGetTicket(v3Car);
        // this_thread::sleep_for(chrono::minutes(2)); simulate vehicle was parked for 2 mins

        pm.viewTicket(t3);
        pm.showTicketAndExit(t3, v3Car);

        int t4 = pm.parkVehicleAndGetTicket(v4Truck);
        pm.viewTicket(t4);
        pm.showTicketAndExit(t4, v4Truck);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    delete v1Bike;
    delete v2Bike;
    delete v3Car;

    return 0;
}
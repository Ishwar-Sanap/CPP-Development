#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// VehicleType
enum class VehicleType
{
    BIKE,
    CAR,
    TRUCK
};

// Entity Vehicle
// RELATIONSHIP: Base class for all vehicle types (IS-A inheritance with Car, Bike, Truck)
class Vehicle
{
public:
    Vehicle(const string &number, VehicleType vt) : m_strNumber(number), m_eVehicleType(vt) {}
    virtual ~Vehicle() = default;

    VehicleType getType() { return m_eVehicleType; }
    const string &getNumber() { return m_strNumber; }

protected:
    string m_strNumber;
    VehicleType m_eVehicleType;
};

// RELATIONSHIP: Concrete vehicle types - Inheritance (IS-A) from Vehicle base class
class Car : public Vehicle
{
public:
    Car(const string &number) : Vehicle(number, VehicleType::CAR) {}
};
class Bike : public Vehicle
{
public:
    Bike(const string &number) : Vehicle(number, VehicleType::BIKE) {}
};
class Truck : public Vehicle
{
public:
    Truck(const string &number) : Vehicle(number, VehicleType::TRUCK) {}
};

enum class SpotType
{
    BIKE,
    COMPACT,
    LARGE
};

// Parking Spot
// RELATIONSHIP: Holds a non-owning reference to a Vehicle (HAS-A association)
// Why: ParkingSpot is a parking location that temporarily references a vehicle but doesn't manage its lifecycle
class ParkingSpot
{
public:
    ParkingSpot(int id, SpotType st) : m_iId(id), m_eSpotType(st) {}

    void park(Vehicle *ptrVehicle)
    {
        m_ptrVehicle = ptrVehicle;
        m_bIsOccupied = true;
    }
    void unpark()
    {
        m_ptrVehicle = nullptr;
        m_bIsOccupied = false;
    }

    bool canFitVehicle(VehicleType vt)
    {
        if (vt == VehicleType::BIKE)
        {
            return true;
        }
        else if (vt == VehicleType::CAR)
        {
            return m_eSpotType != SpotType::BIKE;
        }
        else if (vt == VehicleType::TRUCK)
        {
            return m_eSpotType == SpotType::LARGE;
        }

        return false;
    }

    int getId() const { return m_iId; }
    SpotType getType() const { return m_eSpotType; }
    bool isOccupied() { return m_bIsOccupied; }

private:
    int m_iId;
    bool m_bIsOccupied{false};
    SpotType m_eSpotType;
    Vehicle *m_ptrVehicle{nullptr};
};

// RELATIONSHIP: Owns a collection of ParkingSpots (Composition - HAS-A)
// Why: A level is responsible for creating and managing its parking spots. Spots are destroyed when the level is destroyed.
class ParkingLevel
{
public:
    ParkingLevel(int level, int numCompact, int numLarge, int numBike) : m_level(level)
    {
        int id = 0;
        for (int i = 0; i < numCompact; i++)
        {
            m_vectPtrParkingSpots.push_back(new ParkingSpot(id, SpotType::COMPACT));
            id++;
        }
        for (int i = 0; i < numLarge; i++)
        {
            m_vectPtrParkingSpots.push_back(new ParkingSpot(id, SpotType::LARGE));
            id++;
        }
        for (int i = 0; i < numBike; i++)
        {
            m_vectPtrParkingSpots.push_back(new ParkingSpot(id, SpotType::BIKE));
            id++;
        }
    }

    ParkingSpot *findAvailableSpot(VehicleType vType)
    {
        for (auto ptr : m_vectPtrParkingSpots)
        {
            if (!ptr->isOccupied() && ptr->canFitVehicle(vType))
                return ptr;
        }

        return nullptr;
    }

    ParkingSpot *getSpotById(int id)
    {
        for (auto ptr : m_vectPtrParkingSpots)
        {
            if (ptr->getId() == id)
                return ptr;
        }

        return nullptr;
    }

    ~ParkingLevel()
    {
        // Delete all the parking spots
        for (ParkingSpot *ptr : m_vectPtrParkingSpots)
        {
            delete ptr;
            ptr = nullptr;
        }
    }

private:
    int m_level;
    vector<ParkingSpot *> m_vectPtrParkingSpots;
};

struct Ticket
{
    int m_iId;
    string m_strVehicleNumber;
    VehicleType m_enumVehicleType;
    int m_iSpotId;
};

// RELATIONSHIP: Base class for pricing strategies (IS-A inheritance with RegularPricing, SpecialEventPricing)
// Why: Strategy pattern allows switching pricing algorithms at runtime
class PricingStrategy
{
public:
    virtual ~PricingStrategy() = default;
    virtual double calculateFee(const Ticket &ticket) = 0;
};

// RELATIONSHIP: Concrete strategy for regular pricing - Inheritance (IS-A) from PricingStrategy
class RegularPricing : public PricingStrategy
{
public:
    double calculateFee(const Ticket &ticket)
    {
        VehicleType vt = ticket.m_enumVehicleType;

        if (vt == VehicleType::BIKE)
            return 20;
        else if (vt == VehicleType::CAR)
            return 50;
        else if (vt == VehicleType::TRUCK)
            return 100;

        return 0;
    }
};

// RELATIONSHIP: Concrete strategy for special event pricing - Inheritance (IS-A) from PricingStrategy
class SpecialEventPricing : public PricingStrategy
{
public:
    double calculateFee(const Ticket &ticket)
    {
        VehicleType vt = ticket.m_enumVehicleType;

        if (vt == VehicleType::BIKE)
            return 40;
        else if (vt == VehicleType::CAR)
            return 80;
        else if (vt == VehicleType::TRUCK)
            return 130;

        return 0;
    }
};

// Factory Class to get the vehicle object
// RELATIONSHIP: Creates instances of Vehicle subclasses (Factory pattern - Association)
// Why: Encapsulates object creation logic, allowing flexible vehicle instantiation
class VehicleFactory
{
public:
    static Vehicle *getVehicleObject(const string &number, VehicleType vType)
    {
        if (vType == VehicleType::BIKE)
            return new Bike(number);

        else if (vType == VehicleType::CAR)
            return new Car(number);

        else if (vType == VehicleType::TRUCK)
            return new Truck(number);

        return nullptr;
    }
};

// RELATIONSHIP: Singleton that owns ParkingLevels (Composition), PricingStrategy (Composition), and Tickets (Composition)
// Why: ParkingLot is the main controller managing all parking operations. It owns and manages lifecycle of levels, pricing, and tickets.
class ParkingLot
{
public:
    static ParkingLot &getInstance()
    {
        static ParkingLot obj;
        return obj;
    }

    // delete copy constructor
    ParkingLot(const ParkingLot &obj) = delete;

    // delete copy assignment
    ParkingLot &operator=(const ParkingLot &obj) = delete;

    void destroyParkingLot()
    {
        delete m_ptrPricingStrategy;
        m_ptrPricingStrategy = nullptr;

        for (ParkingLevel *level : m_vectPtrParkingLevel)
        {
            delete level;
            level = nullptr;
        }

        for (auto it : m_mapTicketId)
        {
            delete it.second;
            it.second = nullptr;
        }

        m_mapTicketId.clear();
    }

    Ticket *parkVehicle(Vehicle *ptrVehicle)
    {
        Ticket *tobj = nullptr;
        const string &number = ptrVehicle->getNumber();
        VehicleType vType = ptrVehicle->getType();

        // Find the right parking spot for vehicle and return the ticket to owner
        ParkingSpot *ptrParkingSpot = nullptr;
        for (auto ptrLevel : m_vectPtrParkingLevel)
        {
            ptrParkingSpot = ptrLevel->findAvailableSpot(vType);
            if (ptrParkingSpot)
            {
                break;
            }
        }

        if (ptrParkingSpot)
        {
            ptrParkingSpot->park(ptrVehicle);
            tobj = new Ticket();

            tobj->m_strVehicleNumber = number;
            tobj->m_iSpotId = ptrParkingSpot->getId();
            tobj->m_iId = m_nextTickedID;
            tobj->m_enumVehicleType = vType;

            m_mapTicketId[tobj->m_iId] = tobj;
            m_nextTickedID++;

            return tobj;
        }

        return nullptr;
    }

    double unParkVehicle(int ticketId)
    {
        Ticket *ptrTicket = nullptr;

        if (m_mapTicketId.find(ticketId) != m_mapTicketId.end())
            ptrTicket = m_mapTicketId[ticketId];

        if (!ptrTicket)
        {
            cout << "Ticket is not valid" << endl;
            return 0.0;
        }

        double fee = m_ptrPricingStrategy->calculateFee((*ptrTicket));

        for (auto ptrLevel : m_vectPtrParkingLevel)
        {
            ParkingSpot *ptrParkingSpot = ptrLevel->getSpotById(ptrTicket->m_iSpotId);
            if (ptrParkingSpot)
            {
                ptrParkingSpot->unpark();
                break;
            }
        }

        m_mapTicketId.erase(ptrTicket->m_iId);

        delete ptrTicket;
        ptrTicket = nullptr;

        return fee;
    }

private:
    ParkingLot()
    {
        // m_ptrPricingStrategy = new RegularPricing();
        m_ptrPricingStrategy = new SpecialEventPricing();
        m_vectPtrParkingLevel.push_back(new ParkingLevel(1, 10, 5, 5));
    }

    vector<ParkingLevel *> m_vectPtrParkingLevel;
    unordered_map<int, Ticket *> m_mapTicketId;
    PricingStrategy *m_ptrPricingStrategy;
    int m_nextTickedID = 1;
};

int main()
{
    ParkingLot &plobj = ParkingLot::getInstance();
    Vehicle *vehicle1 = VehicleFactory::getVehicleObject("MH23BQ0001", VehicleType::BIKE);
    Vehicle *vehicle2 = VehicleFactory::getVehicleObject("MH23BH0002", VehicleType::CAR);
    Vehicle *vehicle3 = VehicleFactory::getVehicleObject("MH12BH0003", VehicleType::TRUCK);

    Ticket *ticketPtr1 = plobj.parkVehicle(vehicle1);
    cout << "Paid : " << plobj.unParkVehicle(ticketPtr1->m_iId) << endl;
    delete vehicle1;  // Clean up vehicle memory after unparking

    Ticket *ticketPtr2 = plobj.parkVehicle(vehicle2);
    cout << "Paid : " << plobj.unParkVehicle(ticketPtr2->m_iId) << endl;
    delete vehicle2;  // Clean up vehicle memory after unparking

    Ticket *ticketPtr3 = plobj.parkVehicle(vehicle3);
    cout << "Paid : " << plobj.unParkVehicle(ticketPtr3->m_iId) << endl;
    delete vehicle3;  // Clean up vehicle memory after unparking

    plobj.destroyParkingLot();
    return 0;
}
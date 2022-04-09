#include <string> 
#include <vector> 
#include <fstream> 
#include <iostream>


class Vehicle;
class Car;
class Truck;
class ISimOutput;
class ISimInput;
class GUI;
class MetricGUI;
class ImperialGUI;
class Constants;
class Conversions; 
class Map;
class Road;
class CharMatrix;
class IPrintDriver;
class ConsolePrint;
class ISaveDriver; 
class ILoadDriver;
class JsonMapLoad;
class JsonMapSave;

// Shared.h
enum Heading { 
    North, East, South, West 
}; // clockwise 0-3

class Container{ // instead of Object
public:
	virtual ~Container()=default;
};

class Vehicle  {
private:
    double currentSpeed=0.0;
    double desiredSpeed;
protected: 
    virtual void Accelerate(int secondsDelta)=0; // abstract
    virtual void Decelerate(int secondsDelta)=0; // abstract
public: 
    // virtual ~Vehicle();
    double GetCurrentSpeed();
    void SetCurrentSpeed(double speed);
    void SetDesiredSpeed(double mph);
    void UpdateSpeed(int seconds);
};

class Car : public Vehicle {
protected:
    void Accelerate(int secondsDelta) override;
    void Decelerate(int secondsDelta) override;
};

class Truck : public Vehicle {
private:
    int loadWeight; // in tons
protected:
    void Accelerate(int secondsDelta) override;
    void Decelerate(int secondsDelta) override;
public: 
    Truck(int weight);
};

class ISimOutput  {
public:
    virtual double GetSpeed(Vehicle &v)=0;
};

class ISimInput {
public:
    virtual void SetSpeedLimit(Vehicle &v, double speed)=0;
};

class GUI : public ISimInput, public ISimOutput {
public:
    virtual Road CreateRoad(std::string, double x, double y, double z, Heading direction)=0; 
    virtual double GetSpeed(Vehicle &v)=0;
    virtual void SetSpeedLimit(Vehicle &v, double speed)=0;
};

class ImperialGUI: public GUI {
public:
    Road CreateRoad(std::string, double x, double y, double z, Heading direction) override;
    double GetSpeed(Vehicle &v) override;
    void SetSpeedLimit(Vehicle &v, double speed) override;
};

class MetricGUI: public GUI {
public:
    Road CreateRoad(std::string, double x, double y, double z, Heading direction) override;
    double GetSpeed(Vehicle &v) override;
    void SetSpeedLimit(Vehicle &v, double speed) override;
};

// Constants.h
class Constants {
public:
        static const double AccRate;
        static const double AccRateEmpty;     // Acceleration rate for light trucks in m/s
        static const double AccRateFull;      // Acceleration rate for heavy trucks in m/s
        static const double DecRate;          // Braking rate for cars in m/s
        static const double DecRateEmpty;     // Braking rate for light trucks in m/s
        static const double DecRateFull;      // Braking rate for light trucks in m/s
        static const double MpsToMph;
        static const double MpsToKph;
        static const double MetersToMiles;
        static const double MetersToKm;
        static const int CharMapSize; // hw6
        static const double WorldSize;
};

// Conversions.h
class Conversions // static class
{
public:
    static int WCpointToCCpoint(double val);
    static int WClengthToCClength(double val);
};

// Map.h 
class Map
{
private:
    std::vector<Road> roads;

public:
    Map();
    void AddRoad(Road road);
    void Print(IPrintDriver* pd, Container* o); 
    void Save(ISaveDriver *sd, std::ostream& stream); // Hm7 
    void Load(ILoadDriver *ld, std::istream& stream); 
    std::vector<Road> GetRoads(); // For parser 
};

// Road.h
class Road
{
private:
    std::string name;
    double length;
    double xlocation;
    double ylocation;
    Heading heading;
    
public: 
    int NumOfRoads;
    Road(std::string streetName, double locX, double locY, double len, Heading hdg);
    double GetLength();
    double GetXLocation();
    double GetYLocation();
    Heading GetHeading(); 
    std::string GetRoadName(); 
    void Print(IPrintDriver* print, Container* o); 
    void Save(ISaveDriver *sd, std::ostream& stream); // Hm7
    void Load(ILoadDriver *ld, std::istream& stream); // Hm7 
    Road(); // default constructor for Parser 
    void InitRoad(std::string streetName, double locX, double locY, double len, Heading hdg);
};

// SUI.h 
class CharMatrix : public Container
{ 
public:
    std::vector<std::vector<char>> map;
    CharMatrix();
};

class IPrintDriver : public Container { // interface
public:
    virtual void PrintRoad(Road* road, Container* o)=0; // Object = Container
    virtual void PrintCar(Car* car, Container* o)=0;
};

class ConsolePrint : public IPrintDriver {
public:
    void PrintRoad(Road* road, Container* o); 
    void PrintCar(Car* car, Container* o);
};

// Homework #7 
// For Saving a Map in unspecified encoding to a file
class ISaveDriver {
public: // added std::
	virtual void SaveMap(Map *map, std::ostream& stream) = 0;
	virtual void SaveRoad(Road *road, std::ostream& stream) = 0;
};
class JsonMapSave : public ISaveDriver {
public:
	void SaveMap(Map *map, std::ostream& stream);
	void SaveRoad(Road *road, std::ostream& stream);
};
// For Loading a Map in unspecified encoding from a file
class ILoadDriver {
public:
	virtual void LoadMap(Map *map, std::istream& stream) = 0;
	virtual void LoadRoad(Road *road, std::istream& stream) = 0;
};
class JsonMapLoad : public ILoadDriver {
public:
	void LoadMap(Map *map, std::istream& stream);
	void LoadRoad(Road *road, std::istream& stream);
	bool GetString(std::string * str, std::istream& stream);
};


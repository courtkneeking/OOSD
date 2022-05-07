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


class RoadItem;
class StaticRoadItem;
class StopSign;
class SpeedLimit;
class RoadItemsElement;
class Simulation;
class TrafficLight; 
class DynamicRoadItem;

// Shared.h
enum Heading { 
    North, South, East, West 
}; // clockwise 0-3
class Container{ // instead of Object
public:
	virtual ~Container()=default;
};

// Vehicle.h 
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
class Conversions { // static class 
public:
    static int WCpointToCCpoint(double val);
    static int WClengthToCClength(double val);
};

// Map.h 
class Map {
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
class Road {
private:
    std::string name;
    double length;
    double xlocation;
    double ylocation;
    Heading heading;
    
public: 
    int NumOfRoads;
    Road(); // default constructor for Parser 
    Road(std::string streetName, double locX, double locY, double len, Heading hdg);
    void InitRoad(std::string streetName, double locX, double locY, double len, Heading hdg);
    double GetLength();
    double GetXLocation();
    double GetYLocation();
    Heading GetHeading(); 
    std::string GetRoadName(); 
    void Print(IPrintDriver* print, Container* o); 
    void Save(ISaveDriver *sd, std::ostream& stream); // Hm7
    void Load(ILoadDriver *ld, std::istream& stream); // Hm7 
    // week 12 vv
    void AddRoadItem(RoadItem *ri); 
};


// SUI.h 
// these three are abstract classes so no implementation in .cpp files 
class ISimOutput  {
public:
    virtual double GetSpeed(Vehicle &v)=0;
};
class ISimInput {
public:
    virtual void SetSpeedLimit(Vehicle &v, double speed)=0;
    virtual SpeedLimit CreateSpeedLimit(double speed, double location) = 0;
    virtual StopSign CreateStopSign(double location) = 0;
};
class GUI : public ISimInput, public ISimOutput {
public:
    virtual Road CreateRoad(std::string, double x, double y, double z, Heading direction)=0; 
    virtual double GetSpeed(Vehicle &v)=0;
    virtual void SetSpeedLimit(Vehicle &v, double speed)=0;
    virtual SpeedLimit CreateSpeedLimit(double speed, double location) = 0;
    virtual StopSign CreateStopSign(double location) = 0;
};

class CharMatrix : public Container { 
public:
    std::vector<std::vector<char> > map;
    CharMatrix();
};
class ImperialGUI: public GUI {
public:
    Road CreateRoad(std::string, double x, double y, double z, Heading direction) override;
    double GetSpeed(Vehicle &v) override;
    void SetSpeedLimit(Vehicle &v, double speed) override;
    virtual SpeedLimit CreateSpeedLimit(double speed, double location) override;
    virtual StopSign CreateStopSign(double location) override;
};

class MetricGUI: public GUI {
public:
    Road CreateRoad(std::string, double x, double y, double z, Heading direction) override;
    double GetSpeed(Vehicle &v) override;
    void SetSpeedLimit(Vehicle &v, double speed) override;
    virtual SpeedLimit CreateSpeedLimit(double speed, double location) override;
    virtual StopSign CreateStopSign(double location) override;
};

// abstract classes IPrintDriver, no implementation in cpp file 
class IPrintDriver : public Container { 
public:
    virtual void PrintRoad(Road* road, Container* o)=0; 
    virtual void PrintCar(Car* car, Container* o)=0;
};
class ISaveDriver {
public: 
	virtual void SaveMap(Map *map, std::ostream& stream) = 0;
	virtual void SaveRoad(Road *road, std::ostream& stream) = 0;
    // week 12 
    virtual void SaveStopSign(StopSign *roadItem, std::ostream& stream) = 0;
    virtual void SaveSpeedLimit(SpeedLimit *roadItem, std::ostream& stream) = 0;
};
class ILoadDriver {
public:
	virtual void LoadMap(Map *map, std::istream& stream) = 0;
	virtual void LoadRoad(Road *road, std::istream& stream) = 0;
    // week 12 
    virtual void LoadStopSign(StopSign *roadItem, std::ostream& stream) = 0;
    virtual void LoadSpeedLimit(SpeedLimit *roadItem, std::ostream& stream) = 0;
};

class ConsolePrint : public IPrintDriver {
public:
    void PrintRoad(Road* road, Container* o); 
    void PrintCar(Car* car, Container* o);
};

class JsonMapLoad : public ILoadDriver {
public:
	void LoadMap(Map *map, std::istream& stream);
	void LoadRoad(Road *road, std::istream& stream);
	bool GetString(std::string * str, std::istream& stream);
    // week 12 
    void LoadStopSign(StopSign *roadItem, std::ostream& stream) override;
    void LoadSpeedLimit(SpeedLimit *roadItem, std::ostream& stream) override;
};

class JsonMapSave : public ISaveDriver {
public:
	void SaveMap(Map *map, std::ostream& stream);
	void SaveRoad(Road *road, std::ostream& stream);
    // week 12 
    void SaveStopSign(StopSign *roadItem, std::ostream& stream) override;
    void SaveSpeedLimit(SpeedLimit *roadItem, std::ostream& stream) override;
};

// week 12 start 
// roadItem.h 
class RoadItem {
private: 
    Road currentRoad;
protected:
   double mileMarker = 0.0;
//    RoadItem previousItem;
//    RoadItem nextItem;
public:
   double GetMileMarker();
   void SetMileMarker(double distance);
   Road GetCurrentRoad();
   void SetCurrentRoad(Road road);
//    RoadItem GetNext();
   virtual void Save(ISaveDriver *sd, std::ostream& stream) = 0;

    // void SetPrevious(RoadItem item);
    // SetNext(RoadItem item);
};

class StaticRoadItem : public RoadItem { 
    virtual void Save(ISaveDriver *sd, std::ostream& stream) = 0;

}; // empty

class DynamicRoadItem : public RoadItem {
public:
    virtual void Update(int seconds)=0; 
    virtual void Save(ISaveDriver *sd, std::ostream& stream) = 0;

}; // finalweek 

class StopSign : public StaticRoadItem {
public:
   StopSign(double distance);
   void Save(ISaveDriver *sd, std::ostream& stream) override;
};

class SpeedLimit : public StaticRoadItem {
private:
   double speedLimit;

public:
   SpeedLimit(double postedSpeed, double distance);
   double GetSpeedLimit();
   void Save(ISaveDriver *sd, std::ostream& stream) override;
};

class RoadItemsElement {
private:
    RoadItem *roadItem;
    RoadItemsElement *nextRoadItem;
    RoadItemsElement *prevRoadItem;
    void AddNext(RoadItem *roadItem); // these doubly linked list
    void AddPrev(RoadItem *roadItem);

public:
    RoadItemsElement();
    RoadItem * GetRoadItem();
    RoadItemsElement * GetNext();
    RoadItemsElement * GetPrev();
    void AddNew(RoadItem * roadItem);
};



// FINAL WEEK 
// Adding a traffic light and simulation of it:
// Create a class called Simulation with the following attribute and methods
// Attribute: {list, array, vector,…} of DynamicRoadItems
// Method: void AddDynamicRoadItem(DynamicRoadItem) // Adds entry to list
// Method: void Update(int seconds) // Iterates through list of DynamicRoadItems sending each an Update message
class Simulation {
public: 
    std::vector<DynamicRoadItem*> items;
    void AddDynamicRoadItem(DynamicRoadItem* d); // Adds entry to list
    void Update(int seconds); // Iterates through list of DynamicRoadItems sending each an Update message   
};

// Create a class called TrafficLight which inherits from DynamicRoadItem 
// with the following attributes and methods
// Attributes: int redTime, yellowTime, greenTime, timeOn; Color lit;
// Method/Constructor: TrafficLight(int redTime, int yellowTime, int GreenTime, Color startColor, double mileMarker) // the amount of time it should stay x color
// Method: override void Update(int seconds)
// Increments timeOn by seconds
// Checks to see if it is time to change the light (and does it)
// Print the current color of the light
class TrafficLight : public DynamicRoadItem  {
private: 
    int redTime; 
    int yellowTime; 
    int greenTime;
    char startColor='g'; // {green=0, yellow=1,red=2}

public:

    double mileMarker =0; // Also Roaditem Attribute 
    int timeOn; // not specified in the constructor
    int litColor; // maybe the simulator gives these? 

    // constructor the amount of time it should stay x color 
    TrafficLight(int redTime, int yellowTime, int greenTime, char startColor, double mileMarker);
    void Update(int seconds) override; 
    // Required by DRI class, required by RI class 
    void Save(ISaveDriver *sd, std::ostream& stream) override;

};









/*
    Courtney King, OOSD Homework 2 Feb 2, 2022
    Compile: g++ -std=c++11 hw2.cpp -o hw2
    File includes class defintions, function implementations in hw2.cpp 
*/

#include <vector>
#include <string>
#include <list>

using namespace std;

// Association - RoadItem 
class RoadItem; // Road and RoadItem have Dependency, must declare one first
class Road 
{
private:
    string name;
    double length;
    RoadItem* head; // fill with AddRoadItem;
public:
    Road(const string& newName );
    double GetLength();
    string GetRoadName();
    void AddRoadItem(RoadItem& newRoadItem); // Assocation relations
};
class RoadItem {
protected:
    double mileMarker;
    Road currentRoad; // SetCurrentRoad assocation
    RoadItem* nextRoad; // ** linked lists? 
    RoadItem*  prevItem;
public:
    RoadItem(double newMileMarker, Road &newCurrentRoad);
    double GetMileMarker();
    Road GetCurrentRoad();
    void SetCurrentRoad(Road& newRoad); // Association relation
    RoadItem GetNext();
    void SetNext();
    RoadItem GetPrevious();
    void SetPrevious();
    
};


class Dynamic:  public RoadItem // Assocation with Simulation, Inherits from RoadItem
{ // Parent of Light and Vehicle
public:
    void virtual UpDate(int seconds); // **abstract function 
};
class Simulation // Assocation with dynamic
{
private:
    list<Dynamic> roadItems;
public:
    void Update(int seconds); // keyword virtual in Dynamic
    void AddDynamicRoadItem(Dynamic& newItem);
};
class Light: public Dynamic
{
private:
    int redTime;
    int yellowTime;
    int greenTime;
public:
    void Update(int seconds); // **abstract function 
    void GetLightColor();
};
class Vehicle: public Dynamic // Inherits from Dynamic, Base class of Car, Truck
{
private: // could use 'protected' to give derived classes (Truck) access
    int currentSpeed;
    char currentDirection; // {'n','s','e','w'}
    vector<float> currentLocation; // {lat, long}
public: // public methods
    void Accelerate(int toSpeed);
    void Decelerate(int toSpeed);
    void Turn(char direction, int degrees);
};
class Car: public Vehicle{};
class Truck: public Vehicle // Specialization of Vehicle, 'is-a' use public inheritance
{
private:
    int loadWeight;
public:
    void SetLoadWeight(int weight);
};

class Static: public RoadItem{};
class StopSign: public Static{};
class Intersection: public Static{};
class SpeedLimit: public Static{};
class Yield: public Static{};
/*
    Courtney King, OOSD Homework 1, January 25, 2022
    Compile: g++ -std=c++11 hw1.cpp -o hw1
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std; 

/*
    A car whose attributes are current speed, current direction, and current location; 
    and whose methods are Accelerate(toSpeed), Decelerate(toSpeed), and Turn(direction, degrees) 
*/
class Car // Base class
{
private: // could use 'protected' to give derived classes (Truck) access
    int currentSpeed;
    char currentDirection; // {'n','s','e','w'}
    vector<float> currentLocation; // {lat, long}
public: // public methods
    void Accelerate(int toSpeed) { cout << "calling Car::Accelerate" << endl;};
    void Decelerate(int toSpeed) {};
    void Turn(char direction, int degrees) {};
};

/* 
    A truck whose attributes and methods are the same as the car, but with the additional 
    attribute of loadWeight and the additional method SetLoadWeight(weight)
*/
class Truck: public Car // Specialization of Car, 'is-a' use public inheritance
{
private:
    int loadWeight;
public:
    void SetLoadWeight(int weight) {};
};

/* 
    In an object-oriented language of your choice, encode the above
    The methods can just be empty for now, e.g. {}
    The program should compile error free, but does not have to do anything (for now!) 
*/
int main() // Quick test
{
    Car myCar; // default constructor 
    myCar.Accelerate(0); // public Car method 
    Truck myTruck;
    myTruck.SetLoadWeight(0); // public Truck method
    myTruck.Accelerate(0); // accessing Car method through Truck object
    return 0;
}


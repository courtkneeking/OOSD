#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <string>
#include <iostream>
#include <list>
#include "Map.h"
#include "Road.h"
#include "SUI.h"
// using namespace HW5_2021_OOP;
namespace HW5_2021_OOP
{
    namespace Constants 
    {
        static const double MpsToKph = 3.6;
        static const double AccRate=3.5;
        static const double AccRateEmpty = 2.5;     // Acceleration rate for light trucks in m/s
        static const double AccRateFull = 1.0;      // Acceleration rate for heavy trucks in m/s
        static const double DecRate = 7.0;          // Braking rate for cars in m/s
        static const double DecRateEmpty = 5.0;     // Braking rate for light trucks in m/s
        static const double DecRateFull = 2.0;      // Braking rate for light trucks in m/s
        static const double MpsToMph = 2.237;
        static const double speedLimit=0;
        static const int CharMapSize = 40; // hw6
        static const double WorldSize = 200.0;
        static const double MetersToMiles = 0.000621371;
        static const double MetersToKm = 0.001;
    };

    class Vehicle // abstract class Vehicle
    {
    private:
        double currentSpeed;
        double desiredSpeed;
    protected: 
        virtual void Accelerate(int secondsDelta); // abstract
        virtual void Decelerate(int secondsDelta); // abstract
        void SetCurrentSpeed(double speed);
    public: 
        virtual ~Vehicle();
        double GetCurrentSpeed();
        void SetDesiredSpeed(double mph);
        void UpdateSpeed(int seconds);
    };
    // removed conversion constants, added in interface 
    class Car : public Vehicle
    {
    public:
        void Accelerate(int secondsDelta) override;
        void Decelerate(int secondsDelta) override;
    };
    class Truck : public Vehicle
    {
    private:
        int loadWeight; // in tons
    public:
        Truck(int weight);
        void Accelerate(int secondsDelta) override;
        void Decelerate(int secondsDelta) override;
    };
    class ISimOutput  
    {
    public:
        virtual double GetSpeed(Vehicle &v)=0;
    };
    class ISimInput 
    {
    public:
        virtual void SetSpeedLimit(Vehicle &v, double speed)=0;
    };
    class GUI : public ISimInput, public ISimOutput
    {
    public:
        virtual Road* CreateRoad(std::string, double x, double y, double z, Heading direction)=0; 
        virtual double GetSpeed(Vehicle &v)=0;
        virtual void SetSpeedLimit(Vehicle &v, double speed)=0;
    };
    class ImperialGUI: public GUI
    {
    public:
        Road* CreateRoad(std::string, double x, double y, double z, Heading direction) override;
        double GetSpeed(Vehicle &v) override;
        void SetSpeedLimit(Vehicle &v, double s) override;
    };
    class MetricGUI: public GUI
    {
    public:
        Road* CreateRoad(std::string, double x, double y, double z, Heading direction) override;
        double GetSpeed(Vehicle &v) override;
        void SetSpeedLimit(Vehicle &v, double s) override;
    };

    class Program
    {
    public:
        static void Main();
    };
}

#endif




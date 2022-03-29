#ifndef PROGRAM_CPP_
#define PROGRAM_CPP_

#include <string>
#include <iostream>
#include <list>

#include "Map.cpp"
#include "Road.cpp"
#include "SUI.cpp"

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
        virtual void Accelerate(int secondsDelta){}; // abstract
        virtual void Decelerate(int secondsDelta){}; // abstract
        void SetCurrentSpeed(double speed)
        {
            if(currentSpeed <= speed) // accelerating
            {
                if (speed > desiredSpeed) currentSpeed = desiredSpeed;
                else currentSpeed = speed;
            }
            else // braking
            {
                if (speed < desiredSpeed) currentSpeed = desiredSpeed;
                else currentSpeed = speed;
            }
        }
    public: 
        virtual ~Vehicle() {};
        double GetCurrentSpeed(){
            return currentSpeed;
        }
        void SetDesiredSpeed(double mph)
        {
            desiredSpeed = mph;
        }
        void UpdateSpeed(int seconds)
        {
            if (currentSpeed > desiredSpeed) {
                Decelerate(seconds);
            }
            else if (currentSpeed < desiredSpeed) {
                Accelerate(seconds);
            }
        }
    };
    // removed conversion constants, added in interface 
    class Car : public Vehicle
    {
    public:
        void Accelerate(int secondsDelta) override {
            SetCurrentSpeed(GetCurrentSpeed()+Constants::AccRate*secondsDelta);
        }
        void Decelerate(int secondsDelta) override {
            SetCurrentSpeed(GetCurrentSpeed()-Constants::AccRate*secondsDelta);
        }
    };
    class Truck : public Vehicle
    {
    private:
        int loadWeight; // in tons
    public:
        Truck(int weight)
        {
            loadWeight = weight;
        }
        // removed conversion constants, added in interface 
        void Accelerate(int secondsDelta) override 
        {
            if (loadWeight <= 5){
                SetCurrentSpeed(GetCurrentSpeed()+Constants::AccRateEmpty*secondsDelta); 
            }
            else{
                SetCurrentSpeed(GetCurrentSpeed()+Constants::AccRateFull*secondsDelta);
            }
        }
        // removed conversion constants, added in interface 
        void Decelerate(int secondsDelta) override 
        {
            if (loadWeight <= 5){
                SetCurrentSpeed(GetCurrentSpeed()-Constants::DecRateEmpty*secondsDelta);
            }
            else
            {
                SetCurrentSpeed(GetCurrentSpeed()-Constants::DecRateFull*secondsDelta);
            }
        }
    };
    // interface virtual class, does not implment any methods
    // implmented by GUI, through public inheritance 
    // GUI have the same declarations 
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
    // GUI implements interfaces, but is an abstract class 
    // must contain interface functions, but they're still virtual
    class GUI : public ISimInput, public ISimOutput
    {
    public:
        // hw6
        virtual Road* CreateRoad(std::string, double x, double y, double z, Heading direction)=0; 
        virtual double GetSpeed(Vehicle &v)=0;
        virtual void SetSpeedLimit(Vehicle &v, double speed)=0;
    };
    // ImperialGUI, MetricGUI, is-a GUI inheritance 
    // finally define the functions, use keyword override (or final?)
    class ImperialGUI: public GUI
    {
    public:
        // hw6
        Road* CreateRoad(std::string, double x, double y, double z, Heading direction) override 
        {};

        double GetSpeed(Vehicle &v) override
        {
            return v.GetCurrentSpeed()*Constants::MpsToMph; 
        };
        void SetSpeedLimit(Vehicle &v, double s) override 
        { 
            v.SetDesiredSpeed( s/Constants::MpsToMph );
        };
    };
    class MetricGUI: public GUI
    {
    public:
        // hw6
        Road* CreateRoad(std::string, double x, double y, double z, Heading direction) override 
        {};

        double GetSpeed(Vehicle &v) override
        {
            return v.GetCurrentSpeed()*Constants::MpsToKph; 
        };
        void SetSpeedLimit(Vehicle &v, double s) override
        { 
            v.SetDesiredSpeed(s/Constants::MpsToKph);
        };
    };

    class Program
    {
    public:
        static void Main()
        {
            GUI* simInput;
            Map* map = new Map();
            // IPrintDriver cp = new ConsolePrint();
            simInput = new MetricGUI();
            // Road* Uptown = simInput->CreateRoad("Uptown", 0.0, -0.09, .180, Heading North);
            // map->AddRoad(Uptown);
            // Road* Crosstown = simInput->CreateRoad("Crosstown", -0.09, 0.0, .180, Heading East);
            // map->AddRoad(Crosstown);

            CharMatrix* cm = new CharMatrix();
            // map->Print(cp, cm);
            // for (int i = 0; i < Constants::CharMapSize; i++)
            // {
            //     std::string* s = new std::string(cm.map[i]);
            //     std::cout << s << std::endl;
            // }
   
        }
    };
}

#endif








// using System;
// using System.Collections.Generic;

// namespace HW5_2021_OOP
// {
//     static class Constants
//     {
//         public const double AccRate = 3.5;          // Acceleration rate for cars in m/s
//         public const double AccRateEmpty = 2.5;     // Acceleration rate for light trucks in m/s
//         public const double AccRateFull = 1.0;      // Acceleration rate for heavy trucks in m/s
//         public const double DecRate = 7.0;          // Braking rate for cars in m/s
//         public const double DecRateEmpty = 5.0;     // Braking rate for light trucks in m/s
//         public const double DecRateFull = 2.0;      // Braking rate for light trucks in m/s
//         public const double MpsToMph = 2.237;
//         public const double MpsToKph = 3.6;
//         public const double MetersToMiles = 0.000621371;
//         public const double MetersToKm = 0.001;
//         public const int CharMapSize = 40;
//         public const double WorldSize = 200.0;
//     }

//     class Program : ISimInput, ISimOutput
//     {
//         static void Main(string[] args)
//         {
//             GUI simInput;
//             Map map = new Map();
//             IPrintDriver cp = new ConsolePrint();
//             //Console.Write("Enter 'M' for metric or 'I' for Imperial: ");
//             //string units = Console.ReadLine();
//             //Console.Write("Enter speed limit: ");
//             //double speedLimit = Convert.ToDouble(Console.ReadLine());
//             //if (units == "I") gui = new ImperialGUI();
//             //else gui = new MetricGUI();
//             //Car car = new Car(); gui.SetSpeedLimit(car, speedLimit);
//             //Truck truck1 = new Truck(4); gui.SetSpeedLimit(truck1, speedLimit);
//             //Truck truck2 = new Truck(8); gui.SetSpeedLimit(truck2, speedLimit);
//             //List<Vehicle> vehicles = new List<Vehicle>();
//             //vehicles.Add(car); vehicles.Add(truck1); vehicles.Add(truck2);
//             //for (int i = 0; i < 11; i++)
//             //{
//             //    foreach (Vehicle v in vehicles)
//             //    {
//             //        v.UpdateSpeed(1);
//             //        string s = v.GetType().ToString();
//             //        Console.WriteLine("{0} speed: {1:F}", s, gui.GetSpeed(v));
//             //    }
//             //}
//             simInput = new MetricGUI();
//             Road Uptown = simInput.CreateRoad("Uptown", 0.0, -0.09, .180, Heading.North);
//             map.AddRoad(Uptown);
//             Road Crosstown = simInput.CreateRoad("Crosstown", -0.09, 0.0, .180, Heading.East);
//             map.AddRoad(Crosstown);

//             CharMatrix cm = new CharMatrix();
//             map.Print(cp, cm);
//             for (int i = 0; i < Constants.CharMapSize; i++)
//             {
//                 string s = new string(cm.map[i]);
//                 Console.WriteLine(s);
//             }
//         }

//         public double GetSpeed(Vehicle v)
//         {
//             return v.GetCurrentSpeed() * Constants.MpsToMph;
//         }

//         public void SetSpeedLimit(Vehicle v, double speed)
//         {
//             v.SetDesiredSpeed(speed / Constants.MpsToMph);
//         }
//     }

//     interface ISimInput
//     {
//         void SetSpeedLimit(Vehicle v, double speed);
//     }

//     interface ISimOutput
//     {
//         double GetSpeed(Vehicle v);
//     }
    
//     abstract class GUI : ISimInput, ISimOutput
//     {
//         public abstract Road CreateRoad(string name, double locx, double locy, double len, Heading hdg);
//         public abstract double GetSpeed(Vehicle v);
//         public abstract void SetSpeedLimit(Vehicle v, double speed);
//     }

//     class MetricGUI : GUI
//     {
//         public override Road CreateRoad(string name, double locx, double locy, double len, Heading hdg)
//         {
//             return new Road(name, locx / Constants.MetersToKm, locy / Constants.MetersToKm, len / Constants.MetersToKm, hdg);
//         }

//         public override double  GetSpeed(Vehicle v)
//         {
//             return v.GetCurrentSpeed() * Constants.MpsToKph;
//         }

//         public override void SetSpeedLimit(Vehicle v, double speed)
//         {
//             v.SetDesiredSpeed(speed / Constants.MpsToKph);
//         }
//     }

//     class ImperialGUI : GUI
//     {
//         public override Road CreateRoad(string name, double locx, double locy, double len, Heading hdg)
//         {
//             return new Road(name, locx / Constants.MetersToMiles, locy / Constants.MetersToMiles, len / Constants.MetersToMiles, hdg);
//         }
//         public override double GetSpeed(Vehicle v)
//         {
//             return v.GetCurrentSpeed() * Constants.MpsToMph;
//         }

//         public override void SetSpeedLimit(Vehicle v, double speed)
//         {
//             v.SetDesiredSpeed(speed / Constants.MpsToMph);
//         }
//     }

//     abstract class Vehicle
//     {
//         private double currentSpeed = 0.0;
//         private double desiredSpeed;

//         protected abstract void Accelerate(int secondsDelta);
//         protected abstract void Decelerate(int secondsDelta);

//         public double GetCurrentSpeed()
//         {
//             return currentSpeed;
//         }

//         public void SetDesiredSpeed(double speed)
//         {
//             desiredSpeed = speed;
//         }

//         protected void SetCurrentSpeed(double speed)
//         {
//             if (currentSpeed <= speed) // accelerating
//             {
//                 if (speed > desiredSpeed) currentSpeed = desiredSpeed;
//                 else currentSpeed = speed;
//             }
//             else // braking
//             {
//                 if (speed < desiredSpeed) currentSpeed = desiredSpeed;
//                 else currentSpeed = speed;
//             }
//         }

//         public void UpdateSpeed(int seconds)
//         {
//             if (currentSpeed > desiredSpeed) Decelerate(seconds);
//             else if (currentSpeed < desiredSpeed) Accelerate(seconds);
//         }
//     }

//     class Car : Vehicle
//     {
//         protected override void Accelerate(int secondsDelta)
//         {
//             SetCurrentSpeed(GetCurrentSpeed() + Constants.AccRate * secondsDelta);
//         }

//         protected override void Decelerate(int secondsDelta)
//         {
//             SetCurrentSpeed(GetCurrentSpeed() - Constants.DecRate * secondsDelta);
//         }
//     }

//     class Truck : Vehicle
//     {
//         private int loadWeight;      // in tons

//         public Truck(int weight)
//         {
//             loadWeight = weight;
//         }

//         protected override void Accelerate(int secondsDelta)
//         {
//             if (loadWeight <= 5)
//                 SetCurrentSpeed(GetCurrentSpeed() + Constants.AccRateEmpty * secondsDelta);
//             else
//                 SetCurrentSpeed(GetCurrentSpeed() + Constants.AccRateFull * secondsDelta);
//         }

//         protected override void Decelerate(int secondsDelta)
//         {
//             if (loadWeight <= 5)
//                 SetCurrentSpeed(GetCurrentSpeed() - Constants.DecRateEmpty * secondsDelta);
//             else
//                 SetCurrentSpeed(GetCurrentSpeed() - Constants.DecRateFull * secondsDelta);
//         }
//     }

// }

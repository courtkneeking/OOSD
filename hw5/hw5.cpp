/* Start with last week’s homework:
1.Add a constant for converting meters per second to kilometers per hour, e.g:
  public const double MpsToKph = 3.6;
2.Remove all conversions from Car and Truck class definitions.
3.Add input to the program that gets a choice of using metric or imperial i/o and input of a speed limit. 
Use this entry for the desired speed for all three vehicles.
4.Modify your program to have a GUI class that facilitates switching between metric input and output, 
and imperial input and output to produce output similar to the last slide (program run once 
for (M)etric and once for (I)mperial). Week5.pptx */

#include <string>
#include <iostream>
#include <list>

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
        virtual double GetSpeed(Vehicle &v)=0;
        virtual void SetSpeedLimit(Vehicle &v, double speed)=0;
    };
    // ImperialGUI, MetricGUI, is-a GUI inheritance 
    // finally define the functions, use keyword override (or final?)
    class ImperialGUI: public GUI
    {
    public:
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
            // declare gui, get input, set gui using interface 
            GUI* gui;
            char units;
            std::cout << "Enter units ('M' for metric 'I' for Imperial)" << std::endl;
            std::cin>>units;
            if (units == 'I') gui = new ImperialGUI();
            else gui = new MetricGUI();
            // get speedlimit from user 
            double speedLimit;
            std::cout << "Enter speed limit (float)" << std::endl;
            std::cin>>speedLimit;

            // set the speed limit for the three cars 
            // based on the speedLimit input and interface unit
            Car* car =  new Car(); 
            Truck* truck1 = new Truck(4);  // random load weight 
            Truck* truck2 = new Truck(8); 

            // car->SetDesiredSpeed(speedLimit);
            // truck1->SetDesiredSpeed(speedLimit);
            // truck2->SetDesiredSpeed(speedLimit);

            gui->SetSpeedLimit(*car,speedLimit);
            gui->SetSpeedLimit(*truck1,speedLimit);
            gui->SetSpeedLimit(*truck2,speedLimit);



            std::list<Vehicle*> vehicles;

            vehicles.push_back(car); 
            vehicles.push_back(truck1); 
            vehicles.push_back(truck2);

            for(int i=0; i<11; i++){
                for(Vehicle* v: vehicles){ 
                    v->UpdateSpeed(1); 
                    std::cout <<  typeid(*v).name() << " speed " << gui->GetSpeed(*v) << std::endl;  
                }
            }
        }
    };
}


int main(){
    using namespace HW5_2021_OOP;
    Program p =Program();
    p.Main();
    return 0;
}
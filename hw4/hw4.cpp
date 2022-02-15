
#include <string>
#include <iostream>
#include <list>

// For now, just declare in driver function 
// using namespace HW3_2021_OOP; 
namespace HW3_2021_OOP
{
    // implementing a static class to hold data members of type double 
    // seems to be more lengthy and complicated in C++
    // seemed reasonable to use namespace to hold static variables 
    // Access within HW3_2021_OOP by Constants::data_member 
    namespace Constants 
    {
        static const double AccRate=3.5;
        static const double AccRateEmpty = 2.5;     // Acceleration rate for light trucks in m/s
        static const double AccRateFull = 1.0;      // Acceleration rate for heavy trucks in m/s
        static const double DecRate = 7.0;          // Braking rate for cars in m/s
        static const double DecRateEmpty = 5.0;     // Braking rate for light trucks in m/s
        static const double DecRateFull = 2.0;      // Braking rate for light trucks in m/s
        static const double MpsToMph = 2.237;
    };

    class Vehicle // abstract class Vehicle
    {
    // Only Vehicle can access these attributes, not Car, Truck or driver function 
    // Car, Truck can access through protected method, Vehicle::SetCurrentSpeed()
    private:
        // It probably doesn't make a difference if we set these to zero or not 
        // We are using a default destructor 
        double currentSpeed;
        double desiredSpeed;
    // Protected means derived classes (Car, Truck) can call these methods,
    // they are not public, so cannot be called in driver function 
    protected: 
        // these are the abstract methods, marked by keyword virtual 
        // they should be implemented in the derived classes: Car, Truck 
        // (?) maybe we should have '=0' instead of '{}' to make this a virtual class (?)
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
    // Public Vehicle methods can be called from Car, Truck, or driver function 
    public: 
        // Abstract Base Class requires having a virtual destructor
        // Otherwise there will be a memory leak
        // The destructors in the derived classes should do the destruction
        virtual ~Vehicle() {};
        double GetCurrentSpeed(){
            return currentSpeed;
        }
        void SetDesiredSpeed(double mph)
        {
            desiredSpeed = mph;
        }
        // Accelerate, Decelerate methods called here are virtual in Vehicle class
        // the eponymous methods are called based on the object's specific type (Car, Truck) 
        void UpdateSpeed(int seconds)
        {
            // only Vehicle has access to these data members 
            if (currentSpeed > desiredSpeed) {
                Decelerate(seconds);
            }
            else if (currentSpeed < desiredSpeed) {
                Accelerate(seconds);
            }
        }
    };
    // Inheritance Car IS-A Vehicle; use public inhertance of base class 
    class Car : public Vehicle
    {
    public:
        // this is virtual function in the inherited class Vehicle 
        // must be implemented in all derived classes 
        // keywords override, final tell the compiler of intention, so will protect from insidious errors
        void Accelerate(int secondsDelta) override {
            SetCurrentSpeed(GetCurrentSpeed() \
                + Constants::AccRate * secondsDelta * Constants::MpsToMph);
        }
        // this is a virtual function in the inherited class Vehicle 
        void Decelerate(int secondsDelta) override {
            SetCurrentSpeed(GetCurrentSpeed() \
                - Constants::AccRate * secondsDelta * Constants::MpsToMph);
        }
    };
    // Inheritance Truck IS-A Vehicle; use public inhertance of base class 
    // Now Truck can have its own separate data members and functions from Car class
    // Yet share those in Vehicle class 
    class Truck : public Vehicle
    {
    private:
        int loadWeight;// in tons
    public:
        Truck(int weight)
        {
            loadWeight = weight;
        }
        // this is a virtual function in the inherited class Vehicle 
        // must be implemented in all derived classes 
        // keywords override, final tell the compiler of intention, so will protect from insidious errors
        void Accelerate(int secondsDelta) override 
        {
            // only Truck has access to this data member loadWeight 
            if (loadWeight <= 5){
                SetCurrentSpeed(GetCurrentSpeed() \
                    + Constants::AccRateEmpty * secondsDelta * Constants::MpsToMph);
            }
            else{
                SetCurrentSpeed(GetCurrentSpeed() \
                    + Constants::AccRateFull * secondsDelta * Constants::MpsToMph);
            }
        }
        // this is a virtual function in the inherited class Vehicle 
        void Decelerate(int secondsDelta) override 
        {
            if (loadWeight <= 5){
                SetCurrentSpeed(GetCurrentSpeed() \
                    - Constants::DecRateEmpty * secondsDelta * Constants::MpsToMph);
            }
            else
            {
                SetCurrentSpeed(GetCurrentSpeed() \
                    - Constants::DecRateFull * secondsDelta * Constants::MpsToMph);
            }
        }
    };
    // ISimOutput will not be instantiated, more as a wrapper
    // the purpose is that we'll have other methods here
    // that ImperialOutput or MetricOutput can access 
    // maybe they both need to be printed, rounded, etc.
    class ISimOutput
    {
    public:
        // pure virtual method, now ISimOutput is an Abstract Base Class (ABC)
        // dervied classes MUST implement this method
        // can also use keywords override, final to inform compiler of intention to prevent insidious errors
        virtual double GetSpeed(Vehicle &v)=0;
    };
    // ABC, public inhertiance 
    class ImperialOutput: public ISimOutput
    {
    public: 
        // pass existing Vehicle object by reference, not value 
        double GetSpeed(Vehicle &v){
            // the vehicle parameter is not a pointer here 
            // but an existing/reference object, use dot for method calls 
            return v.GetCurrentSpeed();
        }
    };
    class MetricOutput: public ISimOutput
    {
    public:
        double GetSpeed(Vehicle &v){
            return v.GetCurrentSpeed() * 1.6;
        }
    };

    class Program
    {
        public:
        static void Main()
        {
            // derived classes from ABC ISimOutput 
            MetricOutput metricSim;
            ImperialOutput imperialSim;

            // derived classes of Vehicle 
            // declare on heap, hold pointer values in variables 
            Car* car =  new Car(); 
            car->SetDesiredSpeed(65.0);
            Truck* truck1 = new Truck(4); 
            truck1->SetDesiredSpeed(55.0);
            Truck* truck2 = new Truck(8); 
            truck2->SetDesiredSpeed(50.0);

            // push Car, Truck pointer variables into list of Vehicle pointers 
            std::list<Vehicle*> vehicles;
            vehicles.push_back(car); 
            vehicles.push_back(truck1); 
            vehicles.push_back(truck2);
            
            // Iterate Vehicle pointers list
            for(Vehicle* v: vehicles){ // could also use auto 
                // I don't completely understand the program functions 
                // this function must be here or the calls below will stay at 0 
                v->UpdateSpeed(1);  
                // GetSpeed takes in reference Vehicle object
                // so pass the value at the pointer into these function calls              
                std::cout << "Metric: " <<  metricSim.GetSpeed(*v) << std::endl;
                std::cout << "Imperial: " <<  imperialSim.GetSpeed(*v) << std::endl;
            }

        }
    };
}


int main(){
    using namespace HW3_2021_OOP;
    Program p =Program();
    p.Main();
    return 0;
}
// Courtney King, OOSD, Homework 3, February 8 
// Compile: g++ -std=c++11 Program.cpp -o p

# include <list>
# include <iostream>
# include <string>

namespace HW3_2021_OOP
{
    // implementing a static class to hold data members of type double 
    // seems to be more lengthy and complicated in C++
    // seemed reasonable to use namespace to hold static variables 
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
    private:
        double currentSpeed = 0.0;
        double desiredSpeed= 0.0;

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
        // method call from outside function 
        // GetVehicleType(Vehicle& inputVehicle)
        virtual void GetType() {
            std::cout<< "Vehicle";
        }
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

    class Car : public Vehicle
    {
    public:
        // method call from outside function 
        // GetVehicleType(Vehicle& inputVehicle)
        void GetType() override {
            std::cout<< "Car";
        }
    protected:
        void Accelerate(int secondsDelta) override {
            SetCurrentSpeed(GetCurrentSpeed() \
                + Constants::AccRate * secondsDelta * Constants::MpsToMph);
        }
        void Decelerate(int secondsDelta) override {
            SetCurrentSpeed(GetCurrentSpeed() \
                - Constants::AccRate * secondsDelta * Constants::MpsToMph);
        }
    };

    class Truck : public Vehicle
    {
    private:
        int loadWeight;      // in tons
    public:
        Truck(int weight)
        {
            loadWeight = weight;
        }
        // method call from outside function 
        // GetVehicleType(Vehicle& inputVehicle)
        void GetType() override {
            std::cout<< "Truck";
        }
    protected:
        void Accelerate(int secondsDelta) override // override 
        {
            if (loadWeight <= 5){
                SetCurrentSpeed(GetCurrentSpeed() \
                    + Constants::AccRateEmpty * secondsDelta * Constants::MpsToMph);
            }
            else{
                SetCurrentSpeed(GetCurrentSpeed() \
                    + Constants::AccRateFull * secondsDelta * Constants::MpsToMph);
            }
        }
        void Decelerate(int secondsDelta) override // override 
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
    // function declared outside of Vehicle hierarchy 
    // calls GetType() virtual/override to get specific vehicle type
    void GetVehicleType(Vehicle& inputVehicle){
        inputVehicle.GetType();
    }
    class Program
    {
        public:
        static void Main(){
            Car* car =  new Car(); 
            car->SetDesiredSpeed(65.0);
            Truck* truck1 = new Truck(4); 
            truck1->SetDesiredSpeed(55.0);
            Truck* truck2 = new Truck(8); 
            truck2->SetDesiredSpeed(50.0);

            std::list<Vehicle*> vehicles;

            vehicles.push_back(car); 
            vehicles.push_back(truck1); 
            vehicles.push_back(truck2);

            for(int i=0; i<11; i++){
                for(Vehicle* v: vehicles){ // could also use auto 
                    v->UpdateSpeed(1); 
                    GetVehicleType(*v); // calls function v.GetType()
                    std::cout << " speed: " << v->GetCurrentSpeed() << " mph" << std::endl;  
                }
            }
        }
    };
};

int main()
{   
    using namespace HW3_2021_OOP;
    Program p = Program();
    p.Main();
    return 0;
}

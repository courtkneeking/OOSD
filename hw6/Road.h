#ifndef ROAD_H_
#define ROAD_H_ 

#include <string>
#include "SUI.h"

namespace HW5_2021_OOP
{
    enum Heading { North, South, East, West };
    class Road
    {
    private:
        std::string name;
        double length;
        double xlocation;
        double ylocation;
        Heading heading;
        static int NumOfRoads;
    public: 
        Road(std::string streetName, double locX, double locY, double len, Heading hdg);
        double GetLength();
        double GetXLocation();
        double GetYLocation();
        Heading GetHeading(); 
        std::string GetRoadName(); 
        void Print(IPrintDriver print, Container* o); // Container = object
    };
}
#endif 


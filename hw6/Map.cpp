#ifndef _MAP_CPP
#define _MAP_CPP 

#include <list>
#include "Road.cpp"
#include "Program.cpp"

namespace HW5_2021_OOP
{
    class Map
    {
    private:
        std::list<Road*> roads;

    public:
        Map()
        {
            // roads = new std::list<Road*>();
        }

        void AddRoad(Road* road)
        {
            // roads.Add(road);
            roads.push_back(road);
        }

        void Print(IPrintDriver pd, Container* o) // Object = Container
        {
            for (Road* road: roads)
            {
                road->Print(pd, o);
            }
        }
    };
}
#endif

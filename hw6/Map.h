#ifndef _MAP_H
#define _MAP_H

#include <list>

#include "Road.h"
#include "Program.h"

// class Container // instead of Object
// {
// 	public:
// 	virtual ~Container() = default;
// };
namespace HW5_2021_OOP
{
    class Map
    {
    private:
        std::list<Road*> roads;

    public:
        Map();
        void AddRoad(Road* road);
        void Print(IPrintDriver pd, Container* o); // container = object
    };
}
#endif

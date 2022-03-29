#ifndef ROAD_CPP_
#define ROAD_CPP_ 

#include <string>
#include "SUI.cpp"

// should this just be redelcared in each file? 
class Container // instead of Object
{
	public:
	virtual ~Container() = default;
};
// using namespace HW5_2021_OOP;
namespace HW5_2021_OOP
{
// public 
    enum Heading { North, South, East, West };
    class Road
    {
        //private RoadItem head;
    private:
        std::string name;
        double length;
        double xlocation;
        double ylocation;
        Heading heading;
        // static int NumOfRoads = 0;
         static int NumOfRoads;

    public: 
        Road(std::string streetName, double locX, double locY, double len, Heading hdg)
        {
            //head = new RoadItem();
            //head.SetPrevious(null);
            //head.SetNext(null);
            name = streetName;
            length = len;
            heading = hdg;
            xlocation = locX;
            ylocation = locY;
            NumOfRoads++;
        }

        double GetLength() { return length; }

        double GetXLocation() { return xlocation; }

        double GetYLocation() { return ylocation; }

        Heading GetHeading() { return heading; }

        std::string GetRoadName() { return name; }

        //public void AddRoadItem(RoadItem roadItem)
        //{
        //    roadItem.SetCurrentRoad(this);
        //    RoadItem currentItem = head;
        //    while (currentItem.GetNext() != null)
        //    {
        //        currentItem = currentItem.GetNext();
        //        if (currentItem.GetMileMarker() > roadItem.GetMileMarker())
        //        {
        //            InsertNewItemBefore(currentItem, roadItem);
        //            return;
        //        }
        //    }
        //    InsertNewItemAfter(currentItem, roadItem);
        //}

        void Print(IPrintDriver print, Container* o) // Obj = Continaer
        {
            print.PrintRoad(this, o);
            // print.PrintRoad()
        }

        //    private void InsertNewItemBefore(RoadItem current, RoadItem newItem)
        //    {
        //        newItem.SetPrevious(current.GetPrevious());
        //        newItem.SetNext(current);
        //        current.SetPrevious(newItem);
        //        newItem.GetPrevious().SetNext(newItem);
        //    }

        //    private void InsertNewItemAfter(RoadItem current, RoadItem newItem)
        //    {
        //        newItem.SetNext(current.GetNext());
        //        current.SetNext(newItem);
        //        newItem.SetPrevious(current);
        //        if (newItem.GetNext() != null) newItem.GetNext().SetPrevious(newItem);
        //    }
        //}
    };
}
#endif 


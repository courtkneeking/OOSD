#ifndef SUI_H_
#define SUI_H_

#include "Program.h"
#include "Map.h"
#include "Common.h"
#include "Road.h"

// using namespace HW5_2021_OOP;
namespace HW5_2021_OOP
{
class Container // instead of Object
{
	public:
	virtual ~Container() = default;
};
class CharMatrix : public Container // Object
{
public:
    // char** map = new char[Constants::CharMapSize][];
    char* map[Constants::CharMapSize];
    CharMatrix();
};
class IPrintDriver : public Container // interface
{
public:
    void PrintRoad(Road* road, Container* o); // Object = Container
    void PrintCar(Car* car, Container* o);
};

class ConsolePrint : IPrintDriver
{
public:
    void PrintRoad(Road* road, Container* o); 
    void PrintCar(Car* car, Container* o);
};
}
#endif


// class Container
// {
// 	public:
// 	virtual ~Container() = default;
// };
// class CharArray : public Container
// {
// 	public:
// 	char map[3] = { 'x','y','z' };
// };

// class IntArray : public Container
// {
// 	public:
// 	int map[3] = { 3,4,5 };
// };
// void PrintChar(Container* c, int index);
// void PrintInt(Container* c, int index);


#ifndef SUI_CPP_
#define SUI_CPP_

#include "Program.cpp"
#include "Map.cpp"
#include "Common.cpp"
#include "Road.cpp"

// using namespace HW5_2021_OOP;
namespace HW5_2021_OOP{
class Container // instead of Object
{
	public:
	virtual ~Container() = default;
};

class CharMatrix : public Container 
{
public:
    // char** map = new char[Constants::CharMapSize][];
    char* map[Constants::CharMapSize];
    CharMatrix()
    {
        for (int i = 0; i < Constants::CharMapSize; i++)
        {
            map[i] = new char[Constants::CharMapSize];
            for (int j = 0; j < Constants::CharMapSize; j++) map[i][j] = ' ';
        }
    }
};

class IPrintDriver  : public Container // interface
{
public:
    void PrintRoad(Road* road, Container* o); // Object = auto
    void PrintCar(Car* car, Container* o);
};

class ConsolePrint : IPrintDriver
{
public:
    void PrintRoad(Road* road, Container* o) // Obj = auto
    {
        // CharMatrix cm = (CharMatrix)o;
        CharMatrix* cm = new CharMatrix();
        int x, y;
        int CCx = Conversions::WCpointToCCpoint(road->GetXLocation());
        int CCy = Conversions::WCpointToCCpoint(-road->GetYLocation());
        int distance = 0;
        int CCRoadLength = Conversions::WClengthToCClength(road->GetLength());
        Heading h = road->GetHeading();
        // switch (road.GetHeading())
        switch (h)
        {
            // case Heading.North:
            case North:
                x = (int)CCx;
                if (x >= 0 && x < Constants::CharMapSize)
                {
                    while (distance < CCRoadLength)
                    {
                        y = (int)(CCy - distance);
                        if (y >= 0 && y < Constants::CharMapSize)
                        {
// ˜˜˜˜ CK adjust here to complete map 
                            continue; 
                            // cm.map[y][x] = '|';
                            // cm.map[y][x + 2] = '|';
                            // cm.map[y][x + 4] = '|';
                        }
                        distance += 1;
                    }
                }
                break;
            // case Heading.South:
            case South:
                break;
            // case Heading.East:
            case East:
                y = (int)CCy;
                if (y >= 0 && y < Constants::CharMapSize)
                {
                    while (distance < CCRoadLength)
                    {
                        x = (int)(CCx + distance);
                        if (x >= 0 && x < Constants::CharMapSize)
                        {
                            continue;
                            // cm.map[y][x] = '-';
                            // cm.map[y + 2][x] = '-';
                            // cm.map[y + 4][x] = '-';
                        }
                        distance += 1;
                    }
                }
                break;
            // case Heading.West:
            case West:
                break;
            default:
                break;
        }
    }

    void PrintCar(Car* car, Container* o) // OB = auto
    {

    }
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

// void PrintChar(Container* c, int index)
// {
// 	CharArray* ca = dynamic_cast<CharArray*>(c);
// 	std::cout << "The character is: " << (ca->map[index]) << std::endl;
// };

// void PrintInt(Container* c, int index)
// {
// 	IntArray* ia = dynamic_cast<IntArray*>(c);
// 	std::cout << "The number is: " << (ia->map[index]) << std::endl;
// };

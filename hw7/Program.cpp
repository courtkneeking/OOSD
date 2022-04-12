#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "Program.h"


void Vehicle::SetCurrentSpeed(double speed) {
    if(currentSpeed <= speed) // accelerating
    {
        if (speed > desiredSpeed) 
            currentSpeed = desiredSpeed;
        else currentSpeed = speed;
    }
    else // braking
    {
        if (speed < desiredSpeed) 
            currentSpeed = desiredSpeed;
        else currentSpeed = speed;
    }
}
double Vehicle::GetCurrentSpeed(){
    return currentSpeed;
}
void Vehicle::SetDesiredSpeed(double mph) {
    desiredSpeed = mph;
}
void Vehicle::UpdateSpeed(int seconds) {
    if (currentSpeed > desiredSpeed) {
        Decelerate(seconds);
    }
    else if (currentSpeed < desiredSpeed) {
        Accelerate(seconds);
    }
}

void Car::Accelerate(int secondsDelta) {
    SetCurrentSpeed(GetCurrentSpeed()+Constants::AccRate*secondsDelta);
}
void Car::Decelerate(int secondsDelta) {
    SetCurrentSpeed(GetCurrentSpeed()-Constants::AccRate*secondsDelta);
}

Truck::Truck(int weight){
    loadWeight = weight;
}
void Truck::Accelerate(int secondsDelta) { // keyword override in header file, not here 
    if (loadWeight <= 5)
        SetCurrentSpeed(GetCurrentSpeed()+Constants::AccRateEmpty*secondsDelta); 
    else
        SetCurrentSpeed(GetCurrentSpeed()+Constants::AccRateFull*secondsDelta);
}
void Truck::Decelerate(int secondsDelta)
{
    if (loadWeight <= 5)
        SetCurrentSpeed(GetCurrentSpeed()-Constants::DecRateEmpty*secondsDelta);
    else
        SetCurrentSpeed(GetCurrentSpeed()-Constants::DecRateFull*secondsDelta);
}

Road ImperialGUI::CreateRoad(std::string name, double x, double y, double z, Heading direction) 
{
    return Road(name, x / Constants::MetersToMiles, y / Constants::MetersToMiles, z / Constants::MetersToMiles, direction);
};
double ImperialGUI::GetSpeed(Vehicle &v) 
{
    return v.GetCurrentSpeed()*Constants::MpsToMph; 
};
void ImperialGUI::SetSpeedLimit(Vehicle &v, double speed) 
{ 
    v.SetDesiredSpeed( speed /Constants::MpsToMph );
};
Road MetricGUI::CreateRoad(std::string name, double x, double y, double z, Heading direction)
{
    return Road(name, x / Constants::MetersToKm, y / Constants::MetersToKm, z / Constants::MetersToKm, direction);
};
double MetricGUI::GetSpeed(Vehicle &v) 
{
    return v.GetCurrentSpeed()*Constants::MpsToKph; 
};
void MetricGUI::SetSpeedLimit(Vehicle &v, double speed ) 
{ 
    v.SetDesiredSpeed(speed /Constants::MpsToKph);
};

//Constants.cpp 
const double Constants::AccRate=3.5;
const double Constants::AccRateEmpty = 2.5;     // Acceleration rate for light trucks in m/s
const double Constants::AccRateFull = 1.0;      // Acceleration rate for heavy trucks in m/s
const double Constants::DecRate = 7.0;          // Braking rate for cars in m/s
const double Constants::DecRateEmpty = 5.0;     // Braking rate for light trucks in m/s
const double Constants::DecRateFull = 2.0;      // Braking rate for light trucks in m/s
const double Constants::MpsToMph = 2.237;
const double Constants::MpsToKph = 3.6;
const double Constants::MetersToMiles = 0.000621371;
const double Constants::MetersToKm = 0.001;
const int Constants::CharMapSize = 40; // hw6
const double Constants::WorldSize = 200.0;

// Conversions.cpp 
int Conversions::WCpointToCCpoint(double val)
{
    return (int)(val * (Constants::CharMapSize / Constants::WorldSize) + (Constants::CharMapSize / 2));
};
int Conversions::WClengthToCClength(double val)
{
    return (int)(val * (Constants::CharMapSize / Constants::WorldSize));
};

// Map.cpp 
Map::Map(){}

void Map::AddRoad(Road road) {
    roads.push_back(road);
}

void Map::Print(IPrintDriver* pd, Container* o) // Object = Container
{
    for (std::vector<Road>::iterator it = roads.begin(); it != roads.end(); ++it) {
		it->Print(pd, o);
	}
}

// Road.cpp 
Road::Road(std::string streetName, double locX, double locY, double len, Heading hdg)
{
    name = streetName;
    length = len;
    heading = hdg;
    xlocation = locX;
    ylocation = locY;
    NumOfRoads++;
}

// Hm7 Parser 
Road::Road(){}; // Add default constructor 
void Road::InitRoad(std::string streetName, double locX, double locY, double len, Heading hdg)
{
    name = streetName;
    length = len;
    heading = hdg;
    xlocation = locX;
    ylocation = locY;
}
double Road::GetLength() { return length; }

double Road::GetXLocation() { return xlocation; }

double Road::GetYLocation() { return ylocation; }

Heading Road::GetHeading() { return heading; }

std::string Road::GetRoadName() { return name; }

void Road::Print(IPrintDriver* print, Container* o) // Obj = Continaer
{
    print->PrintRoad(this, o);
}

// SUI.cpp 
CharMatrix::CharMatrix()
{
    for (int i = 0; i < Constants::CharMapSize; i++)
    {
        std::vector<char> tempVec;
        for (int j = 0; j < Constants::CharMapSize; j++) {
            tempVec.push_back(' ');
        }
        map.push_back(tempVec);
    }
}

void ConsolePrint::PrintRoad(Road* road, Container* o) 
{
    CharMatrix* cm = dynamic_cast<CharMatrix*>(o);
    int x, y;
    int CCx = Conversions::WCpointToCCpoint(road->GetXLocation());
    int CCy = Conversions::WCpointToCCpoint(-road->GetYLocation());
    int distance = 0;
    int CCRoadLength = Conversions::WClengthToCClength(road->GetLength());
    switch (road->GetHeading())
    {
        case North:
            x = (int)CCx;
            if (x >= 0 && x < Constants::CharMapSize) {
                while (distance < CCRoadLength) {
                    y = (int)(CCy - distance);
                    if (y >= 0 && y < Constants::CharMapSize){
                        cm->map[y][x] = '|';
                        cm->map[y][x + 2] = '|';
                        cm->map[y][x + 4] = '|';
                    }
                    distance += 1;
                }
            }
            break;
        case South:
            break;
        case East:
            y = (int)CCy;
            if (y >= 0 && y < Constants::CharMapSize){
                while (distance < CCRoadLength){
                    x = (int)(CCx + distance);
                    if (x >= 0 && x < Constants::CharMapSize){
                        cm->map[y][x] = '-';
                        cm->map[y + 2][x] = '-';
                        cm->map[y + 4][x] = '-';
                    }
                    distance += 1;
                }
            }
            break;
        case West:
            break;
        default:
            break;
    }
}

void ConsolePrint::PrintCar(Car* car, Container* o) {};

// Homework 7 
void Map::Save(ISaveDriver *sd, std::ostream& stream) {
	sd->SaveMap(this, stream);
}
void Map::Load(ILoadDriver *ld, std::istream& stream) {
	ld->LoadMap(this, stream);
}
// Hm7 for Parser 
std::vector<Road> Map::GetRoads(){
    return roads;
};

// In Road
void Road::Save(ISaveDriver *sd, std::ostream& stream)
{
	sd->SaveRoad(this, stream);
}
void Road::Load(ILoadDriver *ld, std::istream& stream)
{
	ld->LoadRoad(this, stream);
}

void JsonMapLoad::LoadMap(Map *map, std::istream& stream)
{
	std::string identifier;
	char symbol;
	stream >> symbol;
	if (symbol != '{') return;

	do {
		identifier = "";
		GetString(&identifier, stream);
		stream >> symbol;
		if (symbol != ':') return;
		if (identifier == "Roads")
		{
			stream >> symbol;
			if (symbol != '[') return;
			do
			{
				Road r;
				r.Load(this, stream);
				map->AddRoad(r);
				stream >> symbol;
			} while (symbol == ',');
		}
		stream >> symbol;
	} while (symbol == ',');
	if (symbol != '}') return;
}
bool JsonMapLoad::GetString(std::string * str, std::istream& stream){
    char x;
    std::string temp;
    stream >> x;
    if (x != '"') return false; // first must have opening quotes, throw away
    while(stream>>x){
        // stream>>x;
        if(x=='"') 
        {
            *str = temp; //save temp string into reference parameter
            if (temp=="Name" ||  temp=="Length" ||  temp=="XLocation"||  temp=="YLocation"||  temp=="Heading")
                return true;
            else return false;
        }
        else temp+=x; //save chars to temp string
    }
    return false;
};

// load the map into memory from json map (stream)
// and save into the road parameter object
void JsonMapLoad::LoadRoad(Road *road, std::istream& stream)
{
    // these variables will be loaded in by the stream below
	std::string identifier, roadName;
	double xLocation, yLocation, length;
	Heading heading;
	char symbol;
    // first load a symbol
	stream >> symbol;
    // the first symbol must be a brace, so check
	if (symbol != '{') return;
	do {
        // after brace, there should be key/identifier next in the stream
		identifier = "";
        // if not, it is empty or incorrectly formatted, this returns False, exit. 
        // Else identifier has been filled with a data member key 
		if (!GetString(&identifier, stream)) return; 
        // After key comes colon 
		stream >> symbol;
		if (symbol != ':') return;
        // Name might be more than one word, so may do this more 
		if (identifier == "Name") GetString(&roadName, stream);
        // these are numbers; doubles 
		else if (identifier == "Length") stream >> length;
		else if (identifier == "XLocation") stream >> xLocation;
		else if (identifier == "YLocation") stream >> yLocation;
        // type enum 
		else if (identifier == "Heading")
		{
			int hdg;
			stream >> hdg;
			heading = (Heading)hdg;
		}
		else return;
		stream >> symbol;
	} while (symbol == ',');
	if (symbol != '}') return;
    // these variables have been populated by the stream
	road->InitRoad(roadName, xLocation, yLocation, length, heading);
}
void JsonMapSave::SaveMap(Map *map, std::ostream& stream)
{
	stream << "{";
	stream << "\"Roads\":";
	stream << "[";
	std::vector<Road> roads = map->GetRoads();
	for (std::vector<Road>::iterator it = roads.begin(); it != roads.end(); ++it) {
		it->Save(this, stream);
		if((it+1) != roads.end()) 
            stream << ",";
	}
	stream << "]}";
}
void JsonMapSave::SaveRoad(Road *road, std::ostream& stream)
{
	stream << "{";
	stream << "\"Name\":\"" << road->GetRoadName() << "\",";
	stream << "\"Length\":" << road->GetLength() << ",";
	stream << "\"XLocation\":" << road->GetXLocation() << ",";
	stream << "\"YLocation\":" << road->GetYLocation() << ",";
	stream << "\"Heading\":" << road->GetHeading();
	stream << "}";
}


// In C++
int main() {

	GUI *simInput;
	Map map;
	IPrintDriver *cp = new ConsolePrint();
	ISaveDriver *sd = new JsonMapSave();
	ILoadDriver *ld = new JsonMapLoad();

	// Load in map
	std::ifstream loadfile;
    loadfile.open("MyMap.json");
	map.Load(ld, loadfile);

	// Display map
	CharMatrix *cm = new CharMatrix();
	map.Print(cp, cm);
	for (int i = 0; i < Constants::CharMapSize; i++) {
		std::string s = "";
		for (int j = 0; j < Constants::CharMapSize; j++) {
			s = s + cm->map[i][j];
		}
		std::cout << s << std::endl;
	}
	// Save map
	std::ofstream savefile;
    savefile.open("NewMap.json");
	map.Save(sd, savefile);
    return 0;
}



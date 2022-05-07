#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "Program.h"

// Vehicle.cpp 
void Vehicle::SetCurrentSpeed(double speed) {
    if(currentSpeed <= speed) { // accelerating
        if (speed > desiredSpeed) currentSpeed = desiredSpeed;
        else currentSpeed = speed;
    }
    else { // braking
        if (speed < desiredSpeed) currentSpeed = desiredSpeed;
        else currentSpeed = speed;
    }
}
double Vehicle::GetCurrentSpeed(){return currentSpeed;}
void Vehicle::SetDesiredSpeed(double mph) {desiredSpeed = mph;}
void Vehicle::UpdateSpeed(int seconds) {
    if (currentSpeed > desiredSpeed) Decelerate(seconds);
    else if (currentSpeed < desiredSpeed) Accelerate(seconds);
}
// Car Class 
void Car::Accelerate(int secondsDelta) {
    SetCurrentSpeed(GetCurrentSpeed()+Constants::AccRate*secondsDelta);
}
void Car::Decelerate(int secondsDelta) {
    SetCurrentSpeed(GetCurrentSpeed()-Constants::AccRate*secondsDelta);
}
// Truck Class 
Truck::Truck(int weight){loadWeight = weight;}
void Truck::Accelerate(int secondsDelta) { // keyword override in header file, not here 
    if (loadWeight <= 5) SetCurrentSpeed(GetCurrentSpeed()+Constants::AccRateEmpty*secondsDelta); 
    else SetCurrentSpeed(GetCurrentSpeed()+Constants::AccRateFull*secondsDelta);
}
void Truck::Decelerate(int secondsDelta){
    if (loadWeight <= 5) SetCurrentSpeed(GetCurrentSpeed()-Constants::DecRateEmpty*secondsDelta);
    else SetCurrentSpeed(GetCurrentSpeed()-Constants::DecRateFull*secondsDelta);
}


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
int Conversions::WCpointToCCpoint(double val){
    return (int)(val * (Constants::CharMapSize / Constants::WorldSize) + (Constants::CharMapSize / 2));
};
int Conversions::WClengthToCClength(double val){
    return (int)(val * (Constants::CharMapSize / Constants::WorldSize));
};


// Map.cpp 
Map::Map(){}
void Map::AddRoad(Road road) {roads.push_back(road);}
void Map::Print(IPrintDriver* pd, Container* o) {
    for (std::vector<Road>::iterator it = roads.begin(); it != roads.end(); ++it)
		it->Print(pd, o);
}
void Map::Save(ISaveDriver *sd, std::ostream& stream) {sd->SaveMap(this, stream);}
void Map::Load(ILoadDriver *ld, std::istream& stream) {ld->LoadMap(this, stream);}
std::vector<Road> Map::GetRoads(){return roads;};


// Road.cpp 
Road::Road(){}; 
Road::Road(std::string streetName, double locX, double locY, double len, Heading hdg) {
    name = streetName;
    length = len;
    heading = hdg;
    xlocation = locX;
    ylocation = locY;
    NumOfRoads++;
}
void Road::InitRoad(std::string streetName, double locX, double locY, double len, Heading hdg) {
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
void Road::Print(IPrintDriver* print, Container* o) {print->PrintRoad(this, o);}
void Road::Save(ISaveDriver *sd, std::ostream& stream){sd->SaveRoad(this, stream);}
void Road::Load(ILoadDriver *ld, std::istream& stream){ld->LoadRoad(this, stream);}

// week 12 param anonoymous item container(?)
void Road::AddRoadItem(RoadItem *ri){}; 


// SUI.cpp 
CharMatrix::CharMatrix(){
    for (int i = 0; i < Constants::CharMapSize; i++){
        std::vector<char> tempVec;
        for (int j = 0; j < Constants::CharMapSize; j++) 
            tempVec.push_back(' ');
        map.push_back(tempVec);
    }
}

// Imperial Class 
Road ImperialGUI::CreateRoad(std::string name, double x, double y, double z, Heading direction) {
    return Road(name, x / Constants::MetersToMiles, y / Constants::MetersToMiles, z / Constants::MetersToMiles, direction);
};
double ImperialGUI::GetSpeed(Vehicle &v) {
    return v.GetCurrentSpeed()*Constants::MpsToMph; 
};
void ImperialGUI::SetSpeedLimit(Vehicle &v, double speed) { 
    v.SetDesiredSpeed( speed /Constants::MpsToMph );
};
SpeedLimit ImperialGUI::CreateSpeedLimit(double speed, double location){};
StopSign ImperialGUI::CreateStopSign(double location) {};

// Metric Class 
Road MetricGUI::CreateRoad(std::string name, double x, double y, double z, Heading direction){
    return Road(name, x / Constants::MetersToKm, y / Constants::MetersToKm, z / Constants::MetersToKm, direction);
};
double MetricGUI::GetSpeed(Vehicle &v) {
    return v.GetCurrentSpeed()*Constants::MpsToKph; 
};
void MetricGUI::SetSpeedLimit(Vehicle &v, double speed ) { 
    v.SetDesiredSpeed(speed /Constants::MpsToKph);
};
SpeedLimit MetricGUI::CreateSpeedLimit(double speed, double location){};
StopSign MetricGUI::CreateStopSign(double location) {};

// Class ConsolePrint
void ConsolePrint::PrintRoad(Road* road, Container* o) {
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
// Class JsonMapLoad 
// load the map into memory from json map (stream)
// and save into the road parameter object
void JsonMapLoad::LoadRoad(Road *road, std::istream& stream) {
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
void JsonMapLoad::LoadMap(Map *map, std::istream& stream) {
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
void JsonMapLoad::LoadStopSign(StopSign *roadItem, std::ostream& stream){};
void JsonMapLoad::LoadSpeedLimit(SpeedLimit *roadItem, std::ostream& stream){};

// class JsonMapSave
void JsonMapSave::SaveMap(Map *map, std::ostream& stream) {
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
void JsonMapSave::SaveRoad(Road *road, std::ostream& stream) {
	stream << "{";
	stream << "\"Name\":\"" << road->GetRoadName() << "\",";
	stream << "\"Length\":" << road->GetLength() << ",";
	stream << "\"XLocation\":" << road->GetXLocation() << ",";
	stream << "\"YLocation\":" << road->GetYLocation() << ",";
	stream << "\"Heading\":" << road->GetHeading();
	stream << "}";
}
void JsonMapSave::SaveStopSign(StopSign *roadItem, std::ostream& stream){};
void JsonMapSave::SaveSpeedLimit(SpeedLimit *roadItem, std::ostream& stream){};


// RoadItem.cpp 
// class RoadItem 
double RoadItem::GetMileMarker(){
    return mileMarker;
};
void RoadItem::SetMileMarker(double distance){
    mileMarker = distance;
};

// class StopSign 
void StopSign::Save(ISaveDriver *sd, std::ostream& stream){};

// class SpeedLimit
double SpeedLimit::GetSpeedLimit(){};
void SpeedLimit::Save(ISaveDriver *sd, std::ostream& stream) {};

// class RoadItemsElement 
RoadItemsElement::RoadItemsElement(){};
void RoadItemsElement::AddNext(RoadItem *roadItem){};
void RoadItemsElement::AddPrev(RoadItem *roadItem){};
RoadItem * RoadItemsElement::GetRoadItem(){};
RoadItemsElement * RoadItemsElement::GetNext(){};
RoadItemsElement * RoadItemsElement::GetPrev(){};
void RoadItemsElement::AddNew (RoadItem * roadItem) {};

  


// FINAL WEEK 
// class Traffic Light 
TrafficLight::TrafficLight(int greenTime, int yellowTime, int redTime, char startColor, double mileMarker)
{
    greenTime=greenTime;
    yellowTime=yellowTime;
    redTime=redTime;
    startColor='g';
    mileMarker=mileMarker;
};
  

// Method: override void Update(int seconds)
// Increments timeOn by seconds
// Checks to see if it is time to change the light (and does it)
// Print the current color of the light
// { green=0, yellow=1, red=2 }
void TrafficLight::Update(int seconds) {
    timeOn+=1;
    std::cout<< "light is " << startColor << std::endl;
    if (startColor == 'g' ) { 
        if(timeOn >= redTime) {
            std::cout<< "light is green "<< std::endl; 
            startColor='y'; // switch to yellow
            timeOn=0; // reset time
        }
    } // yellow
    else if( startColor == 'y'){ 
        if(timeOn >= greenTime){
            startColor='r'; // switch to red
            timeOn=0; // reset time
        }
        std::cout<< "light is yellow "<< std::endl; 
        return;
    } // red
    else if(startColor == 'r' ) { 
        std::cout<< "light is red "<< std::endl; 
        if(timeOn >= yellowTime){
            startColor='g'; // back to green
            timeOn=0; // reset time
        }
    }else{
        std::cout << "the light is broken today" << std::endl;
    }
}
void TrafficLight::Save(ISaveDriver *sd, std::ostream& stream) {};



// class Simulation 
// Method: void AddDynamicRoadItem(DynamicRoadItem) 
// Adds entry to list
void Simulation::AddDynamicRoadItem(DynamicRoadItem* d){
    items.push_back(d);
};
// Method: void Update(int seconds) 
// Iterates through list of DynamicRoadItems sending each an Update message
void Simulation::Update(int seconds){
    for(auto r : items){ 
        r->Update(seconds);
    }
};


// FINAL MAIN 
// In your main program
int main( ){
    GUI *simInput;
    simInput = new MetricGUI();

    IPrintDriver *cp = new ConsolePrint();
	ISaveDriver *sd = new JsonMapSave();
	ILoadDriver *ld = new JsonMapLoad();

    // Load in map: (used existing from Homework 7)
	std::ifstream loadfile;
    loadfile.open("MyMap.json");
    Map map;
	map.Load(ld, loadfile);

    // Instantiate a simulator
    // Instantiate a TrafficLight with (7,2,5,green,0.0)
    // Instantiate a second TrafficLight with (7,2,5,red,0.0)
    Simulation *sm = new Simulation();
    TrafficLight *t1 =new TrafficLight(7,2,5,0,0); // { green =0, yellow=1, red=2}
    TrafficLight *t2= new TrafficLight(7,2,5,2,0); //  in the fourth parameter slot 

    
    // Add both lights to the simulator
    sm->AddDynamicRoadItem(t1);
    sm->AddDynamicRoadItem(t2);

    // Iterate through a loop 20 times with
    // simulation.Update(1)
    for ( int i=0; i<20; i++){
        sm->Update(1);
    }
        
    Road Uptown = simInput->CreateRoad("Uptown", 0.0, -0.09, .180, North);
    map.AddRoad(Uptown);
    Road Crosstown = simInput->CreateRoad("Crosstown", -0.09, 0.0, .180, East);
    map.AddRoad(Crosstown);
    StopSign sign = simInput->CreateStopSign(.01);
    Crosstown.AddRoadItem(&sign);
    StopSign sign2 = simInput->CreateStopSign(.23);
    Uptown.AddRoadItem(&sign2);
    StopSign sign3 = simInput->CreateStopSign(.32);
    Uptown.AddRoadItem(&sign3);
    StopSign sign4 = simInput->CreateStopSign(.302);
    Uptown.AddRoadItem(&sign4);
    SpeedLimit limit = simInput->CreateSpeedLimit(80.0, .02);
    Crosstown.AddRoadItem(&limit);
    SpeedLimit limit2 = simInput->CreateSpeedLimit(50.0, .123);
    Uptown.AddRoadItem(&limit2);

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







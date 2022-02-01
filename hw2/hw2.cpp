/*
    Courtney King, OOSD Homework 2 Feb 2, 2022
    Compile: g++ -std=c++11 hw2.cpp -o hw2
*/

#include <string>
#include <vector>
#include <iostream>
#include <string>
#include "hw2.h"

using namespace std; 

void Simulation::Update(int seconds){};
void Dynamic::UpDate(int seconds){}; // **abstract function 

void Light::Update(int seconds){}; // **abstract function 
void Light::GetLightColor(){};

void Vehicle::Accelerate(int toSpeed){};
void Vehicle::Decelerate(int toSpeed) {};
void Vehicle::Turn(char direction, int degrees) {};

void Truck::SetLoadWeight(int weight) {};
double Road::GetLength(){};
string Road::GetRoadName(){};

int main() // Quick test
{
    return 0;
}



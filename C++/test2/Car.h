#pragma once
#include "Engine.h"
class Car
{
private:
	int numberOfDoors;
	int price;
	Engine* engine;
public:
	Car(Engine* eng, int numerdoors, int price) : engine{ eng }, numberOfDoors{ numerdoors }, price{ price } {};
	~Car() { delete engine; };
	double computePrice();
	string toString();
	int getNumberDoors() { return numberOfDoors; }
};


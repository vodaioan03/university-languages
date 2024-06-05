#pragma once
#include "Engine.h"
class ElectricEngine : public Engine
{
private:
	int autonomy;
public:
	ElectricEngine(int auton) : autonomy{ auton } {};
	~ElectricEngine() {};
	double getPrice();
	string toString() { return "| Electric  Autonomy " + to_string(this->autonomy) + " Price " + to_string(this->getPrice()); }

};


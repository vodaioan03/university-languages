#pragma once
#include <iostream>
#include <string>
#include <vector>


using namespace std;
class Engine
{
protected:
	double basePrice = 3000;
public:
	Engine(){};
	virtual ~Engine() {};
	virtual double getPrice() { return this->basePrice; };
	virtual string toString() = 0;
};


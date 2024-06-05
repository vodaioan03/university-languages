#pragma once
#include "Engine.h"
class TurboEngine : public Engine
{
public:
	TurboEngine(){};
	~TurboEngine() {};
	double getPrice();
	string toString() { return "| Turbo -> Price:" + to_string(this->getPrice());}
};


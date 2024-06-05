#include "Car.h"

double Car::computePrice()
{
    return this->price + this->engine->getPrice();
}

string Car::toString()
{
    return " Price:" + to_string(this->computePrice()) + " | Car doors: " + to_string(this->numberOfDoors) + " " + engine->toString();
}

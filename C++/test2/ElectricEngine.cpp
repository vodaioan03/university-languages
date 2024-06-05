#include "ElectricEngine.h"

double ElectricEngine::getPrice()
{
    return Engine::getPrice() + this->autonomy*0.01;
}

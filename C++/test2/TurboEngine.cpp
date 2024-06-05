#include "TurboEngine.h"

double TurboEngine::getPrice()
{
    return Engine::getPrice() + 100;
}

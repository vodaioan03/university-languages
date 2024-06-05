#include "Service.h"

void Service::addCar(int numberDoors, string engineType, int autonomy)
{
	Engine* engine;
	int basePrice = 7000;
	if (numberDoors == 4) basePrice = 8500;
	if (engineType.compare("Turbo") == 0) {
		engine = new TurboEngine();
	}
	else {
		engine = new ElectricEngine(autonomy);
	}
	Car* car = new Car(engine,numberDoors,basePrice);
	this->cars.push_back(car);
}

vector<Car*> Service::getCarsWithMaxPrice(double maxPrice)
{
	vector<Car*> found;
	for (auto c : this->cars) {
		if (c->computePrice() < maxPrice) {
			found.push_back(c);
		}
	}
	return found;
}

void Service::writeToFile(string filename,vector<Car*> carss)
{

	ofstream out(filename);
	vector<Car*> twoDoors;
	vector<Car*> forDoors;
	for (auto c : carss) {
		if (c->getNumberDoors() == 2) twoDoors.push_back(c);
		else forDoors.push_back(c);
	}
	out << "2 doors cars:" << endl;
	for (auto c : twoDoors) {
		out << c->toString() << endl;
	}
	out << endl << "4 doors cars:" << endl;
	for (auto c : forDoors) {
		out << c->toString() << endl;
	}
	out.close();
}

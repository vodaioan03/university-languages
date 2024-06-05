#pragma once
#include "Car.h"
#include "Engine.h"
#include "TurboEngine.h"
#include "ElectricEngine.h"
#include <fstream>
#include <string>
class Service
{
private:
	vector<Car*> cars;
public:
	Service() {};
	~Service() {
		for (auto c : cars) {
			delete c;
		}
	}
	void addCar(int numberDoors, string engineType, int autonomy);
	vector<Car*> getCarsWithMaxPrice(double maxPrice);
	vector<Car*> getAllCars() { return this->cars; }
	Car* getLastCar() { return this->cars.at(this->cars.size()-1); }
	void writeToFile(string filename, vector<Car*> carss);



	//IN PLUS
	void toLower(string& str) {
		string newstr = "";

		for (char c : str) {
			newstr += tolower(c);
		}
		str = newstr;
	}
};


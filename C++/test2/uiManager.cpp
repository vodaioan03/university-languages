#include "uiManager.h"

void uiManager::printMenu()
{
	cout << " -- Car MENU -- " << endl;
	cout << "1. Add car" << endl;
	cout << "2. Show cars" << endl;
	cout << "3. Write to file" << endl;
	cout << "0. Exit" << endl;
	cout << "Type option:";
}

void uiManager::optionProceed()
{
	string option = "";
	getline(cin, option);
	int opt = 0;
	try
	{
		opt = stoi(option);
	}
	catch (const std::exception&)
	{
		throw exception("Invalid option");
	}
	switch (opt)
	{
	case 0:
		this->isRunning = false;
		break;
	case 1:
		this->addCar();
		break;
	case 2:
		this->showAllCars();
		break;
	case 3:
		this->saveToFile();
		break;
	default:
		throw exception("Invalid option");
		break;
	}
}

void uiManager::addCar()
{
	cout << "Add car" << endl;
	string input;
	int numberDoors;
	string engineType;
	int autonomy=0;
	cout << "[1/2] Type number of doors [2/4]: ";
	getline(cin, input);
	try
	{
		numberDoors = stoi(input);
	}
	catch (const std::exception&)
	{
		throw exception("Invalid input!");
	}
	if (numberDoors != 2 && numberDoors != 4) throw exception("Invalid number of doors.");
	cout << "[2/2] Engine type: [Turbo/Electric]: ";
	getline(cin, input);
	this->service.toLower(input);
	if (input.compare("turbo") == 0) {
		engineType = "Turbo";
	}
	else if (input.compare("electric") == 0) {
		engineType = "Electric";
		cout << "[1/1] Type autonomy[INTEGER]: ";
		getline(cin, input);
		try
		{
			autonomy = stoi(input);
		}
		catch (const std::exception&)
		{
			throw exception("Invalid autonomy!");
		}
	}
	this->service.addCar(numberDoors, engineType, autonomy);
	Car* lastcar = this->service.getLastCar();
	cout << lastcar->toString() << endl;
	
}

void uiManager::showAllCars()
{
	vector<Car*> carss = this->service.getAllCars();
	if (carss.size() == 0) throw exception("No cars found!");
	cout << "We found " + to_string(carss.size()) + " cars! " << endl;
	int index = 0;
	for (auto c : carss) {
		cout << to_string(index) + ". " + c->toString() << endl;
		index++;
	}
}

void uiManager::saveToFile()
{
	string filename;
	double maxPrice;
	cout << "[1/2]Type file name:";
	getline(cin, filename);
	cout << "[2/2]Type max price:";
	string input;
	getline(cin, input);
	try
	{
		maxPrice = stod(input);
	}
	catch (const std::exception&)
	{
		throw exception("Invalid maxPrice inserted.");
	}
	vector<Car*> carss = this->service.getCarsWithMaxPrice(maxPrice);
	this->service.writeToFile(filename,carss);
	cout << "Cars are in file!" << endl;
}

void uiManager::addInputs()
{

	this->service.addCar(2, "Electric", 20);
	this->service.addCar(2, "Turbo", 0);
	this->service.addCar(4, "Electric", 100);
	this->service.addCar(4, "Turbo", 0);
	this->service.addCar(4, "Electric", 140);
	this->service.addCar(4, "Electric", 2300);
}

void uiManager::start()
{
	this->isRunning = true;
	this->addInputs();
	while (this->isRunning) {
		try
		{
			this->printMenu();
			this->optionProceed();
		}
		catch (const std::exception& e)
		{
			cout << "ERROR: " << e.what() << endl;
		}
		
	}
}

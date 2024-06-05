#pragma once
#include "Service.h"
#include "Engine.h"
#include "TurboEngine.h"
#include "ElectricEngine.h"
class uiManager
{
private:
	Service& service;
	bool isRunning = true;
	void printMenu();
	void optionProceed();
	void addCar();
	void showAllCars();
	void saveToFile();
	void addInputs();
public:
	uiManager(Service& service) : service{ service } {};
	~uiManager() {};
	void start();
};


#pragma once
#include "Dog.h"
#include "Service.h"
#include <iostream>
#include <string>
using namespace std;
class managerUI
{

private:
	Service managerService = Service();
	string loggedAs = "0";

public:
	managerUI();
	~managerUI();
	void printLoginMenu();
	void printUserMenu();
	void addDogOption();
	void addInputs();
	void deleteDogOption();
	void updateDogOption();
	void showAllDogs();
	void showMenuDog(int indexDog);
	void showDogsForUser(int& exited, int& disconnected);
	void showDogsForUser();
	void searchDogByBreedAge();
	void showAllAdoptedDogs();
	void printAdminMenu();
	int startUI();
};


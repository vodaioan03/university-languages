#pragma once
#include "Dog.h"
#include "Service.h"
#include "Exceptions.h"
#include "utils.h"
#include "Verifications.h"
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class managerUI
{

private:
	Service managerService;
	string loggedAs = "0";
	Verifications verify{};

public:
	/// <summary>
	/// Construct for managerUI
	/// </summary>
	managerUI();
	managerUI(const Service& service);
	/// <summary>
	/// Destructor for managerUI
	/// </summary>
	~managerUI();
	/// <summary>
	/// Function for print login menu
	/// </summary>
	void printLoginMenu();
	/// <summary>
	/// Function for print user menu
	/// </summary>
	void printUserMenu();
	/// <summary>
	/// Function input for  add dog
	/// </summary>
	void addDogOption();
	/// <summary>
	/// Input for hard coded values
	/// </summary>
	void addInputs();
	/// <summary>
	/// Delete dog input UI
	/// </summary>
	void deleteDogOption();
	/// <summary>
	/// Update dog input UI
	/// </summary>
	void updateDogOption();
	/// <summary>
	/// Show all dogs not addopted
	/// </summary>
	void showAllDogs();
	/// <summary>
	/// Show menu dog for user
	/// </summary>
	/// <param name="indexDog"></param>
	void showMenuDog(int indexDog);
	/// <summary>
	/// Show all dogs for user
	/// </summary>
	/// <param name="exited"></param>
	/// <param name="disconnected"></param>
	void showDogsForUser(int& exited, int& disconnected);
	/// <summary>
	/// Search input dog by breed and age
	/// </summary>
	void searchDogByBreedAge();
	/// <summary>
	/// Show list of addopted dogs
	/// </summary>
	void showAllAdoptedDogs();
	/// <summary>
	/// Print admin menu
	/// </summary>
	void printAdminMenu();

	void chooseRepo();
	/// <summary>
	/// Function for startui
	/// </summary>
	/// <returns>int exited - value of exit</returns>
	int startUI();
};


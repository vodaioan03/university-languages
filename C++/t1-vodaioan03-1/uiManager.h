#pragma once
#include <iostream>
#include <assert.h>
#include "model.h"
#include "service.h"
using namespace std;
class uiManager
{
private:
	service serviceManager{};
	bool isRunning = true;
public:

	void testtsAdd();
	void testsSearch();
	void inputSchools();
	void addSchool();
	void showSchools();
	void closestSchools();
	void printMenu();
	void optionProceed();
	void start();
};


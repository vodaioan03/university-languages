#pragma once
#include <iostream>
#include <algorithm>
#include "model.h"
#include "repository.h"

using namespace std;
class service
{
private:
	repository repo{};
public:

	/// <summary>
	///  Add school by params. Create new model.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="address"></param>
	/// <param name="date"></param>
	void addSchool(string name, string longitutde, string latitude, string date);

	/// <summary>
	/// Find school by given params
	/// </summary>
	/// <param name="longitude"></param>
	/// <param name="latitude"></param>
	/// <param name="indexes"></param>
	void findSchools(string longitude, string latitude, vector<model>& indexes);

	int getSizeOfSchools();

	model getElemt(int position);

	string getStringForElem(int position);
};


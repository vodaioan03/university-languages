#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "model.h"

using namespace std;
class repository
{
private:
	vector<model> elems;
public:
	/// <summary>
	/// Add a given element in vector.
	/// </summary>
	/// <param name="elem"></param>
	void addElement(model elem);
	model getElement(int position);
	int getSize();

};


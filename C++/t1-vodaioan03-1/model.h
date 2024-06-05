#pragma once
#include <iostream>
#include <string>

using namespace std;
class model
{
private:
	string name;
	string address;
	string date;
	string longitutde;
	string latitude;

public:
	model(string name, string longitude, string latitude, string date);

	void setName(string name);
	string getName();
	void setAdress(string address);
	string getAddress();
	void setDate(string date);
	string getDate();
	string getLongitutde();
	string getLatitude();

	string toString();
};


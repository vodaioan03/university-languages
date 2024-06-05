#include "model.h"

model::model(string name, string longitutde, string latitude, string date)
{
	this->setName(name);
	this->longitutde = longitutde;
	this->latitude = latitude;
	this->address = longitutde + ", " + latitude;
	this->setDate(date);
}

void model::setName(string name)
{
	this->name = name;
}

string model::getName()
{
	return this->name;
}

void model::setAdress(string address)
{
	this->address = address;
}

string model::getAddress()
{
	return this->address;
}

void model::setDate(string date)
{
	this->date = date;
}

string model::getDate()
{
	return this->date;
}

string model::getLongitutde()
{
	return this->longitutde;
}

string model::getLatitude()
{
	return this->latitude;
}

string model::toString()
{
	return "Name: " + this->name + " | " + this->address + " | " + this->date + " ";
}

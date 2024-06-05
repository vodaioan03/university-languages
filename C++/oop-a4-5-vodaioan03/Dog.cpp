#include "Dog.h"

Dog::Dog()
{
	this->setName("Unknown");
	this->setBreed("Unknown");
	this->setAge(0);
	this->setPhotograph("Unknown");
	this->setAdopted(false);
}

Dog::Dog(string breed, string name, int age, string photograph)
{
	this->setName(name);
	this->setBreed(breed);
	this->setAge(age);
	this->setPhotograph(photograph);
	this->setAdopted(false);
}

Dog::~Dog() {
}

bool Dog::getAdopted()
{
	return this->adopted;
}

void Dog::setAdopted(bool adopt)
{
	this->adopted = adopt;
}

string Dog::getBreed()
{
	return this->breed;
}

void Dog::setBreed(string breed)
{
	this->breed.assign(breed);
}

string Dog::getName()
{
	return this->name;
}

void Dog::setName(string name)
{
	this->name.assign(name);
}

int Dog::getAge() {
	return this->age;
}
void Dog::setAge(int age)
{
	this->age = age;
}

string Dog::getPhotograph()
{
	return this->photograph;
}

void Dog::setPhotograph(string photograph)
{
	this->photograph.assign(photograph);
}

string Dog::dogToString()
{
	string forPrint;
	forPrint.assign("Name: "+this->getName() + " | Breed: " + this->getBreed() + " | Age: " + to_string(this->getAge()) + " | Photograph: " + this->getPhotograph());
	return forPrint;
}

string Dog::dogShow() {
	string forPrint;
	forPrint.assign("Name: " + this->getName() + "\nBreed: " + this->getBreed() + " \nAge: " + to_string(this->getAge()) + " \nPhotograph: " + this->getPhotograph());
	return forPrint;
}

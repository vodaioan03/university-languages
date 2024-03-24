#include "Repository.h"

Repository::Repository()
{
}

Repository::~Repository()
{
}

void Repository::addDog(Dog dogAdd)
{
	this->dogs.addElement(dogAdd);
}

void Repository::deleteDog(Dog dogDelete)
{
	this->dogs.deleteElement(dogDelete);
}
void Repository::deleteAddoptedDog(Dog dogDelete)
{
	this->addoptions.deleteElement(dogDelete);
}

void Repository::updateDog(Dog &dogUpdate, string newName, string newBreed, int newAge, string newPhotograph) {
	dogUpdate.setAge(newAge);
	dogUpdate.setName(newName);
	dogUpdate.setBreed(newBreed);
	dogUpdate.setPhotograph(newPhotograph);
	cout << dogUpdate.dogToString() << endl;
}

Dog* Repository::searchDogByIndex(int index)
{
	return this->dogs.getElemById(index);
}

Dog* Repository::getDogForUpdate(string name, string breed)
{
	return this->dogs.getElemForUpdate(name,breed);
}

Dog* Repository::getAddoptedDogForUpdate(string name, string breed)
{
	return this->addoptions.getElemForUpdate(name, breed);
}

Dog* Repository::getAllElements()
{
	return this->dogs.getAllElements();
}

int Repository::getSizeOfDogs() {
	return this->dogs.getSize();
}

Dog* Repository::getAllElementsAddopted()
{
	return this->addoptions.getAllElements();
}

int Repository::getSizeOfDogsAddopted() {
	return this->addoptions.getSize();
}

void Repository::addoptDog(string name, string breed) {
	Dog dogForMove = *this->dogs.getElemForUpdate(name, breed);
	this->dogs.deleteElement(dogForMove);
	this->addoptions.addElement(dogForMove);

}

void Repository::addoptDog(int index) {
	Dog dogForMove = *this->dogs.getElemById(index);
	this->dogs.deleteElement(dogForMove);
	this->addoptions.addElement(dogForMove);

}

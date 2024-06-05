#include "Repository.h"

void Repository::addDog(Dog dogAdd)
{
	this->dogs.push_back(dogAdd);
}

void Repository::deleteDog(Dog dogDelete)
{
	int positionForDelete = this->getPositionForDog(dogDelete);
	this->dogs.erase(this->dogs.begin() + positionForDelete);
}
void Repository::deleteAddoptedDog(Dog dogDelete)
{
	int positionForDelete = this->getPositionForAddoptedDog(dogDelete);
	this->addoptions.erase(this->addoptions.begin() + positionForDelete);
}

void Repository::updateDog(Dog &dogUpdate, string newName, string newBreed, int newAge, string newPhotograph) {
	dogUpdate.setAge(newAge);
	dogUpdate.setName(newName);
	dogUpdate.setBreed(newBreed);
	dogUpdate.setPhotograph(newPhotograph);
}

Dog* Repository::searchDogByIndex(int index)
{
	if (index < 0 || index > this->dogs.size()) return NULL;
	return &this->dogs[index];
}

Dog* Repository::getDogForUpdate(string name, string breed)
{
	Dog found{};
	for (Dog as : this->dogs) {
		if(compareLower(as.getName(),name) && compareLower(as.getBreed(),breed)){
			return &this->dogs[this->getPositionForDog(as)];
		}
	}
	return NULL;
}

Dog Repository::getAddoptedDogForUpdate(string name, string breed)
{
	vector<Dog> dogsFound;
	copy_if(this->addoptions.begin(), this->addoptions.end(), back_inserter(dogsFound), [&](Dog& dog) {return isDogAddopted(dog, name, breed); });
	if (dogsFound.size() == 0) throw Exceptions().dogNotExist();
	return dogsFound[0]; 
}

vector<Dog> Repository::getAllElements()
{
	return this->dogs;
}

int Repository::getSizeOfDogs() {
	return this->dogs.size();
}

vector<Dog> Repository::getAllElementsAddopted()
{
	return this->addoptions;
}

vector<Dog> Repository::getAllElementsAddoptedPrint()
{
	return this->addoptions;
}

int Repository::getSizeOfDogsAddopted() {
	return this->addoptions.size();
}

void Repository::addoptDog(string name, string breed) {
	auto it = find_if(this->dogs.begin(), this->dogs.end(), [&](Dog& as) {
		return compareLower(as.getName(), name) && compareLower(as.getBreed(), breed);
		});

	if (it != this->dogs.end()) {
		Dog found = *it;
		this->dogs.erase(it);
		this->addoptions.push_back(found);
	}
}

void Repository::addoptDog(int index) {
	Dog dog = this->dogs[index];
	this->dogs.erase(this->dogs.begin() + index);
	this->addoptions.push_back(dog);
	dog.setAdopted(true);
}

int Repository::getPositionForDog(Dog elem)
{
	int index = 0;
	for(Dog as: this->dogs) {
		if (as == elem) {
			return index;
		}
		index++;
	}
	throw Exceptions().dogsNotFound();
}

int Repository::getPositionForAddoptedDog(Dog elem)
{
	int index = 0;
	for (Dog as : this->addoptions) {
		if (as == elem) {
			return index;
		}
		index++;
	}
	throw Exceptions().dogNotExist();
}

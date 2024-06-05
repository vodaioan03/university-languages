#include "Service.h"


Service::Service(VirtualRepo* repository)
{
	this->repo = repository;
}

Service::Service()
{
}

Service::~Service()
{

}

void Service::addDog(string name, string breed, string age, string photograph) {
	int ageToAdd = stoi(age);
	this->repo->addDog(Dog(breed,name,ageToAdd,photograph));
}

void Service::deleteDog(string name, string breed) {
	this->repo->deleteDog(*this->repo->getDogForUpdate(name,breed));
}

void Service::deleteDogAddopted(string name, string breed) {
	this->repo->deleteAddoptedDog(this->repo->getAddoptedDogForUpdate(name, breed));
}

void Service::updateDog(string name, string breed, string newName, string newBreed, string newAge, string newPhotograph) {
	
	int ageUpdate = stoi(newAge);
	this->repo->updateDog(*this->repo->getDogForUpdate(name, breed), newName, newBreed, ageUpdate,newPhotograph);

}




vector<Dog> Service::getAllElementsNotAddopted() {
	return this->repo->getAllElements();
}

int Service::getSizeForDogsNotAddopted() {
	return this->repo->getSizeOfDogs();
}

vector<Dog> Service::getAllElementsAddopted() {
	return this->repo->getAllElementsAddopted();
}

vector<Dog> Service::getAllElementsAddoptedPrint() {
	return this->repo->getAllElementsAddoptedPrint();
}


int Service::getSizeForDogsAddopted() {
	return this->repo->getSizeOfDogsAddopted();
}

void Service::addoptDog(string name, string breed) {
	if (this->repo->getDogForUpdate(name, breed) == NULL) throw Exceptions().invalidBreedName();
	this->repo->addoptDog(name, breed);
}

void Service::addoptDog(int index) {
	this->repo->addoptDog(index);
}


bool isAgeLessThan(Dog& dog, int ageInt) {
	return dog.getAge() < ageInt;
}



void Service::searchDogByBreedAge(vector<Dog>& indexes, string breed, string age) {
	int ageInt = stoi(age);
	vector<Dog> allDogs = this->getAllElementsAddopted();
	if (breed.compare("") == 0) {
		copy_if(allDogs.begin(), allDogs.end(), back_inserter(indexes), [&](Dog& dog) {return isAgeLessThan(dog, ageInt); });
	}
	else {
		copy_if(allDogs.begin(), allDogs.end(), back_inserter(indexes), [&](Dog& dog) {return isDogFound(dog, ageInt,breed); });
	}

}

Dog* Service::searchDogByIndex(int indexSearch) {
	if (indexSearch >= this->repo->getSizeOfDogs()) throw Exceptions().invalidIndex();
	return this->repo->searchDogByIndex(indexSearch);
}
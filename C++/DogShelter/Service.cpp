#include "Service.h"

Service::Service()
{
}

Service::~Service()
{
}

bool Service::verifyDogExist(string nameVerify, string breedVerify){
	if (this->repo.getDogForUpdate(nameVerify, breedVerify) != NULL) return true;
	return false;
}
bool Service::verifyAddoptedDogExist(string nameVerify, string breedVerify) {
	if (this->repo.getAddoptedDogForUpdate(nameVerify, breedVerify) != NULL) return true;
	return false;
}

bool Service::validAge(string age) {
	delSpaces(age);
	int counter = 0;
	for (char& c : age) {
		if (!isdigit(c)) return false;
		else counter++;
	}
	if (counter == 0 || counter > 2) return false;

	return true;
}


void Service::addDog(string name, string breed, string age, string photograph) {
	int ageToAdd = stoi(age);
	this->repo.addDog(Dog(breed,name,ageToAdd,photograph));
}

void Service::deleteDog(string name, string breed) {
	this->repo.deleteDog(*this->repo.getDogForUpdate(name,breed));
}

void Service::deleteDogAddopted(string name, string breed) {
	this->repo.deleteAddoptedDog(*this->repo.getAddoptedDogForUpdate(name, breed));
}

void Service::updateDog(string name, string breed, string newName, string newBreed, string newAge, string newPhotograph) {
	
	int ageUpdate = stoi(newAge);
	this->repo.updateDog(*this->repo.getDogForUpdate(name, breed), newName, newBreed, ageUpdate,newPhotograph);

}

bool Service::verifyAddopt(string name, string breed) {
	if(this->repo.getAddoptedDogForUpdate(name, breed) == NULL) return false;
	return true;
}

Dog* Service::getAllElementsNotAddopted() {
	return this->repo.getAllElements();
}

int Service::getSizeForDogsNotAddopted() {
	return this->repo.getSizeOfDogs();
}

Dog* Service::getAllElementsAddopted() {
	return this->repo.getAllElementsAddopted();
}

int Service::getSizeForDogsAddopted() {
	return this->repo.getSizeOfDogsAddopted();
}

void Service::addoptDog(string name, string breed) {
	if (this->repo.getDogForUpdate(name, breed) == NULL) throw exception("Invalid breed or name.");
	this->repo.addoptDog(name, breed);
}

void Service::addoptDog(int index) {
	this->repo.addoptDog(index);
}


void Service::searchDogByBreedAge(int* indexes, int &indexIndexes, string breed, string age) {
	int ageInt = stoi(age);
	Dog* allDogs = this->getAllElementsNotAddopted();
	if (breed.compare("") == 0) {
		for (int i = 0; i < this->repo.getSizeOfDogs(); i++) {
			if (allDogs[i].getAge() < ageInt) {
				indexes[indexIndexes] = i;
				indexIndexes++;
			}
		}
	}
	else {
		for (int i = 0; i < this->repo.getSizeOfDogs(); i++) {
			if (allDogs[i].getAge() < ageInt && compareLower(breed, allDogs[i].getBreed())) {
				indexes[indexIndexes] = i;
				indexIndexes++;
			}
		}
	}

}

Dog* Service::searchDogByIndex(int indexSearch) {
	if (indexSearch >= this->repo.getSizeOfDogs()) throw exception("Index invalid!");
	return this->repo.searchDogByIndex(indexSearch);
}
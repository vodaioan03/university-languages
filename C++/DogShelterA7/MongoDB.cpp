#include "MongoDB.h"

MongoDB::MongoDB(string filename)
{
	this->file = filename;
	this->loadData();
}

void MongoDB::loadData()
{
	ifstream fin(this->file);
	string line;
	while (getline(fin, line)) {
		istringstream ss(line);
		vector<std::string> lineParse;
		string token;
		while (getline(ss, token, ',')) {
			lineParse.push_back(token);
		}
		Dog dog = Dog(lineParse[1], lineParse[0], stoi(lineParse[2]), lineParse[3]);
		if (stoi(lineParse[4]) == 1) {
			dog.setAdopted(true);
			this->addoptions.push_back(dog);
		}
		else {
			this->dogs.push_back(dog);
		}

	}
	cout << "File loaded!" << endl;
}

void MongoDB::saveData()
{
	ofstream out(this->file);
	for (Dog var : this->dogs)
	{
		out << var.dogSave() << endl;
	}

	for (Dog var : this->addoptions)
	{
		out << var.dogSave() << endl;
	}
}

MongoDB::MongoDB()
{
}

void MongoDB::addDog(Dog dogAdd)
{
	this->dogs.push_back(dogAdd);
	this->saveData();
}

void MongoDB::deleteDog(Dog dogDelete)
{
	int positionForDelete = this->getPositionForDog(dogDelete);
	this->dogs.erase(this->dogs.begin() + positionForDelete);
	this->saveData();
}
void MongoDB::deleteAddoptedDog(Dog dogDelete)
{
	int positionForDelete = this->getPositionForAddoptedDog(dogDelete);
	this->addoptions.erase(this->addoptions.begin() + positionForDelete);
	this->saveData();
}

void MongoDB::updateDog(Dog& dogUpdate, string newName, string newBreed, int newAge, string newPhotograph) {
	dogUpdate.setAge(newAge);
	dogUpdate.setName(newName);
	dogUpdate.setBreed(newBreed);
	dogUpdate.setPhotograph(newPhotograph);
	this->saveData();
}

Dog* MongoDB::searchDogByIndex(int index)
{
	if (index < 0 || index > this->dogs.size()) return NULL;
	return &this->dogs[index];
}

Dog* MongoDB::getDogForUpdate(string name, string breed)
{
	Dog found{};
	for (Dog as : this->dogs) {
		if (compareLower(as.getName(), name) && compareLower(as.getBreed(), breed)) {
			return &this->dogs[this->getPositionForDog(as)];
		}
	}
	return NULL;
}

Dog MongoDB::getAddoptedDogForUpdate(string name, string breed)
{
	vector<Dog> dogsFound;
	copy_if(this->addoptions.begin(), this->addoptions.end(), back_inserter(dogsFound), [&](Dog& dog) {return isDogAddopted(dog, name, breed); });
	if (dogsFound.size() == 0) throw Exceptions().dogNotExist();
	return dogsFound[0];
}

vector<Dog> MongoDB::getAllElements()
{
	return this->dogs;
}

int MongoDB::getSizeOfDogs() {
	return this->dogs.size();
}

vector<Dog> MongoDB::getAllElementsAddopted()
{
	return this->addoptions;
}

vector<Dog> MongoDB::getAllElementsAddoptedPrint()
{
	return this->addoptions;
}

int MongoDB::getSizeOfDogsAddopted() {
	return this->addoptions.size();
}

void MongoDB::addoptDog(string name, string breed) {
	auto it = find_if(this->dogs.begin(), this->dogs.end(), [&](Dog& as) {
		return compareLower(as.getName(), name) && compareLower(as.getBreed(), breed);
		});
	if (it != this->dogs.end()) {
		Dog found = *it;
		found.setAdopted(true);
		this->dogs.erase(it);
		this->addoptions.push_back(found);
	}

	this->saveData();
}

void MongoDB::addoptDog(int index) {
	Dog dog = this->dogs[index];
	dog.setAdopted(true);
	this->dogs.erase(this->dogs.begin() + index);
	this->addoptions.push_back(dog);
	this->saveData();
}

int MongoDB::getPositionForDog(Dog elem)
{
	int index = 0;
	for (Dog as : this->dogs) {
		if (as == elem) {
			return index;
		}
		index++;
	}
	throw Exceptions().dogNotExist();
}

int MongoDB::getPositionForAddoptedDog(Dog elem)
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

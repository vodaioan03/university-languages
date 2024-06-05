#include "HTMLRepository.h"

HTMLRepository::HTMLRepository(string filename, string fileHTML)
{
	this->file = filename;
	this->fileHTML = fileHTML;
	this->command = "start " + fileHTML;
	this->loadData();
}

void HTMLRepository::loadData()
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
	this->saveData();
	cout << "File loaded!" << endl;
}

void HTMLRepository::saveData()
{
	ofstream out(this->file);
	ofstream html(this->fileHTML);
	html << this->front;
	string result = "";
	for (Dog var : this->dogs)
	{
		out << var.dogSave() << endl;
	}

	for (Dog var : this->addoptions)
	{
		out << var.dogSave() << endl;

		html << this->htmlAddDog(var);
	}
	html << this->back;
}

string HTMLRepository::htmlAddDog(Dog dog) {
	return "<tr>\n<td>" + dog.getName() + "</td>\n<td>" + dog.getBreed() + "</td>\n<td>" + to_string(dog.getAge()) + "</td >\n<td><a href = " + dog.getPhotograph() + ">Link</a></td>\n</tr>\n";
}

HTMLRepository::HTMLRepository()
{
}

void HTMLRepository::addDog(Dog dogAdd)
{
	this->dogs.push_back(dogAdd);
	this->saveData();
}

void HTMLRepository::deleteDog(Dog dogDelete)
{
	int positionForDelete = this->getPositionForDog(dogDelete);
	this->dogs.erase(this->dogs.begin() + positionForDelete);
	this->saveData();
}
void HTMLRepository::deleteAddoptedDog(Dog dogDelete)
{
	int positionForDelete = this->getPositionForAddoptedDog(dogDelete);
	this->addoptions.erase(this->addoptions.begin() + positionForDelete);
	this->saveData();
}

void HTMLRepository::updateDog(Dog& dogUpdate, string newName, string newBreed, int newAge, string newPhotograph) {
	dogUpdate.setAge(newAge);
	dogUpdate.setName(newName);
	dogUpdate.setBreed(newBreed);
	dogUpdate.setPhotograph(newPhotograph);
	this->saveData();
}

void HTMLRepository::updateDog(string name, string breed, string newName, string newBreed, int newAge, string newPhotograph) {
	Dog& dogUpdate = *this->getDogForUpdate(name, breed);
	dogUpdate.setAge(newAge);
	dogUpdate.setName(newName);
	dogUpdate.setBreed(newBreed);
	dogUpdate.setPhotograph(newPhotograph);
	this->saveData();
}

Dog* HTMLRepository::searchDogByIndex(int index)
{
	if (index < 0 || index > this->dogs.size()) return NULL;
	return &this->dogs[index];
}

Dog* HTMLRepository::getDogForUpdate(string name, string breed)
{
	Dog found{};
	for (Dog as : this->dogs) {
		if (compareLower(as.getName(), name) && compareLower(as.getBreed(), breed)) {
			return &this->dogs[this->getPositionForDog(as)];
		}
	}
	return NULL;
}

Dog HTMLRepository::getAddoptedDogForUpdate(string name, string breed)
{
	vector<Dog> dogsFound;
	copy_if(this->addoptions.begin(), this->addoptions.end(), back_inserter(dogsFound), [&](Dog& dog) {return isDogAddopted(dog, name, breed); });
	if (dogsFound.size() == 0) throw Exceptions().dogNotExist();
	return dogsFound[0];
}

vector<Dog> HTMLRepository::getAllElements()
{
	return this->dogs;
}

int HTMLRepository::getSizeOfDogs() {
	return this->dogs.size();
}

vector<Dog> HTMLRepository::getAllElementsAddopted()
{
	return this->addoptions;
}

vector<Dog> HTMLRepository::getAllElementsAddoptedPrint()
{
	cout << command << endl;
	system(command.c_str());
	return this->addoptions;
}

int HTMLRepository::getSizeOfDogsAddopted() {
	return this->addoptions.size();
}

void HTMLRepository::addoptDog(string name, string breed) {
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

void HTMLRepository::addoptDog(int index) {
	Dog dog = this->dogs[index];
	dog.setAdopted(true);
	this->dogs.erase(this->dogs.begin() + index);
	this->addoptions.push_back(dog);
	this->saveData();
}

int HTMLRepository::getPositionForDog(Dog elem)
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

int HTMLRepository::getPositionForAddoptedDog(Dog elem)
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

#pragma once
#include "Dog.h"
#include "Repository.h"
#include <iostream>
#include <string>
#include <cctype>
#include <crtdbg.h>

using namespace std;

class Service
{

private:
	Repository repo = Repository();

public:
	Service();
	~Service();
	bool verifyDogExist(string nameVerify, string breedVerify);
	bool validAge(string age);
	void addDog(string name, string breed, string age, string photograph);
	void deleteDog(string name, string breed);
	void updateDog(string name, string breed, string newName, string newBreed, string newAge, string newPhotograph);
	bool verifyAddopt(string name, string breed);
	Dog* getAllElementsNotAddopted();
	Dog* getAllElementsAddopted();
	int getSizeForDogsAddopted();
	int getSizeForDogsNotAddopted();
	void addoptDog(string name, string breed);
	void addoptDog(int index);
	void searchDogByBreedAge(int* indexes, int &indexIndexes, string breed, string age);
	Dog* searchDogByIndex(int indexSearch);
};


#pragma once
#include "utils.h"
#include "Dog.h"
#include "DynamicArrays.h"
#include <iostream>
#include <typeinfo>

using namespace std;

class Repository
{
private:
	DynamicArray<class Dog> dogs = DynamicArray<class Dog>();
	DynamicArray<class Dog> addoptions = DynamicArray<class Dog>();


public:
	Repository();
	~Repository();

	void addDog(Dog dogAdd);
	void deleteDog(Dog dogDelete);
	void updateDog(Dog &dogUpdate, string newName, string newBreed, int newAge, string newPhotograph);
	Dog searchDogByName(string nameSearch);
	Dog* searchDogByIndex(int index);
	Dog* getDogForUpdate(string name, string breed);
	Dog* getAllElements();
	int getSizeOfDogs();
	Dog* getAllElementsAddopted();
	int getSizeOfDogsAddopted();
	void addoptDog(string name, string breed);
	void addoptDog(int index);
};


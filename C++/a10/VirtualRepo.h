#pragma once
#include "utils.h"
#include "Dog.h"
#include "DynamicArrays.h"
#include <iostream>
#include <typeinfo>
#include <vector>
#include <algorithm>

using namespace std;

class VirtualRepo
{

public:
	virtual ~VirtualRepo() {}
	/// <summary>
	/// Add Dog in dogs array
	/// </summary>
	/// <param name="dogAdd"></param>
	virtual void addDog(Dog dogAdd) = 0;
	/// <summary>
	/// Delete dog.
	/// </summary>
	/// <param name="dogDelete"></param>
	virtual void deleteDog(Dog dogDelete) = 0;
	virtual void deleteAddoptedDog(Dog dogDelete) = 0;
	/// <summary>
	/// Update dog with given value
	/// </summary>
	/// <param name="dogUpdate"></param>
	/// <param name="newName"></param>
	/// <param name="newBreed"></param>
	/// <param name="newAge"></param>
	/// <param name="newPhotograph"></param>
	virtual void updateDog(Dog& dogUpdate, string newName, string newBreed, int newAge, string newPhotograph) = 0;
	virtual void updateDog(string name, string breed, string newName, string newBreed, int newAge, string newPhotograph) = 0;
	/// <summary>
	/// Search dog by index and return pointer
	/// </summary>
	/// <param name="index"></param>
	/// <returns>Dog* pointer</returns>
	virtual Dog* searchDogByIndex(int index) = 0;;
	/// <summary>
	/// Return dog for update by name and breed
	/// </summary>
	/// <param name="name"></param>
	/// <param name="breed"></param>
	/// <returns>Dog* pointer</returns>
	virtual Dog* getDogForUpdate(string name, string breed) = 0;;
	virtual Dog getAddoptedDogForUpdate(string name, string breed) = 0;;
	/// <summary>
	/// Return list with all elements
	/// </summary>
	/// <returns>Dog* pointer</returns>
	virtual vector<Dog> getAllElements() = 0;;
	/// <summary>
	/// Return size of dogs.
	/// </summary>
	/// <returns>int size</returns>
	virtual int getSizeOfDogs() = 0;;
	/// <summary>
	/// Return all elements addopted
	/// </summary>
	/// <returns>Dog* pointer</returns>
	virtual vector<Dog> getAllElementsAddopted() = 0;;
	virtual vector<Dog> getAllElementsAddoptedPrint() = 0;
	/// <summary>
	/// Return size of list of dogs addopted
	/// </summary>
	/// <returns>int size</returns>
	virtual int getSizeOfDogsAddopted() = 0;;
	/// <summary>
	/// Set dog addopted and move to the addoption list. By name and breed
	/// </summary>
	/// <param name="name"></param>
	/// <param name="breed"></param>
	virtual void addoptDog(string name, string breed) = 0;;
	/// <summary>
	/// Addopt dog by index and move to the addoption list.
	/// </summary>
	/// <param name="index"></param>
	virtual void addoptDog(int index) = 0;;

	virtual int getPositionForDog(Dog elem) = 0;;
	virtual int getPositionForAddoptedDog(Dog elem) = 0;;
};


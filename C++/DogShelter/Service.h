#pragma once
#include "Dog.h"
#include "Repository.h"
#include "utils.h"
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
	/// <summary>
	/// Constructor for service
	/// </summary>
	Service();
	/// <summary>
	/// Destructor for service
	/// </summary>
	~Service();
	/// <summary>
	/// Check if dog exist by name and breed
	/// </summary>
	/// <param name="nameVerify"></param>
	/// <param name="breedVerify"></param>
	/// <returns>True if exist, False if doesn't exist</returns>
	bool verifyDogExist(string nameVerify, string breedVerify);
	bool verifyAddoptedDogExist(string nameVerify, string breedVerify);
	/// <summary>
	/// Verify if a string is age < 99
	/// </summary>
	/// <param name="age"></param>
	/// <returns>True if is string is with only digits and <99 </returns>
	bool validAge(string age);
	/// <summary>
	/// Add dog in repository and create object of Dog class
	/// </summary>
	/// <param name="name"></param>
	/// <param name="breed"></param>
	/// <param name="age"></param>
	/// <param name="photograph"></param>
	void addDog(string name, string breed, string age, string photograph);
	/// <summary>
	/// Delete dog from repo by name and breed
	/// </summary>
	/// <param name="name"></param>
	/// <param name="breed"></param>
	void deleteDog(string name, string breed);
	void deleteDogAddopted(string name, string breed);
	/// <summary>
	/// Update dog by given values
	/// </summary>
	/// <param name="name"></param>
	/// <param name="breed"></param>
	/// <param name="newName"></param>
	/// <param name="newBreed"></param>
	/// <param name="newAge"></param>
	/// <param name="newPhotograph"></param>
	void updateDog(string name, string breed, string newName, string newBreed, string newAge, string newPhotograph);
	/// <summary>
	/// Verify if dog is addopt or no
	/// </summary>
	/// <param name="name"></param>
	/// <param name="breed"></param>
	/// <returns>True if addopted ,False else</returns>
	bool verifyAddopt(string name, string breed);
	/// <summary>
	/// Return Dog* with all elements wich are not addopted
	/// </summary>
	/// <returns>Dog* pointer</returns>
	Dog* getAllElementsNotAddopted();
	/// <summary>
	/// Return Dog* with all elements wich are addopted
	/// </summary>
	/// <returns>Dog* pointer</returns>
	Dog* getAllElementsAddopted();
	/// <summary>
	/// Return size of dogs addopted
	/// </summary>
	/// <returns>int size</returns>
	int getSizeForDogsAddopted();
	/// <summary>
	/// Return size for dogs not addopted
	/// </summary>
	/// <returns>int size</returns>
	int getSizeForDogsNotAddopted();
	/// <summary>
	/// Addopt dog by given name and breed
	/// </summary>
	/// <param name="name"></param>
	/// <param name="breed"></param>
	void addoptDog(string name, string breed);
	/// <summary>
	/// Addopt dog by given index
	/// </summary>
	/// <param name="index"></param>
	void addoptDog(int index);
	/// <summary>
	/// Search dog by breed and by given age. Breed = "" ==> return all elemnts smaller then <
	/// </summary>
	/// <param name="indexes"></param>
	/// <param name="indexIndexes"></param>
	/// <param name="breed"></param>
	/// <param name="age"></param>
	void searchDogByBreedAge(int* indexes, int &indexIndexes, string breed, string age);
	/// <summary>
	/// Search dog by index
	/// </summary>
	/// <param name="indexSearch"></param>
	/// <returns>Dog* dog</returns>
	Dog* searchDogByIndex(int indexSearch);
};


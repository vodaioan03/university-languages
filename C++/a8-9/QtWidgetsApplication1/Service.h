#pragma once
#include "Dog.h"
#include "VirtualRepo.h"
#include "Repository.h"
#include "TextRepository.h"
#include "utils.h"
#include "Exceptions.h"
#include "Verifications.h"
#include <iostream>
#include <string>
#include <cctype>
#include <crtdbg.h>
#include <algorithm>


using namespace std;

class Service
{

private:
	VirtualRepo *repo;
	Verifications verify{repo};
public:
	/// <summary>
	/// Constructor for service
	/// </summary>
	Service();
	Service(VirtualRepo* repository);
	/// <summary>
	/// Destructor for service
	/// </summary>
	~Service();
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
	/// Return Dog* with all elements wich are not addopted
	/// </summary>
	/// <returns>Dog* pointer</returns>
	vector<Dog> getAllElementsNotAddopted();
	/// <summary>
	/// Return Dog* with all elements wich are addopted
	/// </summary>
	/// <returns>Dog* pointer</returns>
	vector<Dog> getAllElementsAddopted();
	vector<Dog> getAllElementsAddoptedPrint();
	
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
	void searchDogByBreedAge(vector<Dog>& indexes, string breed, string age);
	/// <summary>
	/// Search dog by index
	/// </summary>
	/// <param name="indexSearch"></param>
	/// <returns>Dog* dog</returns>
	Dog* searchDogByIndex(int indexSearch);
	VirtualRepo* getRepo() {
		return this->repo;
	}
};


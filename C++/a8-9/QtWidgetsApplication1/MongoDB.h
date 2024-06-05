#pragma once
#include "utils.h"
#include "Dog.h"
#include "DynamicArrays.h"
#include <iostream>
#include <typeinfo>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "VirtualRepo.h"
#include "Exceptions.h"

#include <stdlib.h>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

using namespace std;

class MongoDB : public VirtualRepo
{
private:
	vector<class Dog> dogs;
	vector<class Dog> addoptions;
	Exceptions except{};

	string server = "localhost:3306";
	string database = "dogshelter";
	string username = "Voda";
	string password = "Parola123";

	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;


public:
	MongoDB();
	~MongoDB();

	void loadData();
	/// <summary>
	/// Add Dog in dogs array
	/// </summary>
	/// <param name="dogAdd"></param>
	void addDog(Dog dogAdd);
	void addDogSQL(Dog dogadd);
	/// <summary>
	/// Delete dog.
	/// </summary>
	/// <param name="dogDelete"></param>
	void deleteDog(Dog dogDelete);
	void deleteAddoptedDog(Dog dogDelete);
	/// <summary>
	/// Update dog with given value
	/// </summary>
	/// <param name="dogUpdate"></param>
	/// <param name="newName"></param>
	/// <param name="newBreed"></param>
	/// <param name="newAge"></param>
	/// <param name="newPhotograph"></param>
	void updateDog(Dog& dogUpdate, string newName, string newBreed, int newAge, string newPhotograph);
	/// <summary>
	/// Search dog by index and return pointer
	/// </summary>
	/// <param name="index"></param>
	/// <returns>Dog* pointer</returns>
	Dog* searchDogByIndex(int index);
	/// <summary>
	/// Return dog for update by name and breed
	/// </summary>
	/// <param name="name"></param>
	/// <param name="breed"></param>
	/// <returns>Dog* pointer</returns>
	Dog* getDogForUpdate(string name, string breed);
	Dog getAddoptedDogForUpdate(string name, string breed);
	/// <summary>
	/// Return list with all elements
	/// </summary>
	/// <returns>Dog* pointer</returns>
	vector<Dog> getAllElements();
	/// <summary>
	/// Return size of dogs.
	/// </summary>
	/// <returns>int size</returns>
	int getSizeOfDogs();
	/// <summary>
	/// Return all elements addopted
	/// </summary>
	/// <returns>Dog* pointer</returns>
	vector<Dog> getAllElementsAddopted();
	vector<Dog> getAllElementsAddoptedPrint();
	/// <summary>
	/// Return size of list of dogs addopted
	/// </summary>
	/// <returns>int size</returns>
	int getSizeOfDogsAddopted();
	/// <summary>
	/// Set dog addopted and move to the addoption list. By name and breed
	/// </summary>
	/// <param name="name"></param>
	/// <param name="breed"></param>
	void addoptDog(string name, string breed);
	/// <summary>
	/// Addopt dog by index and move to the addoption list.
	/// </summary>
	/// <param name="index"></param>
	void addoptDog(int index);

	int getPositionForDog(Dog elem);
	int getPositionForAddoptedDog(Dog elem);
};


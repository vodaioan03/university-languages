#pragma once
#include <iostream>
#include <string>

using namespace std;

class Dog
{
private:
	string breed;
	string name;
	int age;
	string photograph;
	bool adopted;

public:
	/// <summary>
	/// Constructor for Dog. All elems are defined with "Unknown".
	/// </summary>
	Dog();
	
	/// <summary>
	/// Constructor for dog with all elems given.
	/// </summary>
	/// <param name="breed"></param>
	/// <param name="name"></param>
	/// <param name="age"></param>
	/// <param name="photograph"></param>
	Dog(string breed, string name, int age, string photograph);
	/// <summary>
	/// Destructor for dog.
	/// </summary>
	/// <summary>
	/// Return value of addopted dog.
	/// </summary>
	/// <returns>True - addopted, False - not addopted</returns>
	bool getAdopted();
	/// <summary>
	/// Set status of addopted
	/// </summary>
	/// <param name="adopt"></param>
	void setAdopted(bool adopt);
	/// <summary>
	/// Return value of breed
	/// </summary>
	/// <returns>string breed</returns>
	string getBreed();
	/// <summary>
	/// Set value of breed
	/// </summary>
	/// <param name="breed"></param>
	void setBreed(string breed);
	/// <summary>
	/// Return value of name
	/// </summary>
	/// <returns>string name</returns>
	string getName();
	/// <summary>
	/// Set value of name
	/// </summary>
	/// <param name="name"></param>
	void setName(string name);
	/// <summary>
	/// Return value of age
	/// </summary>
	/// <returns>int age</returns>
	int getAge();
	/// <summary>
	/// Set value of age
	/// </summary>
	/// <param name="age"></param>
	void setAge(int age);
	/// <summary>
	/// return value of photograph
	/// </summary>
	/// <returns>string photograph</returns>
	string getPhotograph();
	/// <summary>
	/// Set value of photograph
	/// </summary>
	/// <param name="photograph"></param>
	void setPhotograph(string photograph);
	/// <summary>
	/// Return string of dog values
	/// </summary>
	/// <returns>string</returns>
	string dogToString();
	/// <summary>
	/// Return values of dogs
	/// </summary>
	/// <returns>string print</returns>
	string dogShow();

	string dogSave();
	/// <summary>
	/// Define operator of ==
	/// </summary>
	/// <param name="compare"></param>
	/// <returns></returns>
	bool operator==(const Dog& compare) const {
		if (this->name.compare(compare.name) != 0) return false;
		if (this->age != compare.age) return false;
		if (this->breed.compare(compare.breed) != 0) return false;
		if (this->photograph.compare(compare.photograph) != 0) return false;
		return true;
	}
	/// <summary>
	/// Define operator of !=
	/// </summary>
	/// <param name="compare"></param>
	/// <returns></returns>
	bool operator!=(const Dog& compare) const {
		if (this->name.compare(compare.name) != 0) return true;
		if (this->age != compare.age) return true;
		if (this->breed.compare(compare.breed) != 0) return true;
		if (this->photograph.compare(compare.photograph) != 0) return true;
		return false;
	}


	friend ostream& operator<<(ostream& os, const Dog& entity) {
		os << entity.breed << " "
			<< entity.name << " "
			<< entity.age << " "
			<< entity.photograph << " "
			<< (entity.adopted ? "1" : "0");
		return os;
	}


};


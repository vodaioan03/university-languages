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
	//Constructor
	Dog();
	Dog(string breed, string name, int age, string photograph);
	//Destructor
	~Dog();
	//Getters & setters
	bool getAdopted();
	void setAdopted(bool adopt);
	string getBreed();
	void setBreed(string breed);
	string getName();
	void setName(string name);
	int getAge();
	void setAge(int age);
	string getPhotograph();
	void setPhotograph(string photograph);
	string dogToString();

	string dogShow();

	bool operator==(const Dog& compare) const {
		if (this->name.compare(compare.name) != 0) return false;
		if (this->age != compare.age) return false;
		if (this->breed.compare(compare.breed) != 0) return false;
		if (this->photograph.compare(compare.photograph) != 0) return false;
		return true;
	}

	bool operator!=(const Dog& compare) const {
		if (this->name.compare(compare.name) != 0) return true;
		if (this->age != compare.age) return true;
		if (this->breed.compare(compare.breed) != 0) return true;
		if (this->photograph.compare(compare.photograph) != 0) return true;
		return false;
	}
};


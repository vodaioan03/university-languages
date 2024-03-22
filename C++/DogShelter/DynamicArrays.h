#pragma once
#include "Dog.h"
#include "utils.h"
#include <iostream>
#include <typeinfo>

using namespace std;

template <typename TElem> class DynamicArray
{
private:
	TElem* listOfElems;
	int capacity;
	int size;

public:
	DynamicArray() {
		this->capacity = 1;
		this->size = 0;
		this->listOfElems = new TElem[this->capacity];
	}
	DynamicArray(int capacity) {
		this->capacity = capacity;
		this->size = 0;
		this->listOfElems = new TElem[this->capacity];
	}
	~DynamicArray() {
		delete[] this->listOfElems;
	}

	const int getCapacity() {
		return this->capacity;
	}
	void setCapacity(int newCapacity) {
		this->capacity = newCapacity;
	}
	const int getSize() {
		return this->size;
	}
	void setSize(int newSize) {
		this->size = newSize;
	}

	//RESIZE
	void resizeListElems() {
		this->setCapacity(this->getCapacity() * 2);
		TElem* newArray = new TElem[this->getCapacity()];

		for (int i = 0; i < this->size; i++) {
			newArray[i] = this->listOfElems[i];
		}

		delete[] this->listOfElems;
		this->listOfElems = newArray;
	}

	void addElement(TElem elemToBeAdded) {
		if (this->getCapacity() == this->getSize() + 1) {
			this->resizeListElems();
		}
		this->listOfElems[this->getSize()] = elemToBeAdded;
		this->setSize(this->getSize() + 1);
	}
	void deleteElement(TElem elemToBeDeleted) {
		for (int i = 0; i < this->getSize(); i++) {
			if (*getElemById(i) == elemToBeDeleted) {
				for (int j = i; j < this->getSize() - 1; j++) {
					this->listOfElems[j] = this->listOfElems[j + 1];
				}
				this->setSize(this->getSize() - 1);
				break;
			}
		}
	}
	TElem* getAllElements() {
		return this->listOfElems;
	}


	TElem* getElemByName(string name) {
		for (int i = 0; i < this->getSize(); i++) {
			if (this->listOfElems[i].getName().compare(name) == 0)
			{
				return &this->listOfElems[i];
			}
		}
		return NULL;
	}

	TElem* getElemForUpdate(string name, string breed) {
		for (int i = 0; i < this->getSize(); i++) {
			if (compareLower(this->listOfElems[i].getName(),name) && compareLower(this->listOfElems[i].getBreed(),breed))
			{
				return &this->listOfElems[i];
			}
		}
		return NULL;
	}

	TElem* getElemById(int idSearch) {
		if (idSearch < this->getSize()) return &this->listOfElems[idSearch];
		return NULL;
	}


};
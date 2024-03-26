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
	/// <summary>
	///  Constructor for array. Initial value for size is 0, capacity is 1.
	/// </summary>
	DynamicArray() {
		this->capacity = 1;
		this->size = 0;
		this->listOfElems = new TElem[this->capacity];
	}
	/// <summary>
	/// Constructor for array with given size. Capacity is given, size is 0.
	/// </summary>
	/// <param name="capacity"></param>
	DynamicArray(int capacity) {
		this->capacity = capacity;
		this->size = 0;
		this->listOfElems = new TElem[this->capacity];
	}
	/// <summary>
	/// Destructor. Delete array listOfElems
	/// </summary>
	~DynamicArray() {
		delete[] this->listOfElems;
	}

	DynamicArray(const DynamicArray& vector) {
		this->capacity = vector.capacity;
		this->size = vector.size;
		this->listOfElems = new TElem[this->size];
		for (int i = 0; i < this->size; i++) {
			this->listOfElems[i] = vector.listOfElems[i];
		}
	}
	/// <summary>
	/// Get max capacity for list
	/// </summary>
	/// <returns>int capacity</returns>
	const int getCapacity() {
		return this->capacity;
	}
	/// <summary>
	/// Set capacity for array with given value.
	/// </summary>
	/// <param name="newCapacity"></param>
	void setCapacity(int newCapacity) {
		this->capacity = newCapacity;
	}
	/// <summary>
	/// Get size of array.
	/// </summary>
	/// <returns></returns>
	const int getSize() {
		return this->size;
	}
	/// <summary>
	/// Set size for arrag.
	/// </summary>
	/// <param name="newSize"></param>
	void setSize(int newSize) {
		this->size = newSize;
	}

	/// <summary>
	/// Resize list of Elems.
	/// </summary>
	void resizeListElems() {
		this->setCapacity(this->getCapacity() * 2);
		TElem* newArray = new TElem[this->getCapacity()];

		for (int i = 0; i < this->size; i++) {
			newArray[i] = this->listOfElems[i];
		}

		delete[] this->listOfElems;
		this->listOfElems = newArray;
	}
	/// <summary>
	/// Add a given element.
	/// </summary>
	/// <param name="elemToBeAdded"></param>
	void addElement(TElem elemToBeAdded) {
		if (this->getCapacity() == this->getSize() + 1) {
			this->resizeListElems();
		}
		this->listOfElems[this->getSize()] = elemToBeAdded;
		this->setSize(this->getSize() + 1);
	}
	/// <summary>
	/// Delete element by given elem.
	/// </summary>
	/// <param name="elemToBeDeleted"></param>
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
	/// <summary>
	/// Get list of all elements.
	/// </summary>
	/// <returns>Pointer of listOfelems.</returns>
	TElem* getAllElements() {
		return this->listOfElems;
	}

	/// <summary>
	///  Get element only by name.
	/// </summary>
	/// <param name="name"></param>
	/// <returnsNULL if doesn't exit, else pointer of elem></returns>
	TElem* getElemByName(string name) {
		for (int i = 0; i < this->getSize(); i++) {
			if (this->listOfElems[i].getName().compare(name) == 0)
			{
				return &this->listOfElems[i];
			}
		}
		return NULL;
	}
	/// <summary>
	/// Get element by name and breed.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="breed"></param>
	/// <returns>NULL if doesn't exit, else pointer of elem</returns>
	TElem* getElemForUpdate(string name, string breed) {
		for (int i = 0; i < this->getSize(); i++) {
			if (compareLower(this->listOfElems[i].getName(),name) && compareLower(this->listOfElems[i].getBreed(),breed))
			{
				return &this->listOfElems[i];
			}
		}
		return NULL;
	}
	/// <summary>
	/// Give element from listElems by index.
	/// </summary>
	/// <param name="idSearch"></param>
	/// <returns> NULL if doesn't exit, else pointer of elem</returns>
	TElem* getElemById(int idSearch) {
		if (idSearch < this->getSize()) return &this->listOfElems[idSearch];
		return NULL;
	}

	DynamicArray& operator=(const DynamicArray& array) const {
		if (this == &other) return *this;
		this->size = array.size;
		this->capacity = array.capacity;
		delete[] this->listOfElems;
		this->listOfElems = new TElem[array.capacity];
		for (int i = 0; i < this->size; i++) {
			this->listOfElems[i] = array.listOfElems[i];
		}
		return *this;
	}

	TElem& operator[](int position) {
		return this->listOfElems[position];
	}
};
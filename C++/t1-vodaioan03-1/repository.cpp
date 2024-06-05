#include "repository.h"

void repository::addElement(model elem)
{
	this->elems.push_back(elem);
}

model repository::getElement(int position)
{
	return this->elems[position];
}

int repository::getSize()
{
	return this->elems.size();
}

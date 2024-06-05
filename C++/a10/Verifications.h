#pragma once
#include "Exceptions.h"
#include "VirtualRepo.h"
#include "utils.h"
#include <iostream>
class Verifications
{
private:
	VirtualRepo* repo;
public:

	Verifications() {}
	Verifications(VirtualRepo* rep) : repo(rep) {}

	void setRepo(VirtualRepo* rep) {
		this->repo = rep;
	}



	bool validAge(string age) {
		delSpaces(age);
		int counter = 0;
		for (char& c : age) {
			if (!isdigit(c)) return false;
			else counter++;
		}
		if (counter == 0 || counter > 2) return false;

		return true;
	}

	bool verifyDogExist(string nameVerify, string breedVerify) {
		if (this->repo->getDogForUpdate(nameVerify, breedVerify) != NULL) return true;
		try
		{
			this->repo->getAddoptedDogForUpdate(nameVerify, breedVerify);
			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
		return false;
	}
	bool verifyAddoptedDogExist(string nameVerify, string breedVerify) {
		try
		{
			this->repo->getAddoptedDogForUpdate(nameVerify, breedVerify);
			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}

	bool verifyAddopt(string name, string breed) {
		try
		{
			this->repo->getAddoptedDogForUpdate(name, breed);
			return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
	}
};


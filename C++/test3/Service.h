#pragma once
#include "Repository.h"
class Service
{
private:
	Repository repo{};

public:
	Service() {}
	~Service() {}

	void populateRepo() { this->repo.readFromFile(); }

	vector<Task*> getItemsSorted();
	vector<Task*> getItemsByWord(string word);
	double getSimilarityByName(string word,string name);
};


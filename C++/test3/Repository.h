#pragma once
#include "Task.h"
class Repository
{
private:
	vector<Task*> tasks;

public:
	Repository() {}
	~Repository() {
		for (Task* t : tasks) {
			delete t;
		}
	}

	void addTask(Task* t) { this->tasks.push_back(t); }
	void readFromFile();
	vector<Task*> getTasks() { return this->tasks; }
};


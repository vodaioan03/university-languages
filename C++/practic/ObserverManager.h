#pragma once
#include <iostream>
#include <vector>
#include "Observer.h"

using namespace std;

class ObserverManager
{
private:
	vector<Observer*> observers;

public:
	ObserverManager() {}
	~ObserverManager() {
		for (Observer* obs : observers) {
			delete obs;
		}
	}

	void registerObserver(Observer* obs) { observers.push_back(obs); }
	void notify() {
		for (Observer* obs : observers) {
			obs->update();
		}
	}
};


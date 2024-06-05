#pragma once

#include "ui_A9.h"
#include "ui_login.h"
#include "A9.h"
#include <iostream>

using namespace std;

class Connections
{
private:
	A9* mainu = NULL;

public:
	Connections(A9* mainn) { this->mainu = mainn; };
	~Connections() {};

	void connectAll();
};


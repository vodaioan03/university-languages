#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
class Task
{
private:
	string name, keywords, content;
public:
	Task(string nam, string key, string cont) : name{ nam }, keywords{ key }, content{ cont } {}
	~Task() {}

	string getName() { return this->name; }
	string getContent() { return this->content; }
	string getKeywords() { return this->keywords; }

	string toString() { return this->name + " -> " + this->keywords; }
};


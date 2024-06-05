#include "Repository.h"

void Repository::readFromFile()
{
	ifstream in("input.txt");
	string line;
	char separator = '|';
	while (getline(in, line)) {
		istringstream ss(line);
		string nam, cont, key;
		getline(ss, nam, separator);
		getline(ss, key, separator);
		getline(ss, cont, separator);
		string keys="";
		for (int i = 1; i < key.size(); i++) {
			keys += key[i];
		}
		Task* t = new Task(nam, keys,cont);
		this->addTask(t);
	}
	in.close();
}

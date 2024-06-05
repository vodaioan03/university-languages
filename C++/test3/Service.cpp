#include "Service.h"

vector<Task*> Service::getItemsSorted()
{
	vector<Task*> tasks = this->repo.getTasks();
	sort(tasks.begin(), tasks.end(), [](Task* a, Task* b) {return a->getContent().size() < b->getContent().size(); });
	return tasks;
}

vector<Task*> Service::getItemsByWord(string word)
{
	vector<Task*> tasks;
	for (Task* t : this->repo.getTasks()) {
		if (t->getContent().find(word) != string::npos || t->getName().find(word) != string::npos || t->getKeywords().find(word) != string::npos) {
			tasks.push_back(t);
		}
	}
	sort(tasks.begin(), tasks.end(), [](Task* a, Task* b) {return a->getContent().size() < b->getContent().size(); });
	return tasks;
}

double getSimilarity(string s1, string s2) {
	int sizeMin = min(s1.size(), s2.size());
	int matched = 0;
	int i = 0;
	for (i = 0; i < sizeMin; i++) {
		if (s1[i] == s2[i]) {
			matched++;
		}
	}
	return (double)matched / (double)s2.size();
}

double Service::getSimilarityByName(string word,string name)
{
	vector<Task*> tasks = this->repo.getTasks();
	for (Task* t : tasks) {
		if (t->getName() == name) {
			return getSimilarity(word, t->getKeywords());
		}
	}
	return 0.0;
}

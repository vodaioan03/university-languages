#include "utils.h"
void toLower(string& stringCombine)
{
	for (char& c : stringCombine) {
		c = tolower(c);
	}
}


void delSpaces(string& stringCombine) {
	string resultString;
	for (int i = 0; i < stringCombine.length(); i++) {
		if (stringCombine[i] != ' ') {
			resultString.push_back(stringCombine[i]);
		}
	}

	stringCombine.assign(resultString);
}

bool compareLower(string firstString, string secondString)
{
	delSpaces(firstString);
	delSpaces(secondString);
	for (char& c : firstString) {
		c = tolower(c);
	}
	for (char& c : secondString) {
		c = tolower(c);
	}
	if (firstString.compare(secondString) == 0) return true;
	return false;
}
#include "uiManager.h"

void uiManager::testtsAdd()
{
	this->serviceManager.addSchool("Avram_Iancu", "46.77", "23.60", "2022.04.15");
	this->serviceManager.addSchool("George_Cosbuc", "46.77", "23.58", "2022.04.18");
	this->serviceManager.addSchool("Test_school", "46.77", "23.63", "2022.04.23");
	this->serviceManager.addSchool("Alexandru_Vaida_Voievod", "46.53", "24.57", "2022.05.04");
	this->serviceManager.addSchool("Colegiul_Transilvania", "46.54", "24.57", "2022.05.03");
	assert(this->serviceManager.getSizeOfSchools() == 5);
	cout << "test succes add" << endl;
}

void uiManager::testsSearch()
{
	string longitude = "46.77", latitude = "23.60";
	vector<model> indexes;
	this->serviceManager.findSchools(longitude, latitude, indexes);
	assert(indexes.size() == 3);
	cout << "test succes search" << endl;
}

void uiManager::inputSchools()
{
	this->serviceManager.addSchool("Avram_Iancu", "46.77", "23.60", "2022.04.15");
	this->serviceManager.addSchool("George_Cosbuc","46.77" ,"23.58", "2022.04.18");
	this->serviceManager.addSchool("Test_school", "46.77", "23.63", "2022.04.23");
	this->serviceManager.addSchool("Alexandru_Vaida_Voievod","46.53", "24.57", "2022.05.04");
	this->serviceManager.addSchool("Colegiul_Transilvania","46.54","24.57", "2022.05.03");
}

void uiManager::addSchool()
{
	string name, date, longitude, latitude;
	cout << "1. Type the name for school: ";
	getline(cin, name);
	cout << "2. Type the longitude: ";
	getline(cin, longitude);
	cout << "3. Type the latitude: ";
	getline(cin, latitude);
	cout << "4. Type the date(YYYY.MM.DD): ";
	getline(cin, date);
	this->serviceManager.addSchool(name, longitude, latitude, date);
	cout << "School has been added!" << endl;
}

void uiManager::showSchools()
{
	for (int i = 0; i < this->serviceManager.getSizeOfSchools(); i++) {
		cout << this->serviceManager.getStringForElem(i) << endl;
	}
}

void uiManager::closestSchools()
{
	string longitude, latitude, adress;
	cout << "1. Type longitude: ";
	getline(cin, longitude);
	cout << "2. Type latitude:";
	getline(cin, latitude);
	vector<model> indexes;
	this->serviceManager.findSchools(longitude, latitude, indexes);
	for (int i = 0; i < indexes.size(); i++) {
		cout << indexes[i].toString() << endl;
	}
}

void uiManager::printMenu()
{
	cout << " == SCHOOL MENU ==" << endl;
	cout << " 1. Add school" << endl;
	cout << " 2. Show schools." << endl;
	cout << " 3. Show the closet 3 schools." << endl;
	cout << "0. Exit" << endl;
	cout << "Type option: ";
}

void uiManager::optionProceed()
{
	string optionRead;
	getline(cin, optionRead);
	try
	{
		int option = stoi(optionRead);
		switch (option)
		{
		case 0:
			this->isRunning = false;
			cout << "Exiting..." << endl;
			break;
		case 1:
			this->addSchool();
			break;
		case 2:
			this->showSchools();
			break;
		case 3:
			this->closestSchools();
			break;
		default:
			break;
		}
	}
	catch (const std::exception& e)
	{
		cout << "[ERROR] " << e.what() << endl;
	}
}

void uiManager::start()
{
	this->inputSchools();
	while (this->isRunning) {
		this->printMenu();
		this->optionProceed();
	}
}

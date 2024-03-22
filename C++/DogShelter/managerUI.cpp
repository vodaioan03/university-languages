#include "managerUI.h"


managerUI::managerUI() {
	this->addInputs();
}

managerUI::~managerUI()
{
}

void managerUI::addInputs() {
	this->managerService.addDog("Ufi", "Samoyed", "10", "https://i.imgur.com/ImgurLink1.jpg");
	this->managerService.addDog("Lucy", "Beagle", "5", "https://i.imgur.com/ImgurLink2.jpg");
	this->managerService.addDog("Charlie", "Bulldog", "2", "https://i.imgur.com/ImgurLink3.jpg");
	this->managerService.addDog("Michael", "Bulldog", "4", "https://i.imgur.com/ImgurLink3.jpg");
	this->managerService.addDog("Azorel", "Bulldog", "5", "https://i.imgur.com/ImgurLink3.jpg");
	this->managerService.addDog("Viorel", "Bulldog", "8", "https://i.imgur.com/ImgurLink3.jpg");
	this->managerService.addDog("Conrel", "Bulldog", "15", "https://i.imgur.com/ImgurLink3.jpg");
	this->managerService.addDog("Luna", "Poodle", "1", "https://i.imgur.com/ImgurLink4.jpg");
	this->managerService.addDog("Cooper", "Siberian Husky", "3", "https://i.imgur.com/ImgurLink5.jpg");
	this->managerService.addDog("Daisy", "Boxer", "4", "https://i.imgur.com/ImgurLink6.jpg");
	this->managerService.addDog("Bailey", "Dachshund", "2", "https://i.imgur.com/ImgurLink7.jpg");
	this->managerService.addDog("Molly", "Shih Tzu", "6", "https://i.imgur.com/ImgurLink8.jpg");
	this->managerService.addDog("Maximus", "Doberman Pinscher", "3", "https://i.imgur.com/ImgurLink9.jpg");
	this->managerService.addDog("Sadie", "Rottweiler", "4", "https://i.imgur.com/ImgurLink10.jpg");
	this->managerService.addDog("Tucker", "Great Dane", "5", "https://i.imgur.com/ImgurLink11.jpg");
	this->managerService.addDog("Zoe", "Chihuahua", "2", "https://i.imgur.com/ImgurLink12.jpg");
	this->managerService.addDog("Oscar", "Pug", "3", "https://i.imgur.com/ImgurLink13.jpg");
	this->managerService.addDog("Maggie", "Yorkshire Terrier", "1", "https://i.imgur.com/ImgurLink14.jpg");
	this->managerService.addDog("Duke", "Australian Shepherd", "4", "https://i.imgur.com/ImgurLink15.jpg");
	this->managerService.addDog("Rosie", "Border Collie", "2", "https://i.imgur.com/ImgurLink16.jpg");
	this->managerService.addDog("Bear", "Bernese Mountain Dog", "5", "https://i.imgur.com/ImgurLink17.jpg");
	this->managerService.addDog("Stella", "Cavalier King Charles Spaniel", "3", "https://i.imgur.com/ImgurLink18.jpg");
	this->managerService.addoptDog("oscar", "pug");
	this->managerService.addoptDog("daisy", "boxer");
	this->managerService.addoptDog("sadie", "Rottweiler");
	this->managerService.addoptDog("luna", "poodle");
	this->managerService.addoptDog("bailey", "Dachshund");
	this->managerService.addoptDog("Lucy", "beagle");
	this->managerService.addoptDog("Cooper", "Siberian Husky");
	this->managerService.addoptDog("zoe", "Chihuahua");
	this->managerService.addoptDog("Tucker", "Great Dane");
	this->managerService.addoptDog("Bear", "Bernese Mountain Dog");
}

void managerUI::printLoginMenu() {
	cout << "     Login Menu" << endl;
	cout << "[USERS] Admin, User" << endl;
	cout << "0. Exit Application" << endl;
	cout << "Type user for logging: ";
}


//USER MENU
void managerUI::printUserMenu() {
	cout << "   User Menu Options  " << endl;
	cout << "1. Show dogs [One by One]" << endl;
	cout << "2. See all the dogs of a given breed, having an age less than a given number.[Breed = " " => All dogs] " << endl;
	cout << "3. See all adopted dogs." << endl;
	cout << "4. Disconnect." << endl;
	cout << "0. Exit." << endl;
	cout << "[INPUT] Choose a option[0-4]: ";
}


void managerUI::showMenuDog(int indexDog) {
	Dog* acutalDog = this->managerService.searchDogByIndex(indexDog);
	if (acutalDog == NULL) throw exception("Dog Object IS NULL!");
	cout << endl << "New dog found. Index: " << to_string(indexDog) << "." << endl;
	cout << acutalDog->dogShow() << endl<<endl;
	cout << "1. Addopt Dog  | 2. Next Dog | 3. Back | 4. Back to Menu | 5. Disconnect | 0. Exit Application |" << endl;
	cout << "[INPUT] Type option [0-5]:";
}

void managerUI::showDogsForUser(int &exited, int &disconnected) {
	if (this->managerService.getSizeForDogsNotAddopted() == 0) throw exception("We don't have dogs for addopt!");
	int initialIndex = this->managerService.getSizeForDogsNotAddopted(), actualIndex = 0;

	while (true) {
		if (actualIndex >= initialIndex) actualIndex = 0;
		if (actualIndex < 0) actualIndex = initialIndex - 1;
		this->showMenuDog(actualIndex);
		string option;
		getline(cin, option);
		delSpaces(option);
		if (!this->managerService.validAge(option) || option.compare("5") > 0)  cout << "Invalid Option! Try Again!" << endl;
		else {
			if (option.compare("1") == 0) {
				this->managerService.addoptDog(actualIndex);
				cout << "You addopted one Dog. Thank You!" << endl;
				break;
			}
			else if (option.compare("2") == 0) {
				cout << "We prepare next dog for you!" << endl;
			}
			else if (option.compare("3") == 0) {
				actualIndex -= 2;
			}
			else if (option.compare("4") == 0) {
				break;
			}
			else if (option.compare("5") == 0) {
				disconnected = 1;
				break;
			}
			else if (option.compare("0") == 0) {
				exited = 1;
				break;
			}
			actualIndex++;
		}
		
	}

	return;
}

void managerUI::searchDogByBreedAge() {
	string givenBreed, givenAge;
	cout << "  Search Dog Option" << endl;
	cout << "[1/2] Type the breed for dog: ";
	getline(cin, givenBreed);
	cout << "[2/2] Type the age for " << givenBreed << ":";
	getline(cin, givenAge);
	if (!this->managerService.validAge(givenAge)) throw exception("Invalid Age! Enter only digits! Maximum 99.");
	int* indexes = new int[this->managerService.getSizeForDogsNotAddopted()];
	int indexIndexes = 0;
	this->managerService.searchDogByBreedAge(indexes, indexIndexes, givenBreed, givenAge);
	Dog* dogs = this->managerService.getAllElementsNotAddopted();
	cout << endl;
	if (indexIndexes == 0) {
		cout << "We found 0 dogs with that info." << endl;
	}
	else {
		for (int i = 0; i < indexIndexes; i++) {
			cout << dogs[indexes[i]].dogToString() << endl;
		}
	}
}

void managerUI::showAllAdoptedDogs() {
	cout << endl;
	Dog* dogs = this->managerService.getAllElementsAddopted();
	for (int i = 0; i < this->managerService.getSizeForDogsAddopted(); i++) {
		cout << dogs[i].dogToString() << endl;
	}
	cout << endl;
}

//ADMIN MENU
void managerUI::printAdminMenu() {
	cout << "   Admin Menu Options  " << endl;
	cout << "1. Add Dog" << endl;
	cout << "2. Delete Dog[ONLY IF WAS ADOPTED]" << endl;
	cout << "3. Update info for Dog" << endl;
	cout << "4. Show all dogs." << endl;
	cout << "5. Disconnect." << endl;
	cout << "0. Exit" << endl;
	cout << "[INPUT] Choose a option[0-5]: ";
}

void managerUI::addDogOption() {
	string nameDog, breedDog, photograph, age;
	cout << "  Add Dog Option" << endl;
	cout << "[1/4] Type the name for dog: ";
	getline(cin, nameDog);
	cout << "[2/4] Type the breed for " << nameDog << ":";
	getline(cin, breedDog);
	if (this->managerService.verifyDogExist(nameDog, breedDog)) throw exception("This dog already exist!");
	cout << "[3/4] Type the age for " << nameDog << ":";
	getline(cin, age);
	if (!this->managerService.validAge(age)) throw exception("Invalid Age! Enter only digits! Maximum 99.");
	cout << "[4/4] Type the photograph for " << nameDog << ":";
	getline(cin, photograph);
	cout << "Dog added! " << nameDog << " Breed: " << breedDog << " Age: " << age << " Photograph: " << photograph << endl;
	this->managerService.addDog(nameDog, breedDog, age, photograph);
}

void managerUI::deleteDogOption() {
	string nameDog, breedDog;
	cout << "  Delete Dog Option" << endl;
	cout << "[1/2] Type the name for dog: ";
	getline(cin, nameDog);
	cout << "[2/2] Type the breed for " << nameDog << ":";
	getline(cin, breedDog);
	if (!this->managerService.verifyDogExist(nameDog, breedDog)) throw exception("This dog doesn't exist!");
	if (!this->managerService.verifyAddopt(nameDog, breedDog)) throw exception("This dog isn't addopted");
	this->managerService.deleteDog(nameDog, breedDog);
}

void managerUI::updateDogOption() {
	string nameDog, breedDog, newName, newBreed, newAge, newPhotograph;
	cout << "  Update Dog Option" << endl;
	cout << "[1/6] Type the name for dog: ";
	getline(cin, nameDog);
	cout << "[2/6] Type the breed for " << nameDog << ":";
	getline(cin, breedDog);
	if (!this->managerService.verifyDogExist(nameDog, breedDog)) throw exception("This dog doesn't exist!");
	if (this->managerService.verifyAddopt(nameDog, breedDog)) throw exception("This dog is addopted. You can't update.");
	cout << "[3/6] Type new name for " << nameDog << ": ";
	getline(cin, newName);
	cout << "[4/6] Type new breed for " << nameDog << ":";
	getline(cin, newBreed);
	if (this->managerService.verifyDogExist(newName, newBreed)) throw exception("This new dog already exist!");
	cout << "[5/6] Type new age for " << nameDog << ":";
	getline(cin, newAge);
	if (!this->managerService.validAge(newAge)) throw exception("Invalid Age! Enter only digits! Maximum 99.");
	cout << "[6/6] Type new photograph for " << nameDog << ":";
	getline(cin, newPhotograph);
	this->managerService.updateDog(nameDog, breedDog, newName, newBreed, newAge, newPhotograph);
}

void managerUI::showAllDogs() {
	if (this->managerService.getSizeForDogsNotAddopted() == 0) throw exception("No dogs found! All are addopted.");
	cout << endl;
	Dog* dogs = this->managerService.getAllElementsNotAddopted();
	for (int i = 0; i < this->managerService.getSizeForDogsNotAddopted(); i++) {
		cout << dogs[i].dogToString() << endl;
	}
	cout << endl;
}


//START APPLICATION
int managerUI::startUI()
{
	this->loggedAs = "";
	int exited = 0;
	while (this->loggedAs.compare("admin") != 0 && this->loggedAs.compare("user") != 0 && exited == 0) {
		this->printLoginMenu();
		try
		{
			getline(cin,this->loggedAs);
			if (this->loggedAs.compare("0") == 0) {
				exited = 1;
				break;
			}
			delSpaces(this->loggedAs);
			toLower(this->loggedAs);
			
			if (this->loggedAs.compare("admin") != 0 && this->loggedAs.compare("user") != 0) {
				throw exception("Invalid Input");
			}
		}
		catch (const std::exception& e)
		{
			cout << endl << "[ERROR]: " << e.what() << endl<<endl;
		}
	}
	cout << "[Logged] Connected as " << this->loggedAs << endl;
	int disconnected = 0;
	if (!exited) {
		string option = "";
		if (this->loggedAs.compare("admin") == 0) {
			while (exited == 0 && disconnected == 0) {
				try
				{
					option = "";
					this->printAdminMenu();
					getline(cin, option);
					toLower(option);
					delSpaces(option);
					if (option.compare("0") == 0) exited = 1;
					else if (option.compare("5") == 0) disconnected = 1;
					else if (option.compare("1") == 0) this->addDogOption();
					else if (option.compare("2") == 0) this->deleteDogOption();
					else if (option.compare("3") == 0) this->updateDogOption();
					else if (option.compare("4") == 0) this->showAllDogs();
					else throw exception("Invalid Input! Type a digit between 0 and 5.");
				}
				catch (const std::exception& e)
				{
					cout << endl << "[ERROR] " << e.what() << endl <<endl;
				}
			}
		}
		else if (this->loggedAs.compare("user") == 0) {
			while (exited == 0 && disconnected == 0) {
				try
				{
					option = "";
					this->printUserMenu();
					getline(cin, option);
					toLower(option);
					delSpaces(option);
					if (option.compare("0") == 0) exited = 1;
					else if (option.compare("4") == 0) disconnected = 1;
					else if (option.compare("1") == 0) this->showDogsForUser(exited,disconnected);
					else if (option.compare("2") == 0) this->searchDogByBreedAge();
					else if (option.compare("3") == 0) this->showAllAdoptedDogs();
					else throw exception("[ERROR] Invalid Input! Type a digit between 0 and 4.");
				}
				catch (const std::exception& e)
				{
					cout << endl << "[ERROR] " << e.what() << endl<<endl;
				}
			}
		}
		return exited;
	}

	return exited;
}


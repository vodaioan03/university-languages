#include "tests.h"

void dogTests() {
	Dog newDog = Dog();
	assert(newDog.getName() == "Unknown");

	Dog newDog2 = Dog("Breed","Name",11,"Photography");
	assert(newDog2.getName() == "Name");
	assert(newDog2.getBreed() == "Breed");
	assert(newDog2.getAge() == 11);
	assert(newDog2.getPhotograph() == "Photography");
	assert(newDog2.getAdopted() == false);
	newDog2.setAdopted(true);
	assert(newDog2.getAdopted() == true);
	newDog2.setAge(12);
	assert(newDog2.getAge() == 12);
	newDog2.setBreed("TestBreed");
	assert(newDog2.getBreed() == "TestBreed");
	newDog2.setName("TestName");
	assert(newDog2.getName() == "TestName");
	newDog2.setPhotograph("TestPhoto");
	assert(newDog2.getPhotograph() == "TestPhoto");
	newDog2 = Dog("Breed", "Name", 11, "Photography");
	newDog = Dog("Breed", "Name", 11, "Photography");
	assert((newDog == newDog2) == true);
	assert((newDog != newDog2) == false);
	string dogshow, dogstring;
	dogshow.assign("Name: " + newDog.getName() + "\nBreed: " + newDog.getBreed() + " \nAge: " + to_string(newDog.getAge()) + " \nPhotograph: " + newDog.getPhotograph());
	assert(newDog.dogShow() == dogshow);
	assert(newDog.dogToString() == ("Name: " + newDog.getName() + " | Breed: " + newDog.getBreed() + " | Age: " + to_string(newDog.getAge()) + " | Photograph: " + newDog.getPhotograph()));
	cout << "Model Tests are done" << endl;

}

void utilTests() {
	string test1, test2, test3;
	test1 = "TesT";
	test2 = "T e s T";
	test3 = "TesT";
	toLower(test1);
	assert(test1 == "test");
	delSpaces(test2);
	assert(test2 == "TesT");
	assert(compareLower(test1, test2) == true);
	cout << "Util Tests are done" << endl;

}


void serviceTest() {
	Service managerService = Service();
	managerService.addDog("Nameut", "bredut", "12", "photo");
	managerService.addDog("Nameut2", "bredut2", "13", "photo");
	managerService.addDog("Nameut3", "bredut3", "14", "photo");
	assert(managerService.getSizeForDogsNotAddopted() == 3);
	assert(managerService.getSizeForDogsAddopted() == 0);
	managerService.updateDog("Nameut", "bredut", "name1", "bred1", "21", "newph");
	managerService.addoptDog("name1", "bred1");
	assert(managerService.getSizeForDogsAddopted() == 1);
	managerService.deleteDog("Nameut2", "bredut2");
	managerService.deleteDogAddopted("name1", "bred1");
	assert(managerService.getSizeForDogsAddopted() == 0);
	assert(managerService.getSizeForDogsNotAddopted() == 1);
	assert(managerService.verifyAddopt("Nameut3", "bredut3") == false);
	vector<Dog> indexes;
	managerService.searchDogByBreedAge(indexes, "","97");
	assert(indexes.size() == 0);
	vector<Dog> indexes2;
	managerService.searchDogByBreedAge(indexes2, "e", "98");
	assert(indexes2.size() == 0);

	managerService.addDog("Nameutt", "bredutt", "12", "photo");
	managerService.addDog("Nameutt2", "bredutt2", "13", "photo");
	managerService.addDog("Nameutt3", "bredutt3", "14", "photo");

	managerService.addoptDog(1);
	assert(managerService.verifyAddopt("Nameutt", "bredutt") == true);
	assert(managerService.verifyAddoptedDogExist("nameutt", "bredutt") == true);
	assert(managerService.verifyDogExist("nameutt3", "bredutt3") == true);
	assert(managerService.verifyAddoptedDogExist("nameuttewq", "breduttqweq") == false);
	assert(managerService.verifyDogExist("namwqeeutt3", "brqweedutt3") == false);
	managerService.getAllElementsAddopted();
	managerService.getAllElementsNotAddopted();
	Dog* dogfound = managerService.searchDogByIndex(1);
	assert(dogfound != NULL);
	cout << "Service Tests are done" << endl;
}

void repositoryTest() {
	Repository repo = Repository();
	Dog newDog2 = Dog("Breed", "NameB", 11, "Photography");
	Dog newDog3 = Dog("BreedK", "NameC", 12, "Photography");
	Dog newDog4 = Dog("BreedA", "NameB", 13, "Photography");
	Dog newDog5 = Dog("BreedB", "NameA", 14, "Photography");
	repo.addDog(newDog2);
	assert(repo.getSizeOfDogs() == 1);
	repo.addDog(newDog3);
	assert(repo.getSizeOfDogs() == 2);
	repo.deleteDog(newDog3);
	assert(repo.getSizeOfDogs() == 1);
	repo.addDog(newDog3);
	repo.addDog(newDog4);
	repo.addDog(newDog5);
	repo.addoptDog(0);
	assert(repo.getSizeOfDogs() == 3);
	assert(repo.getSizeOfDogsAddopted() == 1);
	repo.addoptDog("NameA","BreedB");
	assert(repo.getSizeOfDogsAddopted() == 2);
	repo.getAllElements();
	repo.getAllElementsAddopted();
	Dog searchDog = repo.getAddoptedDogForUpdate("NameA", "BreedB");
	assert(searchDog == newDog5);
	Dog* nullDog = repo.searchDogByIndex(10);
	assert(nullDog == NULL);
	searchDog = *repo.searchDogByIndex(0);
	assert(searchDog == newDog3);
	repo.deleteAddoptedDog(newDog2);
	assert(repo.getSizeOfDogsAddopted() == 1);
	repo.updateDog(newDog5, "newname", "newbreed", 9, "newphoto");
	cout << "Repo Tests are done" << endl;
}



void callTests() {
	dogTests();
	utilTests();
	repositoryTest();
	serviceTest();
	cout << endl << endl;
}
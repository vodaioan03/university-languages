#include "MongoDB.h"


void MongoDB::loadData()
{
	try
	{
		res = stmt->executeQuery("SELECT * FROM animals");

		while (res->next()) {
			string breed = res->getString("breed");
			string name = res->getString("name");
			int age = res->getInt("age");
			string photograph = res->getString("photograph");
			bool adopted = res->getBoolean("adopted");

			Dog dog(breed, name, age, photograph);
			if (adopted == 1) {
				dog.setAdopted(true);
				this->addoptions.push_back(dog);
			}
			else {
				this->dogs.push_back(dog);
			}
		}
		cout << "File loaded!" << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
	
}

MongoDB::MongoDB()
{
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
		stmt = con->createStatement();
		stmt->execute("CREATE DATABASE IF NOT EXISTS " + this->database);
		con->setSchema(this->database);
		stmt->execute("CREATE TABLE IF NOT EXISTS animals (id INT PRIMARY KEY AUTO_INCREMENT, breed VARCHAR(255), name VARCHAR(255), age INT, photograph VARCHAR(255), adopted BOOLEAN)");
	}
	catch (sql::SQLException e)
	{
	}
	this->loadData();
}

MongoDB::~MongoDB()
{
	delete pstmt;
	delete con;
	delete res;
}

void MongoDB::addDog(Dog dogAdd)
{
	this->dogs.push_back(dogAdd);
	this->addDogSQL(dogAdd);
}

void MongoDB::addDogSQL(Dog dogadd)
{
	string insertQuery = "INSERT INTO animals (breed, name, age, photograph, adopted) VALUES (?, ?, ?, ?, ?)";
	unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(insertQuery));

	pstmt->setString(1, dogadd.getBreed()); 
	pstmt->setString(2, dogadd.getName()); 
	pstmt->setInt(3, dogadd.getAge()); 
	pstmt->setString(4, dogadd.getPhotograph()); 
	pstmt->setBoolean(5, dogadd.getAdopted()); 

	pstmt->executeUpdate();
}

void MongoDB::deleteDog(Dog dogDelete)
{
	int positionForDelete = this->getPositionForDog(dogDelete);
	this->dogs.erase(this->dogs.begin() + positionForDelete);
}
void MongoDB::deleteAddoptedDog(Dog dogDelete)
{
	int positionForDelete = this->getPositionForAddoptedDog(dogDelete);
	string deleteQuery = "DELETE FROM animals WHERE name = ?";
	unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(deleteQuery));

	pstmt->setString(1, dogDelete.getName());
	pstmt->executeUpdate();

	this->addoptions.erase(this->addoptions.begin() + positionForDelete);

}

void MongoDB::updateDog(Dog& dogUpdate, string newName, string newBreed, int newAge, string newPhotograph) {
	string updateQuery = "UPDATE animals SET breed = ?, name = ?, age = ?, photograph = ? WHERE name = ?";
	unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(updateQuery));

	pstmt->setString(1, newBreed);
	pstmt->setString(2, newName);
	pstmt->setInt(3, newAge);
	pstmt->setString(4, newPhotograph);
	pstmt->setString(5, dogUpdate.getName());

	pstmt->executeUpdate();

	dogUpdate.setAge(newAge);
	dogUpdate.setName(newName);
	dogUpdate.setBreed(newBreed);
	dogUpdate.setPhotograph(newPhotograph);
}

Dog* MongoDB::searchDogByIndex(int index)
{
	if (index < 0 || index > this->dogs.size()) return NULL;
	return &this->dogs[index];
}

Dog* MongoDB::getDogForUpdate(string name, string breed)
{
	Dog found{};
	for (Dog as : this->dogs) {
		if (compareLower(as.getName(), name) && compareLower(as.getBreed(), breed)) {
			return &this->dogs[this->getPositionForDog(as)];
		}
	}
	return NULL;
}

Dog MongoDB::getAddoptedDogForUpdate(string name, string breed)
{
	vector<Dog> dogsFound;
	copy_if(this->addoptions.begin(), this->addoptions.end(), back_inserter(dogsFound), [&](Dog& dog) {return isDogAddopted(dog, name, breed); });
	if (dogsFound.size() == 0) throw Exceptions().dogNotExist();
	return dogsFound[0];
}

vector<Dog> MongoDB::getAllElements()
{
	return this->dogs;
}

int MongoDB::getSizeOfDogs() {
	return this->dogs.size();
}

vector<Dog> MongoDB::getAllElementsAddopted()
{
	return this->addoptions;
}

vector<Dog> MongoDB::getAllElementsAddoptedPrint()
{
	return this->addoptions;
}

int MongoDB::getSizeOfDogsAddopted() {
	return this->addoptions.size();
}

void MongoDB::addoptDog(string name, string breed) {
	auto it = find_if(this->dogs.begin(), this->dogs.end(), [&](Dog& as) {
		return compareLower(as.getName(), name) && compareLower(as.getBreed(), breed);
		});
	if (it != this->dogs.end()) {
		Dog found = *it;
		found.setAdopted(true);

		string updateQuery = "UPDATE animals SET adopted = ? WHERE name = ?";
		unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(updateQuery));

		pstmt->setBoolean(1, true);
		pstmt->setString(2, found.getName());

		pstmt->executeUpdate();
		this->dogs.erase(it);
		this->addoptions.push_back(found);
	}

}

void MongoDB::addoptDog(int index) {
	Dog dog = this->dogs[index];
	dog.setAdopted(true);
	string updateQuery = "UPDATE animals SET adopted = ? WHERE name = ?";
	unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(updateQuery));

	pstmt->setBoolean(1, true);
	pstmt->setString(2, dog.getName());

	pstmt->executeUpdate();
	this->dogs.erase(this->dogs.begin() + index);
	this->addoptions.push_back(dog);
}

int MongoDB::getPositionForDog(Dog elem)
{
	int index = 0;
	for (Dog as : this->dogs) {
		if (as == elem) {
			return index;
		}
		index++;
	}
	throw Exceptions().dogNotExist();
}

int MongoDB::getPositionForAddoptedDog(Dog elem)
{
	int index = 0;
	for (Dog as : this->addoptions) {
		if (as == elem) {
			return index;
		}
		index++;
	}
	throw Exceptions().dogNotExist();
}

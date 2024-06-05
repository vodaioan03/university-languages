#include "service.h"

void service::addSchool(string name, string longitutde, string latitude, string date)
{
	string address = longitutde + ", " + latitude;
	for (int i = 0; i < this->repo.getSize(); i++) {
		model school = this->repo.getElement(i);
		if (school.getName() == name && school.getAddress() == address) {
			throw exception("School already exists.");
		}
	}
	model school = model(name, longitutde, latitude, date);
	this->repo.addElement(school);
}

bool sortName(model elem1, model elem2) {
	return elem1.getName() < elem2.getName();
}

void service::findSchools(string longitude, string latitude, vector<model>& indexes)
{
	double longitudedD = stod(longitude), latitudeD = stod(latitude);
	double longitudeFound, latitudeFound;
	double diff1=-1, diff2=-1, diff3=-1;
	int index1=-1, index2=-1, index3=-1;
	vector<double> diffForIndexes;
	for (int i = 0; i < this->repo.getSize(); i++) {
		model elem = this->repo.getElement(i);
		latitudeFound = stod(elem.getLatitude());
		longitudeFound = stod(elem.getLongitutde());
		double diff = (longitudedD - longitudeFound) * (longitudedD - longitudeFound) + (latitudeD - latitudeFound) * (latitudeD - latitudeFound);
		if (diff1 == -1) {
			diff1 = diff;
			index1 = i;
		}
		else if (diff2 == -1) {
			if (diff < diff1) {
				diff2 = diff1;
				index2 = index1;
				diff1 = diff;
				index1 = i;
			}
			else {
				diff2 = diff;
				index2 = i;
			}
			
		}
		else if (diff3 == -1) {
			if (diff < diff1) {
				diff3 = diff2;
				index3 = index2;
				diff2 = diff1;
				index2 = index1;
				diff1 = diff;
				index1 = i;
			}
			else if (diff < diff2) {
				diff3 = diff2;
				index3 = index2;
				diff2 = diff;
				index2 = i;
			}
			else {
				diff3 = diff;
				index3 = i;
			}
		}
		else {
			if (diff < diff1) {
				diff3 = diff2;
				index3 = index2;
				diff2 = diff1;
				index2 = index1;
				diff1 = diff;
				index1 = i;
			}
			else if (diff < diff2) {
				diff3 = diff2;
				index3 = index2;
				diff2 = diff;
				index2 = i;
			}
			else if (diff < diff3) {
				diff3 = diff;
				index3 = i;
			}
		}
	}
	indexes.push_back(this->repo.getElement(index1));
	indexes.push_back(this->repo.getElement(index2));
	indexes.push_back(this->repo.getElement(index3));
	sort(indexes.begin(), indexes.end(), sortName);

}

int service::getSizeOfSchools()
{
	return this->repo.getSize();
}

model service::getElemt(int position)
{
	return this->repo.getElement(position);
}

string service::getStringForElem(int position)
{
	return this->repo.getElement(position).toString();
}



#include "domain.h"


Medicine createMedicine(char* name, int concentration, int quantity, int price) {
	//Create object for telem
	Medicine m;
	m.name = (char*)malloc((strlen(name)+1) * sizeof(char));
	strcpy(m.name, name);
	m.concentration = concentration;
	m.quantity = quantity;
	m.price = price;

	return m;
}

Medicine deleteMedicine(Medicine* medic) {
	//delete object
	free(medic);
}

Medicine updateMedicine(Medicine* medic, char* newName, int newConcentration, int newQuantity, int newPrice) {
	//Update info for medicine
	medic->name = (char*)realloc(medic->name, (strlen(newName) + 1)*sizeof(char));
	strcpy(medic->name, newName);
	medic->concentration = newConcentration;
	medic->price = newPrice;
	medic->quantity = newQuantity;
}

char* getMedicineName(Medicine* medic) {
	//Return medicine name
	return medic->name;
}

int getMedicineConcentration(Medicine* medic) {
	//Return medicine concentration
	return medic->concentration;
}

int getMedicineQuantity(Medicine* medic) {
	//Return medicine quantity
	return medic->quantity;
}
int getMedicinePrice(Medicine* medic) {
	//Return medicine price
	return medic->price;
}

void setMedicinePrice(Medicine* medic, int value){
	// Set medidince price
	medic->price = value;
}

void setMedicineQuantity(Medicine* medic, int value) {
	//Set medicine quantity
	medic->quantity = value;
}

void setMedicineConcentration(Medicine* medic, int value) {
	//Set medicine concentration
	medic->concentration = value;
}
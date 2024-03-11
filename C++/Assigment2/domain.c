#include "domain.h"


Medicine createMedicine(char* name, int concentration, int quantity, int price) {

	Medicine m;
	m.name = (char*)malloc((strlen(name)+1) * sizeof(char));
	strcpy(m.name, name);
	m.concentration = concentration;
	m.quantity = quantity;
	m.price = price;

	return m;
}

Medicine deleteMedicine(Medicine* medic) {
	free(medic);
}

Medicine updateMedicine(Medicine* medic, char* newName, int newConcentration, int newQuantity, int newPrice) {
	medic->name = (char*)realloc(medic->name, (strlen(newName) + 1)*sizeof(char));
	strcpy(medic->name, newName);
	medic->concentration = newConcentration;
	medic->price = newPrice;
	medic->quantity = newQuantity;
}

char* getMedicineName(Medicine* medic) {
	return medic->name;
}

int getMedicineConcentration(Medicine* medic) {
	return medic->concentration;
}

int getMedicineQuantity(Medicine* medic) {
	return medic->quantity;
}
int getMedicinePrice(Medicine* medic) {
	return medic->price;
}
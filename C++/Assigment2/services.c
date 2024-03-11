#include "services.h"

void addMedicineLogic(Repository* repository, char* nameMedic, int concentrationMedic, int quantityMedic, int priceMedic) {
	int medicExist = 0;
	for (int i = 0; i < getSizePharmacy(repository->pharmacy); i++) {
		if (strcmp(nameMedic, getMedicineName(getElemByID(repository->pharmacy,i))) == 0 && getMedicineConcentration(getElemByID(repository->pharmacy,i)) == concentrationMedic) {
			addQuantity(repository->pharmacy, i, quantityMedic);
			medicExist = 1;
		}
	}
	if (!medicExist) {
		addMedicamentToPharmacy(repository, nameMedic, concentrationMedic, quantityMedic, priceMedic);
	}
}

void deleteMedicineLogic(Repository* repository, char* nameMedic, int concentration) {
	int indexName = -1;
	int i = 0;
	for (i = 0; i < getSizePharmacy(repository->pharmacy); i++) {
		if (strcmp(nameMedic, getMedicineName(getElemByID(repository->pharmacy, i))) == 0 && getMedicineConcentration(getElemByID(repository->pharmacy, i)) == concentration) {
			indexName = i;
			break;
		}
	}
	if (indexName != -1) {
		deleteMedicamentFromPharmacy(repository, indexName);
	}
}

void updateMedicineLogic(Repository* repository, char* nameMedic, int concentration, char* newName, int newConcentration, int newQuantity, int newPrice) {
	int indexName = -1;
	int i = 0;
	for (i = 0; i < getSizePharmacy(repository->pharmacy); i++) {
		if (strcmp(nameMedic, getMedicineName(getElemByID(repository->pharmacy, i))) == 0 && getMedicineConcentration(getElemByID(repository->pharmacy, i)) == concentration) {
			indexName = i;
			break;
		}
	}
	if (indexName != -1) {
		updateMedicine(getElemByID(repository->pharmacy, indexName), newName, newConcentration, newQuantity, newPrice);
	}

}

void lowerString(char* string) {
	for (int i = 0; i < strlen(string); i++) {
		string[i] = tolower(string[i]);
	}
}

int compareString(char* string1, char* string2) {
	return strcmp(string1, string2);
}

void sortArrayByNameAscending(Repository* repository,int* sizeIndex, int* arr) {
	for (int i = 0; i < *sizeIndex; i++) {
		char string1[100];
		
		for (int j = i + 1; j < *sizeIndex; j++) {
			strcpy(string1, getMedicineName(getElemByID(repository->pharmacy, arr[i])));
			lowerString(string1);
			char string2[100];
			strcpy(string2, getMedicineName(getElemByID(repository->pharmacy, arr[j])));
			lowerString(string2);
			if (compareString(string2, string1)<0) {
				int aux = arr[i];
				arr[i] = arr[j];
				arr[j] = aux;
			}
		}
	}
}
void sortArrayByNameDescending(Repository* repository, int* sizeIndex, int* arr) {
	for (int i = 0; i < *sizeIndex; i++) {
		char string1[100];

		for (int j = i + 1; j < *sizeIndex; j++) {
			strcpy(string1, getMedicineName(getElemByID(repository->pharmacy, arr[i])));
			lowerString(string1);
			char string2[100];
			strcpy(string2, getMedicineName(getElemByID(repository->pharmacy, arr[j])));
			lowerString(string2);
			if (compareString(string1, string2) < 0) {
				int aux = arr[i];
				arr[i] = arr[j];
				arr[j] = aux;
			}
		}
	}
}


//Sorttare facuta la b pentru ca la c nu cere sortat.
void searchAllMedicineString(Repository* repository, char* searchName, int* sizeIndex, int** indexFound,int sortNumber) {
	int i = 0;
	int lenName = strlen(searchName);
	char nameString[100];
	lowerString(searchName);
	for (i = 0; i < getSizePharmacy(repository->pharmacy); i++) {
		strcpy(nameString,getMedicineName(getElemByID(repository->pharmacy, i)));
		lowerString(nameString);
		if (strstr(nameString, searchName)) {
			(*indexFound)[(*sizeIndex)] = i;
			(*sizeIndex)++;
		}
	}
	if (sortNumber == 1) { sortArrayByNameAscending(repository, sizeIndex, *indexFound); }
	else sortArrayByNameDescending(repository, sizeIndex, *indexFound);
	
}



//TODO de facut sa trimit functia ca parametru si sa sortez si aici crescator sau descrescator dupa cantitate
void showAllMedicineBySupply(Repository* repository, int minimSupply, int* sizeIndex, int** indexFound,int sortNumber) {
	int i;
	for (i = 0; i < (getSizePharmacy(repository->pharmacy)); i++) {
		if (getMedicineQuantity(getElemByID(repository->pharmacy, i)) < minimSupply) {
			(*indexFound)[(*sizeIndex)] = i;
			(*sizeIndex)++;
		}
	}
	if(sortNumber == 1) { sortArrayByNameAscending(repository, sizeIndex, *indexFound); }
	else sortArrayByNameDescending(repository, sizeIndex, *indexFound);
}

//TODO de facut
void undoOperation() {
	printf("You need to write code here!\n");
}

//TODO de facut
void redoOperation() {
	printf("You need to write code here!\n");
}
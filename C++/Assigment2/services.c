#include "services.h"

Repository* createPharmacyLogic(int maxSize) {
	return createPharmacy(maxSize);
}

void lowerString(char* string) {
	//Transform a string in lower 
	for (int i = 0; i < strlen(string); i++) {
		string[i] = tolower(string[i]);
	}
}

int compareString(char* string1, char* string2) {
	//Compare two given strngs
	return strcmp(string1, string2);
}

void addMedicineLogic(Repository* repository, char* nameMedic, int concentrationMedic, int quantityMedic, int priceMedic) {
	//Add medicine in repository, only logic part
	int medicExist = 0;
	for (int i = 0; i < getSizeArray(getPharmacy(repository)); i++) {
		
		if (strcmp(nameMedic, getMedicineName(getElemByID(getPharmacy(repository),i))) == 0 && getMedicineConcentration(getElemByID(getPharmacy(repository),i)) == concentrationMedic) {
			addQuantity(repository, i, quantityMedic);
			medicExist = 1;
		}
	}
	if (!medicExist) {
		Medicine newMedic = createMedicineRepo(repository,nameMedic, concentrationMedic, quantityMedic, priceMedic);
		addMedicamentToPharmacy(repository, newMedic);
	}
}

void deleteMedicineLogic(Repository* repository, char* nameMedic, int concentration) {
	//Delete a medicine from repository
	int indexName = -1;
	int i = 0;
	lowerString(nameMedic);
	char* newName[101];
	for (i = 0; i < getSizeArray(getPharmacy(repository)); i++) {
		strcpy(newName, getMedicineName(getElemByID(getPharmacy(repository), i)));
		lowerString(newName);
		if (strcmp(nameMedic, newName) == 0 && getMedicineConcentration(getElemByID(getPharmacy(repository), i)) == concentration) {
			indexName = i;
			break;
		}
	}
	if (indexName != -1) {
		deleteMedicamentFromPharmacy(repository, indexName);
	}
}

void updateMedicineLogic(Repository* repository, char* nameMedic, int concentration, char* newName, int newConcentration, int newQuantity, int newPrice) {
	//Update info for medicine in logic
	int indexName = -1;
	int i = 0;
	for (i = 0; i < getSizeArray(getPharmacy(repository)); i++) {
		if (strcmp(nameMedic, getMedicineName(getElemByID(getPharmacy(repository), i))) == 0 && getMedicineConcentration(getElemByID(getPharmacy(repository), i)) == concentration) {
			indexName = i;
			break;
		}
	}
	if (indexName != -1) {
		updateMedicamentfromPharmacy(repository,indexName,getElemByID(getPharmacy(repository), indexName), newName, newConcentration, newQuantity, newPrice);
	}
}

void sortArrayByNameAscending(Repository* repository,int* sizeIndex, int* arr) {
	//Sort a given array ascending
	for (int i = 0; i < *sizeIndex; i++) {
		char string1[100];
		
		for (int j = i + 1; j < *sizeIndex; j++) {
			strcpy(string1, getMedicineName(getElemByID(getPharmacy(repository), arr[i])));
			lowerString(string1);
			char string2[100];
			strcpy(string2, getMedicineName(getElemByID(getPharmacy(repository), arr[j])));
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
	//Sort a given array descending by name
	for (int i = 0; i < *sizeIndex; i++) {
		char string1[100];

		for (int j = i + 1; j < *sizeIndex; j++) {
			strcpy(string1, getMedicineName(getElemByID(getPharmacy(repository), arr[i])));
			lowerString(string1);
			char string2[100];
			strcpy(string2, getMedicineName(getElemByID(getPharmacy(repository), arr[j])));
			lowerString(string2);
			if (compareString(string1, string2) < 0) {
				int aux = arr[i];
				arr[i] = arr[j];
				arr[j] = aux;
			}
		}
	}
}


void searchAllMedicineString(Repository* repository, char* searchName, int* sizeIndex, int** indexFound, SortFunction functionSort) {
	//Search all mediicne string who matches with given string
	int i = 0;
	int lenName = strlen(searchName);
	char nameString[100];
	lowerString(searchName);
	for (i = 0; i < getSizeArray(getPharmacy(repository)); i++) {
		strcpy(nameString,getMedicineName(getElemByID(getPharmacy(repository), i)));
		lowerString(nameString);
		if (strstr(nameString, searchName)) {
			(*indexFound)[(*sizeIndex)] = i;
			(*sizeIndex)++;
		}
	}
	(*functionSort)(repository, sizeIndex, *indexFound);
	
}

void searchAllMedicineQuantity(Repository* repository, int quantitySearcb, int* sizeIndex, int** indexFound, SortFunction functionSort) {
	//Search medicine by quantity
	int i = 0;
	for (i = 0; i < getSizeArray(getPharmacy(repository)); i++) {
		if (getMedicineQuantity(getElemByID(getPharmacy(repository),i)) == quantitySearcb) {
			(*indexFound)[(*sizeIndex)] = i;
			(*sizeIndex)++;
		}
	}
	(*functionSort)(repository, sizeIndex, *indexFound);
}

void showAllMedicineBySupply(Repository* repository, int minimSupply, int* sizeIndex, int** indexFound, SortFunction functionSort) {
	//Search all medicine who are smaller than supply
	int i;
	for (i = 0; i < (getSizeArray(getPharmacy(repository))); i++) {
		if (getMedicineQuantity(getElemByID(getPharmacy(repository), i)) < minimSupply) {
			(*indexFound)[(*sizeIndex)] = i;
			(*sizeIndex)++;
		}
	}
	(*functionSort)(repository, sizeIndex, *indexFound);
}

int undoOperationLogic(Repository* repository) {
	//Undo operation logical
	if (getPosUndo(repository) > 1) {
		undoOperation(repository);
		return getPosUndo(repository);
	}
	else {
		return 0;
	}
}

int redoOperationLogic(Repository* repository) {
	//Redo operational logic
	if (getPosRedo(repository) > 1) {
		redoOperation(repository);
		return getPosRedo(repository);
	}
	else {
		return 0;
	}
}

int getLogicSizePharmacy(Repository* repo) {
	//Return size of pharmacy
	return getSizeArray(getPharmacy(repo));
}

void getLogicalPrint(Repository* repository,int position, char** textInfo) {
	//Set print for text
	getPrintText(repository, position,textInfo);
}
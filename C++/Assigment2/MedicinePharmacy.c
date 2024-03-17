#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include "tests.h"
#include "services.h"


void printMedicine(Repository* repository, int id) {
	char* text;
	text = (char*)malloc(1000 * sizeof(char));
	getLogicalPrint(repository, id, &text);
	printf("%s", text);
	free(text);
}


void printMenu() {

	printf("= = = = = Pharmacy Menu = = = = =\n");
	printf("1. Add medicine(Name,Concentration,Quantity,Price).\n");
	printf("2. Delete medicine(Name and Concentration).\n");
	printf("3. Update medicine(Name and Concentration).\n");
	printf("4. See all medicine containing a given string.\n");
	printf("5. Show all medicines that are in short supply, give quantity.\n");
	printf("6. Undo last operation.\n");
	printf("7. Redo last operation.\n");
	printf("8. Exit.\n");
}

int sortingChoose() {
	int sortOrdin;
	printf("\nChoose Sorting");
	printf("\n1. Ascending");
	printf("\n2. Descending\n");
	printf("Choose Sorting [1/2]:");
	scanf("%d", &sortOrdin);
	if (sortOrdin != 1 && sortOrdin != 2) return 0;
	return sortOrdin;

}
int sortingChooseNameQuantity() {
	int sortOrdin;
	printf("\nChoose Sorting");
	printf("\n1. Name");
	printf("\n2. Quantity\n");
	printf("Choose Sorting [1/2]:");
	scanf("%d", &sortOrdin);
	if (sortOrdin != 1 && sortOrdin != 2) return 0;
	return sortOrdin;

}

//TODO De revizuit
void manageOperation(int operation, Repository* repository) {
	char name[100];
	int concentration;
	int quantity;
	int price;
	int sizeIndexFound = 0;
	int sortOrdin = 0;
	int nameSort = 0;
	int* indexFound = (int*)malloc(getLogicSizePharmacy(repository) * sizeof(int));
	int opSucces = 0;
	switch (operation)
	{
	case 1:
		printf("\n[1/4]Type the name for medicine:");
		scanf("%s", name);
		printf("\n[2/4]Type the concentration for %s:", name);
		scanf("%d", &concentration);
		printf("\n[3/4]Type the quantity for %s:", name);
		scanf("%d", &quantity);
		printf("\n[4/4]Type the price for %s:", name);
		scanf("%d", &price);
		addMedicineLogic(repository,name, concentration, quantity, price);
		printf("Medicine added!\n");
		break;
	case 2:
		if (getLogicSizePharmacy(repository) == 0) {
			printf("\n\nPharmacy is empty. First you need to add a medicine.\n\n");
			break;
		}
		else {
			printf("\n[1/2]Type the name for medicine:");
			scanf("%s", name);
			printf("\n[2/2]Type the concentration for %s:", name);
			scanf("%d", &concentration);
			printf("");
			deleteMedicineLogic(repository, name, concentration);
		}
		break;
	case 3:
		if (getLogicSizePharmacy(repository) == 0) {
			printf("\n\nPharmacy is empty. First you need to add a medicine.\n\n");
			break;
		}
		else {
			printf("\n[1/6]Type the name for medicine:");
			scanf("%s", name);
			printf("\n[2/6]Type the concentration for %s:", name);
			scanf("%d", &concentration);
			char newName[30];
			int newConc;
			int newQuantity;
			int newPrice;
			printf("\n[3/6] Type the new name for %s: ",name);
			scanf("%s", newName);
			printf("\n[4/6] Type nre concentration for %s: ",newName);
			scanf("%d", &newConc);
			printf("\n[5/6] Type new quantity for %s: ",newName);
			scanf("%d", &newQuantity);
			printf("\n[6/6] Type new price for %s: ",newName);
			scanf("%d", &newPrice);
			updateMedicineLogic(repository, name, concentration,newName,newConc,newQuantity,newPrice);
			break;
		}
	case 4:
		nameSort = sortingChooseNameQuantity();
		if (nameSort == 0) return;
		if (nameSort == 2) {
			printf("\n[1/1] Type the quantity for the medicine: ");
			getchar();
			fgets(name, sizeof(name), stdin);
			name[strcspn(name, "\n")] = '\0';
			sortOrdin = sortingChoose();
			int quantitySearch = atoi(name);
			if (strlen(name) == 0) { printf("\nYou can't search with empty quantity. If you wan't to see entire list, search by name with empty string."); }
			if (sortOrdin == 0) return;
			if (sortOrdin == 1) {
				searchAllMedicineQuantity(repository, quantitySearch, &sizeIndexFound, &indexFound, &sortArrayByNameAscending);
			}
			else {
				searchAllMedicineQuantity(repository, quantitySearch, &sizeIndexFound, &indexFound, &sortArrayByNameDescending);
			}
			printf("\n %d results found! \n", sizeIndexFound);
			for (int i = 0; i < sizeIndexFound; i++) {
				printMedicine(repository, (indexFound)[i]);
			}
		}
		else if (nameSort == 1) {
			printf("\n[1/1] Type the name for the medicine: ");
			getchar();
			fgets(name, sizeof(name), stdin);
			name[strcspn(name, "\n")] = '\0';
			sortOrdin = sortingChoose();
			if (sortOrdin == 0) return;
			if (sortOrdin == 1) {
				searchAllMedicineString(repository, name, &sizeIndexFound, &indexFound, &sortArrayByNameAscending);
			}
			else {
				searchAllMedicineString(repository, name, &sizeIndexFound, &indexFound, &sortArrayByNameDescending);
			}
			printf("\n %d results found! \n", sizeIndexFound);
			for (int i = 0; i < sizeIndexFound; i++) {
				printMedicine(repository, (indexFound)[i]);
			}
		}
		break;
	case 5:
		printf("\n[1/1] Type the minimum supply for search:");
		scanf("%d", &quantity);
		sortOrdin = sortingChoose();
		if (sortOrdin == 0) return;
		if (sortOrdin == 1) {
			showAllMedicineBySupply(repository, quantity, &sizeIndexFound, &indexFound, &sortArrayByNameAscending);
		}
		else {
			showAllMedicineBySupply(repository, quantity, &sizeIndexFound, &indexFound, &sortArrayByNameDescending);
		}
		printf("\n %d results found! \n", sizeIndexFound);
		for (int i = 0; i < sizeIndexFound; i++) {
			printMedicine(repository, (indexFound)[i]);
		}
		break;
	case 6:
		opSucces = undoOperationLogic(repository);
		if (opSucces == 0) {
			printf("No more undos!\n");
		}
		else { printf("Undo succes! Remaining %d \n",opSucces); }
		break;
	case 7:
		opSucces = redoOperationLogic(repository);
		if (opSucces == 0) {
			printf("No more redos!\n");
		}
		else { printf("Redo succes! Remaining %d \n", opSucces); }
		break;
	case 8:
		if (indexFound != NULL) free(indexFound);
		destroyPharmacy(repository);
		_CrtDumpMemoryLeaks();
		printf("\n\nExiting! Wait...\n\n");
		exit(1);
		break;
	default:
		break;
	}
	if (indexFound != NULL) free(indexFound);
}

void operationInput(Repository* repository) {
	int operation = 0;
	printf("\nType the operation: ");
	scanf("%d", &operation);
	if (operation < 1 || operation > 8) {
		printf("Invalid operation. Choose between 1 and 8. Try again!\n");
	}
	else {
		manageOperation(operation, repository);
	}
}


void createEntryValues(Repository* repository) {

	addMedicineLogic(repository, "Paracetamol", 500, 100, 2);
	addMedicineLogic(repository, "Ibuprofen", 200, 50, 3);
	addMedicineLogic(repository, "Aspirina", 300, 80, 1);
	addMedicineLogic(repository, "Amoxicilina", 250, 30, 5);
	addMedicineLogic(repository, "Omeprazol", 20, 60, 4);
	addMedicineLogic(repository, "Cetirizina", 10, 25, 6);
	addMedicineLogic(repository, "Diazepam", 5, 40, 8);
	addMedicineLogic(repository, "Ranitidina", 150, 70, 2);
	addMedicineLogic(repository, "Metformina", 850, 20, 3);
	addMedicineLogic(repository, "Atorvastatina", 40, 15, 7);
	addMedicineLogic(repository, "Levocetirizina", 5, 55, 4);
	addMedicineLogic(repository, "Furosemida", 20, 45, 6);
	addMedicineLogic(repository, "Mometazona", 0, 10, 9);
	addMedicineLogic(repository, "Cefalexina", 250, 35, 5);
	addMedicineLogic(repository, "Sertralina", 50, 25, 7);
	addMedicineLogic(repository, "Loratadina", 10, 50, 4);
	addMedicineLogic(repository, "Clarithromicina", 500, 15, 8);
	addMedicineLogic(repository, "Naproxen", 250, 40, 3);
	addMedicineLogic(repository, "Ciprofloxacina", 500, 30, 6);
	addMedicineLogic(repository, "Aciclovir", 200, 20, 9);
}


int main()
{
	runAllTests();
	Repository* repository = createPharmacyLogic(5);
	//printf("Dynamic array generated!\n");
	createEntryValues(repository);

	while (1) {
		printMenu();
		operationInput(repository);
	}
	destroyPharmacy(repository);
	_CrtDumpMemoryLeaks();
	return 0;
}
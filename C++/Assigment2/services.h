#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include <ctype.h>
#include "repository.h"
#include "domain.h"


typedef void (*SortFunction)(TElem*);

void addMedicineLogic(Repository* repository, char* nameMedic, int concentrationMedic, int quantityMedic, int priceMedic);
void deleteMedicineLogic(Repository* repository, char* nameMedic, int concentration);
void updateMedicineLogic(Repository* repository, char* nameMedic, int concentration, char* newName, int newConcentration, int newQuantity, int newPrice);
void searchAllMedicineString(Repository* repository, char* searchName, int* sizeIndex, int** indexFound, SortFunction functionSort);
void searchAllMedicineQuantity(Repository* repository, int quantitySearcb, int* sizeIndex, int** indexFound, SortFunction functionSort);
void showAllMedicineBySupply(Repository* repository, int minimSupply, int* sizeIndex, int** indexFound, SortFunction functionSort);
void sortArrayByNameAscending(Repository* repository, int* sizeIndex, int* arr);
void sortArrayByNameDescending(Repository* repository, int* sizeIndex, int* arr);
int undoOperationLogic(Repository* repository);
int redoOperationLogic(Repository* repository);
int getLogicSizePharmacy(Repository* repo);
void getLogicalPrint(Repository* repository, int position, char** textInfo);
Repository* createPharmacyLogic(int maxSize);
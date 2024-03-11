#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include <ctype.h>
#include "repository.h"
#include "domain.h"

void addMedicineLogic(Repository* repository, char* nameMedic, int concentrationMedic, int quantityMedic, int priceMedic);
void deleteMedicineLogic(Repository* repository, char* nameMedic, int concentration);
void updateMedicineLogic(Repository* repository, char* nameMedic, int concentration, char* newName, int newConcentration, int newQuantity, int newPrice);
void searchAllMedicineString(Repository* repository, char* searchName, int* sizeIndex, int** indexFound, int sortOrdin);
void showAllMedicineBySupply(Repository* repository, int minimSupply, int* sizeIndex, int* indexFound,int sortOrdin);
void undoOperation();
void redoOperation();
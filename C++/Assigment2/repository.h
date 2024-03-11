#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include "domain.h"

typedef struct {
	int size;
	int maxSize;
	TElem* medicList;
} ArrayPharmacy;

typedef struct {
	ArrayPharmacy* pharmacy;
} Repository;

Repository* createPharmacy(int maxSize);
void destroyPharmacy(Repository* repository);
void addMedicamentToPharmacy(Repository* repository, char* nameMedic, int concentrationMedic, int quantityMedic, int priceMedic);
void addQuantity(Repository* repository, int index, int addQuantity);
void deleteMedicamentFromPharmacy(Repository* repository);
int getSizePharmacy(ArrayPharmacy* pharmacy);
int getMaxSizePharmacy(ArrayPharmacy* pharmacy);
TElem* getElemByID(ArrayPharmacy* pharmacy, int id);
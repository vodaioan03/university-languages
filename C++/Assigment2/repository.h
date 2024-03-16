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
	int maxSize;
	int posRedo;
	int posUndo;
	ArrayPharmacy* undoList;
	ArrayPharmacy* redoList;
}History;

typedef struct {
	TElem* listOfLEaks;
	ArrayPharmacy** listOfArrays;
	int positionLeaks;
	int maxSize;
	int positionArr;
} MemoryLeak;

typedef struct {
	ArrayPharmacy* pharmacy;
	History* history;
	MemoryLeak* memoryLeak;
} Repository;


Repository* createPharmacy(int maxSize);
void destroyPharmacy(Repository* repository);
void addMedicamentToPharmacy(Repository* repository, TElem medicAdd);
void addQuantity(Repository* repository, int index, int addQuantity);
void deleteMedicamentFromPharmacy(Repository* repository, int indexToDelete);
void updateMedicamentfromPharmacy(Repository* repository, int indexName, Medicine* medic, char* newName, int newConcentration, int newQuantity, int newPrice);
int getSizeArray(ArrayPharmacy* pharmacy);
int getMaxSizeArray(ArrayPharmacy* pharmacy);
TElem createMedicineRepo(Repository* repository, char* name, int concentration, int quantity, int price);
TElem* getElemByID(ArrayPharmacy* pharmacy, int id);
void addRedo(Repository* repository);
void addUndo(Repository* repository);
void undoOperation(Repository* repo);
void redoOperation(Repository* repo);
ArrayPharmacy* cloneArray(Repository* repo, ArrayPharmacy* arr);
void arrayCreated(Repository* repository, ArrayPharmacy* arrayc);
int getPosUndo(Repository* repository);
int getPosRedo(Repository* repository);
ArrayPharmacy* getPharmacy(Repository* repository);


/*
*/
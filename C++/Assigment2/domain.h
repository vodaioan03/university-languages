#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

typedef struct
{
	char* name;
	int concentration;
	int quantity;
	int price;
} Medicine;

typedef Medicine TElem;

Medicine createMedicine(char* name, int concentration, int quantity, int price);
Medicine deleteMedicine(Medicine* medic);
Medicine updateMedicine(Medicine* medic,char* newName, int newConcentration, int newQuantity, int newPrice);
char* getMedicineName(Medicine* medic);
int getMedicineConcentration(Medicine* medic);
int getMedicineQuantity(Medicine* medic);
int getMedicinePrice(Medicine* medic);
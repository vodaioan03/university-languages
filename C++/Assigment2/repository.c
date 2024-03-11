#include "repository.h"


int getSizePharmacy(ArrayPharmacy* pharmacy) {
	return pharmacy->size;
}

int getMaxSizePharmacy(ArrayPharmacy* pharmacy) {
	return pharmacy->maxSize;
}

void resize(ArrayPharmacy* pharmacy) {
	if (pharmacy == NULL) return;
	pharmacy->medicList = (TElem*)realloc(pharmacy->medicList, (getSizePharmacy(pharmacy) * 2) * sizeof(TElem));
}
TElem* getElemByID(ArrayPharmacy* pharmacy, int id) {
	return &pharmacy->medicList[id];
}

Repository* createPharmacy(int maxSize) {
	Repository* repository = (Repository*)malloc(sizeof(Repository));
	repository->pharmacy = (ArrayPharmacy*)malloc(1 * sizeof(ArrayPharmacy));
	if (repository->pharmacy == NULL) return NULL;
	repository->pharmacy->size = (int)0;
	repository->pharmacy->maxSize = maxSize;
	repository->pharmacy->medicList = (TElem*)malloc((*repository).pharmacy->maxSize * sizeof(TElem));
	if (repository->pharmacy->medicList == NULL) return NULL;
	return repository;
}

void destroyPharmacy(Repository* repository) {
	if (repository->pharmacy == NULL) return;
	for (int i = 0; i < getSizePharmacy(repository->pharmacy); i++) {
		free(repository->pharmacy->medicList[i].name);
	}
	free(repository->pharmacy->medicList);
	free(repository->pharmacy);
	if (repository == NULL) return;
	free(repository);
}

void addMedicamentToPharmacy(Repository* repository, char* nameMedic, int concentrationMedic, int quantityMedic, int priceMedic) {
	if (getSizePharmacy(repository->pharmacy) + 1 >= getMaxSizePharmacy(repository->pharmacy)) {
		resize(repository->pharmacy);
		if (repository->pharmacy->medicList == NULL) {
			exit(EXIT_FAILURE);
		}
	}
	repository->pharmacy->medicList[getSizePharmacy(repository->pharmacy)] = createMedicine(nameMedic, concentrationMedic, quantityMedic, priceMedic);
	(repository->pharmacy->size)++;
}

void addQuantity(Repository* repository, int index, int addQuantity) {
	repository->pharmacy->medicList[index].quantity += addQuantity;
}

void deleteMedicamentFromPharmacy(Repository* repository, int indexToDelete) {
	memmove(&repository->pharmacy->medicList[indexToDelete], &repository->pharmacy->medicList[indexToDelete + 1], (getSizePharmacy(repository->pharmacy) - indexToDelete - 1) * sizeof(Medicine));
	if (repository->pharmacy->medicList == NULL) {
		repository->pharmacy->medicList = (TElem*)calloc(1, sizeof(TElem));
	}
	(repository->pharmacy->size)--;

}
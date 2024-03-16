#include "repository.h"


ArrayPharmacy* getPharmacy(Repository* repository) {
	return repository->pharmacy;
}

int getSizeArray(ArrayPharmacy* arrayx) {
	return arrayx->size;
}
int getMaxSizeArray(ArrayPharmacy* arrayx) {
	return arrayx->maxSize;
}

void setArraySize(ArrayPharmacy* arrayx, int value) {
	arrayx->size = value;
}

void setArrayMaxSize(ArrayPharmacy* arrayx, int value) {
	arrayx->maxSize = value;
}

int getPosUndo(Repository* repository) {
	return repository->history->posUndo;
}

void setPosUndo(Repository* repository, int value) {
	repository->history->posUndo = value;
}

int getPosRedo(Repository* repository) {
	return repository->history->posRedo;
}

void setPosRedo(Repository* repository, int value) {
	repository->history->posRedo = value;
}

int getMaxSizeHistory(Repository* repository) {
	return repository->history->maxSize;
}

void setMaxSizeHistory(Repository* repository, int value) {
	repository->history->maxSize = value;
}

TElem* getMedicList(ArrayPharmacy* array) {
	return array->medicList;
}

int getLeakMaxSize(Repository* repository) {
	return repository->memoryLeak->maxSize;
}

void setLeakMaxSize(Repository* repository,int value) {
	repository->memoryLeak->maxSize = value;
}

int getMemoryPosArr(Repository* repository) {
	return repository->memoryLeak->positionArr;
}

void setMemoryPosArr(Repository* repository, int value) {
	repository->memoryLeak->positionArr = value;
}


ArrayPharmacy* getValueListOfArrays(Repository* repository, int position) {
	return repository->memoryLeak->listOfArrays[position];
}

ArrayPharmacy** getListOfArrays(Repository* repository) {
	return repository->memoryLeak->listOfArrays;
}
void setListOfArrays(Repository* repository, ArrayPharmacy** setValue) {
	repository->memoryLeak->listOfArrays = setValue;
}

void resizeMemory(Repository* repo) {
	repo->memoryLeak->maxSize = repo->memoryLeak->maxSize * 2;
	repo->memoryLeak->listOfLEaks = (TElem*)realloc(repo->memoryLeak->listOfLEaks, repo->memoryLeak->maxSize * sizeof(TElem));
	setListOfArrays(repo,(ArrayPharmacy*)realloc(repo->memoryLeak->listOfArrays, repo->memoryLeak->maxSize * sizeof(ArrayPharmacy)));
	
}

void setUndoListArray(Repository* repository, ArrayPharmacy* addArr) {
	repository->history->undoList = addArr;
}
void setRedoListArray(Repository* repository, ArrayPharmacy* addArr) {
	repository->history->redoList = addArr;
}

ArrayPharmacy* getUndoListArray(Repository* repository) {
	return repository->history->undoList;
}
ArrayPharmacy* getRedoListarray(Repository* repository) {
	return repository->history->redoList;
}


TElem copyElement(Repository* repo, TElem element) {
	return createMedicineRepo(repo, element.name, element.concentration, element.quantity, element.price);
}


ArrayPharmacy* cloneArray(Repository* repo, ArrayPharmacy* arr) {
	ArrayPharmacy* newArray = (ArrayPharmacy*)malloc(sizeof(ArrayPharmacy));

	newArray->maxSize = getMaxSizeArray(arr);
	newArray->size = getSizeArray(arr);
	newArray->medicList = (TElem*)malloc(newArray->maxSize * sizeof(TElem));
	for (int i = 0; i < getSizeArray(newArray); i++) {
		newArray->medicList[i] = copyElement(repo, *getElemByID(arr, i));
	}
	arrayCreated(repo, newArray);
	return newArray;
}

void addElementToListOfArrays(Repository* repository, ArrayPharmacy* valueArr,int position) {
	repository->memoryLeak->listOfArrays[position] = valueArr;
	if(position == getMemoryPosArr(repository)) setMemoryPosArr(repository, getMemoryPosArr(repository) + 1);
}


void arrayCreated(Repository* repository, ArrayPharmacy* arrayc) {
	if (getMemoryPosArr(repository) + 1 >= getLeakMaxSize(repository)) {
		resizeMemory(repository);
		if (getListOfArrays(repository) == NULL) {
			exit(EXIT_FAILURE);
		}
	}
	addElementToListOfArrays(repository, arrayc,getMemoryPosArr(repository));
}

void addUndoInRepository(Repository* repository) {
	if (getPosUndo(repository) + 1 >= getMaxSizeHistory(repository)) {
		setMaxSizeHistory(repository, getMaxSizeHistory(repository) * 2);
		int indexOfUndo = -1;
		int indexOfRedo = -1;
		for (int i = 0; i < repository->memoryLeak->positionArr; i++) {
			if (getValueListOfArrays(repository,i) == getUndoListArray(repository)) indexOfUndo = i;
			if (getValueListOfArrays(repository,i) == getRedoListarray(repository)) indexOfRedo = i;
		}
		setUndoListArray(repository, (ArrayPharmacy*)realloc(getUndoListArray(repository), getMaxSizeHistory(repository) * sizeof(ArrayPharmacy)));
		setRedoListArray(repository, (ArrayPharmacy*)realloc(getRedoListarray(repository), getMaxSizeHistory(repository) * sizeof(ArrayPharmacy)));
		addElementToListOfArrays(repository, getUndoListArray(repository), indexOfUndo);
		addElementToListOfArrays(repository, getRedoListarray(repository), indexOfRedo);
	}
	repository->history->undoList[repository->history->posUndo] = *cloneArray(repository, getPharmacy(repository));
	setPosUndo(repository,getPosUndo(repository) + 1);
}

void addNewUndo(Repository* repository) {
	addUndoInRepository(repository);
	setPosRedo(repository, 1);
}

void addUndo(Repository* repository) {
	addUndoInRepository(repository);
}

void undoOperation(Repository* repo) {
	addRedo(repo);
	repo->history->posUndo--;
	repo->pharmacy = &repo->history->undoList[repo->history->posUndo];
}

void redoOperation(Repository* repo) {
	addUndo(repo);
	repo->history->posRedo--;
	repo->pharmacy = &repo->history->redoList[repo->history->posRedo];
}

void addRedo(Repository* repository) {
	repository->history->redoList[repository->history->posRedo] = *cloneArray(repository, getPharmacy(repository));
	repository->history->posRedo++;
}

void resize(ArrayPharmacy* pharmacy) {
	if (pharmacy == NULL) return;
	pharmacy->medicList = (TElem*)realloc(pharmacy->medicList, (pharmacy->maxSize * 2) * sizeof(TElem));
	pharmacy->maxSize = pharmacy->maxSize * 2;
}
TElem* getElemByID(ArrayPharmacy* pharmacy, int id) {
	return &getMedicList(pharmacy)[id];
}

Repository* createPharmacy(int maxSize) {
	Repository* repository = (Repository*)malloc(sizeof(Repository));

	repository->memoryLeak = (MemoryLeak*)malloc(maxSize * sizeof(MemoryLeak));
	repository->memoryLeak->listOfLEaks = (TElem*)malloc(maxSize * sizeof(TElem));
	setListOfArrays(repository, (ArrayPharmacy**)malloc(maxSize * sizeof(ArrayPharmacy*)));
	setMemoryPosArr(repository, 0);
	repository->memoryLeak->positionLeaks = 0;
	setLeakMaxSize(repository, maxSize);

	repository->pharmacy = (ArrayPharmacy*)malloc(1 * sizeof(ArrayPharmacy));
	
	repository->history = (History*)malloc(1 * sizeof(History));
	
	if (getPharmacy(repository) == NULL) return NULL;
	if (repository->history == NULL) return NULL;
	if (repository->memoryLeak == NULL) return NULL;
	setArraySize(repository->pharmacy, 0);
	setArrayMaxSize(repository->pharmacy, maxSize);
	repository->pharmacy->medicList = (TElem*)malloc((*repository).pharmacy->maxSize * sizeof(TElem));

	setRedoListArray(repository, (ArrayPharmacy*)malloc(maxSize * sizeof(ArrayPharmacy)));
	repository->history->redoList->medicList = (TElem*)malloc(sizeof(TElem));
	setArraySize(repository->history->redoList,2);
	setUndoListArray(repository, (ArrayPharmacy*)malloc(maxSize * sizeof(ArrayPharmacy)));
	repository->history->undoList->medicList = (TElem*)malloc(sizeof(TElem));
	setArraySize(repository->history->redoList, 2);
	setPosRedo(repository, 1);
	setPosUndo(repository, 1);
	setMaxSizeHistory(repository, maxSize);
	if (getMedicList(getPharmacy(repository)) == NULL) return NULL;
	if (getUndoListArray(repository) == NULL) return NULL;
	if (getRedoListarray(repository) == NULL) return NULL;
	arrayCreated(repository, getPharmacy(repository));
	arrayCreated(repository, getUndoListArray(repository));
	arrayCreated(repository, getRedoListarray(repository));
	return repository;
}

void destroyPharmacy(Repository* repository) {
	if (getPharmacy(repository) == NULL) return;
	for (int i = 0; i < repository->memoryLeak->positionLeaks; i++) {
		free(repository->memoryLeak->listOfLEaks[i].name);
	}
	for (int i = 0; i < getMemoryPosArr(repository); i++) {
		free((*getValueListOfArrays(repository,i)).medicList);
		if(getValueListOfArrays(repository,i) != NULL) free(getValueListOfArrays(repository,i));
	}
	free(repository->memoryLeak->listOfLEaks);
	free(getListOfArrays(repository));
	free(repository->memoryLeak);
	free(repository->history);
	if (repository == NULL) return;
	free(repository);
}

void addMedicamentToPharmacy(Repository* repository, TElem medicAdd) {
	if (getSizeArray(getPharmacy(repository)) + 1 >= getMaxSizeArray(getPharmacy(repository))) {
		resize(getPharmacy(repository));
		if (getMedicList(getPharmacy(repository)) == NULL) {
			exit(EXIT_FAILURE);
		}
	}
	addNewUndo(repository);
	getMedicList(getPharmacy(repository))[getSizeArray(getPharmacy(repository))] = medicAdd;
	setArraySize(getPharmacy(repository), getSizeArray(getPharmacy(repository)) + 1);
}

void addQuantity(Repository* repository, int index, int addQuantity) {
	addNewUndo(repository);
	getMedicList(getPharmacy(repository))[index].quantity += addQuantity;
}

void deleteMedicamentFromPharmacy(Repository* repository, int indexToDelete) {
	addNewUndo(repository);
	memmove(&getMedicList(getPharmacy(repository))[indexToDelete], &getPharmacy(repository)->medicList[indexToDelete + 1], (getSizeArray(getPharmacy(repository)) - indexToDelete - 1) * sizeof(Medicine));
	if (getMedicList(getPharmacy(repository)) == NULL) {
		getPharmacy(repository)->medicList = (TElem*)calloc(1, sizeof(TElem));
	}
	setArraySize(getPharmacy(repository), getSizeArray(getPharmacy(repository)) - 1);
}

void updateMedicamentfromPharmacy(Repository* repository, int indexName,Medicine* medic, char* newName, int newConcentration, int newQuantity, int newPrice) {
	addNewUndo(repository);
	TElem newElem = createMedicineRepo(repository, newName, newConcentration, newQuantity, newPrice);
	getMedicList(getPharmacy(repository))[indexName] = newElem;
}

TElem createMedicineRepo(Repository* repository, char* name, int concentration, int quantity, int price) {
	TElem newMedic = createMedicine(name, concentration, quantity,price);
	if (repository->memoryLeak->positionLeaks + 1 >= getLeakMaxSize(repository)) {
		resizeMemory(repository);
		if (getMedicList(getPharmacy(repository)) == NULL) {
			exit(EXIT_FAILURE);
		}
	}
	int verifyOK = 1;
	for (int i = 0; i < repository->memoryLeak->positionLeaks; i++) {
		if (getValueListOfArrays(repository,i) == &newMedic) verifyOK = 0;
	}
	if (verifyOK) {
		repository->memoryLeak->listOfLEaks[repository->memoryLeak->positionLeaks] = newMedic;
		repository->memoryLeak->positionLeaks++;
	}
	return newMedic;
}
#include "repository.h"


ArrayPharmacy* getPharmacy(Repository* repository) {
	//Return pharmacy from repository
	return repository->pharmacy;
}

void setUndoListArray(Repository* repository, ArrayPharmacy* addArr) {
	//Set an array to undoList
	repository->history->undoList = addArr;
}
void setRedoListArray(Repository* repository, ArrayPharmacy* addArr) {
	//Set an array to redoList
	repository->history->redoList = addArr;
}

ArrayPharmacy* getUndoListArray(Repository* repository) {
	//Return pointer to undolist
	return repository->history->undoList;
}
ArrayPharmacy* getRedoListarray(Repository* repository) {
	//Return pointer to redolist
	return repository->history->redoList;
}

void setPharmacy(Repository* repository, ArrayPharmacy* value) {
	//Set pointer to pharmacy from repository
	repository->pharmacy = value;
}

int getSizeArray(ArrayPharmacy* arrayx) {
	//Return size of a given array
	return arrayx->size;
}
int getMaxSizeArray(ArrayPharmacy* arrayx) {
	//Return maxsize of a given array
	return arrayx->maxSize;
}

void setArraySize(ArrayPharmacy* arrayx, int value) {
	//Set size of a given array
	arrayx->size = value;
}

void setArrayMaxSize(ArrayPharmacy* arrayx, int value) {
	//set maxsize of a given array
	arrayx->maxSize = value;
}

int getPosUndo(Repository* repository) {
	//Return posundo from repository history
	return repository->history->posUndo;
}

History* getHistoryArr(Repository* repo) {
	// Return history repo
	return repo->history;
}

void setPosUndo(Repository* repository, int value) {
	//Set position undo for history
	repository->history->posUndo = value;
}

int getPosRedo(Repository* repository) {
	//Return undo positon from history
	return repository->history->posRedo;
}

void setPosRedo(Repository* repository, int value) {
	//Set position redo for history
	repository->history->posRedo = value;
}

int getMaxSizeHistory(Repository* repository) {
	//Return maxSize for history
	return repository->history->maxSize;
}

void setMaxSizeHistory(Repository* repository, int value) {
	//Set maxsize for history from repository
	repository->history->maxSize = value;
}

TElem* getMedicList(ArrayPharmacy* array) {
	//Return mediclist from a given array
	return array->medicList;
}

void setMedicList(ArrayPharmacy* arr, TElem* value) {
	//Set medicList from arr with pointer
	arr->medicList = value;
}

void setMedicListPosition(ArrayPharmacy* arr, TElem value, int position) {
	//Set medic list position for elemnt from a given position;
	getMedicList(arr)[position] = value;
}

int getLeakMaxSize(Repository* repository) {
	//Return leak max size from memoryleak
	return repository->memoryLeak->maxSize;
}

void setLeakMaxSize(Repository* repository,int value) {
	//Set maxsize for memoryleak from repo
	repository->memoryLeak->maxSize = value;
}

int getMemoryPosArr(Repository* repository) {
	//Return memory positionarray from repository
	return repository->memoryLeak->positionArr;
}

void setMemoryPosArr(Repository* repository, int value) {
	//Set positionarr with a given value for repository memoryleak;
	repository->memoryLeak->positionArr = value;
}

int getMemoryPosLeak(Repository* repository) {
	//Return memory positionleak from memoryleak
	return repository->memoryLeak->positionLeaks;
}

void setMemoryPosLeak(Repository* repository, int value) {
	//Set memoryleak positionleaks with a value
	repository->memoryLeak->positionLeaks = value;
}

MemoryLeak* getMemoryLeak(Repository* repository) {
	//Return memoryleak pointer from repository
	return repository->memoryLeak;
}


ArrayPharmacy* getValueListOfArrays(Repository* repository, int position) {
	//Return a element from listofarrays from a given position
	return repository->memoryLeak->listOfArrays[position];
}

ArrayPharmacy** getListOfArrays(Repository* repository) {
	//Return list with all arrays created
	return repository->memoryLeak->listOfArrays;
}

TElem* getValueListOfLeaks(MemoryLeak* memory, int index) {
	//Return a pointer to the value from listofleaks
	return &(memory->listOfLEaks[index]);
}

TElem* getListOfLeaks(MemoryLeak* memory) {
	//Return pointer to the listofleaks from memoryleak
	return memory->listOfLEaks;
}

void setElemLeaksOfLeaks(TElem* listLeaks, int position, TElem value) {
	//Set a value for element from lestofleaks
	listLeaks[position] = value;
}

void setListOfArrays(Repository* repository, ArrayPharmacy** setValue) {
	//Set pointer to the listofarrays from repository
	repository->memoryLeak->listOfArrays = setValue;
}

void setMemoryLeak(Repository* repository, MemoryLeak* value) {
	//Set pointer to memory leak
	repository->memoryLeak = value;
}

void setListOfLeaks(MemoryLeak* memory, TElem* value) {
	//Set pointer to the list of leaks
	memory->listOfLEaks = value;
}

void setHistory(Repository* repository, History* history) {
	//Set pointer to the history
	repository->history = history;
}

void resizeMemory(Repository* repo) {
	//Resize listofleaks memory from repository
	repo->memoryLeak->maxSize = repo->memoryLeak->maxSize * 2;
	repo->memoryLeak->listOfLEaks = (TElem*)realloc(repo->memoryLeak->listOfLEaks, repo->memoryLeak->maxSize * sizeof(TElem));
	setListOfArrays(repo,(ArrayPharmacy*)realloc(repo->memoryLeak->listOfArrays, repo->memoryLeak->maxSize * sizeof(ArrayPharmacy)));
	
}

TElem copyElement(Repository* repo, TElem element) {
	//Duplicate Telem for undo/redo
	return createMedicineRepo(repo, element.name, element.concentration, element.quantity, element.price);
}

void getPrintText(Repository* repository, int position, char** textt) {
	//Set printText for ui.
	sprintf(*textt, "[%d] Name: %s, Concentration: %d, Quantity: %d, Price: %d\n", position,
		repository->pharmacy->medicList[position].name,
		repository->pharmacy->medicList[position].concentration,
		repository->pharmacy->medicList[position].quantity,
		repository->pharmacy->medicList[position].price);
}


ArrayPharmacy* cloneArray(Repository* repo, ArrayPharmacy* arr) {
	//Return pointer to the new array cloned by this function[all elements are cloned and copied]
	ArrayPharmacy* newArray = (ArrayPharmacy*)malloc(sizeof(ArrayPharmacy));
	setArrayMaxSize(newArray, getMaxSizeArray(arr));
	setArraySize(newArray, getSizeArray(arr));
	setMedicList(newArray, (TElem*)malloc(getMaxSizeArray(newArray) * sizeof(TElem)));
	for (int i = 0; i < getSizeArray(newArray); i++) {
		getMedicList(newArray)[i] = copyElement(repo, *getElemByID(arr, i));
	}
	arrayCreated(repo, newArray);
	return newArray;
}

void addElementToListOfArrays(Repository* repository, ArrayPharmacy* valueArr,int position) {
	//Add element in listofarrays. at the end or at the given pos
	repository->memoryLeak->listOfArrays[position] = valueArr;
	if(position == getMemoryPosArr(repository)) setMemoryPosArr(repository, getMemoryPosArr(repository) + 1);
}


void arrayCreated(Repository* repository, ArrayPharmacy* arrayc) {
	//This function add in history arraypharmacy
	if (getMemoryPosArr(repository) + 1 >= getLeakMaxSize(repository)) {
		resizeMemory(repository);
		if (getListOfArrays(repository) == NULL) {
			exit(EXIT_FAILURE);
		}
	}
	addElementToListOfArrays(repository, arrayc,getMemoryPosArr(repository));
}

void addUndoInRepository(Repository* repository) {
	//AddUndo in repository
	if (getPosUndo(repository) + 1 >= getMaxSizeHistory(repository)) {
		setMaxSizeHistory(repository, getMaxSizeHistory(repository) * 2);
		int indexOfUndo = -1;
		int indexOfRedo = -1;
		for (int i = 0; i < getMemoryPosArr(repository); i++) {
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
	//Add new undo and  reset pos of redo
	addUndoInRepository(repository);
	setPosRedo(repository, 1);
}

void addUndo(Repository* repository) {
	//Move only in undo
	addUndoInRepository(repository);
}

void undoOperation(Repository* repo) {
	//Make undo operation
	addRedo(repo);
	setPosUndo(repo, getPosUndo(repo) - 1);
	setPharmacy(repo, &getUndoListArray(repo)[getPosUndo(repo)]);
}

void redoOperation(Repository* repo) {
	//Make redo operation
	addUndo(repo);
	setPosRedo(repo, getPosRedo(repo) - 1);
	setPharmacy(repo, &getRedoListarray(repo)[getPosRedo(repo)]);
	
}

void addRedo(Repository* repository) {
	//Add redo in history
	getRedoListarray(repository)[getPosRedo(repository)] = *cloneArray(repository, getPharmacy(repository));
	setPosRedo(repository, getPosRedo(repository) + 1);
}

void resize(ArrayPharmacy* pharmacy) {
	//Resize pharmacy repo
	if (pharmacy == NULL) return;
	setArrayMaxSize(pharmacy, getMaxSizeArray(pharmacy) * 2);
	setMedicList(pharmacy, (TElem*)realloc(getMedicList(pharmacy), getMaxSizeArray(pharmacy) * sizeof(TElem)));
}

TElem* getElemByID(ArrayPharmacy* pharmacy, int id) {
	//Return element from position id
	return &getMedicList(pharmacy)[id];
}

Repository* createPharmacy(int maxSize) {
	//Create all pharmacy, history, leaks etc
	Repository* repository = (Repository*)malloc(sizeof(Repository));

	setMemoryLeak(repository, (MemoryLeak*)malloc(maxSize * sizeof(MemoryLeak)));
	setListOfLeaks(getMemoryLeak(repository), (TElem*)malloc(maxSize * sizeof(TElem)));
	setListOfArrays(repository, (ArrayPharmacy**)malloc(maxSize * sizeof(ArrayPharmacy*)));
	setMemoryPosArr(repository, 0);
	setMemoryPosLeak(repository, 0);
	setLeakMaxSize(repository, maxSize);

	setPharmacy(repository, (ArrayPharmacy*)malloc(1 * sizeof(ArrayPharmacy)));

	setHistory(repository, (History*)malloc(1 * sizeof(History)));
	
	if (getPharmacy(repository) == NULL) return NULL;
	if (getHistoryArr(repository) == NULL) return NULL;
	if (getMemoryLeak(repository) == NULL) return NULL;
	setArraySize(getPharmacy(repository), 0);
	setArrayMaxSize(getPharmacy(repository), maxSize);
	setMedicList(getPharmacy(repository), (TElem*)malloc(getMaxSizeArray(getPharmacy(repository)) * sizeof(TElem)));
	setRedoListArray(repository, (ArrayPharmacy*)malloc(maxSize * sizeof(ArrayPharmacy)));
	setMedicList(getRedoListarray(repository), (TElem*)malloc(sizeof(TElem)));
	setArraySize(getRedoListarray(repository), 2);
	setUndoListArray(repository, (ArrayPharmacy*)malloc(maxSize * sizeof(ArrayPharmacy)));
	setMedicList(getUndoListArray(repository), (TElem*)malloc(sizeof(TElem)));
	setArraySize(getUndoListArray(repository), 2);
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
	//Destroy pharmacy and free all dynamic arrays
	if (getPharmacy(repository) == NULL) return;
	for (int i = 0; i < getMemoryPosLeak(repository); i++) {
		free(getMedicineName(getValueListOfLeaks(getMemoryLeak(repository), i)));
	}
	for (int i = 0; i < getMemoryPosArr(repository); i++) {
		free(getMedicList(getValueListOfArrays(repository, i)));
		if(getValueListOfArrays(repository,i) != NULL) free(getValueListOfArrays(repository,i));
	}
	free(getListOfLeaks(getMemoryLeak(repository)));
	free(getListOfArrays(repository));
	free(getMemoryLeak(repository));
	free(getHistoryArr(repository));
	if (repository == NULL) return;
	free(repository);
}

void addMedicamentToPharmacy(Repository* repository, TElem medicAdd) {
	//ADd in repo medicament, add in undo
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
	//Add only quantity, not object
	addNewUndo(repository);
	setMedicineQuantity(&getMedicList(getPharmacy(repository))[index], getMedicineQuantity(&getMedicList(getPharmacy(repository))[index]) + addQuantity);
}

void deleteMedicamentFromPharmacy(Repository* repository, int indexToDelete) {
	//Delete medicament from pharmacy and add undo
	addNewUndo(repository);
	memmove(&getMedicList(getPharmacy(repository))[indexToDelete], &getMedicList(getPharmacy(repository))[indexToDelete + 1], (getSizeArray(getPharmacy(repository)) - indexToDelete - 1) * sizeof(Medicine));
	if (getMedicList(getPharmacy(repository)) == NULL) {
		setMedicList(getPharmacy(repository), (TElem*)calloc(1, sizeof(TElem)));
	}
	setArraySize(getPharmacy(repository), getSizeArray(getPharmacy(repository)) - 1);
}

void updateMedicamentfromPharmacy(Repository* repository, int indexName,Medicine* medic, char* newName, int newConcentration, int newQuantity, int newPrice) {
	//Update value for medicament
	addNewUndo(repository);
	TElem newElem = createMedicineRepo(repository, newName, newConcentration, newQuantity, newPrice);
	getMedicList(getPharmacy(repository))[indexName] = newElem;
}

TElem createMedicineRepo(Repository* repository, char* name, int concentration, int quantity, int price) {
	//Create new medicine repo
	TElem newMedic = createMedicine(name, concentration, quantity,price);
	if (getMemoryPosLeak(repository) + 1 >= getLeakMaxSize(repository)) {
		resizeMemory(repository);
		if (getMedicList(getPharmacy(repository)) == NULL) {
			exit(EXIT_FAILURE);
		}
	}
	int verifyOK = 1;
	for (int i = 0; i < getMemoryPosArr(repository); i++) {
		if (getValueListOfArrays(repository,i) == &newMedic) verifyOK = 0;
	}
	if (verifyOK) {
		setElemLeaksOfLeaks(getListOfLeaks(getMemoryLeak(repository)), getMemoryPosLeak(repository), newMedic);
		setMemoryPosLeak(repository, getMemoryPosLeak(repository) + 1);
	}
	return newMedic;
}
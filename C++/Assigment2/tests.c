#include <stdio.h>
#include <assert.h>
#include "repository.h"

void testCreatePharmacy() {
    Repository* repo = createPharmacy(10);
    assert(repo != NULL);
    destroyPharmacy(repo);
}

void testDestroyPharmacy() {
    Repository* repo = createPharmacy(10);
    destroyPharmacy(repo);
}

void testAddMedicamentToPharmacy() {
    Repository* repo = createPharmacy(10);
    TElem newMedic = createMedicineRepo(repo, "Paracetamol", 500, 20, 5);
    addMedicamentToPharmacy(repo, newMedic);
    assert(getSizeArray(getPharmacy(repo)) == 1);
    destroyPharmacy(repo);
}

void testAddQuantity() {
    Repository* repo = createPharmacy(10);
    TElem newMedic = createMedicineRepo(repo, "Ibuprofen", 200, 15, 8);
    addMedicamentToPharmacy(repo, newMedic);
    addQuantity(repo, 0, 5);
    assert(getElemByID(getPharmacy(repo), 0)->quantity == 20);
    destroyPharmacy(repo);
}

void testDeleteMedicamentFromPharmacy() {
    Repository* repo = createPharmacy(10);
    TElem newMedic = createMedicineRepo(repo, "Aspirin", 100, 30, 3);
    addMedicamentToPharmacy(repo, newMedic);
    deleteMedicamentFromPharmacy(repo, 0);
    assert(getSizeArray(getPharmacy(repo)) == 0);
    destroyPharmacy(repo);
}

void testUpdateMedicamentfromPharmacy() {
    Repository* repo = createPharmacy(10);
    TElem newMedic = createMedicineRepo(repo, "Nurofen", 400, 10, 7);
    addMedicamentToPharmacy(repo, newMedic);
    updateMedicamentfromPharmacy(repo, 0, NULL, "NewName", 500, 20, 8);
    TElem* updatedMedic = getElemByID(getPharmacy(repo), 0);
    assert(updatedMedic->concentration == 500 && updatedMedic->quantity == 20 && updatedMedic->price == 8);
    destroyPharmacy(repo);
}

void testAddRedo() {
    Repository* repo = createPharmacy(10);
    addRedo(repo);
    assert(getPosRedo(repo) == 2);
    destroyPharmacy(repo);
}

void testAddUndo() {
    Repository* repo = createPharmacy(10);
    addUndo(repo);
    assert(getPosUndo(repo) == 2);
    destroyPharmacy(repo);
}

void testUndoOperation() {
    Repository* repo = createPharmacy(10);
    TElem medicAdd = createMedicineRepo(repo, "Ibuprofen", 200, 15, 8);
    addUndo(repo);
    undoOperation(repo);
    assert(getSizeArray(getPharmacy(repo)) == 0);
    destroyPharmacy(repo);
}

void testRedoOperation() {
    Repository* repo = createPharmacy(10);
    TElem medicAdd = createMedicineRepo(repo, "Aspirin", 100, 30, 3);
    addUndo(repo);
    undoOperation(repo);
    redoOperation(repo);
    assert(getSizeArray(getPharmacy(repo)) == 0);
    destroyPharmacy(repo);
}

void testCloneArray() {
    Repository* repo = createPharmacy(10);
    TElem newMedic = createMedicineRepo(repo, "Paracetamol", 500, 20, 5);
    addMedicamentToPharmacy(repo, newMedic);
    ArrayPharmacy* clonedArray = cloneArray(repo, getPharmacy(repo));
    assert(getSizeArray(clonedArray) == getSizeArray(getPharmacy(repo)));
    destroyPharmacy(repo);
}

void testCreateMedicine() {
    Medicine m = createMedicine("Paracetamol", 500, 20, 5);
    assert(strcmp(getMedicineName(&m), "Paracetamol") == 0);
    assert(getMedicineConcentration(&m) == 500);
    assert(getMedicineQuantity(&m) == 20);
    assert(getMedicinePrice(&m) == 5);
    free(m.name);
}

void testUpdateMedicine() {
    Medicine m = createMedicine("Paracetamol", 500, 20, 5);
    updateMedicine(&m, "NewName", 1000, 30, 10);
    assert(strcmp(getMedicineName(&m), "NewName") == 0);
    assert(getMedicineConcentration(&m) == 1000);
    assert(getMedicineQuantity(&m) == 30);
    assert(getMedicinePrice(&m) == 10);
    free(m.name);
}

void testSetMedicinePrice() {
    Medicine m = createMedicine("Paracetamol", 500, 20, 5);
    setMedicinePrice(&m, 8);
    assert(getMedicinePrice(&m) == 8);
    free(m.name);
}

void testSetMedicineQuantity() {
    Medicine m = createMedicine("Paracetamol", 500, 20, 5);
    setMedicineQuantity(&m, 25);
    assert(getMedicineQuantity(&m) == 25);
    free(m.name);
}

void testSetMedicineConcentration() {
    Medicine m = createMedicine("Paracetamol", 500, 20, 5);
    setMedicineConcentration(&m, 1000);
    assert(getMedicineConcentration(&m) == 1000);
    free(m.name);
}

void runAllTests() {
    testCreatePharmacy();
    testDestroyPharmacy();
    testAddMedicamentToPharmacy();
    testAddQuantity();
    testDeleteMedicamentFromPharmacy();
    testUpdateMedicamentfromPharmacy();
    testAddRedo();
    testAddUndo();
    testUndoOperation();
    testRedoOperation();
    testCloneArray();
    testCreateMedicine();
    testUpdateMedicine();
    testSetMedicinePrice();
    testSetMedicineQuantity();
    testSetMedicineConcentration();
}

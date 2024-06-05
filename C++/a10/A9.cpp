#include "A9.h"

A9::A9(Service& service,QWidget *parent)
    : QWidget(parent), managerService{service}
{   
    this->setWindows();
    this->setButtonsWindows();
    this->connectAll();
    ui.stackedWidget->setCurrentIndex(0);
}

A9::~A9()
{}

void A9::setRepository(int id)
{
    VirtualRepo* reposit = NULL;
    switch (id)
    {
    case 1: //MEMORY
        reposit = new Repository();
        break;
    case 2: //HTML
        reposit = new HTMLRepository("output.txt","output.html");
        break;
    case 3: // CSV
        reposit = new CSVRepository("output.txt","output.csv");
        break;
    case 4: // TEXT FILE
        reposit = new TextRepository("output.txt");
        break;
    default:
        break;
    }
    this->verify = Verifications{ reposit };
    this->managerService.setRepo(reposit);
    this->ui.stackedWidget->setCurrentIndex(1);
}

void A9::setUser(int id)
{
    switch (id)
    {
    case 1:
        populateList();
        this->ui.stackedWidget->setCurrentIndex(2);
        break;
    case 2:
        populateUser();
        this->ui.stackedWidget->setCurrentIndex(3);
        break;
    default:
        break;
    }
    
}

void A9::connectAll()
{
    QObject::connect(ui.MEMORY, &QPushButton::clicked, this, [=]() { this->setRepository(1); });
    QObject::connect(ui.HTML, &QPushButton::clicked, this, [=]() { this->setRepository(2); });
    QObject::connect(ui.CSV, &QPushButton::clicked, this, [=]() { this->setRepository(3); });
    QObject::connect(ui.textFile, &QPushButton::clicked, this, [=]() { this->setRepository(4); });
    QObject::connect(login.ADMIN, &QPushButton::clicked, this, [=]() { this->setUser(1); });
    QObject::connect(login.USER, &QPushButton::clicked, this, [=]() { this->setUser(2); });
    QObject::connect(login.exit, &QPushButton::clicked, this, [=]() { this->close(); });

    QObject::connect(admin.logout, &QPushButton::clicked, this, [=]() { this->ui.stackedWidget->setCurrentIndex(1); });
    QObject::connect(user.logout, &QPushButton::clicked, this, [=]() { this->ui.stackedWidget->setCurrentIndex(1); });
    
    //ADD DOG
    QObject::connect(admin.addDog, &QPushButton::clicked, this, [=]() { addDogButton->show(); });
    QObject::connect(addDog.subbButon, &QPushButton::clicked, this, [=]() { 
        if (addDog.age->text().isEmpty() || addDog.name->text().isEmpty() || addDog.breed->text().isEmpty() || addDog.photograph->text().isEmpty()) {
            QMessageBox::warning(addDogButton, "Warning", "All fields must be filled!");
            return;
        }
        if (addDog.age->text().toInt() == 0) {
            QMessageBox::warning(addDogButton, "Warning", "Age must be an integer!");
            return;
        }
        if (addDog.age->text().toInt() < 0) {
            QMessageBox::warning(addDogButton, "Warning", "Age must be a positive integer!");
            return;
        }
        if (this->verify.verifyDogExist(addDog.name->text().toStdString(), addDog.breed->text().toStdString()))
        {

            QMessageBox::warning(addDogButton, "Warning", "Dog Already Exist!");
            return;
        }
        this->managerService.addDog(addDog.name->text().toStdString(), addDog.breed->text().toStdString(), addDog.age->text().toStdString(), addDog.photograph->text().toStdString());
        this->populateList();
        addDog.name->clear();
        addDog.breed->clear();
        addDog.age->clear();
        addDog.photograph->clear();
        addDogButton->close();
        });
    //DELETE DOG
    QObject::connect(admin.deleteDog, &QPushButton::clicked, this, [=]() { deleteDogButton->show(); });
    QObject::connect(deleteDog.subbButon, &QPushButton::clicked, this, [=]() {
        if (deleteDog.name->text().isEmpty() || deleteDog.breed->text().isEmpty()) {
            QMessageBox::warning(deleteDogButton, "Warning", "All fields must be filled!");
            return;
        }
        if (!this->verify.verifyDogExist(deleteDog.name->text().toStdString(), deleteDog.breed->text().toStdString()) && !this->verify.verifyAddoptedDogExist(deleteDog.name->text().toStdString(), deleteDog.breed->text().toStdString())) {
            QMessageBox::warning(deleteDogButton, "Warning", "Dog Doesn't Exist!");
            return;
        }
        if (!this->verify.verifyAddopt(deleteDog.name->text().toStdString(), deleteDog.breed->text().toStdString())) {

            QMessageBox::warning(deleteDogButton, "Warning", "Dog is not addopted!");
            return;
        }
        this->managerService.deleteDogAddopted(deleteDog.name->text().toStdString(), deleteDog.breed->text().toStdString());
        this->populateList();
        deleteDog.name->clear();
        deleteDog.breed->clear();
        deleteDogButton->close();
        });
    //UPDATE DOG
    QObject::connect(admin.UpdateDog, &QPushButton::clicked, this, [=]() { updateDogButton->show(); });
    QObject::connect(updateDog.subbButon, &QPushButton::clicked, this, [=]() {
        if (updateDog.age->text().isEmpty() || updateDog.name->text().isEmpty() || updateDog.breed->text().isEmpty() || updateDog.photograph->text().isEmpty() || updateDog.actualbreed->text().isEmpty() || updateDog.actualname->text().isEmpty()) {
            QMessageBox::warning(updateDogButton, "Warning", "All fields must be filled!");
            return;
        }
        if (updateDog.age->text().toInt() == 0) {
            QMessageBox::warning(updateDogButton, "Warning", "Age must be an integer!");
            return;
        }
        if (updateDog.age->text().toInt() < 0) {
            QMessageBox::warning(updateDogButton, "Warning", "Age must be a positive integer!");
            return;
        }
        if (!this->verify.verifyDogExist(updateDog.actualname->text().toStdString(), updateDog.actualbreed->text().toStdString()))
        {
            QMessageBox::warning(updateDogButton, "Warning", "Dog Doesn't Exist!");
            return;
        }
        if (this->verify.verifyDogExist(updateDog.name->text().toStdString(), updateDog.breed->text().toStdString()))
        {
            QMessageBox::warning(this, "Warning", "Dog Already Exist!");
            return;
        }
        this->managerService.updateDog(updateDog.actualname->text().toStdString(), updateDog.actualbreed->text().toStdString(), updateDog.name->text().toStdString(), updateDog.breed->text().toStdString(), updateDog.age->text().toStdString(), updateDog.photograph->text().toStdString());
        this->populateList();
        updateDog.actualbreed->clear();
        updateDog.actualname->clear();
        updateDog.name->clear();
        updateDog.breed->clear();
        updateDog.age->clear();
        updateDog.photograph->clear();
        updateDogButton->close();
        });
    //SEARCH DOG CUSTOM
    QObject::connect(user.searchDog, &QPushButton::clicked, this, [=]() { 
        searchDogCustom.age->clear();
        searchDogCustom.breed->clear();
        customModel->clear();
        searchDogCustomButton->show(); });
    QObject::connect(searchDogCustom.subbButon, &QPushButton::clicked, this, [=]() {
        if (!this->verify.validAge(searchDogCustom.age->text().toStdString())) {
            QMessageBox::warning(searchDogCustomButton, "Warning", "Invalid Age!");
            return;
        }
        if (searchDogCustom.age->text().isEmpty()) {
            QMessageBox::warning(searchDogCustomButton, "Warning", "Age empty! Provide a value.!");
            return;
        }
        this->populateCustom(searchDogCustom.age->text().toStdString(), searchDogCustom.breed->text().toStdString());
        });
    //ADDOPT DOG
    QObject::connect(user.addoptDog, &QPushButton::clicked, this, [=]() {
        counterDog = 0;
        dogAddoptButton->show();
        dogOneByOne(counterDog); });
    QObject::connect(dogAddopt.NEXT, &QPushButton::clicked, this, [=]() {
        counterDog++;
        dogOneByOne(counterDog); });
    QObject::connect(dogAddopt.back, &QPushButton::clicked, this, [=]() {
        counterDog++;
        dogOneByOne(counterDog); });
    QObject::connect(dogAddopt.addopt, &QPushButton::clicked, this, [=]() {
        this->managerService.addoptDog(counterDog);
        populateUser();
        counterDog = 0;
        dogAddoptButton->close(); });
    QObject::connect(dogAddopt.exit, &QPushButton::clicked, this, [=]() {
        dogAddoptButton->close(); });
    //UNDO REDO
    QObject::connect(shortcutUndo, &QShortcut::activated, this, [=]() {
        try
        {
            this->undoCommand();
            this->populateList();
        }
        catch (const std::exception& e)
        {
            QMessageBox::warning(this, "Undo Information", e.what());
        }

        });
    QObject::connect(shortcutRedo, &QShortcut::activated, this, [=]() {
        try
        {
            this->redoCommand();
            this->populateList();
        }
        catch (const std::exception& e)
        {
            QMessageBox::warning(this, "Redo Information", e.what());
        } });
    QObject::connect(admin.undoButton, &QPushButton::clicked, this, [=]() {
        try
        {
            this->undoCommand();
            this->populateList();
        }
        catch (const std::exception& e)
        {
            QMessageBox::warning(this, "Undo Information", e.what());
        }

        });
    QObject::connect(admin.redoButton, &QPushButton::clicked, this, [=]() {
        try
        {
            this->redoCommand();
            this->populateList();
        }
        catch (const std::exception& e)
        {
            QMessageBox::warning(this, "Redo Information", e.what());
        }
         });
}

void A9::populateList()
{
    dogModel->clear();
    dogModel->setHorizontalHeaderLabels({ "Name", "Breed", "Age", "Photograph", "Adopted" });
    int cnt = 0;
    if (this->managerService.getSizeForDogsNotAddopted() > 0) {
        for (Dog as : this->managerService.getAllElementsNotAddopted()) {
            QList<QStandardItem*> rowItems;
            rowItems.append(new QStandardItem(QString::fromStdString(as.getName())));
            rowItems.append(new QStandardItem(QString::fromStdString(as.getBreed())));
            rowItems.append(new QStandardItem(QString::number(as.getAge())));
            rowItems.append(new QStandardItem(QString::fromStdString(as.getPhotograph())));
            rowItems.append(new QStandardItem(as.getAdopted() ? "Yes" : "No"));
            dogModel->appendRow(rowItems);
            cnt++;
        }
    }
    if (this->managerService.getSizeForDogsAddopted() > 0) {
        for (Dog as : this->managerService.getAllElementsAddopted()) {
            QList<QStandardItem*> rowItems;
            rowItems.append(new QStandardItem(QString::fromStdString(as.getName())));
            rowItems.append(new QStandardItem(QString::fromStdString(as.getBreed())));
            rowItems.append(new QStandardItem(QString::number(as.getAge())));
            rowItems.append(new QStandardItem(QString::fromStdString(as.getPhotograph())));
            rowItems.append(new QStandardItem(as.getAdopted() ? "Yes" : "No"));
            dogModel->appendRow(rowItems);
            cnt++;
        }
    }
    this->admin.tableView->resizeColumnsToContents();

    this->admin.tableView->resizeRowsToContents();

    QHeaderView* header = this->admin.tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    this->ui.stackedWidget->repaint();
}

void A9::populateUser()
{
    userModel->clear();
    userModel->setHorizontalHeaderLabels({ "Name", "Breed", "Age", "Photograph", "Adopted" });
    int cnt = 0;
    if (this->managerService.getSizeForDogsNotAddopted() > 0) {
        for (Dog as : this->managerService.getAllElementsNotAddopted()) {
            QList<QStandardItem*> rowItems;
            rowItems.append(new QStandardItem(QString::fromStdString(as.getName())));
            rowItems.append(new QStandardItem(QString::fromStdString(as.getBreed())));
            rowItems.append(new QStandardItem(QString::number(as.getAge())));
            rowItems.append(new QStandardItem(QString::fromStdString(as.getPhotograph())));
            rowItems.append(new QStandardItem(as.getAdopted() ? "Yes" : "No"));
            userModel->appendRow(rowItems);
            cnt++;
        }
    }
    this->user.tableView->resizeColumnsToContents();

    this->user.tableView->resizeRowsToContents();

    QHeaderView* header = this->user.tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    this->ui.stackedWidget->repaint();
}

void A9::populateCustom(string age, string breed)
{
    customModel->clear();
    customModel->setHorizontalHeaderLabels({ "Name", "Breed", "Age", "Photograph", "Adopted" });
    vector<Dog> dogsFound;
    this->managerService.searchDogByBreedAge(dogsFound, breed, age);
    int cnt = 0;
    for (Dog as : dogsFound) {
        QList<QStandardItem*> rowItems;
        rowItems.append(new QStandardItem(QString::fromStdString(as.getName())));
        rowItems.append(new QStandardItem(QString::fromStdString(as.getBreed())));
        rowItems.append(new QStandardItem(QString::number(as.getAge())));
        rowItems.append(new QStandardItem(QString::fromStdString(as.getPhotograph())));
        rowItems.append(new QStandardItem(as.getAdopted() ? "Yes" : "No"));
        customModel->appendRow(rowItems);
        cnt++;
    }
    this->searchDogCustom.tableView->resizeColumnsToContents();

    this->searchDogCustom.tableView->resizeRowsToContents();

    QHeaderView* header = this->searchDogCustom.tableView->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    this->ui.stackedWidget->repaint();
}

void A9::dogOneByOne(int cnt)
{
    if (cnt < 0) {
        cnt = this->managerService.getSizeForDogsNotAddopted() - 1;
        counterDog = 0;
    }
    if (this->managerService.getSizeForDogsNotAddopted() <= cnt) {
        counterDog = 0;
        cnt = 0;
    }
    if (this->managerService.getSizeForDogsNotAddopted() == 0) {
        QMessageBox::warning(this, "Warning", "0 dogs found!");
        dogAddoptButton->close();
        return;
    }
    Dog dog = this->managerService.getAllElementsNotAddopted()[cnt];
    dogAddopt.nameDog->setText(QString::fromStdString(dog.getName()));
    dogAddopt.breedDog->setText(QString::fromStdString(dog.getBreed()));
    dogAddopt.ageDog->setText(QString::fromStdString(to_string(dog.getAge())));
    dogAddopt.photographDog->setText(QString::fromStdString(dog.getPhotograph()));

}

void A9::setWindows()
{
    ui.setupUi(this);
    login.setupUi(widgLogin);
    admin.setupUi(widgAdmin);
    user.setupUi(widgUser);
    admin.tableView->setModel(dogModel);
    user.tableView->setModel(userModel);


    ui.stackedWidget->insertWidget(1, widgLogin);
    ui.stackedWidget->insertWidget(2, widgAdmin);
    ui.stackedWidget->insertWidget(3, widgUser);
}

void A9::setButtonsWindows()
{
    addDog.setupUi(addDogButton);
    deleteDog.setupUi(deleteDogButton);
    updateDog.setupUi(updateDogButton);
    searchDogCustom.setupUi(searchDogCustomButton);
    dogAddopt.setupUi(dogAddoptButton);

    customModel->setHorizontalHeaderLabels({ "Name", "Breed", "Age", "Photograph", "Adopted" });
    searchDogCustom.tableView->setModel(customModel);
}

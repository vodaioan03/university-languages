#include "A9.h"

A9::A9(const Service& service,QWidget *parent)
    : QWidget(parent)
{   
    this->managerService = service;
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
    QObject::connect(user.openList, &QPushButton::clicked, this, [=]() { this->openFile(); });
    //ADD DOG
    QObject::connect(admin.addDog, &QPushButton::clicked, this, [=]() { addDogButton->show(); });
    QObject::connect(addDog.subbButon, &QPushButton::clicked, this, [=]() { 
        if (addDog.age->text().isEmpty() || addDog.name->text().isEmpty() || addDog.breed->text().isEmpty() || addDog.photograph->text().isEmpty()) {
            QMessageBox::warning(this, "Warning", "All fields must be filled!");
            return;
        }
        if (addDog.age->text().toInt() == 0) {
            QMessageBox::warning(this, "Warning", "Age must be an integer!");
            return;
        }
        if (addDog.age->text().toInt() < 0) {
            QMessageBox::warning(this, "Warning", "Age must be a positive integer!");
            return;
        }
        if (this->verify.verifyDogExist(addDog.name->text().toStdString(), addDog.breed->text().toStdString()))
        {

            QMessageBox::warning(this, "Warning", "Dog Already Exist!");
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
            QMessageBox::warning(this, "Warning", "All fields must be filled!");
            return;
        }
        if (!this->verify.verifyDogExist(deleteDog.name->text().toStdString(), deleteDog.breed->text().toStdString()) && !this->verify.verifyAddoptedDogExist(deleteDog.name->text().toStdString(), deleteDog.breed->text().toStdString())) {
            QMessageBox::warning(this, "Warning", "Dog Doesn't Exist!");
            return;
        }
        if (!this->verify.verifyAddopt(deleteDog.name->text().toStdString(), deleteDog.breed->text().toStdString())) {

            QMessageBox::warning(this, "Warning", "Dog is not addopted!");
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
            QMessageBox::warning(this, "Warning", "All fields must be filled!");
            return;
        }
        if (updateDog.age->text().toInt() == 0) {
            QMessageBox::warning(this, "Warning", "Age must be an integer!");
            return;
        }
        if (updateDog.age->text().toInt() < 0) {
            QMessageBox::warning(this, "Warning", "Age must be a positive integer!");
            return;
        }
        if (!this->verify.verifyDogExist(updateDog.actualname->text().toStdString(), updateDog.actualbreed->text().toStdString()))
        {
            QMessageBox::warning(this, "Warning", "Dog Doesn't Exist!");
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
            QMessageBox::warning(this, "Warning", "Invalid Age!");
            return;
        }
        if (searchDogCustom.age->text().isEmpty()) {
            QMessageBox::warning(this, "Warning", "Age empty! Provide a value.!");
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
    //PIE
    QObject::connect(admin.statistics, &QPushButton::clicked, this, &A9::drawBreedStatistics);
}

void A9::populateList()
{
    dogModel->clear();

    int cnt = 0;
    if (this->managerService.getSizeForDogsNotAddopted() > 0) {
        for (Dog as : this->managerService.getAllElementsNotAddopted()) {
            string s = as.dogToString();
            s.pop_back();
            s.pop_back();
            QStandardItem* item = new QStandardItem(QString::fromStdString("[" + to_string(cnt) + "]  " + s));
            dogModel->appendRow(item);
            cnt++;
        }
    }
    if (this->managerService.getSizeForDogsAddopted() > 0) {
        for (Dog as : this->managerService.getAllElementsAddopted()) {
            string s = as.dogToString();
            s.pop_back();
            s.pop_back();
            QStandardItem* item = new QStandardItem(QString::fromStdString("[" + to_string(cnt) + "]  " + s));
            dogModel->appendRow(item);
            cnt++;
        }
    }
    this->ui.stackedWidget->repaint();
}

void A9::populateUser()
{
    userModel->clear();
    int cnt = 0;
    if (this->managerService.getSizeForDogsNotAddopted() > 0) {
        for (Dog as : this->managerService.getAllElementsNotAddopted()) {
            string s = as.dogToString();
            s.pop_back();
            s.pop_back();
            QStandardItem* item = new QStandardItem(QString::fromStdString("[" + to_string(cnt) + "]  " + s));
            userModel->appendRow(item);
            cnt++;
        }

    }
}

void A9::populateCustom(string age, string breed)
{
    customModel->clear();
    vector<Dog> dogsFound;
    this->managerService.searchDogByBreedAge(dogsFound, breed, age);
    int cnt = 0;
    for (Dog as : dogsFound) {
        string s = as.dogToString();
        s.pop_back();
        s.pop_back();
        QStandardItem* item = new QStandardItem(QString::fromStdString("[" + to_string(cnt) + "]  " + s));
        customModel->appendRow(item);
        cnt++;
    }
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
    admin.listDogs->setModel(dogModel);
    user.listDogs->setModel(userModel);


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
    plots.setupUi(plotsButton);

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    view->setAlignment(Qt::AlignCenter | Qt::AlignCenter); // Adjust alignment as needed
    plotsButton->setLayout(new QVBoxLayout);
    plotsButton->layout()->addWidget(view);

    searchDogCustom.listView->setModel(customModel);
}


map<string, int> A9::gatherBreedStatistics() {
    map<string, int> breedCount;
    for (Dog& dog : this->managerService.getAllElementsAddopted()) {
        breedCount[dog.getBreed()]++;
    }
    for (Dog& dog : this->managerService.getAllElementsNotAddopted()) {
        breedCount[dog.getBreed()]++;
    }
    return breedCount;
}

void A9::openFile()
{
    this->managerService.getAllElementsAddoptedPrint();
}

void A9::drawBreedStatistics()
{
    map<string, int> breeds = this->gatherBreedStatistics();

    int barWidth = 22;
    int spaceBetweenBars = 80;
    int numRows = breeds.size();
    int maxCount = 0;
    QFontMetrics fm(QFont("Verdana", 8));
    for (const auto& breed : breeds) {
        maxCount = max(maxCount, breed.second);
    }
    int maxLabelWidth = 0;
    for (const auto& breed : breeds) {
        int labelWidth = fm.horizontalAdvance(QString::fromStdString(breed.first));
        maxLabelWidth = max(maxLabelWidth, labelWidth);
    }
    int maxDigitWidth = fm.horizontalAdvance('9');
    int chartWidth = (barWidth + spaceBetweenBars) * numRows + maxLabelWidth + maxDigitWidth + 50;
    int chartHeight = maxCount * 44 + 50;

    QWidget* chartWidget = new QWidget();
    chartWidget->setFixedSize(chartWidth, chartHeight);

    QPixmap pixmap(chartWidth, chartHeight);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont font("Verdana", 8);
    painter.setFont(font);

    int labelHeight = fm.height();
    int x = maxLabelWidth + 25;
    for (const auto& breed : breeds) {
        int barCenter = x + barWidth / 2;
        int textX = barCenter - fm.horizontalAdvance(QString::fromStdString(breed.first)) / 2;
        int textY = chartHeight - 6;
        painter.drawText(textX, textY, QString::fromStdString(breed.first));
        x += barWidth + spaceBetweenBars;
    }

    QFont countFont("Verdana", 8);
    painter.setFont(countFont);

    QPen blackPen(Qt::black);
    painter.setPen(blackPen);

    x = maxLabelWidth - 10;
    for (int i = 0; i <= maxCount + 4; i++) {
        painter.drawText(x, chartHeight - 20 - i * 44, QString::number(i));

        QPen dottedPen(Qt::black);
        dottedPen.setStyle(Qt::DotLine);
        painter.setPen(dottedPen);
        painter.drawLine(x + maxDigitWidth + 2, chartHeight - 20 - i * 44, chartWidth - 10, chartHeight - 20 - i * 44);
    }

    x = maxLabelWidth + 35;
    for (const auto& breed : breeds) {
        QColor randomColor = QColor::fromRgb(
            QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256),
            QRandomGenerator::global()->bounded(256)
        );

        QPen pen(randomColor);
        pen.setWidth(barWidth);
        painter.setPen(pen);

        float barHeight = breed.second * 44 - 12;
        painter.drawLine(x, chartHeight - 30, x, chartHeight - 20 - barHeight);

        x += barWidth + spaceBetweenBars;
    }

    painter.end();

    QLabel* label = new QLabel(chartWidget);
    label->setPixmap(pixmap);
    label->resize(chartWidth, chartHeight);

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidget(chartWidget);
    scrollArea->setWidgetResizable(false);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QWidget* window = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(window);
    mainLayout->addWidget(scrollArea);
    window->setLayout(mainLayout);
    window->resize(700, 500);
    window->setMinimumSize(700, 500);
    window->setMaximumSize(700, 500);

    window->show();
}


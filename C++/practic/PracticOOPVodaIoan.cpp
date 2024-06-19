#include "PracticOOPVodaIoan.h"

PracticOOPVodaIoan::PracticOOPVodaIoan(Department* dep, Service& serv, QWidget* parent)
    : QWidget(parent), department{ dep }, service{ serv }
{
    ui.setupUi(this);
    addvolWind.setupUi(addVolWidget);
    this->service.registerObserver(this);
    this->setWindowTitle(QString::fromStdString(dep->getName()));
    ui.putDescription->setText(QString::fromStdString(dep->getDescription()));

    connect();
    populateList();
}


void PracticOOPVodaIoan::update()
{
    populateList();
}

void PracticOOPVodaIoan::connect()
{
    QObject::connect(ui.addVolunteer, &QPushButton::clicked, this, &PracticOOPVodaIoan::openAddVolunteer);
    QObject::connect(ui.asssignButton, &QPushButton::clicked, this, &PracticOOPVodaIoan::assignVolunteer);
    QObject::connect(addvolWind.addButton, &QPushButton::clicked, this, [=]() {
        string name, email, listinterests;
        name = addvolWind.getName->text().toStdString();
        email = addvolWind.getEmail->text().toStdString();
        listinterests = addvolWind.getInterests->text().toStdString();
        try
        {
            if (name.empty()) throw exception("Name is empty.");
            if (email.empty()) throw exception("Email is empty.");

            this->addVolunteer(name,email,listinterests);
        }
        catch (const std::exception& e)
        {
            QMessageBox::critical(addVolWidget, "ERROR", e.what());
        }
        });
    QObject::connect(ui.topThreeBox, &QCheckBox::clicked, this, &PracticOOPVodaIoan::topVolunteersUnassigned);
}

void PracticOOPVodaIoan::populateList()
{
    ui.assignedList->clear();
    ui.unassignedList->clear();
    for (Volunteer* vol : this->service.getVolunteerByDepartment(department)) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(vol->toString()));
        QVariant v(vol->getEmail().c_str());
        item->setData(Qt::UserRole, v);
        if (vol->getDepartment() == "unassigned" && !topVol) {
            ui.unassignedList->addItem(item);
        }
        else if (vol->getDepartment() != "unassigned") {
            ui.assignedList->addItem(item);
        }
    }
    if (topVol) {
        populateTop();
    }
}

void PracticOOPVodaIoan::openAddVolunteer()
{
    addVolWidget->show();
}

void PracticOOPVodaIoan::topVolunteersUnassigned(bool acc)
{
    topVol = acc;
    if (topVol) {
        populateTop();
    }
    else {
        populateList();
    }
    
}

void PracticOOPVodaIoan::populateTop()
{
    vector<Volunteer*> vols = this->service.getSuitableVolunteers(department);
    for (Volunteer* vol : vols) {
        if (vol == NULL) {
            QMessageBox::warning(this, "Warning", "3 volunteers doesn't exist.");
            return;
        }
    }
    ui.unassignedList->clear();
    for (Volunteer* vol : vols) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(vol->toString()));
        QVariant v(vol->getEmail().c_str());
        item->setData(Qt::UserRole, v);
        ui.unassignedList->addItem(item);
    }
}

void PracticOOPVodaIoan::addVolunteer(string name, string mail, string listinterests)
{
    addvolWind.getEmail->setText(" ");
    addvolWind.getName->setText(" ");
    addvolWind.getInterests->setText(" ");
    service.addVolunteer(name, mail, listinterests);
    addVolWidget->hide();
    service.notify();
}

void PracticOOPVodaIoan::assignVolunteer()
{
    QListWidgetItem* item = ui.unassignedList->currentItem();
    if (item == NULL) return;
    string email = item->data(Qt::UserRole).toString().toStdString();
    service.assignVolunteer(email, department);
    service.notify();
}

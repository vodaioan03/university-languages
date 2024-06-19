#pragma once

#include <QtWidgets/QWidget>
#include "ui_PracticOOPVodaIoan.h"
#include "ui_addVolunteer.h"
#include <QMessageBox>
#include "Observer.h"
#include "Service.h"
class PracticOOPVodaIoan : public QWidget,public Observer
{
    Q_OBJECT

public:
    PracticOOPVodaIoan(Department* dep , Service& serv,QWidget *parent = nullptr);
    ~PracticOOPVodaIoan() {
        delete addVolWidget;
    }
    void update();
    void connect();
    void populateList();
    void openAddVolunteer();
    void topVolunteersUnassigned(bool acc);
    void populateTop();
    void addVolunteer(string name, string mail, string listinterests);
    void assignVolunteer();
private:
    Ui::PracticOOPVodaIoanClass ui;
    Ui::addVolunteerWindow addvolWind;
    Service& service;
    Department* department;
    bool topVol = false;
    QWidget* addVolWidget = new QWidget();
};

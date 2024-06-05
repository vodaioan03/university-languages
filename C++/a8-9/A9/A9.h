#pragma once

#include <QtWidgets/QWidget>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QGraphicsTextItem>
#include <QRandomGenerator>
#include "Service.h"
#include "Verifications.h"
#include "ui_plots.h"
#include "ui_A9.h"
#include "ui_login.h"
#include "ui_admin.h"
#include "ui_user.h"
#include "ui_addDog.h"
#include "ui_deleteDog.h"
#include "ui_updateDog.h"
#include "ui_searchDogbreed.h"
#include "ui_addoptDo.h"

class A9 : public QWidget
{
    Q_OBJECT

public:
    A9(const Service& service, QWidget* parent = nullptr);
    ~A9();

    Ui::A9Class ui;

    void setRepository(int id);
    void setUser(int id);
    void connectAll();


    void populateList();
    void populateUser();
    void populateCustom(string age, string breed);
    void dogOneByOne(int cnt);
    void drawBreedStatistics();
    map<string, int> gatherBreedStatistics();
    void openFile();

    void setWindows();
    void setButtonsWindows();

private:
    Service managerService;
    Verifications verify;
    //WINDOWS
    
    Ui::Login login;
    Ui::Admin admin;
    Ui::user user;
   
    int counterDog = 0;
    
    QWidget* widgLogin = new QWidget();
    QWidget* widgAdmin = new QWidget();
    QWidget* widgUser = new QWidget();

    //BUTTONS
    Ui::addDog addDog;
    Ui::deleteDog deleteDog;
    Ui::updateDog updateDog;
    Ui::searcDogByAgeBreed searchDogCustom;
    Ui::addoptDOG dogAddopt;
    Ui::Plots plots;
    QWidget* addDogButton = new QWidget();
    QWidget* deleteDogButton = new QWidget();
    QWidget* updateDogButton = new QWidget();
    QWidget* searchDogCustomButton = new QWidget();
    QWidget* dogAddoptButton = new QWidget();
    QWidget* plotsButton = new QWidget();
    QGraphicsScene* scene;
    QGraphicsView* view;

    //MODELS
    QStandardItemModel* dogModel = new QStandardItemModel(this);
    QStandardItemModel* userModel = new QStandardItemModel(this);
    QStandardItemModel* customModel = new QStandardItemModel(this);

};

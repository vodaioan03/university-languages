#pragma once

#include <QtWidgets/QWidget>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QShortcut>
#include "Service.h"
#include "Verifications.h"
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
    A9(Service& service, QWidget* parent = nullptr);
    ~A9();

    Ui::A9Class ui;

    void setRepository(int id);
    void setUser(int id);
    void connectAll();


    void populateList();
    void populateUser();
    void populateCustom(string age, string breed);
    void dogOneByOne(int cnt);
    void undoCommand() { this->managerService.undoCommand(); }
    void redoCommand() { this->managerService.redoCommand(); }

    void setWindows();
    void setButtonsWindows();

private:
    Service& managerService;
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
    QWidget* addDogButton = new QWidget();
    QWidget* deleteDogButton = new QWidget();
    QWidget* updateDogButton = new QWidget();
    QWidget* searchDogCustomButton = new QWidget();
    QWidget* dogAddoptButton = new QWidget();

    //MODELS
    QStandardItemModel* dogModel = new QStandardItemModel(this);
    QStandardItemModel* userModel = new QStandardItemModel(this);
    QStandardItemModel* customModel = new QStandardItemModel(this);

    //SHORTCUTS
    QShortcut* shortcutUndo = new QShortcut(QKeySequence("Ctrl+Z"), widgAdmin);
    QShortcut* shortcutRedo = new QShortcut(QKeySequence("Ctrl+Y"), widgAdmin);
};

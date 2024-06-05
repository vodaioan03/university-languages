#pragma once
#include "Service.h"
#include <QMessageBox>
#include <QtWidgets/QWidget>
#include "ui_GUI.h"

class GUI : public QWidget
{
    Q_OBJECT

public:
    GUI(Service& serv,QWidget *parent = nullptr);
    ~GUI();

    void populateList();
    void lineChanged();
    void getSimilarity();

private:
    Ui::GUIClass ui;

    Service& service;
};

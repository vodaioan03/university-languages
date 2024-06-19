#pragma once
#include <QtWidgets/QWidget>
#include "ui_PracticOOPVodaIoan.h"
#include "ui_listWindow.h"
#include <QMessageBox>
#include "Observer.h"
#include "Service.h"
class listWindow:public QWidget, public Observer
{
	Q_OBJECT
private:
	Ui::Statistics stats;
	Service& service;
	void update();
	void populateList();
public:
	listWindow(Service& serv, QWidget* parent = nullptr);
};


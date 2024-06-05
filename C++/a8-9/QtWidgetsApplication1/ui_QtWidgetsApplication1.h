#ifndef QTWIDGETSAPPLICATION1WKTKWX_H
#define QTWIDGETSAPPLICATION1WKTKWX_H

#include <iostream>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QDebug>
#include <string>
using namespace std;

QT_BEGIN_NAMESPACE

class Ui_QtWidgetsApplication1Class
{
public:
    QWidget* centralWidget;
    QPushButton* adminButton;
    QPushButton* userButton;
    QToolBar* toolBar;
    QStatusBar* statusBar;
    QObject* logic;
    string txt = "Admin";
    QMainWindow* main;

    void setMain(QMainWindow* sett) {
        this->main = sett;
    }

    void setupUi()
    {
        QMainWindow* QtWidgetsApplication1Class = this->main;
        if (QtWidgetsApplication1Class->objectName().isEmpty())
            QtWidgetsApplication1Class->setObjectName("QtWidgetsApplication1Class");
        QtWidgetsApplication1Class->resize(600, 400);
        centralWidget = new QWidget(QtWidgetsApplication1Class);
        centralWidget->setObjectName("centralWidget");
        adminButton = new QPushButton(centralWidget);
        adminButton->setObjectName("adminButton");
        adminButton->setGeometry(QRect(10, 330, 80, 24));
        userButton = new QPushButton(centralWidget);
        userButton->setObjectName("userButton");
        userButton->setGeometry(QRect(510, 330, 80, 24));
        QtWidgetsApplication1Class->setCentralWidget(centralWidget);
        userButton->raise();
        adminButton->raise();
        toolBar = new QToolBar(QtWidgetsApplication1Class);
        toolBar->setObjectName("toolBar");
        QtWidgetsApplication1Class->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(QtWidgetsApplication1Class);
        statusBar->setObjectName("statusBar");
        QtWidgetsApplication1Class->setStatusBar(statusBar);

        QObject::connect(adminButton, SIGNAL(released()), QtWidgetsApplication1Class, SLOT(onAdminButtonClicked()));
        QObject::connect(userButton, SIGNAL(released()), QtWidgetsApplication1Class, SLOT(onUserButtonClicked()));

        retranslateUi(QtWidgetsApplication1Class);

        QMetaObject::connectSlotsByName(QtWidgetsApplication1Class);
    }

    void retranslateUi(QMainWindow* QtWidgetsApplication1Class)
    {
        QtWidgetsApplication1Class->setWindowTitle(QCoreApplication::translate("QtWidgetsApplication1Class", "QtWidgetsApplication1", nullptr));
        adminButton->setText(QCoreApplication::translate("QtWidgetsApplication1Class", txt.c_str(), nullptr));
        userButton->setText(QCoreApplication::translate("QtWidgetsApplication1Class", "User", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("QtWidgetsApplication1Class", "toolBar", nullptr));
    }
};

namespace Ui {
    class QtWidgetsApplication1Class : public Ui_QtWidgetsApplication1Class {};
}

QT_END_NAMESPACE

#endif // QTWIDGETSAPPLICATION1WKTKWX_H

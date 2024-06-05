#include "QtWidgetsApplication1.h"

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QWidget(parent){}

QtWidgetsApplication1::QtWidgetsApplication1(const Service& service, QWidget* parent)
{
    this->managerService = service;
    this->verify.setRepo(managerService.getRepo());
}

QtWidgetsApplication1::~QtWidgetsApplication1()
{}
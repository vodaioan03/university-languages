#include "listWindow.h"

void listWindow::update()
{
	populateList();
}

void listWindow::populateList()
{
	service.setNrVolunteers();
	stats.listWidget->clear();
	int countt = 0;
	for (Department* dep : service.getDepartmentsSorted()) {
		countt += dep->getNrVolunteers();
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(dep->getName() + " have " + to_string(dep->getNrVolunteers()) + " volunteers."));
		stats.listWidget->addItem(item);
	}
	QListWidgetItem* item = new QListWidgetItem(QString::fromStdString("unassigned have " + to_string(this->service.getVolunteers().size() - countt) + " volunteers."));
	stats.listWidget->addItem(item);
}

listWindow::listWindow(Service& serv, QWidget* parent)
	: QWidget(parent), service{ serv }
{
	stats.setupUi(this);
	service.registerObserver(this);
	populateList();
	this->setWindowTitle("Statistics");
}

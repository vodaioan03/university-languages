#include "GUI.h"

GUI::GUI(Service& serv,QWidget *parent)
    : service{ serv },QWidget(parent)
{
    ui.setupUi(this);
    service.populateRepo();
    this->populateList();
    QObject::connect(ui.lineEdit, &QLineEdit::textChanged, this, &GUI::lineChanged);
    QObject::connect(ui.listWidget, &QListWidget::itemSelectionChanged, this, &GUI::getSimilarity);
}

GUI::~GUI()
{}

void GUI::populateList()
{
    this->ui.listWidget->clear();
    vector<Task*> tasks = this->service.getItemsSorted();
    int cnt = 0;
    for (Task* task : tasks) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString("["+to_string(cnt)+"] " + task->toString() ));
        QVariant var{ task->getName().c_str() }; // ADD THE NAME FOR IDENTIFY THE ITEM
        item->setData(3, var);
        cnt++;
        this->ui.listWidget->addItem(item);
    }

}

void GUI::lineChanged()
{
    this->ui.listWidget->setCurrentItem(NULL); // without this i have a little bug when i delete the input and i write something very fast
    string line = this->ui.lineEdit->text().toStdString();
    vector<Task*> tasks = this->service.getItemsByWord(line);
    this->ui.listWidget->clear();
    int cnt = 0;
    for (Task* task : tasks) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString("[" + to_string(cnt) + "] " + task->toString()));
        QVariant var{ task->getName().c_str()}; // ADD THE NAME FOR IDENTIFY THE ITEM
        item->setData(3, var);
        cnt++;
        this->ui.listWidget->addItem(item);
    }
}

void GUI::getSimilarity()
{
    string line = this->ui.lineEdit->text().toStdString();
    if (line.size() == 0) { // VERIFY IF THE LINE EDIT WHERE DO YOU WRITE THE CODE IS EMPTY
        this->ui.showResult->setText(QString::fromStdString(""));
        return;
    }
    QListWidgetItem* item = this->ui.listWidget->currentItem();
    if (item == NULL) {
        this->ui.showResult->setText(QString::fromStdString(""));
        return;
    }
    double val = this->service.getSimilarityByName(line,item->data(3).toString().toStdString());
    this->ui.showResult->setText(QString::fromStdString(to_string(val)));
   
}

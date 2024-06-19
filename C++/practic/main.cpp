#include "PracticOOPVodaIoan.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "listWindow.h"
// o ora 27
int main(int argc, char *argv[])
{
    Service serv{};
    QApplication a(argc, argv);
    vector<PracticOOPVodaIoan*> windows;
    for (Department* dep : serv.getDepartments()) {
        PracticOOPVodaIoan* w = new PracticOOPVodaIoan(dep,serv);
        w->show();
        windows.push_back(w);
    }
    listWindow* wind = new listWindow{ serv };
    wind->show();
    return a.exec();
}

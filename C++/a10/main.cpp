#include "A9.h"
#include <QtWidgets/QApplication>
#include "Service.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Service serv{};
    A9 w{ serv };
    w.show();
    return a.exec();
}

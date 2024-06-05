#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Service serv{};
    GUI w{ serv };
    w.show();
    return a.exec();
}

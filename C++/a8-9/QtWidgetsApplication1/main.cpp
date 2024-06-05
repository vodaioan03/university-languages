#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include "managerUI.h"
#include "crtdbg.h"
#include "TextRepository.h"
#include "CSVRepository.h"
#include "HTMLRepository.h"

using namespace std;

int main(int argc, char *argv[])
{
    VirtualRepo* repository = new CSVRepository("output.txt","output.csv");
    Service service{ repository };
    QApplication a(argc, argv);
    QtWidgetsApplication1 w{ service };
    w.startProgram();
    return a.exec();
    
}

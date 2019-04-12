#include "Globals.hpp"
#include "windows/MainWindow.hpp"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName(qglobals::ORGANISATION_NAME);
    QApplication::setApplicationName(qglobals::APPLICATION_NAME);
    MainWindow w;
    w.show();
    return a.exec();
}

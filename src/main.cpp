#include "windows/MainWindow.hpp"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("mapret");
    QApplication::setApplicationName("modelviewer");
    MainWindow w;
    w.show();
    return a.exec();
}

#include <QApplication>
#include <QDebug>

#include "tarjeem.h"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qApp->addLibraryPath( qApp->applicationDirPath() + "/plugins");

    Tarjeem *tarjeem = new Tarjeem;
    tarjeem->showMaximized();

    app.exec();
}

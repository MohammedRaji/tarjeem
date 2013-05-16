#include <QApplication>
#include <QDebug>

#include "tarjeem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qApp->addLibraryPath( qApp->applicationDirPath() + "/plugins");

    Tarjeem *tarjeem = new Tarjeem;
    tarjeem->showMaximized();

    app.exec();
}

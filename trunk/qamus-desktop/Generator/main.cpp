#include <QApplication>
#include <QDebug>

#include "qamus.h"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qApp->addLibraryPath( qApp->applicationDirPath() + "/plugins");

    Qamus *m_qamus = new Qamus();
    m_qamus->setGeometry(300,300,800,400);
    m_qamus->showMaximized();

    app.exec();

    return 0;
}

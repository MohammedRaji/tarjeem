#include <QHash>
#include <QLabel>
#include <QtGui>
#include <QApplication>
#include <QString>
#include <QHBoxLayout>
#include <QWidget>
#include <QDesktopWidget>
#include <QDir>
#include <QFile>
#include <QDebug>

#include <iostream>

#include "qamus.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Qamus w;
    w.setGeometry(0,0,500,400);
    w.move(QApplication::desktop()->screen()->rect().center() - w.rect().center());
    w.show();

//    QFile file("DatabaseMunawir.txt");
//    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//        return 1;

//    QFile fileout("DatabaseMunawir.xml");
//    if (!fileout.open(QIODevice::WriteOnly | QIODevice::Text))
//        return 1;

//    int count = 0;

//    QTextStream in(&file);
//    QString line = in.readLine();
//    while (!line.isNull())
//    {
//        count++;

//        QStringList wew = line.split("\t");

//        if (wew.size() == 2)
//        {

//            //" ، "

//            QStringList dash = wew.at(1).split(" - ");

//            if (dash.size() > 0)
//            {
//                for (int i=0; i<dash.size(); i++)
//                {
//                    fileout.write(QString("<data ar=\"%1\" id=\"%2\" />\n").arg(dash.at(i)).arg(wew.at(0)).toUtf8());
//                }
//            }
//            else
//            {
//                QStringList comma = wew.at(1).split(QString("،").toUtf8());

//                if (comma.size() > 0)
//                {
//                    for (int j=0; j<comma.size(); j++)
//                    {
//                        fileout.write(QString("<data ar=\"%1\" id=\"%2\" />\n").arg(comma.at(j)).arg(wew.at(0)).toUtf8());
//                    }
//                }
//                else
//                {
//                    fileout.write(QString("<data ar=\"%1\" id=\"%2\" />\n").arg(wew.at(1)).arg(wew.at(0)).toUtf8());
//                }
//            }
//        }

//        line = in.readLine();
//    }

//    qDebug() << "finished";

    return a.exec();
}

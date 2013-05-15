#include <QMessageBox>
#include <QMenuBar>
#include <QFileDialog>
#include <QTreeWidget>
#include <QHBoxLayout>
#include <QTextBlock>
#include <QHeaderView>
#include <QToolBar>
#include <QDebug>

#include "tarjeem.h"

Tarjeem::Tarjeem()
{
    createMenu();
    activateMenu(false);

    listMain.append("BkId");
    listMain.append("Bk");
    listMain.append("Betaka");
    listMain.append("Inf");
    listMain.append("Auth");
    listMain.append("AuthInf");
    listMain.append("TafseerNam");
    listMain.append("IslamShort");
    listMain.append("oNum");
    listMain.append("oVer");
    listMain.append("seal");
    listMain.append("oAuth");
    listMain.append("bVer");
    listMain.append("oAuth");
    listMain.append("bVer");
    listMain.append("Pdf");
    listMain.append("oAuthVer");
    listMain.append("verName");
    listMain.append("cat");
    listMain.append("Lng");
    listMain.append("HigriD");
    listMain.append("AD");
    listMain.append("aSeal");
    listMain.append("bLnk");
    listMain.append("PdfCs");
    listMain.append("ShrtCs");

    //    QString listMain = "BkId, Bk, Betaka, Inf, Auth, AuthInf, TafseerNam, IslamShort, oNum, oVer, seal, oAuth, bVer, oAuth, bVer, Pdf, oAuthVer, verName, cat, Lng, HigriD, AD, aSeal, bLnk, PdfCs, ShrtCs";

    listContent.append("tit");
    listContent.append("lvl");
    listContent.append("sub");
    listContent.append("id");

    this->setWindowTitle("Tarjeem Desktop v0.1");
}

Tarjeem::~Tarjeem()
{
}

void Tarjeem::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(QIcon("://open.png"), "Open Book...", this, SLOT(openBook()), Qt::ControlModifier + Qt::Key_O);
    fileMenu->addAction(QIcon("://open_url.png"), "Open Book from URL...", this, SLOT(openBook()), Qt::ControlModifier + Qt::Key_U);
    fileMenu->addSeparator();
    fileMenu->addAction("Exit", this, SLOT(close()), Qt::ControlModifier + Qt::Key_Q);

    fileMenu->actions().at(1)->setDisabled(true);

    translateMenu = menuBar()->addMenu(tr("&Translate"));
    translateMenu->addAction(QIcon("://run.png"), "Run", this, SLOT(openBook()), Qt::ControlModifier + Qt::Key_R);
    translateMenu->addAction(QIcon("://pause.png"), "Pause", this, SLOT(openBook()), NULL);
    translateMenu->addAction(QIcon("://restart.png"), "Restart", this, SLOT(openBook()), NULL);
    translateMenu->addSeparator();
    translateMenu->addAction(QIcon("://stop.png"), "Stop", this, SLOT(openBook()), Qt::ControlModifier + Qt::Key_X);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction("About", this, SLOT(openHelp()));

    language = new QComboBox(this);
    language->addItem(QIcon("://country_id.png"), "Indonesia", 0);
    language->addItem(QIcon("://country_jp.png"), "Japan", 0);
    language->addItem(QIcon("://country_us.png"), "United States", 0);

    QToolBar *fileToolbar = addToolBar("File");
    fileToolbar->addAction(fileMenu->actions().at(0));
    fileToolbar->addAction(fileMenu->actions().at(1));

    QToolBar *translateToolbar = addToolBar("Translate");
    translateToolbar->addWidget(language);
    translateToolbar->addAction(translateMenu->actions().at(0));
    translateToolbar->addAction(translateMenu->actions().at(1));
    translateToolbar->addAction(translateMenu->actions().at(2));
    translateToolbar->addAction(translateMenu->actions().at(4));
}

void Tarjeem::activateMenu(bool opt)
{
    translateMenu->actions().at(0)->setEnabled(opt);
    translateMenu->actions().at(1)->setEnabled(opt);
    translateMenu->actions().at(2)->setEnabled(opt);
    translateMenu->actions().at(4)->setEnabled(opt);
}

void Tarjeem::openBook()
{
    currentBookFile = QFileDialog::getOpenFileName(this, tr("Buka File Buku"), "", tr("Shamela Book (*.bok)"));

    this->setWindowTitle(QString("Tarjeem Desktop v0.1.0 - (%1)").arg(currentBookFile));

    QFileInfo pathInfo(currentBookFile);
    if(currentBookFile.isEmpty())
    {
        return;
    }
    else
    {
        onOpenBook();
    }
}

void Tarjeem::openHelp()
{
    QMessageBox msgBox;
    msgBox.setText("Tarjeem v0.1.0 \nShamela's Book Translation Software");
    msgBox.setInformativeText("Copyright 2013 Tarjeem.com \n For more information contact us (yansyaf@gmail.com)");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

void Tarjeem::onOpenBook()
{
    tab = new QTabWidget(this);
    mainInfo = new QTableWidget(this);
    content = new QWidget(this);
    tableOfContent = new QTreeWidget(this);
    contentText = new QTextEdit(this);

    QFont font("Arial", 16, QFont::Normal, false);
    contentText->setFont(font);
    contentText->setStyleSheet("QLabel { color : black; }");

    connect(tableOfContent, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(onItemClicked(QTreeWidgetItem*)) );

    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->addWidget(tableOfContent,30);
    contentLayout->addWidget(contentText,70);
    content->setLayout(contentLayout);

    mainInfo->setColumnCount(2);
    mainInfo->horizontalHeader()->setStretchLastSection(true);
    mainInfo->resizeRowsToContents();
    tableOfContent->setColumnCount(4);
    tableOfContent->setColumnWidth(0,300); //icon
    tableOfContent->setColumnWidth(1,20); //icon
    tableOfContent->setColumnWidth(2,20); //icon
    tableOfContent->setColumnWidth(3,20); //icon
    tableOfContent->setHeaderLabels(listContent);
    tab->addTab(mainInfo, "Main");
    tab->addTab(content, "Content");

    this->setCentralWidget(tab);

    QString filePath = QString("DRIVER={Driver do Microsoft Access (*.mdb)};FIL={CONN_NAME};DBQ=%1").arg(currentBookFile);

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "odbc");
    db.setDatabaseName(filePath);

    if (!db.open()) {
        QMessageBox::warning(this,"Error","SQlite: Failed to create database");
    }
    else {
        QSqlQuery query(db); // get data from .mdb file

        //Main table
        for (int i=0; i<listMain.count(); i++)
        {
            query.exec(QString("SELECT %1 FROM Main;").arg(listMain.at(i)));
            query.next();
            mainInfo->setRowCount(i+1);
            mainInfo->setItem(i,0,new QTableWidgetItem(QString("%1").arg(listMain.at(i))));
            mainInfo->setItem(i,1,new QTableWidgetItem(QString("%1").arg(query.value(0).toString())));
        }

        //Content table
        tableOfContent->insertTopLevelItem(0, new QTreeWidgetItem(QStringList(QString("Daftar Isi")), 0));

        QString list = "tit, lvl, sub, id";
        query.exec(QString("SELECT %1 FROM t%2;").arg(list).arg(mainInfo->item(0,1)->text()));

        while( query.next() )
        {
            QStringList content;
            for (int i=0; i<4; i++)
            {
                content.append(QString("%1").arg(query.value(i).toString()));
            }
            tableOfContent->itemAt(0,0)->addChild( new QTreeWidgetItem(content));
        }
        tableOfContent->expandAll();
    }
    db.close();
}

void Tarjeem::onItemClicked(QTreeWidgetItem* item)
{
    QString filePath = "DRIVER={Driver do Microsoft Access (*.mdb)};FIL={CONN_NAME};DBQ=";
    filePath.append(currentBookFile);

    // create database
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "odbc");
    db.setDatabaseName(filePath);

    if (!db.open()) {
        QMessageBox::warning(this,"Error","SQlite: Failed to create database");
    }
    else {
        QSqlQuery query(db); // get data from .mdb file

        //content
        query.exec(QString("SELECT nass FROM b%1;").arg(mainInfo->item(0,1)->text()));

        contentText->clear();
        query.next();
        contentText->append(QString(query.value(0).toString()));
        contentText->append("==========================================");
        query.next();
        contentText->append(QString(query.value(0).toString()));
        contentText->append("==========================================");
        query.next();
        contentText->append(QString(query.value(0).toString()));
        contentText->append("==========================================");
        query.next();
        contentText->append(QString(query.value(0).toString()));
        contentText->append("==========================================");
        query.next();
        contentText->append(QString(query.value(0).toString()));
        contentText->append("==========================================");
        query.next();
        contentText->append(QString(query.value(0).toString()));
        contentText->append("==========================================");
        query.next();
        contentText->append(QString(query.value(0).toString()));
        contentText->append("==========================================");
        query.next();
        contentText->append(QString(query.value(0).toString()));
        contentText->append("==========================================");
//        query.next();
//        contentText->append(QString(query.value(0).toString()));
//        contentText->append("==========================================");

//        while(query.next())
//        {
//            contentText->append(QString(query.value(0).toString()));
//        }
    }
}

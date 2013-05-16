#include <QMessageBox>
#include <QMenuBar>
#include <QFileDialog>
#include <QTreeWidget>
#include <QHBoxLayout>
#include <QTextBlock>
#include <QHeaderView>
#include <QToolBar>
#include <QTextCodec>
#include <QStatusBar>
#include <QDebug>

#include "tarjeem.h"

Tarjeem::Tarjeem()
{
    createMenu();
    createStatusBar();
    activateMenu(false);

    listMain << "BkId" << "Bk" << "Betaka" << "Inf" << "Auth" << "AuthInf" << "TafseerNam" << "IslamShort"
             << "oNum" << "oVer" << "seal" << "oAuth" << "bVer" << "oAuth" << "bVer" << "Pdf" << "oAuthVer"
             << "verName" << "cat" << "Lng" << "HigriD" << "AD" << "aSeal" << "bLnk" << "PdfCs" << "ShrtCs";

    listContent << "tit" << "lvl" << "sub" << "id";

    readingStatus = IS_NOT_READING;

    this->setWindowTitle("Tarjeem Desktop");
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
    language->addItem(QIcon("://country_id.png"), "Bahasa Indonesia", 0);
    language->addItem(QIcon("://country_jp.png"), "Japanese", 0);
    language->addItem(QIcon("://country_us.png"), "English (US)", 0);

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

void Tarjeem::createStatusBar()
{
    status = new QLabel("Ready", this);
    status->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    progressBar = new QProgressBar(this);
    progressBar->setInvertedAppearance(true);
    progressBar->setVisible(true);
    //    progressBar->hide();

    statusBar()->addWidget(status, 0);
    statusBar()->addWidget(progressBar, 1);
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

    this->setWindowTitle(QString("Tarjeem Desktop - (%1)").arg(currentBookFile));

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
    msgBox.setText("Tarjeem Desktop \nShamela's Book Translation Software");
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

    QStringList bookInfoHeader;
    bookInfoHeader << "Code" << "Items" << "Original Text" << "Translation Text";
    mainInfo->setColumnCount(4);
    mainInfo->setHorizontalHeaderLabels(bookInfoHeader);
    mainInfo->horizontalHeader()->setStretchLastSection(true);
    mainInfo->resizeRowsToContents();
    mainInfo->setColumnWidth(0,100);
    mainInfo->setColumnWidth(1,100);
    mainInfo->setColumnWidth(2,500);
    mainInfo->setColumnWidth(3,500);
    tableOfContent->setColumnCount(4);
    tableOfContent->setColumnWidth(0,300); //icon
    tableOfContent->setColumnWidth(1,20); //icon
    tableOfContent->setColumnWidth(2,20); //icon
    tableOfContent->setColumnWidth(3,20); //icon
    tableOfContent->setHeaderLabels(listContent);
    tab->addTab(mainInfo, "Book Information");
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

        //Book Info table
        QString bookInfoItems = "BkId, Bk, Betaka, Inf, Auth, AuthInf, TafseerNam, IslamShort, oNum, oVer, seal, oAuth, bVer, oAuth, bVer, Pdf, oAuthVer, verName, cat, Lng, HigriD, AD, aSeal, bLnk, PdfCs, ShrtCs";
        query.exec(QString("SELECT %1 FROM Main;").arg(bookInfoItems));
        query.next();
        for (int i=0; i<listMain.count(); i++)
        {
            mainInfo->setRowCount(i+1);
            mainInfo->setItem(i,0,new QTableWidgetItem(QString("%1").arg(listMain.at(i))));
            mainInfo->setItem(i,1,new QTableWidgetItem(QString("%1").arg(listMain.at(i))));
            mainInfo->setItem(i,2,new QTableWidgetItem(QString("%1").arg(query.value(i).toString())));
            mainInfo->setItem(i,3,new QTableWidgetItem(QString("...")));
        }

        //Content table
        tableOfContent->insertTopLevelItem(0, new QTreeWidgetItem(QStringList(QString("Table of Contents")), 0));

        QString list = "tit, lvl, sub, id";

        //level 1
        int level1idx = 1;
        query.exec(QString("SELECT %1 FROM t%2 WHERE lvl = 1;").arg(list).arg(mainInfo->item(0,2)->text()));
        while( query.next() )
        {
            QStringList content;

            QString number = QString("%1").arg(level1idx);
            content.append(QString("%1 - %2").arg(number).arg(query.value(0).toString()));  //tit
            content.append(QString("%1").arg(query.value(1).toString()));  //lvl
            content.append(QString("%1").arg(query.value(2).toString()));  //sub
            content.append(QString("%1").arg(query.value(3).toString()));  //id

            tableOfContent->itemAt(0,0)->addChild( new QTreeWidgetItem(content));
            level1idx++;
        }

        //level 2
        int currentIdx = 0;
        int level2idx = 1;
        query.exec(QString("SELECT %1 FROM t%2 WHERE lvl = 2;").arg(list).arg(mainInfo->item(0,2)->text()));
        while( query.next() )
        {
            int i;
            for (i=0; i<tableOfContent->itemAt(0,0)->childCount(); i++)
            {
                //check if id is bellow
                if (tableOfContent->itemAt(0,0)->child(i)->data(3,0).toInt() > query.value(3).toInt())
                    break;
            }

            if (currentIdx != i-1)
            {
                level2idx = 1;
                currentIdx = i-1;
            }

            QStringList content;
            QString number = QString("%1.%2").arg(i).arg(level2idx);
            content.append(QString("%1 - %2").arg(number).arg(query.value(0).toString()));  //tit
            content.append(QString("%1").arg(query.value(1).toString()));  //lvl
            content.append(QString("%1").arg(query.value(2).toString()));  //sub
            content.append(QString("%1").arg(query.value(3).toString()));  //id

            tableOfContent->itemAt(0,0)->child(i-1)->addChild( new QTreeWidgetItem(content));
            level2idx++;
        }

        tableOfContent->expandAll();
    }
    db.close();
}

void Tarjeem::onItemClicked(QTreeWidgetItem* item)
{
    disconnect(tableOfContent, SIGNAL(itemClicked(QTreeWidgetItem*,int)), 0, 0);

    QString filePath = "DRIVER={Driver do Microsoft Access (*.mdb)};FIL={CONN_NAME};DBQ=";
    filePath.append(currentBookFile);

    // create database
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "content_odbc");
    db.setDatabaseName(filePath);

    if (!db.open()) {
        QMessageBox::warning(this,"Error","SQlite: Failed to create database");
    }
    else {
        QSqlQuery query(db); // get data from .mdb file

        //get size
        query.exec(QString("SELECT nass FROM b%1;").arg(mainInfo->item(0,2)->text()));
        int size = 0;
        while(query.next())
        {
            size++;
        }
        progressBar->setRange(0,size-1); //set impossible value

        //content
        query.exec(QString("SELECT nass FROM b%1;").arg(mainInfo->item(0,2)->text()));

        int i=0;
        while(query.next())
        {
            contentText->append(query.value(0).toString());
            progressBar->setValue(i);
            i++;
        }
        progressBar->setValue(0);
    }
    db.close();

    connect(tableOfContent, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(onItemClicked(QTreeWidgetItem*)) );
}

//QTreeWidgetItem* diggIn(QTreeWidgetItem* current, int level)
//{
//    switch(level)
//    {
//        case 1: return current->child(0);
//    }
//}

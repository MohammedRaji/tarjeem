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
#include <QPalette>
#include <QNetworkAccessManager>
#include <QRegExp>
#include <QTimer>
#include <QDebug>

#include "tarjeem.h"

Tarjeem::Tarjeem()
{
    createMenu();
    createStatusBar();
    activateMenu(false);

    listMain << "Book Number"
             << "Title"
             << "Subtitle"
             << "Author"
             << "Author's' Biography"
             << "Category"
             << "Author"
             << "Year";

    listContent << "tit"
                << "lvl"
                << "sub"
                << "id";

    progressValue = 0;

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

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction("Show Document Navigation", this, SLOT(showNavigation(bool)), Qt::ControlModifier + Qt::Key_L);
    viewMenu->addAction("Show Translation Page", this, SLOT(showTranslation(bool)), Qt::ControlModifier + Qt::Key_T);
    viewMenu->addAction("Show Search Panel", this, SLOT(showTranslation(bool)), Qt::ControlModifier + Qt::Key_F);
    viewMenu->actions().at(0)->setCheckable(true);
    viewMenu->actions().at(0)->setChecked(true);
    viewMenu->actions().at(1)->setCheckable(true);
    viewMenu->actions().at(1)->setChecked(false);

    translateMenu = menuBar()->addMenu(tr("&Translate"));
    translateMenu->addAction(QIcon("://run.png"), "Run", this, SLOT(onTranslate()), Qt::ControlModifier + Qt::Key_T);
    //    translateMenu->addAction(QIcon("://pause.png"), "Pause", this, SLOT(openBook()), NULL);
    //    translateMenu->addAction(QIcon("://restart.png"), "Restart", this, SLOT(openBook()), NULL);
    //    translateMenu->addSeparator();
    //    translateMenu->addAction(QIcon("://stop.png"), "Stop", this, SLOT(openBook()), Qt::ControlModifier + Qt::Key_X);
    //    translateMenu->addAction(QIcon("://run.png"), "Run");
    translateMenu->addAction(QIcon("://pause.png"), "Pause");
    translateMenu->addAction(QIcon("://restart.png"), "Restart");
    translateMenu->addAction(QIcon("://stop.png"), "Stop");
    translateMenu->addSeparator();
    translateMenu->addAction("Dictionary");
    translateMenu->addSeparator();
    translateMenu->addAction("Settings", this, SLOT(openSettings()));

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
    status->setFixedWidth(100);
    progressBar = new QProgressBar(this);
    progressBar->setInvertedAppearance(true);
    progressBar->setVisible(true);

    statusBar()->addWidget(status, 0);
    statusBar()->addWidget(progressBar, 1);
}

void Tarjeem::activateMenu(bool opt)
{
    viewMenu->actions().at(0)->setEnabled(opt);
    viewMenu->actions().at(1)->setEnabled(opt);
    translateMenu->actions().at(0)->setEnabled(opt);
    translateMenu->actions().at(1)->setEnabled(opt);
    translateMenu->actions().at(2)->setEnabled(opt);
    translateMenu->actions().at(4)->setEnabled(opt);
}

void Tarjeem::openBook()
{
    currentBookFile = QFileDialog::getOpenFileName(this, tr("Buka File Buku"), "", tr("Shamela Book (*.bok)"));

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
    m_content = new Content(this);
    dock = new QDockWidget("Books", NULL);

    connect(m_content->tableOfContent, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(onItemClicked(QTreeWidgetItem*)) );
    connect(m_content->showNavigation, SIGNAL(clicked(bool)), this, SLOT(showNavigation(bool)) );
    connect(m_content->showTranslation, SIGNAL(clicked(bool)), this, SLOT(showTranslation(bool)) );

    dock->setWidget(m_content);
    this->setCentralWidget(dock);

    QString filePath = QString("DRIVER={Driver do Microsoft Access (*.mdb)};FIL={CONN_NAME};DBQ=%1").arg(currentBookFile);

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC", "odbc");
    db.setDatabaseName(filePath);

    if (!db.open()) {
        QMessageBox::warning(this,"Error","SQlite: Failed to create database");
    }
    else {
        QSqlQuery query(db); // get data from .mdb file

        //-----------------------------------
        // Cover
        //-----------------------------------
        QString bookInfoItems = "BkId, Bk, Betaka, Auth, AuthInf, cat, Lng, HigriD";
        query.exec(QString("SELECT %1 FROM Main;").arg(bookInfoItems));
        query.next();

        bookId = query.value(0).toInt();
        this->setWindowTitle(QString("Tarjeem Desktop - %1").arg(query.value(1).toString()));

        QString title = QString("<font color=\"blue\">%1</font>").arg(query.value(1).toString());

        QString coverText;
        //coverText.append(QString("<p>%1 •</p>").arg(query.value(0).toString()));
        //        coverText.append(QString("<p>%1 •</p>").arg(query.value(5).toString()));
        //        coverText.append(QString("<p>%1 •</p>").arg(query.value(1).toString()));
        //        coverText.append(QString("<p>%1 •</p>").arg(query.value(2).toString()));
        //        coverText.append(QString("<p>%1 •</p>").arg(query.value(3).toString()));
        //        coverText.append(QString("<p>%1 •</p>").arg(query.value(4).toString()));
        //        coverText.append(QString("<p>%1 •</p>").arg(query.value(6).toString()));
        //        coverText.append(QString("<p>%1 •</p>").arg(query.value(7).toString()));

        coverText.append(QString("<p>%1</p>").arg(query.value(5).toString()));
        coverText.append(QString("<p>%1</p>").arg(query.value(1).toString()));
        coverText.append(QString("<p>%1</p>").arg(query.value(2).toString()));
        coverText.append(QString("<p>%1</p>").arg(query.value(3).toString()));
        coverText.append(QString("<p>%1</p>").arg(query.value(4).toString()));
        coverText.append(QString("<p>%1</p>").arg(query.value(6).toString()));
        coverText.append(QString("<p>%1</p>").arg(query.value(7).toString()));

        int row = 0;
        m_content->contentTable->setRowCount(row+1);
        m_content->contentTable->setItem(row, 0, new QTableWidgetItem(coverText));
        m_content->contentTable->setItem(row, 1, new QTableWidgetItem("0"));
        row++;

        //-----------------------------------
        // Table of Content
        //-----------------------------------
        QString list = "tit, lvl, sub, id";
        QString contentList = "nass, id";

        query.exec(QString("SELECT %1 FROM t%2;").arg(list).arg(bookId));
        int range = 0;
        while(query.next())
        {
            range++;
        }
        query.exec(QString("SELECT %1 FROM b%2;").arg(contentList).arg(bookId));
        while(query.next())
        {
            range++;
        }
        progressBar->setRange(0,range-1);

        m_content->tableOfContent->insertTopLevelItem(0, new QTreeWidgetItem(QStringList(QString("Table of Contents")), 0));
        m_content->tableOfContent->itemAt(0,0)->setForeground( 0,QBrush(Qt::white) );

        int levelDepth[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int currentLevel = 1;

        query.exec(QString("SELECT %1 FROM t%2;").arg(list).arg(bookId));

        QTreeWidgetItem *current = m_content->tableOfContent->itemAt(0,0);
        progressBar->setValue(0);
        int progress = 0;
        while (query.next())
        {
            if ( query.value(1).toInt() > currentLevel )
            {
                current = levelIn(current, (query.value(1).toInt() - currentLevel) );
            }
            else if ( query.value(1).toInt() < currentLevel )
            {
                current = levelUp(current, (currentLevel - query.value(1).toInt()) );
            }

            currentLevel = query.value(1).toInt();
            levelDepth[currentLevel-1] = levelDepth[currentLevel-1]++;

            QString number;
            for (int i=0; i<10; i++)
            {
                if (i<currentLevel)
                {
                    number.append(QString::number(levelDepth[i]));
                    number.append(".");
                }
                else
                {
                    levelDepth[i] = 0;
                }
            }

            QStringList content;
            content.append(QString("%1 - %2").arg(number).arg(query.value(0).toString()));  //numbering and title
            content.append(QString("%1").arg(query.value(0).toString()));  //title
            content.append(QString("%1").arg(number));                     //numbering
            content.append(QString("%1").arg(query.value(1).toString()));  //level
            content.append(QString("%1").arg(query.value(3).toString()));  //id
            content.append(QString("%1").arg(query.value(3).toString()));  //content

            current->addChild(new QTreeWidgetItem(content));
            current->child( current->childCount()-1 )->setIcon(0,QIcon("://book-icon.png"));
            current->child( current->childCount()-1 )->setForeground( 0,QBrush(Qt::white) );

            progressBar->setValue(progress);
            progress++;
        }
        m_content->tableOfContent->expandAll();

        QString text;
        text.append(m_content->contentTable->item(0,0)->text());

        m_content->contentText->clear();
        m_content->contentText->setHtml(text);

        QStringList coverContent;
        coverContent.append("Cover");
        coverContent.append("0");
        coverContent.append("0");
        coverContent.append("0");
        coverContent.append("0");
        m_content->tableOfContent->insertTopLevelItem(0, new QTreeWidgetItem(coverContent, 0));
        m_content->tableOfContent->itemAt(0,1)->setForeground( 0,QBrush(Qt::white) );

        query.exec(QString("SELECT %1 FROM b%2;").arg(contentList).arg(bookId));

        while(query.next())
        {
            m_content->contentTable->setRowCount(row+1);
            m_content->contentTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
            m_content->contentTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
            row++;

            progressBar->setValue(progress);
            progress++;
        }
        progressBar->setValue(0);

    }
    db.close();

    activateMenu(true);
}

void Tarjeem::onItemClicked(QTreeWidgetItem* item)
{
    QString text;
    if      (item->text(3).toInt() == 1)
        text.append(QString("<div align=center><p><font color=\"blue\" size=\"8\">%1</font></p></div>").arg(item->text(1)));
    else if (item->text(3).toInt() == 2)
        text.append(QString("<p><font color=\"blue\" size=\"7\">%1</font></p>").arg(item->text(1)));
    else if (item->text(3).toInt() == 3)
        text.append(QString("<p><font color=\"blue\" size=\"6\">%1</font></p>").arg(item->text(1)));
    else if (item->text(3).toInt() == 4)
        text.append(QString("<p><font color=\"blue\" size=\"5\">%1</font></p>").arg(item->text(1)));
    else if (item->text(3).toInt() == 5)
        text.append(QString("<p><font color=\"blue\" size=\"4\">%1</font></p>").arg(item->text(1)));

    int id = 0;
    while(id < item->text(4).toInt())
    {
        id++;
    }

    m_content->contentText->clear();
    m_content->contentText->setHtml(text);
    m_content->contentText->append(m_content->contentTable->item(id,0)->text());
}

QTreeWidgetItem* Tarjeem::levelIn(QTreeWidgetItem* current, int level)
{
    int numberOfChild = current->childCount();
    switch(level)
    {
    case 1: return current->child(numberOfChild-1); break;
    default: return current;
    }
}

QTreeWidgetItem* Tarjeem::levelUp(QTreeWidgetItem* current, int level)
{
    switch(level)
    {
    case 1: return current->parent(); break;
    case 2: return current->parent()->parent(); break;
    case 3: return current->parent()->parent()->parent(); break;
    case 4: return current->parent()->parent()->parent()->parent(); break;
    case 5: return current->parent()->parent()->parent()->parent()->parent(); break;
    default: return current;
    }
}

void Tarjeem::showNavigation(bool show)
{
    if (show)
        m_content->tableOfContent->show();
    else
        m_content->tableOfContent->hide();

    m_content->showNavigation->setChecked(show);
    viewMenu->actions().at(0)->setChecked(show);

    if (m_content->showNavigation->isChecked())
        m_content->showNavigation->setIcon(QIcon("://navigation_btn_show.png"));
    else
        m_content->showNavigation->setIcon(QIcon("://navigation_btn.png"));
}

void Tarjeem::showTranslation(bool show)
{
    if (show)
        m_content->translatedText->show();
    else
        m_content->translatedText->hide();

    m_content->showTranslation->setChecked(show);
    viewMenu->actions().at(1)->setChecked(show);

    if (m_content->showTranslation->isChecked())
        m_content->showTranslation->setIcon(QIcon("://translation_btn_show.png"));
    else
        m_content->showTranslation->setIcon(QIcon("://translation_btn.png"));
}

void Tarjeem::onTranslate()
{
    m_content->translatedText->setText("Translating...");

    QNetworkAccessManager *netManager = new QNetworkAccessManager();

    connect(netManager, SIGNAL(finished(QNetworkReply*)), SLOT(translateFinished(QNetworkReply*)));

    QString text = m_content->contentText->toPlainText();

    QStringList splitted = text.split("\n"); //example: "الكتاب: مَقَاصِدُ المُكَلفينَ فيمَا يُتعَبَّدُ به لِرَبِّ العَالمين";

    //calculate number of parts
    int numOfParts = 0;
    for (int index=0; index<splitted.count(); index++)
    {
        QStringList tmp = splitted.at(index).split(".");
        numOfParts = numOfParts+tmp.count();
    }
    progressBar->setRange(0,numOfParts-1);

    //run translating
    m_content->translatedText->clear();

    QString lang;
    if (language->currentIndex() == 0) {
        lang.append("id");
    } else if (language->currentIndex() == 1) {
        lang.append("ja");
    } else if (language->currentIndex() == 2) {
        lang.append("en");
    }

    QStringList splitted2;
    for (int index_outer=0; index_outer<splitted.count(); index_outer++)
    {
        splitted2.clear();
        splitted2 = splitted.at(index_outer).split(".");

        for (int index_inner=0; index_inner<splitted2.count(); index_inner++)
        {
            if (splitted2.at(index_inner).size() < 256)
            {
                QUrl url(QString("http://fusi.co.id/translate.php?lang=%1\&\&input=\"%2\"").arg(lang).arg(splitted2.at(index_inner)));
                QNetworkReply *reply = netManager->get(QNetworkRequest(url));
                connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(showDownloadProgress(qint64,qint64)));
            }
        }
    }
}

void Tarjeem::startTranslate()
{
}

void Tarjeem::translateFinished(QNetworkReply* reply)
{
    // no error received?
    if (reply->error() == QNetworkReply::NoError)
    {
        // read data from QNetworkReply here
        QByteArray bytes = reply->readAll();  // bytes
        QString string(bytes); // string

        QStringList wew = string.split("\"");
        m_content->translatedText->append(wew.at(1));
    }
    else
    {
        m_content->translatedText->append("Failed to translate...");
    }

    progressValue++;
    progressBar->setValue(progressValue);
    if (progressValue == progressBar->maximum())
        progressBar->setValue(0);

    reply->deleteLater();

    //    QTimer *timer = new QTimer(this);
    //    timer->setSingleShot(true);
    //    timer->setInterval(100);
    //    timer->start();
    //    connect(timer, SIGNAL(timeout()), this, SLOT(startTranslate()) );
}

void Tarjeem::showDownloadProgress(qint64 byteReceived, qint64 byteTotal)
{
    //    progressBar->setRange(0, byteTotal);
}

void Tarjeem::openSettings()
{
    m_settings = new Settings();
    m_settings->show();
}

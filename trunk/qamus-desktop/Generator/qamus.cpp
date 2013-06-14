#include "qamus.h"

#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QEvent>
#include <QFileDialog>
#include <QSpinBox>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QUrlQuery>
#include <QGroupBox>
#include <QRadioButton>
#include <QDebug>

Qamus::Qamus()
{
    QVBoxLayout *vbox = new QVBoxLayout;
    QVBoxLayout *vbox1 = new QVBoxLayout;
    QHBoxLayout *hbox = new QHBoxLayout;

    QGroupBox *group = new QGroupBox("Apps ID", this);
    QFormLayout *fbox1 = new QFormLayout;
    publicCheck = new QRadioButton("Use Public Apps ID", group);
    ownCheck = new QRadioButton("Use Own Apps ID", group);
    clientId = new QLineEdit(group);
    clientSecret = new QLineEdit(group);
    fbox1->addRow("Apps ID Source", publicCheck);
    fbox1->addRow("", ownCheck);
    fbox1->addRow("Client ID", clientId);
    fbox1->addRow("Client Secret", clientSecret);
    group->setLayout(fbox1);

    QGroupBox *group1 = new QGroupBox("Input Wordlists", this);
    QFormLayout *fbox = new QFormLayout;
    wordlist = new QLineEdit(group1);
    firstIndex = new QSpinBox(group1);
    lastIndex = new QSpinBox(group1);
    fbox->addRow("Input File (Wordlist)", wordlist);
    fbox->addRow("First Index (max=10000)", firstIndex);
    fbox->addRow("Last Index (max=10000)", lastIndex);
    group1->setLayout(fbox);

    table = new QTableWidget(group1);
    scan = new QPushButton("Scan", this);
    push = new QPushButton("Translate", this);
    save = new QPushButton("Save to XML!", this);
    query = new QLabel("URL: ", this);
    status = new QProgressBar(this);

    publicCheck->setChecked(true);
    clientId->setText("tarjeem");
    clientSecret->setText("DzV/gL2NagVZr5DHRFnNfz+CVXUw+UFhX9JQ6VDQITs");
    clientId->setDisabled(true);
    clientSecret->setDisabled(true);

    scan->setFixedHeight(80);
    push->setFixedHeight(80);
    save->setFixedHeight(80);

    table->setColumnCount(2);
    table->setRowCount(0);
    table->setColumnWidth(0,300);
    table->setColumnWidth(1,300);
    table->setSortingEnabled(true);

    firstIndex->setRange(0,9000000);
    lastIndex->setRange(0,9000000);
    lastIndex->setValue(1);

    vbox1->addWidget(scan);
    vbox1->addWidget(push);
    vbox1->addWidget(save);
    vbox1->setAlignment(Qt::AlignTop);

    hbox->addLayout(vbox1);
    hbox->addWidget(table);

    vbox->addWidget(group);
    vbox->addWidget(group1);
    vbox->addLayout(hbox);
    vbox->addWidget(query);
    vbox->addWidget(status);

    connect(publicCheck, SIGNAL(clicked()), this, SLOT(changeAppsIdSource()));
    connect(ownCheck, SIGNAL(clicked()), this, SLOT(changeAppsIdSource()));
    connect(scan, SIGNAL(clicked()), this, SLOT(onScan()) );
    connect(push, SIGNAL(clicked()), this, SLOT(onRun()) );
    connect(save, SIGNAL(clicked()), this, SLOT(onSave()) );
    wordlist->installEventFilter(this);

    currentRow = 0;
    progressValue = 0;
    this->setLayout(vbox);
}

bool Qamus::eventFilter(QObject* object, QEvent* event)
{
    if(object == wordlist && event->type() == QEvent::MouseButtonPress) {
        openFile();
        return false; // lets the event continue to the edit
    }
    return false;
}

Qamus::~Qamus()
{

}

void Qamus::changeAppsIdSource()
{
    if (publicCheck->isChecked()) {
        clientId->setDisabled(true);
        clientSecret->setDisabled(true);
    } else {
        clientId->setDisabled(false);
        clientSecret->setDisabled(false);
    }
}

void Qamus::openFile()
{
    currentWordlistFile = QFileDialog::getOpenFileName(this, tr("Buka File Wordlist"), "", tr("Text (*.txt)"));

    if(currentWordlistFile.isEmpty())
    {
        return;
    }
    else
    {
        wordlist->setText(currentWordlistFile);
    }
}

void Qamus::onScan()
{
    table->clearContents();
    currentRow = 0;

    QFile file(currentWordlistFile);
    if (!file.open(QFile::ReadOnly))
    {
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-8");
    QString line = in.readLine();

    int index = 0;
    int minIndex = firstIndex->text().toInt();
    int maxIndex = lastIndex->text().toInt();

    status->setRange(minIndex, maxIndex-1);
    progressValue = minIndex;
    status->setValue(progressValue);

    while ((!line.isNull()) && (index < maxIndex))
    {
        line = in.readLine();
        if ((index >= minIndex) && (index < maxIndex))
        {
            table->setRowCount(currentRow+1);
            table->setItem(currentRow, 0, new QTableWidgetItem(line) );
            currentRow++;
        }
        index++;
    }

    file.close();
}

void Qamus::onRun()
{
    QNetworkAccessManager *netManager = new QNetworkAccessManager();
    connect(netManager, SIGNAL(finished(QNetworkReply*)), SLOT(translateFinished(QNetworkReply*)));

    QUrlQuery qurlqr;

    for (int i=0; i<table->rowCount(); i++)
    {
        qurlqr.clear();

        QUrl url;
        if (ownCheck->isChecked())
        {
            qurlqr.addQueryItem("cid",      clientId->text());
            qurlqr.addQueryItem("csecret",  clientSecret->text());
            qurlqr.addQueryItem("lang",     "id");
            qurlqr.addQueryItem("idx",      QString("%1").arg(i) );
            qurlqr.addQueryItem("input",    table->item(i,0)->text());
            url = QString("http://fusi.co.id/translatedict.php?");
        }
        else
        {
            qurlqr.addQueryItem("lang",     "id");
            qurlqr.addQueryItem("idx",      QString("%1").arg(i) );
            qurlqr.addQueryItem("input",    table->item(i,0)->text());
            url = QString("http://fusi.co.id/translatego.php?");
        }

        url.setQuery(qurlqr);
        url.toEncoded();

        qDebug() << url.toString(QUrl::FullyEncoded);

        QNetworkReply *reply = netManager->get(QNetworkRequest(url));
    }
}

void Qamus::onSave()
{
    QString savepath = QFileDialog::getSaveFileName(this, tr("Save Qamus Database"), "", tr("XML Document (*.xml)"));

    QStringList attributes;
    attributes << "ar" << "id";
    CreateXMLFile(table, "data", savepath, attributes);
}

void Qamus::translateFinished(QNetworkReply* reply)
{
    // no error received?
    if (reply->error() == QNetworkReply::NoError)
    {
        // read data from QNetworkReply here
        QByteArray bytes = reply->readAll();  // bytes
        QString string(bytes); // string
        QStringList splitted = string.split(";");

        int detectedIndex = splitted.at(0).toInt();
        table->setItem(detectedIndex, 1, new QTableWidgetItem(splitted.at(1)) );
    }

    query->setText(QString("URL: %1").arg(reply->url().toString(QUrl::FullyEncoded)));

    progressValue++;
    status->setValue(progressValue);
    if (progressValue == status->maximum())
        status->setValue(status->minimum());

    reply->deleteLater();
}


void Qamus::CreateXMLFile(QTableWidget *table, QString itemname, QString xmlpath, QStringList attributes)
{
    QFile file(xmlpath);

    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(0, "Read only", QString("File database %1 sedang digunakan! Tutup dulu, dan ulangi!").arg(xmlpath));
    }
    else
    {
        QXmlStreamWriter* xmlWriter = new QXmlStreamWriter();

        xmlWriter->setDevice(&file);
        xmlWriter->setAutoFormatting(true);

        xmlWriter->writeStartDocument();
        xmlWriter->writeStartElement("database");
        xmlWriter->writeAttribute("server", "localhost");

        for (int rowCount=0; rowCount<table->rowCount(); rowCount++)
        {
            xmlWriter->writeStartElement(itemname);

            for (int columnCount=0; columnCount<table->columnCount(); columnCount++)
            {
                xmlWriter->writeAttribute(attributes.at(columnCount),
                                          table->item(rowCount,columnCount)->data(0).toString());
            }

            xmlWriter->writeEndElement();
        }

        xmlWriter->writeEndElement();
        xmlWriter->writeEndDocument();

        delete xmlWriter;
    }

    file.close();
}

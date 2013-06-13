#include "qamus.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QXmlStreamWriter>
#include <QFile>
#include <QApplication>
#include <QDesktopWidget>

#include <iostream>

Qamus::Qamus()
{
    QWidget *main = new QWidget();
    input = new QLineEdit(main);
    search = new QPushButton("Search",main);
    setting = new QPushButton("Setting",main);
    list = new QTextEdit(main);
    list->setReadOnly(true);
    status = new QLabel(main);
    status->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    //    list->setStyleSheet( "QListWidget::item { border-bottom: 1px solid black; }" );
    //    list->setStyleSheet( "QListWidget::item:selected { color: black; background-color: orange; }" );

    QVBoxLayout *vbox = new QVBoxLayout;
    QHBoxLayout *hbox = new QHBoxLayout;

    hbox->addWidget(input, 60);
    hbox->addWidget(search, 20);
    hbox->addWidget(setting, 20);

    vbox->addLayout(hbox);
    vbox->addWidget(list);
    vbox->addWidget(status, 0);

    main->setLayout(vbox);
    this->setCentralWidget(main);

    wordCount = 0;

    getDictionaryData();
    connect(search, SIGNAL(clicked()), this, SLOT(onSearch()) );
    connect(setting, SIGNAL(clicked()), this, SLOT(openSetting()) );
}

Qamus::~Qamus()
{
}

void Qamus::openSetting()
{
    m_setting = new Setting();
    m_setting->setGeometry(0,0,500,300);
    m_setting->move(QApplication::desktop()->screen()->rect().center() - m_setting->rect().center());
    m_setting->show();
}

void Qamus::onSearch()
{
    QString result = hash.value(input->text(), QString("Kata <span style=\"color:red;\">%1</span> tidak ditemukan\n\n").arg(input->text()));

    QString content = QString(
                "<ul>"
                "   <li>"
                "       <div style=\"font-weight:bold; font-size:18px;\"><p>%1</p></div>"
                "       <div style=\"text-align:right; font-size:12px;\"><p>%2</p></div>"
                "   </li>"
                "   <hr />"
                "</ul>"
                ).arg(input->text())
            .arg(result);

    list->clear();
    list->setHtml(content);
}

void Qamus::getDictionaryData()
{
    //read from XML
    QDir dir;
    dir.setPath("./Data");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        QFile file(fileInfo.filePath());

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(NULL, "Open File Error", "File not open.", 0, 0, 0);
        }
        else
        {
            QXmlStreamReader xml(&file);

            while(!xml.atEnd() && !xml.hasError())
            {
                QXmlStreamReader::TokenType token = xml.readNext();

                if (token == QXmlStreamReader::StartDocument)
                    continue;

                if (token == QXmlStreamReader::StartElement) {

                    if (xml.name() == "database")
                        continue;

                    if (xml.name() == "data") {
                        QXmlStreamAttributes attributes = xml.attributes();
                        hash[attributes.value("ar").toString()] = attributes.value("id").toString();
                        wordCount++;
                    }

                }
            }

            xml.clear();
        }

        file.close();

        std::cout << qPrintable(QString("%1 %2").arg(fileInfo.filePath()).arg(fileInfo.fileName()));
        std::cout << std::endl;
    }

    status->setText(QString("%1 words available").arg(wordCount));
}

void Qamus::getDictionaryDataFromFile(QString filepath)
{
    QFile file(filepath);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(NULL, "Open File Error", "File not open.", 0, 0, 0);
    }
    else
    {
        QXmlStreamReader xml(&file);

        while(!xml.atEnd() && !xml.hasError())
        {
            QXmlStreamReader::TokenType token = xml.readNext();

            if (token == QXmlStreamReader::StartDocument)
                continue;

            if (token == QXmlStreamReader::StartElement) {

                if (xml.name() == "database")
                    continue;

                if (xml.name() == "data") {
                    QXmlStreamAttributes attributes = xml.attributes();
                    hash[attributes.value("ar").toString()] = attributes.value("id").toString();
                    wordCount++;
                }

            }
        }

        xml.clear();
    }

    file.close();
}

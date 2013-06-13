#ifndef QAMUS_H
#define QAMUS_H

#include <QMainWindow>
#include <QLabel>
#include <QHash>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QStatusBar>
#include <QTextEdit>

#include "setting.h"

class Qamus : public QMainWindow
{
    Q_OBJECT

public:
    Qamus();
    ~Qamus();

public slots:
    void openSetting();
    void onSearch();

private:
    QLineEdit *input;
    QPushButton *search;
    QPushButton *setting;
    QTextEdit *list;
    QLabel *status;
    QHash<QString, QString> hash;

    int wordCount;
    void getDictionaryData();
    void getDictionaryDataFromFile(QString file);

    Setting *m_setting;
};

#endif

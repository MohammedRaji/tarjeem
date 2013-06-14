#ifndef QAMUS_H
#define QAMUS_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QStatusBar>
#include <QProgressBar>
#include <QTableWidget>
#include <QNetworkReply>
#include <QCheckBox>
#include <QRadioButton>

class Qamus : public QWidget
{
    Q_OBJECT

public:
    Qamus();
    ~Qamus();

    QRadioButton *publicCheck;
    QRadioButton *ownCheck;
    QLineEdit *clientId;
    QLineEdit *clientSecret;
    QLineEdit *wordlist;
    QSpinBox *firstIndex;
    QSpinBox *lastIndex;
    QTableWidget *table;
    QPushButton *scan;
    QPushButton *push;
    QPushButton *save;
    QLabel *query;
    QProgressBar *status;

    QString currentWordlistFile;
    int currentRow;
    int progressValue;

protected:
    bool eventFilter(QObject* object, QEvent* event);

public slots:
    void openFile();

    void onScan();
    void onRun();
    void onSave();

    void changeAppsIdSource();
    void translateFinished(QNetworkReply* reply);
    void CreateXMLFile(QTableWidget *table, QString itemname, QString xmlpath, QStringList attributes);

};

#endif

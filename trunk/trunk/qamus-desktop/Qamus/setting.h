#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>

class Setting : public QDialog
{
    Q_OBJECT

public:
    Setting();
    ~Setting();

public slots:
    void openXML();
    void onApply();

private:
    QTableWidget *list;
    QPushButton *add;
    QPushButton *remove;
    QPushButton *apply;
    QPushButton *ok;
};

#endif

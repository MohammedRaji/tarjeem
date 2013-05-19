#ifndef CONTENT_H
#define CONTENT_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QTreeWidget>
#include <QTableWidget>

class Content : public QWidget
{
    Q_OBJECT

public:
    Content(QWidget *parent = NULL);
    ~Content();

    int bookId;

    QLabel *leftMargin;
    QTextEdit *contentText;
    QTextEdit *translatedText;
    QLabel *rightMargin;

    QTreeWidget  *tableOfContent;
    QTableWidget *contentTable;
};

#endif

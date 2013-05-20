#ifndef CONTENT_H
#define CONTENT_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>
#include <QTreeWidget>
#include <QTableWidget>
#include <QPushButton>

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

    QPushButton *showNavigation;
    QPushButton *showTranslation;

    QTreeWidget  *tableOfContent;
    QTableWidget *contentTable;

protected:
    bool eventFilter(QObject* object, QEvent* event);
};

#endif

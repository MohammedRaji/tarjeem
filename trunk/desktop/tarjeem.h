#ifndef TARJEEM_H
#define TARJEEM_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QTextEdit>
#include <QTabWidget>
#include <QTableWidget>
#include <QTreeWidgetItem>
#include <QComboBox>
#include <QMenu>

class Tarjeem : public QMainWindow
{
    Q_OBJECT

public:
    Tarjeem();
    ~Tarjeem();

public slots:
    void openBook();
    void openHelp();
    void onOpenBook();
    void onItemClicked(QTreeWidgetItem* item);

private:
    void createMenu();
    void activateMenu(bool opt);

    QMenu *fileMenu;
    QMenu *translateMenu;
    QMenu *helpMenu;

    QString currentBookFile;

    QStringList listMain;
    QStringList listContent;

    QTabWidget   *tab;
    QTableWidget *mainInfo;
    QWidget      *content;
    QTreeWidget  *tableOfContent;
    QTextEdit    *contentText;
    QComboBox    *language;
};

#endif

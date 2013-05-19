#ifndef TARJEEM_H
#define TARJEEM_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QTextEdit>
#include <QTabWidget>
#include <QDockWidget>
#include <QTableWidget>
#include <QTreeWidgetItem>
#include <QComboBox>
#include <QLabel>
#include <QProgressBar>
#include <QMenu>

#include "content.h"

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

    void showNavigation(bool state);
    void showTranslation(bool state);

private:
    void createMenu();
    void createStatusBar();
    void activateMenu(bool opt);
    QTreeWidgetItem* levelIn(QTreeWidgetItem* current, int level);
    QTreeWidgetItem* levelUp(QTreeWidgetItem* current, int level);

    QMenu        *fileMenu;
    QMenu        *translateMenu;
    QMenu        *viewMenu;
    QMenu        *helpMenu;

    QLabel       *status;
    QProgressBar *progressBar;
    QComboBox    *language;

    QString       currentBookFile;

    QStringList   listMain;
    QStringList   listContent;

    QDockWidget  *dock;
    Content      *m_content;

    int bookId;

};

#endif

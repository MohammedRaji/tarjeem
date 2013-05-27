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
#include <QNetworkReply>

#include "content.h"
#include "settings.h"

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
    void onTranslate();

    void showNavigation(bool state);
    void showTranslation(bool state);
    void translateFinished(QNetworkReply*);
    void startTranslate();
    void showDownloadProgress(qint64 byteReceived, qint64 byteTotal);
    void openSettings();

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
    Settings     *m_settings;

    int bookId;

    int progressValue;
};

#endif

#include "content.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QPalette>

Content::Content(QWidget *parent)
    : QWidget (parent)
{
    //----------------------------------------------
    // Content
    //----------------------------------------------
    QLabel *left = new QLabel(parent);
    leftMargin = new QLabel(parent);
    contentText = new QTextEdit(parent);
    translatedText = new QTextEdit(parent);
    rightMargin = new QLabel(parent);
    QLabel *right = new QLabel(parent);

    left->setScaledContents(true);
    left->setPixmap(QPixmap("://background.png"));
    right->setScaledContents(true);
    right->setPixmap(QPixmap("://background.png"));
    leftMargin->setScaledContents(true);
    leftMargin->setPixmap(QPixmap("://bg_white.png"));
    rightMargin->setScaledContents(true);
    rightMargin->setPixmap(QPixmap("://bg_white.png"));

    QFont fontAr("Arial", 16, QFont::Normal, false);
    contentText->setFont(fontAr);
    contentText->setStyleSheet("QLabel { color : black; }");
    contentText->setFrameShadow(QFrame::Raised);
    contentText->setFrameShape(QFrame::VLine);
    contentText->setFrameStyle(QFrame::NoFrame);
    contentText->setWindowFlags(Qt::FramelessWindowHint);

    QFont fontId("Arial", 12, QFont::Normal, false);
    translatedText->setFont(fontId);
    translatedText->setStyleSheet("QLabel { color : black; }");
    translatedText->setFrameShadow(QFrame::Raised);
    translatedText->setFrameShape(QFrame::VLine);
    translatedText->setFrameStyle(QFrame::NoFrame);
    translatedText->setWindowFlags(Qt::FramelessWindowHint);
    translatedText->hide();

    //----------------------------------------------
    // Table of Content
    //----------------------------------------------
    tableOfContent = new QTreeWidget(this);
    contentTable = new QTableWidget(this);

    contentTable->setColumnCount(2);
    contentTable->setRowCount(0);
    contentTable->hide();

    tableOfContent->setColumnCount(1);
    tableOfContent->setColumnWidth(0,300); //icon
    tableOfContent->setColumnWidth(1,20); //icon
    tableOfContent->setColumnWidth(2,20); //icon
    tableOfContent->setColumnWidth(3,20); //icon
    tableOfContent->setHeaderHidden(true);

    QPalette p( tableOfContent->palette() );
    p.setColor( QPalette::Base, Qt::darkGray );
    tableOfContent->setPalette( p );

    //----------------------------------------------
    // Content Layout
    //----------------------------------------------
    QHBoxLayout *contentLayout = new QHBoxLayout;
    contentLayout->addWidget(tableOfContent,30);
    contentLayout->addWidget(left,15);
    contentLayout->addWidget(leftMargin,5);
    contentLayout->addWidget(contentText,70);
    contentLayout->addWidget(translatedText,70);
    contentLayout->addWidget(rightMargin,5);
    contentLayout->addWidget(right,15);
    contentLayout->setMargin(0);
    contentLayout->setSpacing(0);
    this->setLayout(contentLayout);
}

Content::~Content()
{

}

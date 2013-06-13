#include "setting.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>

Setting::Setting()
{
    QHBoxLayout *hbox = new QHBoxLayout;
    QVBoxLayout *vbox = new QVBoxLayout;

    list = new QTableWidget();
    add = new QPushButton("Add");
    remove = new QPushButton("Remove");
    apply = new QPushButton("Apply");
    ok = new QPushButton("OK");

    list->setRowCount(100);
    list->setColumnCount(1);
    list->horizontalHeader()->setStretchLastSection(true);
    list->horizontalHeader()->hide();
    list->verticalHeader()->hide();

    vbox->addWidget(add);
    vbox->addWidget(remove);
    vbox->addWidget(apply);
    vbox->addWidget(ok);
    vbox->setAlignment(Qt::AlignTop);

    hbox->addWidget(list,70);
    hbox->addLayout(vbox,30);

    this->setLayout(hbox);
}

Setting::~Setting()
{

}

void Setting::openXML()
{

}

void Setting::onApply()
{

}

#include "DbInfoTableForm.h"
#include "ui_DbInfoTableForm.h"

#include <QTextStream>

void fillInfoTable(QTreeWidget* treeWidget, QString info);

DbInfoTableForm::DbInfoTableForm(QString info, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DbInfoTableForm)
{
    ui->setupUi(this);

    fillInfoTable(ui->treeWidget, info);
}

DbInfoTableForm::~DbInfoTableForm()
{
    delete ui;
}

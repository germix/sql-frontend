#include "DbTableStructureForm.h"
#include "ui_DbTableStructureForm.h"

#include "utils.h"
#include <QTextStream>

DbTableStructureForm::DbTableStructureForm(const QString dbName, const QString dbTable, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DbTableStructureForm)
{
    ui->setupUi(this);

//  QMessageBox::information(0, "", exec_sql("SHOW FULL COLUMNS IN `"+dbTable+"` IN `"+dbName+"`;"), QMessageBox::Information);

    int i = 0;
    QString s = exec_sql("SHOW FULL COLUMNS IN `"+dbTable+"` IN `"+dbName+"`;");
    QTextStream in(&s);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList sl = line.split("\t");
        if(i == 0)
        {
            ui->treeWidget->setHeaderLabels(sl);
        }
        else if(i > 0)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(sl);
            item->setIcon(0, QIcon(":/items/tvw_item-table-column.png"));

            ui->treeWidget->addTopLevelItem(item);
        }
        i++;
    }
}

DbTableStructureForm::~DbTableStructureForm()
{
    delete ui;
}

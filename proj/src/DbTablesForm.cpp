#include "DbTablesForm.h"
#include "ui_DbTablesForm.h"


#include "utils.h"
#include <QTextStream>
#include "ISetCurrentWidget.h"
#include "DbInfoTableForm.h"
#include "DbTableStructureForm.h"

DbTablesForm::DbTablesForm(ISetCurrentWidget* ___setCurrentWidget, const QString& ___dbName, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::DbTablesForm)
    , dbName(___dbName)
    , setCurrentWidget(___setCurrentWidget)
{
    ui->setupUi(this);
    //QMessageBox::information(0, "", exec_sql("SHOW COLUMNS IN brand IN `canawa`;"), QMessageBox::Information);

    int i = 0;
    QString s = exec_sql("SHOW TABLES IN `"+dbName+"`;");
    QTextStream in(&s);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        if(i > 0)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(QStringList() << line);
            item->setIcon(0, QIcon(":/items/tvw_item-table.png"));

            ui->treeWidget->addTopLevelItem(item);
        }
        i++;
    }
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slotTreeWidget_itemDoubleClicked(QTreeWidgetItem*,int)));
}

DbTablesForm::~DbTablesForm()
{
    delete ui;
}

void DbTablesForm::slotTreeWidget_itemDoubleClicked(QTreeWidgetItem* item, int column)
{
    QString table = item->text(0);
    setCurrentWidget->setCurrentWidget(new DbInfoTableForm(exec_sql("SELECT * FROM `"+dbName+"`.`"+table+"`;")));
//  setCurrentWidget->setCurrentWidget(new DbTableStructureForm(dbName, item->text(0)));
}

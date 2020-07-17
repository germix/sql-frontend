#include <QProcess>

QString mysql;

QString exec_sql(const QString& sql, QString* err)
{
    QProcess p;

    p.start(mysql + " -u root -e \""+sql+"\"");
    p.waitForFinished();
    if(err)
        *err = p.readAllStandardError();
    return p.readAll();
}

#include <QTextStream>
#include <QTreeWidget>
void fillInfoTable(QTreeWidget* treeWidget, QString info)
{
    int i = 0;
    QTextStream in(&info);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QStringList sl = line.split("\t");
        if(i == 0)
        {
            treeWidget->setHeaderLabels(sl);
        }
        else if(i > 0)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(sl);
            item->setIcon(0, QIcon(":/items/tvw_item-table-row.png"));

            treeWidget->addTopLevelItem(item);
        }
        i++;
    }
}

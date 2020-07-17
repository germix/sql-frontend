#ifndef DBTABLESFORM_H
#define DBTABLESFORM_H

#include <QWidget>

namespace Ui {
class DbTablesForm;
}
class QTreeWidgetItem;
class ISetCurrentWidget;

class DbTablesForm : public QWidget
{
    Q_OBJECT
    Ui::DbTablesForm*   ui;
    QString             dbName;
    ISetCurrentWidget*  setCurrentWidget;
public:
    explicit DbTablesForm(ISetCurrentWidget* setCurrentWidget, const QString& dbName, QWidget* parent = 0);
    ~DbTablesForm();
private slots:
    void slotTreeWidget_itemDoubleClicked(QTreeWidgetItem* item, int column);
};

#endif // DBTABLESFORM_H

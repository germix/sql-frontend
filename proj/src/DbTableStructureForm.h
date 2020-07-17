#ifndef DBTABLESTRUCTUREFORM_H
#define DBTABLESTRUCTUREFORM_H

#include <QWidget>

namespace Ui {
class DbTableStructureForm;
}

class DbTableStructureForm : public QWidget
{
    Q_OBJECT
    Ui::DbTableStructureForm* ui;
public:
    explicit DbTableStructureForm(const QString dbName, const QString dbTable, QWidget* parent = 0);
    ~DbTableStructureForm();
private:
};

#endif // DBTABLESTRUCTUREFORM_H

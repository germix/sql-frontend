#ifndef DBINFOTABLEFORM_H
#define DBINFOTABLEFORM_H

#include <QWidget>

namespace Ui {
class DbInfoTableForm;
}

class DbInfoTableForm : public QWidget
{
    Q_OBJECT
    Ui::DbInfoTableForm* ui;
public:
    explicit DbInfoTableForm(QString info, QWidget* parent = 0);
    ~DbInfoTableForm();
private:
};

#endif // DBINFOTABLEFORM_H

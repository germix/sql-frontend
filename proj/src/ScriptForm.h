#ifndef SCRIPTFORM_H
#define SCRIPTFORM_H

#include <QWidget>

namespace Ui {
class ScriptForm;
}

#include "SqlHighlighter.h"

class ScriptForm : public QWidget
{
    Q_OBJECT
    Ui::ScriptForm*     ui;
    QString             dbName;
    SqlHighlighter*     highlighter;
    QWidget*            resultWidget;
public:
    explicit ScriptForm(const QString& dbName, QWidget* parent = 0);
    ~ScriptForm();
private:
    void exec();
private:
    bool eventFilter(QObject* watched, QEvent* event);
private slots:
    void slotButton();
};

#endif // SCRIPTFORM_H

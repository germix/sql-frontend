#include "ScriptForm.h"
#include "ui_ScriptForm.h"

#include "utils.h"
#include "DbInfoTableForm.h"

//void fillInfoTable(QTreeWidget* treeWidget, QString info);

ScriptForm::ScriptForm(const QString& ___dbName, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::ScriptForm)
    , dbName(___dbName)
{
    ui->setupUi(this);

    ui->textEdit->setFocus();
    highlighter = new SqlHighlighter(ui->textEdit->document());

    ui->textEdit->installEventFilter(this);

    resultWidget = 0;

    connect(ui->btnRun, SIGNAL(clicked()), this, SLOT(slotButton()));
    connect(ui->btnClear, SIGNAL(clicked()), this, SLOT(slotButton()));
}

ScriptForm::~ScriptForm()
{
    delete ui;
}
#include <QMessageBox>
void ScriptForm::exec()
{
    QString s;
    if(!dbName.isEmpty())
    {
        s += "USE `"+dbName+"`aa;";
    }
    QString err;
    QString ret = exec_sql(s + ui->textEdit->toPlainText(), &err);

    if(resultWidget)
        delete resultWidget;

    if(!err.isEmpty())
        resultWidget = new QTextEdit(err);
    else
        resultWidget = new DbInfoTableForm(ret);

    ((QGridLayout*)layout())->addWidget(resultWidget, 4, 0, -1, 0);
}
bool ScriptForm::eventFilter(QObject* watched, QEvent* event)
{
    if(watched == ui->textEdit)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent* e = (QKeyEvent*)event;
            if((e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) && e->modifiers() & Qt::ControlModifier)
            {
                exec();
                return true;
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}
void ScriptForm::slotButton()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    if(button == ui->btnRun)
    {
        exec();
    }
    else if(button == ui->btnClear)
    {
        if(resultWidget)
        {
            delete resultWidget;
            resultWidget = NULL;
        }
    }
}

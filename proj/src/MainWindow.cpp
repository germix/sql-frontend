#include "MainWindow.h"
#include "ui_MainWindow.h"

#define SETTINGS_APPLICATION "SqlFrontend"
#define SETTINGS_ORGANIZATION "Germix"

#include <QSettings>

#include "HomeForm.h"
#include "AboutDialog.h"
#include "SettingsDialog.h"

#include "DbTablesForm.h"

#include "ScriptForm.h"

#include <QProcess>
#include <QMessageBox>
#include <QSqlDatabase>

#include <QTextStream>

#include "utils.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSettings s(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);

    mysql = s.value("Mysql").toString();

    systemDatabases.append("performance_schema");
    systemDatabases.append("information_schema");
    systemDatabases.append("mysql");

    connect(ui->actionFileExit, SIGNAL(triggered()), this, SLOT(slotActions()));
    connect(ui->actionOptionsSettings, SIGNAL(triggered()), this, SLOT(slotActions()));
    connect(ui->actionHelpAbout, SIGNAL(triggered()), this, SLOT(slotActions()));
    connect(ui->actionSqlScript, SIGNAL(triggered()), this, SLOT(slotActions()));


    splitter = new QSplitter();
    splitter->addWidget(ui->treeWidget);
    splitter->addWidget(ui->contentWidget);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    setCentralWidget(splitter);

    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotTreeWidget_customContextMenuRequested(QPoint)));
    connect(ui->treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(slotTreeWidget_itemDoubleClicked(QTreeWidgetItem*,int)));

    restoreGeometry(s.value("WindowGeometry").toByteArray());
    restoreState(s.value("WindowState").toByteArray());
    splitter->restoreGeometry(s.value("SplitterGeometry").toByteArray());
    splitter->restoreState(s.value("SplitterState").toByteArray());

    currentWidget = 0;

    /*
    QStringList drivers = QSqlDatabase::drivers();
    for(int i = 0; i < drivers.size(); i++)
    {
        qDebug("driver: %ls", drivers.at(i).constData());
    }
    */
    loadDatabases();
}

MainWindow::~MainWindow()
{
    QSettings s(SETTINGS_ORGANIZATION, SETTINGS_APPLICATION);
    s.setValue("WindowGeometry", saveGeometry());
    s.setValue("WindowState", saveState());
    s.setValue("SplitterGeometry", splitter->saveGeometry());
    s.setValue("SplitterState", splitter->saveState());
    s.setValue("Mysql", mysql);
    delete ui;
}
void MainWindow::setCurrentWidget(QWidget* widget)
{
    if(currentWidget != NULL)
    {
        ui->contentWidget->layout()->removeWidget(currentWidget);
        currentWidget->hide();
    }
    currentWidget = widget;
    if(widget != NULL)
    {
        ui->contentWidget->layout()->addWidget(widget);
        currentWidget->show();
    }
}
void MainWindow::loadDatabases()
{
    ui->treeWidget->clear();
    activeItemDb = NULL;
    setCurrentWidget(new HomeForm());

    {
        QString s = exec_sql("SHOW DATABASES;");
#if 0
        QStringList lines = s.split("\n");
        for(int i = 1; i < lines.size(); i++)
        {
            QTreeWidgetItem* item = new QTreeWidgetItem(QStringList() << lines.at(i));
            item->setIcon(0, QIcon(":/items/tvw_item-db.png"));

            ui->treeWidget->addTopLevelItem(item);
        }
#else
        int i = 0;
        QTextStream in(&s);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            if(i > 0)
            {
                QTreeWidgetItem* item = new QTreeWidgetItem(QStringList() << line);
                item->setIcon(0, QIcon(":/items/tvw_item-db.png"));

                ui->treeWidget->addTopLevelItem(item);
            }
            i++;
        }
#endif
    }
}
void MainWindow::slotActions()
{
    QAction* action = qobject_cast<QAction*>(sender());

    if(action == ui->actionFileExit)
    {
        close();
    }
    else if(action == ui->actionHelpAbout)
    {
        AboutDialog().exec();
    }
    else if(action == ui->actionOptionsSettings)
    {
        SettingsDialog dlg(mysql);

        if(dlg.exec() == SettingsDialog::Accepted)
        {
            mysql = dlg.getMysql();
        }
    }
    else if(action == ui->actionSqlScript)
    {
        if(!activeItemDb)
            setCurrentWidget(new ScriptForm(""));
        else
            setCurrentWidget(new ScriptForm(activeItemDb->text(0)));
    }
}
void MainWindow::slotTreeWidget_itemDoubleClicked(QTreeWidgetItem* item, int column)
{
//	if(activeItemDb != item)
    {
        if(activeItemDb)
            activeItemDb->setIcon(0, QIcon(":/items/tvw_item-db.png"));

        activeItemDb = item;

        if(activeItemDb)
        {
            activeItemDb->setIcon(0, QIcon(":/items/tvw_item-db-active.png"));

            setCurrentWidget(new DbTablesForm(this, item->text(0)));
        }
    }
}
void MainWindow::slotTreeWidget_customContextMenuRequested(const QPoint& pos)
{
    QMenu menu;
    QAction* action;
    QTreeWidgetItem* item = ui->treeWidget->itemAt(pos);
    QAction* actionDeleteDb = nullptr;
    if(item != nullptr)
    {
        menu.addAction(actionDeleteDb = new QAction(tr("Delete database"), &menu));
    }
    if(nullptr != (action = menu.exec(QCursor::pos())))
    {
        if(action == actionDeleteDb)
        {
            if(QMessageBox::Yes == QMessageBox::question(
                                            this,
                                            tr("Delete database"),
                                            tr("Are you sure to delete \"%1\" database?").arg(item->text(0)),
                                            QMessageBox::Yes | QMessageBox::No))
            {
                QString ret;
                QString sql;
                QString error;

                ret = exec_sql("DROP DATABASE `" + item->text(0) + "`;", &error);
                if(error.isEmpty())
                {
                }
                else
                {
                    QMessageBox::information(this, tr("Error"), tr("Can't delete database \"%1\"\n\n%2").arg(item->text(0)).arg(error), QMessageBox::Ok);
                }
#ifdef DEBUG
                qDebug("ret: %ls", ret.constData());
                qDebug("sql: %ls", sql.constData());
                qDebug("error: %ls", error.constData());
#endif
            }
        }
    }
}


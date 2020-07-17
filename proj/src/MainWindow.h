#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
#include <QSplitter>

class QTreeWidgetItem;
#include "ISetCurrentWidget.h"

class MainWindow : public QMainWindow, public ISetCurrentWidget
{
    Q_OBJECT
    Ui::MainWindow*     ui;
    QStringList         systemDatabases;

    QSplitter*          splitter;
    QWidget*            currentWidget;

    QTreeWidgetItem*    activeItemDb;
public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
private:
    void setCurrentWidget(QWidget* widget);
    void loadDatabases();
private slots:
    void slotActions();
    void slotTreeWidget_itemDoubleClicked(QTreeWidgetItem* item, int column);
    void slotTreeWidget_customContextMenuRequested(const QPoint& pos);
};

#endif // MAINWINDOW_H

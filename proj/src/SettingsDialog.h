#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    Ui::SettingsDialog* ui;
public:
    explicit SettingsDialog(const QString& mysql, QWidget* parent = 0);
    ~SettingsDialog();
public:
    QString getMysql() const;
private:
};

#endif // SETTINGSDIALOG_H

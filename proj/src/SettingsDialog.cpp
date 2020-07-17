#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

SettingsDialog::SettingsDialog(const QString& mysql, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    ui->txtMysql->setText(mysql);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

QString SettingsDialog::getMysql() const
{
    return ui->txtMysql->text();
}

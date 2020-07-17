#include "HomeForm.h"
#include "ui_HomeForm.h"

HomeForm::HomeForm(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::HomeForm)
{
    ui->setupUi(this);
}

HomeForm::~HomeForm()
{
    delete ui;
}

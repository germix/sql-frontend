#ifndef HOMEFORM_H
#define HOMEFORM_H

#include <QWidget>

namespace Ui {
class HomeForm;
}

class HomeForm : public QWidget
{
    Q_OBJECT
    Ui::HomeForm* ui;
public:
    explicit HomeForm(QWidget* parent = 0);
    ~HomeForm();
private:
};

#endif // HOMEFORM_H

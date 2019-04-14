#include "exp_start.h"
#include "ui_exp_start.h"

exp_start::exp_start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exp_start)
{
    ui->setupUi(this);

    setWindowTitle("Начало");
}

void exp_start::init(int n)
{
    this->n = n;
    ui->verticalLayout_2->addWidget(new QLabel("Выберите вещи, нужные для эксперимента"));
    for(int i = 0; i < n; i++)
    {
        ui->verticalLayout_2->addWidget(new QCheckBox(QString::number(i + 1)));
    }
}

QList<bool> exp_start::get_res()
{
    QList<bool> res;
    for (int i = 0; i < n; i++)
    {
        res.append(qobject_cast<QCheckBox*>(ui->verticalLayout_2->itemAt(i + 1)->widget())->isChecked());
    }
    return  res;
}

exp_start::~exp_start()
{
    delete ui;
}

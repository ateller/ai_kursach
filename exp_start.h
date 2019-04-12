#ifndef EXP_START_H
#define EXP_START_H

#include <QDialog>
#include <QCheckBox>
#include <QString>
#include <QLabel>

namespace Ui {
class exp_start;
}

class exp_start : public QDialog
{
    Q_OBJECT

public:
    explicit exp_start(QWidget *parent = nullptr);
    void init(int n);
    QList <bool> get_res();
    ~exp_start();

private:
    int n;
    Ui::exp_start *ui;
};

#endif // EXP_START_H

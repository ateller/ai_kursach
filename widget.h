#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <target.h>
#include <exp_start.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    bool is_closed;

private:
    Ui::Widget *ui;
    QList <target*> targets;
    QList <robot*> robots;
public slots:
    void action();

    void paintEvent(QPaintEvent *event);
};

#endif // WIDGET_H

#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), SLOT(action()));

    targets.append(new target(100, 100));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::action()
{
    repaint();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter P;
    P.begin(this);
    P.setPen(QPen(Qt::black,1));
    P.drawLine(500,0,500,240);
    P.drawLine(500,260,500,500);
    foreach (target* t, targets)
    {
        t->show(this);
    }
    P.end();
}

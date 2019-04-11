#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), SLOT(action()));

    targets.append(new target(300, 100));
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
    P.setPen(QPen(Qt::black,2));
    P.setRenderHint(QPainter::Antialiasing, true);

    P.save();
    //Готовимся рисовать хумана

    P.drawEllipse(50,50,20,20);
    //Голова
    P.translate(56,77);
    P.rotate(-45);
    P.drawEllipse(0,0,20,45);
    //Туловище
    P.drawEllipse(5,45,12,35);
    //Правая нога
    P.restore();

    P.save();
    P.rotate(10);
    P.drawEllipse(100,86,12,35);
    P.restore();
    //Левая нога

    P.save();
    P.translate(40,97);
    P.rotate(-55);
    P.drawEllipse(0,0,30,10);
    P.restore();
    //Левое плечо

    P.save();
    P.translate(25,74);
    P.rotate(45);
    P.drawEllipse(0,0,30,10);
    P.restore();
    //Левое предплечье

    P.drawEllipse(12,73,10,7);
    //Левая кисть

    P.drawLine(10,10,10,500);
    P.drawLine(990,10,990,500);
    //Вертикальные по краям
    P.drawLine(10,10,490,10);
    P.drawLine(510,10,990,10);
    //Горизонтальные сверху
    P.drawLine(490,10,500,180);
    P.drawLine(510,10,500,180);
    //Косые сверху
    P.drawLine(500,180,500,230);
    P.drawLine(500,270,500,320);
    //Вертикальные в середине
    P.drawLine(490,500,500,320);
    P.drawLine(510,500,500,320);
    //Косые снизу
    P.drawLine(10,500,490,500);
    P.drawLine(510,500,990,500);
    //Горизонтальные снизу

    //P.draw

    foreach (target* t, targets)
    {
        t->show(this);
    }
    foreach (robot* r, robots)
    {
        r->act();
        r->show(this);
    }
    P.end();
}

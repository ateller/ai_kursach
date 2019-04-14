#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), SLOT(action()));
    setWindowTitle("SKYBAL");

    targets.append(new target(300, 190));
    targets.append(new target(450, 130));
    targets.append(new target(250, 330));
    targets.append(new target(400, 420));

    targets.append(new target(650, 320));
    targets.append(new target(550, 450));
    targets.append(new target(700, 70));
    targets.append(new target(800, 250));
    targets.append(new target(900, 290));

    exp_start* e = new exp_start;
    e->init(targets.size());
    e->show();
    e->exec();
    is_closed = !e->result();
    QList<bool> checks = e->get_res();

    QList<target*> experiment;
    QList<bool>::iterator b = checks.begin();
    QList<target*>::iterator t = targets.begin();

    for(;b != checks.end(); b++, t++)
    {
        if(*b)
        {
            experiment.append(*t);
        }
    }

    targets.append(new tablet(259, 148));
    experiment.append(targets.back());

    robots.append(new robot(200, 400, nullptr, GATE_X + 15, GATE_Y, GATE_X - 15, GATE_Y));
    robots.append(new robot(600, 400, robots.back(), GATE_X + 15, GATE_Y, GATE_X - 15, GATE_Y));

    foreach(robot* temp, robots)
    {
        temp->start_experiment(experiment);
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::action()
{
    foreach (robot* r, robots)
    {
        r->act();
    }
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
    P.translate(42,93);
    P.rotate(-55);
    P.drawEllipse(0,0,25,10);
    P.restore();
    //Левое плечо

    P.save();
    P.translate(25,74);
    P.rotate(42);
    P.drawEllipse(0,0,30,10);
    P.restore();
    //Левое предплечье

    P.drawEllipse(12,73,10,7);
    //Левая кисть

    P.save();
    P.translate(77,64);
    P.rotate(10);
    P.drawEllipse(0,0,25,10);
    P.restore();
    //Правое плечо

    P.save();
    P.translate(106,72);
    P.rotate(60);
    P.drawEllipse(0,0,30,10);
    P.restore();
    //Правое предплечье

    P.drawEllipse(116,98,10,7);
    //Правая кисть

    P.save();
    P.translate(86,133);
    P.rotate(20);
    P.drawEllipse(0,0,30,10);
    P.restore();
    //Левая нижняя нога

    P.drawEllipse(111,147,7,10);
    //Левая стопа

    P.save();
    P.translate(120,122);
    P.rotate(-5);
    P.drawEllipse(0,0,30,10);
    P.restore();
    //Правая нижняя нога

    P.save();
    P.translate(149,126);
    P.rotate(-50);
    P.drawEllipse(0,0,7,10);
    P.restore();
    //Правая стопа

    P.drawLine(10,10,10,500);
    P.drawLine(990,10,990,500);
    //Вертикальные по краям
    P.drawLine(10,10,490,10);
    P.drawLine(510,10,990,10);
    //Горизонтальные сверху
    P.drawLine(490,10,500,140);
    P.drawLine(510,10,500,140);
    //Косые сверху
    P.drawLine(500,140,500,200);
    P.drawLine(500,300,500,360);
    //Вертикальные в середине
    P.drawLine(490,500,500,360);
    P.drawLine(510,500,500,360);
    //Косые снизу
    P.drawLine(10,500,490,500);
    P.drawLine(510,500,990,500);
    //Горизонтальные снизу

    foreach (target* t, targets)
    {
        t->show(this);
    }
    foreach (robot* r, robots)
    {
        r->show(this);
    }
    P.end();
}

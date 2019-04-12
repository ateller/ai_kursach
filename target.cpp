#include "target.h"

target::target()
{
    this->radius = TARGET_R;
}

target::target(int x, int y)
{
    this->x = x;
    this->y = y;
    this->radius = TARGET_R;
    if(x > 500) room = 2;
    else room = 1;
}

void target::show(QPaintDevice *d)
{
    QPainter p;
    p.begin(d);
    p.setPen(QPen(Qt::black,2));
    p.drawEllipse(x, y, radius, radius);
    p.end();
}

int target::get_room()
{
    return  room;
}

robot::robot(int x, int y, robot* companion)
{
    this->x = x;
    this->y = y;
    this->radius = ROBOT_R;
    this->companion = companion;
    status = SEARCHING;
}

void robot::act()
{
    switch (status) {
    case MOVING:
        break;
    case SEARCHING:
        break;
    case WAITING:
        break;
    case FINISHED:
        break;
    }
}


tablet::tablet(int x, int y) : target(x, y)
{

}

void tablet::show(QPaintDevice* d)
{
    QPainter p;
    p.begin(d);
    p.setPen(QPen(Qt::black,2));
    p.drawRect(x, y, TAB_W, TAB_H);
    p.end();
}

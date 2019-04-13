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
    if(x > 500) room = 1;
    else room = 0;
}

void target::move(int dx, int dy)
{
    x+=dx;
    y+=dy;
}

void target::show(QPaintDevice *d)
{
    QPainter p;
    p.begin(d);
    p.setPen(QPen(Qt::black,2));
    p.drawEllipse(x - radius/2, y - radius/2, radius, radius);
    p.end();
}

int target::get_room()
{
    return  room;
}

int target::get_x()
{
    return x;
}

int target::get_y()
{
    return y;
}

void target::teleport(int x, int y)
{
    this->x = x;
    this->y = y;
}

int target::dist(int tx, int ty, int troom)
{
    int d = static_cast<int>(sqrt(((x-tx)*(x-tx))+((y-ty)*(y-ty))));
    if (troom != room) d+=10000 * (ROOMS_COUNT - room);
    return d;
}

robot::robot(int x, int y, robot* companion, int gate_1_x, int gate_1_y, int gate_2_x, int gate_2_y)
{
    this->x = x;
    this->y = y;
    this->gate_1_x = gate_1_x;
    this->gate_1_y = gate_1_y;
    this->gate_2_x = gate_2_x;
    this->gate_2_y = gate_2_y;
    this->radius = ROBOT_R;
    this->companion = companion;
    status = SEARCHING;
    if(x > 500) room = 1;
    else room = 0;
}

void robot::wake_up(QList<target *> take)
{
    foreach(target* t, take)
    {
        grab(t);
        targets.removeOne(t);
    }
    status = SEARCHING;
}

bool robot::r_u_here()
{
    if((status == WAITING) && (room < next->get_room()))
        return true;
    else
        return false;
}

void robot::act()
{
    switch (status) {
    case TO_GATE:
    case TO_HUMAN:
    case TO_TARGET:
        move();
        break;
    case SEARCHING:
        select();
        break;
    case WAITING:
        wait();
        break;
    case FINISHED:
        break;
    }
}

void robot::start_experiment(QList<target*> targets)
{
    this->targets += targets;
}

void robot::grab(target *t)
{
    t->teleport(x + static_cast<int>(15*cos(((cargo.size()-4)*M_PI)/6)), y + static_cast<int>(15*sin(((cargo.size()-4)*M_PI)/6)));
    cargo.append(t);
}

void robot::select()
{
    if(targets.isEmpty() == true)
    {
        decision(nullptr);
        return;
    }
    int i = 0, min_i = 0;
    int min = INT_MAX;
    foreach(target* temp, targets)
    {
        int d = temp->dist(x, y, room);
        if(d < min)
        {
            min_i = i;
            min = d;
        }
        i++;
    }

    if (targets[min_i]->get_room() == room)
    {
        decision(targets[min_i]);
        targets.removeAt(min_i);
    }
    else {
        decision(targets[min_i]);
    }
}

void robot::go_to(int d_x, int d_y)
{
    dest_x = d_x;
    dest_y = d_y;
    f_x = static_cast<double>(x);
    f_y = static_cast<double>(y);
    int dx = dest_x - x;
    int dy = dest_y - y;
    double g = sqrt((dy)*(dy) + (dx)*(dx));
    speed_x = (dx/g) * SPEED;
    speed_y = (dy/g) * SPEED;
}

void robot::decision(target *t)
{
    if(t == nullptr)
    {
        next = nullptr;
        if(cargo.isEmpty() == true)
        {
            status = FINISHED;
        }
        else {
            if(companion == nullptr)
            {
                go_to(HUMAN_X, HUMAN_Y);
                status = TO_HUMAN;
            }
            else {
                go_to(gate_1_x, gate_1_y);
                status = TO_GATE;
            }
        }
    }
    else {
        next = t;
        if(t->get_room() == room)
        {
            go_to(t->get_x(),t->get_y());
            status = TO_TARGET;
        }
        else
        {
            if(t->get_room() < room)
            {
                if(cargo.isEmpty() == true)
                {
                    status = FINISHED;
                }
                else {
                    go_to(gate_1_x, gate_1_y);
                    status = TO_GATE;
                }
            }
            else {
                go_to(gate_2_x, gate_2_y);
                status = TO_GATE;
            }
        }
    }
}

void robot::move()
{
    if((abs(x - dest_x) <= abs(static_cast<int>(speed_x+0.5)))&&(abs(y - dest_y) <= abs(static_cast<int>(speed_y+0.5))))
    {
        foreach(target* temp, cargo)
        {
            temp->move(dest_x - x, dest_y - y);
        }
        teleport(dest_x, dest_y);
        if(status == TO_TARGET)
        {
            grab(next);
            status = SEARCHING;
        }
        else
        {
            if(status == TO_GATE)
                status = WAITING;
            else {
                show_tabl();
                status = FINISHED;
            }
        }
        return;
    }
    int dx, dy;
    f_x+=speed_x;
    f_y+=speed_y;
    dx = static_cast<int>(f_x - x);
    dy = static_cast<int>(f_y - y);
    x+= dx;
    y+= dy;
    foreach(target* temp, cargo)
    {
        temp->move(dx, dy);
    }
}

void robot::show_tabl()
{
    foreach (target* t, cargo)
    {
        if(qobject_cast<tablet*>(t) != nullptr)
        {
            t->teleport(x - 15, y);
        }
    }
}

void robot::wait()
{
    if(next != nullptr)
        if(next->get_room() > room)
            return;
    if(companion->r_u_here() == true)
    {
        companion->wake_up(cargo);
        cargo.clear();
        targets.clear();
        status = FINISHED;
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
    p.drawRect(x - TAB_W/2, y - TAB_H/2, TAB_W, TAB_H);
    p.end();
}

#ifndef TARGET_H
#define TARGET_H

#include <QObject>
#include <QPainter>
#include <QList>
#include <math.h>

#define TARGET_R 6
#define ROBOT_R 10
#define SPEED 1
#define TAB_W 6
#define TAB_H 12
#define GATE_X 500
#define GATE_Y 250
#define HUMAN_X 50
#define HUMAN_Y 150
#define ROOMS_COUNT 2

class target : public QObject
{
    Q_OBJECT
public:
    target();
    target(int x, int y);
    void move(int dx, int dy);
    virtual void show(QPaintDevice*);
    int get_room();
    int get_x();
    int get_y();
    void teleport(int x, int y);
    int dist(int tx, int ty, int troom);
protected:
    int x, y, radius, room;
signals:

public slots:
};

#define TO_TARGET 1
#define TO_GATE 2
#define TO_HUMAN 3
#define SEARCHING 4
#define WAITING 5
#define FINISHED 6

class robot : public target
{
    Q_OBJECT
public:
    robot(int x, int y, robot* companion);
    void wake_up();
    void act();
    void start_experiment(QList<target *> targets);
    void grab(target*);
private:
    int status;
    target* next;
    QList <target*> targets;
    QList <target*> cargo;
    int distance(target*);
    void select();
    void go_to(int d_x, int d_y);
    void decision(target* t);
    void move();
    void show_tabl();

    double f_x, f_y, speed_x, speed_y;
    int dest_x, dest_y;
    robot* companion;
};

class tablet : public target
{
    Q_OBJECT
public:
    tablet(int x, int y);
    void show(QPaintDevice*);
};

#endif // TARGET_H

#ifndef TARGET_H
#define TARGET_H

#include <QObject>
#include <QPainter>
#include <QList>
#include <math.h>

#define TARGET_R 5
#define ROBOT_R 10
#define SPEED 2
#define TAB_W 5
#define TAB_H 10
#define GATE_X 500
#define GATE_Y 250
#define HUMAN_X 50
#define HUMAN_Y 150

class target : public QObject
{
    Q_OBJECT
public:
    target();
    target(int x, int y);
    void move(int dx, int dy);
    void show(QPaintDevice*);
    int get_room();
    int get_x();
    int get_y();
protected:
    int x, y, radius;
private:
    int room;
signals:

public slots:
};

#define MOVING 1;
#define SEARCHING 2;
#define WAITING 3;
#define FINISHED 4;

class robot : public target
{
public:
    robot(int x, int y, robot* companion);
    void wake_up();
    void act();
    void start_experiment(QList <target> targets);

private:
    int status;
    QList <target*> targets;
    QList <target*> cargo;
    int distance(target*);
    double f_x, f_y, speed_x, speed_y;
    int dest_x, dest_y;
    robot* companion;
};

class tablet : public target
{
public:
    tablet(int x, int y);
    void show(QPaintDevice*);
};

#endif // TARGET_H

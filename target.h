#ifndef TARGET_H
#define TARGET_H

#include <QObject>
#include <QPainter>
#include <QList>
#include <math.h>

#define TARGET_R 5
#define ROBOT_R 10
#define SPEED 2;

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
    robot(int x, int y, robot* companion);
private:
    int status;
    QList <target*> targets;
    QList <target*> cargo;
    int distance(target*);
    double rest_x, rest_y, speed_x, speed_y;
    robot* companion;
public:
    void wake_up();
    void act();
    void start_experiment(QList <target> targets);
};

#endif // TARGET_H

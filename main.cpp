#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    if(!w.is_closed)
    {
        w.show();
        return a.exec();
    }
    else {
        return 0;
    }

}

#include <QApplication>
#include <QDebug>

#include "widget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w;
    w.show();

    qDebug() << "Debug message";

    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.resize(800,500);//主窗口
    w.show();//主窗口显示

    return a.exec();
}

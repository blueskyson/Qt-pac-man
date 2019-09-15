#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.setStyleSheet("QMainWindow {background: 'black';}");
    window.show();

    return a.exec();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QKeyEvent>
#include <QString>
#include <QObject>
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include "QThread"
#include "item.h"

#define _width 20       //width of items
#define _xborder 30     //(x of qgraphicsview) - 20
#define _yborder 30     //(y of qgraphicsview) - 20
#define _slptime 5000   //moving sleep time

/*item move direction*/
#define _up 0
#define _down 1
#define _left 2
#define _right 3
#define _stop 4

/*ghost color*/
#define _red 0
#define _yellow 1
#define _pink 2
#define _green 3

/*ghost state*/
#define _normal 0
#define _blue 1
#define _run 2

/*declare shared resource*/
extern char map[22][31]; //20,29
extern QGraphicsPixmapItem *block[22][31];
extern QGraphicsScene *scene;
extern int dot_num, eat_sum, totalscore, gatex, gatey, pball_num;
extern QLabel *score_title, *score, *win_label, *lose_label;
extern QString eat_str;
extern Item *pac, *ghost[4];
extern QVector<QGraphicsPixmapItem*> pball;
extern bool islose, iswin;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void set_board();
    void chase(int);
    void escape(int);
    void run(int);
    ~MainWindow() override;

private slots:
    void ghostmv();
    void powerball_flash();

private:
    Ui::MainWindow *ui;  
    QTimer *timer, *flash;
    bool flashtik;
protected:
    void keyPressEvent(QKeyEvent *event) override;
};


#endif // MAINWINDOW_H

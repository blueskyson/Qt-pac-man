#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include"item.h"
class GhostBegin : public QThread {
public:
    void run();
    void setisinbox(bool b){isinbox = b;}
    bool getisinbox(){return isinbox;}
private:
    bool isinbox;
    Item *ghost[4];
};

class GhostControl : public QThread {
public:
    void run();
};

#endif // THREAD_H

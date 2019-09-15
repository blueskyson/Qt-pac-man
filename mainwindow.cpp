#include "mainwindow.h"
#include "item.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("pac-man"));
    ui->graphicsView->setStyleSheet("QGraphicsView {border: none;}");
    ui->graphicsView->setBackgroundBrush(Qt::black);
    scene = new QGraphicsScene(50, 50, ui->graphicsView->width() - 2, ui->graphicsView->height() - 2);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);
    ui->graphicsView->setScene(scene);
    set_board();
    timer = new QTimer(this);
    flash = new QTimer(this);
    timer->start(6);
    flash->start(200);
    connect(timer,SIGNAL(timeout()),this,SLOT(ghostmv()));
    connect(flash,SIGNAL(timeout()),this,SLOT(powerball_flash()));
}

void MainWindow::ghostmv() {
    if(islose) {
        timer->stop();
        flash->stop();
        QCoreApplication::processEvents();
        QThread::sleep(1);
        lose_label->show();
        return;
    }
    if(iswin) {
        timer->stop();
        for(int i=0;i<4;++i) {
            delete ghost[i];
        }
        return;
    }
    for(int i=0;i<4;++i) {
        switch(ghost[i]->get_dir()) {
        case _left:
            ghost[i]->moveleft();
            break;
        case _right:
            ghost[i]->moveright();
            break;
        case _up:
            ghost[i]->moveup();
            break;
        case _down:
            ghost[i]->movedown();
            break;
        case _stop:
            if(ghost[i]->isinbox()) {
                if(ghost[i]->state == _run) {
                    run(i);
                    break;
                }
                int disx, disy;
                disx = gatex - ghost[i]->get_px();
                disy = gatey - ghost[i]->get_py();  
                if(disx==0 && disy==0) {
                    ghost[i]->setinbox(false);
                    ghost[i]->set_dir(ghost[i]->get_lastdir());
                    switch(ghost[i]->get_lastdir()) {
                    case _left:
                        ghost[i]->moveleft();
                        break;
                    case _right:
                        ghost[i]->moveright();
                        break;
                    case _up:
                        ghost[i]->moveup();
                        break;
                    case _down:
                        ghost[i]->movedown();
                        break;
                    }
                    return;
                }

                if(disx>0) {
                    ghost[i]->set_dir(_right);
                } else if(disx<0) {
                    ghost[i]->set_dir(_left);
                } else if(disx == 0) {
                    if(disy > 0)
                        ghost[i]->set_dir(_down);
                    else
                        ghost[i]->set_dir(_up);
                }
            }
            else {
                if(ghost[i]->begintik) {
                    ghost[i]->begintik--;
                    if(ghost[i]->begintik==0)
                        ghost[i]->setinbox(true);
                }
                switch(ghost[i]->state) {
                case _normal:
                    chase(i);
                    break;
                case _blue:
                    ghost[i]->bluetik--;
                    if(ghost[i]->bluetik%5 == 0) {
                        if(ghost[i]->bluetik == 0) {
                            ghost[i]->state = _normal;
                        }
                        escape(i);
                    }
                    break;
                }
            }
            break;
        }
    }
}

void MainWindow::powerball_flash() {
    if(pball.empty()) {
        flash->stop();
        return;
    }
    if(flashtik) {
        for(int i=0;i<pball.size();++i)
            pball.at(i)->hide();
        flashtik=0;
    } else {
        for(int i=0;i<pball.size();++i)
            pball.at(i)->show();
        flashtik=1;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(islose){
        return;
    }
    if(event->key() == Qt::Key_W){      //w
        switch(pac->get_dir()) {
        case _down: case _stop:
            pac->set_nextdir(_stop);
            pac->set_changept(-1);
            pac->moveup();
            break;
        case _left:
            if(pac->get_py()>0) {
                int nowx = pac->get_px() - 1, nowy = pac->get_py();
                while(map[nowy][nowx] == '0') {
                    if(map[nowy-1][nowx] == '0') {
                        pac->set_nextdir(_up);
                        pac->set_changept(nowx);
                        break;                 
                    }
                    --nowx;
                }
            }
            break;
        case _right:
            if(pac->get_py()>0) {
                int nowx = pac->get_px() + 1, nowy = pac->get_py();
                while(map[nowy][nowx] == '0') {
                    if(map[nowy-1][nowx] == '0') {
                        pac->set_nextdir(_up);
                        pac->set_changept(nowx);
                        break;
                    }
                    ++nowx;
                }
            }
            break;
        }
    }

    else if(event->key() == Qt::Key_A){     //a
        switch(pac->get_dir()) {
        case _right: case _stop:
            pac->set_nextdir(_stop);
            pac->set_changept(-1);
            pac->moveleft();
            break;
        case _up:
            if(pac->get_px()>0) {
                int nowx = pac->get_px(), nowy = pac->get_py() - 1;
                while(map[nowy][nowx] == '0') {
                    if(map[nowy][nowx-1] == '0') {
                        pac->set_nextdir(_left);
                        pac->set_changept(nowy);
                        break;
                    }
                    --nowy;
                }
            }
            break;
        case _down:
            if(pac->get_px()>0) {
                int nowx = pac->get_px(), nowy = pac->get_py() + 1;
                while(map[nowy][nowx] == '0') {
                    if(map[nowy][nowx-1] == '0') {
                        pac->set_nextdir(_left);
                        pac->set_changept(nowy);
                        break;
                    }
                    ++nowy;
                }
            }
            break;
        }
    }
    else if(event->key() == Qt::Key_S){     //s
        switch(pac->get_dir()) {
        case _up: case _stop:
            pac->set_nextdir(_stop);
            pac->set_changept(-1);
            pac->movedown();
            break;
        case _left:
            if(pac->get_py()<21) {
                int nowx = pac->get_px() - 1, nowy = pac->get_py();
                while(map[nowy][nowx] == '0') {
                    if(map[nowy+1][nowx] == '0') {
                        pac->set_nextdir(_down);
                        pac->set_changept(nowx);
                        break;
                    }
                    --nowx;
                }
            }
            break;
        case _right:
            if(pac->get_py()<21) {
                int nowx = pac->get_px() + 1, nowy = pac->get_py();
                while(map[nowy][nowx] == '0') {
                    if(map[nowy+1][nowx] == '0') {
                        pac->set_nextdir(_down);
                        pac->set_changept(nowx);
                        break;
                    }
                    ++nowx;
                }
            }
            break;
        }
    }
    else if(event->key() == Qt::Key_D){         //d
        switch(pac->get_dir()) {
        case _left: case _stop:
            pac->moveright();
            break;
        case _up:
            if(pac->get_px()<30) {
                int nowx = pac->get_px(), nowy = pac->get_py() - 1;
                while(map[nowy][nowx] == '0') {
                    if(map[nowy][nowx+1] == '0') {
                        pac->set_nextdir(_right);
                        pac->set_changept(nowy);
                        break;
                    }
                    --nowy;
                }
            }
            break;
        case _down:
            if(pac->get_px()<30) {
                int nowx = pac->get_px(), nowy = pac->get_py() + 1;
                while(map[nowy][nowx] == '0') {
                    if(map[nowy][nowx+1] == '0') {
                        pac->set_nextdir(_right);
                        pac->set_changept(nowy);
                        break;
                    }
                    ++nowy;
                }
            }
            break;
        }       
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

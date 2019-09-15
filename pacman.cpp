#include "mainwindow.h"

void Item::moveup(){}; //out of line definition

Pacman::Pacman(int j, int i):px(j),py(i),dir(0) {
    dir = _stop;
    nextdir = _stop;
    changept = -1;
    setPixmap(QPixmap(":/rsc/a1.png"));
    for(int i=0;i<4;++i) {
        for(int j=0;j<10;++j)
            anim[i][j] = new animation;
    }

    anim[_right][0]->img.load(":/rsc/a1.png");
    anim[_right][1]->img.load(":/rsc/a2.png");
    anim[_right][2]->img.load(":/rsc/a3.png");
    anim[_right][3]->img.load(":/rsc/a4.png");
    anim[_right][4]->img.load(":/rsc/a5.png");
    anim[_right][5]->img.load(":/rsc/a6.png");
    anim[_right][6]->img.load(":/rsc/a5.png");
    anim[_right][7]->img.load(":/rsc/a4.png");
    anim[_right][8]->img.load(":/rsc/a3.png");
    anim[_right][9]->img.load(":/rsc/a2.png");
    anindex[_right] = anim[_right][0];

    anim[_up][0]->img.load(":/rsc/a1.png");
    anim[_up][1]->img.load(":/rsc/b2.png");
    anim[_up][2]->img.load(":/rsc/b3.png");
    anim[_up][3]->img.load(":/rsc/b4.png");
    anim[_up][4]->img.load(":/rsc/b5.png");
    anim[_up][5]->img.load(":/rsc/b6.png");
    anim[_up][6]->img.load(":/rsc/b5.png");
    anim[_up][7]->img.load(":/rsc/b4.png");
    anim[_up][8]->img.load(":/rsc/b3.png");
    anim[_up][9]->img.load(":/rsc/b2.png");
    anindex[_up] = anim[_up][0];

    anim[_left][0]->img.load(":/rsc/a1.png");
    anim[_left][1]->img.load(":/rsc/c2.png");
    anim[_left][2]->img.load(":/rsc/c3.png");
    anim[_left][3]->img.load(":/rsc/c4.png");
    anim[_left][4]->img.load(":/rsc/c5.png");
    anim[_left][5]->img.load(":/rsc/c6.png");
    anim[_left][6]->img.load(":/rsc/c5.png");
    anim[_left][7]->img.load(":/rsc/c4.png");
    anim[_left][8]->img.load(":/rsc/c3.png");
    anim[_left][9]->img.load(":/rsc/c2.png");
    anindex[_left] = anim[_left][0];

    anim[_down][0]->img.load(":/rsc/a1.png");
    anim[_down][1]->img.load(":/rsc/d2.png");
    anim[_down][2]->img.load(":/rsc/d3.png");
    anim[_down][3]->img.load(":/rsc/d4.png");
    anim[_down][4]->img.load(":/rsc/d5.png");
    anim[_down][5]->img.load(":/rsc/d6.png");
    anim[_down][6]->img.load(":/rsc/d5.png");
    anim[_down][7]->img.load(":/rsc/d4.png");
    anim[_down][8]->img.load(":/rsc/d3.png");
    anim[_down][9]->img.load(":/rsc/d2.png");
    anindex[_down] = anim[_down][0];

    for(int i=0;i<9;++i) {
        anim[_right][i]->next = anim[_right][i+1];
        anim[_up][i]->next = anim[_up][i+1];
        anim[_left][i]->next = anim[_left][i+1];
        anim[_down][i]->next = anim[_down][i+1];
    }
    anim[_right][9]->next = anim[_right][0];
    anim[_up][9]->next = anim[_up][0];
    anim[_left][9]->next = anim[_left][0];
    anim[_down][9]->next = anim[_down][0];    
}

void Pacman::moveup(){
    int posy = static_cast<int>(this->y());
    int remender = (posy-_yborder)%_width;
    py = (posy-_yborder)/_width;
    dir = _up;
    while(remender){            //adjust coordinate
        this->setPixmap(anindex[_up]->img);
        anindex[_up]=anindex[_up]->next;
        this->setY(--posy);      
        --remender;
        QCoreApplication::processEvents();
        QThread::usleep(_slptime);
        if(dir!=_up)
            return;
        if(islose) {
            return;
        }
    }

    if(block[py][px]) {
        if(addscore())
            return;
    }
    if(py == changept) {        //changedir
        check_dirchange();
        return;
    }

    while(py>0 && map[py-1][px] == '0'){
        for(int i=0; i<_width; ++i) {
            this->setPixmap(anindex[_up]->img);
            anindex[_up]=anindex[_up]->next;
            this->setY(--posy);
            QCoreApplication::processEvents();
            QThread::usleep(_slptime);
            if(dir != _up)
                return;
            if(islose) {
                return;
            }
        }
        --py;

        if(block[py][px]) {
            if(addscore())
                return;
        }
        if(py == changept) {        //changedir
            check_dirchange();
            return;
        }
    }
    dir = _stop;
}

void Pacman::movedown() {    
    posy = static_cast<int>(this->y());
    int remender = _width - (posy-_yborder)%_width;
    py = (posy-_yborder)/_width;
    if(remender == _width && map[py+1][px] == '1')
        return;
    dir = _down;
    while(remender){           //adjust coordinate
        this->setPixmap(anindex[_down]->img);
        anindex[_down]=anindex[_down]->next;
        this->setY(++posy);
        --remender;
        QCoreApplication::processEvents();
        QThread::usleep(_slptime);
        if(dir!=_down)
            return;
        if(islose) {
            return;
        }
    }
    ++py;

    if(block[py][px]) {
        if(addscore())
            return;
    }
    if(py == changept) {        //changedir
        check_dirchange();
        return;
    }

    while(py<21 && map[py+1][px] == '0'){
        for(int i=0; i<_width; ++i) {
            this->setPixmap(anindex[_down]->img);
            anindex[_down]=anindex[_down]->next;
            this->setY(++posy);
            QCoreApplication::processEvents();
            QThread::usleep(_slptime);
            if(dir!=_down)
                return;
            if(islose) {
                return;
            }
        }
        ++py;

        if(block[py][px]) {
            if(addscore())
                return;
        }
        if(py == changept) {        //changedir
            check_dirchange();
            return;
        }
    }
    dir = _stop;
}

void Pacman::moveleft() {   
    posx = static_cast<int>(this->x());
    int remender = (posx-_xborder)%_width;
    dir = _left;
    while(remender){            //adjust coordinate
        this->setPixmap(anindex[_left]->img);
        anindex[_left]=anindex[_left]->next;
        this->setX(--posx);
        --remender;
        QCoreApplication::processEvents();
        QThread::usleep(_slptime);
        if(dir!=_left)
            return;
        if(islose) {
            return;
        }
    }

    if(block[py][px]) {
        if(addscore())
            return;
    }
    if(px == changept) {        //changedir
        check_dirchange();
        return;
    }

    while(py>0 && map[py][px-1] == '0'){        
        for(int i=0; i<_width; ++i) {
            this->setPixmap(anindex[_left]->img);
            anindex[_left]=anindex[_left]->next;
            this->setX(--posx);
            QCoreApplication::processEvents();
            QThread::usleep(_slptime);
            if(dir != _left)
                return;
            if(islose) {
                return;
            }
        }
        --px;
        if(block[py][px]) {
            if(addscore())
                return;
        }
        if(px == changept) {        //changedir
            check_dirchange();
            return;
        }
    }
    dir = _stop;
}

void Pacman::moveright() {   
    posx = static_cast<int>(this->x());
    int remender = _width - (posx-_xborder)%_width;
    px = (posx-_xborder)/_width;
    if(remender == _width && map[py][px+1] == '1')
        return;
    dir = _right;
    while(remender){
        this->setPixmap(anindex[_right]->img);
        anindex[_right]=anindex[_right]->next;
        this->setX(++posx);
        --remender;
        QCoreApplication::processEvents();
        QThread::usleep(_slptime);
        if(dir!=_right)
            return;
        if(islose) {
            return;
        }
    }
    ++px;
    if(block[py][px]) {
        if(addscore())
            return;
    }
    if(px == changept) {        //changedir
        check_dirchange();
        return;
    }

    while(px<30 && map[py][px+1] == '0'){
        for(int i=0; i<_width; ++i) {
            this->setPixmap(anindex[_right]->img);
            anindex[_right]=anindex[_right]->next;
            this->setX(++posx);
            QCoreApplication::processEvents();
            QThread::usleep(_slptime);
            if(dir != _right)
                return;
            if(islose) {
                return;
            }
        }
        ++px;
        if(block[py][px]) {
            if(addscore())
                return;
        }
        if(px == changept) {        //changedir
            check_dirchange();
            return;
        }
    }
    dir = _stop;
}

void Pacman::check_dirchange() {
    changept = -1;
    int tmp = nextdir;
    nextdir = _stop;
    switch(tmp) {
    case _up:
        moveup();
        break;
    case _down:
        movedown();
        break;
    case _left:
        moveleft();
        break;
    case _right:
        moveright();
        break;
    }
}

int Pacman::addscore() {
    if(py == gatey && px == gatex) {
        return 0;
    }
    eat_sum++;
    totalscore+=10;
    score->setText(QString::number(totalscore));
    for(int i=0;i<pball.size();++i) {
        if(block[py][px] == pball.at(i)) {
            pball.remove(i);
            for(int j=0; j<4 ;++j) {
                if(ghost[j]->state == _normal) {
                     ghost[j]->state = _blue;
                }
                ghost[j]->bluetik = 300;
            }
        }
    }
    delete block[py][px];
    block[py][px] = nullptr;
    if(eat_sum == dot_num) {
        win_label->show();
        iswin=true;
        dir = _stop;
        return 1;
    }
    else {
        return 0;
    }
}

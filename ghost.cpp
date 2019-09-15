#include "item.h"
#include "mainwindow.h"

Ghost::Ghost(int j, int i, int c):px(j),py(i),color(c){
    setZValue(3);
    dir = _stop;
    nextdir = _stop;
    lastdir = _down;
    changept = -1;
    inbox = false;
    anim[4][0].load(":/rsc2/bl1.png");
    anim[4][1].load(":/rsc2/bl2.png");
    switch(color) {
        case _red:
        setPixmap(QPixmap(":/rsc2/redright1.png"));
        anim[_right][0].load(":/rsc2/redright1.png");
        anim[_right][1].load(":/rsc2/redright2.png");
        anim[_up][0].load(":/rsc2/redup1.png");
        anim[_up][1].load(":/rsc2/redup2.png");
        anim[_left][0].load(":/rsc2/redleft1.png");
        anim[_left][1].load(":/rsc2/redleft2.png");
        anim[_down][0].load(":/rsc2/reddown1.png");
        anim[_down][1].load(":/rsc2/reddown2.png");
        break;
    case _yellow:
        setPixmap(QPixmap(":/rsc2/yellowright1.png"));
        anim[_right][0].load(":/rsc2/yellowright1.png");
        anim[_right][1].load(":/rsc2/yellowright2.png");
        anim[_up][0].load(":/rsc2/yellowup1.png");
        anim[_up][1].load(":/rsc2/yellowup2.png");
        anim[_left][0].load(":/rsc2/yellowleft1.png");
        anim[_left][1].load(":/rsc2/yellowleft2.png");
        anim[_down][0].load(":/rsc2/yellowdown1.png");
        anim[_down][1].load(":/rsc2/yellowdown2.png");
        break;
    case _green:
        setPixmap(QPixmap(":/rsc2/greenright1.png"));
        anim[_right][0].load(":/rsc2/greenright1.png");
        anim[_right][1].load(":/rsc2/greenright2.png");
        anim[_up][0].load(":/rsc2/greenup1.png");
        anim[_up][1].load(":/rsc2/greenup2.png");
        anim[_left][0].load(":/rsc2/greenleft1.png");
        anim[_left][1].load(":/rsc2/greenleft2.png");
        anim[_down][0].load(":/rsc2/greendown1.png");
        anim[_down][1].load(":/rsc2/greendown2.png");
        break;
    case _pink:
        setPixmap(QPixmap(":/rsc2/pinkright1.png"));
        anim[_right][0].load(":/rsc2/pinkright1.png");
        anim[_right][1].load(":/rsc2/pinkright2.png");
        anim[_up][0].load(":/rsc2/pinkup1.png");
        anim[_up][1].load(":/rsc2/pinkup2.png");
        anim[_left][0].load(":/rsc2/pinkleft1.png");
        anim[_left][1].load(":/rsc2/pinkleft2.png");
        anim[_down][0].load(":/rsc2/pinkdown1.png");
        anim[_down][1].load(":/rsc2/pinkdown2.png");
        break;
    }

}

void Ghost::moveup() {
    if(map[py-1][px] == '0' || (inbox == true && map[py-1][px]=='2')) {
        if(state == _normal)
            setPixmap(anim[_up][posy&1]);
        else if(state == _blue)
            setPixmap(anim[4][posy&1]);
        setY(--posy);
        if((static_cast<int>(y())-_yborder)%_width==0) {
            py--;
            dir = _stop;
        }
    } else {
        dir = _stop;
    }
    if(collidesWithItem(pac,Qt::IntersectsItemShape)){
        if(state == _normal)
            islose = true;
        else if(state == _blue) {
            setPixmap(QPixmap(":/rsc2/run.png"));
            totalscore +=200;
            score->setText(QString::number(totalscore));
            inbox = true;
            state = _run;
        }
    }
}

void Ghost::movedown() {
    if(map[py+1][px] == '0' || (inbox == true && map[py+1][px]=='2')) {
        if(state == _normal)
            setPixmap(anim[_down][posy&1]);
        else if(state == _blue)
            setPixmap(anim[4][posy&1]);
        setY(++posy);
        if((static_cast<int>(y())-_yborder)%_width==0) {
            py++;
            dir = _stop;
        }
    } else {
        dir = _stop;
    }
    if(collidesWithItem(pac,Qt::IntersectsItemShape)){
        if(state == _normal)
            islose = true;
        else if(state == _blue) {
            setPixmap(QPixmap(":/rsc2/run.png"));
            totalscore +=200;
            score->setText(QString::number(totalscore));
            inbox = true;
            state = _run;
        }
    }
}

void Ghost::moveleft() {
    if(map[py][px-1] == '0' || (inbox == true && map[py][px-1]=='2')) {
        if(state == _normal)
            setPixmap(anim[_left][posx&1]);
        else if(state == _blue)
            setPixmap(anim[4][posx&1]);
        setX(--posx);
        if((static_cast<int>(x())-_xborder)%_width==0) {
            px--;
            dir = _stop;
        }
    } else {
        dir = _stop;
    }
    if(collidesWithItem(pac,Qt::IntersectsItemShape)){
        if(state == _normal)
            islose = true;
        else if(state == _blue) {
            setPixmap(QPixmap(":/rsc2/run.png"));
            totalscore +=200;
            score->setText(QString::number(totalscore));
            inbox = true;
            state = _run;
        }
    }
}

void Ghost::moveright() {
    if(map[py][px+1] == '0' || (inbox == true && map[py][px+1]=='2')) {
        if(state == _normal)
            setPixmap(anim[_right][posx&1]);
        else if(state == _blue)
            setPixmap(anim[4][posx&1]);
        setX(++posx);
        if((static_cast<int>(x())-_xborder)%_width==0) {
            px++;
            dir = _stop;
        }
    } else {
        dir = _stop;
    }
    if(collidesWithItem(pac,Qt::IntersectsItemShape)){
        if(state == _normal)
            islose = true;
        else if(state == _blue) {
            setPixmap(QPixmap(":/rsc2/run.png"));
            totalscore +=200;
            score->setText(QString::number(totalscore));
            inbox = true;
            state = _run;
        }
    }
}

void Ghost::check_dirchange() {

}

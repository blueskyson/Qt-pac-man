#include "mainwindow.h"
#include "item.h"
void MainWindow::chase(int ind) {
    int disx=0, disy=0, gpx, gpy,oknum=0,lastdir;
    bool okdir[4];
    QVector<int> way;
    gpx = ghost[ind]->get_px();
    gpy = ghost[ind]->get_py();
    okdir[_right] = map[gpy][gpx+1] == '0' ? true:false;
    okdir[_left] = map[gpy][gpx-1] == '0' ? true:false;
    okdir[_up] = map[gpy-1][gpx] == '0' ? true:false;
    okdir[_down] = map[gpy+1][gpx] == '0' ? true:false;
    for(int i=0; i<4; ++i) {
        if(okdir[i]) {
            oknum++;
            way.push_back(i);
        }
    }
    lastdir = ghost[ind]->get_lastdir();
    if(oknum==2) {      //not intersection
        if(okdir[lastdir] == false) {
            switch(ghost[ind]->get_lastdir()) {
            case _left:
                if(way.at(0)==_right)
                    ghost[ind]->set_dir(way.at(1));
                else
                    ghost[ind]->set_dir(way.at(0));
                break;
            case _right:
                if(way.at(0)==_left)
                    ghost[ind]->set_dir(way.at(1));
                else
                    ghost[ind]->set_dir(way.at(0));
                break;
            case _up:
                if(way.at(0)==_down)
                    ghost[ind]->set_dir(way.at(1));
                else
                    ghost[ind]->set_dir(way.at(0));
                break;
            case _down:
                if(way.at(0)==_up)
                    ghost[ind]->set_dir(way.at(1));
                else
                    ghost[ind]->set_dir(way.at(0));
                break;
            }
        } else {
            ghost[ind]->set_dir(ghost[ind]->get_lastdir());
        }
        return;
    }
    switch(ind) {
    case 0:
        disx = pac->get_px() - gpx;
        disy = pac->get_py() - gpy;
        break;
    case 1:
        disx = pac->get_px() - gpx;
        disy = pac->get_py() - gpy;
        switch(pac->get_dir()) {
        case _up:
            disy-=4;
            break;
        case _down:
            disy+=4;
            break;
        case _left:
            disx-=4;
            break;
        case _right:
            disx+=4;
            break;
        }
        break;
    case 2:
        disx = 2*(pac->get_px()) - ghost[0]->get_px() - gpx;
        disy = 2*(pac->get_py()) - ghost[0]->get_py() - gpy;
        break;
    case 3:
        disx = pac->get_px() - gpx;
        disy = pac->get_py() - gpy;
        if(disx*disx + disy*disy < 64) {
            disx = 2 - gpx;
            disy = 2 - gpy;
        }
        break;
    }

    if(disy > 0) {
        if(okdir[_down] && lastdir != _up)
            ghost[ind]->set_dir(_down);
        else {
            if(disx >= 0) {
                if(okdir[_right])
                    ghost[ind]->set_dir(_right);
                else if(okdir[_left])
                    ghost[ind]->set_dir(_left);
            } else if(disx < 0){
                if(okdir[_left])
                    ghost[ind]->set_dir(_left);
                else if(okdir[_right])
                    ghost[ind]->set_dir(_right);
            }
        }
    } else if(disy < 0) {
        if(okdir[_up] && lastdir != _down)
            ghost[ind]->set_dir(_up);
        else {
            if(disx >= 0) {
                if(okdir[_right])
                    ghost[ind]->set_dir(_right);
                else if(okdir[_left])
                    ghost[ind]->set_dir(_left);
            } else if(disx < 0){
                if(okdir[_left])
                    ghost[ind]->set_dir(_left);
                else if(okdir[_right])
                    ghost[ind]->set_dir(_right);
            }
        }
    } else if(disx > 0) {
        if(okdir[_right] && lastdir != _left)
            ghost[ind]->set_dir(_right);
        else {
            if(okdir[_up])
                ghost[ind]->set_dir(_up);
            else if(okdir[_down])
                ghost[ind]->set_dir(_down);
        }
    } else if(disx < 0) {
        if(okdir[_left] && lastdir != _right)
            ghost[ind]->set_dir(_left);
        else {
            if(okdir[_up])
                ghost[ind]->set_dir(_up);
            else if(okdir[_down])
                ghost[ind]->set_dir(_down);
        }
    }
}

void MainWindow::escape(int ind) {
    int disx=0, disy=0, gpx, gpy,oknum=0,lastdir;
    bool okdir[4];
    QVector<int> way;
    gpx = ghost[ind]->get_px();
    gpy = ghost[ind]->get_py();
    okdir[_right] = map[gpy][gpx+1] == '0' ? true:false;
    okdir[_left] = map[gpy][gpx-1] == '0' ? true:false;
    okdir[_up] = map[gpy-1][gpx] == '0' ? true:false;
    okdir[_down] = map[gpy+1][gpx] == '0' ? true:false;
    for(int i=0; i<4; ++i) {
        if(okdir[i]) {
            oknum++;
            way.push_back(i);
        }
    }
    lastdir = ghost[ind]->get_lastdir();
    if(oknum==2) {      //not intersection
        if(okdir[lastdir] == false) {
            switch(ghost[ind]->get_lastdir()) {
            case _left:
                if(way.at(0)==_right)
                    ghost[ind]->set_dir(way.at(1));
                else
                    ghost[ind]->set_dir(way.at(0));
                break;
            case _right:
                if(way.at(0)==_left)
                    ghost[ind]->set_dir(way.at(1));
                else
                    ghost[ind]->set_dir(way.at(0));
                break;
            case _up:
                if(way.at(0)==_down)
                    ghost[ind]->set_dir(way.at(1));
                else
                    ghost[ind]->set_dir(way.at(0));
                break;
            case _down:
                if(way.at(0)==_up)
                    ghost[ind]->set_dir(way.at(1));
                else
                    ghost[ind]->set_dir(way.at(0));
                break;
            }
        } else {
            ghost[ind]->set_dir(ghost[ind]->get_lastdir());
        }
        return;
    }

    disx = pac->get_px() - gpx;
    disy = pac->get_py() - gpy;

    if(disy > 0) {
        if(okdir[_up])
            ghost[ind]->set_dir(_up);
        else {
            if(qrand()&1) {
            if(disx >= 0) {
                if(okdir[_left])
                    ghost[ind]->set_dir(_left);
                else if(okdir[_right])
                    ghost[ind]->set_dir(_right);
            } else if(disx < 0){
                if(okdir[_right])
                    ghost[ind]->set_dir(_right);
                else if(okdir[_left])
                    ghost[ind]->set_dir(_left);
            }
            }
            else {
                if(disx >= 0) {
                    if(okdir[_right])
                        ghost[ind]->set_dir(_right);
                    else if(okdir[_left])
                        ghost[ind]->set_dir(_left);
                } else if(disx < 0){
                    if(okdir[_left])
                        ghost[ind]->set_dir(_left);
                    else if(okdir[_right])
                        ghost[ind]->set_dir(_right);
                }
            }
        }
    } else if(disy < 0) {
        if(okdir[_down])
            ghost[ind]->set_dir(_down);
        else {
            if(qrand()&1) {
            if(disx >= 0) {
                if(okdir[_left])
                    ghost[ind]->set_dir(_left);
                else if(okdir[_right])
                    ghost[ind]->set_dir(_right);
            } else if(disx < 0){
                if(okdir[_right])
                    ghost[ind]->set_dir(_right);
                else if(okdir[_left])
                    ghost[ind]->set_dir(_left);
            }
            }
            else {
                if(disx >= 0) {
                    if(okdir[_right])
                        ghost[ind]->set_dir(_right);
                    else if(okdir[_left])
                        ghost[ind]->set_dir(_left);
                } else if(disx < 0){
                    if(okdir[_left])
                        ghost[ind]->set_dir(_left);
                    else if(okdir[_right])
                        ghost[ind]->set_dir(_right);
                }
            }
        }
    } else if(disy == 0) {
        if(okdir[_up])
            ghost[ind]->set_dir(_up);
        else if(okdir[_down])
            ghost[ind]->set_dir(_down);
        else {
            if(disx >= 0) {
                if(okdir[_left])
                    ghost[ind]->set_dir(_left);
                else if(okdir[_right])
                    ghost[ind]->set_dir(_right);
            } else if(disx < 0){
                if(okdir[_right])
                    ghost[ind]->set_dir(_right);
                else if(okdir[_left])
                    ghost[ind]->set_dir(_left);
            }
        }
    }
}

void MainWindow::run(int ind) {
    int disx=0, disy=0, gpx, gpy,oknum=0,lastdir;
    bool okdir[4];
    QVector<int> way;
    gpx = ghost[ind]->get_px();
    gpy = ghost[ind]->get_py();
    okdir[_right] = (map[gpy][gpx+1] == '0' || map[gpy][gpx+1] =='2') ? true:false;
    okdir[_left] = (map[gpy][gpx-1] == '0' || map[gpy][gpx-1] == '2' )? true:false;
    okdir[_up] = (map[gpy-1][gpx] == '0' || map[gpy-1][gpx] == '2') ? true:false;
    okdir[_down] = (map[gpy+1][gpx] == '0' || map[gpy+1][gpx] == '2') ? true:false;
    if(gpx == gatex && gpy == gatey)
        ghost[ind]->throughgate = true;
    for(int i=0; i<4; ++i) {
        if(okdir[i]) {
            oknum++;
            way.push_back(i);
        }
    }
    lastdir = ghost[ind]->get_lastdir();
    if(oknum==2) {      //not intersection
        if(okdir[lastdir] == false) {
            switch(ghost[ind]->get_lastdir()) {
            case _left:
                if(way.at(0)==_right)
                    ghost[ind]->set_dir(way.at(1));
                else
                    ghost[ind]->set_dir(way.at(0));
                break;
            case _right:
                if(way.at(0)==_left)
                    ghost[ind]->set_dir(way.at(1));
                else
                    ghost[ind]->set_dir(way.at(0));
                break;
            case _up:
                if(way.at(0)==_down)
                    ghost[ind]->set_dir(way.at(1));
                else
                    ghost[ind]->set_dir(way.at(0));
                break;
            case _down:
                if(way.at(0)==_up)
                    ghost[ind]->set_dir(way.at(1));
                else
                    ghost[ind]->set_dir(way.at(0));
                break;
            }
        } else {
            ghost[ind]->set_dir(ghost[ind]->get_lastdir());
        }
        return;
    }

    if(ghost[ind]->throughgate) {
        ghost[ind]->throughgate = false;
        ghost[ind]->state = _normal;
        return;
    }

    disx = gatex - gpx;
    disy = gatey - gpy;

    if(disx > 0) {
        if(okdir[_right] && lastdir != _left)
            ghost[ind]->set_dir(_right);
        else {
            if(disy >= 0) {
                if(okdir[_down])
                    ghost[ind]->set_dir(_down);
                else if(okdir[_up])
                    ghost[ind]->set_dir(_up);
            } else if(disy < 0){
                if(okdir[_up])
                    ghost[ind]->set_dir(_up);
                else if(okdir[_down])
                    ghost[ind]->set_dir(_down);
            }
        }
    } else if(disx < 0) {
        if(okdir[_left] && lastdir != _right)
            ghost[ind]->set_dir(_left);
        else {
            if(disy >= 0) {
                if(okdir[_down])
                    ghost[ind]->set_dir(_down);
                else if(okdir[_up])
                    ghost[ind]->set_dir(_up);
            } else if(disy < 0){
                if(okdir[_up])
                    ghost[ind]->set_dir(_up);
                else if(okdir[_down])
                    ghost[ind]->set_dir(_down);
            }
        }
    } else if(disy > 0) {
        if(okdir[_down] && lastdir != _up)
            ghost[ind]->set_dir(_down);
        else {
            if(okdir[_left])
                ghost[ind]->set_dir(_left);
            else if(okdir[_right])
                ghost[ind]->set_dir(_right);
        }
    } else if(disy < 0) {
        if(okdir[_up] && lastdir != _down)
            ghost[ind]->set_dir(_up);
        else {
            if(okdir[_left])
                ghost[ind]->set_dir(_left);
            else if(okdir[_right])
                ghost[ind]->set_dir(_right);
        }
    }
}

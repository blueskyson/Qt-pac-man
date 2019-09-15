#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "item.h"
#include <QFile>
#include<QRandomGenerator>
#include<QDateTime>

/*create shared resource*/
char map[22][31];
QGraphicsPixmapItem *block[22][31];
QGraphicsScene *scene;
int dot_num, eat_sum, totalscore, gatex, gatey;
QLabel *score_title, *score, *win_label, *lose_label;
QString eat_str;
Item *pac,*ghost[4];
QVector<QGraphicsPixmapItem*> pball;
bool islose=false, iswin=false;

void MainWindow::set_board() {
    qsrand(QDateTime::currentDateTime().toTime_t());
    int ghost_ind=0;
    memset(map,'0',sizeof(map));
    dot_num = eat_sum = 0;
    totalscore = flashtik=0;
    QPixmap blockpix(":/rsc/block.png");
    QPixmap dotpix(":/rsc/dot.png");
    QPixmap powerball(":/rsc/power_ball.png");
    QFile mapfile(":/rsc/map.txt");
    QString mapstr;
    QByteArray mapline;
    mapfile.open(QIODevice::ReadOnly|QIODevice::Text);
    for(int i=1;i<21;++i) {
        QByteArray mapline = mapfile.readLine();
        mapstr = QString(mapline);
        for(int j=1;j<30;++j) {
            map[i][j] = mapline.at(j-1);
            switch(map[i][j]) {
            case '1':
                block[i][j] = new QGraphicsPixmapItem(blockpix);
                scene->addItem(block[i][j]);
                block[i][j]->setPos(_xborder+j*_width, _yborder+i*_width);
                break;
            case '0':
                block[i][j] = new QGraphicsPixmapItem(dotpix);
                scene->addItem(block[i][j]);
                block[i][j]->setPos(_xborder+j*_width, _yborder+i*_width);
                dot_num++;
                break;
            case '4':
                map[i][j] = '0';
                block[i][j] = new QGraphicsPixmapItem(powerball);
                scene->addItem(block[i][j]);
                block[i][j]->setPos(_xborder+j*_width, _yborder+i*_width);
                pball.push_back(block[i][j]);
                dot_num++;
                break;
            case 'g':
                map[i][j] = '0';
                block[i][j] = nullptr;
                ghost[ghost_ind] = new Ghost(j,i,ghost_ind);
                ghost[ghost_ind]->setPos(_xborder+j*_width, _yborder+i*_width);               
                scene->addItem(ghost[ghost_ind]);
                ghost[ghost_ind]->set_posx(static_cast<int>(ghost[ghost_ind]->x()));
                ghost[ghost_ind]->set_posy(static_cast<int>(ghost[ghost_ind]->y()));
                ghost[ghost_ind]->state = _normal;
                ghost[ghost_ind]->throughgate = false;
                ghost_ind++;
                break;
            case '3':
                map[i][j] = '0';
                block[i][j]=nullptr;
                break;
            case 'p':
                map[i][j] = '0';
                block[i][j] = nullptr;
                pac = new Pacman(j,i);
                pac->setPos(_xborder+j*_width, _yborder+i*_width);
                scene->addItem(pac);
                break;
            case '2':
                block[i][j] = new QGraphicsPixmapItem(QPixmap(":/rsc/gate.png"));
                scene->addItem(block[i][j]);
                block[i][j]->setPos(_xborder+j*_width, _yborder+i*_width);
                gatex=j;
                gatey=i;
            }
        }
    }
    pac->setZValue(2);
    score_title = new QLabel(this);
    score_title->setText("score");
    score_title->setStyleSheet("QLabel {font-family: Fixedsys;color: white;font-size: 16px;}");
    score_title->setGeometry(50,12,60,26);
    score = new QLabel(this);
    score->setIndent(-80);
    score->setText("0");
    score->setStyleSheet("QLabel {font-family: Fixedsys;color: white;font-size: 16px;}");
    score->setGeometry(110,12,150,26);

    win_label = new QLabel(this);
    win_label->hide();
    win_label->setText("You win!");
    win_label->setStyleSheet("QLabel {font-family: Fixedsys;color: yellow;font-size: 16px;}");
    win_label->setGeometry(310,12,150,26);

    lose_label = new QLabel(this);
    lose_label->hide();
    lose_label->setText("You lose");
    lose_label->setStyleSheet("QLabel {font-family: Fixedsys;color: red;font-size: 16px;}");
    lose_label->setGeometry(310,12,150,26);
    ghost[0]->begintik = 1;
    ghost[1]->begintik = 50;
    ghost[2]->begintik = 100;
    ghost[3]->begintik = 150;
    mapfile.close();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initLabels();
    void keyPressEvent(QKeyEvent*) override;

private slots:
    void update_score();

private:
    Ui::MainWindow *ui;
    QLabel *score_title, *score;
    QLabel *win_label, *lose_label;
    QTimer *score_timer;
    Game *game;
};
#endif // MAINWINDOW_H

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QVector>


/* Predefine the game object */
class Game;


/* Base class of ghosts, pacman */
class GameObject : public QGraphicsPixmapItem
{
public:
    enum ObjectType {Ball, Wall, Gate, Pacman, Ghost, Blank, PowerBall};
    enum Dir {Up = 0, Down = 1, Left = 2, Right = 3, Stop = 4};
    static const int Width = 20;      // game object size by pixel

    GameObject(ObjectType, QPixmap);
    ~GameObject();
    ObjectType get_type();
    int get_x();
    int get_y();
    int get_score();
    void set_score(int);
    void set_dir(Dir);
    void set_next_dir(Dir);
    Dir get_dir();
    Dir get_next_dir();

    friend class Game;
    friend class Ghost;

protected:
    int _x, _y;                 // coordinate in map
    Dir dir;                    // current moving direction
    Dir next_dir;               // next direction by w, a, s, d key
    ObjectType type;
    int score;
};


/* Pacman */
class Pacman : public GameObject
{
public:
    Pacman();
    void move();
    Game *game;                 // the pacman game object

    friend class Game;

private:
    void moveup();
    void movedown();
    void moveleft();
    void moveright();
    void eat_ball(int, int);
    bool overlapable(int, int); // check if pacman can go to map[i][j]

    QVector<QPixmap> anim[4];   // animations
    int anim_index;
};


/* Ghost */
class Ghost : public GameObject
{
public:
    enum Color {Red = 0, Yellow = 1, Pink = 2, Green = 3};
    enum Status {Normal, Panic, Running};
    const static int GhostNum = 4;
    Game *game;                 // the pacman game object

    Ghost(int);
    void move();
    Color get_color();

    friend class Game;
    friend class Pacman;

private:
    void moveup();
    void movedown();
    void moveleft();
    void moveright();

    void setdir_randomly();
    void go_out_cage();
    void chase_pacman();
    void dodge_pacman();
    void go_to_cage();
    QPair<int, int> (*chase_strategy)(Ghost*);  // function pointer of a chasing stragety
    bool overlapable(int, int);                 // check if ghost can go to map[i][j]

    Color color;
    Status status;
    QVector<QPixmap> anim[4];                   // animations
    QVector<QPixmap> panic_anim;
    QVector<QPixmap> running_anim;
    int anim_index;
    int release_time;           // time to get out the cage
    bool is_released;
    int panic_time;
};


/* Chasing strategies of ghosts,
 * which is represented as a QPair of vector
 * from the ghost to the pacman. */
QPair<int, int> strategy1(Ghost*);
QPair<int, int> strategy2(Ghost*);
QPair<int, int> strategy3(Ghost*);
QPair<int, int> strategy4(Ghost*);

#endif // GAMEOBJECT_H

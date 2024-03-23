#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QIcon>
#include <QTimer>
#include "bomb.h"
#include "enemyplane.h"
#include "map.h"
#include <QPainter>
#include "hero.h"
#include <QMouseEvent>
#include <ctime>
#include "bullet.h"
#include   <QKeyEvent>
#include  <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSoundEffect>
class MainScene : public QWidget
{
    Q_OBJECT

private:
    QTimer m_MoveTimer;

public:
    MainScene(QWidget *parent = nullptr);
    void  initScene();
    QTimer m_Timer;
    ~MainScene();
    //启动游戏  用于启动定时器对象
    void playGame();
    //更新坐标
    void updatePosition();
    //绘图事件
    void paintEvent(QPaintEvent *event);
    //飞机对象
    Hero hero;
    //地图对象
    Map m_map;

//    void mouseMoveEvent(QMouseEvent *event);
    //键盘使之移动的代码
    void keyPressEvent(QKeyEvent *event);
    void moveHeroLeft();
    void moveHeroRight();
    void shootBullet();
    void moveHeroUp();
    void moveHeroDown();
    bool m_MoveLeft  ,m_MoveRight  ,m_MoveUp, m_MoveDown,m_isSpecialButtonVisible;;
    void continuousMove();
    //敌机出场
    void enemyToScene();

    //敌机数组
    EnemyPlane m_enemys[ENEMY_NUM];

    //敌机出场间隔记录
    int m_recorder;
    //碰撞
    void collisionDetection();
    //爆炸数组
    Bomb m_bombs[BOMB_NUM];


     QMovie gifMovie; // 添加一个 QMovie 对象
     //尝试使用积分
     QLabel* m_scoreLabel;
     //添加开始按钮
     QPushButton* m_startButton;
     //特殊宝箱按钮
     QPushButton* m_specialButton;
     void specialButtonClicked();
     void  startGame();
     int m_score;

};



#endif // MAINSCENE_H

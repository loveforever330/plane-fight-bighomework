#ifndef HERO_H
#define HERO_H
#include "bullet.h"
#include "config.h"
#include <QMovie>
#include <QRect>
#include <QLabel>
class Hero
{
public:
    Hero();
    //发射子弹
    void shoot();
    void setPosition(int x, int y);
public:
    //英雄资源 对象
    QLabel  heroLabel;
    QMovie heroMovie;
    //英雄坐标
    int m_X;
    int m_Y;

    //英雄的矩形边框
    QRect m_Rect;

    //弹匣
    Bullet m_bullets[BULLET_NUM];

    //发射间隔记录
    int m_recorder;
    void setRect(const QRect& rect);
};

#endif // HERO_H

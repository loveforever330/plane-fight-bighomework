#include "hero.h"


#include "config.h"

Hero::Hero()
{
    //加载人物图像
    QMovie movie(":/resource/hero.png");
    QRect frameRect = movie.frameRect();
    int gifWidth =frameRect.width();
    int gifHeight = frameRect.height();

    QLabel* label = new QLabel();
    label->setMovie(&movie);

    // 设置 QLabel 的尺寸
    label->setFixedSize(gifWidth, gifHeight);

    // 开始播放动画
    movie.start();
    //人物位置
    m_X = GAME_WIDTH * 0.5 - gifWidth*0.5;
    m_Y = GAME_HEIGHT-gifHeight ;

    //heroLabel.setParent(this); // 设置父对象，通常是一个QWidget或QMainWindow
    heroLabel.setMovie(&heroMovie);
    heroMovie.setFileName(":/resource/Dragoncat.gif");
    heroMovie.start();
    //初始化矩形框
    m_Rect.setWidth(gifWidth);
    m_Rect.setHeight(gifHeight);
    m_Rect.moveTo(m_X,m_Y);
    //初始化发射间隔记录
        m_recorder=0;
}
void Hero::setPosition(int x, int y)
{
    if (x < 0)
        x = 0;
    else if (x > GAME_WIDTH - m_Rect.width())
        x = GAME_WIDTH - m_Rect.width();

    if (y < 0)
        y = 0;
    else if (y > GAME_HEIGHT - m_Rect.height())
        y = GAME_HEIGHT - m_Rect.height()-300;

    m_X = x;
    m_Y = y;
    m_Rect.moveTo(m_X, m_Y);
}

void Hero::shoot()
{
    //累加时间间隔记录变量
    m_recorder++;
    //判断如果记录数字 未达到发射间隔，直接return
    if(m_recorder < BULLET_INTERVAL)
    {
        return;
    }
    //到达发射时间处理
    //重置发射时间间隔记录
    m_recorder = 0;

    //发射子弹
    for(int i = 0 ; i < BULLET_NUM;i++)
    {
        //如果是空闲的子弹进行发射
        if(m_bullets[i].m_Free)
        {
            //将改子弹空闲状态改为假
            m_bullets[i].m_Free = false;
            //设置发射的子弹坐标
            m_bullets[i].m_X = m_X + m_Rect.width()*0.5 + 100;
            m_bullets[i].m_Y = m_Y +80 ;
            break;
        }
    }
}
void Hero::setRect(const QRect& rect)
{
    m_Rect = rect;
}

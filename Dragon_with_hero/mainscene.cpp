#include "mainscene.h"
#include "config.h"
MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{

    hero.heroLabel.move(hero.m_X, hero.m_Y);
    initScene();
}
void MainScene::initScene()
{
    //初始化窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置窗口标题
    setWindowTitle(GAME_TITLE);
    setWindowIcon(QIcon( GAME_ICON));  //加头文件 #include <QIcon>
    setFocusPolicy(Qt::StrongFocus);
    // 初始化移动定时器
    m_MoveTimer.setInterval(100); // 设置定时器间隔为100毫秒，可以根据需要调整
    connect(&m_MoveTimer, &QTimer::timeout, this, &MainScene::continuousMove);
    // ...
    //定时器设置
    m_Timer.setInterval(GAME_RATE);
    //随机数种子
    srand((unsigned int)time(NULL));  //头文件  #include <ctime>
    m_score =0;//得分
    m_recorder = 0;//
    hero.setPosition(x()+540, y()+250);
    // 设置英雄对象的矩形框
    int heroWidth = PdmWidth;  // 根据英雄图像的宽度调整矩形框的大小
    int heroHeight = PdmHeight;  // 根据英雄图像的高度调整矩形框的大小
    QRect heroRect(hero.m_X, hero.m_Y, heroWidth, heroHeight);
    hero.setRect(heroRect);
    //显示得分多少

    QHBoxLayout* layout = new QHBoxLayout(this);

    // 创建 QLabel 对象
    m_scoreLabel = new QLabel(this);
    m_scoreLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); // 设置 QLabel 的大小策略
    m_scoreLabel->setText("Score: 0");
    m_scoreLabel->setAlignment(Qt::AlignTop | Qt::AlignHCenter); // 设置文本居中显示
    // 创建按钮对象
    m_startButton = new QPushButton("开始游戏", this);
    m_startButton->setGeometry(10, 10, 100, 30);

    // 创建特殊按钮对象
    m_specialButton = new QPushButton("神秘宝箱", this);
    m_specialButton->setGeometry(10, 20, 100, 30);
    m_specialButton->hide();


    // 连接按钮的点击事件到槽函数
    connect(m_startButton, &QPushButton::clicked, this, &::MainScene::startGame);
       // startSound->stop();
    //特殊按钮的链接
    connect(m_specialButton, &QPushButton::clicked, this, &MainScene::specialButtonClicked);



    // 将 QLabel 添加到布局管理器中
    layout->addWidget(m_scoreLabel);

    // 设置布局管理器
    setLayout(layout);


}
void MainScene::playGame()
{
    //音乐
    QSoundEffect * startSound = new QSoundEffect(this);//创建对象
    startSound->setSource(QUrl::fromLocalFile(":/resource/Knock_1.wav"));//添加资源
    startSound->setLoopCount(QSoundEffect::Infinite);//设置循环次数int；  QSoundEffect::Infinite 枚举值 无限循环
    startSound->play();//软件启动自动播放

    //启动定时器
    m_Timer.start();

    //监听定时器
    connect(&m_Timer,&QTimer::timeout,[=]()
    {
        //敌机出场
        enemyToScene();
        //更新游戏中元素的坐标
        updatePosition();
        //重新绘制图片
        update();
        collisionDetection();
    });

}
void MainScene::updatePosition()
{
    //更新地图坐标
    m_map.mapPosition();
    hero.shoot();
    //计算子弹坐标
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲，计算发射位置
        if(!hero.m_bullets[i].m_Free)
        {
            hero.m_bullets[i].updatePosition();
        }
    }
    //敌机坐标计算
        for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        //非空闲敌机 更新坐标
        if(m_enemys[i].m_Free == false)
        {
            m_enemys[i].updatePosition();
        }
    }
        //计算爆炸播放的图片
        for(int i = 0 ; i < BOMB_NUM;i++)
        {
            if(m_bombs[i].m_Free == false)
            {
            m_bombs[i].updateInfo();
            }
        }

        if (m_score >25 && !m_isSpecialButtonVisible)
        {
             // 显示特殊按钮
             m_specialButton->show();
             m_isSpecialButtonVisible = true;
        }

}

void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(m_map.m_map1_posX ,0, m_map.m_map1);
    painter.drawPixmap(m_map.m_map2_posX ,0,m_map.m_map2);

    // 绘制英雄的 GIF 图像
    QRect heroRect(hero.m_X, hero.m_Y, hero.heroMovie.currentPixmap().width(), hero.heroMovie.currentPixmap().height());
    painter.drawImage(heroRect, hero.heroMovie.currentImage());
    //绘制子弹
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲，计算发射位置
             if(!hero.m_bullets[i].m_Free)
        {
            painter.drawPixmap(hero.m_bullets[i].m_X,hero.m_bullets[i].m_Y,hero.m_bullets[i].m_Bullet);
        }
    }
    //绘制敌机
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free == false)
        {
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy);
        }
    }
    //绘制爆炸图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
            painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,m_bombs[i].m_pixArr[m_bombs[i].m_index]);
        }
    }
    if (m_isSpecialButtonVisible)
    {
        painter.drawPixmap(m_specialButton->geometry(), QPixmap("button.png"));  // 替换 "button.png" 为你的按钮图像路径
    }

}
//void MainScene::mouseMoveEvent(QMouseEvent *event)
//{
//    int x = event->x() - hero.m_Rect.width()*0.5; //鼠标位置 - 飞机矩形的一半
//    int y = event->y() - hero.m_Rect.height()*0.5;

//    //边界检测
//    if(x <= 0 )
//    {
//        x = 0;
//    }
//    if(x >= GAME_WIDTH - hero.m_Rect.width())
//    {
//        x = GAME_WIDTH - hero.m_Rect.width();
//    }
//    if(y <= 0)
//    {
//        y = 0;
//    }
//    if(y >= GAME_HEIGHT - hero.m_Rect.height())
//    {
//        y = GAME_HEIGHT - hero.m_Rect.height();
//    }
//    hero.setPosition(x,y);
//}
void MainScene::keyPressEvent(QKeyEvent *event)
{
    // 获取按下的键盘按键
    int key = event->key();

    // 根据按下的键盘按键进行相应操作
    switch (key)
    {
    case Qt::Key_A:
        // 向左移动
        moveHeroLeft();
        m_MoveTimer.start();
        break;
    case Qt::Key_D:
        // 向右移动
        moveHeroRight();
        m_MoveTimer.start();
        break;
    case Qt::Key_W:
        // 向上移动
        moveHeroUp();
        m_MoveTimer.start();
        break;
    case Qt::Key_S:
        // 向下移动
        moveHeroDown();
        m_MoveTimer.start();
        break;
    case Qt::Key_Space:
        // 发射子弹
        shootBullet();
        break;
    default:
        // 其他按键不处理
        break;
    }
}
void MainScene::continuousMove()
{
    // 根据当前按下的键盘按键持续进行移动
    if (m_MoveLeft)
    {
        moveHeroLeft();
    }
    else if (m_MoveRight)
    {
        moveHeroRight();
    }
    else if (m_MoveUp)
    {
        moveHeroUp();
    }
    else if (m_MoveDown)
    {
        moveHeroDown();
    }
}
void MainScene::moveHeroLeft()
{
    // 向左移动的逻辑
    int x = hero.m_X - HERO_SPEED;
    // 边界检测
    if (x < 0)
        x = 0;
    hero.setPosition(x, hero.m_Y);

    // 记录当前移动的方向
    m_MoveLeft = true;
    m_MoveRight = false;
    m_MoveUp = false;
    m_MoveDown = false;
}
void MainScene::moveHeroRight()
{
    // 向右移动的逻辑
    int x = hero.m_X + HERO_SPEED;
    // 边界检测
    if (x > GAME_WIDTH - hero.m_Rect.width())
        x = GAME_WIDTH - hero.m_Rect.width();
    hero.setPosition(x, hero.m_Y);

    // 记录当前移动的方向
    m_MoveLeft = false;
    m_MoveRight = true;
    m_MoveUp = false;
    m_MoveDown = false;
}

void MainScene::moveHeroUp()
{
    // 向上移动的逻辑
    int y = hero.m_Y - HERO_SPEED;
    // 边界检测
    if (y < 0)
        y = 0;
    hero.setPosition(hero.m_X, y);

    // 记录当前移动的方向
    m_MoveLeft = false;
    m_MoveRight = false;
    m_MoveUp = true;
    m_MoveDown = false;
}

void MainScene::moveHeroDown()
{
    // 向下移动的逻辑
    int y = hero.m_Y + HERO_SPEED;
    // 边界检测
    if (y > GAME_HEIGHT - hero.m_Rect.height())
        y = GAME_HEIGHT - hero.m_Rect.height()-1;
    hero.setPosition(hero.m_X, y);

    // 记录当前移动的方向
    m_MoveLeft = false;
    m_MoveRight = false;
    m_MoveUp = false;
    m_MoveDown = true;
}
void MainScene::shootBullet()
{

}
void MainScene::enemyToScene()
{
    m_recorder++;
    if(m_recorder < ENEMY_INTERVAL)
    {
        return;
    }

    m_recorder = 0;

    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(m_enemys[i].m_Free)
        {
            //敌机空闲状态改为false
            m_enemys[i].m_Free = false;
            //设置坐标
            m_enemys[i].m_X = rand() % (GAME_WIDTH - m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y = -m_enemys[i].m_Rect.height();
            break;
        }
    }
}
//以上是移动设计
void MainScene::collisionDetection()
{
    //遍历所有非空闲的敌机
    for(int i = 0 ;i < ENEMY_NUM;i++)
    {
        //如果敌机矩形框和英雄矩形框相交，得分减一
        if(m_enemys[i].m_Rect.intersects(hero.m_Rect))
        {
            m_score -=1;
            m_scoreLabel->setText("Score: " + QString::number(m_score));

        }
        if(m_enemys[i].m_Free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }

        //遍历所有 非空闲的子弹
        for(int j = 0 ; j < BULLET_NUM;j++)
        {
            if(hero.m_bullets[j].m_Free)
            {
                //空闲子弹 跳转下一次循环
                continue;
            }

            //如果子弹矩形框和敌机矩形框相交，发生碰撞，同时变为空闲状态即可
            if(m_enemys[i].m_Rect.intersects(hero.m_bullets[j].m_Rect))
            {
                m_enemys[i].m_Free = true;
                hero.m_bullets[j].m_Free = true;
                // 在发生子弹碰撞的地方
                // 假设子弹碰撞后需要增加1分
                m_score += 1;
                m_scoreLabel->setText("Score: " + QString::number(m_score));

            //播放爆炸效果
                 for(int k = 0 ; k < BOMB_NUM;k++)
                {
                if(m_bombs[k].m_Free)
                    {
                     //爆炸状态设置为非空闲
                        m_bombs[k].m_Free = false;
                        //更新坐标

                        m_bombs[k].m_X = m_enemys[i].m_X;
                        m_bombs[k].m_Y = m_enemys[i].m_Y;
                        break;
                    }
                }
            }
        }
    }
}
void MainScene::specialButtonClicked()
{
    // 处理特殊按钮点击事件的逻辑
    QMessageBox::information(this, "宝箱按钮", "没有用的神秘宝箱");
    m_specialButton->hide();
}
void MainScene::startGame()
{
    // 显示游戏玩法
    QMessageBox::information(this, "Game Instructions", "通过wasd方向键控制方位，命中敌人即可得分,看看你是否可以获取神秘宝箱");
    m_startButton->hide();

    // 开始游戏逻辑
    playGame();
}
MainScene::~MainScene()
{

}

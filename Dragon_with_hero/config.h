#ifndef CONFIG_H
#define CONFIG_H
/***窗口化***/
#define GAME_HEIGHT  600
#define GAME_WIDTH 1200
#define GAME_TITLE "龙与英雄v1.0"
#define GAME_ICON  ":/resource/app.ico"
/**********  地图配置数据 **********/
#define MAP_PATH  ":/resource/img_bg_level_1.jpg" //地图图片路径
#define MAP_PATH1 ":/resource/img_bg_level_2.jpg"
#define MAP_SCROLL_SPEED 2  //地图滚动速度
#define GAME_RATE  10   //刷新间隔，帧率 单位毫秒
/***英雄类***/
#define HERO_PATH ":/resource/Dragoncat.gif"
#define HERO_SPEED 15
/**********  子弹配置数据 **********/
#define BULLET_PATH ":/resource/bullet_5.png"   //子弹图片路径
#define BULLET_SPEED 5  //子弹移动速度
#define BULLET_NUM 8   //弹匣中子弹总数
#define BULLET_INTERVAL 20 //发射子弹时间间隔
/**********  敌机配置数据 **********/
#define ENEMY_PATH  ":/resource/hero.png"  //敌机资源图片
#define ENEMY_SPEED 4  //敌机移动速度
#define ENEMY_NUM   20  //敌机总数量
#define ENEMY_INTERVAL  30  //敌机出场时间间隔
//爆炸//
#define BOMB_PATH  ":/resource/bomb-%1.png"   //爆炸资源图片
#define BOMB_NUM  20     //爆炸数量
#define BOMB_MAX  7      //爆炸图片最大索引
#define BOMB_INTERVAL 20   //爆炸切图时间间隔
#endif // CONFIG_H

#include "map.h"
#include "config.h"

Map::Map()
{
    //初始化加载地图对象
    m_map1.load(MAP_PATH1);
    m_map2.load(MAP_PATH1);

    //设置地图其实x轴坐标
    m_map1_posX = 0;
    m_map2_posX = GAME_WIDTH;

    //设置地图滚动速度
    m_scroll_speed = MAP_SCROLL_SPEED;
}

void Map::mapPosition()
{
    //处理第一张图片滚动
    m_map1_posX -= MAP_SCROLL_SPEED;
    if(m_map1_posX <=-GAME_WIDTH)
    {
        m_map1_posX =0;
    }

    //处理第二张图片滚动
    m_map2_posX -= MAP_SCROLL_SPEED;
    if(m_map2_posX <=0 )
    {
        m_map2_posX =GAME_WIDTH;
    }
}

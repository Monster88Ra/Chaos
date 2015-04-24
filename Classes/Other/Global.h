#ifndef _GLOBAL_H
#define _GLOBAL_H
#include "cocos2d.h"
USING_NS_CC;

#include "Singleton.h"
#include "Game\GameLayer.h"
#include "Operate\OperateLayer.h"
#include "State\StateLayer.h"

class GameLayer;
class OperateLayer;
class StateLayer;
class Hero;
class Enemy;

//全局单列
class Global:public Singleton<Global>
{
public:
	Global();
	~Global();

	GameLayer *gameLayer;			//游戏层
	OperateLayer *operateLayer;		//操作层
	StateLayer * stateLayer;		//状态层
	Hero *hero;						//英雄
	__Array *enemies;				//敌人
	TMXTiledMap *tileMap;			//地图



	Point tilePosFromLocation(Vec2 MovePoint, TMXTiledMap *map = 0);//将point转换成地图GID的point
	bool  tileAllowMove(Vec2 MovePoint);
};
#define global Global::instance()
#endif//Global.h

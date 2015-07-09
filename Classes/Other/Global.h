#ifndef _GLOBAL_H
#define _GLOBAL_H
#include "cocos2d.h"
USING_NS_CC;
#include <vector>
#include "Singleton.h"
#include "Game\GameLayer.h"
#include "Logo\ShowLayer.h"
#include "Operate\OperateLayer.h"
#include "Operate\SkillButton.h"
#include "State\StateLayer.h"
#include "Other\GameSceneInfo.h"
#include "ReadJson\HeroMessage.h"
#include "ReadJson\HeroMessageUtil.h"
class GameLayer;
class ShowLayer;
class OperateLayer;
class StateLayer;
class Hero;
class Enemy;
class Boss;
class SkillButton;
//全局单列
class Global:public Singleton<Global>
{
public:
	Global();
	~Global();

	GameLayer *gameLayer;			//游戏层
	ShowLayer *showLayer;			//logo 展示层
	OperateLayer *operateLayer;		//操作层
	StateLayer * stateLayer;		//状态层
	Hero *hero;						//英雄
	__Array *enemies;				//敌人array
	__Array *bosses;				//bossarray
	TMXTiledMap *tileMap;			//地图
	Sprite *deadFire;				//鬼火
	Sprite *ultimateSkill;			//终极技能
	std::vector<GameSceneInfo*> sceneInfoVector;//保存场景的信息

	bool enemiesAllDie;				//记录敌人状态

	Point tilePosFromLocation(Vec2 MovePoint, TMXTiledMap *map = 0);//将point转换成地图GID的point
	bool  tileAllowMove(Vec2 MovePoint);
	float getTileMapWidth();//地图宽度
	float getTileMapHeight();//地图高度

	std::size_t sceneIndex;	//场景索引
	HeroMessage heroInfo;//英雄信息

	SkillButton *skillA;
};
#define global Global::instance()
#endif//Global.h

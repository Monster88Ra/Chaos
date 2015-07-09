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
//ȫ�ֵ���
class Global:public Singleton<Global>
{
public:
	Global();
	~Global();

	GameLayer *gameLayer;			//��Ϸ��
	ShowLayer *showLayer;			//logo չʾ��
	OperateLayer *operateLayer;		//������
	StateLayer * stateLayer;		//״̬��
	Hero *hero;						//Ӣ��
	__Array *enemies;				//����array
	__Array *bosses;				//bossarray
	TMXTiledMap *tileMap;			//��ͼ
	Sprite *deadFire;				//���
	Sprite *ultimateSkill;			//�ռ�����
	std::vector<GameSceneInfo*> sceneInfoVector;//���泡������Ϣ

	bool enemiesAllDie;				//��¼����״̬

	Point tilePosFromLocation(Vec2 MovePoint, TMXTiledMap *map = 0);//��pointת���ɵ�ͼGID��point
	bool  tileAllowMove(Vec2 MovePoint);
	float getTileMapWidth();//��ͼ���
	float getTileMapHeight();//��ͼ�߶�

	std::size_t sceneIndex;	//��������
	HeroMessage heroInfo;//Ӣ����Ϣ

	SkillButton *skillA;
};
#define global Global::instance()
#endif//Global.h

#ifndef _GAME_LAYER_H
#define _GAME_LAYER_H
#include "cocos2d.h"
USING_NS_CC;
#include "MapLayer.h"
#include "Role\Hero.h"
#include "Role\Enemy.h"
#include "Role\Boss.h"
#include "Other\Global.h"
#include "Other\Resources.h"
#include "SimpleAudioEngine.h"

class Hero;
class Boss;
class GameLayer:public cocos2d::Layer
{
public:
	GameLayer();
	~GameLayer();
	virtual bool init();

	void addHero();
	void addaddEnemies(int number);
	void addBoss(int number);
	void addGhostFire(Vec2 p);

	void update(float dt);
	void updateHero(float dt);
	void updateEnemies(float dt);
	void updateBoss(float dt);
	__Array *m_pEnemies;

	CC_SYNTHESIZE_READONLY(Hero*, m_pHero, Hero);
	CC_SYNTHESIZE_READONLY(Boss*, m_pBoss, Boss);
	CREATE_FUNC(GameLayer);


	CC_SYNTHESIZE_RETAIN(Action*, m_pdeadfire, deadFire);
private:
	Size _visibleSize;
	Vec2 _visibleOrigin;
};
#endif //GameLayer.h
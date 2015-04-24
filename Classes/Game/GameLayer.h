#ifndef _GAME_LAYER_H
#define _GAME_LAYER_H
#include "cocos2d.h"
USING_NS_CC;
#include "MapLayer.h"
#include "Role\Hero.h"
#include "Other\Global.h"
class Hero;
class GameLayer:public cocos2d::Layer
{
public:
	GameLayer();
	~GameLayer();
	virtual bool init();

	void addHero();

	void update(float dt);
	void updateHero(float dt);

	CC_SYNTHESIZE_READONLY(Hero*, m_pHero, Hero);
	CREATE_FUNC(GameLayer);
private:
	Size _visibleSize;
	Vec2 _visibleOrigin;
};
#endif //GameLayer.h
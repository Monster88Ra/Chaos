#ifndef _HERO_H	
#define _HERO_H

#include "cocos2d.h"
USING_NS_CC;
#include "Role.h"
#include "Other\Global.h"
class Hero:public Role
{
public:
	Hero(void);
	~Hero(void);
	virtual bool init();
	CREATE_FUNC(Hero);

	void onMove(Vec2 direction, float distance);
	void onStop();
	void onAttack(int number);
	void updateSelf();
};
#endif //Hero.h
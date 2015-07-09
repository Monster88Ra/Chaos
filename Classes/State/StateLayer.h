#ifndef _STATE_LAYER_H	
#define _STATE_LAYER_H

#include "cocos2d.h"
USING_NS_CC;
#include "HpShow.h"
#include "MagicShow.h"
#include "Other\Global.h"
class StateLayer:public cocos2d::Layer
{
public:
	StateLayer();
	~StateLayer();
	virtual bool init();

	CC_SYNTHESIZE_RETAIN(Action*, m_ultimateskill, ultimateSkill);

	CREATE_FUNC(StateLayer);

};
#endif //StateLayer.h
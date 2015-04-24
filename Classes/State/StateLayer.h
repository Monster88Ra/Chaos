#ifndef _STATE_LAYER_H	
#define _STATE_LAYER_H

#include "cocos2d.h"
USING_NS_CC;
#include "Other\Global.h"
class StateLayer:public cocos2d::Layer
{
public:
	StateLayer();
	~StateLayer();
	virtual bool init();

	CREATE_FUNC(StateLayer);
};
#endif //StateLayer.h
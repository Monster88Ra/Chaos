#ifndef _OPERATE_LAYER_H
#define _OPERATE_LAYER_H

#include "cocos2d.h"
USING_NS_CC;
#include "Joystick.h"
class OperateLayer:public cocos2d::Layer
{
public:
	OperateLayer();
	~OperateLayer();
	virtual bool init();
	void attackButton(Ref *pSender);//为手游准备
	CREATE_FUNC(OperateLayer);
};
#endif //OperateLayer.h
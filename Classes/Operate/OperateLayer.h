#ifndef _OPERATE_LAYER_H
#define _OPERATE_LAYER_H

#include "cocos2d.h"
USING_NS_CC;
#include "Joystick.h"
#include "SkillButton.h"
class OperateLayer:public cocos2d::Layer
{
public:
	OperateLayer();
	~OperateLayer();
	virtual bool init();
	void attackButton(Ref *pSender);//Ϊ����׼��
	CREATE_FUNC(OperateLayer);
};
#endif //OperateLayer.h
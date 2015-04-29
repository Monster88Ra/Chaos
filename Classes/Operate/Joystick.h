#ifndef _JOYSTICK_H
#define _JOYSTICK_H
#include "cocos2d.h"
USING_NS_CC;
#include "Other\Global.h"
#include <Windows.h>
class Hero;
class Joystick :public Sprite
{
public:
	Joystick();
	~Joystick();
	virtual bool init();
	virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	virtual	void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);
	void setJoystick(Vec2 point);
	void setDistance(float ds);//移动的基本单位
	EventListenerKeyboard *keyboardListener;
	CREATE_FUNC(Joystick);

private:
	void showJoystick();
	void hideJoystick();
	void updateJoystick(Touch *touch);
	int m_pJoystickr;
	int m_pJoystickR;
	Sprite *m_pJoystick;
	Sprite *m_pJoystickBg;
	Vec2 start;
	float roleDistance;
	

	static double Joystick::pressButtonTime ;
};

#endif //Joystick.h
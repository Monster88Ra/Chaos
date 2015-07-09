#ifndef _SHOW_LAYER_H
#define _SHOW_LAYER_H

#include "cocos2d.h"
#include "Other\Global.h"
#include "Other\GameScene.h"
#include "Other\DialogScene.h"
USING_NS_CC;

class ShowLayer :public cocos2d::Layer
{
public:
	ShowLayer();
	~ShowLayer();
	virtual bool init();
	static Animation* createAttackAnimation(const char* formatStr, int frameCountBegan, int frameCountEnd, int fps);
	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);

	//void sceneCallBack(Object* pSender);
	void opEndCallBack(Node *pSender);//op 结束后回调
	void opBGMCallBackAction(Node *pSender);//op BGM 回调
	CREATE_FUNC(ShowLayer);
private:
	Size _visibleSize;
	Vec2 _visibleOrigin;
	Sprite *sprite;

public:
	EventListenerKeyboard *keyboardListener;
	int inLogoStep;
};
#endif//_SHOW_LAYER_H
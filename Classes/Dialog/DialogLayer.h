#ifndef _DIALOG_LAYER_H
#define _DIALOG_LAYER_H

#include "cocos2d.h"
#include "Other\Global.h"
#include "Other\DialogScene.h"


class DialogLayer :public cocos2d::Layer
{
public:
	DialogLayer();
	~DialogLayer();
	virtual bool init();

	virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event);
	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event);
	void sceneCallBack(Object* pSender);
	Vector<Sprite*> createDialogPic(const char* formatStr, int frameCount);

	CREATE_FUNC(DialogLayer);
private:
	Sprite *sprite;
	Vector<Sprite*>  spriteVector;
	Size _visibleSize;
	Vec2 _visibleOrigin;
public:
	EventListenerKeyboard *keyboardListener;
	std::size_t index;
};

#endif//_DIALOG_LAYER_H
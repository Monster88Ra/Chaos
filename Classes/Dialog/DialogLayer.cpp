#include "DialogLayer.h"

USING_NS_CC;

DialogLayer::DialogLayer():index(0)
{

}

DialogLayer::~DialogLayer()
{

}

bool DialogLayer::init()
{
	bool ret = false;
	do{
		CC_BREAK_IF(!Layer::init());
		_visibleSize = Director::getInstance()->getVisibleSize();
		_visibleOrigin = Director::getInstance()->getVisibleOrigin();

		//初始化剧情
		spriteVector = createDialogPic("dialog%d.png", 4);
		//章节
		Sprite *chapter2 = Sprite::createWithSpriteFrameName("chapter2.png");
		chapter2->setAnchorPoint(Vec2(0.5f, 0.5f));
		chapter2->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
		spriteVector.pushBack(chapter2);

		sprite = spriteVector.at(index);

		sprite->setAnchorPoint(Vec2(0.5f,0.5f));
		sprite->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
		this->addChild(sprite);

		//停止全部音效
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
		//停止背景音乐
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		//播放音效
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/City1_Loop.mp3", true);

		keyboardListener = EventListenerKeyboard::create();
		keyboardListener->onKeyPressed = CC_CALLBACK_2(DialogLayer::onKeyPressed, this);
		keyboardListener->onKeyReleased = CC_CALLBACK_2(DialogLayer::onKeyReleased, this);
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
		ret = true;
	}while(0);

	return ret;
}

void DialogLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event)
{

}
void DialogLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_ENTER:
	{
		index++;
		if (index < 5)
		{
			this->removeChild(sprite);
			sprite = spriteVector.at(index);
			sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
			sprite->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
			this->addChild(sprite);
		}
		else
		{
			//下一个场景
			global->sceneIndex++;
			//test
			auto scene = GameScene::createScene();
			//auto scene = DialogScene::createScene();
			Director::sharedDirector()->replaceScene(CCTransitionFade::create(0, scene));
		}

		break;
	}
	default:
		break;
	}
}

Vector<Sprite*> DialogLayer::createDialogPic(const char* formatStr, int frameCount)
{
	Vector<Sprite*> pFrames;
	for (int i = 1; i <= frameCount; i++)
	{
		const char* imgName = String::createWithFormat(formatStr, i)->getCString();
		Sprite *pFrame = Sprite::createWithSpriteFrameName(imgName);
		pFrames.insert(i - 1, pFrame);
	}
	return pFrames;
}
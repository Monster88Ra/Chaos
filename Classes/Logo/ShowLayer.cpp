#include "ShowLayer.h"

USING_NS_CC;

ShowLayer::ShowLayer():inLogoStep(0)
{
	global->showLayer = this;
}

ShowLayer::~ShowLayer()
{

}

bool ShowLayer::init()
{
	bool ret = false;

	do{
		CC_BREAK_IF(!Layer::init());
		_visibleSize = Director::getInstance()->getVisibleSize();
		_visibleOrigin = Director::getInstance()->getVisibleOrigin();

		//预加载
		FileUtils::getInstance()->setSearchPaths(searchPaths);

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(sp_girlIdle);
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlRun.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlAttackABC.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlSkillA.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlSkillB.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlSkillC.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlBeAttack.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlDead.plist");
		// SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/9Monster.plist");
		// SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/9Monster.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlBeAttackFly.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlBeAttackFall.plist");
		// SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/9MonsterBeAttackFly.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Boss/23Monster.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Monsters/9Monster.plist");
		//story&logo
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Story/story_logo.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Op/op_1.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Op/op_2.plist");

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Effects/deadFire.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Effects/ultimateSkill1.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Effects/ultimateSkill2.plist");
		//effect sound & background sound
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/hit_cut01.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/Bladeblink.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/BladeBig2.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/Swordrotate.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/woman_atked2a.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/hbnz_atked1.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/BladeBig1.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/BladeBig2.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/BladeBig3.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/op.wav"); 
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("Sound/Login2.mp3");

		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sound/Battle3_Loop.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sound/City1_Loop.mp3"); 
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Sound/BossBattle1_Loop.mp3");
		

		sprite = Sprite::create("logo.png");
		sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
		sprite->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));

		
		this->addChild(sprite);

		keyboardListener = EventListenerKeyboard::create();
		keyboardListener->onKeyPressed = CC_CALLBACK_2(ShowLayer::onKeyPressed, this);
		keyboardListener->onKeyReleased = CC_CALLBACK_2(ShowLayer::onKeyReleased, this);
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

		ret = true;
	} while (0);

	return ret;
}

Animation* ShowLayer::createAttackAnimation(const char* formatStr, int frameCountBegan, int frameCountEnd, int fps)
{
	//通过frameCountBegan,frameCountEnd从SpriteFrameCache中创建一个动作
	Vector<SpriteFrame*> pFrames;
	for (int i = frameCountBegan; i < frameCountEnd; i++)
	{
		const char* imgName = String::createWithFormat(formatStr, i)->getCString();
		SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		pFrames.insert(i - frameCountBegan, pFrame);
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
}

void ShowLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{

}


void ShowLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event)
{
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_ENTER:
	{
		if (0 == inLogoStep)
		{
			inLogoStep++;

			Animation *logoAnim_1 = createAttackAnimation("op_%03d.png", 1, 40, 13);
			Animation *logoAnim_2 = createAttackAnimation("op_%03d.png", 41, 80, 13);

			sprite->runAction(Sequence::create(
				CallFuncN::create(CC_CALLBACK_1(ShowLayer::opBGMCallBackAction, this)),
				Animate::create(logoAnim_1),
				Animate::create(logoAnim_2),
				CallFuncN::create(CC_CALLBACK_1(ShowLayer::opEndCallBack, this)),
				NULL));
		}
		else if (1 == inLogoStep)
		{
			sprite->stopAllActions();
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();//停止全部音效

			//播放音效
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Login2.mp3",true);

			inLogoStep++;

			this->removeChild(sprite);
			sprite = Sprite::createWithSpriteFrameName("chapter0.png");
			sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
			sprite->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
			this->addChild(sprite);
		}
		else if (2 == inLogoStep)
		{
			inLogoStep++;

			this->removeChild(sprite);
			sprite = Sprite::createWithSpriteFrameName("chapter1.png");
			sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
			sprite->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
			this->addChild(sprite);
		}
		else
		{ 
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();//停止全部音效
			//test
			auto scene = GameScene::createScene();
			//auto scene = DialogScene::createScene();
			Director::sharedDirector()->replaceScene(CCTransitionFade::create(0, scene));
		}

		break;
	}
	default:
	{
		break;
	}
	}
}

void ShowLayer::opBGMCallBackAction(Node *pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/op.wav");
}

/*
void ShowLayer::sceneCallBack(Object* pSender)
{
	//this->removeChild(sprite);

	auto scene = GameScene::createScene();
	Director::sharedDirector()->replaceScene(CCTransitionFade::create(2, scene));
}
*/
//op 结束后回调
void ShowLayer::opEndCallBack(Node *pSender)
{
	sprite->stopAllActions();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();//停止全部音效
	//播放音效
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Login2.mp3", true);

	inLogoStep++;

	this->removeChild(sprite);
	sprite = Sprite::createWithSpriteFrameName("chapter0.png");
	sprite->setAnchorPoint(Vec2(0.5f, 0.5f));
	sprite->setPosition(Vec2(_visibleSize.width / 2, _visibleSize.height / 2));
	this->addChild(sprite);
}
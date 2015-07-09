#include "GameLayer.h"

USING_NS_CC;

GameLayer::GameLayer() :m_pdeadfire(NULL)
{
	global->gameLayer = this;
}

GameLayer::~GameLayer()
{
	CC_SAFE_RELEASE_NULL(m_pdeadfire);
}

bool GameLayer::init()
{
	bool ret = false;
	do{
		 CC_BREAK_IF( !Layer::init());
		 _visibleSize  = Director::getInstance()->getVisibleSize();
		 _visibleOrigin = Director::getInstance()->getVisibleOrigin();
		 /*
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
		 */

		 //testing
		 //global->sceneIndex++;

		

		 auto map = MapLayer::create();
		 this->addChild(map,100);
		 this->addHero();
		
		
		 if (global->sceneInfoVector[global->sceneIndex]->bossFormatStr == NULL)
		 {
			 global->enemiesAllDie = true;
			 this->addaddEnemies(5);
		 }
		 else
		 {
			 this->addBoss(1);
		 }
		

		 global->deadFire = Sprite::createWithSpriteFrameName("EFFECT0003.png");
		 global->deadFire->setVisible(false);

		 this->addChild(global->deadFire,202);
		 this->scheduleUpdate();

         ret = true;
	}while(0);
	return ret;
}

void GameLayer::update(float dt)
{
	this->updateHero(dt);
	if (global->sceneInfoVector[global->sceneIndex]->bossFormatStr == NULL)
	{
		this->updateEnemies(dt);
	}
	else
	{
		this->updateBoss(dt);
	}
	
	
	//debug
	CCLOG("****DEBUG*** hero curr MP is %f", global->hero->getCurrMagicPoint());
}
void GameLayer::updateHero(float dt)
{
	m_pHero->updateSelf();//自更新状态
}

void GameLayer::addHero()
{
	m_pHero = Hero::create();
	m_pHero->setPosition(_visibleOrigin + Vec2(160, 160));
	m_pHero->runIdleAction();
	//属性设置
	HeroMessage heroMsg = global->heroInfo;

	m_pHero->setDamageStrength(heroMsg.damageStrength);
	m_pHero->setSumLifeValue(heroMsg.lifeValue);
	m_pHero->setCurtLifeValue(m_pHero->getSumLifeValue());
	m_pHero->setSumMagicPoint(heroMsg.magicValue);
	m_pHero->setCurrMagicPoint(0.0f);

	m_pHero->setLocalZOrder(_visibleSize.height - m_pHero->getPositionY());
	this->addChild(m_pHero);
}



void GameLayer::addaddEnemies(int number)
{
	m_pEnemies = __Array::createWithCapacity(number);
	m_pEnemies->retain();
	for (int i = 0; i<number; i++)
	{
		Enemy *pEnemy = Enemy::create();
		pEnemy->setPosition(Vec2(random(_visibleSize.width / 2, _visibleSize.width), 70));
		pEnemy->runWalkAction();
		pEnemy->setLocalZOrder(_visibleSize.height - pEnemy->getPositionY());

		//属性设置
		pEnemy->setVelocity(Vec2(0.5f, 0.5f));
		pEnemy->setEyeArea(300);
		pEnemy->setAttackArea(80);
		//pEnemy->setDamageStrenth(5);
		pEnemy->setSumLifeValue(100);
		pEnemy->setCurtLifeValue(m_pHero->getSumLifeValue());

		m_pEnemies->addObject(pEnemy);
		this->addChild(pEnemy, 0);
	}
	global->enemies = m_pEnemies;

	//停止全部音效
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	//停止背景音乐
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	//播放音效
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/Battle3_Loop.mp3", true);
}

void GameLayer::addBoss(int number)
{
	m_pEnemies = __Array::createWithCapacity(number);
	m_pEnemies->retain();
	for (int i = 0; i < number; i++)
	{
		m_pBoss = Boss::create();
		m_pBoss->setPosition(Vec2(200.0f, 200.0f));
		m_pBoss->runWalkAction();
		m_pBoss->setLocalZOrder(_visibleSize.height - m_pBoss->getPositionY());


		//属性设置
		m_pBoss->setVelocity(Vec2(0.5f, 0.5f));
		m_pBoss->setEyeArea(500);
		m_pBoss->setAttackArea(80);
		//pEnemy->setDamageStrenth(5);
		m_pBoss->setSumLifeValue(100);
		m_pBoss->setCurtLifeValue(m_pBoss->getSumLifeValue());

		m_pEnemies->addObject(m_pBoss);

		this->addChild(m_pBoss, 0);
	}
	global->bosses = m_pEnemies;

	//停止全部音效
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
	//停止背景音乐
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	//播放音效
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/BossBattle1_Loop.mp3", true);
}

void GameLayer::updateEnemies(float dt)
{
	Ref *Obj = NULL;
	Vec2 distance = Vec2::ZERO;
	CCARRAY_FOREACH(m_pEnemies, Obj)//遍历所有的怪物
	{
		Enemy *pEnemy = (Enemy*)Obj;
		pEnemy->updateSelf();//自更新状态

		//如果死了就移除他们
		if (pEnemy->getDeadAction()->isDone())
			m_pEnemies->removeObject(pEnemy);
	}
}

void GameLayer::updateBoss(float dt)
{
	m_pBoss->updateSelf();
}
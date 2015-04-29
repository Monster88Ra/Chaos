#include "GameLayer.h"
#include "Other\Resources.h"
USING_NS_CC;

GameLayer::GameLayer()
{
	global->gameLayer = this;
}

GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
	bool ret = false;
	do{
		 CC_BREAK_IF( !Layer::init());
		 _visibleSize  = Director::getInstance()->getVisibleSize();
		 _visibleOrigin = Director::getInstance()->getVisibleOrigin();
		 std::string path = searchPaths[5];
		 SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlIdle.plist");
		 SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlRun.plist");
		 SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlAttackABC.plist");
		 SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlSkillA.plist");
		 SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlSkillB.plist");
		 SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Role/Girl/girlSkillC.plist");
		 auto map = MapLayer::create();
		 
		 this->addChild(map,100);
		 this->addHero();
		 this->scheduleUpdate();

         ret = true;
	}while(0);
	return ret;
}

void GameLayer::update(float dt)
{
	this->updateHero(dt);
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
	m_pHero->setDamageStrength(15);
	m_pHero->setSumLifeValue(200);
	m_pHero->setCurtLifeValue(m_pHero->getSumLifeValue());

	m_pHero->setLocalZOrder(_visibleSize.height - m_pHero->getPositionY());
	this->addChild(m_pHero);
}
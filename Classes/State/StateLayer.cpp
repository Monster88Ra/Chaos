#include "StateLayer.h"

USING_NS_CC;

StateLayer::StateLayer() :m_ultimateskill(NULL)
{
	global->stateLayer = this;
}

StateLayer::~StateLayer()
{
	CC_SAFE_RELEASE_NULL(m_ultimateskill);
}

bool StateLayer::init()
{
	bool ret = false;
	do{
		CC_BREAK_IF( !Layer::init() );
		auto Hp = HpShow::create();
		auto Magic = MagicShow::create();
		this->addChild(Hp);
		this->addChild(Magic);
		
		global->ultimateSkill = Sprite::createWithSpriteFrameName("4EFFECT50001.png");
		global->ultimateSkill->setVisible(false);
		global->ultimateSkill->setAnchorPoint(Vec2(0, 0));
		this->addChild(global->ultimateSkill);

		ret = true;
	}while(0);

	return ret;
}



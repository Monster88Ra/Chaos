#include "MagicShow.h"

MagicShow::MagicShow()
{

}

MagicShow::~MagicShow()
{

}

bool MagicShow::init()
{
	bool ret = false;
	do{
		CC_BREAK_IF(!Node::init());
		auto visibleSize = Director::getInstance()->getVisibleSize();
		Sprite* HeroMagic = Sprite::create("magicBG.png");
		HeroMagic->setPosition(HeroMagic->getContentSize().width / 2,
			visibleSize.height - HeroMagic->getContentSize().height*2);
		this->addChild(HeroMagic);

		m_preal = ProgressTimer::create(Sprite::create("magic.png"));
		m_preal->setType(ProgressTimer::Type::BAR);
		m_preal->setMidpoint(Point(0, 0.5));
		m_preal->setBarChangeRate(Point(1.0, 0));
		m_preal->setPosition(HeroMagic->getContentSize() / 2);
		m_preal->setPercentage(0);
		HeroMagic->addChild(m_preal);

		this->scheduleUpdate();
		ret = true;

	} while (0);

	return ret;
}

void MagicShow::update(float dt)
{
	m_preal->setPercentage((float)global->hero->getCurrMagicPoint() / global->hero->getSumMagicPoint() * 100);
}
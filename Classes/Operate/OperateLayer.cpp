#include "OperateLayer.h"

USING_NS_CC;
using namespace std;

OperateLayer::OperateLayer()
{
	global->operateLayer = this;
}

OperateLayer::~OperateLayer()
{
}

bool OperateLayer::init()
{
	bool ret = false;
	do{
		CC_BREAK_IF( !Layer::init() );
		//��������ҡ��
		auto m_pjoystick = Joystick::create();
		m_pjoystick->setJoystick(Vec2(50, 50));
		this->addChild(m_pjoystick);

		//�������ⰴ��
		auto visibleSize = Director::getInstance()->getVisibleSize();
		//����attackItemͼ��
		auto attackItem = MenuItemImage::create("attackbuttonNormal.png", "attackbuttonSelected.png", CC_CALLBACK_1(OperateLayer::attackButton, this));

		//ͼ���С
		attackItem->setScale(1.5);
		//attackItem->setContentSize(Size(50,50));

		//ͼ�����
		attackItem->setPosition(visibleSize.width - attackItem->getContentSize().width / 2 - 50, attackItem->getContentSize().height / 2 + 20);

		auto menu = Menu::create(attackItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 100);

		global->skillA = SkillButton::create("SkillButton.png", 3.0f);
		global->skillA->setPosition(attackItem->getPosition() - Vec2(50, 0));
		this->addChild(global->skillA);

		ret = true;
	}while(0);

	return ret;
}

void OperateLayer::attackButton(Ref *pSender)
{
	global->hero->onAttack(1);
}


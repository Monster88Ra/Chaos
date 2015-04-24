#include "Hero.h"
#include "Other\Resources.h"
Hero::Hero()
{
	global->hero = this;
}

Hero::~Hero()
{
	
}

bool Hero::init()
{
	bool ret = false;
	do
	{

		// idle第一张图 
		this->initWithSpriteFrameName(si_4IDLE0001);
		//站立时播放动画
		Animation *idleAnim = this->createNomalAnimation("4IDLE%04d.png", 24, 5);
		this->setIdleAction(RepeatForever::create(Animate::create(idleAnim)));

		//行走
		Animation *walkAnim = this->createNomalAnimation("4RUN%04d.png", 18, 12);
		this->setWalkAction(RepeatForever::create(Animate::create(walkAnim)));

		//普通攻击A，分出招和收招，期间夹杂攻击判定.自己可以通过调节fps控制出招速度之类的
		Animation *attackAnima1 = this->createAttackAnimation("4ATTACK%05d.png",1,5,10);
		Animation *attackAnima2 = this->createAttackAnimation("4ATTACK%05d.png", 5, 9, 15);
		this->setNomalAttackA(Sequence::create(
			Animate::create(attackAnima1),
			//CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(attackAnima2),
			Role::createIdleCallbackFunc(),
			NULL));


		//普攻B
		Animation *attackAnimb1 = this->createAttackAnimation("4ATTACK1%04d.png", 1, 5, 10);
		Animation *attackAnimb2 = this->createAttackAnimation("4ATTACK1%04d.png", 5, 11, 15);
		this->setNomalAttackB(Sequence::create(
			Animate::create(attackAnimb1),
			//CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(attackAnimb2),
			Role::createIdleCallbackFunc(),
			NULL));

		//普攻C
		Animation *attackAnimc1 = this->createAttackAnimation("4ATTACK2%04d.png", 1, 4, 10);
		Animation *attackAnimc2 = this->createAttackAnimation("4ATTACK2%04d.png", 4, 7, 15);
		this->setNomalAttackC(Sequence::create(
			Animate::create(attackAnimc1),
			//CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(attackAnimc2),
			Role::createIdleCallbackFunc(),
			NULL));

		//普攻D
		Animation *attackAnimd1 = this->createAttackAnimation("4ATTACK3%04d.png", 1, 6, 10);
		Animation *attackAnimd2 = this->createAttackAnimation("4ATTACK3%04d.png", 6, 13, 15);
		this->setNomalAttackD(Sequence::create(
			Animate::create(attackAnima1),
			Animate::create(attackAnima2),
			Animate::create(attackAnimb1),
			Animate::create(attackAnimb2),
			Animate::create(attackAnimc1),
			Animate::create(attackAnimc2),
			Animate::create(attackAnimd1),
			//CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			Animate::create(attackAnimd2),
			Role::createIdleCallbackFunc(),
			NULL));

		//连续攻击
		/*
		this->setComboAttack(Sequence::create(
			Animate::create(attackAnima1),
			Animate::create(attackAnima2),
			Animate::create(attackAnimb1),
			Animate::create(attackAnimb2),
			Animate::create(attackAnimc1),
			Animate::create(attackAnimc2),
			Animate::create(attackAnimd1),
			Animate::create(attackAnimd2),
			Role::createIdleCallbackFunc(),
			NULL));
		*/
		ret = true;
	} while (0);
	return ret;
}

void Hero::onMove(Vec2  direction, float distance)
{
	//设置朝向
	if (direction.x < 0)
		setRoleDirection(true);
	else if (direction.x > 0)
		setRoleDirection(false);
	// 不是很好的办法
	if (0 == direction.y)
		this->setFlippedX(direction.x < 0 ? true : false);
	this->runWalkAction();
	Vec2 velocity = direction * (distance < 33 ? 1 : 3);
	
	this->setVelocity(velocity);
}

void Hero::onStop()//站立
{
	this->runIdleAction();
	this->setVelocity(Vec2::ZERO);
}

void Hero::onAttack(int number)//执行攻击
{
	//this->setAnchorPoint(Point(0.0f, 0.0f));
	switch (number)
	{
	case ACTION_STATE_NOMAL_ATTACK_D:
	{

		this->setFlippedX(getRoleDirection());
		this->runNomalAttackD();
		break;
	}
	default:
	{
		//CCLOG("%d",getRoleDirection());
		this->setFlippedX(getRoleDirection());
		this->runNomalAttackA();
		break;
	}
		
	}
		
}

void Hero::updateSelf()//刷新自己
{
	if (this->getCurrActionState() == ACTION_STATE_WALK)
	{
		Vec2 currentP = this->getPosition();				//当前坐标
		Vec2 expectP = currentP + this->getVelocity();	//期望坐标
		Vec2 actualP = expectP;							//实际坐标
		float mapWidth = global->tileMap->getContentSize().width;   //整张地图宽度
		//float mapHeight = global->tileMap->getContentSize().height; //整张地图的高度
		float herofat = this->getBodyBox().actual.size.width / 2;     //角色横向宽度,以受攻击的bodybox为准
		//不能跑出前景图
		if ( false == (global->tileAllowMove(expectP)))
		{
			actualP = currentP;
		}
		//不能跑出地图外面
		if (expectP.x < herofat || expectP.x >= mapWidth - herofat)
		{
			actualP.x = currentP.x;
		}

		this->setPosition(actualP);
		this->setLocalZOrder(Director::getInstance()->getVisibleSize().height - this->getPositionY());
	}
}

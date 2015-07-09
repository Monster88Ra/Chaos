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
		//设置锚点
		this->setAnchorPoint(Vec2(0.5, 0.5));

		//初始化AnimationIsDone
		setAnimationIsDone(false);
		
		// idle第一张图 
		this->initWithSpriteFrameName(si_4IDLE0001);
		//站立时播放动画
		Animation *idleAnim = this->createNomalAnimation("4IDLE%04d.png", 24, 20);
		this->setIdleAction(RepeatForever::create(Animate::create(idleAnim)));

		//行走
		Animation *walkAnim = this->createNomalAnimation("4RUN%04d.png", 18, 20);
		this->setWalkAction(RepeatForever::create(Animate::create(walkAnim)));

		//普通攻击A，分出招和收招，期间夹杂攻击判定.自己可以通过调节fps控制出招速度之类的
		Animation *attackAnima1 = this->createAttackAnimation("4ATTACK%05d.png",1,5,20);
		Animation *attackAnima2 = this->createAttackAnimation("4ATTACK%05d.png", 5, 9, 20);
		this->setNomalAttackA(Sequence::create(
			CallFuncN::create(CC_CALLBACK_1(Hero::normalAttackSoundEffectCallBackAction, this)),
			Animate::create(attackAnima1),
			CallFuncN::create(CC_CALLBACK_1(Hero::normalAttackCallBackAction, this)),
			Animate::create(attackAnima2),
			Role::createIdleCallbackFunc(),
			NULL));
		


		//普攻B
		Animation *attackAnimb1 = this->createAttackAnimation("4ATTACK1%04d.png", 1, 5, 10);
		Animation *attackAnimb2 = this->createAttackAnimation("4ATTACK1%04d.png", 5, 11, 15);
		this->setNomalAttackB(Sequence::create(
			CallFuncN::create(CC_CALLBACK_1(Hero::normalAttackSoundEffectCallBackAction, this)),
			Animate::create(attackAnimb1),
			CallFuncN::create(CC_CALLBACK_1(Hero::normalAttackCallBackAction, this)),
			Animate::create(attackAnimb2),
			Role::createIdleCallbackFunc(),
			NULL));

		//普攻C
		Animation *attackAnimc1 = this->createAttackAnimation("4ATTACK2%04d.png", 1, 4, 10);
		Animation *attackAnimc2 = this->createAttackAnimation("4ATTACK2%04d.png", 4, 7, 15);
		this->setNomalAttackC(Sequence::create(
			CallFuncN::create(CC_CALLBACK_1(Hero::normalAttackSoundEffectCallBackAction, this)),
			Animate::create(attackAnimc1),
			CallFuncN::create(CC_CALLBACK_1(Hero::normalAttackCallBackAction, this)),
			Animate::create(attackAnimc2),
			Role::createIdleCallbackFunc(),
			NULL));

		//普攻D
		Animation *attackAnimd1 = this->createAttackAnimation("4ATTACK3%04d.png", 1, 6, 20);
		Animation *attackAnimd2 = this->createAttackAnimation("4ATTACK3%04d.png", 6, 13, 20);
		this->setNomalAttackD(Sequence::create(
			/*
			Animate::create(attackAnima1),
			Animate::create(attackAnima2),
			Animate::create(attackAnimb1),
			Animate::create(attackAnimb2),
			Animate::create(attackAnimc1),
			Animate::create(attackAnimc2),
			*/
			CallFuncN::create(CC_CALLBACK_1(Hero::normalAttackSoundEffectCallBackAction, this)),
			Animate::create(attackAnimd1),
			//CallFuncN::create(CC_CALLBACK_1(Hero::attackCallBackAction,this)),
			CallFuncN::create(CC_CALLBACK_1(Hero::normalAttackCallBackAction, this)),
			Animate::create(attackAnimd2),
			Role::createIdleCallbackFunc(),
			NULL));
		
		//skill A
		Animation *skillAnima1 = this->createAttackAnimation("4EFFECT1%04d.png",1,21,20);
		Animation *skillAnima2 = this->createAttackAnimation("4EFFECT1%04d.png",21,30,20);
		this->setSkillAttackA(Sequence::create(
			CallFuncN::create(CC_CALLBACK_1(Hero::skillAttackASoundEffectCallBackAction, this)),
			Animate::create(skillAnima1),
			CallFuncN::create(CC_CALLBACK_1(Hero::skillAttackCallBackAction, this)),
			Animate::create(skillAnima2),
			Role::createIdleCallbackFunc(),
			NULL));

		//skill B
		Animation *skillAnimb1 = this->createAttackAnimation("4EFFECT2%04d.png", 1, 19, 20);
		Animation *skillAnimb2 = this->createAttackAnimation("4EFFECT2%04d.png", 19, 27, 20);
		this->setSkillAttackB(Sequence::create(
			CallFuncN::create(CC_CALLBACK_1(Hero::skillAttackBSoundEffectCallBackAction_1, this)),
			Animate::create(skillAnimb1),
			CallFuncN::create(CC_CALLBACK_1(Hero::skillAttackCallBackAction, this)),
			CallFuncN::create(CC_CALLBACK_1(Hero::skillAttackBSoundEffectCallBackAction_2, this)),
			Animate::create(skillAnimb2),
			Role::createIdleCallbackFunc(),
			NULL));

		//skill C
		Animation *skillAnimc1 = this->createAttackAnimation("4EFFECT4%04d.png", 1, 22, 20);
		Animation *skillAnimc2 = this->createAttackAnimation("4EFFECT4%04d.png", 22, 32, 20);
		this->setSkillAttackC(Sequence::create(
			CallFuncN::create(CC_CALLBACK_1(Hero::skillAttackCSoundEffectCallBackAction_1, this)),
			Animate::create(skillAnimc1),
			CallFuncN::create(CC_CALLBACK_1(Hero::skillAttackCallBackAction, this)),
			CallFuncN::create(CC_CALLBACK_1(Hero::skillAttackCSoundEffectCallBackAction_2, this)),
			Animate::create(skillAnimc2),
			Role::createIdleCallbackFunc(),
			NULL));

		//被攻击状态
		Animation *hurtAnim = this->createNomalAnimation("4BEATTACK%04d.png",7,20);
		this->setHurtAction(Sequence::create(
			CallFuncN::create(CC_CALLBACK_1(Hero::beAttackedSoundEffectCallBackAction, this)),
			Animate::create(hurtAnim),
			Role::createIdleCallbackFunc(),
			NULL));

		
		//被攻飞倒地
		//Animation *hurtFlyAnim = this->createNomalAnimation("4BEATTACKFLY%04d.png", 6, 20);
		Animation *onGroundAnim = this->createNomalAnimation("4DEAD%04d.png", 3, 6);//倒地动画
		Animation *hurtFlyAnim = this->createNomalAnimation("4BEATTACKFLY%04d.png", 6, 10);

		Point p1 = Point(200, 100), p2 = Point(200, 300), p3 = Point(300, 0);
		auto bezierAnimFlyToRight = createBezierAnim(p1, p2, p3, hurtFlyAnim);
		auto bezierAnimFlyToLeft = createBezierAnim(Point(-p1.x, p1.y), Point(-p2.x, p2.y), Point(-p3.x, p3.y), hurtFlyAnim);
		this->setHurtFlyActionRight(Sequence::create(
			CallFuncN::create(CC_CALLBACK_1(Hero::beAttakedFlyingSoundEffectCallBackAction, this)),
			bezierAnimFlyToRight,
			Animate::create(onGroundAnim),
			Role::createIdleCallbackFunc(),
			NULL));
		this->setHurtFlyActionLeft(Sequence::create(
			CallFuncN::create(CC_CALLBACK_1(Hero::beAttakedFlyingSoundEffectCallBackAction, this)),
			bezierAnimFlyToLeft,
			Animate::create(onGroundAnim),
			Role::createIdleCallbackFunc(),
			NULL));

		//闪现
		Animation *flashAnim = createAttackAnimation("4EFFECT1%04d.png",24,28,10);
		//MoveBy *move = MoveBy::create(100, Vec2(30, 0) );
		//Spawn *flashTo = Spawn::create(move, Animate::create(flashAnim), NULL);
		this->setFlashAction(Sequence::create(
			Animate::create(flashAnim),
			Role::createIdleCallbackFunc(),
			NULL));

		///死亡状态
		Animation *deadAnim = this->createNomalAnimation("4DEAD%04d.png", 3, 6);
		this->setDeadAction(Sequence::create(
			Animate::create(deadAnim),
			Blink::create(3, 9),
			NULL));

		
		
		
		//碰撞盒子设定
		HeroMessage herMsg = global->heroInfo;
		Vec2 bodyBoxOrigin(herMsg.bodyBoxOriginX, herMsg.bodyBoxOriginY);
		Size bodyBoxSize(herMsg.bodyBoxSizeX,herMsg.bodyBoxSizeY);
		Vec2 hitBoxOrigin(herMsg.hitBoxOriginX,herMsg.hitBoxOriginY);
		Size hitBoxSize(herMsg.hitBoxSizeX,herMsg.hitBoxSizeY);

		this->m_bodyBox = this->createBoundingBox(bodyBoxOrigin, bodyBoxSize);
		this->m_hitBox = this->createBoundingBox(hitBoxOrigin, hitBoxSize);

		//debug 参数
		//ccConfig.h
		//debug  
		
		auto rectBodyBox = DrawNode::create();
		rectBodyBox->setTag(0xFF);
		Debug_DrawBoundingBox(rectBodyBox, m_bodyBox, Color4F(1.0f, 0.3f, 0.3f, 0.5f));
		addChild(rectBodyBox);

		auto rectHitBox = DrawNode::create();
		rectHitBox->setTag(0xFE);
		Debug_DrawBoundingBox(rectHitBox, m_hitBox, Color4F(0.3f, 1.0f, 0.3f, 0.5f));
		addChild(rectHitBox);
		
		//初始化时间
		preTime = 0;
		nextTime = 0;
		//初始化hitCount
		hitCount = 0;

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

void Hero::onFlash()
{
	this->setFlippedX(getRoleDirection());
	Vec2 expectP;
	if (this->getRoleDirection())
	{
		expectP = this->getPosition() - Vec2(100, 0);
	}
	else
	{
		expectP = this->getPosition() + Vec2(100, 0);
	}
	if (false == (global->tileAllowMove(expectP)))
	{
		return;
	}
	
	this->setPosition(expectP);
	this->runFlashAction();
}

void Hero::onStop()//站立
{

	this->runIdleAction();
	this->setVelocity(Vec2::ZERO);
}

void Hero::onAttack(int number)//执行攻击
{
	//设置锚点
	//this->setAnchorPoint(Point(0.0f, 0.0f));
	switch (number)
	{
	case ACTION_STATE_NOMAL_ATTACK_B:
	{
		this->setFlippedX(getRoleDirection());
		this->runNomalAttackB();
		break;
	}
	case ACTION_STATE_NOMAL_ATTACK_C:
	{
		this->setFlippedX(getRoleDirection());
		this->runNomalAttackC();
		break;
	}
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

void Hero::onSkill(int number)
{
	
	if (this->getCurrMagicPoint() < 15)
	{
		return;
	}
	
	this->setCurrMagicPoint(this->getCurrMagicPoint() - 15);
	switch (number)
	{
	case ACTION_STATE_SKILL_ATTACK_A:
	{
		this->setFlippedX(getRoleDirection());
		this->runSkillAttackA();
		global->skillA->ClickCallBack(this);
		break;
	}
	case ACTION_STATE_SKILL_ATTACK_B:
	{
		this->setFlippedX(getRoleDirection());
		this->runSkillAttackB();
		break;
	}
	case ACTION_STATE_SKILL_ATTACK_C:
	{
		this->setFlippedX(getRoleDirection());
		this->runSkillAttackC();
		break;
	}
			
	default:
		break;
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

	if (global->enemiesAllDie == true && this->getPosition().x > 2300.0f)
	{
		
		if ( global->sceneIndex == 0)
		{
			auto scene = DialogScene::createScene();
			//auto scene = DialogScene::createScene();
			Director::sharedDirector()->replaceScene(CCTransitionFade::create(0, scene));
		}
	}
}

void Hero::normalAttackCallBackAction(Node* pSender)
{
	/*
	//play sound effect
	if (this->currActionState == ACTION_STATE_NOMAL_ATTACK_A || 
		this->currActionState == ACTION_STATE_NOMAL_ATTACK_B ||
		this->currActionState == ACTION_STATE_NOMAL_ATTACK_C ||
		this->currActionState == ACTION_STATE_NOMAL_ATTACK_D )
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/BladeBig2.mp3");
	*/

	__Array *pEnemies;
	if (global->sceneInfoVector[global->sceneIndex]->bossFormatStr == NULL)
	{
		pEnemies = global->enemies;
	}
	else
	{
		pEnemies = global->bosses;
	}

	Ref *enemyObj = NULL;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//判断是否可以放大招
	if (this->getCurrMagicPoint() >= 100)
	{
		addUltimateSkill();
		
		this->setCurrMagicPoint(0.0f);
	}

	CCARRAY_FOREACH(pEnemies, enemyObj)
	{
		Enemy *pEnemy = (Enemy*)enemyObj;
		if (fabsf(this->getPosition().y - pEnemy->getPosition().y < 20))
		{
			Rect attackRect = m_hitBox.actual;//英雄攻击区域
			Rect hurtRect = pEnemy->getBodyBox().actual;//怪物受伤区域
			if (attackRect.intersectsRect(hurtRect))
			{
				pEnemy->setAllowMove(false);
				//此处可处理怪物被攻击后的后续,产生伤害数字
				int damage = random(this->getDamageStrength()*0.7, this->getDamageStrength()*1.3);
				hitCounter();
				Vec2 point = pEnemy->getBodyBox().actual.origin;
				damageDisplay(damage, Vec2(point.x , point.y + 80));
				pEnemy->runHurtAction();
				enemyBloodDisplay(Vec2(point.x-10,point.y-10));
				

				if (this->getCurrActionState() == ACTION_STATE_NOMAL_ATTACK_C || this->getCurrActionState() == ACTION_STATE_NOMAL_ATTACK_D)
				{
					if (getRoleDirection())
					{
						pEnemy->setFlippedX(false);
						pEnemy->runHurtFlyLeftAction();
					}
					else
					{
						pEnemy->setFlippedX(true);
						pEnemy->runHurtFlyRightAction();
					}
				}
				//pEnemy->runHurtFlyLeftAction();

				if (hitCount > 1)
				{
					combosDisplay(hitCount, Vec2(visibleSize.width *0.15, visibleSize.height * 0.75));
				}

				
				
				pEnemy->setCurtLifeValue(pEnemy->getCurtLifeValue() - damage);
				if (pEnemy->getCurtLifeValue() <= 0)
				{
					pEnemy->runDeadAction();
					pEnemy->setBodyBox(createBoundingBox(Vec2::ZERO, Size::ZERO));
					pEnemy->setOpacity(124);

					float temp = this->getPosition().x - visibleSize.width / 2;
					float destX = (temp > 0) ? temp : 0;
					addDeadFire(Vec2(destX,visibleSize.height) ,pEnemy->getPosition());
					pEnemy->setVisible(false);
					
				}
			}
		}
	}

	CCARRAY_FOREACH(pEnemies, enemyObj)
	{
		Enemy *pEnemy = (Enemy*)enemyObj;
		if (pEnemy->getCurrActionState() != ACTION_STATE_DEAD)
		{
			break;
		}
		global->enemiesAllDie = true;
	}
	//CCLOG("%d", enemiesAllDie);
}

void Hero::skillAttackCallBackAction(Node* pSender)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	__Array *pEnemies;
	if (global->sceneInfoVector[global->sceneIndex]->bossFormatStr == NULL)
	{
		pEnemies = global->enemies;
	}
	else
	{
		pEnemies = global->bosses;
	}

	Ref *enemyObj = NULL;
	CCARRAY_FOREACH(pEnemies, enemyObj)
	{
		Enemy *pEnemy = (Enemy*)enemyObj;
		if (fabsf(this->getPosition().y - pEnemy->getPosition().y < 30))
		{

			Rect attackRect = m_hitBox.actual;//英雄攻击区域
			Rect hurtRect = pEnemy->getBodyBox().actual;//怪物受伤区域
			//需要做判断
			attackRect.setRect(attackRect.origin.x, attackRect.origin.y, attackRect.getMaxX() * 3, attackRect.getMaxY());//重新设置攻击范围
			if (attackRect.intersectsRect(hurtRect))
			{
				pEnemy->setAllowMove(false);
				//此处可处理怪物被攻击后的后续,产生伤害数字
				int damage = random(this->getDamageStrength()*0.7, this->getDamageStrength()*1.3);
				Vec2 point = pEnemy->getBodyBox().actual.origin;
				damageDisplay(damage, Vec2(point.x, point.y + 80));

				if (!getRoleDirection())
				{
					pEnemy->setFlippedX(true);
					pEnemy->runHurtFlyRightAction();
				}
				else
				{
					pEnemy->setFlippedX(false);
					pEnemy->runHurtFlyLeftAction();
				}

				pEnemy->setCurtLifeValue(pEnemy->getCurtLifeValue() - damage);
				if (pEnemy->getCurtLifeValue() <= 0)
				{
					pEnemy->runDeadAction();
					pEnemy->setBodyBox(createBoundingBox(Vec2::ZERO, Size::ZERO));
					pEnemy->setOpacity(124);

					float temp = this->getPosition().x - visibleSize.width / 2;
					float destX = (temp > 0) ? temp : 0;
					addDeadFire(Vec2(destX, visibleSize.height), pEnemy->getPosition());
					pEnemy->setVisible(false);

				}
			}
		}
	}

	CCARRAY_FOREACH(pEnemies, enemyObj)
	{
		Enemy *pEnemy = (Enemy*)enemyObj;
		if (pEnemy->getCurrActionState() != ACTION_STATE_DEAD)
		{
			break;
		}
		global->enemiesAllDie = true;
	}
	//CCLOG("%d", enemiesAllDie);

}

//数字淡出回调
void Hero::FontsCallBackAction(Node* pSender)
{
	global->gameLayer->removeChild(pSender);

}

//连击计数回调
void Hero::hitCounter()
{
	nextTime = millisecondNow();
	if (nextTime - preTime < 2000)
	{
		hitCount++;
	}
	else
	{
		hitCount = 0;
	}

	CCLOG("newxtTime - preTime %d", nextTime - preTime);
	preTime = nextTime;
	CCLOG("hitCout is %d", hitCount);
}

void Hero::damageDisplay(int number, Vec2 point)
{
	//设置字体
	TTFConfig labelConfig;
	labelConfig.fontFilePath = "fonts/Marker Felt.ttf";
	labelConfig.fontSize = 24;
	labelConfig.glyphs = GlyphCollection::DYNAMIC;
	labelConfig.outlineSize = 0;
	labelConfig.customGlyphs = nullptr;
	labelConfig.distanceFieldEnabled = false;
	//数字动画
	auto atLabel = Label::createWithTTF(labelConfig,"");
	atLabel->setString(__String::createWithFormat("-%d", number)->getCString());
	atLabel->setColor(Color3B(255, 70, 30));
	atLabel->setPosition(point);
	global->gameLayer->addChild(atLabel, 200);
	FiniteTimeAction * callFuncN = CallFuncN::create(atLabel, callfuncN_selector(Hero::FontsCallBackAction));
	FiniteTimeAction *sequence = Sequence::create(
		//FadeIn::create(1.5f),
		ScaleTo::create(0.2f, 1.3f),
		MoveBy::create(0.2f, Vec2(0, 20)),
		FadeOut::create(0.5f),
		callFuncN,
		NULL);
	atLabel->runAction(sequence);
}

void Hero::enemyBloodDisplay(Vec2 point)
{
	//飘血特效
	ParticleSystem *particle = ParticleSystemQuad::create("Particle/TestPremultipliedAlpha.plist");
	particle->setPosition(point);
	particle->setAutoRemoveOnFinish(true);
	particle->setDuration(0.3f);
	global->gameLayer->addChild(particle, 200);
}

void Hero::addDeadFire(Vec2 dest, Vec2 enemy)
{
	Animation *effectIdleAnim = this->createAttackAnimation("EFFECT%04d.png", 3, 16, 10);
	Animation *effectMoveAnim = this->createAttackAnimation("EFFECT%04d.png", 1, 2, 5);
	auto MoveTo = Spawn::create(MoveTo::create(0.3f, dest), Animate::create(effectMoveAnim), NULL);

	global->gameLayer->setdeadFire(
		Sequence::create(
		Animate::create(effectIdleAnim),
		MoveTo,
		Animate::create(effectIdleAnim),
		CallFuncN::create(CC_CALLBACK_1(Hero::setDeadFireVisable, this)),
		NULL));
	global->deadFire->setScale(1.5f);
	global->deadFire->setPosition(enemy);
	global->deadFire->setVisible(true);
	
	global->deadFire->setFlippedX(true);
	
	global->deadFire->runAction(global->gameLayer->getdeadFire());

	//global->gameLayer->removeChild(global->gameLayer->deadFire);
	
}
//添加终极技能特效
void Hero::addUltimateSkill()
{
	Animation *ultimateSkillAnim = ultimateSkillAnim = this->createAttackAnimation("4EFFECT5%04d.png", 1, 78, 10);//终极技能
		
	global->stateLayer->setultimateSkill(
		Sequence::create(
		CallFuncN::create(CC_CALLBACK_1(Hero::ultimateSkilSoundEffectCallBackAction_1, this)),
		//CallFuncN::create(CC_CALLBACK_1(Hero::ultimateSkilSoundEffectCallBackAction_2, this)),
		//CallFuncN::create(CC_CALLBACK_1(Hero::ultimateSkilSoundEffectCallBackAction_3, this)),
		Animate::create(ultimateSkillAnim),
		Role::createIdleCallbackFunc(),
		CallFuncN::create(CC_CALLBACK_1(Hero::setUltimateSkillVisable, this)),
		NULL));
	global->ultimateSkill->setVisible(true);
	global->ultimateSkill->runAction(global->stateLayer->getultimateSkill());
}

//CallBack
void Hero::setDeadFireVisable(Node* pSender)
{
	//获得鬼火的MP
	float deltaMP = 10.0f;
	this->setCurrMagicPoint(this->getCurrMagicPoint() + deltaMP);
	global->deadFire->setVisible(false);
}


void Hero::combosDisplay(int number, Vec2 point)
{
	//设置字体
	TTFConfig labelConfig;
	labelConfig.fontFilePath = "fonts/Marker Felt.ttf";
	labelConfig.fontSize = 50;
	labelConfig.glyphs = GlyphCollection::DYNAMIC;
	labelConfig.customGlyphs = nullptr;
	labelConfig.distanceFieldEnabled = false;
	//数字动画
	auto atLabel = Label::createWithTTF(labelConfig, "");
	atLabel->enableOutline(Color4B::BLACK, 3);
	atLabel->setString(__String::createWithFormat("%d", number)->getCString());
	atLabel->setColor(Color3B(255, 0, 0));
	atLabel->setPosition(point);

	//
	Sprite *combos = Sprite::create("Effects/combos.png");
	combos->setPosition(Vec2(point.x + labelConfig.fontSize * 2, point.y));
	combos->setScale(1.3f);
	global->stateLayer->addChild(combos);
	global->stateLayer->addChild(atLabel);

	FiniteTimeAction * labelCallFuncN = CallFuncN::create(atLabel, callfuncN_selector(Hero::combosFontsCallBackAction));
	FiniteTimeAction * spriteCallFuncN = CallFuncN::create(combos, callfuncN_selector(Hero::combosFontsCallBackAction));
	FiniteTimeAction *sequence = Sequence::create(
		//FadeIn::create(1.5f),
		ScaleTo::create(1.0f, 1.3f),
		FadeOut::create(0.3f),
		labelCallFuncN,
		NULL);

	FiniteTimeAction *sequence2 = Sequence::create(
		//FadeIn::create(1.5f),
		FadeOut::create(0.5f),
		spriteCallFuncN,
		NULL);
	atLabel->runAction(sequence);
	combos->runAction(sequence2);
	//设置连击的MP
	float deltaMP = 2.0f;
	this->setCurrMagicPoint(this->getCurrMagicPoint() + deltaMP);
}

void Hero::combosFontsCallBackAction(Node* pSender)
{
	global->stateLayer->removeChild(pSender);
	
}

void Hero::combosSpriteCallBackAction(Node *pSender)
{
	global->stateLayer->removeChild(pSender);
}

void Hero::setUltimateSkillVisable(Node *pSender)
{
	global->ultimateSkill->setVisible(false);
	//敌人fly
	__Array *pEnemies = global->enemies;
	Ref *enemyObj = NULL;

	CCARRAY_FOREACH(pEnemies, enemyObj)
	{
		Enemy *pEnemyHurt = (Enemy*)enemyObj;
		//pEnemyHurt->runHurtAction();
		pEnemyHurt->runHurtFlyLeftAction();
	}

}

//sound effect call back
void Hero::normalAttackSoundEffectCallBackAction(Node *pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/BladeBig2.mp3");
}
//skill A 声音回调
void Hero::skillAttackASoundEffectCallBackAction(Node *pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Swordrotate.mp3");
}
//skill B 声音回调 1
void Hero::skillAttackBSoundEffectCallBackAction_1(Node *pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Swordrotate.mp3");
	
}
//skill B 声音回调 2
void Hero::skillAttackBSoundEffectCallBackAction_2(Node *pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Bladeblink.mp3");
}
//skill C 声音回调
void Hero::skillAttackCSoundEffectCallBackAction_1(Node *pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Swordflying.mp3");

}
//skill C 声音回调 2
void Hero::skillAttackCSoundEffectCallBackAction_2(Node *pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Bladeblink.mp3");
}
//被攻击时声音回调
void Hero::beAttackedSoundEffectCallBackAction(Node *pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/woman_atked2a.mp3");
}
//被击飞时声音回调
void Hero::beAttakedFlyingSoundEffectCallBackAction(Node *pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/hbnz_atked1.mp3");
}
//终极技能声音回调 1
void Hero::ultimateSkilSoundEffectCallBackAction_1(Node *pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/Bladeblink.mp3");
}
//终极技能声音回调 2
void Hero::ultimateSkilSoundEffectCallBackAction_2(Node *pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/BladeBig2.mp3");
}
//终极技能声音回调 3
void Hero::ultimateSkilSoundEffectCallBackAction_3(Node *pSender)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/BladeBig3.mp3");
}
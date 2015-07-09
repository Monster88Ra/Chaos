#include "Role.h"
#include "Other\Global.h"
Role::Role(void):
	m_pidleaction(NULL),
	m_pwalkaction(NULL),
	m_prunaction(NULL),
	m_pjumpaction(NULL),
	m_pnomalattacka(NULL),
	m_pnomalattackb(NULL),
	m_pnomalattackc(NULL),
	m_pnomalattackd(NULL),
	m_pchange(NULL),
	m_pchangeattack(NULL),
	m_prushattack(NULL),
	m_pjumpattacka(NULL),
	m_pjumpattackb(NULL),
	m_pskillattacka(NULL),
	m_pskillattackb(NULL),
	m_pskillattackc(NULL),
	m_phurtaction(NULL),
	m_phurtFlyActionRight(NULL),
	m_phurtFlyActionLeft(NULL),
	m_phurtFallAction(NULL),
	m_pflashAction(NULL),
	m_pdeadaction(NULL),
	m_ultimateskill(NULL),
	currActionState(ACTION_STATE_NONE)
{

}

Role::~Role()
{
	CC_SAFE_RELEASE_NULL(m_pidleaction);
	CC_SAFE_RELEASE_NULL(m_pwalkaction);
	CC_SAFE_RELEASE_NULL(m_prunaction);
	CC_SAFE_RELEASE_NULL(m_pjumpaction);
	CC_SAFE_RELEASE_NULL(m_pnomalattacka);
	CC_SAFE_RELEASE_NULL(m_pnomalattackb);
	CC_SAFE_RELEASE_NULL(m_pnomalattackc);
	CC_SAFE_RELEASE_NULL(m_pnomalattackd);
	CC_SAFE_RELEASE_NULL(m_pchange);
	CC_SAFE_RELEASE_NULL(m_pchangeattack);
	CC_SAFE_RELEASE_NULL(m_prushattack);
	CC_SAFE_RELEASE_NULL(m_pjumpattacka);
	CC_SAFE_RELEASE_NULL(m_pjumpattackb);
	CC_SAFE_RELEASE_NULL(m_pskillattacka);
	CC_SAFE_RELEASE_NULL(m_pskillattackb);
	CC_SAFE_RELEASE_NULL(m_pskillattackc);
	CC_SAFE_RELEASE_NULL(m_phurtaction);
	CC_SAFE_RELEASE_NULL(m_phurtFlyActionRight);
	CC_SAFE_RELEASE_NULL(m_phurtFlyActionLeft);
	CC_SAFE_RELEASE_NULL(m_phurtFallAction);
	CC_SAFE_RELEASE_NULL(m_pflashAction);
	CC_SAFE_RELEASE_NULL(m_pdeadaction);
	CC_SAFE_RELEASE_NULL(m_ultimateskill);
}

void Role::runIdleAction()
{
	//changeState �ж��Ƿ���Ա��״̬��Ȼ��runAction
	if(changeState(ACTION_STATE_IDLE))
		this->runAction(m_pidleaction);
}

void Role::runWalkAction()
{
	if(changeState(ACTION_STATE_WALK))
		this->runAction(m_pwalkaction);
}

void Role::runRunAction()
{	
	if(changeState(ACTION_STATE_RUN))
		this->runAction(m_prunaction);
}
void Role::runJumpAction()
{
	if(changeState(ACTION_STATE_JUMP))
		this->runAction(m_pjumpaction);
}

void Role::runNomalAttackA()
{
	if(changeState(ACTION_STATE_NOMAL_ATTACK_A))
	{
		this->setAllowMove(false);
		this->runAction(m_pnomalattacka);

	}
}
void Role::runNomalAttackB()
{
	if(changeState(ACTION_STATE_NOMAL_ATTACK_B))
	{
		this->setAllowMove(false);
		this->runAction(m_pnomalattackb);
	}
}

void Role::runNomalAttackC()
{
	if(changeState(ACTION_STATE_NOMAL_ATTACK_C))
	{
		this->setAllowMove(false);
		this->runAction(m_pnomalattackc);
	}
}
void Role::runNomalAttackD()
{
	if(changeState(ACTION_STATE_NOMAL_ATTACK_D))
	{
		this->setAllowMove(false);
		this->runAction(m_pnomalattackd);
		
	}
}

void Role::runComboAttack()
{
	if (changeState(ACTION_STATE_COMBO_ATTACK))
	{
		this->setAllowMove(false);
		this->runAction(m_pcomboattack);
	}
}

void Role::runChange()
{
	if(changeState(ACTION_STATE_CHANGE))
	{
		this->setAllowMove(false);
		this->runAction(m_pchange);
	}
}
void Role::runChangeAttack()
{
	if(changeState(ACTION_STATE_CHANGE_ATTACK))
	{
		this->setAllowMove(false);
		this->runAction(m_pchangeattack);
	}
}
void  Role::runRushAttack()
{
	if(changeState(ACTION_STATE_RUSH_ATTACK))
	{
		this->runAction(m_prushattack);
	}
}
void  Role::runJumpAttackA()
{
	if(changeState(ACTION_STATE_JUMP_ATTACK_A))
	{
		this->runAction(m_pjumpattacka);
	}
}
void  Role::runJumpAttackB()
{
	if(changeState(ACTION_STATE_JUMP_ATTACK_B))
	{
		this->runAction(m_pjumpattackb);
	}
}
void  Role::runSkillAttackA()
{
	if(changeState(ACTION_STATE_SKILL_ATTACK_A))
	{
		this->setAllowMove(false);
		this->runAction(m_pskillattacka);
	}
}
void  Role::runSkillAttackB()
{
	if(changeState(ACTION_STATE_SKILL_ATTACK_B))
	{
		this->setAllowMove(false);
		this->runAction(m_pskillattackb);
	}
}
void  Role::runSkillAttackC()
{
	if(changeState(ACTION_STATE_SKILL_ATTACK_C))
	{
		this->setAllowMove(false);
		this->runAction(m_pskillattackc);
	}
}

void Role::runHurtAction()
{
	if(changeState(ACTION_STATE_HURT))
	{
		this->runAction(m_phurtaction);
	}
}

void Role::runHurtFlyRightAction()
{
	if (changeState(ACTION_STATE_HURT_FLY))
	{
		float distance = 300;
		float delta = 32;//����ֵ
		Vec2 excpPoint = Vec2(this->getPosition().x + distance + delta, this->getPosition().y);

		if (excpPoint.x > 0 && excpPoint.x < global->getTileMapWidth())
		{
			this->runAction(m_phurtFlyActionRight);
		}
		else
		{
			this->runHurtAction();
		}
	}
}

void Role::runHurtFlyLeftAction()
{
	if (changeState(ACTION_STATE_HURT_FLY))
	{
		float distance = 300;
		float delta = 32;//����ֵ
		Vec2 excpPoint = Vec2(this->getPosition().x - distance-delta, this->getPosition().y);
		if (excpPoint.x > 0 && excpPoint.x < global->getTileMapWidth())
			this->runAction(m_phurtFlyActionLeft);
		else
		{
			this->runHurtAction();
		}
	}
}

void Role::runHurtFallAction()
{
	if (changeState(ACTION_STATE_HURT_FALL))
	{
		this->runAction(m_phurtFallAction);
	}
}

void Role::runFlashAction()
{
	if (changeState(ACTION_STATE_FLASH))
	{
		this->runAction(m_pflashAction);
	}
}

void Role::runDeadAction()
{
	if(changeState(ACTION_STATE_DEAD))
	{
		this->runAction(m_pdeadaction);
	}
}

void Role::runUltimateSkillAction()
{
	if (changeState(ACTION_STATE_UltimateSkill))
	{
		this->runAction(m_ultimateskill);
	}
}

Animation* Role::createNomalAnimation(const char* formatStr, int frameCount, int fps )
{
	Vector<SpriteFrame*> pFrames;
	for(int i = 1; i <= frameCount; i++)
	{
		const char* imgName = String::createWithFormat(formatStr,i)->getCString();
		SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		pFrames.insert(i-1,pFrame);
	}
	return Animation::createWithSpriteFrames(pFrames,1.0f/fps);
}

Animation* Role::createAttackAnimation(const char* formatStr, int frameCountBegan, int frameCountEnd,int fps)
{
	//ͨ��frameCountBegan,frameCountEnd��SpriteFrameCache�д���һ������
	Vector<SpriteFrame*> pFrames;
	for(int i = frameCountBegan; i < frameCountEnd;i++)
	{
		const char* imgName = String::createWithFormat(formatStr, i)->getCString();
		SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(imgName);
		pFrames.insert(i-frameCountBegan,pFrame);
	}
	return Animation::createWithSpriteFrames(pFrames, 1.0f / fps);
}

bool Role::changeState(ActionState actionState)
{
	//����ı�״̬����������ͬ״̬������ܸı�
	if(currActionState == ACTION_STATE_DEAD || currActionState == actionState)
		return false;
	this->stopAllActions();
	this->currActionState = actionState;
	return true;
}

CallFunc* Role::createIdleCallbackFunc()
{
	this->setAllowMove(true);
	return CallFunc::create(CC_CALLBACK_0(Role::runIdleAction, this));
}
//��������������
Spawn * Role::createBezierAnim(Point p1, Point p2, Point p3, Animation *act)
{
	//��������������
	ccBezierConfig bezier;
	bezier.controlPoint_1 = p1;//����ƫ��ֵ
	bezier.controlPoint_2 = p2;//����ƫ��ֵ
	bezier.endPosition = p3;//�����յ�
	BezierBy * bezierby = BezierBy::create(1.0f, bezier);
	return  Spawn::create(bezierby, Animate::create(act), NULL);//����ͬʱ����
}
BoundingBox Role::createBoundingBox(Vec2 origin, Size size)
{
	//����һ��BoundingBox ����������ײ���
	BoundingBox boundingBox;
	boundingBox.original.origin = origin;
	boundingBox.original.size = size;

	boundingBox.actual.origin = getPosition() + boundingBox.original.origin ;
	boundingBox.actual.size= size;
	return boundingBox;
}

void Role::updateBoxes()
{
	//ͨ������ˢ�к���λ��
	bool isFlippedX = this->isFlippedX();
	float x = 0.0f;
	if(isFlippedX) 
	{
		x = this->getPosition().x - m_hitBox.original.origin.x;
	}else 
	{
		x = this->getPosition().x + m_hitBox.original.origin.x;
	}
	m_hitBox.actual.origin = Vec2(x, this->getPosition().y + m_hitBox.original.origin.y);
	m_bodyBox.actual.origin = this->getPosition() + m_bodyBox.original.origin;
}

void Role::setPosition(const Vec2 &position)
{
	//ÿ�������趨�����ʱ��ˢ�º���
	Sprite::setPosition(position);
	this->updateBoxes();
}

//debug tools
void Role::Debug_DrawBoundingBox(DrawNode *p, BoundingBox box, Color4F color)
{
	Vec2 vertices[] =
	{
		Vec2(box.actual.getMinX(), box.actual.getMinY()),
		Vec2(box.actual.getMinX(), box.actual.getMaxY()),
		Vec2(box.actual.getMaxX(), box.actual.getMaxY()),
		Vec2(box.actual.getMaxX(), box.actual.getMinY())
	};
	p->drawPolygon(vertices, 4, color, 1, Color4F(0.2f, 0.2f, 0.2f, 1));
}


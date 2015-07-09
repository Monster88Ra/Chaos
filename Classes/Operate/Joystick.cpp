#include "Joystick.h"
using namespace std;

//init static
double Joystick::pressButtonTime = 0;

Joystick::Joystick()
{

}

Joystick::~Joystick()
{

}

bool Joystick::init()
{
	bool ret = false;
	do
	{
		CC_BREAK_IF(!Sprite::init());
		roleDistance = 64.0f;
		m_pJoystickBg = Sprite::create("joystickBg.png");//����
		m_pJoystick = Sprite::create("joystick.png");//ҡ��
		this->addChild(m_pJoystickBg, 0);
		this->addChild(m_pJoystick, 1);
		this->hideJoystick();

		m_pJoystickR = m_pJoystickBg->getContentSize().width / 2;
		m_pJoystickr = m_pJoystick->getContentSize().width / 2;

		//ע��
		/*
		auto listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(Joystick::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(Joystick::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(Joystick::onTouchesEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		*/
		
		keyboardListener = EventListenerKeyboard::create();
		keyboardListener->onKeyPressed = CC_CALLBACK_2(Joystick::onKeyPressed, this);
		keyboardListener->onKeyReleased = CC_CALLBACK_2(Joystick::onKeyReleased, this);
		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
		
		ret = true;
	} while (0);
	return ret;
}

void Joystick::showJoystick()
{
	//��ʾҡ��
	m_pJoystick->setVisible(true);
	m_pJoystickBg->setVisible(true);
}

void Joystick::hideJoystick()
{
	//����ҡ��
	//m_pJoystick->setPosition(m_pJoystickBg->getPosition());
	m_pJoystick->setVisible(false);
	//m_pJoystickBg->setVisible(false);
	m_pJoystickBg->setVisible(true);
}

void Joystick::updateJoystick(Touch* touch)
{
	//����ҡ��״̬
	//���������ж�
	Vec2 hit = touch->getLocation();
	float distance = start.getDistance(hit);
	Vec2 direction = (hit - start).getNormalized();
	//Ϊ�˷�ֹҡ���Ƴ�ҡ�˱���
	if (distance < m_pJoystickr / 2)
	{
		m_pJoystick->setPosition(start + (direction * distance));
	}
	else if (distance >m_pJoystickr) {
		m_pJoystick->setPosition(start + (direction * m_pJoystickr));
	}
	else {
		m_pJoystick->setPosition(start + (direction * m_pJoystickr / 2));
	}

	global->hero->onMove(direction, distance);
}

void Joystick::onTouchesBegan(const vector<Touch*>& touches, Event *unused_event)
{
	//�����¼�����
	std::vector<Touch*>::const_iterator touchIter = touches.begin();
	Touch* touch = (Touch*)(*touchIter);
	if (m_pJoystick->getBoundingBox().containsPoint(touch->getLocation()))
	{
		this->showJoystick();
		updateJoystick(touch);
		CCLOG("***************");
		CCLOG("update touch:%f %f", touch->getLocation().x, touch->getLocation().y);

		return;
	}
}

void Joystick::onTouchesMoved(const vector<Touch*>& touches, Event *unused_event)
{
	//�ƶ�ʱ����
	std::vector<Touch*>::const_iterator touchIter = touches.begin();
	Touch* touch = (Touch*)(*touchIter);
	if (m_pJoystick->isVisible())
	{
		updateJoystick(touch);
		return;
	}
}

void Joystick::onTouchesEnded(const vector<Touch*>& touches, Event *unused_event)
{
	//�뿪����
	m_pJoystick->runAction(MoveTo::create(0.08f,start));
	m_pJoystick->setPosition(start);
	global->hero->onStop();
	this->hideJoystick();

}

void Joystick::setJoystick(Vec2 point)
{
	//�����ҡ�˵ķ���ĳ��������
	start = point;
	m_pJoystickBg->setPosition(start);
	m_pJoystick->setPosition(m_pJoystickBg->getPosition());
}

void Joystick::setDistance(float ds)
{
	roleDistance = ds;
}

void Joystick::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* unused_event)
{
	if (global->hero->getCurrActionState() == ACTION_STATE_NOMAL_ATTACK_A ||
		global->hero->getCurrActionState() == ACTION_STATE_NOMAL_ATTACK_B ||
		global->hero->getCurrActionState() == ACTION_STATE_NOMAL_ATTACK_C ||
		global->hero->getCurrActionState() == ACTION_STATE_NOMAL_ATTACK_D ||
		global->hero->getCurrActionState() == ACTION_STATE_SKILL_ATTACK_A ||
		global->hero->getCurrActionState() == ACTION_STATE_SKILL_ATTACK_B ||
		global->hero->getCurrActionState() == ACTION_STATE_SKILL_ATTACK_C ||
		global->hero->getCurrActionState() == ACTION_STATE_HURT ||
		global->hero->getCurrActionState() == ACTION_STATE_HURT_FLY ||
		global->hero->getCurrActionState() == ACTION_STATE_HURT_FALL ||
		global->hero->getCurrActionState() == ACTION_STATE_UltimateSkill)
		return;

	//�������� ��windows
	double prePressButtonTime = pressButtonTime;
	pressButtonTime = GetTickCount();
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
	{
		global->hero->onStop();
		CCLOG("KEY_W release");
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
	{
		global->hero->onStop();
		CCLOG("KEY_S release");
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
	{
		global->hero->onStop();
		CCLOG("KEY_A release");
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
	{
		global->hero->onStop();
		CCLOG("KEY_D release");
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_J:
	{

		double timeInterval = pressButtonTime - prePressButtonTime;
		CCLOG("time Interval is %f", timeInterval);
		if (timeInterval < 200)
		{
			
			global->hero->onAttack(ACTION_STATE_NOMAL_ATTACK_A);
		}
		else if (timeInterval < 700)
		{
			global->hero->onAttack(ACTION_STATE_NOMAL_ATTACK_C);
			global->hero->onAttack(ACTION_STATE_NOMAL_ATTACK_D);
		}
		else
		{
			global->hero->onAttack(ACTION_STATE_NOMAL_ATTACK_A);
			global->hero->onAttack(ACTION_STATE_NOMAL_ATTACK_B);
		}
		CCLOG("KEY_J release ");
		break;
	}

	case cocos2d::EventKeyboard::KeyCode::KEY_U:
	{
		
		if (global->hero->getCurrActionState() == ACTION_STATE_SkillA_CD)
			break;
		
		global->hero->onSkill(ACTION_STATE_SKILL_ATTACK_A);
		
		break;
	}

	case cocos2d::EventKeyboard::KeyCode::KEY_I:
	{
		global->hero->onSkill(ACTION_STATE_SKILL_ATTACK_B);
		break;
	}

	case cocos2d::EventKeyboard::KeyCode::KEY_O:
	{
		global->hero->onSkill(ACTION_STATE_SKILL_ATTACK_C);
		break;
	}

	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
	{
		global->hero->onFlash();
		break;
	}

	default:
	{
		break;
	}

	}
	//keyboardListener->setEnabled(true);
}

void Joystick::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event)
{
	if (global->hero->getCurrActionState() == ACTION_STATE_NOMAL_ATTACK_A ||
		global->hero->getCurrActionState() == ACTION_STATE_NOMAL_ATTACK_D ||
		global->hero->getCurrActionState() == ACTION_STATE_SKILL_ATTACK_A ||
		global->hero->getCurrActionState() == ACTION_STATE_SKILL_ATTACK_B ||
		global->hero->getCurrActionState() == ACTION_STATE_SKILL_ATTACK_C ||
		global->hero->getCurrActionState() == ACTION_STATE_HURT ||
		global->hero->getCurrActionState() == ACTION_STATE_HURT_FLY ||
		global->hero->getCurrActionState() == ACTION_STATE_HURT_FALL ||
		global->hero->getCurrActionState() == ACTION_STATE_UltimateSkill)
		return;


	Vec2 direction(0.0f,0.0f);

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
	{
		direction.y += roleDistance;
		CCLOG("KEY_W press");
		global->hero->onMove(direction.getNormalized(), roleDistance);
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
	{
		direction.y -= roleDistance;
		CCLOG("KEY_S press");
		global->hero->onMove(direction.getNormalized(), roleDistance);
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
	{
		direction.x -= roleDistance;
		CCLOG("KEY_A press");
		global->hero->onMove(direction.getNormalized(), roleDistance);
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
	{

		direction.x += roleDistance;
		CCLOG("KEY_D press");
		global->hero->onMove(direction.getNormalized(), roleDistance);
		break;
	}

	default:
		break;
	}
	
}

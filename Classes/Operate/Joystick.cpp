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
		m_pJoystickBg = Sprite::create("joystickBg.png");//背景
		m_pJoystick = Sprite::create("joystick.png");//摇杆
		this->addChild(m_pJoystickBg, 0);
		this->addChild(m_pJoystick, 1);
		this->hideJoystick();

		m_pJoystickR = m_pJoystickBg->getContentSize().width / 2;
		m_pJoystickr = m_pJoystick->getContentSize().width / 2;

		//注册
		auto listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(Joystick::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(Joystick::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(Joystick::onTouchesEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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
	//显示摇杆
	m_pJoystick->setVisible(true);
	m_pJoystickBg->setVisible(true);
}

void Joystick::hideJoystick()
{
	//隐藏摇杆
	//m_pJoystick->setPosition(m_pJoystickBg->getPosition());
	m_pJoystick->setVisible(false);
	//m_pJoystickBg->setVisible(false);
	m_pJoystickBg->setVisible(true);
}

void Joystick::updateJoystick(Touch* touch)
{
	//更新摇杆状态
	//用向量来判断
	Vec2 hit = touch->getLocation();
	float distance = start.getDistance(hit);
	Vec2 direction = (hit - start).getNormalized();
	//为了防止摇杆移出摇杆背景
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
	//按下事件处理
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
	//移动时处理
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
	//离开处理
	m_pJoystick->runAction(MoveTo::create(0.08f,start));
	m_pJoystick->setPosition(start);
	global->hero->onStop();
	this->hideJoystick();

}

void Joystick::setJoystick(Vec2 point)
{
	//将这个摇杆的放在某个坐标上
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
	
	//按键连击 仅windows
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
		keyboardListener->setEnabled(false);
		double timeInterval = pressButtonTime - prePressButtonTime;
		CCLOG("time Interval is %f", timeInterval);
		if (timeInterval < 200)
		{
			
			global->hero->onAttack(ACTION_STATE_NOMAL_ATTACK_D);
		}
		else
		{
			keyboardListener->setEnabled(false);
			global->hero->onAttack(ACTION_STATE_NOMAL_ATTACK_A);
		}
		CCLOG("KEY_J release");
		break;
	}
	default:
		break;
	}
	Sleep(120);
	keyboardListener->setEnabled(true);
}

void Joystick::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event)
{
	Vec2 direction(0.0f,0.0f);
	
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
	{
		direction.y += roleDistance;
		CCLOG("KEY_W press");
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
	{
		direction.y -= roleDistance;
		CCLOG("KEY_S press");
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
	{
		direction.x -= roleDistance;
		CCLOG("KEY_A press");
		break;
	}
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
	{

		direction.x += roleDistance;
		CCLOG("KEY_D press");
		break;
	}

	default:
		break;
	}
	global->hero->onMove(direction.getNormalized(), roleDistance);
}

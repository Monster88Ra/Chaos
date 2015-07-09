#include "SkillButton.h"

SkillButton::SkillButton() :
_ItemSkill(NULL),
_Mask(NULL),
_cdtime(1.0f),
_ProgressTimer(NULL)
{

}

SkillButton::~SkillButton()
{
}

SkillButton* SkillButton::create(const char* Normal, const char* Click, const char* Mask, float CDTime)
{
	SkillButton* skillButton = new SkillButton();
	if (skillButton && skillButton->init(Normal, Click, Mask, CDTime))
	{
		skillButton->autorelease();
		return skillButton;
	}
	else
	{
		CC_SAFE_DELETE(skillButton);
		return nullptr;
	}
}

bool SkillButton::init(const char* Normal, const char* Click, const char* Mask, float CDTime)
{
	bool ret = false;
	do {
		CC_BREAK_IF(!Node::init());
		//�ϵ��
		CCAssert(Mask, "SkillButton::init Mask != NULL");
		CCAssert(Normal, "SkillButton::init Normal != NULL");
		CCAssert(Click, "SkillButton::init Click != NULL");

		// Notice:���childʱҪע�����²�
		// ���·���MenuItemImage ������ɰ�ͼƬ ���Ϸ���ProgressTimer

		// ��Ӽ��ܰ�ť
		_ItemSkill = MenuItemImage::create(Normal, Click, CC_CALLBACK_1(SkillButton::ClickCallBack, this));
		_ItemSkill->setPosition(Vec2::ZERO);

		auto MenuSkill = Menu::create(_ItemSkill, NULL);
		MenuSkill->setPosition(Vec2::ZERO);
		addChild(MenuSkill, -100);

		// ����ɰ�
		if (Normal == Mask)
		{
			_Mask = Sprite::create();
			_Mask->setTexture(Normal);
			_Mask->setColor(Color3B(0, 0, 0));
			_Mask->setOpacity(100);
		}
		else
		{
			_Mask = Sprite::create(Mask);
		}
		_Mask->setPosition(Vec2::ZERO);
		_Mask->setVisible(false);
		addChild(_Mask, 0);

		// �����ת����������,����Ϊ˳ʱ�����ν��ȼ�ʱ��
		_ProgressTimer = ProgressTimer::create(Sprite::create(Normal));
		_ProgressTimer->setType(ProgressTimer::Type::RADIAL);
		_ProgressTimer->setPosition(Vec2::ZERO);
		_ProgressTimer->setVisible(false);
		addChild(_ProgressTimer, 100);

		this->setCDTime(CDTime);
		CdTime = CDTime;
		_atLabel = Label::create();
		_atLabel->setSystemFontSize(_Mask->getContentSize().width / 3);
		_atLabel->setColor(Color3B(0, 0, 0));
		_atLabel->setPosition(Vec2::ZERO);
		addChild(_atLabel, 200);
		_atLabel->setVisible(false);

		ret = true;
	} while (0);
	return ret;
}
void SkillButton::StartClickCallBack(Ref* obj)
{
	//����Hero״̬
	global->hero->setCurrActionState(ACTION_STATE_SkillA_CD);
}

void SkillButton::ClickCallBack(Ref* obj)
{
	
	// ���ü��ܰ�ť���ɵ��
	_ItemSkill->setEnabled(false);

	// �����ɰ�ɼ�
	_Mask->setVisible(true);

	// ���ý������ɼ�
	_ProgressTimer->setVisible(true);

	//����ʣ��ʱ��ɼ�
	_atLabel->setVisible(true);

	//������ʱ��
	this->schedule(schedule_selector(SkillButton::CoolDownReduce), 0.1f);

	//Hero�ͷż���A
	//global->hero->runSkillAttackA();

	
	CallFunc* action_callback = CallFuncN::create(CC_CALLBACK_1(SkillButton::CoolDownCallBack, this));
	CallFunc* before_action_callback = CallFuncN::create(CC_CALLBACK_1(SkillButton::StartClickCallBack, this));

	//׼��һ������ʱ��ΪCDTime��,��ת360��*100% �Ķ���(�𽥸��ǰ�͸ģ���γ���ȴЧ��;������м�ʱ��ȴ������ʵ�ֺ�ʱ�����)
	//ActionInterval������������Ҫ��������һ��ʱ��Ķ����� ����һ������ʱ��ͽ���ʱ�䡣����ʱ��������ʱ��������ڵó�
	ActionInterval* action_progress_to = Sequence::create(
		before_action_callback,
		ProgressTo::create(this->getCDTime(), 100),
		action_callback,
		NULL);

	
	_ProgressTimer->runAction(action_progress_to);

}
void SkillButton::CoolDownReduce(float dt)
{
	_atLabel->setString(__String::createWithFormat("%.1f", CdTime -= 0.1f)->getCString());
}

void SkillButton::CoolDownCallBack(Node* node)
{
	// ��ť��Ϊ����
	_ItemSkill->setEnabled(true);

	// �����ɰ岻�ɼ�
	_Mask->setVisible(false);

	// ���������ܲ��ɼ�
	_ProgressTimer->setVisible(false);
	_ProgressTimer->setPercentage(0);

	//����ʣ��ʱ�䲻�ɼ�
	_atLabel->setVisible(false);
	CdTime = this->getCDTime();

	//ȡ����ʱ��
	this->unschedule(schedule_selector(SkillButton::CoolDownReduce));

	//����Hero״̬
	global->hero->setCurrActionState(ACTION_STATE_NONE);

}

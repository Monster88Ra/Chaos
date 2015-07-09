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
		//断点宏
		CCAssert(Mask, "SkillButton::init Mask != NULL");
		CCAssert(Normal, "SkillButton::init Normal != NULL");
		CCAssert(Click, "SkillButton::init Click != NULL");

		// Notice:添加child时要注意上下层
		// 最下方是MenuItemImage 其次是蒙版图片 最上方是ProgressTimer

		// 添加技能按钮
		_ItemSkill = MenuItemImage::create(Normal, Click, CC_CALLBACK_1(SkillButton::ClickCallBack, this));
		_ItemSkill->setPosition(Vec2::ZERO);

		auto MenuSkill = Menu::create(_ItemSkill, NULL);
		MenuSkill->setPosition(Vec2::ZERO);
		addChild(MenuSkill, -100);

		// 添加蒙版
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

		// 添加旋转进度条精灵,设置为顺时针扇形进度计时器
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
	//设置Hero状态
	global->hero->setCurrActionState(ACTION_STATE_SkillA_CD);
}

void SkillButton::ClickCallBack(Ref* obj)
{
	
	// 设置技能按钮不可点击
	_ItemSkill->setEnabled(false);

	// 设置蒙版可见
	_Mask->setVisible(true);

	// 设置进度条可见
	_ProgressTimer->setVisible(true);

	//设置剩余时间可见
	_atLabel->setVisible(true);

	//开启定时器
	this->schedule(schedule_selector(SkillButton::CoolDownReduce), 0.1f);

	//Hero释放技能A
	//global->hero->runSkillAttackA();

	
	CallFunc* action_callback = CallFuncN::create(CC_CALLBACK_1(SkillButton::CoolDownCallBack, this));
	CallFunc* before_action_callback = CallFuncN::create(CC_CALLBACK_1(SkillButton::StartClickCallBack, this));

	//准备一个持续时间为CDTime秒,旋转360度*100% 的动画(逐渐覆盖半透模板形成冷却效果;这里进行计时冷却动画的实现和时间控制)
	//ActionInterval持续动作是需要持续运行一段时间的动作。 它有一个启动时间和结束时间。结束时间由启动时间加上周期得出
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
	// 按钮置为可用
	_ItemSkill->setEnabled(true);

	// 设置蒙板不可见
	_Mask->setVisible(false);

	// 进度条技能不可见
	_ProgressTimer->setVisible(false);
	_ProgressTimer->setPercentage(0);

	//设置剩余时间不可见
	_atLabel->setVisible(false);
	CdTime = this->getCDTime();

	//取消定时器
	this->unschedule(schedule_selector(SkillButton::CoolDownReduce));

	//设置Hero状态
	global->hero->setCurrActionState(ACTION_STATE_NONE);

}

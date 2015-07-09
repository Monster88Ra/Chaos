#ifndef _SKILL_BUTTON_H
#define _SKILL_BUTTON_H
#include "cocos2d.h"
USING_NS_CC;
#include "Other\Global.h"

class SkillButton :public Node
{
public:
	SkillButton();
	~SkillButton();

	static SkillButton* create(const char* Nomal, const char* Click, const char* Mask, float CDTime);

	static SkillButton* create(const char* Nomal, const char* Mask, float CDTime)
	{
		return SkillButton::create(Nomal, Nomal, Mask, CDTime);
	};

	static SkillButton* create(const char* Nomal, const char* Mask)
	{
		return SkillButton::create(Nomal, Nomal, Mask, 1.0f);
	};

	static SkillButton* create(const char* Nomal, float CDTime)
	{
		return SkillButton::create(Nomal, Nomal, Nomal, CDTime);
	};

	static SkillButton* create(const char* Nomal)
	{
		return SkillButton::create(Nomal, Nomal, Nomal, 1.0f);
	};

	CC_SYNTHESIZE(float, _cdtime, CDTime);
	void	StartClickCallBack(Ref* obj);
	void    ClickCallBack(Ref* obj);
	void    CoolDownCallBack(Node* node);

private:
	bool    init(const char* Nomal, const char* Click, const char* Mask, float CDTime);

private:
	MenuItemImage*   _ItemSkill;		// 技能按钮
	Sprite*          _Mask;				// 蒙板精灵,黑色半透明(这个是为了显示一个冷却计时效果)
	ProgressTimer*   _ProgressTimer;	// 时间进度条精灵(360度旋转)
	Label*			 _atLabel;			// 显示冷却
	float			CdTime;				// 冷却时间
	void			CoolDownReduce(float dt);	//冷却时间显示定时器
};
#endif//_SKILL_BUTTON_H
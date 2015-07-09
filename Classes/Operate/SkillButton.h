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
	MenuItemImage*   _ItemSkill;		// ���ܰ�ť
	Sprite*          _Mask;				// �ɰ徫��,��ɫ��͸��(�����Ϊ����ʾһ����ȴ��ʱЧ��)
	ProgressTimer*   _ProgressTimer;	// ʱ�����������(360����ת)
	Label*			 _atLabel;			// ��ʾ��ȴ
	float			CdTime;				// ��ȴʱ��
	void			CoolDownReduce(float dt);	//��ȴʱ����ʾ��ʱ��
};
#endif//_SKILL_BUTTON_H
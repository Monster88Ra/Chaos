#ifndef _HERO_H	
#define _HERO_H

#include "cocos2d.h"
USING_NS_CC;
#include "Role.h"
#include "Other\Global.h"
#include "SimpleAudioEngine.h"
class Hero:public Role
{
public:
	Hero(void);
	~Hero(void);
	virtual bool init();
	CREATE_FUNC(Hero);

	void onMove(Vec2 direction, float distance);
	void onFlash();
	void onStop();
	void onAttack(int number);
	void onSkill(int number);
	void updateSelf();

	void normalAttackCallBackAction(Node* pSender);//普通攻击回调
	void skillAttackCallBackAction(Node* pSender);//技能攻击回调
	void FontsCallBackAction(Node* pSender);//数字淡出回调
	void damageDisplay(int number, Vec2 point);//产生伤害数字动画
	void hitCounter();//连击计数
	void enemyBloodDisplay(Vec2 point);//敌人出血伤害
	void addDeadFire(Vec2 hero, Vec2 enemy);//添加鬼火特效
	void addUltimateSkill();//添加终极技能特效
	void combosFontsCallBackAction(Node* pSender);//连击数字淡出回调
	void combosSpriteCallBackAction(Node *pSender);//连击淡出回调
	void combosDisplay(int number, Vec2 point);//产生连击数字动画
	void setDeadFireVisable(Node* pSender);//设置回调
	void setUltimateSkillVisable(Node *psender);//Ultimate Skill回调

	//sound effect callback
	void normalAttackSoundEffectCallBackAction(Node *pSender);//普通攻击声音回调
	void skillAttackASoundEffectCallBackAction(Node *pSender);//skill A 声音回调
	void skillAttackBSoundEffectCallBackAction_1(Node *pSender);//skill B 声音回调 1
	void skillAttackBSoundEffectCallBackAction_2(Node *pSender);//skill B 声音回调 2
	void skillAttackCSoundEffectCallBackAction_1(Node *pSender);//skill C 声音回调 1
	void skillAttackCSoundEffectCallBackAction_2(Node *pSender);//skill C 声音回调 2
	void beAttackedSoundEffectCallBackAction(Node *pSender);//被攻击时声音回调
	void beAttakedFlyingSoundEffectCallBackAction(Node *pSender);//被击飞时声音回调
	void ultimateSkilSoundEffectCallBackAction_1(Node *pSender);//终极技能声音回调 1
	void ultimateSkilSoundEffectCallBackAction_2(Node *pSender);//终极技能声音回调 2
	void ultimateSkilSoundEffectCallBackAction_3(Node *pSender);//终极技能声音回调 3

	long preTime;//记录连击时间间隔
	long nextTime;//记录连击时间间隔
	int hitCount;//连击数
	
	//inline
	long millisecondNow()
	{
		struct timeval now;
		gettimeofday(&now, NULL);
		return (now.tv_sec * 1000 + now.tv_usec / 1000);
	}

	
};
#endif //Hero.h
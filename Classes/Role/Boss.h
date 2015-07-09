#ifndef _BOSS_H
#define _BOSS_H

#include "cocos2d.h"
USING_NS_CC;
#include "Role.h"
#include "Other\Global.h"
#include "SimpleAudioEngine.h"


typedef enum
{
	BOSS_IDLE = 0,
	BOSS_PATROL,
	BOSS_ATTACK,
	BOSS_PURSUIT
}BossState;

class Boss :public Role
{
public:
	Boss();
	~Boss();
	bool init();
	void updateSelf();
	CREATE_FUNC(Boss);

	CC_SYNTHESIZE(cocos2d::Vec2, m_moveDirection, MoveDirection);
	CC_SYNTHESIZE(float, m_eyeArea, EyeArea);
	CC_SYNTHESIZE(float, m_attackArea, AttackArea);
	CC_SYNTHESIZE(BossState, m_aiState, BossState);

	void attackCallBackAction(Node* pSender);//普通攻击回调
	void skillCallBackAction(Node* pSender);//技能攻击回调
	void beAttakedSoundEffectCallBackAction(Node *pSender);//受伤时声音回调 
private:
	void decide(const cocos2d::Vec2& target, float targetBodyWidth);
	void execute(const cocos2d::Vec2& target, float targetBodyWidth);
	unsigned int m_nextDecisionTime;
};


#endif
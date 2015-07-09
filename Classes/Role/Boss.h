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

	void attackCallBackAction(Node* pSender);//��ͨ�����ص�
	void skillCallBackAction(Node* pSender);//���ܹ����ص�
	void beAttakedSoundEffectCallBackAction(Node *pSender);//����ʱ�����ص� 
private:
	void decide(const cocos2d::Vec2& target, float targetBodyWidth);
	void execute(const cocos2d::Vec2& target, float targetBodyWidth);
	unsigned int m_nextDecisionTime;
};


#endif
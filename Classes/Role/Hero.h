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

	void normalAttackCallBackAction(Node* pSender);//��ͨ�����ص�
	void skillAttackCallBackAction(Node* pSender);//���ܹ����ص�
	void FontsCallBackAction(Node* pSender);//���ֵ����ص�
	void damageDisplay(int number, Vec2 point);//�����˺����ֶ���
	void hitCounter();//��������
	void enemyBloodDisplay(Vec2 point);//���˳�Ѫ�˺�
	void addDeadFire(Vec2 hero, Vec2 enemy);//��ӹ����Ч
	void addUltimateSkill();//����ռ�������Ч
	void combosFontsCallBackAction(Node* pSender);//�������ֵ����ص�
	void combosSpriteCallBackAction(Node *pSender);//���������ص�
	void combosDisplay(int number, Vec2 point);//�����������ֶ���
	void setDeadFireVisable(Node* pSender);//���ûص�
	void setUltimateSkillVisable(Node *psender);//Ultimate Skill�ص�

	//sound effect callback
	void normalAttackSoundEffectCallBackAction(Node *pSender);//��ͨ���������ص�
	void skillAttackASoundEffectCallBackAction(Node *pSender);//skill A �����ص�
	void skillAttackBSoundEffectCallBackAction_1(Node *pSender);//skill B �����ص� 1
	void skillAttackBSoundEffectCallBackAction_2(Node *pSender);//skill B �����ص� 2
	void skillAttackCSoundEffectCallBackAction_1(Node *pSender);//skill C �����ص� 1
	void skillAttackCSoundEffectCallBackAction_2(Node *pSender);//skill C �����ص� 2
	void beAttackedSoundEffectCallBackAction(Node *pSender);//������ʱ�����ص�
	void beAttakedFlyingSoundEffectCallBackAction(Node *pSender);//������ʱ�����ص�
	void ultimateSkilSoundEffectCallBackAction_1(Node *pSender);//�ռ����������ص� 1
	void ultimateSkilSoundEffectCallBackAction_2(Node *pSender);//�ռ����������ص� 2
	void ultimateSkilSoundEffectCallBackAction_3(Node *pSender);//�ռ����������ص� 3

	long preTime;//��¼����ʱ����
	long nextTime;//��¼����ʱ����
	int hitCount;//������
	
	//inline
	long millisecondNow()
	{
		struct timeval now;
		gettimeofday(&now, NULL);
		return (now.tv_sec * 1000 + now.tv_usec / 1000);
	}

	
};
#endif //Hero.h
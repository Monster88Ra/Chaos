#ifndef _ROLE_H
#define _ROLE_H

#include "cocos2d.h"
USING_NS_CC;

typedef struct _BoundingBox
{
	Rect actual;
	Rect original;
} BoundingBox;

typedef enum
{
	ACTION_STATE_NONE = 0,
	ACTION_STATE_IDLE,
	ACTION_STATE_WALK,
	ACTION_STATE_RUN,
	ACTION_STATE_JUMP,
	ACTION_STATE_NOMAL_ATTACK_A,
	ACTION_STATE_NOMAL_ATTACK_B,
	ACTION_STATE_NOMAL_ATTACK_C,
	ACTION_STATE_NOMAL_ATTACK_D,
	ACTION_STATE_COMBO_ATTACK,
	ACTION_STATE_CHANGE,
	ACTION_STATE_CHANGE_ATTACK,
	ACTION_STATE_RUSH_ATTACK,
	ACTION_STATE_JUMP_ATTACK_A,
	ACTION_STATE_JUMP_ATTACK_B,
	ACTION_STATE_SKILL_ATTACK_A,
	ACTION_STATE_SKILL_ATTACK_B,
	ACTION_STATE_SKILL_ATTACK_C,
	ACTION_STATE_HURT,
	ACTION_STATE_HURT_FLY,
	ACTION_STATE_HURT_FALL,
	ACTION_STATE_FLASH,
	ACTION_STATE_DEAD,
	ACTION_STATE_UltimateSkill,
	ACTION_STATE_SkillA_CD
}ActionState;

//base class 
//derived by main role or NPC
//custom setting at derived class
class Role:public Sprite
{
public:
	Role();
	~Role();
	//state of role ,init state

	//role name
	CC_SYNTHESIZE(std::string,Name,Name);
	CC_SYNTHESIZE(float,curtLifevalue,CurtLifeValue);
	CC_SYNTHESIZE(float,sumLifevalue,SumLifeValue);	
	//role damage strength
	CC_SYNTHESIZE(float,damagestrength,DamageStrength);	
	//role sum magic point
	CC_SYNTHESIZE(float,sumMagicPoint,SumMagicPoint);
	//role current magic point
	CC_SYNTHESIZE(float, currMagicPoint, CurrMagicPoint);
	//role moving speed
	CC_SYNTHESIZE(Vec2, velocity, Velocity);
	CC_SYNTHESIZE(bool, roleDirection, RoleDirection);		//��ɫ���� true ��ʾ��  false��ʾ��
	CC_SYNTHESIZE(bool, allowmove, AllowMove);
	CC_SYNTHESIZE(ActionState,currActionState,CurrActionState);
	CC_SYNTHESIZE(bool, animationIsDone, AnimationIsDone);	//��ǰ�����Ƿ����

	/* ��Ҫ��creatNomalAnimation����,ֻ����ͨ�������������ж����޹����ж� */
	CC_SYNTHESIZE_RETAIN(Action*, m_pidleaction, IdleAction);		//��ɫ����ʱ����
	CC_SYNTHESIZE_RETAIN(Action*, m_pwalkaction, WalkAction);		//��ɫ�ƶ�ʱ����֡����
	CC_SYNTHESIZE_RETAIN(Action*, m_prunaction,  RunAction );		//��ɫ�ܶ�ʱ����֡����
	CC_SYNTHESIZE_RETAIN(Action*, m_pjumpaction, JumpAction);		//��ɫ��Ծʱ����֡����

	/* �����ǹ������ж�������Ҫ��creatAttackAnimation���������ڶ���ִ���м���ӹ����ж�������Ʈ�ֵ�*/
	CC_SYNTHESIZE_RETAIN(Action*, m_pnomalattacka, NomalAttackA);	//��ɫ��ͨ����Aʱ����֡����
	CC_SYNTHESIZE_RETAIN(Action*, m_pnomalattackb, NomalAttackB);	//��ɫ��ͨ����Bʱ����֡����
	CC_SYNTHESIZE_RETAIN(Action*, m_pnomalattackc, NomalAttackC);	//��ɫ��ͨ����Cʱ����֡����
	CC_SYNTHESIZE_RETAIN(Action*, m_pnomalattackd, NomalAttackD);	//��ɫ��ͨ����Dʱ����֡����
	CC_SYNTHESIZE_RETAIN(Action*, m_pchange,  Change);				//��ɫ����ʱ�Ķ�������
	CC_SYNTHESIZE_RETAIN(Action*, m_pchangeattack,  ChangeAttack);	//��ɫ��������ʱ�Ķ�������

	CC_SYNTHESIZE_RETAIN(Action*, m_pcomboattack, ComboAttack);		//��ɫ��������

	CC_SYNTHESIZE_RETAIN(Action*, m_prushattack,   RushAttack  );	//��ɫ�ܶ�����ʱ����֡����
	CC_SYNTHESIZE_RETAIN(Action*, m_pjumpattacka,  JumpAttackA );	//��ɫ��Ծ����Aʱ����֡����
	CC_SYNTHESIZE_RETAIN(Action*, m_pjumpattackb,  JumpAttackb );	//��ɫ��Ծ����Bʱ����֡����
	CC_SYNTHESIZE_RETAIN(Action*, m_pskillattacka, SkillAttackA);	//��ɫ���ܹ���Aʱ����֡����
	CC_SYNTHESIZE_RETAIN(Action*, m_pskillattackb, SkillAttackB);	//��ɫ���ܹ���Bʱ����֡����
	CC_SYNTHESIZE_RETAIN(Action*, m_pskillattackc, SkillAttackC);	//��ɫ���ܹ���Cʱ����֡����

	/*������createImmortalAnimation����,ֻ�ж���Ч��,�������ж�,Ҳ��������ʱ�򲥷Ŷ������޵е�,���һ������ж���*/
	CC_SYNTHESIZE_RETAIN(Action*, m_phurtaction, HurtAction);				//��ɫ����ʱ����֡����
	CC_SYNTHESIZE_RETAIN(Action*, m_phurtFlyActionRight, HurtFlyActionRight);//��ɫ���˵��ض���֡��������
	CC_SYNTHESIZE_RETAIN(Action*, m_phurtFlyActionLeft, HurtFlyActionLeft);	//��ɫ���˵��ض���֡��������
	CC_SYNTHESIZE_RETAIN(Action*, m_phurtFallAction, HurtFallAction);		//��ɫ�������
	CC_SYNTHESIZE_RETAIN(Action*, m_pflashAction,FlashAction);				//��ɫ��˸����
	CC_SYNTHESIZE_RETAIN(Action*, m_pdeadaction, DeadAction);				//��ɫ����ʱ����֡����
	CC_SYNTHESIZE_RETAIN(Action*, m_ultimateskill, UltimateSkillAction);    //��ɫ���У����壩

	void Role::callBackAction(Node* pSender);						//����ִ����ϵ�ͨ�ûص�����

	/*	���������еĶ����ص�����������ִ�д˶���,	*/
	virtual void runIdleAction();								//ִ�����ö���
	virtual void runWalkAction();								//ִ���ƶ����߶���
	virtual void runRunAction();								//ִ���ܶ����߶���
	virtual void runJumpAction();								//ִ����Ծ��������
	virtual void runNomalAttackA();								//ִ����ͨ����A����
	virtual void runNomalAttackB();								//ִ����ͨ����B����
	virtual void runNomalAttackC();								//ִ����ͨ����C����
	virtual void runNomalAttackD();								//ִ����ͨ����D����
	virtual void runComboAttack();								//ִ����������
	virtual void runChange();									//ִ����������
	virtual void runChangeAttack();								//ִ��������������
	virtual void runRushAttack();								//ִ���ܶ���������
	virtual void runJumpAttackA();								//ִ����Ծ����A����
	virtual void runJumpAttackB();								//ִ����Ծ����B����
	virtual void runSkillAttackA(); 							//ִ�м��ܹ���A����
	virtual void runSkillAttackB(); 							//ִ�м��ܹ���B����
	virtual void runSkillAttackC(); 							//ִ�м��ܹ���C����
	virtual void runHurtAction();								//ִ�б����������˶���
	virtual void runHurtFlyRightAction();						//ִ�б���������󵹵����˶��� ����
	virtual void runHurtFlyLeftAction();						//ִ�б���������󵹵����˶��� ����
	virtual void runHurtFallAction();							//ִ�б�����������ض���
	virtual void runFlashAction();								//ִ�����ֶ���
	virtual void runDeadAction();								//ִ������������
	virtual void runUltimateSkillAction();						//ִ���ռ����ܶ���
	virtual Spawn* createBezierAnim(Point p1, Point p2, Point p3,Animation *act);//����һ������������,p1 ���� p2 ���� p3 �յ�
	CallFunc* createIdleCallbackFunc();							//�ص����ö���

	BoundingBox createBoundingBox(Vec2 origin,Size size);
	CC_SYNTHESIZE(BoundingBox, m_bodyBox, BodyBox);				//������ײ����
	CC_SYNTHESIZE(BoundingBox, m_hitBox, HitBox);				//������ײ����
	virtual void setPosition(const Vec2 &position);

	void updateBoxes();

	//debug tool draw BoundingBox
	void Debug_DrawBoundingBox(DrawNode *p, BoundingBox b, Color4F color);

protected:
	static Animation* createNomalAnimation(const char* formatStr, int frameCount, int fps);
	static Animation* createAttackAnimation(const char* formatStr, int frameCountBegan, int frameCountEnd,int fps);

private:
	bool changeState(ActionState actionState);
	ActionState proActionState;
};
#endif // Role.h
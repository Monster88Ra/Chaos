#ifndef _HP_SHOW_H
#define _HP_SHOW_H

#include "cocos2d.h"
#include "Other\Global.h"

USING_NS_CC;

class HpShow :public Node
{
public:
	HpShow();
	~HpShow();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(HpShow);
private:
	ProgressTimer* m_preal;
};
#endif // _HP_SHOW_H

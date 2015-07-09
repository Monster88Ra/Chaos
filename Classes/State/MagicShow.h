#ifndef _MAGIC_SHOW_H
#define _MAGIC_SHOW_H

#include "cocos2d.h"
#include "Other\Global.h"

USING_NS_CC;

class MagicShow :public Node
{
public:
	MagicShow();
	~MagicShow();
	virtual bool init();
	void update(float dt);
	CREATE_FUNC(MagicShow);

private:
	ProgressTimer* m_preal;
};
#endif
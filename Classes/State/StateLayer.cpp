#include "StateLayer.h"

USING_NS_CC;

StateLayer::StateLayer()
{
	global->stateLayer = this;
}

StateLayer::~StateLayer()
{
}

bool StateLayer::init()
{
	bool ret = false;
	do{
		CC_BREAK_IF( !Layer::init() );
		ret = true;
	}while(0);

	return ret;
}
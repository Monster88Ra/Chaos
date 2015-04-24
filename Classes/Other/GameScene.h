#ifndef _GAME_SCENE_H
#define _GAME_SCENE_H

#include "cocos2d.h"
#include "Game\GameLayer.h"
#include "State\StateLayer.h"
#include "Operate\OperateLayer.h"

class GameScene:public cocos2d::Scene
{
public :
	static cocos2d::Scene *createScene();
};
#endif // GameScene.h
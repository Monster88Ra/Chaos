#ifndef _GAME_SCENE_INFO_H
#define _GAME_SCENE_INFO_H
#include "cocos2d.h"

class GameSceneInfo
{
public:
	GameSceneInfo(const char* map,const char* enemy,const char* boss);
	~GameSceneInfo();

	const char* mapName;
	const char* enemyFormatStr;
	const char* bossFormatStr;
};

#endif//_GAME_SCENE_INFO_H
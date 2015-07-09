#include "Global.h"

DECLARE_SINGLETON_MEMBER(Global);


Global::Global(void) :sceneIndex(0)
{
	//获取英雄信息
	std::map<int, HeroMessage> temp = HeroMessageUtil::getInstance()->getHeroMessageMap();
	heroInfo = temp.at(40001);
	//test need to be modified later
	//init two scene info
	auto info_1 = new GameSceneInfo(stmx_QingQiuMountain, "9", NULL);
	sceneInfoVector.push_back(info_1);
	auto info_2 = new GameSceneInfo("LieYanCave.tmx", NULL, "23");
	sceneInfoVector.push_back(info_2);
}

Global::~Global(void)
{
	CC_SAFE_DELETE(gameLayer);
	CC_SAFE_DELETE(operateLayer);
	CC_SAFE_DELETE(stateLayer);
	CC_SAFE_DELETE(hero);
	CC_SAFE_DELETE(enemies);
	CC_SAFE_DELETE(bosses);
	CC_SAFE_DELETE(skillA);
	//CC_SAFE_DELETE(tileMap);
	gameLayer = NULL;
	operateLayer = NULL;
	stateLayer = NULL;
	hero = NULL;
	enemies = NULL;
	bosses = NULL;
	tileMap = NULL;
	skillA = NULL;
}

Point Global::tilePosFromLocation(Point MovePoint, TMXTiledMap *map)
{
	Point point = MovePoint - map->getPosition();
	Point pointGID = Vec2::ZERO;
	pointGID.x = (int)(point.x / map->getTileSize().width);
	pointGID.y = (int)((map->getMapSize().height * map->getTileSize().height - point.y) / map->getTileSize().height);
	return pointGID;
}

bool Global::tileAllowMove(Point MovePoint)
{
	TMXLayer *metaLayer = global->tileMap->getLayer("Meta");
	Point tileCoord = tilePosFromLocation(MovePoint, global->tileMap);
	int tileGid = metaLayer->getTileGIDAt(tileCoord);

	if (tileGid)
	{
		auto properties = tileMap->getPropertiesForGID(tileGid).asValueMap();
		if (!properties.empty())
		{
			auto collision = properties["Collidable"].asString();
			if ("True" == collision)
				return false;
			else
				return true;
		}
		else
			return true;
	}
	return true;
}

float Global::getTileMapWidth()
{
	return tileMap->getMapSize().width * tileMap->getTileSize().width;
}

float Global::getTileMapHeight()
{
	return tileMap->getMapSize().height * tileMap->getTileSize().height;
}
#include "Global.h"

DECLARE_SINGLETON_MEMBER(Global);

Global::Global(void)
{

}

Global::~Global(void)
{
	CC_SAFE_DELETE(gameLayer);
	CC_SAFE_DELETE(operateLayer);
	CC_SAFE_DELETE(stateLayer);
	CC_SAFE_DELETE(hero);
	CC_SAFE_DELETE(enemies);
	//CC_SAFE_DELETE(tileMap);
	gameLayer = NULL;
	operateLayer = NULL;
	stateLayer = NULL;
	hero = NULL;
	enemies = NULL;
	tileMap = NULL;
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
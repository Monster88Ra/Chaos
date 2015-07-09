#include "MapLayer.h"
#include "Other\Resources.h"
#include <algorithm>
USING_NS_CC;	

MapLayer::MapLayer()
{

}

MapLayer::~MapLayer()
{
}

bool MapLayer::init()
{
	bool ret = false;

	do{
		CC_BREAK_IF(!Layer::init() );
		//m_tileMap = initMapWithFile(stmx_QingQiuMountain);
		m_tileMap = initMapWithFile(global->sceneInfoVector[global->sceneIndex]->mapName);
		m_tileMap->getLayer("Meta")->setVisible(false);
		this->scheduleUpdate();
		ret = true;
	}while(0);

	return ret;
}
TMXLayer* MapLayer::getMaskLayer()
{
	return m_tileMap->getLayer("Mask");
}
TMXTiledMap* MapLayer::initMapWithFile(const char *name)
{
	TMXTiledMap *tileMap;

	std::string path;
	std::string maps("Maps");
	auto iterFind = std::find(searchPaths.begin(), searchPaths.end(), maps);
	if (iterFind == searchPaths.end())
		CCAssert(iterFind != searchPaths.end(), "Maps in vector searchPaths not for");
	else
	{
		path = maps + '/' + name;
		tileMap = TMXTiledMap::create(path);
		CCAssert(tileMap != nullptr, "tileMap == NULL");
		tileMap->setPosition(Vec2(0, 0));
		this->addChild(tileMap);
	}
	global->tileMap = tileMap;
	return tileMap;
}

void MapLayer::update(float dt)
{
	this->setViewpointCenter(global->hero->getPosition());
}

void MapLayer::setViewpointCenter(Point pos)
{
	Size winSize = Director::getInstance()->getWinSize();
	auto _map = global->tileMap;

	//如果主角坐标小于屏幕的一半，则取屏幕中点坐标，否则取对象的坐标  
	int x = MAX(pos.x, winSize.width / 2);
	int y = MAX(pos.y, winSize.height / 2);

	//如果X、Y的坐标大于右上角的极限值，则取极限值的坐标（极限值是指不让地图超出屏幕造成出现黑边的极限坐标 )
	x = MIN(x, (_map->getMapSize().width * _map->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_map->getMapSize().height * _map->getTileSize().height) - winSize.height / 2);

	//对象当前所在坐标
	Point actualPosition = Vec2(x, y);

	//计算屏幕中点和所要移动的目的点之间的距离
	Point centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Point viewPoint = centerOfView - actualPosition;

	//设定一下地图的位置 ,这里一定要注意,单纯移动自己或者是_MAP移动都是无效的,在这里足足卡了好长时间
	//_map->setPosition(viewPoint);  
	//this->setPosition(viewPoint);
	//global->gameLayer->setPosition(viewPoint);
	this->getParent()->setPosition(viewPoint);
}
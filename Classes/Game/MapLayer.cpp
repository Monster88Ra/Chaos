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

	//�����������С����Ļ��һ�룬��ȡ��Ļ�е����꣬����ȡ���������  
	int x = MAX(pos.x, winSize.width / 2);
	int y = MAX(pos.y, winSize.height / 2);

	//���X��Y������������Ͻǵļ���ֵ����ȡ����ֵ�����꣨����ֵ��ָ���õ�ͼ������Ļ��ɳ��ֺڱߵļ������� )
	x = MIN(x, (_map->getMapSize().width * _map->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_map->getMapSize().height * _map->getTileSize().height) - winSize.height / 2);

	//����ǰ��������
	Point actualPosition = Vec2(x, y);

	//������Ļ�е����Ҫ�ƶ���Ŀ�ĵ�֮��ľ���
	Point centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Point viewPoint = centerOfView - actualPosition;

	//�趨һ�µ�ͼ��λ�� ,����һ��Ҫע��,�����ƶ��Լ�������_MAP�ƶ�������Ч��,���������㿨�˺ó�ʱ��
	//_map->setPosition(viewPoint);  
	//this->setPosition(viewPoint);
	//global->gameLayer->setPosition(viewPoint);
	this->getParent()->setPosition(viewPoint);
}
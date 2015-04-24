#ifndef _MAP_LAYER_H
#define _MAP_LAYER_H

#include "cocos2d.h"
USING_NS_CC;
#include "Other\Global.h"
class MapLayer:public cocos2d::Layer
{
public:
	MapLayer();
	~MapLayer();
	virtual bool init();
	TMXLayer* getMaskLayer();
	void update(float dt);
	void setViewpointCenter(Point pos);
	CREATE_FUNC(MapLayer);
private:
	TMXTiledMap* initMapWithFile(const char * path);
	TMXTiledMap* m_tileMap;
};
#endif
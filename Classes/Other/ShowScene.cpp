#include "ShowScene.h"

USING_NS_CC;

Scene* ShowScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ShowLayer::create();

	scene->addChild(layer);
	return scene;
}


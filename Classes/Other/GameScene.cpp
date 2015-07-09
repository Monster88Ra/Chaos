#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto gameLayer = GameLayer::create();

	scene->addChild(gameLayer, 0);

	auto operateLayer = OperateLayer::create();
	scene->addChild(operateLayer,1);

	auto stateLayer = StateLayer::create();
	scene->addChild(stateLayer);

	return scene;
}
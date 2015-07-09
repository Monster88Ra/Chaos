#include "DialogScene.h"

USING_NS_CC;

Scene* DialogScene::createScene()
{
	auto scene = Scene::create();
	auto dialogLayer = DialogLayer::create();

	
	scene->addChild(dialogLayer);

	return scene;
}
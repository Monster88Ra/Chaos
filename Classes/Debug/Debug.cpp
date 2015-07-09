#include "Debug\Debug.h"

USING_NS_CC;

Scene * Debug::createScene() {
	auto scene = Scene::create();
	auto layer = Debug::create();
	scene->addChild(layer);
	return scene;
}
static Size visibleSize;
static Vec2 origin;
bool Debug::init() {
	if (!Layer::init()) {
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	return true;
}

void Debug::draw(Renderer *renderer, const Mat4 &transform, bool transformUpdated)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(Debug::onDraw, this, transform, transformUpdated);
	renderer->addCommand(&_customCommand);
}
void Debug::onDraw(const Mat4 &transform, bool transformUpdated)
{
	// ÀûÓÃStack»º´æ
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	CHECK_GL_ERROR_DEBUG();
	// »­±ß¿ò
	DrawPrimitives::setDrawColor4B(255, 255, 255, 255);
	glLineWidth(4);
	Vec2 vertices[] = { Vec2(1, 1), Vec2(1, visibleSize.height - 1), Vec2(visibleSize.width - 1, visibleSize.height - 1), Vec2(visibleSize.width - 1, 1) };
	DrawPrimitives::drawPoly(vertices, 4, true);

	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
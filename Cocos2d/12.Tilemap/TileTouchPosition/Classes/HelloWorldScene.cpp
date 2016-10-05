#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
	map = TMXTiledMap::create("tilemap/iso-test-touch.tmx");
	this->addChild(map, 0, 1);

	Size s = map->getContentSize();
	log("ContentSize: %f, %f", s.width, s.height);

	map->setPosition(Vec2(0, 0));

    return true;
}


void HelloWorld::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	auto touchPoint = touch->getLocation();
	touchPoint = map->convertToNodeSpace(touchPoint);

	Vec2 pos = TouchToXY(touchPoint, 10);

	log("gid.x = %f, gid.y = %f", pos.x, pos.y);

	return true;

}
void HelloWorld::onTouchMoved(Touch* touch, Event* event) {

}

void HelloWorld::onTouchEnded(Touch* touch, Event* event) {

}

Vec2 HelloWorld::TouchToXY(Vec2 touch, int mapsize) {
	Size ts = map->getTileSize();
	int isoy = (((touch.y / ts.height) + (touch.x - (mapsize*ts.width / 2)) / ts.width) - mapsize)*-1;
	int isox = (((touch.y / ts.height) - (touch.x - (mapsize*ts.width / 2)) / ts.width) - mapsize)*-1;

	return Vec2(isox, isoy);
}











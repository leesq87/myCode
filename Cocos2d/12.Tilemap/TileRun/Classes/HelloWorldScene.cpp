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
	winSize = Director::getInstance()->getWinSize();

	tMap = TMXTiledMap::create("tilemap/background.tmx");
	background = tMap->getLayer("background");
	MetaInfo = tMap->getLayer("MetaInfo");
	MetaInfo->setVisible(false);

	auto move = MoveBy::create(0.1, Vec2(-32, 0));
	auto rep = RepeatForever::create(move);
	tMap->runAction(rep);

	this->addChild(tMap);
	

	pWoman = Sprite::create("Images/grossinis_sister1.png");
	pWoman->setPosition(Vec2(96, 98));
	pWoman->setScale(0.5);
	this->addChild(pWoman);
	
	this->schedule(schedule_selector(HelloWorld::check), 0.5);
    return true;
}

void HelloWorld::check(float f) {
	if (tMap->getPosition().x <= -1000) {
		tMap->setPosition(Vec2(-32, 0));
	}


}
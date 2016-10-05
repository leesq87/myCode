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
    
	Size winSize = Director::getInstance()->getWinSize();

	//화면구성용 레이어 추가
	auto bgLayer = LayerColor::create(Color4B(0, 255, 0, 255), winSize.width, winSize.height);
	bgLayer->setAnchorPoint(Vec2(0, 0));
	bgLayer->setRotation3D(cocos2d::Vertex3F(-20, 0, 0));
	this->addChild(bgLayer);

	auto bgSprite = Sprite::create("Images/HelloWorld.png");
	bgSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	bgLayer->addChild(bgSprite);

	auto man = Sprite::create("Images/grossini.png");
	man->setPosition(Vec2(240, - 50));
	bgLayer->addChild(man);

	//auto act = MoveBy::create(2, Vec2(0, 450));
	//auto seq = Sequence::create(Place::create(vertex2(240, -50)), act, nullptr);

	auto act = MoveBy::create(2, Vec2(0, -500));
	auto seq = Sequence::create(Place::create(Vec2(240, 380)), act, nullptr);

	auto rep = RepeatForever::create(seq);
	man->runAction(rep);


    return true;
}


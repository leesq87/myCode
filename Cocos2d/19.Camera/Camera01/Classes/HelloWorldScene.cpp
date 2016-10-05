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
    
	Vec2 point1 = Vec2(240 - 80, 160);
	Vec2 point2 = Vec2(240 + 80, 160);

	auto pWomen1 = Sprite::create("Images/grossinis_sister1.png");
	pWomen1->setPosition(point1);
	this->addChild(pWomen1);

	auto pWomen2 = Sprite::create("Images/grossinis_sister2.png");
	pWomen2->setPosition(point2);
	this->addChild(pWomen2);

	Size winSize = Director::getInstance()->getWinSize();
	Vec2 center = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 diff = center - point1;

	auto act1 = ScaleBy::create(0.5f, 2.0f);
	auto act1b = act1->reverse();
	auto act2 = MoveBy::create(0.5f, diff);
	auto act2b = act2->reverse();

	auto spa1 = Spawn::create(act1, act2, nullptr);
	auto spa2 = Spawn::create(act1b, act2b, nullptr);

	//auto spa1 = Spawn::create(act1, nullptr);
	//auto spa2 = Spawn::create(act1b, nullptr);

	auto seq = Sequence::create(spa1, spa2, nullptr);


	auto rep = RepeatForever::create(seq);

	this->runAction(rep);

    return true;
}


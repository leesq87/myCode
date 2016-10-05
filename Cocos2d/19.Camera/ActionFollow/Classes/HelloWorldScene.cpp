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
    
	auto pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 160));
	this->addChild(pMan);

	auto pR1 = Sprite::create("Images/r1.png");
	pR1->setPosition(Vec2(25, 160));
	this->addChild(pR1);

	auto pR2 = Sprite::create("Images/r1.png");
	pR2->setPosition(Vec2(960 - 25, 160));
	this->addChild(pR2);


	auto move = MoveBy::create(2, Vec2(480 * 2 - 100, 0));
	auto move_back = move->reverse();
	auto seq = Sequence::create(move, move_back, nullptr);
	auto rep = RepeatForever::create(seq);

	pMan->runAction(rep);
	
	this->runAction(Follow::create(pMan, Rect(0, 0, 480 * 2, 320)));
    return true;
}


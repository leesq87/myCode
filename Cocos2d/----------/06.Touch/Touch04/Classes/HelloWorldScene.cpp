#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    
	auto pLabel1 = LabelTTF::create("Fixed priority test", "Arial", 20);
	pLabel1->setPosition(Vec2(240, 300));
	pLabel1->setColor(Color3B(0, 0, 0));
	this->addChild(pLabel1, 101);

	auto pLabel2 = LabelTTF::create("Fixed Priority, Blue: 30, Red: 20, Yellow: 10\n""작은수가 더 높은 우선순위를 가집니다", "Arial", 14);
	pLabel2->setPosition(Vec2(240, 270));
	pLabel2->setColor(Color3B::BLUE);
	this->addChild(pLabel2, 101);

	sprite1 = new Monster();
	sprite1->setTexture("Images/CyanSquare.png");
	sprite1->setPosition(Vec2(240, 120) + Vec2(-80, 80));
	sprite1->setPriority(30);
	this->addChild(sprite1);

	sprite2 = new Monster();
	sprite2->setTexture("Images/MagentaSquare.png");
	sprite2->setPosition(Vec2(240, 120));
	this->addChild(sprite2);

	sprite3 = new Monster();
	sprite3->setTexture("Images/YellowSquare.png");
	sprite3->setPosition(Vec2(0, 0));
	sprite3->setPriority(10);
	sprite2->addChild(sprite3);
    return true;
}


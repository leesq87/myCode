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

	auto parent = Sprite::create("Images/white-512x512.png");
	parent->setTextureRect(Rect(0, 0, 150, 150));
	parent->setPosition(Vec2(240, 160));
	parent->setColor(Color3B::BLUE);
	this->addChild(parent);

	auto child = Sprite::create("Images/white-512x512.png");
	child->setTextureRect(Rect(0, 0, 50, 50));
	child->setPosition(Vec2(0, 0));
	child->setColor(Color3B::RED);
	parent->addChild(child);




    return true;
}


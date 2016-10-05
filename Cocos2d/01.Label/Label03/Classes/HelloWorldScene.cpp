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
    
	auto pLabel1 = LabelTTF::create("hello 월드", "Arial", 34);

	pLabel1->setPosition(Vec2(240, 250));

	pLabel1->setColor(Color3B::BLACK);

	pLabel1->setOpacity(100.0);

	this->addChild(pLabel1);

	auto pLabel2 = LabelBMFont::create("hello", "futura-48.fnt");

	pLabel2->setPosition(Vec2(240, 150));

	this->addChild(pLabel2);
	auto pLabel3 = LabelAtlas::create("1234", "fps_images.png",12, 32, '.');

	pLabel3->setPosition(Vec2(240, 50));

	this->addChild(pLabel3);

	
	return true;
}


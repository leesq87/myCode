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
    
	auto mask = Sprite::create("mask.png");
	
	auto content = Sprite::create("Calendar1.png");
	
	auto clipper = ClippingNode::create();
	clipper->setStencil(mask);
	clipper->setAlphaThreshold(0.05);
	clipper->setPosition(Vec2(240, 160));
	clipper->addChild(content);

	this->addChild(clipper);
    return true;
}


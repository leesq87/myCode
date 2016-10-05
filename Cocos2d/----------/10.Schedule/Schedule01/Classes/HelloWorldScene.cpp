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
    
	nNum = 0;

	this->schedule(schedule_selector(HelloWorld::callEveryFrame));
	this->schedule(schedule_selector(HelloWorld::myTick), 1.0f);

	//딜레이타임 후 한번 실행하기
	this->scheduleOnce(schedule_selector(HelloWorld::myTickOnce), 3);

	
    return true;
}

void HelloWorld::callEveryFrame(float f) {
	nNum++;
	if (nNum > 60) {
		nNum = 1;
	}

	log("fps..%d", nNum);
}

void HelloWorld::myTick(float f) {
	log("tick");
}

void HelloWorld::myTickOnce(float f) {
	log("tickOnce after delay");
}
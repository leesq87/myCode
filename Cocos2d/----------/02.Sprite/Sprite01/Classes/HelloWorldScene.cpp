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

    //스프라이트 생성 및 초기화
	auto pMan = Sprite::create("Images/grossini.png");
	// 스프라이트 위치 지정
	pMan->setPosition(Vec2(240, 160));

	//레이어에 스프라이트 객체 추가
//	this->addChild(pMan);
//	this->addChild(pMan, 3);
	this->addChild(pMan);

	auto pWoman = Sprite::create("Images/grossinis_sister1.png");

	pWoman->setPosition(Vec2(260, 160));


	this->addChild(pWoman, 1);

	// 스프라이트 위치 동적 지정
	pMan->setLocalZOrder(1);


    return true;
}


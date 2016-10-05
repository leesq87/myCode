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
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)))
    {
        return false;
    }
	// 레이블 생성 및 초기화1
	auto pLabel = LabelTTF::create("동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라 만세", "Arial:", 32, Size(300,200), TextHAlignment::CENTER, TextVAlignment::CENTER);

	//레이블의 위치 지정
	pLabel->setPosition(Vec2(240, 160));
	//pLabel->setAnchorPoint(0);
	
	//레이블의 색 지정
	// pLabel->setColor(Color3B(0,0,0));; // 255,0,0
	pLabel->setColor(Color3B::BLACK);

	//레이블의 투명도 지정
	pLabel->setOpacity(100.0);
	
	//레이블에 레이블 객체 추가
	this->addChild(pLabel);

    return true;
}


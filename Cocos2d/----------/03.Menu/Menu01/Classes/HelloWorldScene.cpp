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
    
	//메뉴 아이템 생성 및 초기화,이미지
	auto pMenuItem1 = MenuItemImage::create("Images/btn-play-normal.png", "Images/btn-play-selected.png", CC_CALLBACK_1(HelloWorld::doClick1, this));
	auto pMenuItem2 = MenuItemImage::create("Images/btn-highscores-normal.png", "Images/btn-highscores-selected.png", CC_CALLBACK_1(HelloWorld::doClick2, this));
	auto pMenuItem3 = MenuItemImage::create("Images/btn-about-normal.png", "Images/btn-about-selected.png", CC_CALLBACK_1(HelloWorld::doClick3, this));

	//메뉴 생성
	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, pMenuItem3, nullptr);

	pMenu->alignItemsVertically();

	this->addChild(pMenu);

    return true;
}

void HelloWorld::doClick1(Ref *pSender) {
	log("첫 번째 메뉴가 선택됨");
}

void HelloWorld::doClick2(Ref *pSender) {
	log("두 째 메뉴가 선택됨");
}
void HelloWorld::doClick3(Ref *pSender) {
	log("세 번째 메뉴가 선택됨");
}

#include "HelloWorldScene.h"
#include "SecondScene.h"

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
    
	auto pMenuItem = MenuItemFont::create("팝업창 띄우기", CC_CALLBACK_1(HelloWorld::doPopup, this));
	pMenuItem->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(pMenuItem, nullptr);

	pMenu->setPosition(Vec2(240, 40));
	this->addChild(pMenu);

	//노티피케이션 리시버 등록
	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HelloWorld::doMsgReceived), "TouchStatus", nullptr);

	
    return true;
}

void HelloWorld::doPopup(Ref* obj) {
	//팝업 레이어 삽입
	Scene* popWin;
	popWin = SecondScene::createScene();
	this->addChild(popWin, 2000, 2000);
}

void HelloWorld::doMsgReceived(Ref* obj) {
	//int pParam = (int)obj;
	//log("[%d] aptlwl ehckr",pParam);

	char* inputStr = (char*)obj;
	char testText[20];
	sprintf(testText, "%s", inputStr);
	log("[%s] 메시지 도착", testText);
}



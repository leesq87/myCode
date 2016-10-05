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
    
	auto pMenuItem = MenuItemFont::create("Action", CC_CALLBACK_1(HelloWorld::doAction, this));

	pMenuItem->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(pMenuItem, nullptr);

	pMenu->setPosition(Vec2(240, 50));

	this->addChild(pMenu);

	pBall = Sprite::create("Images/r1.png");
	pBall->setPosition(Vec2(50, 100));
	pBall->setScale(0.7f);
	this->addChild(pBall);

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 150));
	pMan->setScale(0.5f);
	this->addChild(pMan);

	pWomen1 = Sprite::create("Images/grossinis_sister1.png");
	pWomen1->setPosition(Vec2(50, 220));
	pWomen1->setScale(0.5f);
	this->addChild(pWomen1);

	pWomen2 = Sprite::create("Images/grossinis_sister2.png");
	pWomen2->setPosition(Vec2(50, 280));
	pWomen2->setScale(0.5f);
	this->addChild(pWomen2);

    return true;
}


void HelloWorld::doAction(Ref* pSender) {
	doActionReset();

	auto move = MoveBy::create(3, Vec2(400, 0));

	////속도----------------------
	////빨라지기 : 시작이 늦고 나중에 빠름
	//auto ease_in = EaseIn::create(move->clone(), 4);
	////느려지기 : 시작이 빠르고 나중에 느림
	//auto ease_out = EaseOut::create(move->clone(), 4);
	////빨라졌다 느려지기 : 시작과 끝이 빠르고 중간이 늦음
	//auto ease_inout1 = EaseInOut::create(move->clone(), 4);

	////EaseExponentialIn,EaseExponentialOut,EaseExponentialInOut -> 가속도가 심함
	////EaseSineIn,EaseSineOut,EaseSineInOut -> 가속도가 완화됨

	////탄성---------------------------
	//auto ease_in = EaseElasticIn::create(move->clone(), 0.4f);
	//auto ease_out = EaseElasticOut::create(move->clone(), 0.4f);
	//auto ease_inout1 = EaseElasticInOut::create(move->clone(), 0.4f);

	////바운스--------------------------
	//auto ease_in = EaseBounceIn::create(move->clone());
	//auto ease_out = EaseBounceOut::create(move->clone());
	//auto ease_inout1 = EaseBounceInOut::create(move->clone());

	//속도조정
	auto ease_in = Speed::create(move->clone(), 1);
	auto ease_out = Speed::create(move->clone(), 2);
	auto ease_inout1 = Speed::create(move->clone(), 3);


	pBall->runAction(move);
	pMan->runAction(ease_in);
	pWomen1->runAction(ease_out);
	pWomen2->runAction(ease_inout1);

}

void HelloWorld::doActionReset() {

	pBall->setPosition(Vec2(50, 100));
	pBall->setScale(0.7f);

	pMan->setPosition(Vec2(50, 150));
	pMan->setScale(0.5f);

	pWomen1->setPosition(Vec2(50, 220));
	pWomen1->setScale(0.5f);

	pWomen2->setPosition(Vec2(50, 280));
	pWomen2->setScale(0.5f);

}

#include "HelloWorldScene.h"
#include <time.h>
#include <stdlib.h>

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
    if ( !LayerColor::initWithColor(Color4B(0,0,0,0)) )
    {
        return false;
    }
	underMole1 = true;
	underMole2 = true;
	underMole3 = true;
	srand((unsigned int)time(NULL));

	grassUpper = Sprite::create("grass_upper.png");
	grassUpper->setPosition(Vec2(240, 240));
	this->addChild(grassUpper);
	
	grassLower = Sprite::create("grass_lower.png");
	grassLower->setPosition(Vec2(240, 81));
	this->addChild(grassLower,3);
	
	
	mole1 = Sprite::create("mole_1.png");
	mole1->setPosition(Vec2(95, 95));
	this->addChild(mole1,2);

	mole2 = Sprite::create("mole_1.png");
	mole2->setPosition(Vec2(240, 95));
	this->addChild(mole2, 2);

	mole3 = Sprite::create("mole_1.png");
	mole3->setPosition(Vec2(385, 95));
	this->addChild(mole3, 2);
	
	this->schedule(schedule_selector(HelloWorld::callRandomNum), 0.1);
	
    return true;
}

void HelloWorld::callMole1() {
	underMole1 = false;
	auto up = MoveBy::create(0.2, Vec2(0, 80));
	auto down = up->reverse();
	auto action = Sequence::create(up, DelayTime::create(0.5), down, nullptr);
	mole1->runAction(action);
}

void HelloWorld::callMole2() {
	underMole2 = false;
	auto up = MoveBy::create(0.2, Vec2(0, 80));
	auto down = up->reverse();
	auto action = Sequence::create(up, DelayTime::create(0.5), down, nullptr);
	mole2->runAction(action);
}

void HelloWorld::callMole3() {
	underMole3 = false;

	auto up = MoveBy::create(0.2, Vec2(0, 80));
	auto down = up->reverse();
	auto action = Sequence::create(up, DelayTime::create(0.5), down, nullptr);
	mole3->runAction(action);
}

void HelloWorld::callRandomNum(float f) {
	int RandomNum = RandomNumCreate();
	log  ("%d", RandomNum);
	if (mole1->getPositionY() == 95)
		underMole1 = true;
	if (mole2->getPositionY() == 95)
		underMole2 = true;
	if (mole3->getPositionY() == 95)
		underMole3 = true;

	if (RandomNum == 1 && underMole1 ==true)
		callMole1();

	if (RandomNum == 2 && underMole2 == true)
		callMole2();

	if (RandomNum == 3 && underMole3 == true)
		callMole3();
}

int HelloWorld::RandomNumCreate() {
	int a;
	a = rand() % 10;
	return a;
}


void HelloWorld::onEnter() {
	Layer::onEnter();

	//싱글 터치 모드로 터치 리스너 등록
	auto listener = EventListenerTouchOneByOne::create();
	//Swallow touches only abailable in OneByOne mode
	//핸들링된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미다.

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
//	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
//	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	//the priority of the touch listener is based on the draw order of sprite
	//터치 리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}

//처음 손가락이 화면에 닿는 순간 호출된다.
bool HelloWorld::onTouchBegan(Touch *touch, Event *event) {
	auto touchPoint = touch->getLocation();

	log("onTouchBegan id = %d, x = %f, y= %f", touch->getID(), touchPoint.x, touchPoint.y);

	//touch check------------------------------
	bool moletouch1 = mole1->getBoundingBox().containsPoint(touchPoint);
	bool moletouch2 = mole2->getBoundingBox().containsPoint(touchPoint);
	bool moletouch3 = mole3->getBoundingBox().containsPoint(touchPoint);
	bool lowertouch = grassLower->getBoundingBox().containsPoint(touchPoint);

	if (moletouch1==true && lowertouch ==false) {
		log("moletouch1 touch");
	}
	if (moletouch2 && lowertouch == false) {
		log("moletouch2 touch");
	}
	if (moletouch3 && lowertouch == false) {
		log("moletouch3 touch");
	}

	return true;
}


// 손가락을 화면에서 떼지 않고 이리저리 움직일 때 계속해서 호출된다.
//얼마나 자주 호출되느냐는 전적으로
//이벤트를 핸들링하는 애플리케이션의 Run Loop에 달렸다.
/*
void HelloWorld::onTouchMoved(Touch *touch, Event *event) {
	auto touchPoint = touch->getLocation();

	log("onTouchMoved id= %d, x = %f, y= %f", touch->getID(), touchPoint.x, touchPoint.y);
}

//손가락을 화면에서 떼는 순간 호출된다
void HelloWorld::onTouchEnded(Touch *touch, Event *event) {
	auto touchPoint = touch->getLocation();

	log("onTouchEnded id= %d, x = %f, y= %f", touch->getID(), touchPoint.x, touchPoint.y);
}

//시스템이 터치를 중지시키는 경우에 호출된다

void HelloWorld::onTouchCancelled(Touch *touch, Event *event) {

}
*/

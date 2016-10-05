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
    
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::cahngeCameraAngle, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	auto sprite = Sprite::create("images/HelloWorld.png");
	sprite->setPosition(Vec2(240, 160));
	this->addChild(sprite);

	camera = new ActionCamera;
	camera->startWithTarget(this);
	
    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	return true;
}

void HelloWorld::cahngeCameraAngle(Touch* touch, Event* unused_event) {
	kmVec3 eye = camera->getEye();
	eye.x -= touch->getDelta().x *0.000000001;
	eye.y -= touch->getDelta().y *0.000000001;
	camera->setEye(eye);
}
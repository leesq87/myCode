#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

Vec2 HelloWorld::vec21(float x, float y) {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	return Vec2(x + origin.x, y + origin.y);
}

bool HelloWorld::init()
{
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    
	Size size1 = Director::getInstance()->getWinSize();
	Size size2 = Director::getInstance()->getVisibleSize();

	//Vec2 origin = Director::getInstace()->getVisibleOrigin();

	log("Size1 : %f.... %f", size1.width, size1.height);
	log("Size2 : %f.... %f", size2.width, size2.height);
	//log ("Origin : %f....%f",origin.x, origin.y);

	auto pBack = Sprite::create("HelloWorld.png");
	pBack->setPosition(Vec2(size1.width / 2, size1.height / 2));
	this->addChild(pBack);

	auto pBack1 = Sprite::create("blocks.png");
	pBack1->setPosition(Vec2(0, size1.height / 2));
	this->addChild(pBack1);

	auto pBack2 = Sprite::create("blocks.png");
	pBack2->setPosition(Vec2(size1.width, size1.height / 2));
	this->addChild(pBack2);

	auto pBack31 = Sprite::create("blocks.png");
	pBack31->setPosition(Vec2(size1.width/2-64,0));
	this->addChild(pBack31);

	auto pBack32 = Sprite::create("blocks.png");
	pBack32->setPosition(vec21(size1.width / 2 + 64, 0));
	this->addChild(pBack32);

	auto pBack41 = Sprite::create("blocks.png");
	pBack41->setPosition(Vec2(size1.width / 2 - 64, size1.height));
	this->addChild(pBack41);

	auto pBack42 = Sprite::create("blocks.png");
	pBack42->setPosition(Vec2(size1.width / 2 + 64, size1.height));
	this->addChild(pBack42);


    return true;
}

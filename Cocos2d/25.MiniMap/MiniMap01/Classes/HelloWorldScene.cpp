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
    
	Size winSize = Director::getInstance()->getWinSize();

	gameLayer = LayerColor::create(Color4B(255, 0, 0, 255), winSize.width, winSize.height);
	gameLayer->setAnchorPoint(Vec2(0, 0));
	gameLayer->setPosition(Vec2(0, 0));
	this->addChild(gameLayer);

	menuLayer = LayerColor::create(Color4B(0, 0, 0, 0), winSize.width, winSize.height);
	menuLayer->setAnchorPoint(Vec2(0, 0));
	menuLayer->setPosition(Vec2(0, 0));
	this->addChild(menuLayer);


	auto pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(60, 160));
	gameLayer->addChild(pMan);


	auto myActionForward = MoveBy::create(2, Vec2(380, 0));
	auto myActionBack = myActionForward->reverse();
	auto myAction = Sequence::create(myActionForward, myActionBack, nullptr);
	auto rep = RepeatForever::create(myAction);

	pMan->runAction(rep);

	auto pBack = Sprite::create("Images/minimap_back.png");
	pBack->setPosition(Vec2(400, 260));
	menuLayer->addChild(pBack);
	
	miniMap = RenderTexture::create(480, 320, Texture2D::PixelFormat::RGBA8888);
	miniMap->retain();
	miniMap->setPosition(400, 260);


    return true;
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	miniMap->begin();
	gameLayer->visit();
	miniMap->end();

	Sprite*	mms = miniMap->getSprite();
	mms->setScale(0.22f);
	mms->setScaleY(mms->getScaleY() * 1);
	menuLayer->addChild(miniMap);
	this->schedule(schedule_selector(HelloWorld::updateMinimap));
}

void HelloWorld::updateMinimap(float f) {
	miniMap->clear(0, 0, 0, 255);
	miniMap->begin();
	gameLayer->visit();
	miniMap->end();
}
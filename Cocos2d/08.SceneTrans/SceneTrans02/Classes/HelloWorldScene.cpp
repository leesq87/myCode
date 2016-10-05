#include "HelloWorldScene.h"
#include "SecondScene.h"


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

	auto item1 = MenuItemFont::create("pushSCene", CC_CALLBACK_1(HelloWorld::doChangeScene, this));
	item1->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(item1, nullptr);

	this->addChild(pMenu);

	log("HelloWorld:: init");

    return true;
}

void HelloWorld::doChangeScene(Ref *pSender) {
	//두번째 장면
	auto pScene = SecondScene::createScene();
	Director::getInstance()->replaceScene(pScene);

}

void HelloWorld::onEnter() {
	Layer::onEnter();

	log("HelloWorld:: onEnter");
}
void HelloWorld::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	log("HelloWorld :: onEnterTransitionDidFinish");
}


void HelloWorld::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	log("HelloWorld::onExitTransitionDidStart");

}

void HelloWorld::onExit() {
	Layer::onExit();

	log("HelloWorld::onExit");
}

HelloWorld::~HelloWorld() {
	log("HelloWorld:: dealloc:");
}


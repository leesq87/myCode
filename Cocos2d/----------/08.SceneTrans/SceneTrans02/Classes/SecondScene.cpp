#include "SecondScene.h"
#include "HelloWorldScene.h"

using namespace cocos2d;


Scene *SecondScene::createScene() {

	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SecondScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


// on "init" you need to initialize your instance
bool SecondScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(0, 255, 0, 255)))
	{
		return false;
	}

	auto item1 =MenuItemFont::create("Close Scene2", CC_CALLBACK_1(SecondScene::doClose, this));
	item1->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(item1, nullptr);

	pMenu->setPosition(240, 50);

	this->addChild(pMenu);

	log("Second Scene :: init");

	return true;
}


void SecondScene::onEnter() {
	Layer::onEnter();
	log("SecondScene :: onEnter");
}
void SecondScene::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	log("SecondScene :: onEnterTransitionDidFinish");
}


void SecondScene::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
	log("SecondScene::onExitTransitionDidStart");

}

void SecondScene::onExit() {
	Layer::onExit();

	log("SecondScene::onExit");
}

SecondScene::~SecondScene() {
	log("SecondScene:: dealloc:");
}


void SecondScene::doClose(Ref *pSender) {
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
}
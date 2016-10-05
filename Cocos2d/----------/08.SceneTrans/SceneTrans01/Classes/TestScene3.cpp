#include "TestScene3.h"
#include "HelloWorldScene.h"

USING_NS_CC;
using namespace cocos2d;

Scene* TestScene3::createScene()
{
	auto scene = Scene::create();

	auto layer = TestScene3::create();

	scene->addChild(layer);

	return scene;
}

bool TestScene3::init()
{

	if (!LayerColor::initWithColor(Color4B(0, 255, 255, 255)))
	{
		return false;
	}

	auto item1 = MenuItemFont::create("Close Scene3", CC_CALLBACK_1(TestScene3::doClose, this));
	item1->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(item1, nullptr);

	pMenu->setPosition(Vec2(240, 50));

	this->addChild(pMenu);


	return true;
}



void TestScene3::doClose(Ref *pSender) {
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
}
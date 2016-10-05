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
    
	statusLabel = LabelTTF::create("No custom Event received!", "", 20);
	statusLabel->setColor(Color3B::BLACK);
	statusLabel->setPosition(Vec2(240, 250));
	addChild(statusLabel);

	auto pMenuItem1 = MenuItemFont::create("Send Custom Event 1", CC_CALLBACK_1(HelloWorld::doClick1, this));
	pMenuItem1->setColor(Color3B(0, 0, 0));
	pMenuItem1->setPosition(Vec2(240, 160));

	auto pMenuItem2 = MenuItemFont::create("Send Custom Event 2", CC_CALLBACK_1(HelloWorld::doClick2, this));
	pMenuItem2->setColor(Color3B(0, 0, 0));
	pMenuItem2->setPosition(Vec2(240, 100));

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);
	pMenu->setPosition(Vec2(0, 0));
	this->addChild(pMenu);

    return true;
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	_listener1 = EventListenerCustom::create("game_custom_event_1", CC_CALLBACK_1(HelloWorld::doEvent1, this));

	_eventDispatcher->addEventListenerWithFixedPriority(_listener1, 1);

	/*
	_listener1 = EventListenerCustom::create("game_custom_event1", [=](EventCustom *event) {
		std::string str("Custom event1 received, ");
		char *buf = static_cast<char*>(event->getUserData());
		str += buf;
		str += " times";
		statusLabel->setString(str.c_str());
	});
	*/

	_listener2 = EventListenerCustom::create("game_custom_event_2", CC_CALLBACK_1(HelloWorld::doEvent2, this));

	_eventDispatcher->addEventListenerWithFixedPriority(_listener2, 1);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(_listener1);
	_eventDispatcher->removeEventListener(_listener2);

	Layer::onExit();
}

void HelloWorld::doClick1(Ref *pSender) {
	static int count = 0;
	++count;
	char *buf = new char[10];
	sprintf(buf, "%d", count);

	EventCustom event("game_custom_event_1");
	event.setUserData(buf);
	_eventDispatcher->dispatchEvent(&event);
}

void HelloWorld::doEvent1(EventCustom *event) {
	std::string str("Custom event 1 received, ");
	char *buf = static_cast<char*>(event->getUserData());
	str += buf;
	str += " times";
	statusLabel->setString(str.c_str());
	delete[] buf;
}

void HelloWorld::doClick2(Ref *pSender){
	static int count = 0;
	++count;
	char *buf = new char[10];
	sprintf(buf, "%d", count);

	EventCustom event("game_custom_event_2");
	event.setUserData(buf);
	_eventDispatcher->dispatchEvent(&event);

}

void HelloWorld::doEvent2(EventCustom *event) {
	std::string str("Custom event 2 received, ");
	char *buf = static_cast<char*>(event->getUserData());
	str += buf;
	str += " times";
	statusLabel->setString(str.c_str());
	delete[] buf;

}



















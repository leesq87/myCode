#include "TestScene2.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


//android effect olny support ogg
#if(CC_TARGET_PLATFORM ==CC_PLATFORM_ANDROID)
#define EFFECT_FILE "Sounds/effect2.ogg"
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
#define EFFECT_FILE "Sounds/effect1.raw"
#else
#define EFFECT_FILE "Sounds/effect1.wav"
#endif //CC_PLATFORM_ANDROID


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define MUSIC_FILE "Sounds/music.mid"
#elif(CC_TARGET_PLATFORM == CC_PALTFROM_BLACKBERRY)
#define MUSIC_FILE "Sounds/background.ogg"
#else
#define MUSIC_FILE "Sounds/background.mp3"
#endif //CC_PLATFORM_WIN32


//USING_NS_CC;
using namespace cocos2d;
using namespace CocosDenshion;


Scene* TestScene2::createScene()
{
	auto scene = Scene::create();

	auto layer = TestScene2::create();

	scene->addChild(layer);

	return scene;
}

bool TestScene2::init()
{

	if (!LayerColor::initWithColor(Color4B(255, 0, 255, 255)))
	{
		return false;
	}

	auto item1 = MenuItemFont::create("Close Scene2", CC_CALLBACK_1(TestScene2::doClose, this));
	item1->setColor(Color3B::BLACK);
	auto item2 = MenuItemFont::create("play background music", CC_CALLBACK_1(TestScene2::doSoundAction, this));
	item2->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(item1,item2, nullptr);
	pMenu->alignItemsVertically();


	//from1
	auto pWoman = Sprite::createWithSpriteFrameName("grossinis_sister1.png");
	pWoman->setPosition(Vec2(120, 220));
	this->addChild(pWoman);

	this->addChild(pMenu);


	return true;
}

void TestScene2::doClose(Ref *pSender) {
	auto pScene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(pScene);
}



void TestScene2::doSoundAction(Ref *pSender) {

	SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE, true);
}

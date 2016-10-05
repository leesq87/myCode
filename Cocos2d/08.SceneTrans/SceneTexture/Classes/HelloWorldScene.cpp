#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "TestScene2.h"


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
    

	//SpriteFrameCache는 여러개의 plist를 이용해서 사용할 수 있다.
	auto cache = SpriteFrameCache::getInstance();

	//첫 번째 스프라이트 시트의 위치정보 파일을 읽어들인다.
	//SpriteFrameCache에 addImage를 한 번에 해준다.
	cache->addSpriteFramesWithFile("animations/grossini_family.plist");

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_FILE);


	auto item1 = MenuItemFont::create("Replace Scene", CC_CALLBACK_1(HelloWorld::doReplaceScene, this));
	item1->setColor(Color3B::BLUE);


	auto pMenu = Menu::create(item1, nullptr);
	pMenu->alignItemsVertically();

	this->addChild(pMenu);


    return true;
}

void HelloWorld::onExit() {
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_FILE);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);

	SimpleAudioEngine::getInstance()->end();

	Layer::onExit();
}

void HelloWorld::doReplaceScene(Ref *pSender) {
	auto pScene = TestScene2::createScene();
	Director::getInstance()->replaceScene(pScene);
}



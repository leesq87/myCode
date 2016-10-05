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

std::string menuItems[] = {
	"play background music",
	"pause background music",
	"resume background music",
	"stop background music",
	"play effect",
	"play effect repeatly",
	"pause effect",
	"resume effect",
	"stop effect",
};

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
    
	//메뉴 아이템 생성 및 초기화

	auto pMenu = CCMenu::create();
	int nMenuCount = sizeof(menuItems) / sizeof(menuItems[0]);

	for (int i = 0; i < nMenuCount; ++i) {
		auto label = LabelTTF::create(menuItems[i].c_str(), "Arial", 24);
		label->setColor(Color3B(0, 0, 0));
		auto pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(HelloWorld::doSoundAction, this));
		pMenu->addChild(pMenuItem, i + 10000);
	}

	//메뉴 정렬
	pMenu->alignItemsVertically();

	//레이어에 메뉴 객체 추가

	this->addChild(pMenu);

	//preload background music and effect
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(MUSIC_FILE);
	SimpleAudioEngine::getInstance()->preloadEffect(EFFECT_FILE);

	//set default volume
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	
    return true;
}




void HelloWorld::onExit() {
	SimpleAudioEngine::getInstance()->unloadEffect(EFFECT_FILE);
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);

	SimpleAudioEngine::getInstance()->end();

	Layer::onExit();
}

void HelloWorld::doSoundAction(Ref *pSender) {
	auto pMenuItem = (MenuItem *)(pSender);
	int nIdx = pMenuItem->getZOrder() - 10000;

	switch (nIdx) {
		//play background music
	case 0:
		SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_FILE, true);
		break;
	case 1:
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		break;
	case 2:
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		break;
	case 3:
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		break;
	case 4:
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect(EFFECT_FILE);
		break;
	case 5:
		m_nSoundId = SimpleAudioEngine::getInstance()->playEffect(EFFECT_FILE, true);
		break;
	case 6:
		SimpleAudioEngine::getInstance()->pauseEffect(m_nSoundId);
		break;
	case 7:
		SimpleAudioEngine::getInstance()->resumeEffect(m_nSoundId);
		break;
	case 8:
		SimpleAudioEngine::getInstance()->stopEffect(m_nSoundId);
		break;
	}
}

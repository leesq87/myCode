#include "HelloWorldScene.h"

USING_NS_CC;

static std::string fontList[] = {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	"A Damn Mess",
	"Abberancy",
	"Abduction",
	"PaintBoy",
	"Schwarzwald Regular",
	"Scissor Cuts",
#else
	"fonts/A Damn Mess.ttf",
	"fonts/Abberancy. ttf",
	"fonts/Abduction.ttf",
	"fonts/Paint Boy.ttf",
	"fonts/Schwarzwald Regular.ttf",
	"fonts/Scissor Cuts.ttf",
#endif
};

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

	auto pLabel2 = LabelTTF::create("hello gikimi", fontList[5].c_str(), 34);

	pLabel2->setPosition(Vec2(240, 100));

	pLabel2->setColor(Color3B::BLACK);

	pLabel2->setOpacity(100);

	this->addChild(pLabel2);

    
    return true;
}


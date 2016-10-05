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
    
	//SpriteFrameCache는 여러개의 plist를 이용해서 사용할 수 있다.
	auto cache = SpriteFrameCache::getInstance();

	//첫 번째 스프라이트 시트의 위치정보 파일을 읽어들인다.
	//SpriteFrameCache에 addImage를 한 번에 해준다.
	cache->addSpriteFramesWithFile("animations/grossini_family.plist");

	//두 번째 스프라이트 시트의 위치정보 파일을 읽어들인다.
	cache->addSpriteFramesWithFile("animations/grossini.plist");

	//세 번째 : 개별 스파라이트를 직접 추가한다.
	auto pSprite = SpriteFrame::create("animations/blocks9.png", Rect(0, 0, 96, 96));
	cache->addSpriteFrame(pSprite, "blocks9.png");

	//from1
	auto pWoman = Sprite::createWithSpriteFrameName("grossinis_sister1.png");
	pWoman->setPosition(Vec2(120, 220));
	this->addChild(pWoman);

	//from2
	auto pMan = Sprite::createWithSpriteFrameName("grossini_dance_01.png");
	pMan->setPosition(Vec2(240, 200));
	this->addChild(pMan);

	//from3
	auto pBox = Sprite::createWithSpriteFrameName("blocks9.png");
	pBox->setPosition(Vec2(360, 220));
	this->addChild(pBox);

	//TextureCache는 하나의 텍스처만을 반환하므로 이전 것을 사용할 수 없다.
	//나중에 또 사용하려면 SpriteFrameCache에 createWithTexture로 저장해 둬야 한다.

	//첫 번째 텍스처 로드
	auto texture = Director::getInstance()->getTextureCache()->addImage("animations/grossini_dance_atlas.png");

	//스프라이트 생성 및 초기화
	auto pMan2 = Sprite::createWithTexture(texture, Rect(0, 0, 85, 121));
	pMan2->setPosition(Vec2(120, 100));
	this->addChild(pMan2);

	//두번째 텍스쳐 로드
	texture = Director::getInstance()->getTextureCache()->addImage("animations/dragon_animation.png");

	//스프라이트 생성 및 초기화
	auto pDragon = Sprite::createWithTexture(texture, Rect(0, 0, 130, 140));
	pDragon->setPosition(Vec2(240, 100));
	this->addChild(pDragon);

	//세 번째 텍스쳐 로드
	Director::getInstance()->getTextureCache()->addImageAsync("animations/blocks9.png", CC_CALLBACK_1(HelloWorld::ImageLoaded, this));

    
    return true;
}

//이미지가 메모리에 다 로딩되면 이 함수가 호출된다.
void HelloWorld::ImageLoaded(Ref *pSender) {
	auto tex = static_cast<Texture2D*>(pSender);
	auto sprite = Sprite::createWithTexture(tex);
	sprite->setPosition(Vec2(360, 100));

	this->addChild(sprite);

	log("Image loaded: %p", pSender);
}
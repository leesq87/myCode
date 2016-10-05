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
    //------------------------------------------------------------
	//Ttpe 1 : from Sprite
	//------------------------------------------------------------
	//auto sprite = Sprite::create("Images/grossini_dance_atlas.png");
	//auto texture1 = sprite->getTexture();

	//------------------------------------------------------------
	//Ttpe 2 : from texture
	//------------------------------------------------------------
	//auto texture2 = Director::getInstance()->getTextureCache()->addImage("Images/grossini_dance_atlas.png");

	//------------------------------------------------------------
	//Ttpe 3 : from BatchNode
	//------------------------------------------------------------
	//small capacity. Testing resizing.
	// Don't use capacity=1 in your real game. It is expensive to resize the capacity
	//auto batch = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 10);
	//auto texture3 = batch->getTexture();

	auto sprite = Sprite::create("Images/grossini_dance_atlas.png");
	auto texture = sprite->getTexture();

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3f);

	for (int i = 0; i < 14; i ++ ) {
		int column = i % 5;
		int row = i / 5;
		animation->addSpriteFrameWithTexture(texture, Rect(column * 85, row * 121, 85, 121));
	}

	// 스프라이트 생성 및 초기화
	auto pMan = Sprite::create("Images/grossini_dance_atlas.png", Rect(0, 0, 85, 121));
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan);

	//애니메이션 액션 실행
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pMan->runAction(rep);

    return true;
}


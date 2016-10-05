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
    
	//배치노드는 별도의 TextureCache를 지정하는 일 없이 자기 것을 자기가 직접 가지고 있다.
	//이미 자기의 텍스처이므로 해당 텍스처 안의 이미지는 얼마든지 사용해도
	//배치노드 안에서는 결국 하나로 처리한다.

	auto BatchNode = SpriteBatchNode::create("Images/grossini_dance_atlas.png", 50);
	this->addChild(BatchNode, 0, 1);

	auto texture = BatchNode->getTexture();

	for (int i = 0; i < 14; i++) {
		int column = i % 5;
		int row = i / 5;
		
		auto pTemp = Sprite::createWithTexture(texture, Rect(column * 85, row * 121, 85, 121));
		pTemp->setPosition(Vec2(column * 85, row * 121));

		BatchNode->addChild(pTemp);
	}

    return true;
}


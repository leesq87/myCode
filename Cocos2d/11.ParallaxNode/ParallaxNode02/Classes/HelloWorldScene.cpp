#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    
	auto background1 = Sprite::create("background1.png");
	background1->setAnchorPoint(Vec2(0, 0));

	auto background2 = Sprite::create("background2.png");
	background2->setAnchorPoint(Vec2(0, 0));


	//이미지가 만나는 가장자리에 검은 선이 생기는 현상을 방지하기위해
	//안티엘리어싱을 비활성화 한다
	background1->getTexture()->setAliasTexParameters();
	background2->getTexture()->setAliasTexParameters();


	//배경스프라이트를 담을 부모로 패럴렉스노드 만들기
	auto voidNode = ParallaxNode::create();

	//배경 스프라이트를 패럴렉스 노드에 넣는다.
	//이미지 사이즈는 512*320

	voidNode->addChild(background1, 1, Vec2(1, 1), Vec2(0, 0));
	voidNode->addChild(background2, 1, Vec2(1, 1), Vec2(512, 0));

	auto go = MoveBy::create(4, Vec2(-512, 0));
	auto goBack = go->reverse();
	auto seq = Sequence::create(go, goBack, nullptr);
	auto act = RepeatForever::create(seq);

	voidNode->runAction(act);

	this->addChild(voidNode);



    return true;
}


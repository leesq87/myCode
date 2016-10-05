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
    //배경레이어
	auto background = Sprite::create("Images/background.png");
	background->setAnchorPoint(Vec2(0, 0));

	//시뮬레이션 해상도 480*320
	//배경이미지 640*480

	//패럴랙스노드 생성
	auto voidNode = ParallaxNode::create();

	//패럴랙스노등에 배경 레이어 추가
	//다음은 배경이미지가 패럴랙스노드와 같은 비율로 x축으로만 움직인다.
	voidNode->addChild(background, 1, Vec2(1, 1), Vec2(0, -160));

	auto go = MoveBy::create(4, Vec2(-160, 0));
	auto goBack = go->reverse();
	auto seq = Sequence::create(go, goBack, nullptr);
	auto act = RepeatForever::create(seq);

	//다음 줄을 리마크하면 팰럴랙스노드에 배치된 스프라이트 및 이미지의 초기 위치를 볼 수 있다.

	voidNode->runAction(act);

	this->addChild(voidNode);
	
	//스프라이트
	auto cocosImage = Sprite::create("Images/powered.png");
	cocosImage->setAnchorPoint(Vec2(0, 0));

	auto gubun1 = LabelTTF::create("Start", "Arial", 64);
	gubun1->setPosition(Vec2(0, 240));
	gubun1->setAnchorPoint(Vec2(0, 0.5));

	auto gubun2 = LabelTTF::create("End", "Arial", 64);
	gubun2->setPosition(Vec2(640, 240));
	gubun2->setAnchorPoint(Vec2(1, 0.5));

	auto gubun3 = LabelTTF::create("80 Pixel", "Arial", 24);
	gubun3->setPosition(Vec2(80, 210));
	gubun3->setAnchorPoint(Vec2(0, 0.5));

	voidNode->addChild(cocosImage, 2, Vec2(2, 2), Vec2(240, 0));

	background->addChild(gubun1);
	background->addChild(gubun2);

	cocosImage->addChild(gubun3);


	return true;
}


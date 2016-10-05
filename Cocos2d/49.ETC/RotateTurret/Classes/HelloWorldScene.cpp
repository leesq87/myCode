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

	//화면 사이즈 구하기
	winSize = Director::getInstance()->getWinSize();

	//터렛 탐의 이미지
	player = Sprite::create("turret.png");
	player->setPosition(Vec2(player->getContentSize().width / 2 + 80, winSize.height / 2));
	this->addChild(player);

	//총알 벡터 초기화
	projectiles.clear();

	//상태 변수들 초기화
	bProjectile = false;

	//터치 이벤트 등록
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    

    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	if (bProjectile) {
		return true;
	}
	else {
		bProjectile = true;
	}

	auto touchPoint = touch->getLocation();

	//총알생성
	auto nextProjectile = Sprite::create("bullet2.png");

	//회전해야할 각도를 구한다.
	Vec2 shootVector = touchPoint - player->getPosition();
	float shootAngle = shootVector.getAngle();

	float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);

	//회전시간을 결정한다.
	float curAngle = player->getRotation();
	float rotateDiff = cocosAngle - curAngle;
	if (rotateDiff > 180)
		rotateDiff -= 360;
	if (rotateDiff < -180)
		rotateDiff += 360;
	float rotateSpeed = 0.5f / 180;
	float rotateDuration = fabsf(rotateDiff* rotateSpeed);

	//액션 실행
	auto actRotate1 = RotateTo::create(rotateDuration, cocosAngle);
	auto seqAct1 = Sequence::create(actRotate1, CallFunc::create(CC_CALLBACK_0(HelloWorld::finishRotate, this, nextProjectile)), nullptr);
	player->runAction(seqAct1);

	//총알을 화면 밖으로 보낸다
	shootVector.normalize();
	Vec2 overshotVector = shootVector * 420;

	//캐릭터와 같은 각도로 총알 방향 바꾸기 (회전)
	nextProjectile->setRotation(cocosAngle);

	//총알을 화면 밖으로 보낸다
	auto actMove2 = MoveBy::create(1.0f, overshotVector);
	auto seqAct2 = Sequence::create(actMove2, CallFunc::create(CC_CALLBACK_0(HelloWorld::spriteMoveFinished, this, nextProjectile)), nullptr);
	nextProjectile->runAction(seqAct2);

	//그로시니 애니메이션이 히든이다가 쇼하면 처음부터 하는지 확인

	return true;
}

void HelloWorld::finishRotate(Ref* sender) {
	Sprite* sprite = (Sprite *)sender;

	//ok to add new - we've finished rotation!
	Vec2 nPos1 = Vec2(player->getContentSize().width, player->getContentSize().height / 2);
	Vec2 nPos2 = player->convertToWorldSpace(nPos1);

	sprite->setPosition(nPos2);

	//화면에 추가
	//추가된 이후부터 액션이 런되는지 확인
	this->addChild(sprite);
	bProjectile = false;
}

void HelloWorld::spriteMoveFinished(Ref* sender){
	Sprite* sprite = (Sprite *)sender;
	this->removeChild(sprite, true);

	projectiles.eraseObject(sprite);

}
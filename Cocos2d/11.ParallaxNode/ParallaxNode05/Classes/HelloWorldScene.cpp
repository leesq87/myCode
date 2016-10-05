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
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	layer1 = Layer::create();
	this->addChild(layer1);

	layer2 = Layer::create();
	this->addChild(layer2);

	winSize = Director::getInstance()->getWinSize();

	//배경
	this->createBackgroundParallax();
	//드래곤
	this->createDragon();

	//메뉴
	this->createArrowButtons();


	return true;
}

void HelloWorld::createBackgroundParallax() {

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


	//auto go = MoveBy::create(4, Vec2(-512, 0));
	//auto goBack = go->reverse();
	//auto seq = Sequence::create(go, goBack, nullptr);
	//auto act = RepeatForever::create(seq);
	//voidNode->runAction(act);


	voidNode->setTag(1);

	layer1->addChild(voidNode, 0);

}
void HelloWorld::createDragon() {
	//움직이는 드래곤 넣기
	auto texture = Director::getInstance()->getTextureCache()->addImage("animations/dragon_animation.png");

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1);

	for (int i = 0; i < 6; i++) {
		int index = i % 4;
		int rowIndex = i / 4;

		animation->addSpriteFrameWithTexture(texture, Rect(index * 130, rowIndex * 140, 130, 140));
	}

	//스프라이트 생성 및 초기화

	dragon = Sprite::createWithTexture(texture, Rect(0, 0, 130, 140));
	dragon->setPosition(Vec2(240, 160));
	layer1->addChild(dragon);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	dragon->runAction(rep);

}

void HelloWorld::createArrowButtons() {
	//왼쪽화살표ㅕ
	leftSprite = Sprite::create("Images/b1.png");
	leftSprite->setPosition(Vec2(180, 30));

	layer2->addChild(leftSprite, 2);

	//눌렸을떄
	leftPressedSprite = Sprite::create("Images/b2.png");
	//self.leftSprite와 같은 위치에 표시
	leftPressedSprite->setPosition(leftSprite->getPosition());

	layer2->addChild(leftPressedSprite, 1);

	//오른쪽 화살표
	rightSprite = Sprite::create("Images/f1.png");
	rightSprite->setPosition(Vec2(300, 30));

	layer2->addChild(rightSprite, 2);

	//눌렸을떄
	rightPressedSprite = Sprite::create("Images/f2.png");
	//self.leftSprite와 같은 위치에 표시
	rightPressedSprite->setPosition(rightSprite->getPosition());

	layer2->addChild(rightPressedSprite, 1);
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	//싱글 터치 모드

	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}

#pragma mark -
#pragma mark Touch Event Handling

//손가락이 닫는 순간 호출

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
	//아래 boolen 변수 대신 leftsprite 와 rightsprite의 bisible 의 값을 직접 사용해도 무방

	isLeftPressed = false;
	isRightPressed = false;

	//터치가 왼쪽 또는 오른쪽 화살표 안에 들어있는지 확인
	if (this->isTouchInside(leftSprite, touch) == true) {
		//왼쪽 화살표를 안보이게, 눌린 이미지 표시
		leftSprite->setVisible(false);
		isLeftPressed = true;
	}

	else if (this->isTouchInside(rightSprite, touch) == true) {
		rightSprite->setVisible(false);
		isRightPressed = true;
	}

	//버튼이 눌리면 화면을 움직임

	if (isLeftPressed == true || isRightPressed == true)
		this->startMovingBackground();

	return true;
}

//손가락을 화면에서 떼지 않고 이리저리 움직일때 계속호출
void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
	//손가락이 버튼을 벗어나면 움직임을 중단
	if (isLeftPressed == true && this->isTouchInside(leftSprite, touch) == false) {
		leftSprite->setVisible(true);
		this->stopMovingBackground();
	}

	else if (isRightPressed == true && this->isTouchInside(rightSprite, touch) == false) {
		rightSprite->setVisible(true);
		this->stopMovingBackground();
	}
}


void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
	//배경화면을 멈춘다
	if (isLeftPressed == true || isRightPressed == true)
		this->stopMovingBackground();

	//감춰뒀던 이미지를 다시 보이게
	if (isLeftPressed == true)
		leftSprite->setVisible(true);

	if (isRightPressed == true)
		rightSprite->setVisible(true);
}

#pragma mark-
#pragma mark Game Play

//터치가 버튼 sprite 안에서 이뤄졌는지 확인

bool HelloWorld::isTouchInside(cocos2d::Sprite *sprite, cocos2d::Touch *touch) {

	//cocoa좌표
	auto touchPoint = touch->getLocation();
	bool bTouch = sprite->getBoundingBox().containsPoint(touchPoint);

	return bTouch;
}

void HelloWorld::startMovingBackground() {
	if (isLeftPressed == true && isRightPressed == true)
		return;
	log("start moving");
	this->schedule(schedule_selector(HelloWorld::moveBackground));
}

void HelloWorld::stopMovingBackground() {
	log("stop moving");
	this->unschedule(schedule_selector(HelloWorld::moveBackground));
}

void HelloWorld::moveBackground(float f) {
//	log("moving background");
	//매프레임마다 움직일 거리
	auto moveStep = 3;
	if (isLeftPressed) {
		moveStep = -3;
		dragon->setFlippedX(false);
	}
	else {
		moveStep = 3;
		dragon->setFlippedX(true);
	}

	auto newPos = Vec2(dragon->getPositionX() + moveStep, dragon->getPositionY());

	if (newPos.x < 0) {
		newPos.x = 0;
	}

	else if (newPos.x> 512 * 2) {
		newPos.x = 512*2;
	}
	dragon->setPosition(newPos);
	layer1->runAction(Follow::create(dragon, Rect(0, 0, 512 * 2, 320)));
}
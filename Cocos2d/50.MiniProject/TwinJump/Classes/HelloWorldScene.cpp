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
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}
	nNum = 0;
	cnt = 0;
	yPos = 80;
	nNum2 = 0;
	down = false;


	auto sprite = Sprite::create("player2.png");
	auto texture = sprite->getTexture();

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.03f);

	for (int i = 0; i < 10; i++) {
		int column = i % 18;
		int row = i / 18;
		animation->addSpriteFrameWithTexture(texture, Rect(column * 30, row * 30, 30, 30));
	}

	pRun = Sprite::create("player2.png", Rect(0, 0, 30, 30));
	pRun->setPosition(Vec2(140, yPos));
	pRun->setScale(2);
	this->addChild(pRun);

	auto animate = Animate::create(animation);
	auto repRun = RepeatForever::create(animate);
	pRun->runAction(repRun);

	pYpos = Sprite::create("Player2.png", Rect(0, 0, 1, 1));
	pYpos->setPosition(Vec2(0, 80));
	pYpos->setVisible(false);
	this->addChild(pYpos);

	pYpos2 = Sprite::create("Player2.png", Rect(0, 0, 1, 1));
	pYpos2->setPosition(Vec2(0, 0));
	pYpos2->setVisible(false);
	this->addChild(pYpos2);

	pYpos2 = Sprite::create("Player2.png", Rect(0, 0, 1, 1));
	pYpos2->setPosition(Vec2(0, 0));
	pYpos2->setVisible(false);
	this->addChild(pYpos2);

	/*
	auto pJumpItem = MenuItemFont::create("Jump!", CC_CALLBACK_1(HelloWorld::Jump, this));
	pJumpItem->setColor(Color3B::BLACK);
	auto pMenu = Menu::create(pJumpItem, nullptr);
	pMenu->alignItemsHorizontally();
	pMenu->setPosition(Vec2(340, 80));
	this->addChild(pMenu);
	*/
	return true;
}



void HelloWorld::onEnter() {
	Layer::onEnter();

	//싱글 터치 모드로 터치 리스너 등록
	auto listener = EventListenerTouchOneByOne::create();
	//Swallow touches only abailable in OneByOne mode
	//핸들링된 터치 이벤트를 터치 이벤트 array에서 지우겠다는 의미다.

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

	//the priority of the touch listener is based on the draw order of sprite
	//터치 리스너의 우선순위를 (노드가) 화면에 그려진 순서대로 한다.
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event) {
	Jump();
	return true;
}
//
////linear 완
//void HelloWorld::Jump() {
//	yPos = pRun->getPositionY();
//	if (yPos == 80) {
//		cnt = 0;
//		down = false;
//		temp = yPos;
//	}
//
//	if (cnt == 0) {
//		cnt++;
//		this->schedule(schedule_selector(HelloWorld::CallJump), 0.01f);
//	}
//	else if (cnt == 1) {
//		cnt++;
//		yPos = pRun->getPositionY();
//		temp = yPos + 80;
//		this->unschedule(schedule_selector(HelloWorld::CallJump));
//		this->schedule(schedule_selector(HelloWorld::CallJump2), 0.01f);
//	}
//}
//
//void HelloWorld::CallJump(float f) {
//	if (down == false) {
//		yPos = pRun->getPositionY();
//		yPos++;
//		pRun->setPosition(Vec2(140, yPos));
//		if (yPos == 160)
//			down = true;
//	}
//	if (down == true) {
//		yPos = pRun->getPositionY();
//		yPos--;
//		pRun->setPosition(Vec2(140, yPos));
//		if (yPos == 80) {
//			cnt = 0;
//			down = false;
//			this->unschedule(schedule_selector(HelloWorld::CallJump));
//		}
//	}
//}
//
//void HelloWorld::CallJump2(float f) {
//	if (down == false) {
//		yPos = pRun->getPositionY();
//		yPos++;
//		pRun->setPosition(Vec2(140, yPos));
//		if (yPos >= temp)
//			down = true;
//	}
//	if (down == true) {
//		yPos = pRun->getPositionY();
//		yPos--;
//		pRun->setPosition(Vec2(140, yPos));
//		if (yPos == 80) {
//			cnt = 0;
//			down = false;
//			this->unschedule(schedule_selector(HelloWorld::CallJump2));
//		}
//	}
//}


//
//// ease 미완
//
//
//void HelloWorld::Jump() {
//	yPos = pRun->getPositionY();
//	if (yPos == 80) {
//		cnt = 0;
//		down = false;
//		temp = yPos;
//	}
//
//	if (cnt == 0) {
//		cnt++;
//		GetY();
//		this->schedule(schedule_selector(HelloWorld::CallJump), 0.01f);
//	}
//	else if (cnt == 1 && down==false) {
//		cnt++;
//		yPos = pRun->getPositionY();
//		temp = yPos + 80;
//		pYpos3->setPosition(Vec2(0, temp));
//		GetY3();
//		tempY = yPos;
//		GetY2();
//		this->unschedule(schedule_selector(HelloWorld::CallJump));
//		this->schedule(schedule_selector(HelloWorld::CallJump2), 0.01f);
//	}
//}
//
//
//void HelloWorld::CallJump(float f) {
//	if (down ==false) {
//		yPos = pYpos->getPositionY();
//		pRun->setPosition(Vec2(140,yPos));
//		if (yPos == 160)
//			down = true;
//	}
//	if (down ==true ) {
//		yPos = pYpos->getPositionY();
//		pRun->setPosition(Vec2(140, yPos));
//		if (yPos == 80) {
//			cnt = 0;
//			down = false;
//			this->unschedule(schedule_selector(HelloWorld::CallJump));
//		}
//	}
//}
//
//void HelloWorld::CallJump2(float f) {
//	if (down == false) {
//		yPos = tempY + pYpos2->getPositionY();
//		pRun->setPosition(Vec2(140, yPos));
//		if (yPos >= temp)
//			down = true;
//	}
//	if (down == true) {
////		pYpos3 = pRun->getPositionY();
//		if (pYpos2->getPositionY() == 0)
//			tempY--;
//		yPos = tempY + pYpos2->getPositionY();
//		pRun->setPosition(Vec2(140, yPos));
//		if (yPos == 80) {
//			cnt = 0;
//			down = false;
//			this->unschedule(schedule_selector(HelloWorld::CallJump2));
//		}
//	}
//}
//
//void HelloWorld::GetY() {
//	auto Move = MoveBy::create(0.8, Vec2(0, 80));
//	auto MoveEaseSineinOut = EaseSineInOut::create(Move->clone());
//	auto MoveBack = MoveEaseSineinOut->reverse();
//	auto MoveAction = Sequence::create(MoveEaseSineinOut,MoveBack,nullptr);
//	pYpos->runAction(MoveAction);
//
//}
//
//void HelloWorld::GetY2() {
//	auto Move = MoveBy::create(0.8, Vec2(0, 80));
//	auto MoveEaseSineinOut = EaseSineInOut::create(Move->clone());
//	auto MoveBack = MoveTo::create(0.8, Vec2(0, 0));
//	auto MoveSaseSineinOutBack = EaseSineInOut::create(MoveBack->clone());
//	auto MoveAction = Sequence::create(MoveEaseSineinOut, MoveSaseSineinOutBack, nullptr);
//	pYpos2->runAction(MoveAction);
//}
//void HelloWorld::GetY3() {
//	auto Move = MoveTo::create(0.8, Vec2(0, 0));
//	auto MoveEaseSineInOut = EaseSineInOut::create(Move->clone());
//	y
//}


//
//ease 미완
void HelloWorld::Jump() {
	yPos = pRun->getPositionY();
	if (yPos == 80) {
		cnt = 0;
		down = false;
		temp = yPos;
	}

	if (cnt == 0) {
		cnt++;
		GetY();
		this->schedule(schedule_selector(HelloWorld::CallJump), 0.01f);
	}
	else if (cnt == 1) {
		cnt++;
		yPos = pRun->getPositionY();
		temp = yPos + 80;
		tempY = yPos;
		GetY2();
		this->unschedule(schedule_selector(HelloWorld::CallJump));
		this->schedule(schedule_selector(HelloWorld::CallJump2), 0.01f);
	}
}

void HelloWorld::CallJump(float f) {
	if (down ==false) {
		yPos = pYpos->getPositionY();
		pRun->setPosition(Vec2(140,yPos));
		if (yPos == 160)
			down = true;
	}
	if (down ==true ) {
		yPos = pYpos->getPositionY();
		pRun->setPosition(Vec2(140, yPos));
		if (yPos == 80) {
			cnt = 0;
			down = false;
			this->unschedule(schedule_selector(HelloWorld::CallJump));
		}
	}
}

void HelloWorld::CallJump2(float f) {
	if (down == false) {
		yPos = tempY + pYpos2->getPositionY();
		pRun->setPosition(Vec2(140, yPos));
		if (yPos >= temp)
			down = true;
	}
	if (down == true) {
		if (pYpos2->getPositionY() == 0)
			tempY--;
		yPos = tempY + pYpos2->getPositionY();
		pRun->setPosition(Vec2(140, yPos));
		if (yPos == 80) {
			cnt = 0;
			down = false;
			this->unschedule(schedule_selector(HelloWorld::CallJump2));
		}
	}
}

void HelloWorld::GetY() {
	auto Move = MoveBy::create(0.8, Vec2(0, 80));
	auto MoveEaseSineinOut = EaseSineInOut::create(Move->clone());
	auto MoveBack = MoveEaseSineinOut->reverse();
	auto MoveAction = Sequence::create(MoveEaseSineinOut,MoveBack,nullptr);
	pYpos->runAction(MoveAction);

}

void HelloWorld::GetY2() {
	auto Move = MoveBy::create(0.8, Vec2(0, 80));
	auto MoveEaseSineinOut = EaseSineInOut::create(Move->clone());
	auto MoveBack = MoveEaseSineinOut->reverse();
	auto MoveAction = Sequence::create(MoveEaseSineinOut, MoveBack, nullptr);
	pYpos2->runAction(MoveAction);
}

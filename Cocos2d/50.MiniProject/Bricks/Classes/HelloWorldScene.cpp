#include "HelloWorldScene.h"
//#include <time.h>
//#include <stdlib.h>
#include "GameOver.h"

#define FIX_POS(_pos,_min,_max)\
if(_pos<_min)\
_pos = _min; \
else if (_pos>_max)\
_pos = _max;\

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
    if ( !Layer::init() )
    {
        return false;
    }
    
	srand((int)time(NULL));

	winSize = Director::getInstance()->getVisibleSize();


	//벽돌 개수 지정
	BRICKS_HEIGHT = 4;
	BRICKS_WIDTH = 5;

	//벽돌에 사용될 텍츠쳐 로딩
	texture = Director::getInstance()->getTextureCache()->addImage("Images/white-512x512.png");

	//벽돌 초기화
	this->initializeBricks();

	//공 초기화
	this->initializeBall();
	
	//패들 초기화
	this->initializepaddle();

	//2초후 게임 시작
	this->scheduleOnce(schedule_selector(HelloWorld::startGame), 2);


    return true;
}

void HelloWorld::initializeBricks() {
	int count = 0;

	for (int y = 0; y < BRICKS_HEIGHT; y++) {
		for (int x = 0; x < BRICKS_WIDTH; x++) {
			auto bricks = Sprite::createWithTexture(texture, Rect(0, 0, 64, 40));

			//색 지정
			switch (count++ %4){
			case 0:
				bricks->setColor(Color3B(255, 255, 255));
				break;
			case 1:
				bricks->setColor(Color3B(255, 0, 0));
				break;
			case 2:
				bricks->setColor(Color3B(255, 255, 0));
				break;
			case 3:
				bricks->setColor(Color3B(75, 255, 0));
				break;
			default:
				break;
			}

			//좌표 지정
			bricks->setPosition(Vec2(x * 64 + 32, (y * 40) + 280));

			//화면에 추가
			this->addChild(bricks);

			//백터에 추가
			targets.pushBack(bricks);
		}
	}
}

void HelloWorld::initializeBall() {
	ball = Sprite::createWithTexture(texture, Rect(0, 0, 16, 16));
	ball->setColor(Color3B(0, 255, 255));
	ball->setPosition(Vec2(160, 240));
	this->addChild(ball);
}

void HelloWorld::initializepaddle() {
	paddle = Sprite::createWithTexture(texture, Rect(0, 0, 80, 10));
	paddle->setColor(Color3B(255, 255, 0));
	paddle->setPosition(Vec2(160, 50));
	this->addChild(paddle);
}

HelloWorld::~HelloWorld() {
	Device::setAccelerometerEnabled(false);
}


void HelloWorld::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	Device::setAccelerometerEnabled(true);

	auto AccListener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(AccListener, this);
}


//
//void HelloWorld::onExit() {
//
//	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
//
//	Layer::onExit();
//
//}

void HelloWorld::onAcceleration(Acceleration* acc, Event* event) {
	auto pDir = Director::getInstance();
	
	winSize = pDir->getVisibleSize();

	auto paddleSize = paddle->getContentSize();
	auto ptNow = paddle->getPosition();
	auto ptTemp = pDir->convertToUI(ptNow);

	ptTemp.x += acc->x*9.81f;

	auto ptNext = pDir->convertToGL(ptTemp);

	FIX_POS(ptNext.x, (paddleSize.width / 2), (winSize.width - paddleSize.width / 2));

	//패들이 좌우로만 움직이게 t값은 바꾸지 안는다.
	//또한 패들이 화면 바깥으로 나가지 않게 한다.
	if (ptNext.x < 40) {
		ptNext.x = 40;
	}
	if (ptNext.x > 280) {
		ptNext.x = 280;
	}
	auto newLocation = Vec2(ptNext.x, paddle->getPosition().y);
	paddle->setPosition(newLocation);

}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	if (!isPlaying) {
		return true;
	}

	//하나의 터치 이벤트만 가져온다.
	auto touchPoint = touch->getLocation();

	//패들을 터치했는지 체크한다
	auto rect = paddle->getBoundingBox();
	if (rect.containsPoint(touchPoint)) {
		//패들이 터치됐음을 체크
		isPaddleTouched = true;
	}
	else {
		isPaddleTouched = false;
	}

	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event) {
	if (isPaddleTouched) {
		auto touchPoint = touch->getLocation();

		//패들이 좌우로만 움직이게 t값은 바꾸지 안는다.
		//또한 패들이 화면 바깥으로 나가지 않게 한다.
		if (touchPoint.x < 40) {
			touchPoint.x = 40;
		}
		if (touchPoint.x > 280) {
			touchPoint.x = 280;
		}

		auto newLocation = Vec2(touchPoint.x, paddle->getPosition().y);
		paddle->setPosition(newLocation);
	}
}

void HelloWorld::startGame(float dt) {
	ball->setPosition(Vec2(160, 240));

	ballMovement = Vec2(4, 4);
	if (rand() % 100 < 50) {
		ballMovement.x = -ballMovement.x;
	}
	ballMovement.y = -ballMovement.y;

	isPlaying = true;

	this->schedule(schedule_selector(HelloWorld::gameLogic), 2.0f / 60.0f);
}

void HelloWorld::gameLogic(float dt) {
	//ballMovement.y 가 음수이면 본이 내려오는 것
	//ballMovement.y가 양수이면 볼이 올라가고 있는것
	//log("tick... %f",ballMovement.y);

	//볼의 현재 위치
	ball->setPosition(Vec2(ball->getPosition().x + ballMovement.x, ball->getPosition().y + ballMovement.y));

	//볼과 패들 충돌 여부
	bool paddleCollision =
		ball->getPosition().y <= paddle->getPosition().y + 13 &&
		ball->getPosition().x >= paddle->getPosition().x - 48 &&
		ball->getPosition().x <= paddle->getPosition().x + 48;

	//패들과 충돌 시 처리
	if (paddleCollision) {
		if (ball->getPosition().y <= paddle->getPosition().y + 13 && ballMovement.y < 0) {
			ball->setPosition(Vec2(ball->getPosition().x, paddle->getPosition().y + 13));
		}

		//내려오던 것을 위로 올라가도록 공의 상하 진행 방향 바꾸기

		ballMovement.y = -ballMovement.y;
	}

	//블록과 충돌 파악
	bool there_are_solid_bricks = false;

	for (auto &item : targets) {
		Sprite* brick = item;
		if (255 == brick->getOpacity()) {
			there_are_solid_bricks = true;

			Rect rectA = ball->getBoundingBox();
			Rect rectB = brick->getBoundingBox();
			if (rectA.intersectsRect(rectB)) {
				//블록과 충돌 처리
				this->processCollision(brick);
			}
		}
	}


	//블록이 없을때 - 게임 종료 상태
	if (!there_are_solid_bricks) {
		isPlaying = false;
		ball->setOpacity(0);

		//모든 스케쥴 제거
		this->unscheduleAllSelectors();
		log("win!");

		//게임종료 새게임 대기화면
		Scene* pScene = GameOver::createScene();
		Director::getInstance()->replaceScene(TransitionProgressRadialCCW::create(1, pScene));

	}

	//벽면 충돌 체크
	if (ball->getPosition().x > 312 || ball->getPosition().x < 8)
		ballMovement.x = -ballMovement.x;

	if (ball->getPosition().y > 450)
		ballMovement.y = -ballMovement.y;

	//if(ball.posiotion().y<10){
	// ballMovement.y = -ballMovement.y;


	//패들을 빠져 나갈때
	if (ball->getPosition().y < (50 + 5 + 8)) {
		isPlaying = false;
		ball->setOpacity(0);

		//모든 스케쥴 제거
		this->unscheduleAllSelectors();

		log("lose");

		//새게임
		Scene* pScene = GameOver::createScene();
		Director::getInstance()->replaceScene(TransitionProgressRadialCCW::create(1, pScene));

	}
}

void HelloWorld::processCollision(Sprite *brick) {
	auto brickPos = brick->getPosition();
	auto ballPos = ball->getPosition();

	if (ballMovement.x > 0 && brick->getPosition().x < ball->getPosition().x) {
		ballMovement.x = -ballMovement.x;
	}
	else if (ballMovement.x < 0 && brick->getPosition().x < ball->getPosition().x) {
		ballMovement.x = -ballMovement.x;
	}

	if (ballMovement.y > 0 && brick->getPosition().y >ball->getPosition().y) {
		ballMovement.y = -ballMovement.y;
	}
	else if (ballMovement.y < 0 && brick->getPosition().y < ball->getPosition().y) {
		ballMovement.y = -ballMovement.y;
	}
	brick->setOpacity(0);
}

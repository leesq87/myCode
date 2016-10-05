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
    
	//윈도우 크기를 구한다
	winSize = Director::getInstance()->getWinSize();

	//이미지의 텍스쳐를 구한다
	texture = Director::getInstance()->getTextureCache()->addImage("close.png");

	//월드생성 시작-----------------------

	//중력의 방향을 결정한다.
	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

	//월드를 생성한다.
	_world = new b2World(gravity);

	//휴식 상태일때 포함된 바디들을 멈추게 (sleep)할 것인지 결정한다.
	_world->SetAllowSleeping(true);

	//지속적인 물리작용을 할 것인지 결정한다 : 테스트
	_world->SetContinuousPhysics(true);

	//가장자리 (테두리)를 지정해 공간(Ground Box)을 만든다

	//바디데프에 좌표를 설정한다.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	//월드에 바디데프의 정보(좌표)로 바디를 만든다.
	b2Body* groundBody = _world->CreateBody(&groundBodyDef);


	//가장자리(테두리) 경계선을 그릴 수 있는 모양의 객체를 만든다.
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	//Edge 모양의 객체에 set(점1,점2)로 선을 만든다
	//그리고 바디(groundBody)에 모양(groundEdge)을 고정시킨다.

	//아래쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//왼쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//위쪽
	groundEdge.Set(b2Vec2(0, winSize.height/PTM_RATIO), b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//오른쪽
	groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//월드 생성 끝-----------------------------------------------------

	this->schedule(schedule_selector(HelloWorld::tick));

    return true;
}

HelloWorld::~HelloWorld() {
	//월드를 c++의 new로 생성했으므로 여기서 지워준다
	delete _world;
	_world = nullptr;
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void HelloWorld::onExit() {
	_eventDispatcher->removeAllEventListeners();
	Layer::onExit();
}

void HelloWorld::tick(float dt) {
	//물리적 위치를 이용해 그래픽 위치를 갱신한다.

	//velocityIterations : 바디들을 정상적으로 이동시키기 위해 필요한 충돌들을 반복적으로 계산

	//positioniterations : 조인트 분리와 겹침 현상을 줄이기 위해 바디의 위치를 반복적으로 적용
	//값이 클수록 정확한 연산이 가능하지만 성능이 떨어진다.

	//프로젝트 생성시 기본 값
	//int velocityIterations = 8;
	//int positionIterations = 1;

	//메뉴얼 상의 권장값
	int velocityIterations = 8;
	int positionIterations = 3;

	//step : 물리 세계를 시뮬레이션 한다.
	_world->Step(dt, velocityIterations, positionIterations);

	//모든 물리 객체들은 링므드 리스트에 저장되어 참조해 볼 수 있게 구현돼 있다.
	//만들어진 객체만큼 루프를 돌리면서 바디에 붙인 스프라이트를 여기서 제어한다

	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != nullptr) {
			Sprite* spritedata = (Sprite *)b->GetUserData();
			spritedata->setPosition(Vec2(b->GetPosition().x*PTM_RATIO, b->GetPosition().y*PTM_RATIO));
			spritedata->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}


bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	auto touchPoint = touch->getLocation();

	//터치된 지점에 새로운 물리 객체의 바디와 해당 스프라이트를 추가한다.
	addNewSpriteAtPosition(touchPoint);

	return true;
}

void HelloWorld::addNewSpriteAtPosition(Vec2 location) {
	//스프라이트를 파라미터로 넘어온 위치에 만든다.
	Sprite* pSprite = Sprite::createWithTexture(texture, Rect(0, 0, 37, 37));
	pSprite->setPosition(Vec2(location.x, location.y));
	this->addChild(pSprite);

	//바디데프를 만들고 속성들을 지정한다
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
	//유저데이터에 스프라이트를 붙인다.
	bodyDef.userData = pSprite;

	//월드에 바디데프의 정보로 바디를 만든다.
	b2Body* body = _world->CreateBody(&bodyDef);

	//바디에 적용할 물리속성용 바디의 모양을 만든다.

	
	//원 형태를 선택해 반지름을 지정한다.
	b2CircleShape circle;
	circle.m_radius = 0.55f;

	//바디에 모양(circle)을 고정시킨다.
	b2FixtureDef fixtureDef;

	//모양을 지정한다.
	fixtureDef.shape = &circle;
	//밀도
	fixtureDef.density = 1.0f;
	//마찰력 - 0~1
	fixtureDef.friction = 0.2f;
	//반발력 -물체가 닿을때 튕기는 값
	fixtureDef.restitution = 0.7f;

	body->CreateFixture(&fixtureDef);
	

	/*
	// 박스 모양의 객체 생성
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(.5f, .5f);


	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.7f;
	body->CreateFixture(&fixtureDef);

	*/

	/*
	// 다각형 모양의 객체 생성 - 벡터값의 크기에 따라 다양하고 복잡한 모양을 만들 수 있다.
	b2PolygonShape dynamicBox;
	b2Vec2 tri[3];

	tri[0].x = -.5;
	tri[0].y = 0.0;

	tri[1].x = .5;
	tri[1].y = 0.0;

	tri[2].x = 0;
	tri[2].y = 1.0;

	dynamicBox.Set(tri, 3);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f;
	body->CreateFixture(&fixtureDef);

	*/
}



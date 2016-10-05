#include "HelloWorldScene.h"
#include "MyBodyParser.h"


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
    
	//윈도우 크기를 구한다
	winSize = Director::getInstance()->getWinSize();

	//이미지의 텍스쳐를 구한다
	texture = Director::getInstance()->getTextureCache()->addImage("Images/blocks.png");

	//월드생성
	if (this->createBox2dWorld(true)) {
		this->schedule(schedule_selector(HelloWorld::tick));
	}


    return true;
}

bool HelloWorld::createBox2dWorld(bool debug) {

	//월드생성 시작-----------------------

	//중력의 방향을 결정한다.
	b2Vec2 gravity = b2Vec2(0.0f, -30.0f);

	//월드를 생성한다.
	_world = new b2World(gravity);

	//휴식 상태일때 포함된 바디들을 멈추게 (sleep)할 것인지 결정한다.
	_world->SetAllowSleeping(true);

	//지속적인 물리작용을 할 것인지 결정한다 : 테스트
	_world->SetContinuousPhysics(true);

	//디버그 드로잉 설정
	if (debug) {
		//적색 : 현재 물리운동을 하는 것
		//회색 : 현재 물리운동량이 없는것
		m_debugDraw = new GLESDebugDraw(PTM_RATIO);
		_world->SetDebugDraw(m_debugDraw);

		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		//flags += b2Draw::e_aabbBit;
		//flags += b2Draw::e_pairBit;
		//flags += b2Draw::e_centerOfMassBit;
		m_debugDraw->SetFlags(flags);

	}


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
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(winSize.width*2 / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//왼쪽
	groundEdge.Set(b2Vec2(0, 0), b2Vec2(0, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//위쪽
	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO), b2Vec2(winSize.width*2 / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//오른쪽
	groundEdge.Set(b2Vec2(winSize.width*2 / PTM_RATIO, winSize.height / PTM_RATIO), b2Vec2(winSize.width*2 / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//월드 생성 끝-----------------------------------------------------

	//bDrag = false;
	
	//마우스 조인트 바디를 생성해서 월드에 추가한다.
	//gbody = this->addNewSprite(Vec2(0, 0), Size(0, 0), b2_staticBody, nullptr, 0);

	//바디를 생성해서 월드에 추가한다.
	//this->addNewSprite(Vec2(240, 160), Size(32, 32), b2_dynamicBody, "test", 0);

	Sprite* bg1 = Sprite::create("Images/background.png");
	bg1->setPosition(Vec2(0, 0));
	bg1->setAnchorPoint(Vec2(0, 0));
	this->addChild(bg1);

	//Sprite* bg2 = Sprite::create("Images/background2.png");
	//bg2->setPosition(Vec2(0, 0));
	//bg2->setAnchorPoint(Vec2(0, 0));
	//this->addChild(bg2);

	myBall = this->addNewSprite(Vec2(25, 50), Size(50, 50),b2_dynamicBody, "test2", 0);
	Sprite* myBallSprite = (Sprite*)myBall->GetUserData();
	Rect myBoundary = Rect(0, 0, winSize.width * 2, winSize.height);
	//손쉬운 화면 스크롤링 기법인 Follow액션을 사용해 넓은 화면을 이동시킨다.
	//바디를 던지면 해당 바디에 카메라가 붙어 있으므로 자동으로 화면이 스크롤된다.

	this->runAction(Follow::create(myBallSprite, myBoundary));
	this->setBlocks();


	return true;

}

void HelloWorld::setBlocks() {
	float start = winSize.width * 2 - 130;

	struct BLOCK {
		Vec2 point;
		Size size;
	};

	int const numBlocks = 6;
	struct BLOCK blocks[numBlocks] = {
		{ Vec2(start,50),Size(10,100) },
		{ Vec2(start + 50,50),Size(10,100)},
		{ Vec2(start + 25,100 + 5),Size(200,10)},
		{ Vec2(start,120 + 50),Size(10,100)},
		{Vec2(start + 50,120 + 50),Size(10,100)},
		{Vec2(start + 25,220 + 5),Size(200,10)}
	};

	for (int i = 0; i < numBlocks; i++) {
		this->addNewSprite(blocks[i].point, blocks[i].size, b2_dynamicBody, "test", 0);
	}
}



HelloWorld::~HelloWorld() {
	//월드를 c++의 new로 생성했으므로 여기서 지워준다
	delete _world;
	_world = nullptr;
}


void HelloWorld::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);

	_customCmd.init(_globalZOrder, transform, flags);
	_customCmd.func = CC_CALLBACK_0(HelloWorld::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);
}

void HelloWorld::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	CCASSERT(nullptr != director, "Director is null when seting matrix stack");
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	_world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}



void HelloWorld::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);


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


//
//void HelloWorld::addNewSpriteAtPosition(Vec2 location) {
//
//	auto polygon = Sprite::create("f1.png");
//	polygon->setPosition(Vec2(location.x, location.y));
//
//	// this->addchild(polygon)- > 하면안됨
//
//	//바디 데프 만들고 속성들을 지정한다.
//	b2BodyDef bodyDef;
//	bodyDef.type = b2_dynamicBody;
//	bodyDef.position.Set(location.x / PTM_RATIO, location.y / PTM_RATIO);
//
//	//유저데이터에 스프아리트를 붙인다.
//	//bodyDef.userData = polygon;
//	bodyDef.userData = nullptr;
//
//	//월드에 바디데프의 정보로 바디를 만든다.
//	b2Body* body = _world->CreateBody(&bodyDef);
//
//	MyBodyParser::getInstance()->parseJsonFile("exam1.json");
//	MyBodyParser::getInstance()->b2BodyJson(polygon, "arrow", body);
//
//
//	
//}


b2Body* HelloWorld::addNewSprite(Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type) {
	//바디데프를 만들고 속성들을 지정한다
	b2BodyDef bodyDef;
	bodyDef.type = bodytype;
	bodyDef.position.Set(point.x / PTM_RATIO, point.y / PTM_RATIO);

	if (spriteName) {
		if (strcmp(spriteName, "test") == 0 || strcmp(spriteName, "test2")==0) {
			int idx = (CCRANDOM_0_1() > .5 ? 0 : 1);
			int idy = (CCRANDOM_0_1() > .5 ? 0 : 1);
			Sprite* sprite = Sprite::createWithTexture(texture, Rect(32 * idx, 32 * idy, 32, 32));
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
		else {
			Sprite* sprite = Sprite::create(spriteName);
			sprite->setPosition(point);
			this->addChild(sprite);

			bodyDef.userData = sprite;
		}
	}

	//월드에 바디데프의 정보로 바디를 만든다.
	b2Body* body = _world->CreateBody(&bodyDef);

	//바디에 적용할 물리 속성용 바디의 모양을 만든다.
	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
	b2CircleShape circle;

	if (type == 0) {
		dynamicBox.SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);
		fixtureDef.shape = &dynamicBox;
	}
	else {
		circle.m_radius = (size.width / 2) / PTM_RATIO;

		fixtureDef.shape = &circle;
	}

	if (strcmp(spriteName, "test2") == 0) {
		fixtureDef.density = 20;
	}
	else {
		fixtureDef.density = 1;
	}
	fixtureDef.friction = 0.3;

	//define the dynamic body fixture
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 0.3f;
	//fixtureDef.restitution = 0.0f;
	body->CreateFixture(&fixtureDef);

	return body;
}

b2Body* HelloWorld::getBodyAtTab(Vec2 p) {
	b2Fixture* fix;
	for (b2Body* b = _world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != nullptr) {
			if (b->GetType() == b2_staticBody) continue;
			fix = b->GetFixtureList();
			if (fix->TestPoint(b2Vec2(p.x / PTM_RATIO, p.y / PTM_RATIO))) {
				return b;
			}
		}
	}
	return NULL;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	auto touchPoint = touch->getLocation();

	auto TouchPoint2 = Node::convertToNodeSpace(touchPoint);

	b2Body* tBall = this->getBodyAtTab(TouchPoint2);

	bBallTouch = false;

	if (tBall == myBall) {
		log("touch start..");
		bBallTouch = true;
		startPoint = b2Vec2(touchPoint.x / PTM_RATIO, touchPoint.y / PTM_RATIO);
	}
	return true;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event) {

	Vec2 touchPoint = touch->getLocation();

	if (myBall && bBallTouch) {
		log("Touch end..");
		endPoint = b2Vec2(touchPoint.x / PTM_RATIO, touchPoint.y / PTM_RATIO);
		b2Vec2 force = endPoint - startPoint;

		force.x *= 150;
		force.y *= 150;
		b2Vec2 startVec = b2Vec2(startPoint.x, startPoint.y);
		myBall->ApplyLinearImpulse(force, startVec, true);

		bBallTouch = false;
	}
}

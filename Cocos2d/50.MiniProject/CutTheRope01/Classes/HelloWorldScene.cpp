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
    if ( !Layer::init() )
    {
        return false;
    }
    
	ropes = new std::vector<VRope *>;

	//윈도우 크기를 구한다
	winSize = Director::getInstance()->getWinSize();

	//이미지의 텍스쳐를 구한다

	//월드생성
	if (this->createBox2dWorld(false)) {
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
	groundBody = _world->CreateBody(&groundBodyDef);


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
	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO), b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO));
	groundBody->CreateFixture(&boxShapeDef);

	//오른쪽
	groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO), b2Vec2(winSize.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&boxShapeDef);

	//월드 생성 끝-----------------------------------------------------

	//gbody = this->addNewSprite(Vec2(winSize.width/2,winSize.height), Size(0, 0), b2_staticBody, nullptr, 0);

	ropeSpriteSheet = SpriteBatchNode::create("rope_texture.png");
	this->addChild(ropeSpriteSheet);

	b2Body* body1 = this->addNewSpriteAt(Vec2(winSize.width / 2, winSize.height * 2 / 3));
	this->createRope(groundBody, b2Vec2((winSize.width / 2) / PTM_RATIO, winSize.height / PTM_RATIO), body1, body1->GetLocalCenter(), 1.1f);


	return true;

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

	std::vector<VRope *>::iterator rope;
	
	for (rope = ropes->begin(); rope != ropes->end(); ++rope) {
		(*rope)->update(dt);
		(*rope)->updateSprites();

	}
}




b2Body* HelloWorld::addNewSpriteAt(Vec2 point) {
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("CutTheVerlet.plist");

	Sprite* sprite = Sprite::createWithSpriteFrameName("pineapple.png");
	this->addChild(sprite);

	//defines the body of your candy

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = b2Vec2(point.x / PTM_RATIO, point.y / PTM_RATIO);
	bodyDef.userData = sprite;
	bodyDef.linearDamping = 0.3f;
	b2Body* body = _world->CreateBody(&bodyDef);

	//define the fixture as a polygon
	b2FixtureDef fixtureDef;
	b2PolygonShape spriteShape;

	b2Vec2 verts[] = {
		b2Vec2(-7.6f / PTM_RATIO,-34.4f / PTM_RATIO),
		b2Vec2(8.3f / PTM_RATIO,-34.4f / PTM_RATIO),
		b2Vec2(15.55f / PTM_RATIO,-27.15f / PTM_RATIO),
		b2Vec2(13.8f / PTM_RATIO,23.05f / PTM_RATIO),
		b2Vec2(-3.35f / PTM_RATIO,35.25f / PTM_RATIO),
		b2Vec2(-16.25f / PTM_RATIO,25.55f / PTM_RATIO),
		b2Vec2(-15.55f / PTM_RATIO,-23.95f / PTM_RATIO),
	};

	spriteShape.Set(verts, 7);

	fixtureDef.shape = &spriteShape;
	fixtureDef.density = 30.0f;
	fixtureDef.filter.categoryBits = 0x01;
	fixtureDef.filter.maskBits = 0x01;

	body->CreateFixture(&fixtureDef);

	return body;
}

void HelloWorld::createRope(b2Body* bodyA, b2Vec2 anchorA, b2Body* bodyB, b2Vec2 anchorB, float32 sag) {
	b2RopeJointDef jd;
	jd.bodyA = bodyA;
	jd.bodyB = bodyB;
	jd.localAnchorA = anchorA;
	jd.localAnchorB = anchorB;

	//max length of joint
	float32 ropeLength = (bodyA->GetWorldPoint(anchorA) - bodyB->GetWorldPoint(anchorB)).Length()*sag;
	jd.maxLength = ropeLength;

	//create joint
	b2RopeJoint* ropeJoint = (b2RopeJoint*)_world->CreateJoint(&jd);
	VRope* newRope = new VRope(ropeJoint, ropeSpriteSheet);


	ropes->push_back(newRope);

}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {
	auto touchPoint = touch->getLocation();

	b2Body* body1 = this->addNewSpriteAt(touchPoint);

	this->createRope(groundBody, b2Vec2((winSize.width / 2) / PTM_RATIO, winSize.height / PTM_RATIO), body1, body1->GetLocalCenter(), 1.1f);

	return true;

}
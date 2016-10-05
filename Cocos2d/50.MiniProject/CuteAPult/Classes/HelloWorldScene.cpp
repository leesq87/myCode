#include "HelloWorldScene.h"

USING_NS_CC;

#define PTM_RATIO 32
#define FLOOR_HEIGHT 62
enum {
	kTagTileMap = 1,
	kTagSpriteManager = 1,
	kTagAnimation1 = 1,
};

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

	winSize = Director::getInstance()->getWinSize();

	//월드생성
	if (this->createBox2dWorld(true)) {
		DelayTime* delayAction = DelayTime::create(0.5);
		CallFunc* callSelectorAction = CallFunc::create(CC_CALLBACK_0(HelloWorld::resetGame, this));
		this->runAction(Sequence::create(delayAction, callSelectorAction, nullptr));
		
	}

	this->schedule(schedule_selector(HelloWorld::tick));

    return true;
}

bool HelloWorld::createBox2dWorld(bool debug) {
	b2Vec2 gravity;
	gravity.Set(0, -10.f);

	m_world = new b2World(gravity);
	m_world->SetAllowSleeping(true);

	m_world->SetContinuousPhysics(true);
	//바디데프에 좌표를 설정한다.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	m_groundBody = m_world->CreateBody(&groundBodyDef);

	//월드에 바디데프의 정보(좌표)로 바디를 만든다.
	b2Body* groundBody = m_world->CreateBody(&groundBodyDef);


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

	////오른쪽
	//groundEdge.Set(b2Vec2(winSize.width / PTM_RATIO, winSize.height / PTM_RATIO), b2Vec2(winSize.width / PTM_RATIO, 0));
	//groundBody->CreateFixture(&boxShapeDef);

	//월드 생성 끝-----------------------------------------------------


	Sprite* sprite = Sprite::create("bg.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(sprite, -1);

	sprite = Sprite::create("catapult_base_2.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(CCPointMake(181, FLOOR_HEIGHT));
	this->addChild(sprite, 0);

	sprite = Sprite::create("squirrel_1.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(CCPointMake(11, FLOOR_HEIGHT));
	this->addChild(sprite, 0);

	sprite = Sprite::create("catapult_base_1.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(CCPointMake(181, FLOOR_HEIGHT));
	this->addChild(sprite, 9);

	sprite = Sprite::create("squirrel_2.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(CCPointMake(240, FLOOR_HEIGHT));
	this->addChild(sprite, 9);

	sprite = Sprite::create("fg.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(sprite, 10);



	Sprite* arm = Sprite::create("catapult_arm.png");
	this->addChild(arm, 1);

	b2BodyDef armBodyDef;
	armBodyDef.type = b2_dynamicBody;
	armBodyDef.linearDamping = 1;
	armBodyDef.angularDamping = 1;
	armBodyDef.position.Set(230 / PTM_RATIO, (FLOOR_HEIGHT + 91) / PTM_RATIO);
	armBodyDef.userData = arm;
	m_armBody = m_world->CreateBody(&armBodyDef);

	b2PolygonShape armBox;
	armBox.SetAsBox(11.0f / PTM_RATIO, 91.0f / PTM_RATIO);

	b2FixtureDef armBoxDef;
	armBoxDef.shape = &armBox;
	armBoxDef.density = 0.3f;
	m_armFixture = m_armBody->CreateFixture(&armBoxDef);

	b2RevoluteJointDef armJointDef;
	armJointDef.Initialize(m_groundBody, m_armBody, b2Vec2(233.0f / PTM_RATIO, FLOOR_HEIGHT / PTM_RATIO));

	armJointDef.enableMotor = true;
	armJointDef.enableLimit = true;
	armJointDef.motorSpeed = -10;
	armJointDef.lowerAngle = CC_DEGREES_TO_RADIANS(9);
	armJointDef.upperAngle = CC_DEGREES_TO_RADIANS(75);
	armJointDef.maxMotorTorque = 700;
	m_armJoint = (b2RevoluteJoint*)m_world->CreateJoint(&armJointDef);

	//m_mouseJoint = nullptr;

	return true;
}


HelloWorld::~HelloWorld() {
	delete m_world;
	m_world = nullptr;
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

void HelloWorld::createBullets(int count) {
	m_currentBullet = 0;
	float pos = 62.0f;
	if (count > 0) {
		float delta = (count > 1) ? ((165.0f - 62.0f - 30.0f) / (count - 1)) : 0.0f;

		for (int i = 0; i < count; i++, pos += delta) {
			Sprite* sprite = Sprite::create("acorn.png");
			this->addChild(sprite, 2);

			b2BodyDef bulletBodyDef;
			bulletBodyDef.type = b2_dynamicBody;
			bulletBodyDef.bullet = true;
			bulletBodyDef.position.Set(pos / PTM_RATIO, (FLOOR_HEIGHT + 15) / PTM_RATIO);
			bulletBodyDef.userData = sprite;
			b2Body* bullet = m_world->CreateBody(&bulletBodyDef);
			bullet->SetActive(false);

			b2CircleShape circle;
			circle.m_radius = 15 / PTM_RATIO;

			b2FixtureDef ballShapeDef;
			ballShapeDef.shape = &circle;
			ballShapeDef.density = 0.8;
			ballShapeDef.restitution = 0.2;
			ballShapeDef.friction = 0.99;
			bullet->CreateFixture(&ballShapeDef);

			m_bullets.push_back(bullet);
		}
	}
}

void HelloWorld::createTargets() {
	m_targets.clear();
	m_enemies.empty();

	this->createTarget(String::create("brick_2.png"),Vec2(675.0, FLOOR_HEIGHT), 0.0f, false, false, false);
	this->createTarget(String::create("brick_1.png"),
		Vec2(741.0, FLOOR_HEIGHT), 0.0f, false, false, false);
	this->createTarget(String::create("brick_1.png"),
		Vec2(741.0, FLOOR_HEIGHT + 23.0f), 0.0f, false, false, false);
	this->createTarget(String::create("brick_3.png"),
		Vec2(672.0, FLOOR_HEIGHT + 46.0f), 0.0f, false, false, false);
	this->createTarget(String::create("brick_1.png"),
		Vec2(707.0, FLOOR_HEIGHT + 58.0f), 0.0f, false, false, false);
	this->createTarget(String::create("brick_1.png"),
		Vec2(707.0, FLOOR_HEIGHT + 81.0f), 0.0f, false, false, false);

	this->createTarget(String::create("head_dog.png"),
		Vec2(702.0, FLOOR_HEIGHT), 0.0f, true, false, true);
	this->createTarget(String::create("head_cat.png"),
		Vec2(680.0, FLOOR_HEIGHT + 58.0f), 0.0f, true, false, true);
	this->createTarget(String::create("head_dog.png"),
		Vec2(740.0, FLOOR_HEIGHT + 58.0f), 0.0f, true, false, true);

	// 2 bricks at the right of the first block
	this->createTarget(String::create("brick_2.png"),
		Vec2(770.0, FLOOR_HEIGHT), 0.0f, false, false, false);
	this->createTarget(String::create("brick_2.png"),
		Vec2(770.0, FLOOR_HEIGHT + 46.0f), 0.0f, false, false, false);

	// The dog between the blocks
	this->createTarget(String::create("head_dog.png"),
		Vec2(830.0, FLOOR_HEIGHT), 0.0f, true, false, true);

	// Second block
	this->createTarget(String::create("brick_platform.png"),
		Vec2(839.0, FLOOR_HEIGHT), 0.0f, false, true, false);
	this->createTarget(String::create("brick_2.png"),
		Vec2(854.0, FLOOR_HEIGHT + 28.0f), 0.0f, false, false, false);
	this->createTarget(String::create("brick_2.png"),
		Vec2(854.0, FLOOR_HEIGHT + 28.0f + 46.0f), 0.0f, false, false, false);
	this->createTarget(String::create("head_cat.png"),
		Vec2(881.0, FLOOR_HEIGHT + 28.0f), 0.0f, true, false, true);
	this->createTarget(String::create("brick_2.png"),
		Vec2(909.0, FLOOR_HEIGHT + 28.0f), 0.0f, false, false, false);
	this->createTarget(String::create("brick_1.png"),
		Vec2(909.0, FLOOR_HEIGHT + 28.0f + 46.0f), 0.0f, false, false, false);
	this->createTarget(String::create("brick_1.png"),
		Vec2(909.0, FLOOR_HEIGHT + 28.0f + 46.0f + 23.0f), 0.0f, false, false, false);
	this->createTarget(String::create("brick_2.png"),
		Vec2(882.0, FLOOR_HEIGHT + 108.0f), 90.0f, false, false, false);;
}

void HelloWorld::createTarget(String *imageName, Vec2 position, float rotation, bool isCircle, bool isStatic, bool isEnemy) {
	Sprite* sprite = Sprite::create(imageName->getCString());
	this->addChild(sprite, 1);

	b2BodyDef bodyDef;
	bodyDef.type = isStatic ? b2_staticBody : b2_dynamicBody;
	bodyDef.position.Set((position.x + sprite->getContentSize().width / 2) / PTM_RATIO, (position.y + sprite->getContentSize().height / 2) / PTM_RATIO);
	bodyDef.angle = CC_DEGREES_TO_RADIANS(rotation);
	bodyDef.userData = sprite;
	b2Body* body = m_world->CreateBody(&bodyDef);

	b2FixtureDef boxDef;
	if (isCircle)
	{
		b2CircleShape circle;
		circle.m_radius = sprite->getContentSize().width / 2.0f / PTM_RATIO;
		boxDef.shape = &circle;
	}
	else
	{
		b2PolygonShape box;
		box.SetAsBox(sprite->getContentSize().width / 2.0f / PTM_RATIO, sprite->getContentSize().height / 2.0f / PTM_RATIO);
		boxDef.shape = &box;
	}

	if (isEnemy)
	{
		boxDef.userData = (void*)1;
		m_enemies.push_back(body);
	}

	boxDef.density = 0.5f;
	body->CreateFixture(&boxDef);

	m_targets.push_back(body);
}


bool HelloWorld::attachBullet()
{
	if (m_currentBullet < m_bullets.size())
	{
		m_bulletBody = (b2Body*)m_bullets.at(m_currentBullet++);
		m_bulletBody->SetTransform(b2Vec2(230.0f / PTM_RATIO, (155.0f + FLOOR_HEIGHT) / PTM_RATIO), 0.0f);
		m_bulletBody->SetActive(true);

		b2WeldJointDef weldJointDef;
		weldJointDef.Initialize(m_bulletBody, m_armBody, b2Vec2(230.0f / PTM_RATIO, (155.0f + FLOOR_HEIGHT) / PTM_RATIO));
		weldJointDef.collideConnected = false;

		m_bulletJoint = (b2WeldJoint*)m_world->CreateJoint(&weldJointDef);
		return true;
	}

	return false;
}

void HelloWorld::resetBullet()
{
	if (m_enemies.size() == 0)
	{
		// game over
		// We'll do something here later
	}
	else if (this->attachBullet())
	{
		this->runAction(MoveTo::create(2.0f, Vec2::ZERO));
	}
	else
	{
		// We can reset the whole scene here
		// Also, let's do this later
	}
}

void HelloWorld::resetGame()
{
	this->createBullets(4);
	this->attachBullet();
	this->createTargets();
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
	m_world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}


void HelloWorld::tick(float dt) {

	int velocityIterations = 8;
	int positionIterations = 1;

	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	m_world->Step(dt, velocityIterations, positionIterations);

	//Iterate over the bodies in the physics world
	for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL) {
			//Synchronize the AtlasSprites position and rotation with the corresponding body
			Sprite* myActor = (Sprite*)b->GetUserData();
			myActor->setPosition(CCPointMake(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}

	// Arm is being released
	if (m_releasingArm && m_bulletJoint != NULL)
	{
		// Check if the arm reached the end so we can return the limits
		if (m_armJoint->GetJointAngle() <= CC_DEGREES_TO_RADIANS(10))
		{
			m_releasingArm = false;

			// Destroy joint so the bullet will be free
			m_world->DestroyJoint(m_bulletJoint);
			m_bulletJoint = NULL;

			// set up the time delay
			DelayTime *delayAction = DelayTime::create(5);
			// perform the selector call
			CallFunc *callSelectorAction = CCCallFunc::create(CC_CALLBACK_0(HelloWorld::resetBullet,this));
			// run the action
			this->runAction(Sequence::create(delayAction,callSelectorAction,nullptr));
		}
	}

	// Bullet is moving.
	if (m_bulletBody && m_bulletJoint == NULL)
	{
		b2Vec2 position = m_bulletBody->GetPosition();
		Vec2 myPosition = this->getPosition();
		Size screenSize = Director::sharedDirector()->getWinSize();

		// Move the camera.
		if (position.x > screenSize.width / 2.0f / PTM_RATIO)
		{
			myPosition.x = -MIN(screenSize.width * 2.0f - screenSize.width, position.x * PTM_RATIO - screenSize.width / 2.0f);
			this->setPosition(myPosition);
		}
	}
}


bool HelloWorld::onTouchBegan(Touch *touch, Event * event)
{
	if (mouseJoint != NULL) return true;

	Vec2 touchPoint = touch->getLocation();
	Vec2 location = Node::convertToNodeSpace(touchPoint);
	//log("nodeSpace..%f", location.x);

	b2Vec2 locationWorld = b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO);

	if (locationWorld.x < m_armBody->GetWorldCenter().x + 50.0 / PTM_RATIO)
	{
		b2MouseJointDef md;
		md.bodyA = m_groundBody;
		md.bodyB = m_armBody;
		md.target = locationWorld;
		md.maxForce = 2000;

		mouseJoint = (b2MouseJoint *)m_world->CreateJoint(&md);
	}

	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event * event)
{
	if (mouseJoint == NULL) return;

	Vec2 touchPoint = touch->getLocation();
	Vec2 location = Node::convertToNodeSpace(touchPoint);

	b2Vec2 locationWorld = b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO);

	mouseJoint->SetTarget(locationWorld);
}

void HelloWorld::onTouchEnded(Touch *touch, Event * event)
{
	if (mouseJoint != NULL)
	{
		if (m_armJoint->GetJointAngle() >= CC_DEGREES_TO_RADIANS(20))
		{
			m_releasingArm = true;
		}

		m_world->DestroyJoint(mouseJoint);
		mouseJoint = NULL;
	}
}

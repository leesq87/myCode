#include "HelloWorldScene.h"

USING_NS_CC;
#define FLOOR_HEIGHT    62.0f
enum
{
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
	if (!Layer::init())
	{
		return false;
	}

	winSize = Director::getInstance()->getWinSize();


	if (this->createBox2dWorld(true))
	{
		this->schedule(schedule_selector(HelloWorld::tick));
	}

	return true;
}

bool HelloWorld::createBox2dWorld(bool debug)
{
	b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
	_world = new b2World(gravity);
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);


	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	_groundBody = _world->CreateBody(&groundBodyDef);


	b2PolygonShape groundBox;


	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.shape = &groundEdge;

	groundEdge.Set(b2Vec2(0, FLOOR_HEIGHT / PTM_RATIO), b2Vec2(winSize.width * 2 / PTM_RATIO, FLOOR_HEIGHT / PTM_RATIO));
	_groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO), b2Vec2(0, winSize.height / PTM_RATIO));
	_groundBody->CreateFixture(&boxShapeDef);

	groundEdge.Set(b2Vec2(0, winSize.height / PTM_RATIO), b2Vec2(winSize.width * 2 / PTM_RATIO, winSize.height / PTM_RATIO));
	_groundBody->CreateFixture(&boxShapeDef);

	//groundEdge.Set(b2Vec2(winSize.width * 2 / PTM_RATIO, winSize.height / PTM_RATIO), b2Vec2(winSize.width * 2 / PTM_RATIO, 0));
	//groundBody->CreateFixture(&boxShapeDef);

	auto sprite = Sprite::create("bg.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(sprite, -1);

	sprite = Sprite::create("catapult_base_2.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(Vec2(181.0, FLOOR_HEIGHT));
	this->addChild(sprite, 0);

	sprite = Sprite::create("squirrel_1.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(Vec2(11.0, FLOOR_HEIGHT));
	this->addChild(sprite, 0);

	sprite = Sprite::create("catapult_base_1.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(Vec2(181.0, FLOOR_HEIGHT));
	this->addChild(sprite, 9);

	sprite = Sprite::create("squirrel_2.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	sprite->setPosition(Vec2(240.0, FLOOR_HEIGHT));
	this->addChild(sprite, 9);

	sprite = Sprite::create("fg.png");
	sprite->setAnchorPoint(Vec2::ZERO);
	this->addChild(sprite, 10);


	arm = Sprite::create("catapult_arm.png");
	this->addChild(arm, 1);

	b2BodyDef armBodyDef;
	armBodyDef.type = b2_dynamicBody;
	armBodyDef.linearDamping = 1;
	armBodyDef.angularDamping = 1;
	armBodyDef.position.Set(230.0f / PTM_RATIO, (FLOOR_HEIGHT + 91.0f) / PTM_RATIO);
	armBodyDef.userData = arm;
	_armBody = _world->CreateBody(&armBodyDef);

	b2PolygonShape armBox;
	b2FixtureDef armBoxDef;
	armBoxDef.shape = &armBox;
	armBoxDef.density = 0.3F;
	armBox.SetAsBox(11.0f / PTM_RATIO, 91.0f / PTM_RATIO);
	_armFixture = _armBody->CreateFixture(&armBoxDef);

	b2RevoluteJointDef armJointDef;
	armJointDef.Initialize(_groundBody, _armBody, b2Vec2(233.0f / PTM_RATIO, FLOOR_HEIGHT / PTM_RATIO));
	armJointDef.enableMotor = true;
	armJointDef.enableLimit = true;
	armJointDef.motorSpeed = -10; //-1260;
	armJointDef.lowerAngle = CC_DEGREES_TO_RADIANS(9);
	armJointDef.upperAngle = CC_DEGREES_TO_RADIANS(75);
	armJointDef.maxMotorTorque = 700;
	_armJoint = (b2RevoluteJoint*)_world->CreateJoint(&armJointDef);

	_mouseJoint = nullptr;



	auto delayAction = DelayTime::create(0.5f);
	auto callFunc = CallFunc::create(CC_CALLBACK_0(HelloWorld::resetGame, this));
	this->runAction(Sequence::create(delayAction,callFunc, nullptr));

	return true;
}

HelloWorld::~HelloWorld()
{
	delete _world;
	_world = nullptr;
}

void HelloWorld::resetGame()
{
	this->createBullets(4);
	this->attachBullet();
	this->createTargets();
}

void HelloWorld::createBullets(int count)
{
	m_currentBullet = 0;
	float pos = 62.0f;

	if (count > 0)
	{
		float delta = (count > 1) ? ((165.0f - 62.0f - 30.0f) / (count - 1)) : 0.0f;


		for (int i = 0; i<count; i++, pos += delta)
		{
			// Create the bullet
			//
			Sprite *sprite = Sprite::create("acorn.png");
			this->addChild(sprite, 1);

			b2BodyDef bulletBodyDef;
			bulletBodyDef.type = b2_dynamicBody;
			bulletBodyDef.bullet = true;
			bulletBodyDef.position.Set(pos / PTM_RATIO, (FLOOR_HEIGHT + 15.0f) / PTM_RATIO);
			bulletBodyDef.userData = sprite;
			b2Body *bullet = _world->CreateBody(&bulletBodyDef);
			bullet->SetActive(false);

			b2CircleShape circle;
			circle.m_radius = 15.0 / PTM_RATIO;

			b2FixtureDef ballShapeDef;
			ballShapeDef.shape = &circle;
			ballShapeDef.density = 0.8f;
			ballShapeDef.restitution = 0.2f;
			ballShapeDef.friction = 0.99f;
			bullet->CreateFixture(&ballShapeDef);

			m_bullets.push_back(bullet);
		}
	}
}

void HelloWorld::createTargets()
{
	m_targets.clear();
	m_enemies.clear();

	// First block
	this->createTarget("brick_2.png", Vec2(675.0, FLOOR_HEIGHT), 0.0f, false, false, false);
	this->createTarget("brick_1.png", Vec2(741.0, FLOOR_HEIGHT), 0.0f, false, false, false);
	this->createTarget("brick_1.png", Vec2(741.0, FLOOR_HEIGHT + 23.0f), 0.0f, false, false, false);
	this->createTarget("brick_3.png", Vec2(672.0, FLOOR_HEIGHT + 46.0f), 0.0f, false, false, false);
	this->createTarget("brick_1.png", Vec2(707.0, FLOOR_HEIGHT + 58.0f), 0.0f, false, false, false);
	this->createTarget("brick_1.png", Vec2(707.0, FLOOR_HEIGHT + 81.0f), 0.0f, false, false, false);

	this->createTarget("head_dog.png", Vec2(702.0, FLOOR_HEIGHT), 0.0f, true, false, true);
	this->createTarget("head_cat.png", Vec2(680.0, FLOOR_HEIGHT + 58.0f), 0.0f, true, false, true);
	this->createTarget("head_dog.png", Vec2(740.0, FLOOR_HEIGHT + 58.0f), 0.0f, true, false, true);

	// 2 bricks at the right of the first block
	this->createTarget("brick_2.png", Vec2(770.0, FLOOR_HEIGHT), 0.0f, false, false, false);
	this->createTarget("brick_2.png", Vec2(770.0, FLOOR_HEIGHT + 46.0f), 0.0f, false, false, false);

	// The dog between the blocks
	this->createTarget("head_dog.png", Vec2(830.0, FLOOR_HEIGHT), 0.0f, true, false, true);

	// Second block
	this->createTarget("brick_platform.png", Vec2(839.0, FLOOR_HEIGHT), 0.0f, false, true, false);
	this->createTarget("brick_2.png", Vec2(854.0, FLOOR_HEIGHT + 28.0f), 0.0f, false, false, false);
	this->createTarget("brick_2.png", Vec2(854.0, FLOOR_HEIGHT + 28.0f + 46.0f), 0.0f, false, false, false);
	this->createTarget("head_cat.png", Vec2(881.0, FLOOR_HEIGHT + 28.0f), 0.0f, true, false, true);
	this->createTarget("brick_2.png", Vec2(909.0, FLOOR_HEIGHT + 28.0f), 0.0f, false, false, false);
	this->createTarget("brick_1.png", Vec2(909.0, FLOOR_HEIGHT + 28.0f + 46.0f), 0.0f, false, false, false);
	this->createTarget("brick_1.png", Vec2(909.0, FLOOR_HEIGHT + 28.0f + 46.0f + 23.0f), 0.0f, false, false, false);
	this->createTarget("brick_2.png", Vec2(882.0, FLOOR_HEIGHT + 108.0f), 90.0f, false, false, false);
}

void HelloWorld::createTarget(const char *imageName, Vec2 position, float rotation, bool isCircle, bool isStatic, bool isEnemy)
{
	auto sprite = Sprite::create(imageName);
	this->addChild(sprite, 1);

	b2BodyDef bodyDef;
	bodyDef.type = isStatic ? b2_staticBody : b2_dynamicBody;
	bodyDef.position.Set((position.x + sprite->getContentSize().width / 2.0f) / PTM_RATIO,
		(position.y + sprite->getContentSize().height / 2.0f) / PTM_RATIO);
	bodyDef.angle = CC_DEGREES_TO_RADIANS(rotation);
	bodyDef.userData = sprite;
	b2Body *body = _world->CreateBody(&bodyDef);

	b2FixtureDef boxDef;
	b2CircleShape circle;
	b2PolygonShape box;
	if (isCircle)
	{
		circle.m_radius = sprite->getContentSize().width / 2.0f / PTM_RATIO;
		boxDef.shape = &circle;
	}
	else
	{
		box.SetAsBox(sprite->getContentSize().width / 2.0f / PTM_RATIO,
			sprite->getContentSize().height / 2.0f / PTM_RATIO);
		boxDef.shape = &box;
	}

	if (isEnemy)
	{
		boxDef.userData = (void*)1;
		m_enemies.push_back(body);
	}

	boxDef.density = 1.0f;
	boxDef.friction = 0.3f;
	boxDef.restitution = 0.2f;

	body->CreateFixture(&boxDef);

	m_targets.push_back(body);
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

bool HelloWorld::attachBullet()
{
	if (m_currentBullet < m_bullets.size())
	{
		m_bulletBody = (b2Body*)m_bullets.at(m_currentBullet++);
		m_bulletBody->SetTransform(b2Vec2(230.0f / PTM_RATIO, (155.0f + FLOOR_HEIGHT) / PTM_RATIO), 0.0f);
		m_bulletBody->SetActive(true);

		b2WeldJointDef weldJointDef;
		weldJointDef.Initialize(m_bulletBody, _armBody, b2Vec2(230.0f / PTM_RATIO, (155.0f + FLOOR_HEIGHT) / PTM_RATIO));
		weldJointDef.collideConnected = false;

		m_bulletJoint = (b2WeldJoint*)_world->CreateJoint(&weldJointDef);
		return true;
	}

	return false;
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeAllEventListeners();

}

void HelloWorld::tick(float dt)
{
	int velocityIterations = 8;
	int positionIterations = 3;

	_world->Step(dt, velocityIterations, positionIterations);

	for (b2Body *b = _world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != nullptr)
		{
			Sprite* spriteData = (Sprite*)b->GetUserData();
			spriteData->setPosition(Vec2(b->GetPosition().x * PTM_RATIO,
				b->GetPosition().y * PTM_RATIO));
			spriteData->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}

	if (m_releasingArm && m_bulletJoint != NULL)
	{
		// Check if the arm reached the end so we can return the limits
		if (_armJoint->GetJointAngle() <= CC_DEGREES_TO_RADIANS(10))
		{
			m_releasingArm = false;

			// Destroy joint so the bullet will be free
			_world->DestroyJoint(m_bulletJoint);
			m_bulletJoint = NULL;

			// set up the time delay
			auto delayAction = DelayTime::create(5);
			// perform the selector call
			// run the action
			this->runAction(Sequence::create(delayAction,
				CallFunc::create(CC_CALLBACK_0(HelloWorld::resetBullet, this)),
				nullptr));
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
			myPosition.x = -MIN(screenSize.width * 2.0f - screenSize.width,
				position.x * PTM_RATIO - screenSize.width / 2.0f);
			this->setPosition(myPosition);
		}
	}

}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event) {

	auto touchPoint = touch->getLocation();

	if (_mouseJoint != nullptr) {
		return false;
	}

	Vec2 location = touch->getLocationInView();
	location = Director::sharedDirector()->convertToGL(location);
	b2Vec2 locationWorld = b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO);

	if (locationWorld.x < _armBody->GetWorldCenter().x + 50.0 / PTM_RATIO){
		b2MouseJointDef md;
		md.bodyA = _groundBody;
		md.bodyB = _armBody;
		md.target = locationWorld;
		md.maxForce = 2000;
		_mouseJoint = (b2MouseJoint *)_world->CreateJoint(&md);
	}
	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event) {
	auto touchPoint = touch->getLocation();
	if (_mouseJoint == NULL){
		return;
	}
	
	auto myTouch = touch;
	Vec2 location = myTouch->getLocationInView();
	location = Director::sharedDirector()->convertToGL(location);
	b2Vec2 locationWorld = b2Vec2(location.x / PTM_RATIO, location.y / PTM_RATIO);

	_mouseJoint->SetTarget(locationWorld);
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event) {
	if (_mouseJoint != NULL){
		if (_armJoint->GetJointAngle() >= CC_DEGREES_TO_RADIANS(20)){
			m_releasingArm = true;
		}

		_world->DestroyJoint(_mouseJoint);
		_mouseJoint = NULL;
		return;
	}
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

	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
	_world->DrawDebugData();

	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
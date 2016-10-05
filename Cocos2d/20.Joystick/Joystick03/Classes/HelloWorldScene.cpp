#include "HelloWorldScene.h"
#include "ControlManager.h"

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
    
	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan);



	auto listener = EventListenerTouchAllAtOnce::create();
	
	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	JControlManager::getInstance();
	JControlManager::getInstance()->Initialize(this);

	schedule(schedule_selector(HelloWorld::tick), 1.f / 60.f);




    return true;
}

void HelloWorld::tick(float dt) {
	JControlManager::getInstance()->Update(dt);
	if (JControlManager::getInstance()->GetDistance() == 0.f) {
	}
	else {
		float distance = JControlManager::getInstance()->GetDistance() *0.5f + 0.5f;
		float speed = distance*100.f*dt;
		Vec2 axis = JControlManager::getInstance()->GetAxis();
		auto velocity_ = axis*speed;

		pMan->setPosition(pMan->getPosition() + velocity_);

		if (axis.x < 0.f) {
		}
		else if (axis.x>0.f) {
		}
	}
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touch, Event* event) {
	Vec2 point;
	Vec2 touchGlPoint;
	for (auto &item : touch) {
		auto touch = item;
		point = touch->getLocationInView();
		touchGlPoint = Director::getInstance()->convertToGL(point);

		for (int a = 0; a < MAX_BUTTON; ++a) {
			if (JControlManager::getInstance()->IsButtonContainsPoint((eButtonID)a, touchGlPoint)) {
				JControlManager::getInstance()->btnTouchID_[a] = touch;
				JControlManager::getInstance()->btnState_[a] = BEGIN;
				JControlManager::getInstance()->btnTouchPoint_[a] = touchGlPoint;
			}
		}

	}


	JControlManager::getInstance()->SetTouchState(BEGIN);
	JControlManager::getInstance()->SetTouchPoint(touchGlPoint);
}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touch, Event* event) {

	Vec2 point;
	Vec2 TouchGlPoint;
	for (auto &item : touch) {
		auto touch = item;
		point = touch->getLocationInView();
		TouchGlPoint = Director::getInstance()->convertToGL(point);

		for (int a = 0; a < MAX_BUTTON; ++a) {
			if (touch == JControlManager::getInstance()->btnTouchID_[a]) {
				JControlManager::getInstance()->btnState_[a] = MOVE;
				JControlManager::getInstance()->btnTouchPoint_[a] = TouchGlPoint;
			}
		}
	}


	JControlManager::getInstance()->SetTouchState(MOVE);
	JControlManager::getInstance()->SetTouchPoint(TouchGlPoint);
}

void HelloWorld::onTouchesEnded(const std::vector<Touch*>& touch, Event* event) {

	Vec2 point;
	Vec2 touchGlPoint;
	for (auto &item : touch) {
		auto touch = item;
		point = touch->getLocationInView();
		touchGlPoint = Director::getInstance()->convertToGL(point);

		for (int a = 0; a < MAX_BUTTON; ++a) {
			if (touch == JControlManager::getInstance()->btnTouchID_[a]) {
				JControlManager::getInstance()->btnState_[a] = END;
				JControlManager::getInstance()->btnTouchPoint_[a] = touchGlPoint;
			}
		}
	}

	JControlManager::getInstance()->SetTouchState(END);
	JControlManager::getInstance()->SetTouchPoint(touchGlPoint);
}



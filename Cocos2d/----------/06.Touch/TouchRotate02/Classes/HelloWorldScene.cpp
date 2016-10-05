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
    

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(240, 160));
	this->addChild(pMan);

	bSelect = false;

    return true;
}


void HelloWorld::onEnter() {
	Layer::onEnter();

	//싱글터치모드로 터치리스너 등록
	auto listener = EventListenerTouchAllAtOnce::create();

	//swallow

	listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


}
void HelloWorld::onExit() {
	_eventDispatcher->removeAllEventListeners();

	Layer::onExit();
}
void HelloWorld::onTouchesBegan(const std::vector<cocos2d::Touch*> & touches, cocos2d::Event *event) {

	bSelect = false;
	if (touches.size() < 2) {
		return;
	}

	int i = 0;
	for (auto &item : touches) {
		auto touch = item;
		auto touchPoint = touch->getLocation();

		Rect rect = pMan->getBoundingBox();
		if (rect.containsPoint(touchPoint)) {
			log("Touch x:%d / y:  %d", (int)touchPoint.x, (int)touchPoint.y);
			i++;
		}
	}

	if (i > 1)
		bSelect = true;
}

void HelloWorld::onTouchesMoved(const std::vector<cocos2d::Touch*> & touches, cocos2d::Event *event) {
	if (bSelect) {

		auto touch = touches[0];


		Vec2 oldPoint = touch->getPreviousLocation();
		Vec2 newPoint = touch->getLocation();

		Vec2 firstVector = oldPoint - pMan->getPosition();
		float firstRotateAngle = -firstVector.getAngle();
		float previousTouch = CC_RADIANS_TO_DEGREES(firstRotateAngle);

		Vec2 secondVector = newPoint - pMan->getPosition();
		float secondRotateVector = -secondVector.getAngle();
		float currentTouch = CC_RADIANS_TO_DEGREES(secondRotateVector);

		gRotation += currentTouch - previousTouch;
		gRotation = fmod(gRotation, 360);

		pMan->setRotation(gRotation);
	}
}

void HelloWorld::onTouchesEnded(const std::vector<cocos2d::Touch*> & touches, cocos2d::Event *event) {
	bSelect = false;
}
#include "HelloWorldScene.h"

#define FIX_POS(_pos,_min,_max)\
if(_pos<_min)\
_pos = _min;\
else if(_pos>_max)\
_pos=_max;\


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
    //윈도우 사이즈 구하기
	winSize = Director::getInstance()->getVisibleSize();

	//상단 구분용 레이블 추가
	auto label = LabelTTF::create("Accleerometer Test", "Arial", 32);
	label->setPosition(Vec2(winSize.width/2, winSize.height - 50));
	label->setColor(Color3B(0, 0, 0));
	this->addChild(label);

	//중력값에 의해 굴러다니는 볼(스프라이트) 추가

	m_pBall = Sprite::create("CloseNormal.png");
	m_pBall->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	addChild(m_pBall);
	m_pBall->retain();

    return true;
}

HelloWorld::~HelloWorld(void) {
	m_pBall->release();
	Device::setAccelerometerEnabled(false);
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	Device::setAccelerometerEnabled(true);

	auto listener = EventListenerAcceleration::create(
		CC_CALLBACK_2(HelloWorld::onAcceleration, this));

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onAcceleration(Acceleration* acc, Event* event) {
	auto pDir = Director::getInstance();

	//윈도우 사이즈 구하기
	winSize = pDir->getVisibleSize();

	//FIXME : Testing on the Nexus S sometimes _ball is NULL

	if (m_pBall == nullptr) {
		return;
	}

	auto ballSize = m_pBall->getContentSize();
	auto ptNow = m_pBall->getPosition();
	auto ptTemp = pDir->convertToUI(ptNow);

	ptTemp.x += acc->x*9.81f;
	ptTemp.y -= acc->y*9.81f;

	auto ptNext = pDir->convertToGL(ptTemp);

	FIX_POS(ptNext.x, (ballSize.width / 2), (winSize.width - ballSize.width / 2));
	FIX_POS(ptNext.y, (ballSize.height / 2), (winSize.height - ballSize.height / 2));
	m_pBall->setPosition(ptNext);
}

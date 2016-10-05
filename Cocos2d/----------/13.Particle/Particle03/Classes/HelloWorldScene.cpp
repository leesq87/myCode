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
    

    return true;
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);

	Layer::onExit();
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event) {
	auto touchPoint = touch->getLocation();

	this->showParticle(touchPoint);

	return true;
}

void HelloWorld::showParticle(Vec2 pPoint) {
	const char* filname1 = "Particles/BoilingFoam.plist";
	const char* filname2 = "Particles/BurstPipe.plist";
	const char* filname3 = "Particles/Comet.plist";
	const char* filname4 = "Particles/ExplodingRing.plist";
	const char* filname5 = "Particles/Flower.plist";
	const char* filname6 = "Particles/Galaxy.plist";
	const char* filname7 = "Particles/LavaFlow.plist";
	const char* filname8 = "Particles/Phoenix.plist";
	const char* filname9 = "Particles/SmallSun.plist";
	const char* filname10 = "Particles/SpinningPeas.plist";
	const char* filname11 = "Particles/Spiral.plist";
	const char* filname12 = "Particles/SpookyPeas.plist";
	const char* filname13 = "Particles/TestPremultipliedAlpha.plist";
	const char* filname14 = "Particles/Upsidedown.plist";
	const char* filname15 = "Particles/holly.plist";


	ParticleSystem* emitter = ParticleSystemQuad::create(filname3);
	emitter->setPosition(pPoint);
	emitter->setDuration(2.0f);
	emitter->setAutoRemoveOnFinish(true);
	this->addChild(emitter);


}
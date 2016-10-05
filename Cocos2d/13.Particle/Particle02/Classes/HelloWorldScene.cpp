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
	if (!Layer::init() )
    {
        return false;
    }
    //눈내리기
	this->doSnow();


	//// 비내리기
	//this->doRain();
    return true;
}


void HelloWorld::doSnow()
{
	ParticleSystem* m_emitter = ParticleSnow::create();
	m_emitter->retain();

	Point p = m_emitter->getPosition();

	m_emitter->setTotalParticles(200);  // default : 700

	m_emitter->setPosition(Vec2(p.x, p.y - 110));
	m_emitter->setLife(5); // 3
	m_emitter->setLifeVar(1);

	// gravity
	m_emitter->setGravity(Vec2(0, -10));

	// speed of particles
	m_emitter->setSpeed(100);  // 130
	m_emitter->setSpeedVar(30); // 30


	Color4F startColor = m_emitter->getStartColor();
	startColor.r = 0.9f;
	startColor.g = 0.9f;
	startColor.b = 0.9f;
	m_emitter->setStartColor(startColor);


	Color4F endColorVar = m_emitter->getStartColorVar();
	endColorVar.r = 0.0f;
	endColorVar.g = 0.0f;
	endColorVar.b = 0.0f;
	m_emitter->setStartColorVar(endColorVar);

	m_emitter->setEmissionRate(m_emitter->getTotalParticles() / m_emitter->getLife());

	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/snow.png");
	m_emitter->setTexture(texture);



	if (m_emitter != NULL)
	{
		m_emitter->setPosition(Vec2(240, 320));

		this->addChild(m_emitter);
	}
}

void HelloWorld::doRain()
{
	ParticleSystem* m_emitter = ParticleRain::create();
	m_emitter->retain();

	Point p = m_emitter->getPosition();
	m_emitter->setPosition(Vec2(p.x, p.y - 100));
	m_emitter->setLife(4);

	auto texture = Director::getInstance()->getTextureCache()->addImage("Images/fire.png");
	m_emitter->setTexture(texture);
	m_emitter->setScaleY(4);

	if (m_emitter != NULL)
	{
		m_emitter->setPosition(Vec2(240, 320));

		this->addChild(m_emitter);
	}
}


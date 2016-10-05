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
    
	//윈도우 사이즈 구하기
	winSize = Director::getInstance()->getWinSize();

	//Render Texture 만들기
	m_pTarget = RenderTexture::create(winSize.width, winSize.height, Texture2D::PixelFormat::RGBA8888);
	m_pTarget->retain();
	m_pTarget->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	this->addChild(m_pTarget, 1);

	//메뉴 만들기
	MenuItemFont::setFontSize(16);
	auto item1 = MenuItemFont::create("Save Image", CC_CALLBACK_1(HelloWorld::saveImage, this));
	item1->setColor(Color3B::BLACK);
	auto item2 = MenuItemFont::create("Clear", CC_CALLBACK_1(HelloWorld::clearImage, this));
	item2->setColor(Color3B::BLACK);
	auto menu = Menu::create(item1, item2, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(winSize.width - 80, winSize.height - 30));
	this->addChild(menu, 3);

    return true;
}

HelloWorld::~HelloWorld() {
	m_pTarget->release();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onExit() {
	_eventDispatcher->removeEventListener(listener);
	Layer::onExit();
}

void HelloWorld::onTouchesMoved(const std::vector<Touch*> &touches, Event* event) {
	auto touch = touches[0];
	Vec2 start = touch->getLocation();
	Vec2 end = touch->getPreviousLocation();

	m_pTarget->begin();

	//for extra points, we/ll draw this smoothly from the last position and vart the sprite's
	//scale / rotation / offset
	float distance = start.getDistance(end);
	if (distance > 1) {
		int d = (int)distance;
		for (int i = 0; i < d; ++i) {
			auto sprite = Sprite::create("brush2.png");
			sprite->setColor(Color3B::RED);
			//sprite->setOpacity(20);
			//sprite->setOpacity(150);
			m_pBrush.pushBack(sprite);

		}
		for (int i = 0; i < d; i++) {
			float difx = end.x - start.x;
			float dify = end.y - start.y;
			float delta = (float)i / distance;
			m_pBrush.at(i)->setPosition(Vec2(start.x + (difx*delta), start.y + (dify*delta)));
			m_pBrush.at(i)->setRotation(rand() % 360);
			float r = (float)(rand() % 50 / 50.f) + 0.25f;
			m_pBrush.at(i)->setScale(r);

			//m_pBrush.at(i)->setColor(Color3B(rand() % 127 + 128, 255, 255));

			//Call visit to draw the brush, don't call draw
			m_pBrush.at(i)->visit();
		}
	}

	m_pTarget->end();
}

void HelloWorld::saveImage(Ref* sender) {
	static int counter = 0;
	char png[20];
	sprintf(png, "image-%d.png", counter);

	////Type1
	//
	//auto callback = [&](RenderTexture* rt, const std::string&path) {
	//	auto sprite = Sprite::create(path);
	//	addChild(sprite);
	//	sprite->setScale(0.3f);
	//	sprite->setPosition(Vec2(40, 40));
	//	sprite->setRotation(counter * 3);

	//	addChild(sprite);
	//};

	//m_pTarget->saveToFile(png, Image::Format::PNG, true, callback);

	//type2

	m_pTarget->saveToFile(png, Image::Format::PNG, true, nullptr);

	auto image = m_pTarget->newImage();

	auto tex = Director::getInstance()->getTextureCache()->addImage(image, png);

	CC_SAFE_DELETE(image);

	auto sprite = Sprite::createWithTexture(tex);
	sprite->setScale(0.3f);
	sprite->setPosition(Vec2(40, 40));
	sprite->setRotation(counter * 3);

	addChild(sprite);

	//Add this function to avoid crash if we switch to a new scene
	Director::getInstance()->getRenderer()->render();
	log("Image Save %s", png);
	counter++;
}

void HelloWorld::clearImage(Ref* sender) {
	m_pTarget->clear(255, 255, 255, 255);
	//this->removeChild(m_pTarget);

	//m_pTarget = RenderTexture::create(winSize.width, winSize.height, Texture2D::PixelFormat::RGBA8888);
	//m_pTarget->retain();
	//m_pTarget->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	//this->addChild(m_pTarget, 1);

}
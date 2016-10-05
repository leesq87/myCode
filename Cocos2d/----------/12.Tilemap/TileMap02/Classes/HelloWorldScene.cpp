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
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}


	tmap = TMXTiledMap::create("TileMaps/TestDesert.tmx");
	this->addChild(tmap, 0, 11);

	auto objects = tmap->getObjectGroup("Objects");

	ValueMap spawnPoint = objects->getObject("SpawnPoint");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	dragonPosition = Vec2(x, y);

	this->createDragon();

	Size s = tmap->getContentSize();
	log("ContentSize : %f, %f", s.width, s.height);

	return true;
}

void HelloWorld::createDragon() {
	//움직이는 드래곤 넣기
	auto texture = Director::getInstance()->getTextureCache()->addImage("animations/dragon_animation.png");

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1);

	for (int i = 0; i < 6; i++) {
		int index = i % 4;
		int rowIndex = i / 4;

		animation->addSpriteFrameWithTexture(texture, Rect(index * 130, rowIndex * 140, 130, 140));
	}

	//스프라이트 생성 및 초기화

	dragon = Sprite::createWithTexture(texture, Rect(0, 0, 130, 140));
	dragon->setPosition(dragonPosition);
	this->addChild(dragon);

	dragon->setFlippedX(true);
	dragon->setScale(0.5);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	dragon->runAction(rep);

}



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
    
	winSize = Director::getInstance()->getWinSize();

	tmap = TMXTiledMap::create("TileMaps/TestDesert.tmx");
	background = tmap->getLayer("background");
	items = tmap->getLayer("Items");
	metainfo = tmap->getLayer("MetaInfo");
	metainfo->setVisible(false);
	this->addChild(tmap, 0, 11);

	//타일맵에서 OBjects라고 지정한 오브젝트 레이어의 객체들을 가져온다
	auto objects = tmap->getObjectGroup("Objects");
	//오브젝트 레이어에서 spawnPoint라고 지정한 속성값읽어오기
	ValueMap spawnPoint = objects->getObject("SpawnPoint");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();


	dragonPosition = Vec2(x, y);

	this->createDragon();


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
	dragon->setPosition(Vec2(240, 160));
	this->addChild(dragon);

	dragon->setFlippedX(true);
	dragon->setScale(0.5);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	dragon->runAction(rep);


}



void HelloWorld::onEnter() {
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}
void HelloWorld::onExit() {
	_eventDispatcher->removeEventListenersForType(EventListener::Type::TOUCH_ONE_BY_ONE);
	Layer::onExit();

}



bool HelloWorld::onTouchBegan(Touch *touch, Event *event) {
	return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *event) {
	auto touchPoint = touch->getLocation();
	touchPoint = this->convertToNodeSpace(touchPoint);

	Vec2 playerPos = dragon->getPosition();
	Vec2 diff = touchPoint - playerPos;

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += tmap->getTileSize().width;

			//드래곤의 방향을 바꾼다
			dragon->setFlippedX(true);
		}
		else {
			playerPos.x -= tmap->getTileSize().width;
			dragon->setFlippedX(false);
		}
	}
	else {
		if (diff.y > 0) {
			playerPos.y += tmap->getTileSize().height;
		}
		else {
			playerPos.y -= tmap->getTileSize().height;
		}
	}


	if (playerPos.x <= (tmap->getMapSize().width * tmap->getTileSize().width) &&
		playerPos.y <= (tmap->getMapSize().height * tmap->getTileSize().height) &&
		playerPos.y >= 0 && playerPos.x >= 0) {
		//드래곤의 새로운 위치 지정
		//dragon->setPosition(playerPos);
		this->setPlayerPosition(playerPos);
	}

	//드래곤의 위치에 맞춰 화면 위치
	this->setViewpointCenter(dragon->getPosition());
}

void HelloWorld::setViewpointCenter(Vec2 position) {

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);

	x = MIN(x, (tmap->getMapSize().width * tmap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (tmap->getMapSize().height * tmap->getTileSize().height) - winSize.height / 2);

	Vec2 actualPosition = Vec2(x, y);
	Vec2 centerOfView = Vec2(winSize.width / 2, winSize.height / 2);
	Vec2 viewPoint = centerOfView - actualPosition;

	this->setPosition(viewPoint);

}

//현재 탭으로 선택된 타일의 위치를 가져온다

Vec2 HelloWorld::tileCoordForPosition(Vec2 position) {
	int x = position.x / tmap->getTileSize().width;
	int y = ((tmap->getMapSize().height * tmap->getTileSize().height) - position.y) / tmap->getTileSize().height;
	return Vec2(x, y);

}

void HelloWorld::setPlayerPosition(Vec2 position) {
	// 탭된 위치 구하기
	Vec2 tileCoord = this->tileCoordForPosition(position);

	//현재 위치의 tile GiD 구하기
	int tileGid = this->metainfo->getTileGIDAt(tileCoord);

	if (tileGid) {

		//타일맵에서 GID에 해당하는 부분의 속성 읽어오기
		Value properties = tmap->getPropertiesForGID(tileGid);

		if (!properties.isNull()) {
			std::string wall = properties.asValueMap()["Wall"].asString();
			if (wall == "YES") {
				log("wall...");
				return;
			}
			std::string item1 = properties.asValueMap()["Items"].asString();
			if (item1 == "YES") {
				this->metainfo->removeTileAt(tileCoord);
				items->removeTileAt(tileCoord);

				log("아이템획득!!");
			}
		}
	}

	//파라미터로 들어온 위치에 드래곤 위치 조정
	dragon->setPosition(position);
}

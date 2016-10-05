#include "HelloWorldScene.h"
#include <math.h>

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
	Stage = 0;
	
	winSize = Director::getInstance()->getWinSize();

	Panal = Sprite::create("tilemap/white-512x512.png");
	Panal->setTextureRect(Rect(0, 0, 64, 320));
	Panal->setPosition(Vec2(448, 160));
	Panal->setColor(Color3B::BLACK);
	this->  addChild(Panal, 3);
	
	State = Sprite::create("tilemap/white-512x512.png");
	State->setTextureRect(Rect(0, 0, 48, 48));
	State->setPosition(Vec2(32, 280));
	State->setColor(Color3B::WHITE);
	Panal->addChild(State, 1);

	MenuItemFont::setFontSize(20);

	auto lReset = MenuItemFont::create("Reset", CC_CALLBACK_0(HelloWorld::createStage,this,1 ));
	lReset->setColor(Color3B::WHITE);
	auto pMenu = Menu::create(lReset, nullptr);
	pMenu->alignItemsVertically();
	pMenu->setPosition(Vec2(32, 32));
	Panal->addChild(pMenu, 1);


	this->createStage(0);

    return true;
}

void HelloWorld::createStage(int a) {
	if (a == 1)
		Stage--;
	Stage++;
	weapon = 0;
	for (int i = 0; i < Wolf.size(); i++)
		Wolf.popBack();
	for (int i = 0; i < Jelly.size(); i++)
		Jelly.popBack();
	for (int i = 0; i < Demon.size(); i++)
		Demon.popBack();
	for (int i = 0; i < Sword.size(); i++)
		Sword.popBack();
	for (int i = 0; i < Mace.size(); i++)
		Mace.popBack();
	for (int i = 0; i < Holy.size(); i++)
		Holy.popBack();

	State->removeChild(iWeapon, false);
	//tmap->removeAllChildren();

	this->removeChild(tmap);
	if (Stage == 1) {

		tmap = TMXTiledMap::create("tilemap/Stage1.tmx");
		stage = tmap->getLayer("Stage1");
		metainfo = tmap->getLayer("MetaInfo1");
		metainfo->setVisible(false);
		this->addChild(tmap, 0, 11);

		auto objects = tmap->getObjectGroup("player1");
		ValueMap StartPoint = objects->getObject("StartPoint");

		int x = StartPoint["x"].asInt();
		int y = StartPoint["y"].asInt();

		playerPosition = Vec2(x, y);
	}
	else if (Stage == 2) {
		tmap = TMXTiledMap::create("tilemap/Stage2.tmx");
		stage = tmap->getLayer("Stage2");
		metainfo = tmap->getLayer("MetaInfo2");
		metainfo->setVisible(false);
		this->addChild(tmap, 0, 11);

		auto objects = tmap->getObjectGroup("player2");

		ValueMap StartPoint = objects->getObject("StartPoint");

		int x = StartPoint["x"].asInt();
		int y = StartPoint["y"].asInt();

		log("xy ::%d ,%d", x, y);
		playerPosition = Vec2(x, y);

	}
	else if (Stage == 3) {
		tmap = TMXTiledMap::create("tilemap/Stage3.tmx");
		stage = tmap->getLayer("Stage3");
		metainfo = tmap->getLayer("MetaInfo3");
		metainfo->setVisible(false);
		this->addChild(tmap, 0, 11);

		auto objects = tmap->getObjectGroup("player3");

		ValueMap StartPoint = objects->getObject("StartPoint");

		int x = StartPoint["x"].asInt();
		int y = StartPoint["y"].asInt();

		log("xy ::%d ,%d", x, y);
		playerPosition = Vec2(x, y);
	}
	else if (Stage == 4) {
		Stage = 0;
		return createStage(0);
	}

	this->createMeta();
	this->createPlayer();
}
	
void HelloWorld::createMeta() {
	auto cache2 = SpriteFrameCache::getInstance();
	cache2->addSpriteFramesWithFile("tilemap/Holygrail.plist");

	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 10; y++) {
			int tileGid = this->metainfo->getTileGIDAt(Vec2(x, y));
			if (tileGid) {
				Value properties = tmap->getPropertiesForGID(tileGid);

				if (!properties.isNull()) {
					std::string mon = properties.asValueMap()["monster"].asString();
					std::string item = properties.asValueMap()["item"].asString();
					if (mon == "wolf") {
						Vector<SpriteFrame *>WolfFrames;
						SpriteFrame* WolfFrame1 = cache2->getSpriteFrameByName("Wolf2.png");
						SpriteFrame* WolfFrame2 = cache2->getSpriteFrameByName("Wolf3.png");
						SpriteFrame* WolfFrame3 = cache2->getSpriteFrameByName("Wolf1.png");
						WolfFrames.pushBack(WolfFrame1);
						WolfFrames.pushBack(WolfFrame2);
						WolfFrames.pushBack(WolfFrame3);
						auto WolfAnimation = Animation::createWithSpriteFrames(WolfFrames, 0.1f);
						auto WolfAnimate = Animate::create(WolfAnimation);
						auto repWolf = RepeatForever::create(WolfAnimate);
						auto sWolf = Sprite::createWithSpriteFrameName("Wolf2.png");
						sWolf->setPosition(Vec2((x * 32)+16, 320 - ((y * 32)+16)));
						sWolf->runAction(repWolf);
						tmap->addChild(sWolf, 1);
						Wolf.pushBack(sWolf);
						
					}
					if (mon == "jelly") {
						Vector<SpriteFrame *>jellyFrames;
						SpriteFrame* JellyFrame1 = cache2->getSpriteFrameByName("Jelly1.png");
						SpriteFrame* JellyFrame2 = cache2->getSpriteFrameByName("Jelly2.png");
						SpriteFrame* JellyFrame3 = cache2->getSpriteFrameByName("Jelly3.png");
						jellyFrames.pushBack(JellyFrame1);
						jellyFrames.pushBack(JellyFrame2);
						jellyFrames.pushBack(JellyFrame3);
						auto JellyAnimation = Animation::createWithSpriteFrames(jellyFrames, 0.1f);
						auto JellyAnimate = Animate::create(JellyAnimation);
						auto repJelly = RepeatForever::create(JellyAnimate);
						auto sJelly = Sprite::createWithSpriteFrameName("Jelly1.png");
						sJelly->setPosition(Vec2((x * 32) + 16, 320 - ((y * 32) + 16)));
						sJelly->runAction(repJelly);
						tmap->addChild(sJelly, 1);
						Jelly.pushBack(sJelly);
					}
					if (mon == "devil") {
						Vector<SpriteFrame *>DemonFrames;
						SpriteFrame* DemonFrame1 = cache2->getSpriteFrameByName("Demon1.png");
						SpriteFrame* DemonFrame2 = cache2->getSpriteFrameByName("Demon2.png");
						SpriteFrame* DemonFrame3 = cache2->getSpriteFrameByName("Demon3.png");
						DemonFrames.pushBack(DemonFrame1);
						DemonFrames.pushBack(DemonFrame2);
						DemonFrames.pushBack(DemonFrame3);
						auto DemonAnimation = Animation::createWithSpriteFrames(DemonFrames, 0.1f);
						auto DemonAnimate = Animate::create(DemonAnimation);
						auto repDemon = RepeatForever::create(DemonAnimate);
						auto sDemon = Sprite::createWithSpriteFrameName("Demon1.png");
						sDemon->setPosition(Vec2((x * 32) + 16, 320 - ((y * 32) + 16)));
						sDemon->runAction(repDemon);
						tmap->addChild(sDemon, 1);
						Demon.pushBack(sDemon);
					}
					if (mon == "box") {
						Box = Sprite::createWithSpriteFrameName("I_Chest01.png");
						Box->setPosition(Vec2((x * 32) + 16, 320 - ((y * 32) + 16)));
						tmap->addChild(Box, 1);
					}
					if (item == "sword") {
						auto sSword = Sprite::createWithSpriteFrameName("W_Sword001.png");
						sSword->setPosition(Vec2((x * 32) + 16, 320 - ((y * 32) + 16)));
						tmap->addChild(sSword, 1);
						Sword.pushBack(sSword);
					}
					if (item == "mace") {
						auto sMace = Sprite::createWithSpriteFrameName("W_Mace008.png");
						sMace->setPosition(Vec2((x * 32) + 16, 320 - ((y * 32) + 16)));
						tmap->addChild(sMace, 1);
						Mace.pushBack(sMace);

					}
					if (item == "holy") {
						auto sHoly = Sprite::createWithSpriteFrameName("W_Sword015.png");
						sHoly->setPosition(Vec2((x * 32) + 16, 320 - ((y * 32) + 16)));
						tmap->addChild(sHoly, 1);
						Holy.pushBack(sHoly);
					}
					if (item == "key") {
						Key = Sprite::createWithSpriteFrameName("I_Key02.png");
						Key->setPosition(Vec2((x * 32) + 16, 320 - ((y * 32) + 16)));
						tmap->addChild(Key, 1);

					}
				}
			}
		}
	}
}

void HelloWorld::createPlayer() {
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("tilemap/Holygrail.plist");

	Vector<SpriteFrame*> DownFrames;
	SpriteFrame* DownFrame1 = cache->getSpriteFrameByName("Hero02.png");
	SpriteFrame* DownFrame2 = cache->getSpriteFrameByName("Hero03.png");
	SpriteFrame* DownFrame3 = cache->getSpriteFrameByName("Hero01.png");
	DownFrames.pushBack(DownFrame1);
	DownFrames.pushBack(DownFrame2);
	DownFrames.pushBack(DownFrame3);

	auto animationDown = Animation::createWithSpriteFrames(DownFrames, 0.1f);
	auto animateDown = Animate::create(animationDown);
	auto repDown = RepeatForever::create(animateDown);
	player = Sprite::createWithSpriteFrameName("Hero01.png");
	player->setPosition(playerPosition);
	tmap->addChild(player, 1);
	player->runAction(repDown);

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

	Vec2 playerPos = player->getPosition();
	Vec2 diff = touchPoint - playerPos;

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += tmap->getTileSize().width;

			//드래곤의 방향을 바꾼다
			player->setFlippedX(true);
		}
		else {
			playerPos.x -= tmap->getTileSize().width;
			player->setFlippedX(false);
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
		//player->setPosition(playerPos);
		this->setPlayerPosition(playerPos);
	}
}
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
			std::string mon = properties.asValueMap()["monster"].asString();
			std::string item = properties.asValueMap()["item"].asString();
			std::string wall = properties.asValueMap()["wall"].asString();
			if (wall == "yes") {
				log("wall");
				return;
			}

			if (mon == "wolf") {
				if (weapon == 1) {
					for (int i = 0; i < Wolf.size(); i++) {
						auto obj = (Sprite *)Wolf.at(i);
						if (obj->boundingBox().containsPoint(position)) {
							this->metainfo->removeTileAt(tileCoord);
							log("wolf");
							tmap->removeChild(obj);
							Wolf.eraseObject(obj);
							weapon = 0;
							State->removeChild(iWeapon, false);
						}
					}
				}
				else {
					log("not sword");
					return;
				}
			}
			if (mon == "jelly") {
				if (weapon == 2) {
					for (int i = 0; i < Jelly.size(); i++) {
						auto obj = (Sprite *)Jelly.at(i);
						if (obj->boundingBox().containsPoint(position)) {
							this->metainfo->removeTileAt(tileCoord);
							log("jelly");
							tmap->removeChild(obj);
							Jelly.eraseObject(obj);
							weapon = 0;
							State->removeChild(iWeapon, false);
						}
					}
				}
				else {
					log("not mace");
					return;
				}
			}
			if (mon == "devil") {
				if (weapon == 3) {
					for (int i = 0; i < Demon.size(); i++) {
						auto obj = (Sprite *)Demon.at(i);
						if (obj->boundingBox().containsPoint(position)) {
							this->metainfo->removeTileAt(tileCoord);
							log("Demon");
							tmap->removeChild(obj);
							Demon.eraseObject(obj);
							weapon = 0;
							State->removeChild(iWeapon, false);
						}
					}
				}
				else {
					log("not holy");
					return;
				}
			}
			if (mon == "box") {
				if (weapon == 4) {
					log("box");
					tmap->removeChild(Box);
					State->removeChild(iWeapon, false);
					//this->createStage(0);
					//return;
					weapon = 5;
				}
				else {
					log("not key");
					return;
				}
			}
			if (item == "sword") {
				if (weapon == 0) {
					for (int i = 0; i < Sword.size(); i++) {
						auto obj = (Sprite *)Sword.at(i);
						if (obj->boundingBox().containsPoint(position)) {
							this->metainfo->removeTileAt(tileCoord);
							log("Sword");
							tmap->removeChild(obj);
							Sword.eraseObject(obj);
							weapon = 1;
							State->removeChild(iWeapon, false);
							iWeapon = Sprite::createWithSpriteFrameName("W_Sword001.png");
							iWeapon->setPosition(Vec2(24, 24));
							State->addChild(iWeapon);
						}
					}
				}
				else {
					log("not empty");
					return;
				}
			}
			if (item == "mace") {
				if (weapon == 0) {
					for (int i = 0; i < Mace.size(); i++) {
						auto obj = (Sprite *)Mace.at(i);
						if (obj->boundingBox().containsPoint(position)) {
							this->metainfo->removeTileAt(tileCoord);
							log("Mace");
							tmap->removeChild(obj);
							Mace.eraseObject(obj);
							weapon = 2;
							State->removeChild(iWeapon, false);
							iWeapon = Sprite::createWithSpriteFrameName("W_Mace008.png");
							iWeapon->setPosition(Vec2(24, 24));
							State->addChild(iWeapon);
						}
					}
				}
				else {
					log("not empty");
					return;
				}
			}
			if (item == "holy") {
				if (weapon == 0) {
					for (int i = 0; i < Holy.size(); i++) {
						auto obj = (Sprite *)Holy.at(i);
						if (obj->boundingBox().containsPoint(position)) {
							this->metainfo->removeTileAt(tileCoord);
							log("Holy");
							tmap->removeChild(obj);
							Holy.eraseObject(obj);

							weapon = 3;
							State->removeChild(iWeapon, false);
							iWeapon = Sprite::createWithSpriteFrameName("W_Sword015.png");
							iWeapon->setPosition(Vec2(24, 24));
							State->addChild(iWeapon);
						}
					}
				}
				else {
					log("not empty");
					return;
				}
			}
			if (item == "key") {
				if (weapon == 0) {
					log("key");
					tmap->removeChild(Key);

					weapon = 4;
					State->removeChild(iWeapon, false);
					iWeapon = Sprite::createWithSpriteFrameName("I_Key02.png");
					iWeapon->setPosition(Vec2(24, 24));
					State->addChild(iWeapon);
				}
				else {
					log("not empty");
					return;
				}
			}
		}
	}
	if (weapon != 5) 
		player->setPosition(position);
	if(weapon == 5)
		createStage(0);


}


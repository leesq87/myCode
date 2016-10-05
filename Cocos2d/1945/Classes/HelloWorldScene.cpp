#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <stdlib.h>

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;


USING_NS_CC;

HelloWorld::HelloWorld():regenCheckTime_(-1.f)
{
}


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
    

	MenuItemImage *pCloseItem = MenuItemImage::create("Images/close.png","Images/closeSelected.png",this,  menu_selector(HelloWorld::menuCloseCallback));
	pCloseItem->setPosition(Vec2(Director::getInstance()->getWinSize().width - 20, 20));

	Menu *pMenu = Menu::create(pCloseItem, nullptr);
	pMenu->setPosition(Vec2(0,0));
	this->addChild(pMenu, 1);

	size_ = CCDirector::getInstance()->getWinSize();

	auto *pLabel = LabelTTF::create("1945", "Thonduri", 34);
	pLabel->setColor(Color3B::RED);
	pLabel->setPosition(Vec2(size_.width / 2, size_.height - 20));
	this->addChild(pLabel, 1);

	auto *pSprite = Sprite::create("1945/bg.png");
	pSprite->setPosition(Vec2(size_.width / 2, size_.height / 2));
	this->addChild(pSprite, 0);

	player_ = Sprite::create("1945/airplain_01.png");
	player_->setPosition(Vec2(size_.width / 2, 50));
	this->addChild(player_, 1);

	//setTouchEnabled(true);

	this->schedule(schedule_selector(HelloWorld::mytick));
	this->schedule(schedule_selector(HelloWorld::RegenEnemy), 1);
	this->schedule(schedule_selector(HelloWorld::Shooting),0.2);



    return true;
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	//싱글터치모드로 터치리스너 등록
	auto listener = EventListenerTouchOneByOne::create();
	//swallow

	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


}
void HelloWorld::onExit() {
	_eventDispatcher->removeAllEventListeners();

	Layer::onExit();
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
	if (!player_)
		return true;

	Point touchPoint = touch->getLocation();
	Point touchGlPoint = Director::sharedDirector()->convertToGL(touchPoint);

	Point playerPos = player_->getPosition();
	distance_ = Vec2(playerPos.x - touchGlPoint.x, playerPos.y - touchGlPoint.y);

	return true;

}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
	if (!player_)
		return;

	Point touchPoint = touch->getLocationInView();
	Point touchGlPoint = Director::getInstance()->convertToGL(touchPoint);

	Point pos = Vec2(touchGlPoint.x + distance_.x, touchGlPoint.y + distance_.y);

	if (pos.x < 0.f) {
		pos.x = 0.f;
		distance_ = Vec2(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}
	else if (pos.x >size_.width) {
		pos.x = size_.width;
		distance_ = Vec2(pos.x - touchPoint.x, pos.y - touchGlPoint.y);
	}

	if (pos.y < 0.f) {
		pos.y = 0.f;
		distance_ = Vec2(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}
	else if (pos.y>size_.height) {
		pos.y = size_.height;
		distance_ = Vec2(pos.x - touchGlPoint.x, pos.y - touchGlPoint.y);
	}

	player_->setPosition(pos);
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
}

void HelloWorld::menuCloseCallback(Ref* pSender) {
	Director::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::RegenEnemy(float time) {
	for (int a = 0; a < RANDOM_INT(1, 5); ++a) {
		Size size = Director::getInstance()->getWinSize();
		AddEnemy(Vec2(RANDOM_INT(0, (int)size.width), size.height));
	}
}

void HelloWorld::AddEnemy(const Vec2& position) {
	Size size = Director::getInstance()->getWinSize();

	//적 비행기 하나를 Scene에 추가
	auto enemy = Sprite::create("1945/enemy_01.png");
	enemy->setPosition(position); //???
	addChild(enemy);

	//화면 아래로 내려가는 액션
	auto move = MoveBy::create(3, Vec2(0, -size.height));
	enemy->runAction(move);

	//배열에 방금 생성된 적 비행기 스프라이트 포인터를 배열 요소로 추가
	enemy_.pushBack(enemy);

}

void HelloWorld::Shooting(float time) {
	if (!player_)
		return;

	for (int a = 0; a < MAX_MISSILE; ++a) {
		auto missile = Sprite::create("1945/missile.png");

		if (a == 0) {
			missile->setPosition(Vec2(player_->getPositionX() - 16.f, player_->getPositionY()));
		}
		else if (a == 1) {
			missile->setPosition(Vec2(player_->getPositionX() + 16.f, player_->getPositionY()));
		}

		addChild(missile);
		Size size = Director::sharedDirector()->getWinSize();
		auto move = MoveBy::create(0.75, Vec2(0, size.height));
		missile->runAction(move);

		missile_.pushBack(missile);
	}
}

void HelloWorld::mytick(float time) {

	vector<Sprite *>::iterator it = enemy_.begin();
	vector<Sprite *>::iterator it2 = missile_.begin();

	vector<Sprite *> eraseEnemy;
	vector<Sprite *> eraseShoot;


	for (int i = 0; i < enemy_.size();i++) {
		auto obj = (Sprite *)enemy_.at(i);

		//적 비행기가 화면 아래로 사라졌을 경우 메모리에서 삭제
		if (obj->getPosition().y <= 0) {
			//Scene에서 적비행기 제거
			removeChild(obj, false);

			//addObject로 추가했떤 스프라이트 포인터를 배열에서 지움
			enemy_.eraseObject(obj);

			continue;
		}

		for (int a = 0; a < MAX_MISSILE; ++a) {
			for (int j = 0; j < missile_.size();j++) {
				auto missile = (Sprite *)missile_.at(j);
				//미사일이 화면위로 사라졌을때
				if (missile->getPositionY() >= size_.height) {

					//미사일 삭제
					removeChild(missile, false);
					missile_.eraseObject(missile);
					continue;
				}

				if (missile->boundingBox().intersectsRect(obj->boundingBox())) {

					//미사일과 적 비행기가 부딪혔을때
					PutCrashEffect(obj->getPosition());

					//적 비행기 삭제
					removeChild(obj, false);
					enemy_.eraseObject(obj);
					//eraseEnemy.push_back(spr);

					//미사일 삭제
					removeChild(missile, false);
					missile_.eraseObject(missile);
					//eraseShoot.push_back(missile);
				}
			}
		}

		if (player_) {

			//intersectsRect함수 리턴값이 충돌하면 true를 리턴
			if (player_->boundingBox().intersectsRect(obj->boundingBox())) {
				//충돌했을때 처리

				//1. 폭파 이펙트 출력
				PutCrashEffect(player_->getPosition());
				PutCrashEffect(obj->getPosition());

				//2. 적 비행기를 화면에서 없애준다

				//Scene에서 적비행기 스프라이트를 제거
				removeChild(obj, false);
				enemy_.eraseObject(obj);
				removeChild(player_, false);
				player_ = nullptr;

				regenCheckTime_ = 0.f;
			}
		}
		//for (int a = 0; a < eraseEnemy.size(); ++a) {

		//}
		//for (int a = 0; a < eraseShoot.size(); ++a) {

		//}
	}



	if (!player_ && regenCheckTime_ != -1.f) {
		//시간을 누적시켜서 3초이상 경과되었을때만 부활
		regenCheckTime_ += time;
		if (regenCheckTime_ >= 3.f) {
			//유저 비행기 부활처리
			player_ = Sprite::create("1945/airplain_01.png");
			player_->setPosition(Vec2(size_.width / 2, 50));
			this->addChild(player_, 1);
		}
	}


}

void HelloWorld::PutCrashEffect(const Vec2 &pos) {
	//첫번째 스프라이트가 로딩되어 베이스
	auto expBase = Sprite::create("exps/exp_01.png");
	expBase->setPosition(pos);

	//애니메이션 스프라이트 5프레임을 차례로 등록해줌
	auto animation = Animation::create();
	animation->addSpriteFrameWithFileName("exps/exp_01.png");
	animation->addSpriteFrameWithFileName("exps/exp_02.png");
	animation->addSpriteFrameWithFileName("exps/exp_03.png");
	animation->addSpriteFrameWithFileName("exps/exp_04.png");
	animation->addSpriteFrameWithFileName("exps/exp_05.png");

	//0.1초 간격으로 애니메이션 처리설정
	animation->setDelayPerUnit(0.1);

	//애니메이션이 끝나고 시작 프레임(1번)으로 돌아간다.
	animation->setRestoreOriginalFrame(true);

	//애니메이션 생성
	auto animate = Animate::create(animation);

	//애니메이션 끝나면 removechild를 자동으로후출 메모리 삭제 액션임
	auto removeAction = CallFunc::create(expBase, CC_CALLFUNC_SELECTOR(Node::removeFromParent));

	//애니메이션과 리무브 액션 2개의 액션을 하나의 시퀀스로 등록후 runaction실행
	auto seq = Sequence::create(animate, removeAction, nullptr);
	this->addChild(expBase); //신에 이펙트를 추가--베이스 스프라이트
	expBase->runAction(seq); //시퀀스 실행

}

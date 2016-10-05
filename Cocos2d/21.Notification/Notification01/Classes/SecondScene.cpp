#include "SecondScene.h"

USING_NS_CC;

Scene* SecondScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SecondScene::create();
	scene->addChild(layer);
	return scene;
}

bool SecondScene::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 100)))
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();

	auto popLayer = LayerColor::create(Color4B(0, 2555, 0, 255), 300, 200);
	popLayer->setAnchorPoint(Vec2(0, 0));
	popLayer->setPosition(Vec2((winSize.width - popLayer->getContentSize().width) / 2, (winSize.height - popLayer->getContentSize().height) / 2));

	this->addChild(popLayer);

	MenuItemFont::setFontSize(14.0f);

	auto pMenuItem1 = MenuItemFont::create("Notification Center Test", CC_CALLBACK_1(SecondScene::doSendMsg, this));
	pMenuItem1->setColor(Color3B(0, 0, 0));

	auto pMenuItem2 = MenuItemFont::create("창닫기", CC_CALLBACK_1(SecondScene::coClose, this));
	pMenuItem2->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);
	pMenu->alignItemsVerticallyWithPadding(20.0f);
	pMenu->setPosition(Vec2(150, 100));
	popLayer->addChild(pMenu);

	return true;
}

void SecondScene::doSendMsg(Ref* pSender) {
	//노티피케이션 메시지 보내기 : 부모뷰 터치 델리게이트 등록
	//int index = 1;
	//NotificationCenter::getInstance()->postNotification("TouchStatus",(Ref*)(intptr_t)index);

	std::string str1 = "홍길동";
	char str2[20] = { 0 };
	sprintf(str2, "%s", str1.c_str());

	NotificationCenter::getInstance()->postNotification("TouchStatus", (Ref*)str2);

}

void SecondScene::coClose(Ref* pSender) {
	//팝업창 제거
	this->removeFromParentAndCleanup(true);
}





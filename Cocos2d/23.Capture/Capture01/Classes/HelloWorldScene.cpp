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
    
	auto sp1 = Sprite::create("Images/grossini.png");
	sp1->setPosition(Vec2(120, 160));
	addChild(sp1);

	auto sp2 = Sprite::create("Images/grossinis_sister1.png");
	sp2->setPosition(Vec2(120 * 3, 160));
	addChild(sp2);

	auto label1 = Label::createWithTTF(TTFConfig("fonts/Marker Felt.ttf", 24), "capture all");
	label1->setColor(Color3B::BLACK);
	auto mi1 = MenuItemLabel::create(label1, CC_CALLBACK_1(HelloWorld::onCaptured, this));

	auto menu = Menu::create(mi1, nullptr);
	addChild(menu);
	menu->setPosition(240, 80);

	_filename = "";

    return true;
}

void HelloWorld::onCaptured(Ref*) {
	Director::getInstance()->getTextureCache()->removeTextureForKey(_filename);
	removeChildByTag(childTag);
	_filename = "CaptureScreenTest.png";
	utils::captureScreen(CC_CALLBACK_2(HelloWorld::afterCaptured, this), _filename);

}

void HelloWorld::afterCaptured(bool succeed, const std::string& outputFile) {
	if (succeed) {
		auto sp = Sprite::create(outputFile);
		addChild(sp, 0, childTag);
		sp->setPosition(Vec2(240, 200));
		sp->setScale(0.25);

		_filename = outputFile;
	}
	else {
		log("Capture screen failed.");
	}
}

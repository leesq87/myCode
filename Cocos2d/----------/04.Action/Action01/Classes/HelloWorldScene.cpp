#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    
	MenuItemFont::setFontSize(28);

	auto pMenuItem = MenuItemFont::create("Action", CC_CALLBACK_1(HelloWorld::doAction, this));
	pMenuItem->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(pMenuItem, NULL);

	pMenu->alignItemsHorizontally();

	pMenu->setPosition(Vec2(240, 50));

	this->addChild(pMenu);

	pMan = Sprite::create("Images/grossini.png");
	pMan->setPosition(Vec2(50, 200));

	this->addChild(pMan);

    return true;
}

void HelloWorld::doAction(Ref *pSender) {
/* ex1 */
//	auto myAction = MoveBy::create(2, Vec2(400, 0));
//	auto myAction = MoveTo::create(2, Vec2(400, 0));
//	auto myAction = JumpBy::create(2, Vec2(400, 0),50,3);
//	auto myAction = JumpTo::create(2, Vec2(400, 0),50,3);

// bezier
	//ccBezierConfig bezier1;
	//bezier1.controlPoint_1 = Vec2(150, 150);
	//bezier1.controlPoint_2 = Vec2(250, -150);
	//bezier1.endPosition = Vec2(350, 0);

	//ccBezierConfig bezier2;
	//bezier2.controlPoint_1 = Vec2(200, 150);
	//bezier2.controlPoint_2 = Vec2(200, 150);
	//bezier2.endPosition = Vec2(350, 0);

	//	auto myAction = BezierBy::create(3, bezier1);
	////	auto myAction = BezierBy::create(3, bezier2);

// place
	//auto myAction = Place::create(Vec2(300, 200));

//ScaleBy , ScaleTo
//	auto myAction = ScaleBy::create(2, 2.0f);
//	auto myAction = ScaleTo::create(2, 2.0f);

//RotateBy, RotateTo
	auto myAction = RotateTo::create(2, 360);



	pMan->runAction(myAction);

}


/*
MoveTo = 리버스 액션 동작안함
JumpTo = 리버스 액션 에러남
RotateTo :  리버스 액션 에러
ScaleTo : 리버스 액션 에러
TintTo : 리버스 액션 에러

*/
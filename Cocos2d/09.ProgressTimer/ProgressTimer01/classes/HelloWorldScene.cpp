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
    
	pWoman1 = Sprite::create("Images/grossinis_sister1.png");
	pWoman2 = Sprite::create("Images/grossinis_sister2.png");

	this->SpriteProgressToRadial();
	//this->SpriteProgressToHorizontal();
	//this->SpriteProgressToVertical();
	//this->SpriteProgressToRadialMidpointChanged();
	//this->SpriteProgressBarVarious();
	//this->SpriteProgressBarTintAndFade();
	    
    return true;
}


void HelloWorld::SpriteProgressToRadial() {
	this->removeAllChildrenWithCleanup(true);

	auto to1 = ProgressTo::create(2, 100);
	auto to2 = ProgressTo::create(2, 100);

	auto left = ProgressTimer::create(pWoman1);

	left->setType(ProgressTimer::Type::RADIAL);
	addChild(left);
	left->setPosition(Vec2(140, 160));
	left->runAction(RepeatForever::create(to1));

	auto right = ProgressTimer::create(pWoman2);

	right->setType(ProgressTimer::Type::RADIAL);
	//makes the ridial CCW
	right->setReverseProgress(true);
	addChild(right);
	right->setPosition(Vec2(340, 160));
	right->runAction(RepeatForever::create(to2));
}

//------------------------------------------------------------------
//
// SpriteProgressToHorizontal
//
//------------------------------------------------------------------

void HelloWorld::SpriteProgressToHorizontal()
{
	this->removeAllChildrenWithCleanup(true);

	auto to1 = ProgressTo::create(2, 100);
	auto to2 = ProgressTo::create(2, 100);

	auto left = ProgressTimer::create(pWoman1);
	left->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the left since the midpoint is 0 for the x
	left->setMidpoint(Vec2(0, 0));
	// Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
	left->setBarChangeRate(Vec2(1, 0));
	addChild(left);
	left->setPosition(Vec2(140, 160));
	left->runAction(RepeatForever::create(to1));

	auto right = ProgressTimer::create(pWoman2);
	right->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the left since the midpoint is 1 for the x
	right->setMidpoint(Vec2(1, 0));
	// Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
	right->setBarChangeRate(Vec2(1, 0));
	addChild(right);
	right->setPosition(Vec2(340, 160));
	right->runAction(RepeatForever::create(to2));
}

//------------------------------------------------------------------
//
// SpriteProgressToVertical
//
//------------------------------------------------------------------

void HelloWorld::SpriteProgressToVertical()
{
	this->removeAllChildrenWithCleanup(true);

	auto to1 = ProgressTo::create(2, 100);
	auto to2 = ProgressTo::create(2, 100);

	auto left = ProgressTimer::create(pWoman1);
	left->setType(ProgressTimer::Type::BAR);

	// Setup for a bar starting from the bottom since the midpoint is 0 for the y
	left->setMidpoint(Vec2(0, 0));
	// Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
	left->setBarChangeRate(Vec2(0, 1));
	addChild(left);
	left->setPosition(Vec2(140, 160));
	left->runAction(RepeatForever::create(to1));

	auto right = ProgressTimer::create(pWoman2);
	right->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the bottom since the midpoint is 0 for the y
	right->setMidpoint(Vec2(0, 1));
	// Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
	right->setBarChangeRate(Vec2(0, 1));
	addChild(right);
	right->setPosition(Vec2(340, 160));
	right->runAction(RepeatForever::create(to2));
}

//------------------------------------------------------------------
//
// SpriteProgressToRadialMidpointChanged
//
//------------------------------------------------------------------

void HelloWorld::SpriteProgressToRadialMidpointChanged()
{
	this->removeAllChildrenWithCleanup(true);

	auto to1 = ProgressTo::create(2, 100);
	auto to2 = ProgressTo::create(2, 100);

	/**
	*  Our image on the left should be a radial progress indicator, clockwise
	*/
	auto left = ProgressTimer::create(pWoman1);
	left->setType(ProgressTimer::Type::RADIAL);
	addChild(left);
	left->setMidpoint(Vec2(0.25f, 0.75f));
	left->setPosition(Vec2(140, 160));
	left->runAction(RepeatForever::create(to1));

	/**
	*  Our image on the left should be a radial progress indicator, counter clockwise
	*/
	auto right = ProgressTimer::create(pWoman2);
	right->setType(ProgressTimer::Type::RADIAL);
	right->setMidpoint(Vec2(0.75f, 0.25f));

	/**
	*  Note the reverse property (default=NO) is only added to the right image. That's how
	*  we get a counter clockwise progress.
	*/
	addChild(right);
	right->setPosition(Vec2(340, 160));
	right->runAction(RepeatForever::create(to2));
}

//------------------------------------------------------------------
//
// SpriteProgressBarVarious
//
//------------------------------------------------------------------

void HelloWorld::SpriteProgressBarVarious()
{
	this->removeAllChildrenWithCleanup(true);

	auto to1 = ProgressTo::create(2, 100);
	auto to2 = ProgressTo::create(2, 100);
	auto to3 = ProgressTo::create(2, 100);

	auto left = ProgressTimer::create(pWoman1);
	left->setType(ProgressTimer::Type::BAR);

	// Setup for a bar starting from the bottom since the midpoint is 0 for the y
	left->setMidpoint(Vec2(0.5f, 0.5f));
	// Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
	left->setBarChangeRate(Vec2(1, 0));
	addChild(left);
	left->setPosition(Vec2(140, 160));
	left->runAction(RepeatForever::create(to1));

	auto middle = ProgressTimer::create(pWoman2);
	middle->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the bottom since the midpoint is 0 for the y
	middle->setMidpoint(Vec2(0.5f, 0.5f));
	// Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
	middle->setBarChangeRate(Vec2(1, 1));
	addChild(middle);
	middle->setPosition(Vec2(240, 160));
	middle->runAction(RepeatForever::create(to2));

	auto right = ProgressTimer::create(pWoman1);
	right->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the bottom since the midpoint is 0 for the y
	right->setMidpoint(Vec2(0.5f, 0.5f));
	// Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
	right->setBarChangeRate(Vec2(0, 1));
	addChild(right);
	right->setPosition(Vec2(340, 160));
	right->runAction(RepeatForever::create(to3));
}

//------------------------------------------------------------------
//
// SpriteProgressBarTintAndFade
//
//------------------------------------------------------------------

void HelloWorld::SpriteProgressBarTintAndFade()
{
	this->removeAllChildrenWithCleanup(true);

	auto to = ProgressTo::create(6, 100);

	auto tint = Sequence::create(TintTo::create(1, 255, 0, 0),
		TintTo::create(1, 0, 255, 0),
		TintTo::create(1, 0, 0, 255),
		NULL);
	auto fade = Sequence::create(FadeTo::create(1.0f, 0),
		FadeTo::create(1.0f, 255),
		NULL);

	auto left = ProgressTimer::create(pWoman1);
	left->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the bottom since the midpoint is 0 for the y
	left->setMidpoint(Vec2(0.5f, 0.5f));
	// Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
	left->setBarChangeRate(Vec2(1, 0));
	addChild(left);
	left->setPosition(Vec2(140, 160));
	left->runAction(RepeatForever::create(to->clone()));
	left->runAction(RepeatForever::create(tint->clone()));

	left->addChild(LabelTTF::create("Tint", "Marker Felt", 20.0f));


	auto middle = ProgressTimer::create(pWoman2);
	middle->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the bottom since the midpoint is 0 for the y
	middle->setMidpoint(Vec2(0.5f, 0.5f));
	// Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
	middle->setBarChangeRate(Vec2(1, 1));
	addChild(middle);
	middle->setPosition(Vec2(240, 160));
	middle->runAction(RepeatForever::create(to->clone()));
	middle->runAction(RepeatForever::create(fade->clone()));

	middle->addChild(LabelTTF::create("Fade", "Marker Felt", 20.0f));


	auto right = ProgressTimer::create(pWoman1);
	right->setType(ProgressTimer::Type::BAR);
	// Setup for a bar starting from the bottom since the midpoint is 0 for the y
	right->setMidpoint(Vec2(0.5f, 0.5f));
	// Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
	right->setBarChangeRate(Vec2(0, 1));
	addChild(right);
	right->setPosition(Vec2(340, 160));
	right->runAction(RepeatForever::create(to->clone()));
	right->runAction(RepeatForever::create(tint->clone()));
	right->runAction(RepeatForever::create(fade->clone()));

	right->addChild(LabelTTF::create("Tint and Fade", "Marker Felt", 20.0f));

}

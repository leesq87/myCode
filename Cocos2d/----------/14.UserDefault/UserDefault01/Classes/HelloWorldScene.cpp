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

	log("********************************* init value ************************");

	//set default value

	UserDefault::getInstance()->setStringForKey("str_key", "value1");
	UserDefault::getInstance()->setIntegerForKey("int_key", 10);
	UserDefault::getInstance()->setFloatForKey("float_key", 2.3f);
	UserDefault::getInstance()->setDoubleForKey("double_key", 2.4f);
	UserDefault::getInstance()->setBoolForKey("bool_key", true);

	//print value

	std::string ret = UserDefault::getInstance()->getStringForKey("str_key");
	log("string is :%s", ret.c_str());


	int i = UserDefault::getInstance()->getIntegerForKey("int_key");
	log("int is : %d", i);

	float f = UserDefault::getInstance()->getFloatForKey("float_key");
	log("float is : %f", f);

	double d = UserDefault::getInstance()->getDoubleForKey("double_key");
	log("double is : %f", d);

	bool b = UserDefault::getInstance()->getBoolForKey("bool_key");
	if (b)
		log("true");
	else
		log("fail");

	log("*****************************           *a*****************");

	//change the value
	UserDefault::getInstance()->setStringForKey("str_key", "value2");
	UserDefault::getInstance()->setIntegerForKey("int_key", 11);
	UserDefault::getInstance()->setFloatForKey("float_key", 2.5f);
	UserDefault::getInstance()->setDoubleForKey("double_key", 2.6f);
	UserDefault::getInstance()->setBoolForKey("bool_key", false);

	//print value

	ret = UserDefault::getInstance()->getStringForKey("str_key");
	log("string is :%s", ret.c_str());


	i = UserDefault::getInstance()->getIntegerForKey("int_key");
	log("int is : %d", i);

	f = UserDefault::getInstance()->getFloatForKey("float_key");
	log("float is : %f", f);

	d = UserDefault::getInstance()->getDoubleForKey("double_key");
	log("double is : %f", d);

	b = UserDefault::getInstance()->getBoolForKey("bool_key");
	if (b)
		log("true");
	else
		log("fail");

		
	return true;
}


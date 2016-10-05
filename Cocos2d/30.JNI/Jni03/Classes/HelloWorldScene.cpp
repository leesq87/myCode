#include "HelloWorldScene.h"
USING_NS_CC;
static HelloWorld *g_pHello = NULL;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform\android\jni\JniHelper.h"

void callJavaMethod(std::string func) {
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		func.c_str(),
		"()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);

		t.env->DeleteLocalRef(t.classID);
	}
}

#ifdef __cplusplus
extern "C" {
#endif
	void Java_org_cocos2dx_cpp_AppActivity_addSpriteInNative(JNIEnv *env, jobject obj) {
		g_pHello->addSpriteFromJava();
	}
	void Java_org_cocos2dx_cpp_AppActivity_removeSpriteInNative(JNIEnv *env, jobject obj) {
		g_pHello->removeSpriteFromJava();
	}

#ifdef __cplusplus
}
#endif
#endif




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


	MenuItemFont::setFontName("fonts/Marker Felt.ttf");
	auto pMenuItem1 = MenuItemFont::create("Add Sprite", CC_CALLBACK_1(HelloWorld::addSprite, this));
	pMenuItem1->setColor(Color3B::BLACK);

	auto pMenuItem2 = MenuItemFont::create("Remove Sprite", CC_CALLBACK_1(HelloWorld::removeSprite, this));
	pMenuItem2->setColor(Color3B::BLACK);

	auto pMenu = Menu::create(pMenuItem1, pMenuItem2, nullptr);

	pMenu->alignItemsVerticallyWithPadding(50.0f);
	this->addChild(pMenu);


	g_pHello = this;


    return true;
}

void HelloWorld::addSprite(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	callJavaMethod("AddSprite");
#endif
}

void HelloWorld::removeSprite(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	callJavaMethod("RemoveSprite");
#endif

}


void HelloWorld::addSpriteFromJava() {
	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Vec2(240, 160));
	sprite->setTag(1);
	this->addChild(sprite);
}

void HelloWorld::removeSpriteFromJava() {
	auto sprite = (Sprite*)this->getChildByTag(1);
	sprite->removeFromParent();
}

#include "HelloWorldScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#ifdef __cplusplus
extern "C" {
#endif

	jint Java_org_cocos2dx_cpp_AppActivity_cppSum(JNIEnv *env, jobject obj, jint a, jint b) {
		return a + b;
	}

#ifdef __cplusplus
}
#endif
#endif



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



	MenuItemFont::setFontName("fonts/Marker Felt.ttf");
	auto pMenuItem1 = MenuItemFont::create("Java Method Call", CC_CALLBACK_1(HelloWorld::callJavaMethod, this));

	pMenuItem1->setColor(Color3B(0, 0, 0));

	auto pMenu = Menu::create(pMenuItem1, nullptr);

	this->addChild(pMenu);



    return true;
}

void HelloWorld::callJavaMethod(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;

	if (JniHelper::getStaticMethodInfo(t,
		"org/cocos2dx/cpp/AppActivity",
		"JniTestFunc", "()V")) {
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);

	}
#endif
}
